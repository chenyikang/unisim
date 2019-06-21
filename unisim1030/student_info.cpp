#include "student_info.h"

using std::istringstream;

extern map<string, double> config;

////student_info��
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


//common��

istream& common::read(istream& in)
{
	read_common(in);
	read_lover(in);
	return in;
}


istream& common::read_common(istream& in)
{
	in >> stu_name >> stu_sex;			//����ѧ���������Ա�

	string temp_fnum;					//��ʱ������ַ�����¼¥������
	getline(in, temp_fnum, '-');		//����������Ϣ��XX-XX������������-��֮ǰ��Ϊ¥����
	in >> stu_room_num;					//������-��֮���Ϊ����ţ�ֱ�Ӷ���

	istringstream temp(temp_fnum);		//����֮ǰ�����¥�������ַ���
	temp >> stu_floor_num;				//��ת��Ϊ����

	string charac;
	if (getline(in, charac))			//������滹��ѧ��״̬���ݣ��򽫺�����������ʼ��ѧ��״̬
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
	else									//�������û��ѧ��״̬���ݣ�����������Ϣ���г�ʼ��ѧ��״̬
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
	if (getline(in, lover))	//�������ѧ��������ʷ���򽫺�����������ʼ������ʷ
	{
		istringstream record_lover(lover);
		string lover_name;
		while (record_lover >> lover_name)
			stu_lover.push_back(lover_name);
	}
	return in;
}

//male��

istream& male::read(istream& in)
{
	read_common(in);
	if (in >> stu_health);
	else
		stu_health = config["HEALTH"];
	read_lover(in);
	return in;
}


//female��

istream& female::read(istream& in)
{
	read_common(in);
	if (in >> stu_looks);
	else
		stu_looks = config["LOOKS"];
	read_lover(in);
	return in;
}