#include"student_info.h"

using std::cout; using std::endl; using std::istringstream; using std::getline;

//����¥�㺯��
void add_floor(vector<floor_info>& dorm, int num)	
{
	if (dorm.size() + num > 99)
	{
		dorm.resize(100);
		cout << "¥�������Ϊ99��/�䣬������99��" << endl;
	}
	else
	{
		dorm.resize(dorm.size() + num);
		cout << "¥����������" << dorm.size()-1 << "��"<< endl;
	}
}

//���ӷ��䣬��λ����
void add(vector<floor_info>& dorm, int num1, string item1, int num2, string item2)
{
	if (item1 == "ROOM(s)" && item2 == "FLOOR")
	{
		if (dorm[num2].size() + num1 > 100)
		{
			dorm[num2].resize(100);
			cout << num2 << "¥��ķ��������Ϊ99�䣬������99��" << endl;

		}
		else
		{
			dorm[num2].resize(dorm[num2].size() + num1);
			cout << num2 << "¥��ķ�����������" << dorm[num2].size()-1 << "��" << endl;
		}
	}
	else if(item1 == "BED(s)")
	{
		int fnum, rnum;
		read_room(item2, fnum, rnum);

		if (fnum <= dorm.size() && rnum <= dorm[fnum].size())
		{
			dorm[fnum][rnum].reserve(dorm[fnum][rnum].capacity() + num1);
			cout << fnum << "-" << rnum << "����Ĵ�λ������" << dorm[fnum][rnum].capacity() << "��" <<endl;
		}
		else
		{
			cout << "����ָ��" << endl;
		}
	}
	else
	{
		cout << "����ָ��" << endl;
	}
}