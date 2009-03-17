#ifndef H_STDAFX
#define H_STDAFX

// for Visual Studio 2005-2008
#if defined(_WIN32) || defined(WIN32) || defined(WINVER) || defined(_WIN32_WINNT)
#define L2PACKETS_WINDOWS
#define _CRT_SECURE_NO_DEPRECATE // vc2005
#define _CRT_SECURE_NO_WARNINGS // vc2008
#define _CRT_NON_CONFORMING_SWPRINTFS // really?
#else
#define L2PACKETS_LINUX
#endif

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#if defined(_WIN32) || defined(WIN32) || defined(WINVER) || defined(_WIN32_WINNT)
#define WIN32_LEAN_AND_MEAN
#include "targetver.h"
#include <winsock2.h>
#include <windows.h>
#include <tchar.h>
#else // LINUX
#include <sys/time.h>
#endif

#include <openssl/bn.h>
#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/blowfish.h>

#endif
