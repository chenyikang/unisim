#include "student_info.h"

using std::endl; using std::setw; using std::setfill; using std::cout; using std::ostream;


extern map<string, common> students;
extern map<string, common> del_students;
extern map<string, double> config;

ostream& show_student(ostream& out, const common student)
{
	out << student.name();
	out << '\t'<< student.sex();
	out << '\t' << setw(2) << setfill('0') << student.floor_num() << "-";
	out << setw(2) << setfill('0') << student.room_num();
	out << '\t' << student.charm();
	out << '\t' << student.weight();
	out << '\t' << student.money();
	out << '\t' << student.knowledge();
	out << '\t' << student.islove();
	
	vector<string> lover = student.lover();
	for (auto i = lover.begin(); i != lover.end(); i++)
	{
		out << '\t' << *i << " ";
	}
	out << endl;

	return out;
}

ostream& show_dorm(ostream& out, vector<floor_info>& dorm)
{
	string temp;		//����������ʱ�洢�ַ�����temp												
	for (vector<floor_info>::size_type i = 1; i != dorm.size(); i++)
	{
		for (vector<room_info>::size_type j = 1; j != dorm[i].size(); j++)
		{
			vector<string> illegal_student;					//�����洢һ�������ﲻ���Ա�ķǷ�ѧ������
			dorm[i][j].reserve(config["CAPACITY"]);
			for(vector<string>::size_type k = 0; k != dorm[i][j].size(); k++)
			{	
				if (k == 0)									//��Ϊ������ĵ�һ��ѧ��ʱ����¥����������ţ��Ա���ʾ����
				{
					out << "¥����:" << setw(2) << setfill('0') << students[dorm[i][j][k]].floor_num() << endl;
					out << "�����:" << setw(2) << setfill('0') << students[dorm[i][j][k]].room_num() << endl;
					out << "�Ա�:" << students[dorm[i][j][k]].sex() << endl;
					temp = students[dorm[i][j][k]].sex();		//��һ��ѧ�����Ա�����Ϊ�÷���涨���Ա�
				}
				if (students[dorm[i][j][k]].sex() != temp)	//���������ѧ����÷���ǰ��ѧ�����Ա𲻷���ʱ����������ɾ�������洢��illegal_student��
				{
					illegal_student.push_back(dorm[i][j][k]);
					dorm[i][j].erase(dorm[i][j].begin() + k);
					k--;									//����erase�ᵼ��k+1������Ҫ��һ
				}
				else
				{
					out << dorm[i][j][k] << " ";			//�Ϸ��Ա�ѧ������������ʾ
				}
				if (k == dorm[i][j].size() - 1)				//���������һ��ѧ��ʱ��������з�
				{
					out << endl;
				}
			}
			for (auto t = illegal_student.begin(); t != illegal_student.end(); t++)	//�Ѹ÷����еĲ��Ϸ��Ա�ѧ����ʾ����
			{
				out << (*t) << "�����ϸ÷����Ա�����������ɾ��" << endl;
			}
		}
	}
	return out;
}

ostream& show_students(ostream& out)
{
	for (auto map_it = students.begin(); map_it != students.end(); map_it++)
	{
		show_student(out, map_it->second);
	}

	out << "del_students" << endl;

	for (auto map_it = del_students.begin(); map_it != del_students.end(); map_it++)
	{
		show_student(out, map_it->second);
	}

	return out;
}