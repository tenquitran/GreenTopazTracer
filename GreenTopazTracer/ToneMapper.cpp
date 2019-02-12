#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////


ToneMapper::ToneMapper(EToneMapping algorithm)
    : m_algorithm(algorithm)
{
}

EToneMapping ToneMapper::getAlgorithm() const
{
    return m_algorithm;
}

std::unique_ptr<ToneMapper> ToneMapper::createToneMapper(EToneMapping algorithm, ClrComponent exposure, ClrComponent gamma)
{
    switch (algorithm)
    {
    case EToneMapping::Exposure:
        return std::make_unique<ToneMapperExposure>(exposure, gamma);
    case EToneMapping::None:
        std::wcerr << __FUNCTIONW__ << L": invalid tone mapping algorithm\n";
        ATLASSERT(FALSE); return nullptr;
    default:
        // TODO: implement
        ATLASSERT(FALSE); return nullptr;
    }
}
