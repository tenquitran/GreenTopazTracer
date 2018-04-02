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

// ATL and COM functionality for WIC-based ImageProcessor.
#include <Objbase.h>
#include <comdef.h>
#include <atlbase.h>

#include <Wincodec.h>

#include "Exception.h"

#include "Vector3.h"

#include "Color.h"

#include "Ray.h"

#include "HitInfo.h"

#include "GeometricObject.h"
#include "Plane.h"
#include "Sphere.h"

#include "Scene.h"

#include "ImageProcessor.h"

#include "Sampler.h"
