#include <windows.h>
#include <iostream>
#include "include\mysql.h"
#include "stdio.h"
#include "winsock.h" 
#include "mysql_communicate.h"
#include <string>
#include<time.h>
#pragma comment(lib,"libmySQL.lib") 
#pragma warning(disable:4996)

//#param warning(disable:4996)




	//int x;
	//int y;
	//int rt;//return value
	//unsigned int t;

	//int count = 0;


	//printf("input x,y\n");
	////scanf_s("%d,%d", &x, &y);
	//std::cin >> x >> y;
	////	printf("the input value X:_%d_ Y:_%d_",x,y);
	//fflush(stdin);
	//printf("input over\n");



	//  init the mysql;
  bool	mysql::IniteMysqlAndConnected()
{ 
	    int rt;//return value
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
			MessageBoxA(NULL, "Unable to connect the database,check your configuration!", "", NULL);
			return false;
		}
		return true;
}


  //
  bool  mysql::SaveJsonData2Mysql(std::string * strJsonData, std::string id)
  {
	    int rt;//return value   
		char save_mysql_order[500] = "";
		//char save_mysql_order[200]="delete from test";

		/*
		//char * save_order_temp = save_mysql_order;

		                         //   int times = 6;              //  std::stoi(strJsonData[0]);
									                            //printf("\n_%d_\n", times);

		rt = mysql_real_query(con, save_mysql_order, strlen(save_mysql_order));
		if (rt)
		{
			printf("Error making query: %s !!!\n", mysql_error(con));
            return false;
		}
		else
		{
			//printf("%s executed!!!\n", tmp);
			printf("\nIt is success to delete the original Data\n----------------------\n");
			//return true;
		}
		*/

		//for (int i = 0; i < times; i++) {
		// insert into test(openid, driving_type, user_name, user_phone, user_address, user_company, user_zw) values('pSin80PrzfRtKWzjlHEGVC7QZiRA', 1, 'Yy', 'Cvbh', 'Gh', 'Mn', 'Hord');


		printf("insert into %s(id,openid, driving_type, user_name, user_phone, user_address, user_company, user_zw)values(%s,'%s','%s','%s','%s','%s','%s','%s');\r\n",tablename, id.c_str(),
			strJsonData[0].c_str(),strJsonData[1].c_str(), strJsonData[2].c_str(),
		strJsonData[3].c_str(), strJsonData[4].c_str(), strJsonData[5].c_str(), strJsonData[6].c_str());

		              //	);


			//sprintf(tmp,"update %s set 商品=\'%s\',卖出=%d,成交=%d,涨跌=%d,买进=%d,总量=%d,涨幅=%f,时间=\'%s\' where  %s",tablename,goods,sold,deal,fluctuate,buy,total,delta,time,UpdateCon);

			sprintf(save_mysql_order, "insert into %s(id,openid, driving_type, user_name, user_phone, user_address, user_company, user_zw) values(%s,'%s','%s','%s','%s','%s','%s','%s');\r\n",tablename, id.c_str(),
				strJsonData[0].c_str(), strJsonData[1].c_str(), strJsonData[2].c_str(),
				strJsonData[3].c_str(), strJsonData[4].c_str(), strJsonData[5].c_str(), strJsonData[6].c_str());
            
		//	printf("\nstd::string id=%s---%d\n",id.c_str(), strlen(save_mysql_order));
			//注意如何向具有自增字段的数据库中插入记录
									rt = mysql_real_query(con, save_mysql_order, strlen(save_mysql_order));
						if (rt)
						{
							printf("Error making query: %s !!!\n", mysql_error(con));
							//printf("\nINPUT 'C(ontinue)',if you want to continue download data.\ninputting any other character will be QUIT\n ");
							//if (getchar() == 'c' || getchar() == 'C')
								//;
							//else
							////////////////////////////////RETRY//AGAIN//////////////////////////////////
							std::string error_mysql = mysql_error(con);
						    //	strJsonData[0]
						
							if (int  head_position = error_mysql.find(strJsonData[0], 0) >3) {

								                             //UPDATE test SET openid ='GVC7QZiRAqqtime' WHERE openid = 'oSin80PrzfRtKWzjlHEGVC7QZiRA' 

								//std::string temp_mysql_order = "DELETE FROM test WHERE openid =\"" + strJsonData[0] + "\" ;";
								char temp_64[64];
								sprintf(temp_64,"%I64d",time(0));
								std::string temp_64_string = temp_64;
								std::string temp_mysql_order = "UPDATE "+return_tablename_mysql()+" SET openid =\""+ strJsonData[0]+ temp_64_string+"\"" +" WHERE openid =\"" + strJsonData[0] + "\" ;";

								if (commonOrderMysql(temp_mysql_order)) {
									rt = mysql_real_query(con, save_mysql_order, strlen(save_mysql_order));
									if (rt)
									{
										printf("Error making query: %s !!!\n", mysql_error(con));
										printf("mysql_free_result...\n");
										mysql_free_result(res);
										mysql_close(con);
										return false;
									}
									else
									{
										//printf("%s executed!!!\n", tmp);
										printf("success about the mysql ");
										//return true;
									}
									printf("mysql_free_result...\n");
									mysql_free_result(res);
									mysql_close(con);
									return true;
								}

							}
							else {
								 printf("mysql_free_result...\n");
							     mysql_free_result(res);
							     mysql_close(con);
							}
							 return false;

						}

			/////////////////////else if/////////////////////////////////

						else
						{
							//printf("%s executed!!!\n", tmp);
							printf("success about the mysql ");
							//return true;
						}
  /*
			int temppp = strlen(save_mysql_order);
			for (int i = 20;i<temppp+2; i++) {
				save_mysql_order[i] = '\0';
			
			//}
  */
			//save_order_temp += strlen(save_order_temp);

			printf("mysql_free_result...\n");
			mysql_free_result(res);
		    mysql_close(con);
			return true;
}
  ////////////////////////////////// END /////////////////////////////




	//	printf("\nthe jsondata:-----------\n------------\n%s\n",save_mysql_order);

		//printf("the physical address is :%x",save_mysql_order);
	   //getchar();																		
	  //MessageBoxA(NULL,tmp,tmp,MB_OK);
	 //mysql_query(con,tmp);
         
	//char  tempp[140] = "insert into test values(100,2,1495503071,'lincx',110,'\0xc9\0xee','uct','x','Iorder2017052310248579',0,0,'aa','2017-05-23 09:31:11')";
		

	//	rt = mysql_real_query(con, tempp, strlen(tempp));
		
    //}




  bool  mysql::GetIdOrDataFromMysql(std::string column_name, std::string * openid_data)
  {
	  //char tmp[50]="\0";
	  char tmp[200]="\0";

	  sprintf(tmp, "SELECT %s FROM %s WHERE openid=\"%s\";", column_name.c_str(),tablename,(*openid_data).c_str());

	  printf("\ntemp:%s\n",tmp);

	  int rt=0;

	  if (dbuser != NULL) printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
	  //if (con == NULL) printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
	  rt = mysql_real_query(con, tmp, strlen(tmp));
	  if (rt)
	  {
		  printf("Error making query: %s !!!\n", mysql_error(con));

		  mysql_close(con);
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
	 printf("number of rows %d\n", count);


	  printf("mysql_free_result...\n");
	  mysql_free_result(res);


	  mysql_close(con);
	  return true;
	      
  }



  bool  mysql::GetIdFromMysql( std::string*  id, bool whetherReleaseCon)
  {
	  //char tmp[50]="\0";
	  char tmp[100] = "\0";

	  sprintf(tmp, "SELECT id FROM %s;",tablename);

	  printf("\ntemp:%s\n", tmp);

	  int rt = 0;

	  if (dbuser != NULL) printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
	  //if (con == NULL) printf("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
	  rt = mysql_real_query(con, tmp, strlen(tmp));
	  if (rt)
	  {
		  printf("Error making query: %s !!!\n", mysql_error(con));

		  mysql_close(con);
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
			  (*id) = row[t];
		  }
		  printf(".............\n");
		  count++;
	  }
	  printf("number of rows %d\n", count);

	  if (count==0) {
		  (*id) = "0";
	  }

	  if (whetherReleaseCon) {
		    printf("mysql_free_result...\n");
		    mysql_free_result(res);
			mysql_close(con);

	  }
	  return true;

  }







  ///////////////////////////////////////////////////////////

  //int rt;//return value
  //con = mysql_init((MYSQL*)0);


  //if (con != NULL && mysql_real_connect(con, dbip, dbuser, dbpasswd, dbname, 3306/*TCP IP端口*/, NULL/*Unix Socket 连接类型*/, 0/*运行成ODBC数据库标志*/))
  //{
  /*
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
  MessageBoxA(NULL, "Unable to connect the database,check your configuration!", "", NULL);
  return false;
  }

  */

  /////////////////////////////////////////////////////////
  // std::string return_value;















//	sprintf_s(tmp, "select * from %s", tablename);  //add a mysql order to tem[]array;
//
//	rt = mysql_real_query(con, tmp, strlen(tmp));
//	if (rt)
//	{
//		printf("Error making query: %s !!!\n", mysql_error(con));
//	}
//
//	else
//	{
//		printf("%s executed!!!\n", tmp);
//	}
//
//
//	// important;
//	res = mysql_store_result(con);//将结果保存在res结构体中
//
//
//
//
//
//
//
//								  /////////////////////////////////////////////////////////////
//
//	while (row = mysql_fetch_row(res))
//	{
//		/**
//		*        MYSQL_ROW STDCALL   mysql_fetch_row(MYSQL_RES *result);
//		* 检索行
//		*/
//
//		for (t = 0; t<mysql_num_fields(res); t++)
//		{
//			printf("%s  ", row[t]);
//		}
//		printf(".............\n");
//		count++;
//	}
//	printf("number of rows %d\n", count);
//	printf("mysql_free_result...\n");
//
//	mysql_free_result(res);
//	mysql_close(con);
//
//	getchar();
//	return 0;
//}




























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
		printf("Error making query: %s !!!\n", mysql_error(con));

		mysql_close(con);
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
		
		printf(".............\n");
		count++;
	}
	printf("number of rows %d\n", count);


	printf("mysql_free_result...\n");
	mysql_free_result(res);


	mysql_close(con);
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
		printf("Error making query: %s !!!\n", mysql_error(con));

		mysql_close(con);
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

			if (row[1] == "1") {
				printf("I will delete the data that its id equal %s",row[0]);
				theRowHadRead[count] = row[0];
			        
			}
	
		//(*theRowHadRead)[count] = row;

		printf(".............\n");
		count++;
	}
	printf("number of rows %d\n", count);

	printf("mysql_free_result...\n");
	mysql_free_result(res);


	//mysql_close(con);
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
		printf("Error making query: %s !!!\n", mysql_error(con));

		mysql_close(con);
		return false;
	}
	else
	{
		printf("%s executed!!!\n", tmp);
	}

	//res = mysql_store_result(con);//将结果保存在res结构体中


	//printf("mysql_free_result...\n");
	//mysql_free_result(res);


	//mysql_close(con);
	return true;

}


void mysql::closeMysqlCon()
{

	mysql_close(con);



}










