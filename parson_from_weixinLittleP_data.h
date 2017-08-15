#pragma once
#include <string.h>
#include <regex>
#include <iostream>
#include<windows.h>

using namespace std;

///////////////////////////////////////
/*
#include <assert.h>
#include<AFX.h>
#include <string>
#include <ctype.h>

//#define ASC2_0 48
//#define ASC2_A 65
//#define ASC2_Z 90
//#define ASC2_a 97
//#define ASC2_z 122

using namespace std;
unsigned char toHex(unsigned char c);
unsigned char fromHex(unsigned char h);
void encodeUrl(const string& str, string& result);
void encodeUrl(const char* str, string& result);
void decodeUrl(const string& str, string& result);
void decodeUrl(const char* str, string& result);
///////////////////////////////////////////////////////////





using namespace std;
unsigned char FromHex(unsigned char x);
std::string UrlDecode(const std::string& str);
*/

//CString UrlDecode(CString encodeUrl);
BOOL UrlEncode(const char* szSrc, char* pBuf, int cbBufLen, BOOL bUpperCase);
BOOL UrlDecode(const char* szSrc, char* pBuf, int cbBufLen);
void parson_from_weixinLittle_data(std::string & input_original_data, std::string * out_string_array);
