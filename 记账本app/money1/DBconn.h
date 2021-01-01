
#include <cstring>
#include <tchar.h>
#include <afx.h>


typedef struct RESULT {
	char fields[7][10];//��һ���ַ������� һ����7�� ��7���ֶΣ� ��ÿ���ֶγ�Ϊ10��char
	char data[100][7][20]; //��һ����ά�����Ž������ 
	//��һ������Ǵ����ֶ�
	int row;
	int column;
}RESULT;
class DBconn
{

public: 
	//��char*����ת��ΪCString����
	CString transfer(const char chArray[]);
	//�������ݿ�����
	DBconn();
	//����û� ����0Ϊ�ɹ� ����-1Ϊʧ��
	int add_users( char username[], char password[]);
	//�û���¼�������ɹ���½��᷵��һ��userid����Ϊ�û����ʶ�����ݣ���ʧ���򷵻�-1
	int login( char username[],  char password[]);
	//��Ӽ�¼
	int add_record(int userid, int type,  char item_name[],  char classify[], char money[]);
	//ɾ����¼
	int delete_record(char bill_id[]);
	//�޸ļ�¼ ����Ĳ����� userid �� �˵�id    
	int modify_record(int userid, int type, char item_name[], char classify[], char money[],char id[]);
	//��ɸѡ������ѯ
	//����һ���ṹ��  �ṹ��������int���ͳ�Ա��column row �������Ϊ0 �������� ��������ֶκ����ݡ�  ������һ����ά�ַ�������.
	RESULT check_record(int userid);
	//�����˳��˲�ѯ type=1 ���� type=-1 ��Ǯ
	RESULT check_record(int userid, int type);
	//���������Ͳ�ѯ
	RESULT check_record(int userid,  char classify[]);
	//ɾ��ĳ���û��������˵���Ϣ
	int delete_all_record(int userid);
	//��ѯ�ܹ�֧��
	double spend_sum(int userid);
	double income_sum(int userid);
	//��ѯ��������

	//�˻����� �⽫�ᵼ�����и��û����˵���¼��ɾ��
	int delete_user(int userid);
	
	//�������ݿ�
	int back_upDB(int userid);
	//�ָ����ݿ�
	int recover_DB(int userid);

};

