#include"query.h"

extern map<string, common> students;
extern map<string, common> del_students;

/*
函数:show_data（）
功能:输出查询后的学生信息。
*/
void show_data(const vector<string>& stu, ostream& out)
{
	out << "\n----------------------------------------------------------\n";
	out << "姓名"<< '\t' << "性别" << '\t' << "魅力" << '\t' << "金钱" << '\t' << "知识" << '\t' << "体重";
	out << "\n----------------------------------------------------------\n";
	for (auto i = stu.begin(); i != stu.end(); i++)
	{
		out << std::left << setw(4) << *i
			<< '\t' << students[*i].sex()
			<< '\t' << students[*i].charm()
			<< '\t' << students[*i].money()
			<< '\t' << students[*i].knowledge()
			<< '\t' << students[*i].weight()
			<<endl;
	}
	out << "----------------------------------------------------------\n";
}


/*
函数:query_dorm（）
功能:查询学生住哪个宿舍。
*/
void query_dorm(ostream& out)
{
	string stu_name;
	cout << "\t请输入要查询宿舍的学生姓名：";
	cin >> stu_name;
	out << "\n----------------------------------------------------------\n";
	if (students.find(stu_name) != students.end())							//在在读学生中找，找到输出其宿舍信息
	{
		out << stu_name << "的房间号:" << students[stu_name].floor_num() << '-' << students[stu_name].room_num() << endl;
	}
	else if (del_students.find(stu_name) != del_students.end())				//在退学学生中找，找到输出其宿舍信息
	{
		out << stu_name << "退学前的房间号:" << del_students[stu_name].floor_num() << '-' << del_students[stu_name].room_num() << endl;
	}
	else																	//都找不到，显示找不到
	{
		out << "找不到数据" << endl;
	}
	out << "----------------------------------------------------------\n";
}


/*
函数:query_stu（）
功能:输出某个房间所住的学生信息。
*/
void query_stu(ostream& out)
{
	vector<string> stu;
	string dorm;
	int floor, room, empty;
	empty = 1;
	cout << "\t请输入要查询的宿舍房间(xx-xx)：";
	cin >> dorm;
	read_room(dorm, floor, room);												//转化xx-xx为数字
	for (auto map_it = students.begin(); map_it != students.end(); map_it++)	//遍历匹配
	{
		if (map_it->second.floor_num() == floor && map_it->second.room_num() == room)
		{
			stu.push_back(map_it->first);
			empty = 0;
		}
	}
	if (empty == 0)																//找到的话，输出学生信息
	{
		show_data(stu, out);
	}
	if (empty == 1)																//找不到的话，输出错误信息
	{
		out << "\n----------------------------------------------------------\n";
		out << "此房间没有学生或不存在此房间" << endl;
		out << "----------------------------------------------------------\n";
	}
}

bool cmp_charm(string a, string b)												//用于魅力值排序
{
	return students[a].charm() < students[b].charm();
}

/*
函数:query_lover（）
功能:输出某个学生的恋爱史。
*/
void query_lover(ostream& out, string stu_name, int ch)
{
	vector<string> lover;
	if (students.find(stu_name) != students.end())
		lover = students[stu_name].lover();
	else
		lover = del_students[stu_name].lover();
	switch (ch)
	{
	case 1:
		show_data(lover, out);													//默认按时间排序
		break;
	case 2:
		sort(lover.begin(), lover.end());										//按姓名排序
		show_data(lover, out);
		break;
	case 3:
		sort(lover.begin(), lover.end(), cmp_charm);							//按魅力值排序
		show_data(lover, out);
	default:
		query_lover_ch(out);
		break;
	}
}

/*
函数:query_lover_ch（）
功能:查询学生恋爱史的选择界面。
*/
void query_lover_ch(ostream& out)
{
	int ch;
	string stu_name;
	cout << "\t请输入要查询的学生姓名：";
	cin >> stu_name;
	//没有此学生数据，就显示提示信息
	if (students.find(stu_name) == students.end() && del_students.find(stu_name) == del_students.end())
	{
		out << "\n----------------------------------------------------------\n";
		out << "此学生不在学校读过，无学生数据" << endl;
		out << "----------------------------------------------------------\n";
	}
	//有此学生数据，继续选择排序顺序
	else
	{
		cout << "\t请输入排序顺序 1.时间排序 2.姓名排序 3.魅力排序：";
		cin >> ch;
		query_lover(out, stu_name, ch);
	}
}

/*
函数:query_lover_most（）
功能:查询恋爱次数最多的学生。
*/
void query_lover_most(ostream& out)
{
	vector<string> lover_most;											//存储恋爱次数最多的学生（可能多个）
	vector<string>::size_type max=0;
	//遍历寻找学生中恋爱次数最多的学生
	for (auto map_it = students.begin(); map_it != students.end(); map_it++)
	{
		if (map_it->second.lover().size() == max)							//最大值相等，存入lover_most容器
		{
			lover_most.push_back(map_it->first);
		}
		else if (map_it->second.lover().size() > max)						//一旦大于最大值，清空存储lover_most容器
		{
			lover_most.clear();
			lover_most.push_back(map_it->first);
			max = map_it->second.lover().size();
		}
	}
	//输出学生信息
	show_data(lover_most, out);
}

/*
函数:query_lover_charm（）
功能:查询历任恋人魅力值最高的学生。
*/
void query_lover_charm(ostream& out)
{
	vector<string> lover_charm;
	double max_charm = 0;
	//遍历在读学生的恋爱史
	for (auto map_it = students.begin(); map_it != students.end(); map_it++)
	{
		double max = 0;
		//对每个学生的恋爱史找出历任恋人的最大魅力
		vector<string> lover = map_it->second.lover();
		for (auto i = lover.begin(); i != lover.end(); i++)
		{
			if (students[*i].charm() > max)
			{
				max = students[*i].charm();
			}
		}
		//最大魅力等于所有学生中的最大值，存入lover_charm容器
		if (max == max_charm)
		{
			lover_charm.push_back(map_it->first);
		}
		//最大魅力大于所有学生中的最大值，清空并存入lover_charm容器
		else if (max > max_charm)
		{
			lover_charm.clear();
			lover_charm.push_back(map_it->first);
			max_charm = max;
		}
	}
	show_data(lover_charm, out);
}

/*
函数:query_state_ch（）
功能:查询状态的选择界面。
*/
void query_state_ch()
{
	int sex_ch,charac_ch,begin,end;
	do
	{
		cout << "\t请选择性别范围 1.男生 2.女生 3.所有学生 0.退出：";
		cin >> sex_ch;
		if (sex_ch == 0)return;
	} while (sex_ch != 1 && sex_ch != 2 && sex_ch != 3);
	do
	{
		cout << "\t请输入要查询的属性值 1.金钱 2.体重 3.知识 4.魅力 0.退出：";
		cin >> charac_ch;
		if (charac_ch == 0)return;
	} while (sex_ch != 1 && sex_ch != 2 && sex_ch != 3);

	cout << "\t请输入要查询的范围，起始值，终止值：";
	cin >> begin >> end;
	
	switch (sex_ch)
	{
	case 1:
		switch (charac_ch)
		{
		case 1:
			query_money(cout, begin, end, "男");
			break;
		case 2:
			query_weight(cout, begin, end, "男");
			break;
		case 3:
			query_knowledge(cout, begin, end, "男");
			break;
		case 4:
			query_charm(cout, begin, end, "男");
			break;
		}
		break;
	case 2:
		switch (charac_ch)
		{
		case 1:
			query_money(cout, begin, end, "女");
			break;
		case 2:
			query_weight(cout, begin, end, "女");
			break;
		case 3:
			query_knowledge(cout, begin, end, "女");
			break;
		case 4:
			query_charm(cout, begin, end, "女");
			break;
		}
		break;
	case 3:
		switch (charac_ch)
		{
		case 1:
			query_money(cout, begin, end, "男女");
			break;
		case 2:
			query_weight(cout, begin, end, "男女");
			break;
		case 3:
			query_knowledge(cout, begin, end, "男女");
			break;
		case 4:
			query_charm(cout, begin, end, "男女");
			break;
		}
		break;
	}

}

/*
函数:query_charm（）
功能:查询魅力。
*/
void query_charm(ostream& out,int begin, int end, string sex)
{
	vector<string> stu;
	//遍历在读学生，找出符合查询条件的
	for (auto map_it = students.begin(); map_it != students.end(); map_it++)
	{
		if (map_it->second.sex().find_first_of(sex) != string::npos && map_it->second.charm() >= begin && map_it->second.charm() <= end)
		{
			stu.push_back(map_it->first);
		}
	}
	sort(stu.begin(), stu.end(), cmp_charm);			//因map容器本身按姓名排序，只需再按魅力值排序即可
	show_data(stu, out);

}

bool cmp_money(string a, string b)						//用于金钱升序排序
{
	return students[a].money() < students[b].money();
}

/*
函数:query_money（）
功能:查询魅力。
*/
void query_money(ostream& out, int begin, int end, string sex)
{
	vector<string> stu;
	//遍历在读学生，找出符合查询条件的
	for (auto map_it = students.begin(); map_it != students.end(); map_it++)
	{
		if (map_it->second.sex().find_first_of(sex) != string::npos && map_it->second.money() >= begin && map_it->second.money() <= end)
		{
			stu.push_back(map_it->first);
		}
	}
	sort(stu.begin(), stu.end(), cmp_money);			//按金钱值排序
	show_data(stu, out);

}


bool cmp_weight(string a, string b)					//用于体重升序排序
{
	return students[a].weight() < students[b].weight();
}

/*
函数:query_weight（）
功能:查询魅力。
*/
void query_weight(ostream& out, int begin, int end, string sex)
{
	vector<string> stu;
	//遍历在读学生，找出符合查询条件的
	for (auto map_it = students.begin(); map_it != students.end(); map_it++)
	{
		if (map_it->second.sex().find_first_of(sex) != string::npos && map_it->second.weight() >= begin && map_it->second.weight() <= end)
		{
			stu.push_back(map_it->first);
		}
	}
	sort(stu.begin(), stu.end(), cmp_weight);			//按体重值排序
	show_data(stu, out);

}

bool cmp_knowledge(string a, string b)					//用于知识升序排序
{
	return students[a].knowledge() < students[b].knowledge();
}

/*
函数:query_knowledge（）
功能:查询魅力。
*/
void query_knowledge(ostream& out, int begin, int end, string sex)
{
	vector<string> stu;
	//遍历在读学生，找出符合查询条件的
	for (auto map_it = students.begin(); map_it != students.end(); map_it++)
	{
		if (map_it->second.sex().find_first_of(sex) != string::npos && map_it->second.knowledge() >= begin && map_it->second.knowledge() <= end)
		{
			stu.push_back(map_it->first);
		}
	}
	sort(stu.begin(), stu.end(), cmp_knowledge);		//按知识值排序
	show_data(stu, out);

}


