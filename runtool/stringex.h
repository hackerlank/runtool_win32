#pragma once

#include <windows.h>
#include <string>
#include <string.h>

//1.  ANSI to Unicode
std::wstring ANSIToUnicode(const std::string& str);

//2.  Unicode to ANSI
std::string UnicodeToANSI(const std::wstring& str);

//3.  UTF - 8 to Unicode
std::wstring UTF8ToUnicode(const std::string& str);

//4.  Unicode to UTF - 8
std::string UnicodeToUTF8(const std::wstring& str);
