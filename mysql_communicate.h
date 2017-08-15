#pragma once
#include "include\mysql.h"

class mysql {



public:
	bool	IniteMysqlAndConnected();
	bool  mysql::SaveJsonData2Mysql(std::string * strJsonData, std::string id);
//	bool    mysql::GetIdDataFromMysql(std::string * openid_data);
	bool    mysql::GetIdOrDataFromMysql(std::string column_name,std::string * openid_data);

	//void    PrintTable2Screen(void);

	///////////此处我没有关闭MySQL的con///////////////////////////////////
	bool  mysql::GetIdFromMysql(std::string*  id, bool whetherReleaseCon);


	/////////////////////////commonGetDataFromMysql///////////////////////
	bool  mysql::commonGetDataFromMysql(std::string inputString, std::string * theRowHadRead);
	bool  mysql::commonOrderMysql(std::string inputString);

	bool  mysql::deleteFinishEqual1DataFromMysql(std::string inputString, std::string * theRowHadRead);


	void mysql::closeMysqlCon();
	std::string return_tablename_mysql() {
		std::string temp = tablename;
		return temp;
	}
private:
	char dbuser[30] = "root";
	char dbpasswd[30] = "111122";
	char dbip[30] = "localhost";
	char dbname[50] = "save_little_program";
	char tablename[50] = "test";
	char *query = NULL;
	MYSQL * con; //= mysql_init((MYSQL*) 0); 
	MYSQL_RES *res;
	MYSQL_ROW row;

};

