#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////


#if 0
MaterialPhong::MaterialPhong()
{
}
#endif

MaterialPhong::MaterialPhong(const Color& ambient, const Color& diffuse, const Color& specular, 
	double specularity, double reflectivity /*= 0.0*/, double opacity /*= 1.0*/, double refractionIndex /*= 1.0*/)
	: m_ambientColor(ambient), m_diffuseColor(diffuse), m_specularColor(specular), m_specularity(specularity), 
	  m_reflectivity(reflectivity), m_opacity(opacity), m_refractionIndex(refractionIndex)
{
}

MaterialPhong::~MaterialPhong()
{
}

Color MaterialPhong::calculateColor(const HitInfo& hitInfo) const
{
	// TODO: stub
	return m_diffuseColor;
}
