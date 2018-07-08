#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include "worldparametersrepository.h"
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlQuery>

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
{
}

WorldParametersRepository::~WorldParametersRepository()
{
}


bool WorldParametersRepository::open(const QString &aDbPath)
{
    mDatabase_ = QSqlDatabase::addDatabase("QSQLITE");
    mDatabase_.setDatabaseName(aDbPath);
    return mDatabase_.open();
}

bool WorldParametersRepository::hasWorldParammeters(const WorldParametersCacheId& aWorldParametersCacheId) const
{
    if (! mDatabase_.isOpen()) return false;
    QSqlQuery query;
    query.prepare("SELECT id FROM cache WHERE id = (:id)");
    query.bindValue(":id", aWorldParametersCacheId.value());

    if (query.exec())
    {
        if (query.next())
        {
            return true;
        }
    }
    return false;
}

void WorldParametersRepository::loadWorldParameters(const WorldParametersCacheId& aWorldParametersCacheId,
                                                    WorldParameters* aWorldParameters)
{
    if (! mDatabase_.isOpen()) return;

    QSqlQuery query;
    query.prepare("SELECT json FROM cache WHERE id = (:id)");
    query.bindValue(":id", aWorldParametersCacheId.value());
    if(! query.exec()) return;
    int idJson = query.record().indexOf("json");

    while (query.next())
    {
       QJsonDocument jsonDocument = QJsonDocument::fromBinaryData(
                   qUncompress(query.value(idJson).toByteArray())
                   );
       WorldParametersCachePointer cache(
                   new WorldParametersCache(jsonDocument.object())
                   );

       cache->createWorldParameters(aWorldParameters);
    }
}

void WorldParametersRepository::registerWorldParameters(const WorldParametersCacheId& aWorldParametersCacheId,
                                                        WorldParameters* aWorldParameters)
{
    if (! mDatabase_.isOpen()) return;
    if (hasWorldParammeters(aWorldParametersCacheId)) return;

    QSqlQuery query;
    query.prepare("INSERT INTO cache (id, json) VALUES (:id, :json)");
    query.bindValue(":id", aWorldParametersCacheId.value());

    WorldParametersCachePointer cache(
                new WorldParametersCache(aWorldParameters));

    QJsonDocument doc(cache->toJsonObject());
    query.bindValue(":json", qCompress(doc.toBinaryData()));
}
