#include"student_info.h"

using std::cout; using std::endl; using std::istringstream;

extern map<string, common> students;
extern map<string, common> del_students;
extern map<string, double> config;
extern map<string, string> formula;
extern map<string, map<string, int>> students_woo_times;

/*
函数:state（）
功能:根据学生进行的eat/work/study改变学生的状态，也可进行quit操作。
*/
void state(vector<string>& instructions)
{
	string name = instructions[0];									//获取指令的对象学生名字
	double food_taken, study_time, work_time;						
	food_taken = study_time = work_time = 0;				
	int del_flag = 0;												//记录此学生是否要退学
	for (auto i = 1; i < instructions.size(); i+=2)					//获取eat/study/work的数量值
	{
		if (instructions[i] != "QUIT")
		{
			if (instructions[i] == "EAT")
			{
				food_taken += atof(instructions[i + 1].c_str());
			}
			else if(instructions[i] == "STUDY")
			{
				study_time += atof(instructions[i + 1].c_str());
			}
			else if (instructions[i] == "WORK")
			{
				work_time += atof(instructions[i + 1].c_str());
			}
		}
		else														//此学生退学，标记
		{
			del_flag = 1;
		}
	}
	if (!students[name].expression(food_taken, study_time, work_time))
	{
		cout << "EAT/WORK/STUDY无效指令" << endl;					//如果状态改变超过合法范围，则为无效指令
	}
	if (del_flag == 1)												//如果学生标记退学，则将其从学生总体容器中删除，并存入退学学生总体容器
	{
		del_students[name] = students[name];
		students.erase(name);
	}
}

/*
函数:move（）
功能:将学生从一个宿舍搬到另一个宿舍。
*/
void move(vector<floor_info>& dorm, vector<string>&instructions)
{
	string name = instructions[0];									//获取指令对象学生名字
	string from = instructions[2];									//获取对象学生宿舍from
	string to = instructions[3];									//获取对象学生宿舍to
	
	int from_fnum, from_rnum, to_fnum, to_rnum;
	read_room(from, from_fnum, from_rnum);							//将宿舍号字符串转化为int数字
	read_room(to, to_fnum, to_rnum);								//将宿舍号字符串转化为int数字	
	
	//判断指令中from的宿舍号是否正确，不正确则视为无效指令
	if (students[name].floor_num() == from_fnum && students[name].room_num() == from_rnum)
	{
		//判断所要转的to宿舍号是否还有床位，满床则视为无效指令
		if (dorm[to_fnum][to_rnum].size() < dorm[to_fnum][to_rnum].capacity())
		{
			dorm[to_fnum][to_rnum].push_back(name);					//将学生名字存进宿舍结构
			students[name].stu_floor_num = to_fnum;						//并更新学生个人信息的宿舍号
			students[name].stu_room_num = to_rnum;
			auto i = dorm[from_fnum][from_rnum].begin();
			while (i != dorm[from_fnum][from_rnum].end())			//删除学生原宿舍结构中的名字
			{
				if (*i == name)
				{
					i = dorm[from_fnum][from_rnum].erase(i);
				}
				else
					++i;
			}
		}
		else
			cout << "目标宿舍房间已满，无效指令" << endl;
	}
	else
	{
		cout << "错误宿舍信息，无效指令" << endl;
	}
}

/*
函数:read_room（）
功能:将xx-xx宿舍号字符串提取出int型的楼层，房间号。
*/
void read_room(string room, int& fnum, int& rnum)
{
	istringstream record(room);
	string temp;

	getline(record, temp, '-');
	record >> rnum;
	fnum = atoi(temp.c_str());
}

/*
函数:enrol（）
功能:学生第一次入学，如果此学生不是第一次入学（之前退学的），保持其在退学前的状态。
*/
void enrol(vector<floor_info>& dorm, vector<string>& instructions)
{
	string name = instructions[0];									//获取指令中学生对象名字
	string sex = instructions[1];									//获取指令中学生对象性别
	string to = instructions[3];									//获取指令中学生对象入住宿舍
	int fnum, rnum;
	read_room(to, fnum, rnum);										//将xx-xx宿舍号转化为int数字
	//判断目标宿舍是否有床位，满床则无效指令
	if (dorm[fnum][rnum].size() < dorm[fnum][rnum].capacity())
	{
			//判断此学生是否是退学学生，是则赋值之前退学时候的状态，否则则进行初始化
			if (del_students.find(name) != del_students.end())
			{
				dorm[fnum][rnum].push_back(name);

				students[name] = del_students[name];
				students[name].stu_sex = sex;
				students[name].stu_floor_num = fnum;
				students[name].stu_room_num = rnum;

				del_students.erase(name);
			}
			else
			{
				dorm[fnum][rnum].push_back(name);

				students[name].stu_name = name;
				students[name].stu_sex = sex;
				students[name].stu_floor_num = fnum;
				students[name].stu_room_num = rnum;

				students[name].stu_charm = config["CHARM"];
				students[name].stu_weight = config["WEIGHT"];
				students[name].stu_money = config["MONEY"];
				students[name].stu_knowledge = config["KNOWLEDGE"];
			}
	}
	else
		cout << "目标宿舍房间已满，无效指令" << endl;
}

/*
函数:woo（）
功能:两个学生建立恋爱关系。
*/
void woo(vector<string>& instructions)
{
	string stu1_name = instructions[0];										//从指令中获取学生一姓名
	string stu2_name = instructions[2];										//从指令中获取学生二姓名

	common stu1;
	common stu2;

	if (students.find(stu1_name) != students.end())							//从容器中获取学生一信息
		stu1 = students[stu1_name];
	else if(del_students.find(stu1_name) != del_students.end())
		stu1 = del_students[stu1_name];

	if (students.find(stu2_name) != students.end())							//从容器中获取学生二信息
		stu2 = students[stu2_name];
	else if (del_students.find(stu2_name) != del_students.end())
		stu2 = del_students[stu2_name];

	double stu1_charm = stu1.charm();							//获取学生一魅力值
	double stu2_charm = stu2.charm();							//获取学生二魅力值
	double charm_diff;										//魅力差值

	//学生一，二需都是单身状态，否则无效指令
	if (stu1.islove() == 0 && stu2.islove() == 0)
	{
		if (stu1_charm >= stu2_charm)
		{
			charm_diff = (stu1_charm - stu2_charm) / (stu1_charm);
		}
		else
		{
			charm_diff = (stu2_charm - stu1_charm) / (stu2_charm);
		}
		//学生一，二之间的魅力差值需要小于阈值，否则无效指令
		if (charm_diff <= config["LOVE_STANDARD"])
		{
			stu1.stu_islove = 1;									//改变学生一，二恋爱状态
			stu2.stu_islove = 1;
			stu1.stu_lover.push_back(stu2_name);					//将学生一，二分别存入对方恋爱史容器
			stu2.stu_lover.push_back(stu1_name);
		}
		else
			cout << "两人魅力值相差过大，无效指令" << endl;
	}
	//如果学生一是要撬学生二墙角的话
	else if (stu1.islove() == 0 && stu2.islove() == 1)
	{
		double stu3_charm;
		string stu3_name = stu2.lover()[stu2.lover().size() - 1];					//得到学生二的恋人名字

		if (students.find(stu3_name) != students.end())							//从容器中获取学生二的恋人学生三魅力值
			stu3_charm = students[stu3_name].charm();
		else if (del_students.find(stu3_name) != del_students.end())
			stu3_charm = del_students[stu3_name].charm();

		if (stu1_charm > stu3_charm)								//学生一魅力值要比学生三大
		{
			charm_diff = (stu1_charm - stu3_charm) / (stu1_charm);	//计算相对魅力值差
		}
		else														//小的话，直接撬失败
		{
			cout << "魅力值过低，撬墙角失败，无效指令" << endl;
			return;
		}

		if (charm_diff >= config["LOVE_RECONSTUCT_STANDARD"])		//魅力差值大于配置阈值，则可以撬
		{
			//学生一之前有撬过学生二
			if (students_woo_times[stu2_name].find(stu1_name) != students_woo_times[stu2_name].end())
			{
				if (students_woo_times[stu2_name][stu1_name] == 3)	//撬到第3次就成功
				{
					vector<string> ins;
					ins[0] = stu2_name;
					ins[1] = stu2.lover()[stu2.lover().size() - 1];
					breakup(ins);									//先让原先的分手
					woo(instructions);								//再在一起
					return;
				}
				else
				{
					students_woo_times[stu2_name][stu1_name]++;		//不够3次，就++
					cout << "毅力不够，撬不动" << endl;
				}
			}
			//之前没撬过，就初始化为撬次数为1
			else
			{
				students_woo_times[stu2_name][stu1_name] = 1;
				cout << "毅力不够，撬不动" << endl;
			}
		}
		else														//小于配置阈值，则撬失败
		{
			cout << "魅力值过低，撬墙角失败，无效指令" << endl;
			return;
		}
	}
	else
		cout << "两学生不都是单身状态，无效指令" << endl;

	if (students.find(stu1_name) != students.end())				//存储改变后的学生一信息
		students[stu1_name] = stu1;
	else if (del_students.find(stu1_name) != del_students.end())
		del_students[stu1_name] = stu1;

	if (students.find(stu2_name) != students.end())				//存储改变后的学生二信息
		students[stu2_name] = stu2;
	else if (del_students.find(stu2_name) != del_students.end())
		del_students[stu2_name] = stu2;
}

/*
函数:breakup（）
功能:两个学生分手。
*/
void breakup(vector<string>& instructions)
{
	string stu1_name = instructions[0];										//获取学生一名字
	string stu2_name = instructions[1];										//获取学生二名字
	
	common stu1;
	common stu2;

	if (students.find(stu1_name) != students.end())							//从容器中获取学生一信息
		stu1 = students[stu1_name];
	else if (del_students.find(stu1_name) != del_students.end())
		stu1 = del_students[stu1_name];

	if (students.find(stu2_name) != students.end())							//从容器中获取学生二信息
		stu2 = students[stu2_name];
	else if (del_students.find(stu2_name) != del_students.end())
		stu2 = del_students[stu2_name];

	//学生一，二得都是恋爱状态，否则无效指令
	if (stu1.islove() == 1 && stu2.islove() == 1)
	{
		string stu1_lover = stu1.lover()[stu1.lover().size() - 1];
		string stu2_lover = stu2.lover()[stu2.lover().size() - 1];

		//学生一，二的恋爱对象得是对方，否则无效指令
		if (stu1_lover == stu2_name && stu2_lover == stu1_name)
		{
			stu1.stu_islove = 0;									//改变学生一，二恋爱状态
			stu2.stu_islove = 0;
			students_woo_times.erase(stu1_name);
			students_woo_times.erase(stu2_name);
		}
		else
			cout << "两人不是恋人关系，无效指令" << endl;
	}
	else
		cout << "两人不是都是恋爱状态，无效指令" << endl;

	if (students.find(stu1_name) != students.end())				//存储改变后的学生一信息
		students[stu1_name] = stu1;
	else if (del_students.find(stu1_name) != del_students.end())
		del_students[stu1_name] = stu1;

	if (students.find(stu2_name) != students.end())				//存储改变后的学生二信息
		students[stu2_name] = stu2;
	else if (del_students.find(stu2_name) != del_students.end())
		del_students[stu2_name] = stu2;
}