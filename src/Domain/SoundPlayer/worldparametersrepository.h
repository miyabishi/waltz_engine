#ifndef WORLDPARAMETERSREPOSITORY_H
#define WORLDPARAMETERSREPOSITORY_H

#include <QMap>
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
                bool hasWorldParammeters(const WorldParametersCacheId& aWorldParametersCacheId) const;

                void loadWorldParameters(const WorldParametersCacheId& aWorldParametersCacheId,
                                         WorldParameters* aWorldParameters);
                void registerWorldParameters(const WorldParametersCacheId& aWorldParametersCacheId,
                                             WorldParameters* aWorldParameters);

                void saveToFile(const QString& aFilePath) const;
                void loadFromFile(const QString& aFilePath);

            private:
                static WorldParametersRepository* mInstance_;
                QMap<QString, WorldParametersCachePointer> mWorldParametersRepository_;

            private:
                WorldParametersRepository();
            };

        } // namespace SoundPlayer
    } // namespace engine
} // namespace waltz

#endif // WORLDPARAMETERSREPOSITORY_H
