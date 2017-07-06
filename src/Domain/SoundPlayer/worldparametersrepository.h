#ifndef WORLDPARAMETERSREPOSITORY_H
#define WORLDPARAMETERSREPOSITORY_H


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

            private:
                static WorldParametersRepository* mInstance_;

            private:
                WorldParametersRepository();
            };

        } // namespace SoundPlayer
    } // namespace engine
} // namespace waltz

#endif // WORLDPARAMETERSREPOSITORY_H
