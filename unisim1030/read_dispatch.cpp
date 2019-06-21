#include "student_info.h"

using std::istream;  using std::vector; using std::getline; using std::istringstream;
using std::cout;using std::endl;

extern map<string, common> students;
extern map<string, common> del_students;
extern map<string, double>config;

istream& read_dispatch(istream& is, vector<floor_info>& dorm)
{

	string line;								//�����洢һ�е��ַ���
	int del_flag=0;								//�ж��Ƿ�ʼ������ѧѧ��
	while (is && getline(is, line))
	{
		if (line == "del_students")				//һ������del_student��ǣ���del_flag��Ч��������һ��
		{
			del_flag = 1;
			continue;
		}	

		common student;					//һ����ѧ��

		istringstream record(line);				//��һ���ַ�����Ϊ�ַ�������

		student.read(record);					//��ȡѧ����Ϣ

		if (del_flag == 0)							//��del_flagΪ0��������ڶ�ѧ�������������ѧѧ��
		{
			students[student.name()] = student;		//����students����������
			dorm[student.floor_num()][student.room_num()].push_back(student.name());		//��ѧ���Ž����᷿���˳��������
		}	
		else
			del_students[student.name()] = student;

	}
	return is;
}

