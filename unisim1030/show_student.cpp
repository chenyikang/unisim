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
	string temp;		//定义用来暂时存储字符串的temp												
	for (vector<floor_info>::size_type i = 1; i != dorm.size(); i++)
	{
		for (vector<room_info>::size_type j = 1; j != dorm[i].size(); j++)
		{
			vector<string> illegal_student;					//用来存储一个房间里不合性别的非法学生名字
			dorm[i][j].reserve(config["CAPACITY"]);
			for(vector<string>::size_type k = 0; k != dorm[i][j].size(); k++)
			{	
				if (k == 0)									//当为房间里的第一个学生时，将楼层数，房间号，性别显示出来
				{
					out << "楼层数:" << setw(2) << setfill('0') << students[dorm[i][j][k]].floor_num() << endl;
					out << "房间号:" << setw(2) << setfill('0') << students[dorm[i][j][k]].room_num() << endl;
					out << "性别:" << students[dorm[i][j][k]].sex() << endl;
					temp = students[dorm[i][j][k]].sex();		//第一个学生的性别则作为该房间规定的性别
				}
				if (students[dorm[i][j][k]].sex() != temp)	//当房间里的学生与该房间前面学生的性别不符合时，从宿舍中删除，并存储到illegal_student中
				{
					illegal_student.push_back(dorm[i][j][k]);
					dorm[i][j].erase(dorm[i][j].begin() + k);
					k--;									//由于erase会导致k+1，所以要减一
				}
				else
				{
					out << dorm[i][j][k] << " ";			//合法性别学生则进行输出显示
				}
				if (k == dorm[i][j].size() - 1)				//房间里最后一个学生时，输出换行符
				{
					out << endl;
				}
			}
			for (auto t = illegal_student.begin(); t != illegal_student.end(); t++)	//把该房间中的不合法性别学生显示出来
			{
				out << (*t) << "不符合该房间性别，已在宿舍中删除" << endl;
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