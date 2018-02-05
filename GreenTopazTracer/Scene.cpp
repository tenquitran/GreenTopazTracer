#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////

using namespace GreenTopazTracerApp;

//////////////////////////////////////////////////////////////////////////


Scene::Scene()
	: m_backgroundColor(Color(0.0, 0.0, 1.0))    // blue
{
	// Add a sphere with the center at the origin
	m_objects.emplace_back(std::make_unique<Sphere>(Vector3(), 85.0));
}

Scene::~Scene()
{
}
