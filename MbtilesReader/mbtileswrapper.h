#ifndef MBTILESWRAPPER_H
#define MBTILESWRAPPER_H

#include <QObject>
#include <QVariantMap>
#include "mbtilesprovider.h"

class MBTilesWrapper : public QObject
{
    Q_OBJECT
public:
    explicit MBTilesWrapper(QObject *parent = nullptr);
    ~MBTilesWrapper();

    Q_INVOKABLE bool openMBTiles(const QString &filePath);
    Q_INVOKABLE QVariantMap allMetadata();
    MBTilesProvider* provider() const;

private:
    MBTilesProvider *m_provider;
};

#endif // MBTILESWRAPPER_H
