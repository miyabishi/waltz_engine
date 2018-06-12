#ifndef WORLDPARAMETERSREPOSITORY_H
#define WORLDPARAMETERSREPOSITORY_H

#include <QMap>
#include <QSqlDatabase>
#include <QDir>
#include <QPointer>

#include "worldparameters.h"
#include "worldparameterscacheid.h"
#include "worldparameterscache.h"

namespace waltz
{
    namespace engine
    {
        namespace SoundPlayer
        {

            class WorldParametersRepository
            {
            public:
                static WorldParametersRepository& getInstance();
                bool open(const QString& aDbPath);

                bool hasWorldParammeters(const WorldParametersCacheId& aWorldParametersCacheId) const;

                void loadWorldParameters(const WorldParametersCacheId& aWorldParametersCacheId,
                                         WorldParameters* aWorldParameters);
                void registerWorldParameters(const WorldParametersCacheId& aWorldParametersCacheId,
                                             WorldParameters* aWorldParameters);

            private:
                static WorldParametersRepository* mInstance_;
                QSqlDatabase mDatabase_;

            private:
                WorldParametersRepository();
                ~WorldParametersRepository();
            };

        } // namespace SoundPlayer
    } // namespace engine
} // namespace waltz

#endif // WORLDPARAMETERSREPOSITORY_H
