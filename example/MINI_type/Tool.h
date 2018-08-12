

#include<zxc_net/Logger.h>

#include <string.h>
#include <thread>
#include <regex>
#include <fstream>
using namespace std;

#include <iostream>
#include <parsing_from_weixinLittleP_data.h>
#include <mysql_communicate.h>

#ifdef _WIN32
#pragma warning(disable:4996)
#include <windows.h>
#include "mysql_communicate.h"
#pragma comment (lib,"ws2_32.lib")
#endif


bool   writerDataToFile(std::string filepath, std::string data_need_to_writted, int length);

bool   creat_html_aboutId(std::string * strJsonData, std::string id);

class mysql;

class Tool {

	public:
		Tool(): mysql_() {

			if (mysql_.IniteMysqlAndConnected())
				INFO("mysql connect success\n");
		}

		~Tool() {	   
			mysql_.closeMysqlCon();
		}

	public:
  
		void delete_finishEqual_1();

               // 下面是client的http 请求  number中的  1  2  3
		  bool client_1_handle_xhttp(const std::string& request_body, std::string*  wait_2_send_responseBody);
	

		  bool client_2_handle_xhttp(const std::string& request_body, const std::string& boundary);

					//  checking the finish status;
		  bool  client_3_handle_xhttp(const std::string& request_body, std::string*  wait_2_send_responseBody);

		 
		  bool  client_4_handle_xhttp(const std::string& request_body, std::string*  wait_2_send_responseBody);


				
	private:
		mysql   mysql_;
		string	boundary;
			  //  static const 
		const static string	picture_path_in_server_weixin; 
					
};
					

