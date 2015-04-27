#ifndef MacrosAndDefines_h__
#define MacrosAndDefines_h__

#include <string>
#include <tchar.h>

#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif

#endif // MacrosAndDefines_h__
