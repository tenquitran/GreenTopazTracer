#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////

// Epsilon for intersection calculations, etc.
const VComponent GeometricObject::FloatingEpsilon = 0.001;

//////////////////////////////////////////////////////////////////////////


GeometricObject::GeometricObject(const Vector3& center, bool isLight /*= false*/)
	: m_center(center), m_isLight(isLight)
{
}

GeometricObject::~GeometricObject()
{
}
