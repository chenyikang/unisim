#include "student_info.h"

using std::istringstream;

extern map<string, double> config;

////student_info类
//
//student_info::student_info(const student_info& s) : cp(0)
//{
//	if (s.cp) cp = s.cp->clone();
//}
//
//student_info& student_info::operator=(const student_info& s)
//{
//	if (&s != this) {
//		delete cp;
//		if (s.cp)
//			cp = s.cp->clone();
//		else
//			cp = 0;
//	}
//	return *this;
//}
//
//istream& student_info::read(istream& in)
//{
//	string sex;
//	in >> sex;
//	if (sex == "F")
//		cp = new male(in);
//	else if (sex=="M")
//		cp = new female(in);
//
//	return in;
//}


//common类

istream& common::read(istream& in)
{
	read_common(in);
	read_lover(in);
	return in;
}


istream& common::read_common(istream& in)
{
	in >> stu_name >> stu_sex;			//读入学生姓名和性别

	string temp_fnum;					//暂时定义的字符串记录楼层数量
	getline(in, temp_fnum, '-');		//由于宿舍信息是XX-XX，所以遇到‘-’之前的为楼层数
	in >> stu_room_num;					//遇到‘-’之后的为房间号，直接读入

	istringstream temp(temp_fnum);		//由于之前读入的楼层数是字符串
	temp >> stu_floor_num;				//再转换为数字

	string charac;
	if (getline(in, charac))			//如果后面还有学生状态数据，则将后面数据来初始化学生状态
	{
		double money, charm, knowledge, weight;
		int islove;
		istringstream record_charac(charac);
		record_charac >> charm >> weight >> money >> knowledge >> islove;
		stu_charm = charm;
		stu_weight = weight;
		stu_money = money;
		stu_knowledge = knowledge;
		stu_islove = islove;
	}
	else									//如果后面没有学生状态数据，则用配置信息进行初始化学生状态
	{
		stu_charm = config["CHARM"];
		stu_weight = config["WEIGHT"];
		stu_money = config["MONEY"];
		stu_knowledge = config["KNOWLEDGE"];
		stu_islove = 0;
	}

	return in;
}

istream& common::read_lover(istream& in)
{
	string lover;
	if (getline(in, lover))	//如果后面学生有恋爱史，则将后面数据来初始化恋爱史
	{
		istringstream record_lover(lover);
		string lover_name;
		while (record_lover >> lover_name)
			stu_lover.push_back(lover_name);
	}
	return in;
}

//male类

istream& male::read(istream& in)
{
	read_common(in);
	if (in >> stu_health);
	else
		stu_health = config["HEALTH"];
	read_lover(in);
	return in;
}


//female类

istream& female::read(istream& in)
{
	read_common(in);
	if (in >> stu_looks);
	else
		stu_looks = config["LOOKS"];
	read_lover(in);
	return in;
}