
#include "XHTTP.h"

	void XHTTP::close_socket_xhttp() {

		socketConnect_1.socketClose();
		delete this;
	}

//	/************ get the openid ********************/
//	void XHTTP::client_0_handle_xhttp(char * recvBuf)
//	{
//		smatch mas;
//		string src = recvBuf;                   //  [\s\S]*   .*$
//		string pattern = "\r\n\r\nopenid=(.*$)";  // standard
//		regex r(pattern);
//		regex_search(src, mas, r);
//		if (mas.size() == 0)
//		{
//			printf("%s failed!\n", pattern.c_str());
//
//			http_send_function("0");
//			return;
//		}
//		string filepage_end = mas[1];
//		// 得到这个客户data.
//		printf("\n\ndata_client:%s\n", filepage_end.c_str());
//
//
//		///////////http get request////////////////
//
//		struct hostent *host = gethostbyname("api.weixin.qq.com");
//		if (!host) {
//			puts("Get IP address error!");
//			system("pause");
//			exit(0);
//		}
//		//别名
//		//for (int i = 0; host->h_aliases[i]; i++) {
//		//	printf("Aliases %d: %s\n", i + 1, host->h_aliases[i]);
//		//}
//		////地址类型
//		//printf("Address type: %s\n", (host->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6");
//		//IP地址
//		std::string ip_address_getOpenid;
//		for (int i = 0; host->h_addr_list[i]; i++) {
//			printf("IP addr %d: %s\n", i + 1, inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));
//			ip_address_getOpenid = inet_ntoa(*(struct in_addr*)host->h_addr_list[0]);
//
//		}
//		/////////////////////
//		XTcp request_;
//
//		request_.Connect(ip_address_getOpenid.c_str(),443,1000);
///////////////////////////////////////////////////////////////////////////////////////////
//		std::string msg = "";
//		//1> 
//		msg += "HTTP/1.1 200 ok ";
//		//2> name +':' +spaceblock +value 
//		msg += "service: XHttp\r\n";
//		msg += "Content-Type: text/html\r\n";
//		/*	msg += "Content-Length: ";// the 2> is end(double \r\n)
//
//		char bsize[128] = { 0 };
//		sprintf(bsize, "%d", filesize);
//		msg += bsize;
//		//rmsg +=
//		//rmsg += "10\r\n";
//		*/
//		msg += "\r\n\r\n";
//
//		//3>
//		//msg +="1234567890";
//
//		////////filepage_end==0,is not finish/////////////////
//		msg += data_need_to_send; //　server has  received the custom's data, the client should goto the other page.
//
//		int sendSize = socketConnect_1.socketSend(msg.c_str(), msg.size());
//		printf("sendsize = %d\n", sendSize);
//		printf("=======send=========\n%s\n=============\n", msg.c_str());
//////////////////////////////////////////////////////////////////////////////////////////////////
//		
//	
//	}
		
	void XHTTP::delete_finishEqual_1()
	{
		mysql postMysql2;
		if (postMysql2.IniteMysqlAndConnected())
			printf("mysql connect success\n");

		std::string inputString = "select id,finish from test;";
		std::string  the_id_deleted[30];
		//bool  mysql::deleteFinishEqual1DataFromMysql(std::string inputString, std::string * theRowHadRead)
		if (postMysql2.deleteFinishEqual1DataFromMysql(inputString, the_id_deleted) )
			printf("Get the id data. success\n");

		for (int i = 0; the_id_deleted[i] != "\0"; i++ ) {
			std::string temp_mysql_order = "DELETE FROM test WHERE id =" + the_id_deleted[i] + " ;";
		
			postMysql2.commonOrderMysql(temp_mysql_order);
		}
		//mysql_close(postMysql2.con);
		postMysql2.closeMysqlCon();


	}


	string GBKToUTF8(const std::string& strGBK)
	{
		string strOutUTF8 = "";
		WCHAR * str1;
		int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
		str1 = new WCHAR[n];
		MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
		n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
		char * str2 = new char[n];
		WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
		strOutUTF8 = str2;
		delete[]str1;
		str1 = NULL;
		delete[]str2;
		str2 = NULL;
		return strOutUTF8;
	}




	bool creat_html_aboutId(std::string * strJsonData, std::string id)
	{
		char * html_code = new char[2000]();
		

		       //char buf_temp[51200 * 2] = "\0";
				//for (int i = 0; i <= end_begin_value; i++) {
				//printf("msg:%s", msg.c_str());
				//socketConnect_1.socketSend(msg.c_str(), msg.length());
		std::string filepath ="C:/WEIXIN/WEIXIN/nginx-1.13.1/html/237/template.html"; // nginx 的页面路径！！！
				//filepath1 + to_string(begin_number_int + i) + ".jpg";
	//    printf("\nfilepath:%s\n", filepath.c_str());

		       //buf_temp[picture_size[i] + 1] = '\0';
	    ifstream fin(filepath, ios::in | ios::binary | ios::ate);
			   //size = data_need_to_writted.length();
			   //////in.seekg(0, ios::beg);
			   //buffer = new char[size];
			   ///in.read(buffer, size);
		fin.seekg(0, ios::beg);                        ///////////////////
		fin.read(html_code, 1700);
		fin.close();
	          //printf("\n%s\n", html_code);
   /////////////////read  data over///////////////////////////////////	        

   /////////////////modify the data Notice//////////////////////
		//openid, driving_type, user_name, user_phone, user_address, user_company, user_zw

		const int byte_number[7] = {427,545,668,830,967,1236,1503};

		sprintf(html_code+ byte_number[0], "%s",id.c_str());

		for (int i = 1; i < 7; i++) {
		/*
			sprintf(save_mysql_order, "insert into %s(id,openid, driving_type, user_name, user_phone, user_address, user_company, user_zw) values(%s,'%s','%s','%s','%s','%s','%s','%s');\r\n", tablename, id.c_str(),
				strJsonData[0].c_str(), strJsonData[1].c_str(), strJsonData[2].c_str(),
				strJsonData[3].c_str(), strJsonData[4].c_str(), strJsonData[5].c_str(), strJsonData[6].c_str());
	    */	
			if(i==1) {
				if (strJsonData[1] == "1") { sprintf(html_code + byte_number[1],"%s", "橙汁" ); }
				else if (strJsonData[1] == "2") { sprintf(html_code + byte_number[1], "%s", "咖啡"); }
				else if (strJsonData[1] == "3") { sprintf(html_code + byte_number[1], "%s", "奶茶"); }
				
				}
			
			else sprintf(html_code + byte_number[i], "%s",strJsonData[i].c_str());
		}
	

   ///////////////// write to a new html file////////////////////////////////////////
		                //long size;
		filepath = "C:/WEIXIN/WEIXIN/nginx-1.13.1/html/237/"+id+".html";
		ofstream out(filepath, ios::out | ios::binary | ios::ate);
						//size = data_need_to_writted.length();
						//////in.seekg(0, ios::beg);
						//buffer = new char[size];
						///in.read(buffer, size);
		out.write(html_code, 1700);
		out.close();
	     
		
  ///////////////////////////////////////////////////////////


		delete[] html_code;
		return 0;
	}





  void  XHTTP::client_1_handle_xhttp(char * recvBuf )
	{
		smatch mas;
		string src = recvBuf;                   //  [\s\S]*   .*$
		string pattern = "\r\n\r\n(.*$)";  // standard
		regex r(pattern);
		regex_search(src, mas, r);
		if (mas.size() == 0)
		{
			printf("%s failed!\n", pattern.c_str());
			http_send_function("0");
			return;
		}
		string data_client = mas[1];
		// 得到这个客户data.
		printf("\n\ndata_client:%s\n",data_client.c_str());
		printf("data_client length:%d",data_client.length());
		
		/*******************parson the weixin little program ***********************************/

		std::string string_array[8] = {""};
		parson_from_weixinLittle_data(data_client,string_array);
		                           //printf("the address:%x", &string_array[2]);
		/************************save the data to mysql(save_little_program  test )***********************************************/

		std::string  id;
		// save to mysql;
		mysql postMysql;
		if (postMysql.IniteMysqlAndConnected())
			printf("mysql connect success\n");
		if (postMysql.GetIdFromMysql( &id,false)) {
			//char * temp_id=NULL;
			//int temp_temp_id = atoi(id.c_str());
			//itoa(++temp_temp_id, temp_id, 10);
			//id = *temp_id;

			printf("get the id=%s success\n",id.c_str());
			int temp_length_id = id.length();
			int temp_sum_id = 0;
			for (int i = 0; i < temp_length_id; i++) {
				temp_sum_id *= 10;
				temp_sum_id += id[i] - 48;
				
			}
			++temp_sum_id;
			temp_length_id = 0;
			int temp_zxc_i = temp_sum_id;
			while (temp_zxc_i) {
				temp_zxc_i /= 10;
				temp_length_id++;
			}
			for (int i = 0; i < temp_length_id; i++) {
			    id[temp_length_id-i-1]= temp_sum_id%10+48;
				temp_sum_id /= 10;
			}
			printf("get the id=%s success\n", id.c_str());

		}

		if (postMysql.SaveJsonData2Mysql(string_array,id ))
			printf("Json data was transmitted. success\n");


	/*******************************respond the client******************************************************/
		http_send_function(id);
	   

	//_____________________create a  html page in order to two_bar_code______________________________//
		creat_html_aboutId(string_array, id);



	}




	void XHTTP::main_xhttp() {

		printf("\nI am in main_xhttp\n");

		/*********************************recv the http client message ************************************************/
		char recvBuf[51200*2] = { '\0' };
		//std::string recvBuf = "";
		//the recv()function is block function ; so ,
		char * recvBuf_temper = recvBuf;
		printf("\nI am safe in first\n");
		int recvLen = socketConnect_1.socketRecv(recvBuf_temper, 256);
		printf("\nI am safe in second\n");

		int count = 0;
		while (recvLen == 256) {
			recvBuf_temper += 256;
			recvLen = socketConnect_1.socketRecv(recvBuf_temper, 256);
			count++;
			if (256*(count+1)>69013) {
				string filepath = "C:/WEIXIN/error_data.txt";
				writerDataToFile(filepath, recvBuf, 69013);

			}
			if (count%24==0) {
				printf("\nI am safe in -%d-\n", count);
			}
		}
		if (recvLen<0) {
			printf("the data is error form the http client");

			//socketConnect_1.socketClose();
			close_socket_xhttp();
			//delete this;  //delete the function ?
			return;
		}
		printf("\n---the recvLen is:%d\n-------the count is :%d\n-------recvLen's length:%d", recvLen, count, strlen(recvBuf));
		int length_recv = recvLen + 256 * count;
		recvBuf[length_recv] = '\0';

		printf("\n\n==========the data from the receive====================\n%s\n=================================\n", recvBuf);

		//std::cout << "\n" << recvBuf << std::endl;

		/*****************************  respond the http client , just the GET message*******************************************************/







		/*********************************recv the http client message ************************************************/
		/*
		char recvBuf[10240] = { '\0' };
		//std::string recvBuf = "";
		//the recv()function is block function ; so ,
		char * recvBuf_temper = recvBuf;
		int recvLen = socketConnect_1.socketRecv(recvBuf_temper, sizeof(recvBuf) - 1);
		int count = 0;
		while (recvLen == 1024) {
			recvBuf_temper += 1024;
			recvLen = socketConnect_1.socketRecv(recvBuf_temper, sizeof(recvBuf) - 1);
			count++;

		}
		if (recvLen<0) {
			printf("the data is error form the http client");

			//socketConnect_1.socketClose();
			close_socket_xhttp();
			//delete this;  //delete the function ?
			return;
		}
		printf("\n---the recvLen is:%d\n-------the count is :%d\n-------recvLen's length:%d", recvLen, count, strlen(recvBuf));
		int length_recv = recvLen + 1024 * count;
		recvBuf[length_recv] = '\0';

		printf("\n\n==========the data from the receive====================\n%s\n=================================\n", recvBuf);

		//std::cout << "\n" << recvBuf << std::endl;
		*/
		/*****************************  respond the http client , just the GET message*******************************************************/
	

		//页面
		//GET /index.html HTTP/1.1
		//Host: 192.168.3.69
		//User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64; rv:51.0) Gecko/20100101 Fi
		//Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
		//Accept-Language: zh-CN,zh;q=0.8,en-US;q=0.5,en;q=0.3
		//Accept-Encoding: gzip, deflate
		//DNT: 1
		//Connection: keep-alive
		//Upgrade-Insecure-Requests: 1

		string src ="";
		for (int i = 0; i < length_recv ; i++) {
			src += recvBuf[i];
		}
		smatch mas;

		string pattern = "^([A-Z]+) /(.+)/(\\d).* HTTP/1";  // standard
		regex r(pattern);
		regex_search(src, mas, r);
		if (mas.size() == 0)
		{
			printf("%s failed!\n", pattern.c_str());
			close_socket_xhttp();
			return;
		}
		string type = mas[1];
		string client_or_collect = mas[2];
		string number =mas[3];

		std::cout << type <<"\n"<< client_or_collect <<'\n'<< number<<std::endl;


		if (type!="POST" && type != "GET" )
		{
			close_socket_xhttp();
			return;
		}

		if (client_or_collect == "client") {
			switch (stoi(number)) {
			case 1:  if (insert_1_function(recvBuf, &length_recv)) { http_send_function("0"); break; } delete_finishEqual_1(); client_1_handle_xhttp(recvBuf); break;
			case 2: { if (insert_function(recvBuf, &length_recv)) { http_send_function("0"); break ; } client_2_handle_xhttp(recvBuf, length_recv); break; }
			case 3:  if (insert_1_function(recvBuf, &length_recv)) { http_send_function("0"); break; } client_3_handle_xhttp(recvBuf); break;
			case 4: if (insert_1_function(recvBuf, &length_recv)) { http_send_function("0"); break; } client_4_handle_xhttp(recvBuf); break;
			default: {  
				     close_socket_xhttp();
				     return;       }
			}
		
		
		}

		else if(client_or_collect == "backup") {
			switch (stoi(number)) {
			case 1:   if (insert_1_function(recvBuf, &length_recv)) { http_send_function("0"); break; } backup_1_handle_xhttp(recvBuf); break;
			case 2:   if (insert_1_function(recvBuf, &length_recv)) { http_send_function("0"); break; } backup_2_handle_xhttp(recvBuf); break;
			case 3:   if (insert_1_function(recvBuf, &length_recv)) { http_send_function("0"); break; } backup_3_handle_xhttp(recvBuf); break;
			case 4:   if (insert_1_function(recvBuf, &length_recv)) { http_send_function("0"); break; } backup_4_handle_xhttp(recvBuf); break;
			case 5:   if (insert_1_function(recvBuf, &length_recv)) { http_send_function("0"); break; } backup_5_handle_xhttp(recvBuf); break;
			default: {
				close_socket_xhttp();
				return;       }
			}


		}

		else {
			close_socket_xhttp();
			return;
		
		}
		
		close_socket_xhttp();
		printf("\n----------------test_http_reback-----------\n");
		return;

				
	}
		///////////////////////////////////////////////////////////////////////
		///
		///          client_2_handle_xhttp(recvBuf)   
		///
	   ///
	   ///              //  [\s\S]*   .*$      content-length: 9047
		//////////////////////////////////////////////////////////////////////

		void XHTTP::client_2_handle_xhttp(char * recvBuf,int length_recv)
		{
			smatch mas;
			string src ="";//  [\s\S]*   .*$

			
			for (int i = 0; i < length_recv; i++) {
				src += recvBuf[i];
			}



			printf("\nsrc is length:%d", src.length());



			
			//string pattern = "image/jpeg\\r\\n\\r\\n([\\s\\S]*)\\r\\n----------";  // standard

			string pattern = "(^[\\s\\S]*[cC]ontent-[dD]isposition: form-data; name=\"openid\"\r\n\r\n(.+)\r\n--.+\r\n[\\s\\S]*[cC]ontent-[tT]ype: image/[a-zA-Z]+\r\n\r\n)";  //([\\s\\S]*)\r\n--" + boundary + "--\r\n$";  // standard

			printf("\npattern:%s\n",pattern.c_str());
			//string pattern = "^[\\s\\S]*name=\"openid\"\r\n\r\n(.+)\r\n--"+boundary+"\r\n[\\s\\S]*image/jp[a-zA-Z]+\r\n\r\n([\\s\\S]*)\r\n--"+boundary+"--\r\n$";  // standard
		//	string pattern = "(^[\\s\\S]*[cC]ontent-[dD]isposition: form-data; name=\"openid\")" ;   //\r\n\r\n(.+)\r\n--" + boundary + ")";//+ "\r\n[\\s\\S]*image/jp[a-zA-Z]*\r\n\r\n)";  
			//   ([\\s\\S]*)\r\n--" + boundary + "--\r\n$";  // standard
		//	pattern = "(" + boundary + ")";
			regex r(pattern);
			regex_search(src, mas, r);
			if (mas.size() == 0)
			{
				printf("%s failed!\n", pattern.c_str());
				http_send_function("0");
				return;
			}
			string filepage_end = mas[2];
			string data_client = mas[1];

			printf("\nfilepage_end:%s\n",filepage_end.c_str());
			// 得到这个客户data.

			int length_temp=data_client.length();
			data_client = "\0";
			for (int i =length_temp ; i < (length_recv-(int)boundary.length()-8); i++) {
				data_client += recvBuf[i];
			}
			printf("\n\n data_client:%s\n+++++++++++the data_client length is :%d++++++\n", data_client.c_str(),data_client.length());

		                   //	int zxc0000 = data_client.length() - 5;
		//	std::string temp_data_client=mas[2];
				std::cout<< "\ndata_client end data is :----------" << boundary <<"-------------"<<std::endl;

		//	printf("\ndata_client end data is :-----%s-----\n", temp_data_client.c_str() );

  ///////////////////////////read the id related the openid ///////////////////////////////////////////////          
		       // get data from  mysql;
				std::string column_id = "id";
				mysql postMysql2;
				if (postMysql2.IniteMysqlAndConnected())
		     		printf("mysql connect success\n");
				if( postMysql2.GetIdOrDataFromMysql(column_id, &filepage_end) )
					printf("Get the id data. success\n");

///////////////////////////////////////////////////////////////////////////////////////////




			string filepath = "C:/WEIXIN/picture/"+filepage_end+".jpg";

			writerDataToFile(filepath,data_client, data_client.length());
		 // filepath = "S:/WEIXIN/picture/test2.jpg";
		//	writerDataToFile(filepath, boundary, boundary.length());
		//	string filepath2 = "S:/WEIXIN/picture/test2.jpg";
		//	string data_client_2 = mas[2];
		//	writerDataToFile(filepath2, data_client_2);




/*******************************respond the client******************************************************/
			http_send_function("1");
		
		}

		                      //	filepath += filename;

			/*
			FILE *fp = fopen(filepath.c_str(), "wb");

			if (fp == NULL)
			{
				printf("file can not open!\n");
				return;
			}
							//	for (int i = 0; i<SIZE; i++)
							//	{
				if (fwrite(&data_client, data_client.length(), 1, fp) != 1)
				{
					printf("file write error!\n");
				}

									

			fclose(fp);


			*/




	bool	writerDataToFile(std::string filepath, std::string data_need_to_writted , int length)
	{
		
			// reading binary file  
			//const char * filename = "test.txt";
		   //write(char * buffer, streamsize size);
		   //read(char * buffer, streamsize size);
					  //这里 buffer 是一块内存的地址，用来存储或读出数据。
					  //参数size 是一个整数值，表示要从缓存（buffer）中读出或写入的字符数。

		                        //	char * buffer;
			long size;
			ofstream out (filepath, ios::out | ios::binary | ios::ate);
			size = data_need_to_writted.length();
			          //////in.seekg(0, ios::beg);
			              //buffer = new char[size];
			                   ///in.read(buffer, size);
			out.write(data_need_to_writted.c_str(), size);
			out.close();

															//	cout << "the complete file is in a buffer";

															//	delete[] buffer;
			return 0;

}












/*

		string filename = path;
		if (path == "/")
		{
			filename = "/index.html";
		}

		string filepath = "www";
		filepath += filename;
		FILE *fp = fopen(filepath.c_str(), "rb");
		//	printf("HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHh"); 
		if (fp == NULL)
		{
			close_socket_xhttp();
			return;
		}

		//鑾峰彇鏂囦欢澶у皬
		fseek(fp, 0, SEEK_END);
		int filesize = ftell(fp);  //the size of  responed data;
		fseek(fp, 0, 0);
		printf("file size is %d\n", filesize);

*/


      //close_socket_xhttp();

	

	/****************************class funcion Main end *****************************************************/





//		
//		//the response message is the : 1>state line  2>message head   3> message text;
//		
//		std::string msg="";
//		//1> 
//		msg +="HTTP/1.1 200 ok ";   
//		//2> [ name +':' +spaceblock +value ]
//		msg +="service: XHttp\r\n" ;
//		msg +="Tontent-Type: text/html\r\n";
//		msg +="Content-Length: 6\r\n\r\n";// the 2> is end(double \r\n) 
//		//3>
//		msg +="1234567890";


//	int sendLen=socketConnect_1.socketSend(msg.c_str(),msg.size()+1);
//	printf("\nThe http server has sent %d datas:%s\n",sendLen, msg.c_str());

//  socketConnect_1.socketClose();
//  delete this;










	/*****************************************************************/
bool XHTTP::insert_1_function(char * recvBuf, int * length_recv)
{

	///////////////////////////////////////////////////

	string src = "";
	for (int i = 0; i < (*length_recv); i++) {
		src += recvBuf[i];
	}
	smatch mas;

	string pattern = "^[\\s\\S]*[cC]ontent-[lL]ength: ([0-9]+)\r\n";  // standard
																													 /*
																													 string pattern = "^[\\s\\S]*content-length: ([0-9]+)\r\n";  // standard
																													 Content-Type: multipart/form-data; boundary=WABoundary+F283EB321B329CAEWA
																													 */

	regex r(pattern);
	regex_search(src, mas, r);
	if (mas.size() == 0)
	{
		printf("%s failed!\n", pattern.c_str());

		return 1;
	}
	
	string mas_4 = mas[1];

	/////////////////////////////////////////////////

	string P = "\r\n\r\n";
	int  head_position = src.find(P, 0);
	head_position += 4;
	if (head_position != string::npos) {

		string content_length_temp = mas_4;
		int  content_length = atoi(content_length_temp.c_str());
		printf("\n\nthe content_length is :%d------the length_recv is :%d------the head position is :%d\n\n", content_length, (*length_recv), head_position);

		char * recvBuf_temper = recvBuf;
		recvBuf_temper += (*length_recv);
		while ((*length_recv) < content_length + head_position) {

			int recvLen = socketConnect_1.socketRecv(recvBuf_temper, 256);
			int count = 0;
			while (recvLen == 256) {
				recvBuf_temper += 256;
				recvLen = socketConnect_1.socketRecv(recvBuf_temper, 256);
				count++;

			}
			if (recvLen < 0) {
				printf("the data is error form the http client");

				//socketConnect_1.socketClose();
	//			close_socket_xhttp();
				//delete this;  //delete the function ?
				return 1;
			}


			(*length_recv) += (recvLen + count * 256);
		}
	}
	else {
		printf("\nXXXXXXXXXXXXXXXXthis is error in inser_functionXXXXXXXXXXXXXXXXXXXXXXXXXXX");
		return 1;
	}
	return 0;
}



	//////////////////////////////////////////////////////////////////////


	bool XHTTP::insert_function( char * recvBuf, int * length_recv)
	{

		///////////////////////////////////////////////////

		string src = "";
		for (int i = 0; i < (*length_recv); i++) {
			src += recvBuf[i];
		}
		smatch mas;

		string pattern = "^[\\s\\S]*[Cc]ontent-[Tt]ype: multipart/form-data; boundary=(.+)\r\n";  // standard
		/*
		string pattern = "^[\\s\\S]*content-length: ([0-9]+)\r\n";  // standard
		Content-Type: multipart/form-data; boundary=WABoundary+F283EB321B329CAEWA

		string pattern = "^[\\s\\S]*multipart/form-data; boundary=(.+)\r\n[\\s\\S]*[cC]ontent-[lL]ength: ([0-9]+)\r\n";
		*/

		
		regex r(pattern);
		regex_search(src, mas, r);
		if (mas.size() == 0)
		{
			printf("%s failed!\n", pattern.c_str());
		
			return 1;
		}
	    boundary = mas[1];

		/////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////

		smatch mas_2;
		pattern = "^[\\s\\S]*[cC]ontent-[lL]ength: ([0-9]+)\r\n";  // standard
	    /*
		string pattern = "^[\\s\\S]*content-length: ([0-9]+)\r\n";  // standard
		Content-Type: multipart/form-data; boundary=WABoundary+F283EB321B329CAEWA

		string pattern = "^[\\s\\S]*multipart/form-data; boundary=(.+)\r\n[\\s\\S]*[cC]ontent-[lL]ength: ([0-9]+)\r\n";
		*/

		regex r_2(pattern);
		regex_search(src, mas_2, r_2);
		if (mas_2.size() == 0)
		{
			printf("%s failed!\n", pattern.c_str());

			return 1;
		}
				
		string mas_4 = mas_2[1];

		printf("\nthe boundary:%s\n",boundary.c_str());
		///////////////////////////////////////////////////
		/////////////////////////////////////////////////

		string P = "\r\n\r\n";
		int  head_position = src.find(P, 0);
		head_position += 4;
		if (head_position != string::npos) {
			
			string content_length_temp = mas_4;
			int  content_length = atoi(content_length_temp.c_str());
			printf("\n\nthe content_length is :%d------the length_recv is :%d------the head position is :%d\n\n", content_length, (*length_recv), head_position);

			char * recvBuf_temper = recvBuf;
			recvBuf_temper += (*length_recv);
			while ((*length_recv) < content_length+ head_position ) {

				int recvLen = socketConnect_1.socketRecv(recvBuf_temper, 256);
				int count = 0;
				while (recvLen == 256) {
					recvBuf_temper += 256;
					recvLen = socketConnect_1.socketRecv(recvBuf_temper, 256);
					count++;

				}
				if (recvLen < 0) {
					printf("the data is error form the http client");

					//socketConnect_1.socketClose();
		//			close_socket_xhttp();
					//delete this;  //delete the function ?
					return 1;
				}


				(*length_recv) += (recvLen + count * 256);
			}
		}
		else {
			printf("\nXXXXXXXXXXXXXXXXthis is error in inser_functionXXXXXXXXXXXXXXXXXXXXXXXXXXX");
			return 1;
		}
		return 0;
	}




/////////////////////////////////////////////////////////////////////////////////////
	//void client_1_handle_xhttp(char * recvBuf);
	//////////////////////////////////////////////////////////////////

	void  XHTTP::client_3_handle_xhttp(char * recvBuf) {
	
		//openid = oSin80PrzfRtKWzjlHEGVC7QZiRA&driving_type = 2 & 
		//user_name = %E8%B5%B5%E8%BD%A9%E8%B6 % 85 & user_phone = 17711644028 & 
		//user_address = sz&user_company = %E4%BC % 98 % E7%A7 % 91 & user_zw = engineer


		smatch mas;
		string src = recvBuf;                   //  [\s\S]*   .*$
		string pattern = "\r\n\r\nopenid=(.*$)";  // standard
		regex r(pattern);
		regex_search(src, mas, r);
		if (mas.size() == 0)
		{
			printf("%s failed!\n", pattern.c_str());

			http_send_function("0");
			return;
		}
		string filepage_end = mas[1];
		// 得到这个客户data.
		printf("\n\ndata_client:%s\n", filepage_end.c_str());


		/****************************** END ******************************************************/

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////read the status related the openid ///////////////////////////////////////////////          
		// get data from  mysql;
		std::string column_status = "status";
		mysql postMysql2;
		if (postMysql2.IniteMysqlAndConnected())
			printf("mysql connect success\n");
		if (postMysql2.GetIdOrDataFromMysql(column_status, &filepage_end))
			printf("Get the id data. success\n");

		///////////////////////////////////////////////////////////////////////////////////////////
	
		http_send_function(filepage_end);

		

	}

	void  XHTTP::client_4_handle_xhttp(char * recvBuf) {

		//openid = oSin80PrzfRtKWzjlHEGVC7QZiRA&driving_type = 2 & 
		//user_name = %E8%B5%B5%E8%BD%A9%E8%B6 % 85 & user_phone = 17711644028 & 
		//user_address = sz&user_company = %E4%BC % 98 % E7%A7 % 91 & user_zw = engineer


		smatch mas;
		string src = recvBuf;                   //  [\s\S]*   .*$
		string pattern = "\r\n\r\nopenid=(.*$)";  // standard
		regex r(pattern);
		regex_search(src, mas, r);
		if (mas.size() == 0)
		{
			printf("%s failed!\n", pattern.c_str());

			http_send_function("0");
			return;
		}
		string filepage_end = mas[1];
		// 得到这个客户data.
		printf("\n\ndata_client:%s\n", filepage_end.c_str());


		/****************************** END ******************************************************/

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////read the status related the openid ///////////////////////////////////////////////          
		// get data from  mysql;
		std::string column_status = "finish";
		mysql postMysql2;
		if (postMysql2.IniteMysqlAndConnected())
			printf("mysql connect success\n");
		if (postMysql2.GetIdOrDataFromMysql(column_status, &filepage_end))
			printf("Get the id data. success\n");

		///////////////////////////////////////////////////////////////////////////////////////////

		http_send_function(filepage_end);



	}




	void XHTTP::http_send_function(std::string data_need_to_send) 
	
	{
		/*******************************respond the client******************************************************/

		//the response message is the : 1>state line  2>message head   3> message text;
		std::string msg = "";
		//1> 
		msg += "HTTP/1.1 200 ok ";
		//2> name +':' +spaceblock +value 
		msg += "service: XHttp\r\n";
		msg += "Content-Type: text/html\r\n";
		/*	msg += "Content-Length: ";// the 2> is end(double \r\n)

		char bsize[128] = { 0 };
		sprintf(bsize, "%d", filesize);
		msg += bsize;
		//rmsg +=
		//rmsg += "10\r\n";
		*/
		msg += "\r\n\r\n";

		//3>
		//msg +="1234567890";

		////////filepage_end==0,is not finish/////////////////
		msg += data_need_to_send; //　server has  received the custom's data, the client should goto the other page.

		int sendSize = socketConnect_1.socketSend(msg.c_str(), msg.size());
		printf("sendsize = %d\n", sendSize);
		printf("=======send=========\n%s\n=============\n", msg.c_str());

		//  the respond data 
		/*
		while (1) {
		int len = fread(recvBuf, 1, sizeof(recvBuf), fp);  // restart use the recvBuf[256] data;
		if (len <= 0)break;
		int re = socketConnect_1.socketSend(recvBuf, len);
		if (re <= 0)break;
		}
		*/
	
	}







///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////
/////////////////////
////////////////////
///////////////////
//////////////////                            backup  的 函数定义；
////////////////////
////////////////////////
///////////////////////
/////////////////////
///////////////////////
/////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

	void XHTTP::backup_1_handle_xhttp(char * recvBuf) 
	{
		smatch mas;
		string src = recvBuf;                   //  [\s\S]*   .*$
		string pattern = "\r\n\r\n(.*$)";  // standard
		regex r(pattern);
		regex_search(src, mas, r);
		if (mas.size() == 0)
		{
			printf("%s failed!\n", pattern.c_str());
			http_send_function("0");
			return;
		}
		string string_tempo = mas[1];
		printf("\n%s\n",string_tempo.c_str());
		//string_tempo.find("delete",0);

		if (string_tempo.find("delete", 0)!=0 ) {
			/******************************connect mysql**************************************************/
			std::string  id;
			// save to mysql;
			mysql postMysql;
			if (postMysql.IniteMysqlAndConnected())
				printf("mysql connect success\n");
			if (postMysql.GetIdFromMysql(&id, true)) {
				//char * temp_id=NULL;
				//int temp_temp_id = atoi(id.c_str());
				//itoa(++temp_temp_id, temp_id, 10);
				//id = *temp_id;

				printf("get the id=%s success\n", id.c_str());
				//int temp_length_id = id.length();
				//int temp_sum_id = 0;
				//for (int i = 0; i < temp_length_id; i++) {
				//	temp_sum_id *= 10;
				//	temp_sum_id += id[i] - 48;

				//}
				//++temp_sum_id;
				//for (int i = 0; i < temp_length_id; i++) {
				//	id[temp_length_id - i - 1] = temp_sum_id % 10 + 48;
				//	temp_sum_id /= 10;
				//}
				//printf("get the id=%s success\n", id.c_str());

			}

			/******************************END　　　connect mysql**************************************************/

			http_send_function(id);

		}

		else if (string_tempo.find("delete", 0)==0) {
		   
			// DELETE * FROM table_name;  
			// char tablename[50] = "test";
			std::string order_delete = "DELETE  FROM ";
			

			mysql postMysql_2;
			/////////////////////////////////////////////
			order_delete += postMysql_2.return_tablename_mysql();
			////////////////////////////////////////////
			if (postMysql_2.IniteMysqlAndConnected())
				printf("mysql connect success\n");
			if (postMysql_2.commonOrderMysql(order_delete) )
				printf("mysql delete success\n");


			http_send_function("100");

		
		}
	}



	//|||||||||||||||||||||||||||||||||||backup_2_handle_xhttp||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

	void XHTTP::backup_2_handle_xhttp(char * recvBuf) 
	{
		smatch mas;
		string src = recvBuf;                   //  [\s\S]*   .*$
		string pattern = "\r\n\r\n(([0-9]*)XXXX([0-9]*)$)";  // standard
		regex r(pattern);
		regex_search(src, mas, r);
		if (mas.size() == 0)
		{
			printf("%s failed!\n", pattern.c_str());
			http_send_function("0");
			return;
		}
		string data_backup = mas[1];
		string begin_number = mas[2];
		string end_number = mas[3];
		int end_begin_value = 0;
		// 得到这个客户data.

		printf("\n\ndata_client:%s\n", data_backup.c_str());
	//	printf("data_client length:%d", data_backup.length());
       ///////////////////////begin_number////////////////////////////////////
		for (int i = 0; i < 2;i++) {
			string * id= &begin_number;
			if (i == 1) { 
				id = &end_number;
			}

			int temp_length_id = (*id).length();
			int temp_sum_id = 0;
			for (int i = 0; i < temp_length_id; i++) {
				temp_sum_id *= 10;
				temp_sum_id += (*id)[i] - 48;

			}
			
			if (i) end_begin_value = temp_sum_id - end_begin_value;
			else end_begin_value += temp_sum_id;

			//	++temp_sum_id;
		//	for (int i = 0; i < temp_length_id; i++) {
		//		(*id)[temp_length_id - i - 1] = temp_sum_id % 10 + 48;
		//		temp_sum_id /= 10;
		//	}
			printf("get the id=%s success\n", (*id).c_str());

		}
      /////////////////////end_number//////////////////////////////////////////////

		//const int end_begin_value_temp = end_begin_value;
		std::string inputString = "SELECT * FROM test WHERE id between " + begin_number + " and " + end_number + " ;" ;

		std::string theRowHadRead[30];


  ////////////////////////connnect mysql ////////////////////////////////////////////
		mysql postMysql;
		if (postMysql.IniteMysqlAndConnected())
			printf("mysql connect success\n");
		if (postMysql.commonGetDataFromMysql(inputString, theRowHadRead)) 
			printf("Read data success\n");

		printf("\nI have rebacked to backup\\2's pages\n");
		for (int i = 0; i <= end_begin_value; i++) {
			printf("\n%s\n", theRowHadRead[i].c_str());
		}
		
  //////////////////////////////////////////////////////////////////////

  //the response message is the : 1>state line  2>message head   3> message text;
			std::string msg = "";
			//1> 
			msg += "HTTP/1.1 200 ok ";
			//2> name +':' +spaceblock +value 
			msg += "service: XHttp\r\n";
			msg += "Content-Type: text/html\r\n";
			/*	msg += "Content-Length: ";// the 2> is end(double \r\n)

			char bsize[128] = { 0 };
			sprintf(bsize, "%d", filesize);
			msg += bsize;
			//rmsg +=
			//rmsg += "10\r\n";
			*/
			msg += "\r\n\r\n";

			//3>
			//msg +="1234567890";

			////////filepage_end==0,is not finish/////////////////
		//	msg += data_need_to_send; //　server has  received the custom's data, the client should goto the other page.



			for (int i = 0; i <= end_begin_value; i++) {
				msg += theRowHadRead[i];
				msg += "@@@";
			}

			
			int sendSize = socketConnect_1.socketSend(msg.c_str(), msg.size());
			printf("sendsize = %d\n", sendSize);
			printf("=======send=========\n%s\n=============\n", msg.c_str());

			//  the respond data 
			/*
			while (1) {
			int len = fread(recvBuf, 1, sizeof(recvBuf), fp);  // restart use the recvBuf[256] data;
			if (len <= 0)break;
			int re = socketConnect_1.socketSend(recvBuf, len);
			if (re <= 0)break;
			}
			*/
	    
	}







	/////////////////////////////////////////////////////////////////////////////////
	//             backup_3_handle_xhttp
	/////////////////////////////////////////////////////////////////////////////////
	void XHTTP::backup_3_handle_xhttp(char * recvBuf)
	{
		smatch mas;
		string src = recvBuf;                   //  [\s\S]*   .*$
		string pattern = "\r\n\r\n(([0-9]*)XXXX([0-9]*)$)";  // standard
		regex r(pattern);
		regex_search(src, mas, r);
		if (mas.size() == 0)
		{
			printf("%s failed!\n", pattern.c_str());
			http_send_function("0");
			return;
		}
		string data_backup = mas[1];
		string begin_number = mas[2];
		int begin_number_int = 0;
		string end_number = mas[3];
		int end_begin_value = 0;
		// 得到这个客户data.

		printf("\n\ndata_client:%s\n", data_backup.c_str());
		//	printf("data_client length:%d", data_backup.length());

		///////////////////////begin_number////////////////////////////////////
		for (int i = 0; i < 2; i++) {
				string * id = &begin_number;
				if (i == 1) {
					id = &end_number;
				}

				int temp_length_id = (*id).length();
				int temp_sum_id = 0;
				for (int i = 0; i < temp_length_id; i++) {
					temp_sum_id *= 10;
					temp_sum_id += (*id)[i] - 48;

				}
				
				if (i) end_begin_value = temp_sum_id - end_begin_value;
				else {
					end_begin_value += temp_sum_id; 
					begin_number_int = temp_sum_id ;
				}

				//	++temp_sum_id;
				//	for (int i = 0; i < temp_length_id; i++) {
				//		(*id)[temp_length_id - i - 1] = temp_sum_id % 10 + 48;
				//		temp_sum_id /= 10;
				//	}
				printf("get the id=%s success\n", (*id).c_str());
				temp_sum_id = 0;
		}
		printf("\n-----------the begin_number_int :%d the end_begin_value :%d\n", begin_number_int , end_begin_value);
		/******************************************************************************************/

	//	std::string  send_data_picture = "\0";
		string filepath1 = "C:/WEIXIN/picture/";                //+ filepage_end + ".jpg";
		int filesize = 0;
		
		int picture_size[3] = { 0,0,0 };
		for (int i = 0; i <= end_begin_value;i++) {

		  std::string filepath = filepath1+ to_string(begin_number_int)+".jpg";
		  printf("\nfilepath:%s\n",filepath.c_str() );
			FILE *fp = fopen(filepath.c_str(), "rb");
			if (fp == NULL)
			{
				// Close();
				return;
			}
			//获取文件大小
			fseek(fp, 0, SEEK_END);
			picture_size[i]=ftell(fp);
			filesize+=picture_size[i];
			fseek(fp, 0, 0);


		//	filesize += 10;               //10 个@@@@@@@@@@

		//	int len = fread(send_data_picture.c_str(), 1, sizeof(buf), fp);
			
		}

	    filesize+=20;


		printf("file size is %d\n", filesize);


//////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
		std::string msg = "";
		//1> 
		msg += "HTTP/1.1 200 ok ";
		//2> name +':' +spaceblock +value 
		msg += "service: XHttp\r\n";
		msg += "Content-Type: text/html\r\n";
		msg += "Content-Length: "   ;// the 2> is end(double \r\n)

		char bsize[128] = { 0 };
		sprintf(bsize, "%d", filesize);
		msg += bsize;
		//rmsg +=
		//rmsg += "10\r\n";
		
		msg += "\r\n\r\n";



		int sendSize = socketConnect_1.socketSend(msg.c_str(), msg.size());
		printf("sendsize = %d\n", sendSize);
	                                //	printf("=======send=========\n%s\n=============\n", msg.c_str());
		 

		//char head_before_body[41]="\0";
		//printf("@@@@@@@@@@%06d/%06d/%06d@@@@@@@@@@", picture_size[0], picture_size[1], picture_size[2]);
		//sprintf(head_before_body, "@@@@@@@@@@%06d;%06d;%06d@@@@@@@@@@", picture_size[0], picture_size[1], picture_size[2]);


		msg = "@@@@@@@@@@";
	//	sendSize=socketConnect_1.socketSend(head_before_body,strlen(head_before_body));
	//	printf("the body head size=%d sendsize = %d\n", strlen(head_before_body), sendSize);

		char buf_temp[51200*2]="\0";
		for (int i = 0; i <= end_begin_value; i++) {
			printf("msg:%s", msg.c_str());
			socketConnect_1.socketSend(msg.c_str(), msg.length());

			std::string filepath = filepath1 + to_string(begin_number_int) + ".jpg";
			printf("\nfilepath:%s\n", filepath.c_str());

			buf_temp[picture_size[i] + 1] = '\0';
			ifstream fin(filepath, ios::in | ios::binary | ios::ate);
			//	size = data_need_to_writted.length();
			//////in.seekg(0, ios::beg);
			//buffer = new char[size];
			///in.read(buffer, size);
			fin.seekg(0, ios::beg);                        ///////////////////
			fin.read(buf_temp, picture_size[i]);
			fin.close();
			printf("\n%s\n", buf_temp);


				int len=socketConnect_1.socketSend(buf_temp, picture_size[i]);
				if (len==picture_size[i]) printf("\n commit picture is success******\n");
				else  printf("\ncommit picture is error+++%d+++\n",picture_size[i]- len);
			printf("msg:%s",msg.c_str() );
			socketConnect_1.socketSend(msg.c_str(), msg.length());
		}


	}






 /*
 
 		char buf_temp[40000];
		for (int i = 0; i <= end_begin_value; i++) {

			std::string filepath = filepath1 + to_string(begin_number_int + i) + ".jpg";
			printf("\nfilepath:%s\n", filepath.c_str());
			FILE *fp = fopen(filepath.c_str(), "rb");
			if (fp == NULL)
			{
				// Close();
				return;
			}

			for (;;)
			{
				int len = fread(buf_temp, 1, sizeof(buf_temp), fp);
				if (len <= 0)break;
				socketConnect_1.socketSend(buf_temp,len);

			}
			// 分隔符；；；
		//	socketConnect_1.socketSend(msg.c_str(), msg.size());
		}

 
 
 */


	void XHTTP::backup_4_handle_xhttp(char * recvBuf)
	{
	
		smatch mas;
		string src = recvBuf;                   //  [\s\S]*   .*$
		string pattern = "\r\n\r\n([0-9]*)$";   // standard
		regex r(pattern);
		regex_search(src, mas, r);
		if (mas.size() == 0)
		{
			printf("%s failed!\n", pattern.c_str());
			http_send_function("0");
			return;
		}
	//	string data_backup = mas[1];
		string begin_number = mas[1];
		//string end_number = mas[3];
		//int end_begin_value = 0;
		// 得到这个客户data.

		printf("\nbegin_number:%s\n", begin_number.c_str());
		//	printf("data_client length:%d", data_backup.length());
		///////////////////////begin_number////////////////////////////////////
		//for (int i = 0; i < 2; i++) {
		//string * id = &begin_number;
		//	//if (i == 1) {
		//	//	id = &end_number;
		//	//}

		//	int temp_length_id = (*id).length();
		//	int temp_sum_id = 0;
		//	for (int i = 0; i < temp_length_id; i++) {
		//		temp_sum_id *= 10;
		//		temp_sum_id += (*id)[i] - 48;

		//	}

			//if (i) end_begin_value = temp_sum_id - end_begin_value;
			//else end_begin_value += temp_sum_id;

			//	++temp_sum_id;
			//	for (int i = 0; i < temp_length_id; i++) {
			//		(*id)[temp_length_id - i - 1] = temp_sum_id % 10 + 48;
			//		temp_sum_id /= 10;
			//	}
		//	printf("get the id=%s success\n", (*id).c_str());

		
		/////////////////////end_number//////////////////////////////////////////////

		        //const int end_begin_value_temp = end_begin_value;


		std::string inputString = "UPDATE test SET status = 1 WHERE id =" + begin_number + " ;";

		        //std::string theRowHadRead[30];


		////////////////////////connnect mysql ////////////////////////////////////////////
		mysql postMysql;
		if (postMysql.IniteMysqlAndConnected())
			printf("mysql connect success\n");
		if (postMysql.commonOrderMysql(inputString) )
			printf("status was set success success\n");

				//printf("\nI have rebacked to backup\\2's pages\n");
				//for (int i = 0; i <= end_begin_value; i++) {
				//	printf("\n%s\n", theRowHadRead[i].c_str());
				//}
		 postMysql.closeMysqlCon();

		 http_send_function("1");


	
	}


	void XHTTP::backup_5_handle_xhttp(char * recvBuf)
	{

		smatch mas;
		string src = recvBuf;                   //  [\s\S]*   .*$
		string pattern = "\r\n\r\n([0-9]*)$";   // standard
		regex r(pattern);
		regex_search(src, mas, r);
		if (mas.size() == 0)
		{
			printf("%s failed!\n", pattern.c_str());
			http_send_function("0");
			return;
		}
		//	string data_backup = mas[1];
		string begin_number = mas[1];
		//string end_number = mas[3];
		//int end_begin_value = 0;
		// 得到这个客户data.

		printf("\nbegin_number:%s\n", begin_number.c_str());
		//	printf("data_client length:%d", data_backup.length());
		///////////////////////begin_number////////////////////////////////////
		//for (int i = 0; i < 2; i++) {
		//string * id = &begin_number;
		//	//if (i == 1) {
		//	//	id = &end_number;
		//	//}

		//	int temp_length_id = (*id).length();
		//	int temp_sum_id = 0;
		//	for (int i = 0; i < temp_length_id; i++) {
		//		temp_sum_id *= 10;
		//		temp_sum_id += (*id)[i] - 48;

		//	}

		//if (i) end_begin_value = temp_sum_id - end_begin_value;
		//else end_begin_value += temp_sum_id;

		//	++temp_sum_id;
		//	for (int i = 0; i < temp_length_id; i++) {
		//		(*id)[temp_length_id - i - 1] = temp_sum_id % 10 + 48;
		//		temp_sum_id /= 10;
		//	}
		//	printf("get the id=%s success\n", (*id).c_str());


		/////////////////////end_number//////////////////////////////////////////////

		//const int end_begin_value_temp = end_begin_value;


		std::string inputString = "UPDATE test SET finish = 1 WHERE id =" + begin_number + " ;";

		//std::string theRowHadRead[30];


		////////////////////////connnect mysql ////////////////////////////////////////////
		mysql postMysql;
		if (postMysql.IniteMysqlAndConnected())
			printf("mysql connect success\n");
		if (postMysql.commonOrderMysql(inputString))
			printf("status was set success success\n");

		//printf("\nI have rebacked to backup\\2's pages\n");
		//for (int i = 0; i <= end_begin_value; i++) {
		//	printf("\n%s\n", theRowHadRead[i].c_str());
		//}
		postMysql.closeMysqlCon();
		http_send_function("1");
	}




	///////////////////////////////////////////////////////////////////////////////////////

	/*
	//the response message is the : 1>state line  2>message head   3> message text;
	std::string msg = "";
	//1>
	msg += "HTTP/1.1 200 ok ";
	//2> name +':' +spaceblock +value
	msg += "service: XHttp\r\n";
	msg += "Content-Type: text/html\r\n";
	/*	msg += "Content-Length: ";// the 2> is end(double \r\n)

	char bsize[128] = { 0 };
	sprintf(bsize, "%d", filesize);
	msg += bsize;
	//rmsg +=
	//rmsg += "10\r\n";
	//*/
	//	msg += "\r\n\r\n";

	//3>
	//msg +="1234567890";

	////////filepage_end==0,is not finish/////////////////
	//	msg += data_need_to_send; //　server has  received the custom's data, the client should goto the other page.

	/*

	for (int i = 0; i <= end_begin_value; i++) {
	msg += theRowHadRead[i];
	msg += "@@@";
	}


	int sendSize = socketConnect_1.socketSend(msg.c_str(), msg.size());
	printf("sendsize = %d\n", sendSize);
	printf("=======send=========\n%s\n=============\n", msg.c_str());
	*/
















































