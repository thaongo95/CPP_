#include "mbtilesprovider.h"
#include <QSqlError>
#include <QFileInfo>
#include <cmath>

MBTilesProvider::MBTilesProvider()
    : QQuickImageProvider(QQuickImageProvider::Image),
    m_isOpen(false)
{
}

MBTilesProvider::~MBTilesProvider()
{
    closeMBTiles();
}

bool MBTilesProvider::openMBTiles(const QString &filePath)
{
    if (m_isOpen) {
        closeMBTiles();
    }

    // Convert to absolute path and verify file exists
    QFileInfo fileInfo(filePath);
    if (!fileInfo.exists()) {
        qWarning() << "File does not exist:" << filePath;
        return false;
    }

    QString absolutePath = fileInfo.absoluteFilePath();
    qDebug() << "Opening MBTiles file:" << absolutePath;

    m_db = QSqlDatabase::addDatabase("QSQLITE", "mbtiles_connection");
    m_db.setDatabaseName(absolutePath);

    if (!m_db.open()) {
        qWarning() << "Failed to open MBTiles database:" << m_db.lastError().text();
        qWarning() << "Database path:" << absolutePath;
        return false;
    }

    m_isOpen = true;
    return true;
}

void MBTilesProvider::closeMBTiles()
{
    if (m_isOpen) {
        m_db.close();
        m_db = QSqlDatabase();
        QSqlDatabase::removeDatabase("mbtiles_connection");
        m_isOpen = false;
    }
}
QImage MBTilesProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(requestedSize);

    if (!m_isOpen) {
        qWarning() << "MBTiles database not open";
        return QImage();
    }

    QStringList parts = id.split('/');
    if (parts.size() != 3) {
        qWarning() << "Invalid tile ID format:" << id;
        return QImage();
    }

    bool ok;
    int zoom = parts[0].toInt(&ok);
    if (!ok) {
        qWarning() << "Invalid zoom level:" << parts[0];
        return QImage();
    }

    double lon = parts[1].toDouble(&ok);
    if (!ok) {
        qWarning() << "Invalid longitude:" << parts[1];
        return QImage();
    }

    double lat = parts[2].toDouble(&ok);
    if (!ok) {
        qWarning() << "Invalid latitude:" << parts[2];
        return QImage();
    }

    // Convert geographic coordinates to tile coordinates
    double lat_rad = lat * M_PI / 180.0;
    double n = pow(2.0, zoom);
    int xtile = static_cast<int>(n * ((lon + 180.0) / 360.0));
    int ytile = static_cast<int>(n * (1.0 - (log(tan(lat_rad) + 1.0/cos(lat_rad)) / M_PI)) / 2.0);

    // Convert to TMS scheme
    int tmsRow = static_cast<int>(n) - 1 - ytile;

    qDebug() << "Fetching tile - Zoom:" << zoom << "X:" << xtile << "Y:" << ytile << "TMS Y:" << tmsRow;

    QSqlQuery query(m_db);
    query.prepare("SELECT tile_data FROM tiles WHERE zoom_level = ? AND tile_column = ? AND tile_row = ?");
    query.addBindValue(zoom);
    query.addBindValue(xtile);
    query.addBindValue(tmsRow);

    if (!query.exec()) {
        qWarning() << "Query failed:" << query.lastError().text();
        return QImage();
    }

    if (!query.next()) {
        qWarning() << "Tile not found at zoom" << zoom << "x:" << xtile << "y:" << tmsRow;
        return QImage();
    }

    QByteArray imageData = query.value(0).toByteArray();
    QImage image;
    if (!image.loadFromData(imageData)) {
        qWarning() << "Failed to load image data";
        return QImage();
    }

    if (size) {
        *size = image.size();
    }

    return image;
}
// QImage MBTilesProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
// {
//     Q_UNUSED(requestedSize);

//     if (!m_isOpen) {
//         return QImage();
//     }

//     QStringList parts = id.split('/');
//     if (parts.size() != 3) {
//         return QImage();
//     }

//     int zoom = parts[0].toInt();
//     int column = parts[1].toInt();
//     int row = parts[2].toInt();

//     int tmsRow = (1 << zoom) - 1 - row;

//     QSqlQuery query(m_db);
//     query.prepare("SELECT tile_data FROM tiles WHERE zoom_level = ? AND tile_column = ? AND tile_row = ?");
//     query.addBindValue(zoom);
//     query.addBindValue(column);
//     query.addBindValue(tmsRow);

//     if (!query.exec() || !query.next()) {
//         return QImage();
//     }

//     QByteArray imageData = query.value(0).toByteArray();
//     QImage image;
//     if (!image.loadFromData(imageData)) {
//         return QImage();
//     }

//     if (size) {
//         *size = image.size();
//     }

//     return image;

// }

QString MBTilesProvider::metadata(const QString &key)
{
    if (!m_isOpen) {
        return QString();
    }

    QSqlQuery query(m_db);
    query.prepare("SELECT value FROM metadata WHERE name = ?");
    query.addBindValue(key);

    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }

    return QString();
}

QVariantMap MBTilesProvider::allMetadata()
{
    QVariantMap result;
    if (!m_isOpen) {
        return result;
    }

    QSqlQuery query(m_db);
    query.prepare("SELECT name, value FROM metadata");

    if (query.exec()) {
        while (query.next()) {
            result[query.value(0).toString()] = query.value(1).toString();
        }
    }

    return result;
}
