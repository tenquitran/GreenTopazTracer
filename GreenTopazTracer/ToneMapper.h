#pragma once


namespace GreenTopazTracerApp
{
    // Abstract base class for tone mapping algorithms.
    class ToneMapper
    {
    public:
        explicit ToneMapper(EToneMapping algorithm);

        EToneMapping getAlgorithm() const;

        // Return the color converted according to the tone mapping algorithm (with gamma correction).
        virtual Color convert(const Color& clr) const = 0;

        // Tone mapper factory.
        static std::unique_ptr<ToneMapper> createToneMapper(EToneMapping algorithm, ClrComponent exposure, ClrComponent gamma);

    private:
        ToneMapper(const ToneMapper&) = delete;
        ToneMapper& operator=(const ToneMapper&) = delete;

    private:
        const EToneMapping m_algorithm;
    };
}
