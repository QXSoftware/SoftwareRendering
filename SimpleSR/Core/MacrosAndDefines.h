#ifndef MacrosAndDefines_h__
#define MacrosAndDefines_h__

#include <sstream>
#include <string>
#include <tchar.h>

#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

#ifdef _UNICODE
typedef std::wstringstream tstringstream;
#else
typedef std::stringstream tstringstream;
#endif

typedef unsigned char RegionCode;

static const RegionCode CVV_LEFT   = 1 << 0;
static const RegionCode CVV_RIGHT  = 1 << 1;
static const RegionCode CVV_BOTTOM = 1 << 2;
static const RegionCode CVV_TOP    = 1 << 3;
static const RegionCode CVV_NEAR   = 1 << 4;
static const RegionCode CVV_FAR    = 1 << 5;

#define W_CLIPPING_PLANE (0.0001f)

#endif // MacrosAndDefines_h__
