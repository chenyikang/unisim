#include<iostream>
#include<fstream>
#include "student_info.h"
#include "menu.h"

using std::cout; using std::endl; using std::ifstream; using std::setw; using std::setfill; using std::cerr;
using std::ofstream;

map<string, double> config;							//�洢������Ϣ�Ĺ����������ؼ��֣��������� ֵ������ֵ��
map<string, string> formula;						//�洢���ù�ʽ�Ĺ����������ؼ��֣����ù�ʽ���� ֵ�����ù�ʽ��
map<string, common> students;					//�洢�ڶ�ѧ����Ϣ�Ĺ����������ؼ��֣�ѧ������ ֵ��ѧ����Ϣ�ṹ��
map<string, common> del_students;				//�洢��ѧѧ����Ϣ�Ĺ����������ؼ��֣�ѧ������ ֵ��ѧ����Ϣ�ṹ��
map<string, map<string, int>> students_woo_times;	//�洢������ѧ�����󰮵Ĵ����Ĺ����������ؼ��֣�ѧ������ ֵ�����󰮴�����

int main()
{

	cout << "*------------------------Welcome to Unisim.--------------------------*" << endl;
	/*------------------------��ʼ������----------------------------------*/	
	ifstream in;
	ofstream out;
	string file;
	vector<string> instructions;						//�洢ָ���˳������
	/*------------------------��ȡ������Ϣ�ļ�----------------------------*/
	cout << "*------------------------��ȡ������Ϣ�ļ�----------------------------*" << endl;
	cout << "��ʼ��ȡ�����ļ���Ϣ" << endl;
	in.open("sample_config.txt");
	if (in)
	{
		read_config(in);				//��ȡ���ú���
		cout << "��ȡ�ɹ�" << endl;
	}
	else
	{
		cerr << "�������ļ�ʧ��" << endl;
	}
	in.close();

	show_config(config, formula);						//��ʾ���ú���
	/*------------------------��ȡ������Ϣ�ļ�����ʼ��----------------------------*/
	cout << "*------------------------��ȡ������Ϣ�ļ�����ʼ��--------------------*" << endl;

	vector<floor_info> dorm(config["FLOOR"]+1, floor_info(config["ROOM"]+1));

	cout << "��ʼ��ȡ����������Ϣ" << endl;
	in.open("dispatch.txt");
	if (in)
	{
		read_dispatch(in, dorm);				//��ȡ���ắ��
		cout << "��ȡ�ɹ�" << endl;
	}
	else
	{
		cerr << "�����������ļ�ʧ��" << endl;
	}
	in.close();

	show_dorm(cout, dorm);							//��ʾ���ắ��


	/*------------------------��ȡָ����Ϣ�ļ���ִ��----------------------------*/
	cout << "*------------------------��ȡָ����Ϣ�ļ�����ʾ----------------------*" << endl;
	cout << "��ʼ��ȡָ����Ϣ" << endl;
	open:
	cout << "������Ҫ��ȡ��ָ���ļ���" ;
	cin >> file;
	in.open(file);
	if (in)
	{
		read_show_instructions(in, dorm);				//��ȡ����ʾָ���
		cout << "��ȡ�ɹ�" << endl;
	}
	else
	{
		cerr << "��ָ���ļ�ʧ��" << endl;
		goto open;
	}
	in.close();

	/*------------------------����ѧ����Ϣ�ļ�----------------------------*/
	cout << "*------------------------����ѧ����Ϣ�ļ�----------------------------*" << endl;

	out.open(formula["SAVE_FILE_NAME"]);
	if (out)
	{
		show_students(out);
		cout << "����ɹ�" << endl;
	}
	else
	{
		cerr << "���ļ�ʧ��" << endl;
	}
	out.close();

	/*------------------------չʾ��ѯϵͳ����----------------------------*/
	
	display_menu();
}