#include"DBconn.h"
#include"global.h"

int _USERID = 0;
 int LOGIN(char usrname[], char pwd[]){
	DBconn conn;
	_USERID=conn.login(usrname, pwd);
	return _USERID;
}