#ifndef MacrosAndDefines_h__
#define MacrosAndDefines_h__

#include <string>
#include <tchar.h>

#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

typedef unsigned char RegionCode;

static const RegionCode CVV_LEFT   = 1 << 0;
static const RegionCode CVV_RIGHT  = 1 << 1;
static const RegionCode CVV_BOTTOM = 1 << 2;
static const RegionCode CVV_TOP    = 1 << 3;
static const RegionCode CVV_NEAR   = 1 << 4;
static const RegionCode CVV_FAR    = 1 << 5;

#endif // MacrosAndDefines_h__
