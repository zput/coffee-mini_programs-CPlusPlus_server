#pragma once

#include "XTcp.h"
#include <string.h>
#include <thread>
#include <regex>
#include <fstream>
using namespace std;

#include <iostream>
#include "parson_from_weixinLittleP_data.h"
#ifdef _WIN32
#pragma warning(disable:4996)
#include <windows.h>
#include "mysql_communicate.h"
#pragma comment (lib,"ws2_32.lib")
#endif


bool	writerDataToFile(std::string filepath, std::string data_need_to_writted, int length);

bool creat_html_aboutId(std::string * strJsonData, std::string id);

string GBKToUTF8(const std::string& strGBK);


class XHTTP {
public:
	// 主函数的功能：1.parser the request data, which is client's requestment or the collect's requestment
   //            主要是解析http://wkzxc.imwork.net/XXXX/number/ 中的XXXX是client or collect   and the number
  //             2. send the return value of submain function 
 //   
	      void main_xhttp();        // 接收和发送数据，但 recv_data 解析后，调用子函数进行处理，对于子函数的返回值进行发送。


		  //////////////////////////////////////////////////////
		  void delete_finishEqual_1();


		  ////////////////////////////////////////////////////


		//  void client_0_handle_xhttp(char * recvBuf);



		  // the above is the request of backup
		  void XHTTP::backup_1_handle_xhttp(char * recvBuf);     //　　　询问　id 到哪了。
		  void XHTTP::backup_2_handle_xhttp(char * recvBuf);     //      传送指定id段到backup
		  void XHTTP::backup_3_handle_xhttp(char * recvBuf);     //      传送指定id段picture 到backup

		  void XHTTP::backup_4_handle_xhttp(char * recvBuf);
		  void XHTTP::backup_5_handle_xhttp(char * recvBuf);







  // 下面是client的http 请求  number中的  1  2  3

		  void client_1_handle_xhttp(char * recvBuf);
		  bool XHTTP::insert_1_function(char * recvBuf, int * length_recv); //--------repeat------------

		  void client_2_handle_xhttp(char * recvBuf,int length_recv);
		  bool XHTTP::insert_function(char * recvBuf, int * length_recv);



		  void client_3_handle_xhttp(char * recvBuf);
		  //void client_3_handle_xhttp(char * recvBuf);

		  void  XHTTP::client_4_handle_xhttp(char * recvBuf);//  checking the finish status;


		  void XHTTP::http_send_function(std::string data_need_to_send);

  // 下面是collect的http请求  number中的  1  2  3  4

		//std::string collect_1_handle();
		//std::string collect_2_handle();
		//std::string collect_3_handle();
		//std::string collect_4_handle();
				
//private:

	void close_socket_xhttp();
		                                    //unsigned int sock_connect;
    XTcp socketConnect_1;
	string boundary;

};




























