#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

#include <QByteArray>
#include <QVector>

namespace waltz
{
    namespace engine
    {
        namespace SoundPlayer
        {
            typedef struct
            {
                double framePeriod;
                int samplingFrequency;

                double *f0;
                double *timeAxis;
                int lengthOfF0;

                double **spectrogram;
                double **aperiodicity;
                int sizeOfFFT;
            } WorldParameters;

            class Synthesizer
            {

            public:
                static Synthesizer& getInstance();
                void estimateF0(double *aInput,
                                int aLengthOfInput,
                                WorldParameters *aWorldParameters);
                void SpectralEnvelopeEstimation(double *aInput,
                                                int aLengthOfInput,
                                                WorldParameters *aWorldParameters);
                void AperiodicityEstimation(double *aInput,
                                            int aLengthOfInput,
                                            WorldParameters *aWorldParameters);
                void DestroyMemory(WorldParameters *aWorldParameters);
                void WaveformSynthesis(WorldParameters *aWorldParameters,
                                       int aSamplingFrequency,
                                       int aLengthOfOutput,
                                       double* aOutput);
            private:
                static Synthesizer* mInstance_;

            private:
                Synthesizer();
            };

        } // namespace VocalComponent
    } // namespace engine
} // namespace waltz

#endif // SYNTHESIZER_H
