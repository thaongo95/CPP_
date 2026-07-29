#ifndef MBTILESPROVIDER_H
#define MBTILESPROVIDER_H

#include <QQuickImageProvider>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QImage>
#include <QDebug>

class MBTilesProvider : public QQuickImageProvider
{
public:
    MBTilesProvider();
    ~MBTilesProvider();

    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

    bool openMBTiles(const QString &filePath);
    void closeMBTiles();
    QString metadata(const QString &key);
    QVariantMap allMetadata();

private:
    QSqlDatabase m_db;
    bool m_isOpen;
};

#endif // MBTILESPROVIDER_H
