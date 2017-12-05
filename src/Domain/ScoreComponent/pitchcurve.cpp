#include <QtMath>
#include <QTextStream>
#include "pitchcurve.h"

using namespace waltz::engine::ScoreComponent;


namespace
{
    bool PitchChangingPointLessThan(const PitchChangingPointPointer& a,
                                    const PitchChangingPointPointer& b)
    {
        return a->position().value() < b->position().value();
    }

    double interpolation(double aX, double aPreX, double aPreY, double aPostX, double aPostY)
    {
        if (aPreY == aPostY)
        {
            return aPreY;
        }
        double t = (aX - aPreX)/(aPostX - aPreX);

        return aPreY + (-cos(t * M_PI) + 1) / 2 * (aPostY - aPreY);
    }
}

PitchCurve::PitchCurve()
{
}

void PitchCurve::clear()
{
    mPitchCurve_.clear();
}

void PitchCurve::append(const PitchChangingPointPointer& aPitchChangingPoint)
{
    mPitchCurve_.append(aPitchChangingPoint);
}

double PitchCurve::calculateValue(const MilliSeconds& aPosition)
{
    if (mPitchCurve_.size() == 0) return 0;
    if (mPitchCurve_.size() == 1) return mPitchCurve_.first()->value();

    qSort(mPitchCurve_.begin(), mPitchCurve_.end(), PitchChangingPointLessThan);
    for(int index = 0; index < mPitchCurve_.size() - 1; ++index)
    {
        PitchChangingPointPointer pre = mPitchCurve_.at(index);
        PitchChangingPointPointer post = mPitchCurve_.at(index + 1);
        if (pre->position().value() < aPosition.value() &&
            aPosition.value() <= post->position().value())
        {
            /*
            return ((post->value() - pre->value())/
                    (post->position().value() - pre->position().value()))
                    * (aPosition.value() - pre->position().value())
                    + pre->value();
                    */
            // 動作未確認
            return interpolation(aPosition.value(),
                                 pre->position().value(), pre->value(),
                                 post->position().value(), post->value());
        }
    }
    return mPitchCurve_.last()->value();
}

int PitchCurve::length() const
{
    return mPitchCurve_.length();
}

void PitchCurve::outputForDebug(const QString& aFileName)
{
    QFile file(aFileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
         return;

    QTextStream out(&file);
    foreach(const PitchChangingPointPointer& point, mPitchCurve_)
    {
        out << QString("%1\t%2").arg(point->position().value()).arg(point->value()) << "\n";
    }
    file.close();
}
