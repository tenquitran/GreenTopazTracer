#pragma once


namespace GreenTopazTracerApp
{
    // Exposure tone mapping algorithm.
    class ToneMapperExposure
        : public ToneMapper
    {
    public:
        ToneMapperExposure(ClrComponent exposure, ClrComponent gamma);

        // Return the color converted according to the tone mapping algorithm (with gamma correction).
        virtual Color convert(const Color& clr) const override;

    private:
        const ClrComponent m_exposure = { 1.0 };

        // Value for gamma correction.
        const ClrComponent m_gamma = { 2.2 };
    };
}
