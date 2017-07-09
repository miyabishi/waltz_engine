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
{
}
