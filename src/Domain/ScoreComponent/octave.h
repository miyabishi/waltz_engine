#ifndef OCTAVE_H
#define OCTAVE_H


namespace waltz
{
    namespace engine
    {
        namespace ScoreComponent
        {
            class Octave
            {
            public:
                Octave(const int aValue);
                Octave(const Octave& aOther);
                Octave& operator=(const Octave& aOther);
            public:
                double multiplyOctave(double aBaseFrequency) const;

            private:
                int mValue_;
            };
        } // namespace ScoreComponent
    } // namespace engine
} // namespace waltz

#endif // OCTAVE_H
