#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////


Material::Material(EMaterialType type)
    : m_type(type)
{
    if (EMaterialType::Undefined == m_type)
    {
        ATLASSERT(FALSE); throw EXCEPTION(L"Invalid material type");
    }
}

Material::~Material()
{
}

EMaterialType Material::getType() const
{
    return m_type;
}
