#ifndef WORLDPARAMETER_H
#define WORLDPARAMETER_H

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
        }
    }
}


#endif // WORLDPARAMETER_H
