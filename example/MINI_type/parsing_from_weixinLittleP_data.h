
#pragma once
#include <string.h>
#include <regex>
#include <iostream>

#ifdef _WIN32
#include<windows.h>
#else 
#include <stdlib.h>
#endif



using namespace std;


//bool	UrlEncode(const char* szSrc, char* pBuf, int cbBufLen, bool bUpperCase);
//bool	UrlDecode(const char* szSrc, char* pBuf, int cbBufLen);

void	parson_from_weixinLittle_data(const std::string & input_original_data, std::string * out_string_array);
