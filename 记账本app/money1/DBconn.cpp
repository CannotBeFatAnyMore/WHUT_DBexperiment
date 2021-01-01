#define _CRT_SECURE_NO_WARNINGS
#include "DBconn.h"
#include <string>
#include<WinSock.h>
#include <mysql.h>
#include <afx.h> 
#include<iostream>
#include "global.h"
using namespace std;

DBconn::DBconn()
{
	static MYSQL my_connection; /*���ݿ�����*/
	int res; /*sqlִ�к󷵻ر�־*/
	MYSQL_RES* res_ptr; /*���ز�ѯ���ָ��*/
	MYSQL_FIELD* field; /*�ֶνṹָ��*/
	MYSQL_ROW result_row; /*���з��صĲ�ѯ��Ϣ*/
	mysql_init(&my_connection);	//��ʼ�����ݿ����� 

	int row, column; /*��ѯ���ص�����������*/
	/*��������*/
	if (NULL == mysql_real_connect(&my_connection, HOST, USERNAME, PASSWORD,
		DATABASE, 0, NULL, CLIENT_FOUND_ROWS)) {
		/*���Ӳ��ɹ�*/
		cout << "Connect to DB failed." << endl;
	}
	mysql_query(&my_connection, "set names gbk");//֧������ 
	mysql_close(&my_connection);

}
CString DBconn::transfer(const char chArray[]) {
	LPTSTR p = _T((char*)chArray);
	CString theString = chArray;
	theString.Format(_T("%s"), chArray);
	theString = p;
	return theString;
}
int DBconn::add_users( char username[], char password[])
{
	MYSQL my_connection; /*���ݿ�����*/
	int res; /*sqlִ�к󷵻ر�־*/
	mysql_init(&my_connection);	//��ʼ�����ݿ����� 
	mysql_real_connect(&my_connection, HOST, USERNAME, PASSWORD,
		DATABASE, 0, NULL, CLIENT_FOUND_ROWS);
	//ת�����ͣ������ʽ��
	CString usrname=transfer(username);
	CString pwd = transfer(password);
	CString sql ;
	sql.Format("call add_user('%s' ,'%s')",usrname,pwd );
	//��ѯMysql DB
	mysql_query(&my_connection, "set names gbk");//֧������ 
	int ret = mysql_query(&my_connection, sql);
	if (ret != 0)
	{
		printf("error:%s\n", mysql_error(&my_connection));
		return -1;
	}
	my_ulonglong affected_row = mysql_affected_rows(&my_connection);
	printf("%d rows affected.\n", (int)affected_row);
	mysql_close(&my_connection);
	return 0;
}

int DBconn::login( char username[],  char password[])
{
	MYSQL my_connection; /*���ݿ�����*/
	int res; /*sqlִ�к󷵻ر�־*/
	MYSQL_RES* res_ptr; /*���ز�ѯ���ָ��*/
	MYSQL_FIELD* field; /*�ֶνṹָ��*/
	MYSQL_ROW result_row; /*���з��صĲ�ѯ��Ϣ*/
	mysql_init(&my_connection);	//��ʼ�����ݿ����� 
	mysql_real_connect(&my_connection, HOST, USERNAME, PASSWORD,DATABASE, 0, NULL, CLIENT_FOUND_ROWS);	
	mysql_query(&my_connection, "set names gbk");//֧������ 
	CString usrname = transfer(username);
	CString pwd = transfer(password);
	CString sql;
	//���ɲ������	
	  //��֤�û�
	sql.Format("call user_login('%s','%s');", usrname, pwd);
	mysql_query(&my_connection, sql);
	res_ptr = mysql_store_result(&my_connection);
	if (res_ptr == NULL) {
		printf("error:%s\n", mysql_error(&my_connection));
		return -1;
	}
	
	char column[30][40];
	//5.ͳ�� table �ֶ�
	int numFields = mysql_num_fields(res_ptr);
	int numRows = mysql_num_rows(res_ptr);
	if (numRows == 0) {
		return -1;
	}
	//6.�����ֶ�
	for (int i = 0; i < numFields; ++i)
	{
		strcpy_s(column[i], 40 ,mysql_fetch_field(res_ptr)->name);
	}

	result_row = mysql_fetch_row(res_ptr);

	int userid = atoi(result_row[0]); //MYSQL_ROW ��char*����
	//cout << userid;
	//UID = userid;
	mysql_free_result(res_ptr);
	mysql_close(&my_connection);
	return userid;
}

int DBconn::add_record(int userid, int type, char item_name[],  char classify[], char money[])
{
	MYSQL my_connection; /*���ݿ�����*/
	MYSQL_RES* res_ptr; /*���ز�ѯ���ָ��*/
	MYSQL_FIELD* field; /*�ֶνṹָ��*/
	MYSQL_ROW result_row; /*���з��صĲ�ѯ��Ϣ*/
	mysql_init(&my_connection);	//��ʼ�����ݿ����� 
	mysql_real_connect(&my_connection, HOST, USERNAME, PASSWORD,
		DATABASE, 0, NULL, CLIENT_FOUND_ROWS);
	CString itemname=transfer(item_name);
	CString kind =transfer(classify);
	CString sql;	
	//add_item(IN Item_name char(10),IN userid int,IN class char(10),IN type int,IN money double)
	mysql_query(&my_connection, "set names gbk");//֧������ 
	sql.Format("call add_item('%s',%d,'%s',%d,%s);",itemname,userid,kind,type,money);
	cout << sql<<endl;

	int ret = mysql_query(&my_connection, sql);
	if (ret != 0)
	{
		printf("error:%s\n", mysql_error(&my_connection));
		return -1;
	}
	my_ulonglong affected_row = mysql_affected_rows(&my_connection);
	printf("%d rows affected.\n", (int)affected_row);
	mysql_close(&my_connection);
	return 0;
}

int DBconn::delete_record(char id[])
{
	MYSQL my_connection; /*���ݿ�����*/
	MYSQL_RES* res_ptr; /*���ز�ѯ���ָ��*/

	mysql_init(&my_connection);	//��ʼ�����ݿ����� 
	mysql_real_connect(&my_connection, HOST, USERNAME, PASSWORD,
		DATABASE, 0, NULL, CLIENT_FOUND_ROWS);
	CString sql;
	mysql_query(&my_connection, "set names gbk");//֧������ 
	sql.Format("call delete_item(%s);", id);
	int ret = mysql_query(&my_connection, sql);
	if (ret != 0)
	{
		printf("error:%s\n", mysql_error(&my_connection));
		return -1;
	}
	my_ulonglong affected_row = mysql_affected_rows(&my_connection);
	printf("%d rows affected.\n", (int)affected_row);
	mysql_close(&my_connection);
	return 0;
}

int DBconn::modify_record(int userid, int type, char item_name[], char classify[], char money[],char id[])
{
	MYSQL my_connection; /*���ݿ�����*/
	MYSQL_RES* res_ptr; /*���ز�ѯ���ָ��*/
	MYSQL_FIELD* field; /*�ֶνṹָ��*/
	MYSQL_ROW result_row; /*���з��صĲ�ѯ��Ϣ*/
	mysql_init(&my_connection);	//��ʼ�����ݿ����� 
	mysql_real_connect(&my_connection, HOST, USERNAME, PASSWORD,
		DATABASE, 0, NULL, CLIENT_FOUND_ROWS);
	CString itemname = transfer(item_name);
	CString kind = transfer(classify);
	CString sql;
	//modify_item(IN id int,IN Item_name char(10),IN userid int,IN class char(10),IN type int,IN money double)
	mysql_query(&my_connection, "set names gbk");//֧������ 
	sql.Format("UPDATE `billlist`.`spend_list` SET `ItemName` = '%s',`class`='%s', `Type` = '%d', `Money` = %s WHERE (`id` = %s);", itemname,  kind,type, money,id);
	int ret = mysql_query(&my_connection, sql);
	if (ret != 0)
	{
		printf("error:%s\n", mysql_error(&my_connection));
		return -1;
	}
	my_ulonglong affected_row = mysql_affected_rows(&my_connection);
	printf("%d rows affected.\n", (int)affected_row);
	mysql_close(&my_connection);
	return 0;
}

RESULT DBconn::check_record(int userid)
{	
	RESULT result_set;
	MYSQL my_connection; /*���ݿ�����*/
	MYSQL_RES* res_ptr; /*���ز�ѯ���ָ��*/
	MYSQL_FIELD* field; /*�ֶνṹָ��*/
	MYSQL_ROW result_row; /*���з��صĲ�ѯ��Ϣ*/
	mysql_init(&my_connection);	//��ʼ�����ݿ����� 
	mysql_real_connect(&my_connection, HOST, USERNAME, PASSWORD,
		DATABASE, 0, NULL, CLIENT_FOUND_ROWS);
	CString sql;
	mysql_query(&my_connection, "set names gbk");//֧������ 
	sql.Format("call query_bill(%d)",userid);
	int ret = mysql_query(&my_connection, sql);
	if (ret != 0)
	{
		printf("error:%s\n", mysql_error(&my_connection));
		result_set.column = 0;
		result_set.row = 0;
		return result_set;
	}
	res_ptr = mysql_store_result(&my_connection);

	int column_num = mysql_num_fields(res_ptr);
	result_set.column = column_num;
	int row_num = mysql_num_rows(res_ptr);
	result_set.row = row_num;

	for (int i = 0; i < column_num; i++) {
		 strcpy_s(result_set.fields[i],20,mysql_fetch_field(res_ptr)->name);
	}
	int row = 0;
	while ((result_row = mysql_fetch_row(res_ptr)) != NULL) {
		for (int j = 0; j < column_num; j++)
		{
			strcpy_s(result_set.data[row][j],20, result_row[j]);
		}
		row++;
		cout << endl;
	}

	my_ulonglong affected_row = mysql_affected_rows(&my_connection);
	mysql_close(&my_connection);
	return result_set;
}


int DBconn::delete_all_record(int userid)
{
	MYSQL my_connection; /*���ݿ�����*/
	mysql_init(&my_connection);	//��ʼ�����ݿ����� 
	mysql_real_connect(&my_connection, HOST, USERNAME, PASSWORD,
		DATABASE, 0, NULL, CLIENT_FOUND_ROWS);
	CString sql;
	mysql_query(&my_connection, "set names gbk");//֧������ 
	sql.Format("delete from spend_list where userid=%d;",userid);
	cout << sql << endl;
	int ret = mysql_query(&my_connection, sql);
	if (ret != 0)
	{
		printf("error:%s\n", mysql_error(&my_connection));
		return -1;
	}
	my_ulonglong affected_row = mysql_affected_rows(&my_connection);
	printf("%d rows affected.\n", (int)affected_row);
	mysql_close(&my_connection);
	return 0;
}

double DBconn::spend_sum(int userid)
{
	MYSQL my_connection; /*���ݿ�����*/
	int res; /*sqlִ�к󷵻ر�־*/
	MYSQL_RES* res_ptr; /*���ز�ѯ���ָ��*/
	MYSQL_FIELD* field; /*�ֶνṹָ��*/
	MYSQL_ROW result_row; /*���з��صĲ�ѯ��Ϣ*/
	mysql_init(&my_connection);	//��ʼ�����ݿ����� 
	mysql_real_connect(&my_connection, HOST, USERNAME, PASSWORD, DATABASE, 0, NULL, CLIENT_FOUND_ROWS);
	CString sql;
	//���ɲ������	
	  //��֤�û�
	sql.Format("call sum_spend('%d');", userid);
	mysql_query(&my_connection, sql);
	res_ptr = mysql_store_result(&my_connection);
	if (res_ptr == NULL) {
		printf("error:%s\n", mysql_error(&my_connection));
		return 0;
	}
	char column[30][40];
	int numRows = mysql_num_rows(res_ptr);
	result_row = mysql_fetch_row(res_ptr);
	if (result_row[0] == NULL) {
		return 0;
	}
	double sum = atof(result_row[0]); //MYSQL_ROW ��char*����
	mysql_free_result(res_ptr);
	mysql_close(&my_connection);
	return sum;
}

double DBconn::income_sum(int userid)
{
	MYSQL my_connection; /*���ݿ�����*/
	int res; /*sqlִ�к󷵻ر�־*/
	MYSQL_RES* res_ptr; /*���ز�ѯ���ָ��*/
	MYSQL_FIELD* field; /*�ֶνṹָ��*/
	MYSQL_ROW result_row; /*���з��صĲ�ѯ��Ϣ*/
	mysql_init(&my_connection);	//��ʼ�����ݿ����� 
	mysql_real_connect(&my_connection, HOST, USERNAME, PASSWORD, DATABASE, 0, NULL, CLIENT_FOUND_ROWS);
	CString sql;
	//���ɲ������	
	  //��֤�û�
	sql.Format("call income_sum('%d');", _USERID);
	mysql_query(&my_connection, sql);
	res_ptr = mysql_store_result(&my_connection);
	if (res_ptr == NULL) {
		printf("error:%s\n", mysql_error(&my_connection));
		return 0;
	}
	int numRows = mysql_num_rows(res_ptr);
	result_row = mysql_fetch_row(res_ptr);
	if (result_row[0] == NULL) {
		return 0;
	}
	double sum = atof(result_row[0]); //MYSQL_ROW ��char*����
	mysql_free_result(res_ptr);
	mysql_close(&my_connection);
	return sum;
}

int DBconn::delete_user(int userid)
{
	MYSQL my_connection; /*���ݿ�����*/
	int res; /*sqlִ�к󷵻ر�־*/
	mysql_init(&my_connection);	//��ʼ�����ݿ����� 
	mysql_real_connect(&my_connection, HOST, USERNAME, PASSWORD, DATABASE, 0, NULL, CLIENT_FOUND_ROWS);
	CString sql;
	//���ɲ������	
	  //��֤�û�
	sql.Format("call delete_user('%d');", _USERID);
	int ret=mysql_query(&my_connection, sql);
	if (ret != 0)
	{
		printf("error:%s\n", mysql_error(&my_connection));
		return -1;
	}
	mysql_close(&my_connection);
	return 0;
}

int DBconn::back_upDB(int userid)
{
	MYSQL my_connection; /*���ݿ�����*/
	int res; /*sqlִ�к󷵻ر�־*/
	mysql_init(&my_connection);	//��ʼ�����ݿ����� 
	mysql_real_connect(&my_connection, HOST, USERNAME, PASSWORD, DATABASE, 0, NULL, CLIENT_FOUND_ROWS);
	CString sql;
	//���ɲ������	
	  //��֤�û�
	sql.Format(
		"select * from spend_list where userid = %d into outfile 'C:/ProgramData/MySQL/MySQL Server 8.0/Uploads/User%d.csv';", userid, userid);
	int ret = mysql_query(&my_connection, sql);
	if (ret != 0)
	{
		printf("error:%s\n", mysql_error(&my_connection));
		return -1;
	}
	mysql_close(&my_connection);
	return 0;

}

int DBconn::recover_DB(int userid)
{
	MYSQL my_connection; /*���ݿ�����*/
	mysql_init(&my_connection);	//��ʼ�����ݿ����� 
	mysql_real_connect(&my_connection, HOST, USERNAME, PASSWORD, DATABASE, 0, NULL, CLIENT_FOUND_ROWS);
	CString sql;
	//���ɲ������	
	  //��֤�û�
	sql.Format("load data infile'C:/ProgramData/MySQL/MySQL Server 8.0/Uploads/User%d.csv' ignore into table spend_list; ", userid);
	int ret = mysql_query(&my_connection, sql);
	if (ret != 0)
	{
		printf("error:%s\n", mysql_error(&my_connection));
		return -1;
	}
	mysql_close(&my_connection);
	return 0;
}