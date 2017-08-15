
#include "parson_from_weixinLittleP_data.h"

   //  data_client:
    //driving_type=3&user_name=zxc&user_phone=17711644&
   //  user_address=shenzhen&user_company=Uct&user_zw=engineer


/************************************************************************************/


void parson_from_weixinLittle_data(std::string & input_original_data, std::string * out_string_array) {

	std::string  temp = ".+=(.+)&";
	smatch mas;
	string src = input_original_data;
	string pattern = "^" + temp + temp + temp + temp + temp + temp + ".+=(.+)$";  // standard
	printf("\npattern:%s\n", pattern.c_str());

	regex r(pattern);
	regex_search(src, mas, r);
	if (mas.size() == 0)
	{
		printf("%s failed!\n", pattern.c_str());
		//close_socket_xhttp();

		printf("\n parson_from_weixinLittle_data  is error \n");
		return;
	}
	//printf("\nmas[1]:%s-------out_string_array[i]:%s\n", mas[1], out_string_array[0].c_str());

	std::cout << mas[1] << std::endl;

	printf("\n///////////////////////////////\n");
	char szSrc[] = "赵轩超";
	char pBuf[30];
	char pBuf_2[30];

	UrlEncode(szSrc, pBuf, 30, true);


	printf("pBuf:%s---\n", pBuf);

	UrlDecode(pBuf, pBuf_2, 30);
	printf("pBuf:%s----\n", pBuf_2);

	printf("\n///////////////////////////////\n");

	for (unsigned int i = 0; i<mas.size(); i++) {

		//out_string_array[i] = mas[i + 1];
		std::string temp_string = mas[i + 1];
		char temp_array[100];
		UrlDecode(temp_string.c_str(), temp_array, 100);

		out_string_array[i] = temp_array;


		printf("\ntemp_array:%s \n", temp_array);
		std::cout << mas[i + 1] << "---------" << out_string_array[i] << std::endl;


	}

}

/*****************************************************************************************/

//////////////////////////////////////////////////////////////////////////////////////

/*

void parson_from_weixinLittle_data( std::string & input_original_data, std::string * out_string_array ) {

	std::string  temp = ".+=(.+)&";
	smatch mas;
	string src = input_original_data;
	string pattern = "^"+temp+temp+temp+temp+temp+temp+".+=(.+)$";  // standard
	printf("\npattern:%s\n",pattern.c_str());

	regex r(pattern);
	regex_search(src, mas, r);
	if (mas.size() == 0)
	{
		printf("%s failed!\n", pattern.c_str());
		//close_socket_xhttp();

		printf("\n parson_from_weixinLittle_data  is error \n");
		return;
	}
	//printf("\nmas[1]:%s-------out_string_array[i]:%s\n", mas[1], out_string_array[0].c_str());

	std::cout << mas[1] << std::endl;

					printf("\n///////////////////////////////\n");
					char szSrc[] = "赵轩超";
					char pBuf[30];
					char pBuf_2[30];

					UrlEncode(szSrc, pBuf, 30, true);

	
					printf("pBuf:%s---\n",pBuf);

					UrlDecode( pBuf, pBuf_2, 30);
					printf("pBuf:%s----\n", pBuf_2);

					printf("\n///////////////////////////////\n");

	for ( unsigned int i = 0; i<mas.size(); i++) {

		   //out_string_array[i] = mas[i + 1];
		std::string temp_string = mas[i + 1];
		char temp_array[100];
		UrlDecode(temp_string.c_str(), temp_array,100);

		out_string_array[i] = temp_array;


		printf("\ntemp_array:%s \n", temp_array);
		std::cout << mas[i + 1] <<"---------" << out_string_array[i] << std::endl;


	} 

}


*/








/////////////////////////////////////////
//解码后是utf-8编码
BOOL UrlDecode(const char* szSrc, char* pBuf, int cbBufLen)
{
	if (szSrc == NULL || pBuf == NULL || cbBufLen <= 0)
		return FALSE;

	size_t len_ascii = strlen(szSrc);
	if (len_ascii == 0)
	{
		pBuf[0] = 0;
		return TRUE;
	}

	char *pUTF8 = (char*)malloc(len_ascii + 1);
	if (pUTF8 == NULL)
		return FALSE;

	int cbDest = 0; //累加
	unsigned char *pSrc = (unsigned char*)szSrc;
	unsigned char *pDest = (unsigned char*)pUTF8;
	while (*pSrc)
	{
		if (*pSrc == '%')
		{
			*pDest = 0;
			//高位
			if (pSrc[1] >= 'A' && pSrc[1] <= 'F')
				*pDest += (pSrc[1] - 'A' + 10) * 0x10;
			else if (pSrc[1] >= 'a' && pSrc[1] <= 'f')
				*pDest += (pSrc[1] - 'a' + 10) * 0x10;
			else
				*pDest += (pSrc[1] - '0') * 0x10;

			//低位
			if (pSrc[2] >= 'A' && pSrc[2] <= 'F')
				*pDest += (pSrc[2] - 'A' + 10);
			else if (pSrc[2] >= 'a' && pSrc[2] <= 'f')
				*pDest += (pSrc[2] - 'a' + 10);
			else
				*pDest += (pSrc[2] - '0');

			pSrc += 3;
		}
		else if (*pSrc == '+')
		{
			*pDest = ' ';
			++pSrc;
		}
		else
		{
			*pDest = *pSrc;
			++pSrc;
		}
		++pDest;
		++cbDest;
	}
	//null-terminator
	*pDest = '\0';
	++cbDest;

	int cchWideChar = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)pUTF8, cbDest, NULL, 0);
	LPWSTR pUnicode = (LPWSTR)malloc(cchWideChar * sizeof(WCHAR));
	if (pUnicode == NULL)
	{
		free(pUTF8);
		return FALSE;
	}
	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)pUTF8, cbDest, pUnicode, cchWideChar);
	WideCharToMultiByte(CP_ACP, 0, pUnicode, cchWideChar, pBuf, cbBufLen, NULL, NULL);
	free(pUTF8);
	free(pUnicode);
	return TRUE;
}

//////////////////////////////////
BOOL UrlEncode(const char* szSrc, char* pBuf, int cbBufLen, BOOL bUpperCase)
{
	if (szSrc == NULL || pBuf == NULL || cbBufLen <= 0)
		return FALSE;

	size_t len_ascii = strlen(szSrc);
	if (len_ascii == 0)
	{
		pBuf[0] = 0;
		return TRUE;
	}

	//先转换到UTF-8
	char baseChar = bUpperCase ? 'A' : 'a';
	int cchWideChar = MultiByteToWideChar(CP_ACP, 0, szSrc, len_ascii, NULL, 0);
	LPWSTR pUnicode = (LPWSTR)malloc((cchWideChar + 1) * sizeof(WCHAR));
	if (pUnicode == NULL)
		return FALSE;
	MultiByteToWideChar(CP_ACP, 0, szSrc, len_ascii, pUnicode, cchWideChar + 1);

	int cbUTF8 = WideCharToMultiByte(CP_UTF8, 0, pUnicode, cchWideChar, NULL, 0, NULL, NULL);
	LPSTR pUTF8 = (LPSTR)malloc((cbUTF8 + 1) * sizeof(CHAR));
	if (pUTF8 == NULL)
	{
		free(pUnicode);
		return FALSE;
	}
	WideCharToMultiByte(CP_UTF8, 0, pUnicode, cchWideChar, pUTF8, cbUTF8 + 1, NULL, NULL);
	pUTF8[cbUTF8] = '\0';

	unsigned char c;
	int cbDest = 0; //累加
	unsigned char *pSrc = (unsigned char*)pUTF8;
	unsigned char *pDest = (unsigned char*)pBuf;
	while (*pSrc && cbDest < cbBufLen - 1)
	{
		c = *pSrc;
		if (isalpha(c) || isdigit(c) || c == '-' || c == '.' || c == '~')
		{
			*pDest = c;
			++pDest;
			++cbDest;
		}
		else if (c == ' ')
		{
			*pDest = '+';
			++pDest;
			++cbDest;
		}
		else
		{
			//检查缓冲区大小是否够用？
			if (cbDest + 3 > cbBufLen - 1)
				break;
			pDest[0] = '%';
			pDest[1] = (c >= 0xA0) ? ((c >> 4) - 10 + baseChar) : ((c >> 4) + '0');
			pDest[2] = ((c & 0xF) >= 0xA) ? ((c & 0xF) - 10 + baseChar) : ((c & 0xF) + '0');
			pDest += 3;
			cbDest += 3;
		}
		++pSrc;
	}
	//null-terminator
	*pDest = '\0';
	free(pUnicode);
	free(pUTF8);
	return TRUE;
}





















/*




//	printf("\nmas[i+1]:%s-------out_string_array[i]:%s\n", mas[i + 1], out_string_array[i].c_str());
//decodeUrl(mas[i + 1], out_string_array[i]);

std::string temp_string = mas[i + 1];
CString temp= UrlDecode(temp_string.c_str());
temp_string = temp.GetBuffer(0);
//out_string_array[i]




*/


//
//
//unsigned char FromHex(unsigned char x)
//{
//	unsigned char y;
//	if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
//	else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
//	else if (x >= '0' && x <= '9') y = x - '0';
//	else assert(0);
//	return y;
//}
//
//
//
//std::string UrlDecode(const std::string& str)
//{
//	std::string strTemp = "";
//	size_t length = str.length();
//	for (size_t i = 0; i < length; i++)
//	{
//		if (str[i] == '+') strTemp += ' ';
//		else if (str[i] == '%')
//		{
//			assert(i + 2 < length);
//			unsigned char high = FromHex((unsigned char)str[++i]);
//			unsigned char low = FromHex((unsigned char)str[++i]);
//			strTemp += high * 16 + low;
//		}
//		else strTemp += str[i];
//	}
//	return strTemp;
//}
//
//
///*
//
//unsigned char ToHex(unsigned char x)
//{
//	return  x > 9 ? x + 55 : x + 48;
//}
//
//std::string UrlEncode(const std::string& str)
//{
//	std::string strTemp = "";
//	size_t length = str.length();
//	for (size_t i = 0; i < length; i++)
//	{
//		if (isalnum((unsigned char)str[i]) ||
//			(str[i] == '-') ||
//			(str[i] == '_') ||
//			(str[i] == '.') ||
//			(str[i] == '~'))
//			strTemp += str[i];
//		else if (str[i] == ' ')
//			strTemp += "+";
//		else
//		{
//			strTemp += '%';
//			strTemp += ToHex((unsigned char)str[i] >> 4);
//			strTemp += ToHex((unsigned char)str[i] % 16);
//		}
//	}
//	return strTemp;
//}
//
//
//*/
//
//
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
///*
//                //1、urlencode.h
//
//
//                       //2、urlencode.cpp
//
//#include "urlencode.h"
//
//*/
//
//
//
//unsigned char toHex(unsigned char c) {
//	return c > 9 ? 'A' - 10 + c : '0' + c;
//}
//unsigned char fromHex(unsigned char h) {
//	unsigned char c = 0;
//	if (h >= 'A' && h <= 'Z') {
//		c = h - 'A' + 10;
//	}
//	else if (h >= 'a' && h <= 'z') {
//		c = h - 'a' + 10;
//	}
//	else if (h >= '0' && h <= '9') {
//		c = h - '0';
//	}
//	else {
//	}
//	return c;
//}
//void encodeUrl(const string& str, string& result) {
//	int len = str.length();
//	for (int i = 0; i<len; i++) {
//		if (isalnum((unsigned char)str[i]) ||
//			(str[i] == '.') || (str[i] == '-') || (str[i] == '*') || (str[i] == '_')) {
//			result += str[i];
//		}
//		else if (str[i] == ' ') {
//			result += '+';
//		}
//		else {
//			result += '%';
//			result += toHex((unsigned char)str[i] >> 4);
//			result += toHex((unsigned char)str[i] & 0xF);
//		}
//	}
//}
//void encodeUrl(const char* str, string &result) {
//	string tmp = str;
//	encodeUrl(tmp, result);
//}
//void decodeUrl(const string& str, string &result) {
//	result = "";
//	int len = str.length();
//	for (int i = 0; i<len; i++) {
//		if ((str[i] == '.') || (str[i] == '-') || (str[i] == '*') || (str[i] == '_')) {
//			result += str[i];
//		}
//		else if (str[i] == '+') {
//			result += ' ';
//		}
//		else if (str[i] == '%') {
//			assert(i + 2 < len);
//			unsigned char high = fromHex((unsigned char)str[++i]);
//			unsigned char low = fromHex((unsigned char)str[++i]);
//			result += ((high << 4) | low);
//		}
//		else if (isalnum((unsigned char)str[i])) {
//			result += str[i];
//		}
//		else {
//		}
//	}
//}
//
//
//
//void decodeUrl(const char* str, string &result) {
//	string tmp = str;
//	decodeUrl(tmp, result);
//}
//
//
//
/////////////////////////////////////////////////////////////////////////////////
//
//
//CString URLEncode(CString url)
//{
//	std::wstring text = url;
//
//	size_t len = text.length();
//	std::wstring encoded = L"";
//	for (size_t i = 0; i < len; i++)
//	{
//		wchar_t wch = text.at(i);
//		if ('A' <= wch && wch <= 'Z') {
//			encoded += wch;
//		}
//		else if ('a' <= wch && wch <= 'z') {
//			encoded += wch;
//		}
//		else if ('0' <= wch && wch <= '9') {
//			encoded += wch;
//		}
//		else if (wch == ' ') {
//			encoded += hexenc[wch];
//		}
//		else if (wch == '-' || wch == '_'
//			|| wch == '.' || wch == '!'
//			|| wch == '~' || wch == '*'
//			|| wch == '\'' || wch == '('
//			|| wch == ')') {
//			encoded += hexenc[wch];
//		}
//		else if (wch <= 0x007f) {        // other ASCII
//			encoded += hexenc[wch];
//		}
//		else if (wch <= 0x07FF) {        // non-ASCII <= 0x7FF
//			encoded += hexenc[0xc0 | (wch >> 6)];
//			encoded += hexenc[0x80 | (wch & 0x3F)];
//		}
//		else {                    // 0x7FF < ch <= 0xFFFF
//			encoded += hexenc[0xe0 | (wch >> 12)];
//			encoded += hexenc[0x80 | ((wch >> 6) & 0x3F)];
//			encoded += hexenc[0x80 | (wch & 0x3F)];
//		}
//	}
//	return encoded.c_str();
//}

/////////////////////////////////////////////////


/*

CString UrlDecode(CString encodeUrl)
        {
            std::wstring text = encodeUrl;
            std::wstring decoded = L"";
            wchar_t temp[] = L"0x00";
            size_t len = text.length();
            int sequence = 0;
            wchar_t conwch = 0;
            for(size_t i = 0; i < len; i++)
            {    
                wchar_t wch = text.at(i++);
                if((wch == '%') && (i+1 < len))
                {            
                    temp[2] = text.at(i++);
                    temp[3] = text.at(i);
                    long tconwch = wcstol(temp, NULL, 16);
                    if(tconwch <= 0x7F) {
                        decoded += tconwch; // normal ascii char
                    } else if(tconwch >= 0x80 && tconwch <= 0xBF) { // partial byte
                        tconwch = tconwch & 0x3F;
                        if(sequence-- == 2)
                            tconwch = tconwch << 6;
                        conwch |= tconwch;
                        if(sequence == 0)
                            decoded += conwch;
                    } else if(tconwch >= 0xC0 && tconwch <= 0xDF) {
                        conwch = (tconwch & 0x1F) << 6; // make space for partial bytes
                        sequence = 1; // 1 more partial bytes follow
                    } else if(tconwch >= 0xE0 && tconwch <= 0xEF) {
                        conwch = (tconwch & 0xF) << 12; // make space for partial bytes
                        sequence = 2; // 2 more partial bytes follow
                    } // TODO add case fore 3 partial bytes ... very rare
                } else {
                    decoded += text.at(--i);
                }
            }
            return decoded.c_str();
        }

*/