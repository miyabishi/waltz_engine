#ifndef VOCAL_H
#define VOCAL_H

#include <waltzvocalagent.h>
#include <QString>
#include "src/Domain/SoundPlayer/player.h"

namespace waltz
{
    namespace engine
    {
        namespace ScoreComponent
        {
            class Note;
            class Score;
        }
        namespace VocalComponent
        {
            class Vocal
            {
            public:
                static Vocal& getInstance();
                void loadVoiceLibrary(const QString& aPath);
                void singSingleNote(
                        const waltz::engine::ScoreComponent::Note& aNote);
                void sing(const waltz::engine::ScoreComponent::Score& aScore);
                void stopSinging();
                waltz::agent::WaltzVocalAgent* vocalAgent();

            private:
                static Vocal*                      mInstance_;
                waltz::agent::WaltzVocalAgent      mVocalAgent_;
                waltz::engine::SoundPlayer::Player mPlayer_;

            private:
                Vocal();
            };

        } // namespace VocalComponent
    } // namespace engine
} // namespace waltz

#endif // VOCAL_H
