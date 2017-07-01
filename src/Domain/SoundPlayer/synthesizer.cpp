#include "world/harvest.h"
#include "world/dio.h"
#include "world/stonemask.h"
#include "world/cheaptrick.h"
#include "world/d4c.h"
#include "world/synthesis.h"

#include "synthesizer.h"
using namespace waltz::engine::SoundPlayer;

Synthesizer* Synthesizer::mInstance_ = 0;

Synthesizer& Synthesizer::getInstance()
{
    if(mInstance_ == 0)
    {
        static Synthesizer instance;
        mInstance_ = &instance;
    }
    return *mInstance_;
}

void Synthesizer::estimateF0(double *aInput,
                int aLengthOfInput,
                WorldParameters *aWorldParameters)
{
        /*
      HarvestOption option = { 0 };
      InitializeHarvestOption(&option);
      option.frame_period = aWorldParameters->framePeriod;

      // You can set the f0_floor below world::kFloorF0.
      option.f0_floor = 40.0;

      // Parameters setting and memory allocation.
      aWorldParameters->lengthOfF0 = GetSamplesForHarvest(aWorldParameters->samplingFrequency,
        aLengthOfInput, aWorldParameters->framePeriod);
      aWorldParameters->f0 = new double[aWorldParameters->lengthOfF0];
      aWorldParameters->timeAxis = new double[aWorldParameters->lengthOfF0];

      Harvest(aInput, aLengthOfInput, aWorldParameters->samplingFrequency, &option,
              aWorldParameters->timeAxis, aWorldParameters->f0);
    */

    DioOption option;
    InitializeDioOption(&option);

    option.frame_period  = aWorldParameters->framePeriod;
    option.speed         = 1;
    option.f0_floor      = 40.0;
    option.allowed_range = 0.1;

    aWorldParameters->lengthOfF0 = GetSamplesForDIO(aWorldParameters->samplingFrequency,
                                                    aLengthOfInput,
                                                    aWorldParameters->framePeriod);
    aWorldParameters->f0         = new double[aWorldParameters->lengthOfF0];
    aWorldParameters->timeAxis   = new double[aWorldParameters->lengthOfF0];
    double *refinedF0            = new double[aWorldParameters->lengthOfF0];

    Dio(aInput,
        aLengthOfInput,
        aWorldParameters->samplingFrequency,
        &option,
        aWorldParameters->timeAxis,
        aWorldParameters->f0);

    StoneMask(aInput,
            aLengthOfInput,
            aWorldParameters->samplingFrequency,
            aWorldParameters->timeAxis,
            aWorldParameters->f0,
            aWorldParameters->lengthOfF0,
            refinedF0);

    for (int index = 0; index < aWorldParameters->lengthOfF0; ++index)
    {
        aWorldParameters->f0[index] = refinedF0[index];
    }

    delete[] refinedF0;

}

void Synthesizer::SpectralEnvelopeEstimation(double *aInput,
                                int aLengthOfInput,
                                WorldParameters *aWorldParameters)
{
    CheapTrickOption option = { 0 };
    InitializeCheapTrickOption(aWorldParameters->samplingFrequency, &option);
    option.f0_floor = 71.0;
    option.fft_size = GetFFTSizeForCheapTrick(aWorldParameters->samplingFrequency, &option);

    aWorldParameters->sizeOfFFT   = option.fft_size;
    aWorldParameters->spectrogram = new double *[aWorldParameters->lengthOfF0];

    for (int index = 0; index < aWorldParameters->lengthOfF0; ++index)
    {
        aWorldParameters->spectrogram[index] =
            new double[aWorldParameters->sizeOfFFT / 2 + 1];
    }

    CheapTrick(aInput,
               aLengthOfInput,
               aWorldParameters->samplingFrequency,
               aWorldParameters->timeAxis,
               aWorldParameters->f0,
               aWorldParameters->lengthOfF0,
               &option,
               aWorldParameters->spectrogram);
}

void Synthesizer::AperiodicityEstimation(double *aInput,
                            int aLengthOfInput,
                            WorldParameters *aWorldParameters)
{
    D4COption option = {0};
    InitializeD4COption(&option);

    option.threshold = 0.85;

    aWorldParameters->aperiodicity = new double *[aWorldParameters->lengthOfF0];
    for (int i = 0; i < aWorldParameters->lengthOfF0; ++i)
    {
        aWorldParameters->aperiodicity[i] =
          new double[aWorldParameters->sizeOfFFT / 2 + 1];
    }

    D4C(aInput,
        aLengthOfInput,
        aWorldParameters->samplingFrequency,
        aWorldParameters->timeAxis,
        aWorldParameters->f0,
        aWorldParameters->lengthOfF0,
        aWorldParameters->sizeOfFFT,
        &option,
        aWorldParameters->aperiodicity);
}

void Synthesizer::DestroyMemory(WorldParameters *aWorldParameters)
{
    delete[] aWorldParameters->timeAxis;
    delete[] aWorldParameters->f0;
    for (int index = 0; index < aWorldParameters->lengthOfF0; ++index)
    {
        delete[] aWorldParameters->spectrogram[index];
        delete[] aWorldParameters->aperiodicity[index];
    }
    delete[] aWorldParameters->spectrogram;
    delete[] aWorldParameters->aperiodicity;
}

void Synthesizer::WaveformSynthesis(WorldParameters *aWorldParameters,
                                    int aSamplingFrequency,
                                    int aLengthOfOutput,
                                    double *aOutput)
{
    Synthesis(aWorldParameters->f0, aWorldParameters->lengthOfF0,
        aWorldParameters->spectrogram, aWorldParameters->aperiodicity,
        aWorldParameters->sizeOfFFT, aWorldParameters->framePeriod,
        aSamplingFrequency,
        aLengthOfOutput,
        aOutput);
}

Synthesizer::Synthesizer()
{
}

