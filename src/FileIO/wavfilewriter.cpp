#include "wavfilewriter.h"

using namespace waltz::engine::FileIO;

WavFileWriter* WavFileWriter::mInstance_ = 0;

WavFileWriter& WavFileWriter::getInstance()
{
    if (mInstance_ == 0)
    {
        static WavFileWriter instance;
        mInstance_ = &instance;
    }
    return *mInstance_;
}

void WavFileWriter::write()
{

}

WavFileWriter::WavFileWriter()
{
}
