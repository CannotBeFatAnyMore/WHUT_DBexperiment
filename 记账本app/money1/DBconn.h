
#include <cstring>
#include <tchar.h>
#include <afx.h>


typedef struct RESULT {
	char fields[7][10];//是一个字符串数组 一共有7行 （7个字段） ，每个字段长为10个char
	char data[100][7][20]; //用一个三维数组存放结果集。 
	//第一个序号是代表字段
	int row;
	int column;
}RESULT;
class DBconn
{

public: 
	//吧char*类型转换为CString类型
	CString transfer(const char chArray[]);
	//测试数据库链接
	DBconn();
	//添加用户 返回0为成功 返回-1为失败
	int add_users( char username[], char password[]);
	//用户登录函数，成功登陆后会返回一个userid，作为用户身份识别依据，若失败则返回-1
	int login( char username[],  char password[]);
	//添加记录
	int add_record(int userid, int type,  char item_name[],  char classify[], char money[]);
	//删除记录
	int delete_record(char bill_id[]);
	//修改记录 传入的参数是 userid 和 账单id    
	int modify_record(int userid, int type, char item_name[], char classify[], char money[],char id[]);
	//无筛选条件查询
	//返回一个结构体  结构体有两个int类型成员，column row 如果两者为0 则发生错误 里面包含字段和数据。  数据用一个三维字符数组存放.
	RESULT check_record(int userid);
	//按进账出账查询 type=1 消费 type=-1 收钱
	RESULT check_record(int userid, int type);
	//按消费类型查询
	RESULT check_record(int userid,  char classify[]);
	//删除某个用户的所有账单信息
	int delete_all_record(int userid);
	//查询总共支出
	double spend_sum(int userid);
	double income_sum(int userid);
	//查询所有收入

	//账户销户 这将会导致所有该用户的账单记录被删除
	int delete_user(int userid);
	
	//备份数据库
	int back_upDB(int userid);
	//恢复数据库
	int recover_DB(int userid);

};

