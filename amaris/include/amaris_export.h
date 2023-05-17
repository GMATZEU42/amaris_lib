#pragma once

#ifdef _WIN32
#ifdef AMARIS_EXPORT
#define AMARIS_API __declspec(dllexport)
#else
#define AMARIS_API __declspec(dllimport)
#endif
#else	// case unix
#define AMARIS_API __attribute__ ((visibility ("default")))
#endif