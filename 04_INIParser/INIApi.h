#pragma once

#ifdef INI_BUILD_DLL
#define INI_API __declspec(dllexport)
#else
#define INI_API __declspec(dllimport)
#endif
