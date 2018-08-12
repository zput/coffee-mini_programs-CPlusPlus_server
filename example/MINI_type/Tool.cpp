
#include "Tool.h"


 const string picture_path_in_server_weixin = "C:/WEIXIN/picture_9020/";

 
 bool	writerDataToFile(std::string filepath, std::string data_need_to_writted, int length)
 {

	 // reading binary file  
	 //const char * filename = "test.txt";
	 //write(char * buffer, streamsize size);
	 //read(char * buffer, streamsize size);
	 //这里 buffer 是一块内存的地址，用来存储或读出数据。
	 //参数size 是一个整数值，表示要从缓存（buffer）中读出或写入的字符数。

	 long size;
	 ofstream out(filepath, ios::out | ios::binary | ios::ate);
	 size = data_need_to_writted.length();

	 out.write(data_need_to_writted.c_str(), size);
	 out.close();
	 return 0;

 }

 

		
	void Tool::delete_finishEqual_1()
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
		fin.seekg(0, std::ios::end);
		std::streampos html_size=fin.tellg();

		fin.seekg(0, ios::beg);                        ///////////////////
		fin.read(html_code, html_size);
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
				if (strJsonData[1] == "1") { sprintf(html_code + byte_number[1],"%s", "普通咖啡" ); }
				else if (strJsonData[1] == "2") { sprintf(html_code + byte_number[1], "%s", "普通热水"); }
				else if (strJsonData[1] == "3") { sprintf(html_code + byte_number[1], "%s", "特浓咖啡"); }
				else if (strJsonData[1] == "4") { sprintf(html_code + byte_number[1], "%s", "拿铁"); }
				else if (strJsonData[1] == "5") { sprintf(html_code + byte_number[1], "%s", "开水"); }

				}
			
			else sprintf(html_code + byte_number[i], "%s",strJsonData[i].c_str());
		}
	

   ///////////////// write to a new html file////////////////////////////////////////
		                //long size;
		filepath = "C:/WEIXIN/WEIXIN/nginx-1.13.1/html/9020/"+id+".html";
		ofstream out(filepath, ios::out | ios::binary | ios::ate);
						//size = data_need_to_writted.length();
						//////in.seekg(0, ios::beg);
						//buffer = new char[size];
						///in.read(buffer, size);
		out.write(html_code, html_size);
		out.close();
	     
		
  ///////////////////////////////////////////////////////////


		delete[] html_code;
		return 0;
	}







  bool Tool::client_1_handle_xhttp(const std::string& request_body, std::string*  wait_2_send_responseBody)
	{
		// 得到这个客户Request's body.
	/*******************parser the weixin little program ***********************************/
		std::string string_array[8] = {""};
		parson_from_weixinLittle_data(request_body,string_array);

	/************************save the data to mysql(save_little_program test)***********************************************/
		std::string  id;

			// save to mysql;
		if (mysql_.GetIdFromMysql( &id,false)) {

			DEBUG("get the id=%s success\n",id.c_str());
			int temp_length_id = id.length();
			int temp_sum_id = 0;
			for (int i = 0; i < temp_length_id; i++) {
				temp_sum_id *= 10;
				temp_sum_id += id[i] - 48;
				
			}
			++temp_sum_id;
			char temp_id_c[10] = {0};
			sprintf(temp_id_c,"%d",temp_sum_id);
			id = temp_id_c;
			DEBUG("get the id=%s success\n", id.c_str());
		}

		if (mysql_.SaveJsonData2Mysql(string_array, id) ==false) {
			return false;
		}
		INFO("Json data was transmitted. success\n");
		//create a  html page in order to two_bar_code
		creat_html_aboutId(string_array, id);

		*wait_2_send_responseBody = id;
    
		return true;
	}



////////////////////////////////////////////////////////////////////////
		 ///          client_2_handle_xhttp(recvBuf)   
		///
	   ///              //  [\s\S]*   .*$      content-length: 9047
///////////////////////////////////////////////////////////////////////



		bool Tool::client_2_handle_xhttp( const std::string& request_body, const std::string& content_type )
		{
			   // get boundary
			std::string boundary = NULL;
			auto temp = std::find(content_type.begin(),content_type.end(),'=');
			if (temp==content_type.end()) {
				return false;
			}
			boundary = std::string(temp, content_type.end() - 1);     //FIXME
			DEBUG("boundary:%s", boundary.c_str());


			  // 获取openID
			std::string openID = NULL;
 			temp = std::find(request_body.begin(),request_body.end(),"\r\n\r\n");
			if (temp == request_body.end()) {
				return false;
			}
			openID = std::string(temp + 4, std::find(temp + 4, request_body.end(), "\r\n") - 1);
			DEBUG("openID:%s", openID.c_str());


			   // get picture binary
			std::string picture_binary = NULL;
			temp = std::find(temp+4, request_body.end(), "\r\n\r\n");
			if (temp == request_body.end()) {
				return false;
			}
			/*    \r\n--${bound}--*/
			picture_binary = std::string(temp + 4,  request_body.end() - content_type.length() - 7);
			DEBUG("picture_binary:%s", picture_binary.c_str());


			     // 以openID 来得到数据库对应的 ID 号. 
                 // read the id related the openid 
		         // get data from  mysql;
			std::string column_id = "id";				
			if(mysql_.GetIdOrDataFromMysql(column_id, &openID) )
					  DEBUG("Get the id data. success\n");

    		string filepath = picture_path_in_server_weixin + openID + ".jpg";
			writerDataToFile(filepath, picture_binary, picture_binary.length());

			return true;
		}

	bool  Tool::client_3_handle_xhttp( const std::string& request_body, std::string*  wait_2_send_responseBody) {
	
				//openid = oSin80PrzfRtKWzjlHEGVC7QZiRA&driving_type = 2 & 
				//user_name = %E8%B5%B5%E8%BD%A9%E8%B6 % 85 & user_phone = 17711644028 & 
				//user_address = sz&user_company = %E4%BC % 98 % E7%A7 % 91 & user_zw = engineer


		auto temp = std::find(request_body.begin(), request_body.end(), '=');
		if (temp == request_body.end()) {		   
			return false;
		}
		std::string openID(temp, request_body.end() -1 );
		DEBUG("openID:%s", openID.c_str());

				// get data from  mysql;
		std::string column_status = "status";
		if (mysql_.GetIdOrDataFromMysql(column_status, &openID))
			 printf("Get the id data. success\n");

		///////////////////////////////////////////////////////////////////////////////////////////
	  
		*wait_2_send_responseBody = openID;
		
		return true;

	}




	bool  Tool::client_4_handle_xhttp(const std::string& request_body, std::string*  wait_2_send_responseBody) {

		//openid = oSin80PrzfRtKWzjlHEGVC7QZiRA&driving_type = 2 & 
		//user_name = %E8%B5%B5%E8%BD%A9%E8%B6 % 85 & user_phone = 17711644028 & 
		//user_address = sz&user_company = %E4%BC % 98 % E7%A7 % 91 & user_zw = engineer


		auto temp = std::find(request_body.begin(), request_body.end(), '=');
		if (temp == request_body.end()) {
			return false;
		}
		std::string openID(temp, request_body.end() - 1);
		DEBUG("openID:%s", openID.c_str());



		// get data from  mysql;
		std::string column_status = "finish";
		if (mysql_.GetIdOrDataFromMysql(column_status, &openID))
			printf("Get the id data. success\n");

		///////////////////////////////////////////////////////////////////////////////////////////

		*wait_2_send_responseBody = openID;

		return true;

	}
