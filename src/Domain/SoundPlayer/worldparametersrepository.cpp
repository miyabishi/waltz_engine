#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include "worldparametersrepository.h"

using namespace waltz::engine::SoundPlayer;

namespace
{
    const QString KEY_PARAMETER_CACHE("WorldParameterCache");
    const QString KEY_PARAMETER_CACHE_ID("WorldParameterCacheId");
    const QString KEY_PARAMETER_CACHE_VALUE("WorldParameterCacheValue");
}

WorldParametersRepository* WorldParametersRepository::mInstance_ = 0;

WorldParametersRepository& WorldParametersRepository::getInstance()
{
    if(0 == mInstance_)
    {
        static WorldParametersRepository instance;
        mInstance_ = &instance;
    }
    return *mInstance_;
}

WorldParametersRepository::WorldParametersRepository()
    : mWorldParametersRepository_()
{

}

bool WorldParametersRepository::hasWorldParammeters(const WorldParametersCacheId& aWorldParametersCacheId) const
{
    return mWorldParametersRepository_.contains(aWorldParametersCacheId.value());
}

void WorldParametersRepository::loadWorldParameters(const WorldParametersCacheId& aWorldParametersCacheId,
                                                    WorldParameters* aWorldParameters)
{
    WorldParametersCachePointer cache = mWorldParametersRepository_[aWorldParametersCacheId.value()];
    if (cache.isNull())
    {
        return;
    }
    cache->createWorldParameters(aWorldParameters);
}

void WorldParametersRepository::registerWorldParameters(const WorldParametersCacheId& aWorldParametersCacheId,
                                                        WorldParameters* aWorldParameters)
{
    mWorldParametersRepository_[aWorldParametersCacheId.value()] =
            WorldParametersCachePointer(
                new WorldParametersCache(aWorldParameters));
}

void WorldParametersRepository::saveToFile(const QString &aFilePath) const
{
    QJsonObject jsonObject;
    QJsonArray jsonArray;
    QMap<QString, WorldParametersCachePointer>::const_iterator i = mWorldParametersRepository_.constBegin();
    while (i != mWorldParametersRepository_.constEnd()) {
        QJsonObject cacheJsonObject;
        cacheJsonObject[KEY_PARAMETER_CACHE_ID] = i.key();
        cacheJsonObject[KEY_PARAMETER_CACHE_VALUE] = i.value()->toJsonObject();

        jsonArray.append(cacheJsonObject);
        ++i;
    }
    jsonObject[KEY_PARAMETER_CACHE] = jsonArray;

    QJsonDocument jsonDocument(jsonObject);
    QByteArray data = jsonDocument.toJson();
    QFile saveFile(aFilePath);
    saveFile.open(QIODevice::WriteOnly);
    saveFile.write(data);
    saveFile.close();
}

void WorldParametersRepository::loadFromFile(const QString &aFilePath)
{
    QFile openFile(aFilePath);
    openFile.open(QIODevice::ReadOnly);
    QByteArray data = openFile.readAll();
    openFile.close();

    QJsonDocument jsonDocument(QJsonDocument::fromJson(data));
    QJsonObject jsonObject(jsonDocument.object());
    QJsonValue parameterCache = jsonObject.find(KEY_PARAMETER_CACHE).value();
    QJsonArray parameterCacheArray = parameterCache.toArray();

    foreach(const QJsonValue& value, parameterCacheArray)
    {
        QJsonObject object = value.toObject();
        QJsonValue parameterCacheId = object.find(KEY_PARAMETER_CACHE_ID).value();
        QJsonValue cacheValue = object.find(KEY_PARAMETER_CACHE_VALUE).value();
        mWorldParametersRepository_[parameterCacheId.toString()]
                = WorldParametersCachePointer(
                    new WorldParametersCache(cacheValue.toObject())
                    );
    }
}
