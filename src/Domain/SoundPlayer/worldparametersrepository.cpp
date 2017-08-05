#include "worldparametersrepository.h"

using namespace waltz::engine::SoundPlayer;

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

