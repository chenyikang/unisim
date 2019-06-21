#include"student_info.h"

using std::getline; using std::istringstream; using std::cout; using std::endl;

extern map<string, common>students;
extern map<string, common> del_students;
extern map<string, double> config;
extern map<string, string> formula;

int read_instruction(istream& is, vector<string>& instructions)
{
	string temp, tmp;														//用来暂时存储字符串
	string str_num;															//用来存储代表数字的字符串
	is >> temp;																//先读取第一个字符串
	
	//如果第一个字符串是ADD的话，则进入ADD指令的匹配
	if (temp == "ADD")
	{
		instructions.push_back(temp);										//将函数操作存进vector中
		is >> str_num >> temp;												//继续读后面的字符串进行判断
		if (atoi(str_num.c_str()) >= 1 && atoi(str_num.c_str()) < 99)		//数字得在1-99之间
		{
			if (temp == "FLOOR(s)" || temp == "FLOOR")						//匹配floor(s)
			{
				instructions.push_back(str_num);							//存进要add楼层的数量
				instructions.push_back(temp);								//存进"FLOOR"
				return 1;													//返回1，表示增加FLOOR
			}
			else if (temp == "ROOM(s)" || temp == "ROOM")					//匹配room(s)
			{
				instructions.push_back(str_num);							//存进要add房间的数量
				instructions.push_back(temp);								//存进"ROOM"
				is >> temp >> str_num >> tmp;
				if (temp == "TO" && tmp == "FLOOR")							//匹配TO FLOOR
				{
					instructions.push_back(str_num);						//存进所增加房间的楼层数
					instructions.push_back(tmp);							//存进"FLOOR"
					return 2;												//返回2，表示增加ROOM
				}
				else
				{
					return 0;												//返回0,表示无效指令
				}
			}
			else if (temp == "BED(s)" || temp == "BED")						//匹配room(s)
			{
				instructions.push_back(str_num);							//存进要add床位的数量
				instructions.push_back(temp);								//存进"BED"
				is >> tmp;
				if (tmp == "TO")											//匹配TO
				{
					is >> str_num;											
					instructions.push_back(str_num);						//存进所增加的房间号 XX-XX
					return 3;												//返回3，表示增加BED
				}
				else
				{
					return 0;												//返回0，表示无效指令
				}
			}
			else
			{
				return 0;													//返回0，表示无效指令
			}
		}
		else
		{
			return 0;														//返回0，表示无效指令
		}
	}

	//如果第一个字符串是在读学生中的姓名，则进入EAT WORK STUDY ENROL QUIT MOVE指令匹配
	else if (students.find(temp) != students.end())							
	{
		instructions.push_back(temp);										//存进要处理的学生名字
		is >> tmp;															//读取下一个字符串
		if (tmp == "EAT" || tmp == "STUDY" || tmp == "WORK")				//匹配EAT STUDY WORK
		{
			instructions.push_back(tmp);									//存进对应的函数操作
			is >> str_num;													//读取下一个代表数字的字符串
			if (atoi(str_num.c_str()) >= 1 && atoi(str_num.c_str()) <= 100)	//要求数字在1-100之间
				instructions.push_back(str_num);							
			if (getline(is, tmp))											//读取剩下的一行字符串
			{
				istringstream in(tmp);										//转化为字符串流
				while ((instructions.size() < 7) && (in >> temp))			//如果指令没超过3组且能读入的时候则继续读入指令
				{
					if (temp == "EAT" || temp == "STUDY" || temp == "WORK")
					{
						instructions.push_back(temp);
						in >> str_num;
						if (atoi(str_num.c_str()) >= 1 && atoi(str_num.c_str()) <= 100)
							instructions.push_back(str_num);
					}
					else if (temp == "QUIT")								//一旦读入QUIT指令，存进instructions中，然后退出函数
					{
						instructions.push_back(temp);
						return 4;											//返回4，表示操作EAT/WORK/STUDY/QUIT
					}
				}
				return 4;
			}
			else															//循环结束，返回4，表示操作EAT/WORK/STUDY/QUIT
				return 4;
		}
		else if (tmp == "QUIT")
		{
			instructions.push_back(tmp);
			return 4;														//返回4，表示操作EAT/WORK/STUDY/QUIT
		}
		else if (tmp == "MOVE")												//匹配MOVE指令
		{
			instructions.push_back(tmp);
			is >> tmp;
			if (tmp == "FROM")
			{
				is >> str_num;
				instructions.push_back(str_num);
				is >> tmp;
				if (tmp == "TO")
				{
					is >> str_num;
					instructions.push_back(str_num);
					return 5;												//返回5，表示操作MOVE
				}
				else
					return 0;												//返回0，表示无效指令
			}
			else
			{
				return 0;													//返回0，表示无效指令
			}
		}
		else if (tmp == "WOO")
		{
			instructions.push_back(tmp);
			is >> tmp;
			if (students.find(tmp) != students.end() || del_students.find(tmp) != del_students.end())		//求爱的对象也能找得到的话
			{
				instructions.push_back(tmp);
				return 7;									//返回7，表示操作WOO
			}
			else
			{
				return 0;									//找不到的话，返回0,无效指令
			}
		}
		else if (students.find(tmp) != students.end() || del_students.find(tmp) != del_students.end())		//第二个字符串是学生名字，则进入break up指令匹配
		{
			instructions.push_back(tmp);
			is >> tmp >> temp;
			if (tmp == "BREAK" && temp == "UP")				//匹配 break up 指令
			{
				instructions.push_back(tmp);
				instructions.push_back(temp);
				return 8;									//匹配成功，返回8, 表示操作BREAK UP
			}
			else
				return 0;									//匹配失败，返回0，无效指令
		}
		else												//其余情况都视为无效指令
		{
			return 0;
		}
	}

	//如果第一个字符串是退学学生集体中的姓名，则判断是否是WOO或者BREAK UP指令
	else if(del_students.find(temp) != del_students.end())
	{
		instructions.push_back(temp);						//存进要处理的学生名字
		is >> tmp;
		if (tmp == "WOO")																					//第二个字符串是WOO，则进入woo指令匹配
		{
			instructions.push_back(tmp);
			is >> tmp;
			if (students.find(tmp) != students.end() || del_students.find(tmp) != del_students.end())		//求爱的对象也能找得到的话
			{
				instructions.push_back(tmp);
				return 7;									//返回7，表示操作WOO
			}
			else
			{
				return 0;									//找不到的话，返回0,无效指令
			}
		}
		else if (students.find(tmp) != students.end() || del_students.find(tmp) != del_students.end())		//第二个字符串是学生名字，则进入break up指令匹配
		{
			instructions.push_back(tmp);
			is >> tmp >> temp;
			if (tmp == "BREAK" && temp == "UP")				//匹配 break up 指令
			{
				instructions.push_back(tmp);
				instructions.push_back(temp);
				return 8;									//匹配成功，返回8, 表示操作BREAK UP
			}
			else
				return 0;									//匹配失败，返回0，无效指令
		}
		else if(tmp == "男" || tmp == "女")																	//第二个字符串是性别，则进入enrol指令匹配
		{
			instructions.push_back(tmp);
			is >> temp;
			if (temp == "ENROL")
			{
				instructions.push_back(temp);
				is >> str_num;
				instructions.push_back(str_num);
				return 6;									//返回6，表示操作ENROL
			}
			else
			{
				return 0;
			}
		}
		else																								//其余情况都视为无效指令
		{
			return 0;
		}
	}

	//如果第一个字符串不是学生集体中的姓名，则判断是否是入学指令
	else
	{
		instructions.push_back(temp);
		is >> tmp;
		if (tmp == "男" || tmp == "女")
		{
			instructions.push_back(tmp);
			is >> temp;
			if (temp == "ENROL")
			{
				instructions.push_back(temp);
				is >> str_num;
				instructions.push_back(str_num);
				return 6;													//返回6，表示操作ENROL
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;														//返回0，表示无效指令
		}		
	}
}

istream& read_show_instructions(istream& is, vector<floor_info>& dorm)
{
	string line;

	while (getline(is, line) && is )										//取每一行进行处理
	{
		if (line.empty())													//忽略空行
			continue;
		else																//不为空行时
		{
			vector<string> instructions;									//指令顺序容器
			int ch;															//选择
			istringstream record(line);										//将一行字符串转化为字符串流处理
			ch = read_instruction(record, instructions);					//用read_instruction处理每一行
			switch (ch)
			{
			case 0:
				cout << "无效指令" << endl;
				break;
			case 1:															//输出 增加floor 的指令
				cout << "函数：" << instructions[0] << endl;
				cout << "对象：" << instructions[2] << endl;
				cout << "数量：" << instructions[1] << endl;
				add_floor(dorm, atoi(instructions[1].c_str()));
				break;
			case 2:															//输出 增加room 的指令
				cout << "函数：" << instructions[0] << endl;
				cout << "对象：" << instructions[2] << endl;
				cout << "位置：" << instructions[3] << " " << instructions[4] << endl;
				cout << "数量：" << instructions[1] << endl;
				add(dorm, atoi(instructions[1].c_str()), instructions[2], atoi(instructions[3].c_str()), instructions[4]);
				break;
			case 3:															//输出 增加bed 的指令
				cout << "函数：" << instructions[0] << endl;
				cout << "对象：" << instructions[2] << endl;
				cout << "位置：" << instructions[3] << endl;
				cout << "数量：" << instructions[1] << endl;
				add(dorm, atoi(instructions[1].c_str()), instructions[2], 0, instructions[3]);
				break;
			case 4:															//输出 study/work/eat/quit指令
				cout << "对象：" << instructions[0] << endl;
				for (auto i = 1; i != instructions.size(); i++)
				{
					if ((i % 2) == 1)
						cout << "函数：" << instructions[i] << endl;
					if ((i % 2) == 0)
						cout << "数量：" << instructions[i] << endl;
				}
				state(instructions);
				break;
			case 5:															//输出 move 指令
				cout << "对象：" << instructions[0] << endl;
				cout << "函数：" << instructions[1] << endl;
				cout << "从：" << instructions[2] << endl;
				cout << "到：" << instructions[3] << endl;
				move(dorm, instructions);
				break;
			case 6:															//输出退过学的 enrol 指令
				cout << "对象：" << instructions[0] << endl;
				cout << "性别：" << instructions[1] << endl;
				cout << "函数：" << instructions[2] << endl;
				cout << "位置：" << instructions[3] << endl;
				enrol(dorm, instructions);
				break;
			case 7:															//输出 woo 指令
				cout << "对象：" << instructions[0] << endl;
				cout << "函数：" << instructions[1] << endl;
				cout << "对象：" << instructions[2] << endl;
				woo(instructions);
				break;
			case 8:															//输出 break up 指令
				cout << "对象：" << instructions[0] << endl;
				cout << "函数：" << instructions[2] << " " << instructions[3] << endl;
				cout << "对象：" << instructions[1] << endl;
				breakup(instructions);
				break;
			}
			cout << endl;
		}
	}
	return is;
}