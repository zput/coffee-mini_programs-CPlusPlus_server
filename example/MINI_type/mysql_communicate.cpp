
#include <mysql_communicate.h>

#include <iostream>
#include <stdio.h>
#include <string>
#include <time.h>



#if defined(_WIN32)
	#include <windows.h>
	#include "winsock.h" 
	#include "include\mysql.h"
	#pragma comment(lib,"libmySQL.lib") 
	#pragma warning(disable:4996)
#else

#endif


	    //init the mysql;
  bool	mysql::IniteMysqlAndConnected()
{ 
	    int rt;  //return value
		con = mysql_init((MYSQL*)0);


		if (con != NULL && mysql_real_connect(con, dbip, dbuser, dbpasswd, dbname, 3306/*TCP IP端口*/, NULL/*Unix Socket 连接类型*/, 0/*运行成ODBC数据库标志*/))
		{
			if (!mysql_select_db(con, dbname))
			{
				printf("Select successfully the database!\n");

				con->reconnect = 1;

				query = "set names \'GBK\'";
				//mysql_query(con,"set names \'GBK\'"); 

				rt = mysql_real_query(con, query, strlen(query));
				if (rt)
				{
					printf("Error making query: %s !!!\n", mysql_error(con));
					return false;
				}
				else
				{
					printf("query %s succeed!\n", query);
				}

			}
		}

		else
		{
			ERROR("\n\nUnable to connect the database,check your configuration!\n\n");
			return false;
		}
		return true;
}




  bool  mysql::SaveJsonData2Mysql(std::string * strJsonData, std::string id)
  {
	    int rt;			  //return value   
		char save_mysql_order[500] = "";

		long   long int time_now= time(0);
		DEBUG("insert into %s(id,openid, driving_type, user_name, user_phone, user_address, user_company, user_zw,time_zxc) values(%s,'%s','%s','%s','%s','%s','%s','%s','%lld');\r\n", tablename, id.c_str(),
		strJsonData[0].c_str(), strJsonData[1].c_str(), strJsonData[2].c_str(),
		strJsonData[3].c_str(), strJsonData[4].c_str(), strJsonData[5].c_str(), strJsonData[6].c_str(), time_now );

		sprintf(save_mysql_order, "insert into %s(id,openid, driving_type, user_name, user_phone, user_address, user_company, user_zw,time_zxc) values(%s,'%s','%s','%s','%s','%s','%s','%s','%lld');\r\n", tablename, id.c_str(),
		strJsonData[0].c_str(), strJsonData[1].c_str(), strJsonData[2].c_str(),
		strJsonData[3].c_str(), strJsonData[4].c_str(), strJsonData[5].c_str(), strJsonData[6].c_str(), time_now);

            
	
			//注意如何向具有自增字段的数据库中插入记录
									rt = mysql_real_query(con, save_mysql_order, strlen(save_mysql_order));
						if (rt)
						{
							DEBUG("Error making query: %s !!!\n", mysql_error(con));

							std::string error_mysql = mysql_error(con);
						    //	strJsonData[0]
						
							if (int  head_position = error_mysql.find(strJsonData[0], 0) >3) {
								//
								//       比较两者的时间如果<60秒，着这次数据不进入MySQL中。
								//
								std::string openid_temp_check_time = strJsonData[0];
								if (GetIdOrDataFromMysql("time_zxc", &openid_temp_check_time, 0) == true) {
									long long int time_before = atoll(openid_temp_check_time.c_str());
									std::cout << "\ntime_now-time_before----->" << time_now << "-" << time_before << "=[" << time_now - time_before << "]" << std::endl;
									if (time_now - time_before < 60) {
										return false;

									}
								}
								else {
									return false;
								}
									//std::string temp_mysql_order = "DELETE FROM test WHERE openid =\"" + strJsonData[0] + "\" ;";
								char temp_64[64];
								sprintf(temp_64,"%I64d",time(0));
								std::string temp_64_string = temp_64;
								std::string temp_mysql_order = "UPDATE "+return_tablename_mysql()+" SET openid =\""+ strJsonData[0]+ temp_64_string+"\"" +" WHERE openid =\"" + strJsonData[0] + "\" ;";

								if (commonOrderMysql(temp_mysql_order)) {
									rt = mysql_real_query(con, save_mysql_order, strlen(save_mysql_order));
									if (rt)
									{
										DEBUG("Error making query: %s !!!\n", mysql_error(con));
										return false;
									}
									else{
										DEBUG("success about the mysql ");		
									}
									return true;
								}

							}
							else {

							}
							 return false;

						}

			/////////////////////else if/////////////////////////////////

						else
						{
							DEBUG("success about the mysql ");
						}
			return true;
}




  bool  mysql::GetIdOrDataFromMysql(std::string column_name, std::string * openid_data)
  {
	  char tmp[200]="\0";

	  sprintf(tmp, "SELECT %s FROM %s WHERE openid=\"%s\";", column_name.c_str(),tablename,(*openid_data).c_str());
	  DEBUG("\ntemp:%s\n",tmp);

	  int rt=0;
	  if (dbuser != NULL) TRACE("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");

	  rt = mysql_real_query(con, tmp, strlen(tmp));
	  if (rt)
	  {
		  DEBUG("Error making query: %s !!!\n", mysql_error(con));
		  return true;
	  }
	  else
	  {
		  printf("%s executed!!!\n", tmp);
	  }

	  res = mysql_store_result(con);//将结果保存在res结构体中

	  int count = 0;
	  while (row = mysql_fetch_row(res))
	  {
		  /**
		  * MYSQL_ROW STDCALL mysql_fetch_row(MYSQL_RES *result);
		  * 检索行
		  */

		  for (unsigned int t = 0; t<mysql_num_fields(res); t++)
		  {
			  printf("%s  ", row[t]);
			  (*openid_data) = row[t];
		  }
		  printf(".............\n");
		  count++;
	  }
	  DEBUG("number of rows %d\n", count);
	  return true;
	      
  }



  bool    mysql::GetIdOrDataFromMysql(std::string column_name, std::string * openid_data, bool whetherReleaseCon)
  {  
	  char tmp[200] = "\0";
	  sprintf(tmp, "SELECT %s FROM %s WHERE openid=\"%s\";", column_name.c_str(), tablename, (*openid_data).c_str());
	  DEBUG("\ntemp:%s\n", tmp);

	  int rt = 0;
	  if (dbuser != NULL) TRACE("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");

	  rt = mysql_real_query(con, tmp, strlen(tmp));
	  if (rt)
	  {
		  DEBUG("Error making query: %s !!!\n", mysql_error(con));
		  return false;
	  }
	  else
	  {
		  DEBUG("%s executed!!!\n", tmp);
	  }

	  res = mysql_store_result(con);//将结果保存在res结构体中

	  //int count = 0;
	  while (row = mysql_fetch_row(res))
	  {
		  /**
		  * MYSQL_ROW STDCALL mysql_fetch_row(MYSQL_RES *result);
		  * 检索行
		  */

		  for (unsigned int t = 0; t<mysql_num_fields(res); t++)
		  {
			  printf("%s  ", row[t]);
			  (*openid_data) = row[t];
		  }
		  TRACE(".............\n");

	  }

	  if (whetherReleaseCon) {

	  }

	  return true;
    
  }

























  bool  mysql::GetIdFromMysql( std::string*  id, bool whetherReleaseCon)
  {
	  char tmp[100] = "\0";
	  sprintf(tmp, "SELECT id FROM %s;",tablename);
	  DEBUG("\ntemp:%s\n", tmp);

	  int rt = 0;

	  if (dbuser != NULL) DEBUG("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");

	  rt = mysql_real_query(con, tmp, strlen(tmp));
	  if (rt)
	  {
		  DEBUG("Error making query: %s !!!\n", mysql_error(con));
		  return true;
	  }
	  else
	  {
		  DEBUG("%s executed!!!\n", tmp);
	  }

	  res = mysql_store_result(con);//将结果保存在res结构体中

	  int count = 0;
	  while (row = mysql_fetch_row(res))
	  {
		  /**
		  * MYSQL_ROW STDCALL mysql_fetch_row(MYSQL_RES *result);
		  * 检索行
		  */

		  for (unsigned int t = 0; t<mysql_num_fields(res); t++)
		  {
			  printf("%s  ", row[t]);
			  (*id) = row[t];
		  }
		  printf(".............\n");
		  count++;
	  }
	  DEBUG("number of rows %d\n", count);

	  if (count==0) {
		  (*id) = "0";
	  }

	  if (whetherReleaseCon) {

	  }
	  return true;

  }




bool  mysql::commonGetDataFromMysql(std::string inputString,std::string * theRowHadRead )
{
	//char tmp[50]="\0";
	char tmp[300] = "\0";



	sprintf(tmp, "%s", inputString.c_str() );

	printf("\ntemp:%s\n", tmp);

	int rt = 0;

	if (dbuser != NULL) printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
	//if (con == NULL) printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt)
	{
		DEBUG("Error making query: %s !!!\n", mysql_error(con));
		return true;
	}
	else
	{
		printf("%s executed!!!\n", tmp);
	}

	res = mysql_store_result(con);//将结果保存在res结构体中

	int count = 0;
	while (row = mysql_fetch_row(res))
	{
		/**
		* MYSQL_ROW STDCALL mysql_fetch_row(MYSQL_RES *result);
		* 检索行
		*/

		//std::string theRowHadRead[30];

		for (unsigned int t = 0; t<mysql_num_fields(res)-3; t++)
		{
			printf("%s  ", row[t]);
			if (t== mysql_num_fields(res)-4 ) {
				theRowHadRead[count] += "\"";
				theRowHadRead[count] += row[t];
				theRowHadRead[count] += "\" ";
			
			}
			else if (t != 0) {
				theRowHadRead[count] += "\"";
				theRowHadRead[count] += row[t];
				theRowHadRead[count] += "\", ";
			}
			else {
				theRowHadRead[count] += row[t];
				theRowHadRead[count] += ", ";
			}
		}
		//(*theRowHadRead)[count] = row;
		
		/*
		for (unsigned int t = 0; t<mysql_num_fields(res)-2; t++)
		{
			printf("%s  ", row[t]);
			if (t== mysql_num_fields(res)-3 ) {
				theRowHadRead[count] += "\"";
				theRowHadRead[count] += row[t];
				theRowHadRead[count] += "\" ";
			
			}
			else if (t != 0) {
				theRowHadRead[count] += "\"";
				theRowHadRead[count] += row[t];
				theRowHadRead[count] += "\", ";
			}
			else {
				theRowHadRead[count] += row[t];
				theRowHadRead[count] += ", ";
			}
		}
		//(*theRowHadRead)[count] = row;
		*/


		printf(".............\n");
		count++;
	}
	DEBUG("number of rows %d\n", count);

	return true;

}

bool  mysql::deleteFinishEqual1DataFromMysql(std::string inputString, std::string * theRowHadRead)
{
	//char tmp[50]="\0";
	char tmp[300] = "\0";



	sprintf(tmp, "%s", inputString.c_str());

	printf("\ntemp:%s\n", tmp);

	int rt = 0;

	if (dbuser != NULL) printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
	//if (con == NULL) printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt)
	{
		DEBUG("Error making query: %s !!!\n", mysql_error(con));
		return true;
	}
	else
	{
		DEBUG("%s executed!!!\n", tmp);
	}

	res = mysql_store_result(con);//将结果保存在res结构体中

	int count = 0;
	while (row = mysql_fetch_row(res))
	{
		/**
		* MYSQL_ROW STDCALL mysql_fetch_row(MYSQL_RES *result);
		* 检索行
		*/

		//std::string theRowHadRead[30];

			if (row[1] == "1") {
				printf("I will delete the data that its id equal %s",row[0]);
				theRowHadRead[count] = row[0];
			        
			}
	
		//(*theRowHadRead)[count] = row;

		printf(".............\n");
		count++;
	}
	DEBUG("number of rows %d\n", count);

	return true;

}






bool  mysql::commonOrderMysql(std::string inputString)
{
	//char tmp[50]="\0";
	char tmp[300] = "\0";



	sprintf(tmp, "%s", inputString.c_str());

	printf("\ntemp:%s\n", tmp);

	int rt = 0;

	if (dbuser != NULL) printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
	//if (con == NULL) printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
	rt = mysql_real_query(con, tmp, strlen(tmp));
	if (rt)
	{
		DEBUG("Error making query: %s !!!\n", mysql_error(con));
		return false;
	}
	else
	{
		DEBUG("%s executed!!!\n", tmp);
	}

	return true;

}


void mysql::closeMysqlCon()
{
	mysql_close(con);
}










