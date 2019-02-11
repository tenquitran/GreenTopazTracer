// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// Additional headers our program requires.

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <limits>
#include <random>
#include <atomic>
#include <thread>

// ATL and COM functionality for WIC-based ImageProcessor.
#include <Objbase.h>
#include <comdef.h>
#include <atlbase.h>
#include <atltime.h>

#include <Wincodec.h>


namespace GreenTopazTracerApp
{
// Get local time for logging.
#define TIME_STR()    ATL::CTime::GetCurrentTime().Format(L"%d.%m.%Y %H:%M:%S ").GetString()
}


#include "Exception.h"

#include "Vector3.h"

#include "Color.h"

#include "Ray.h"

#include "HitInfo.h"

#include "MaterialType.h"
#include "Material.h"
#include "MaterialPhong.h"
#include "MaterialEmissive.h"

#include "GeometricObject.h"
#include "Plane.h"
#include "Sphere.h"

#include "Scene.h"

#include "ImageProcessor.h"

#include "Sampler.h"

#include "PixelCounter.h"
