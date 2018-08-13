
#pragma once

#if defined(_WIN32)
#include <windows.h>
#include "winsock.h" 
#include "include\mysql.h"
#pragma comment(lib,"libmySQL.lib") 
#pragma warning(disable:4996)
#else

#include <mysql/mysql.h>

#endif


#include<zxc_net/Logger.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <time.h>
#include <string.h>

class mysql {

public:
	bool	IniteMysqlAndConnected();
	bool    SaveJsonData2Mysql(std::string * strJsonData, std::string id);
//	bool    GetIdDataFromMysql(std::string * openid_data);
	bool    GetIdOrDataFromMysql(std::string column_name,std::string * openid_data);

	//overload function GetIdOrDataFromMysql()
	bool    GetIdOrDataFromMysql(std::string column_name, std::string * openid_data, bool whetherReleaseCon);


	//void    PrintTable2Screen(void);

	///////////此处我没有关闭MySQL的con///////////////////////////////////
	bool    GetIdFromMysql(std::string*  id, bool whetherReleaseCon);


	/////////////////////////commonGetDataFromMysql///////////////////////
	bool  commonGetDataFromMysql(std::string inputString, std::string * theRowHadRead);
	bool  commonOrderMysql(std::string inputString);

	bool  deleteFinishEqual1DataFromMysql(std::string inputString, std::string * theRowHadRead);


		void closeMysqlCon();

		std::string   return_tablename_mysql() {
			std::string temp = tablename;
			return temp;
		}

private:
		char dbuser[30] = "debian-sys-maint";
		char dbpasswd[30] = "RY7G5mfX3Nt2U4Bt";
		char dbip[30] = "localhost";
		char dbname[50] = "save_little_program";
		char tablename[50] = "test_9020";
		char *query = NULL;
		MYSQL * con; //= mysql_init((MYSQL*) 0); 
		MYSQL_RES *res;
		MYSQL_ROW  row;

};

