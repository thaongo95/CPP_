#include "mbtileswrapper.h"

MBTilesWrapper::MBTilesWrapper(QObject *parent)
    : QObject(parent), m_provider(new MBTilesProvider())
{
}

MBTilesWrapper::~MBTilesWrapper()
{
    delete m_provider;
}

bool MBTilesWrapper::openMBTiles(const QString &filePath)
{
    return m_provider->openMBTiles(filePath);
}

QVariantMap MBTilesWrapper::allMetadata()
{
    return m_provider->allMetadata();
}

MBTilesProvider* MBTilesWrapper::provider() const
{
    return m_provider;
}
