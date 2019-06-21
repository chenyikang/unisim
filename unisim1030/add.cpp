#include"student_info.h"

using std::cout; using std::endl; using std::istringstream; using std::getline;

//增加楼层函数
void add_floor(vector<floor_info>& dorm, int num)	
{
	if (dorm.size() + num > 99)
	{
		dorm.resize(100);
		cout << "楼层数最多为99层/间，已增至99层" << endl;
	}
	else
	{
		dorm.resize(dorm.size() + num);
		cout << "楼层数已增至" << dorm.size()-1 << "层"<< endl;
	}
}

//增加房间，床位函数
void add(vector<floor_info>& dorm, int num1, string item1, int num2, string item2)
{
	if (item1 == "ROOM(s)" && item2 == "FLOOR")
	{
		if (dorm[num2].size() + num1 > 100)
		{
			dorm[num2].resize(100);
			cout << num2 << "楼层的房间数最多为99间，已增至99间" << endl;

		}
		else
		{
			dorm[num2].resize(dorm[num2].size() + num1);
			cout << num2 << "楼层的房间数已增至" << dorm[num2].size()-1 << "间" << endl;
		}
	}
	else if(item1 == "BED(s)")
	{
		int fnum, rnum;
		read_room(item2, fnum, rnum);

		if (fnum <= dorm.size() && rnum <= dorm[fnum].size())
		{
			dorm[fnum][rnum].reserve(dorm[fnum][rnum].capacity() + num1);
			cout << fnum << "-" << rnum << "房间的床位已增至" << dorm[fnum][rnum].capacity() << "床" <<endl;
		}
		else
		{
			cout << "错误指令" << endl;
		}
	}
	else
	{
		cout << "错误指令" << endl;
	}
}