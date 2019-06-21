#include "student_info.h"

using std::istream;  using std::vector; using std::getline; using std::istringstream;
using std::cout;using std::endl;

extern map<string, common> students;
extern map<string, common> del_students;
extern map<string, double>config;

istream& read_dispatch(istream& is, vector<floor_info>& dorm)
{

	string line;								//用来存储一行的字符串
	int del_flag=0;								//判断是否开始读入退学学生
	while (is && getline(is, line))
	{
		if (line == "del_students")				//一旦读到del_student标记，则del_flag生效，跳到下一行
		{
			del_flag = 1;
			continue;
		}	

		common student;					//一个新学生

		istringstream record(line);				//将一行字符串作为字符流处理

		student.read(record);					//读取学生信息

		if (del_flag == 0)							//当del_flag为0，则存入在读学生，否则存入退学学生
		{
			students[student.name()] = student;		//读进students关联容器中
			dorm[student.floor_num()][student.room_num()].push_back(student.name());		//将学生放进宿舍房间的顺序容器中
		}	
		else
			del_students[student.name()] = student;

	}
	return is;
}

