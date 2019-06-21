#include"student_info.h"

using std::cout; using std::endl; using std::istringstream;

extern map<string, common> students;
extern map<string, common> del_students;
extern map<string, double> config;
extern map<string, string> formula;
extern map<string, map<string, int>> students_woo_times;

/*
����:state����
����:����ѧ�����е�eat/work/study�ı�ѧ����״̬��Ҳ�ɽ���quit������
*/
void state(vector<string>& instructions)
{
	string name = instructions[0];									//��ȡָ��Ķ���ѧ������
	double food_taken, study_time, work_time;						
	food_taken = study_time = work_time = 0;				
	int del_flag = 0;												//��¼��ѧ���Ƿ�Ҫ��ѧ
	for (auto i = 1; i < instructions.size(); i+=2)					//��ȡeat/study/work������ֵ
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
		else														//��ѧ����ѧ�����
		{
			del_flag = 1;
		}
	}
	if (!students[name].expression(food_taken, study_time, work_time))
	{
		cout << "EAT/WORK/STUDY��Чָ��" << endl;					//���״̬�ı䳬���Ϸ���Χ����Ϊ��Чָ��
	}
	if (del_flag == 1)												//���ѧ�������ѧ�������ѧ������������ɾ������������ѧѧ����������
	{
		del_students[name] = students[name];
		students.erase(name);
	}
}

/*
����:move����
����:��ѧ����һ������ᵽ��һ�����ᡣ
*/
void move(vector<floor_info>& dorm, vector<string>&instructions)
{
	string name = instructions[0];									//��ȡָ�����ѧ������
	string from = instructions[2];									//��ȡ����ѧ������from
	string to = instructions[3];									//��ȡ����ѧ������to
	
	int from_fnum, from_rnum, to_fnum, to_rnum;
	read_room(from, from_fnum, from_rnum);							//��������ַ���ת��Ϊint����
	read_room(to, to_fnum, to_rnum);								//��������ַ���ת��Ϊint����	
	
	//�ж�ָ����from��������Ƿ���ȷ������ȷ����Ϊ��Чָ��
	if (students[name].floor_num() == from_fnum && students[name].room_num() == from_rnum)
	{
		//�ж���Ҫת��to������Ƿ��д�λ����������Ϊ��Чָ��
		if (dorm[to_fnum][to_rnum].size() < dorm[to_fnum][to_rnum].capacity())
		{
			dorm[to_fnum][to_rnum].push_back(name);					//��ѧ�����ִ������ṹ
			students[name].stu_floor_num = to_fnum;						//������ѧ��������Ϣ�������
			students[name].stu_room_num = to_rnum;
			auto i = dorm[from_fnum][from_rnum].begin();
			while (i != dorm[from_fnum][from_rnum].end())			//ɾ��ѧ��ԭ����ṹ�е�����
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
			cout << "Ŀ�����᷿����������Чָ��" << endl;
	}
	else
	{
		cout << "����������Ϣ����Чָ��" << endl;
	}
}

/*
����:read_room����
����:��xx-xx������ַ�����ȡ��int�͵�¥�㣬����š�
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
����:enrol����
����:ѧ����һ����ѧ�������ѧ�����ǵ�һ����ѧ��֮ǰ��ѧ�ģ�������������ѧǰ��״̬��
*/
void enrol(vector<floor_info>& dorm, vector<string>& instructions)
{
	string name = instructions[0];									//��ȡָ����ѧ����������
	string sex = instructions[1];									//��ȡָ����ѧ�������Ա�
	string to = instructions[3];									//��ȡָ����ѧ��������ס����
	int fnum, rnum;
	read_room(to, fnum, rnum);										//��xx-xx�����ת��Ϊint����
	//�ж�Ŀ�������Ƿ��д�λ����������Чָ��
	if (dorm[fnum][rnum].size() < dorm[fnum][rnum].capacity())
	{
			//�жϴ�ѧ���Ƿ�����ѧѧ��������ֵ֮ǰ��ѧʱ���״̬����������г�ʼ��
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
		cout << "Ŀ�����᷿����������Чָ��" << endl;
}

/*
����:woo����
����:����ѧ������������ϵ��
*/
void woo(vector<string>& instructions)
{
	string stu1_name = instructions[0];										//��ָ���л�ȡѧ��һ����
	string stu2_name = instructions[2];										//��ָ���л�ȡѧ��������

	common stu1;
	common stu2;

	if (students.find(stu1_name) != students.end())							//�������л�ȡѧ��һ��Ϣ
		stu1 = students[stu1_name];
	else if(del_students.find(stu1_name) != del_students.end())
		stu1 = del_students[stu1_name];

	if (students.find(stu2_name) != students.end())							//�������л�ȡѧ������Ϣ
		stu2 = students[stu2_name];
	else if (del_students.find(stu2_name) != del_students.end())
		stu2 = del_students[stu2_name];

	double stu1_charm = stu1.charm();							//��ȡѧ��һ����ֵ
	double stu2_charm = stu2.charm();							//��ȡѧ��������ֵ
	double charm_diff;										//������ֵ

	//ѧ��һ�����趼�ǵ���״̬��������Чָ��
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
		//ѧ��һ����֮���������ֵ��ҪС����ֵ��������Чָ��
		if (charm_diff <= config["LOVE_STANDARD"])
		{
			stu1.stu_islove = 1;									//�ı�ѧ��һ��������״̬
			stu2.stu_islove = 1;
			stu1.stu_lover.push_back(stu2_name);					//��ѧ��һ�����ֱ����Է�����ʷ����
			stu2.stu_lover.push_back(stu1_name);
		}
		else
			cout << "��������ֵ��������Чָ��" << endl;
	}
	//���ѧ��һ��Ҫ��ѧ����ǽ�ǵĻ�
	else if (stu1.islove() == 0 && stu2.islove() == 1)
	{
		double stu3_charm;
		string stu3_name = stu2.lover()[stu2.lover().size() - 1];					//�õ�ѧ��������������

		if (students.find(stu3_name) != students.end())							//�������л�ȡѧ����������ѧ��������ֵ
			stu3_charm = students[stu3_name].charm();
		else if (del_students.find(stu3_name) != del_students.end())
			stu3_charm = del_students[stu3_name].charm();

		if (stu1_charm > stu3_charm)								//ѧ��һ����ֵҪ��ѧ������
		{
			charm_diff = (stu1_charm - stu3_charm) / (stu1_charm);	//�����������ֵ��
		}
		else														//С�Ļ���ֱ����ʧ��
		{
			cout << "����ֵ���ͣ���ǽ��ʧ�ܣ���Чָ��" << endl;
			return;
		}

		if (charm_diff >= config["LOVE_RECONSTUCT_STANDARD"])		//������ֵ����������ֵ���������
		{
			//ѧ��һ֮ǰ���˹�ѧ����
			if (students_woo_times[stu2_name].find(stu1_name) != students_woo_times[stu2_name].end())
			{
				if (students_woo_times[stu2_name][stu1_name] == 3)	//�˵���3�ξͳɹ�
				{
					vector<string> ins;
					ins[0] = stu2_name;
					ins[1] = stu2.lover()[stu2.lover().size() - 1];
					breakup(ins);									//����ԭ�ȵķ���
					woo(instructions);								//����һ��
					return;
				}
				else
				{
					students_woo_times[stu2_name][stu1_name]++;		//����3�Σ���++
					cout << "�����������˲���" << endl;
				}
			}
			//֮ǰû�˹����ͳ�ʼ��Ϊ�˴���Ϊ1
			else
			{
				students_woo_times[stu2_name][stu1_name] = 1;
				cout << "�����������˲���" << endl;
			}
		}
		else														//С��������ֵ������ʧ��
		{
			cout << "����ֵ���ͣ���ǽ��ʧ�ܣ���Чָ��" << endl;
			return;
		}
	}
	else
		cout << "��ѧ�������ǵ���״̬����Чָ��" << endl;

	if (students.find(stu1_name) != students.end())				//�洢�ı���ѧ��һ��Ϣ
		students[stu1_name] = stu1;
	else if (del_students.find(stu1_name) != del_students.end())
		del_students[stu1_name] = stu1;

	if (students.find(stu2_name) != students.end())				//�洢�ı���ѧ������Ϣ
		students[stu2_name] = stu2;
	else if (del_students.find(stu2_name) != del_students.end())
		del_students[stu2_name] = stu2;
}

/*
����:breakup����
����:����ѧ�����֡�
*/
void breakup(vector<string>& instructions)
{
	string stu1_name = instructions[0];										//��ȡѧ��һ����
	string stu2_name = instructions[1];										//��ȡѧ��������
	
	common stu1;
	common stu2;

	if (students.find(stu1_name) != students.end())							//�������л�ȡѧ��һ��Ϣ
		stu1 = students[stu1_name];
	else if (del_students.find(stu1_name) != del_students.end())
		stu1 = del_students[stu1_name];

	if (students.find(stu2_name) != students.end())							//�������л�ȡѧ������Ϣ
		stu2 = students[stu2_name];
	else if (del_students.find(stu2_name) != del_students.end())
		stu2 = del_students[stu2_name];

	//ѧ��һ�����ö�������״̬��������Чָ��
	if (stu1.islove() == 1 && stu2.islove() == 1)
	{
		string stu1_lover = stu1.lover()[stu1.lover().size() - 1];
		string stu2_lover = stu2.lover()[stu2.lover().size() - 1];

		//ѧ��һ����������������ǶԷ���������Чָ��
		if (stu1_lover == stu2_name && stu2_lover == stu1_name)
		{
			stu1.stu_islove = 0;									//�ı�ѧ��һ��������״̬
			stu2.stu_islove = 0;
			students_woo_times.erase(stu1_name);
			students_woo_times.erase(stu2_name);
		}
		else
			cout << "���˲������˹�ϵ����Чָ��" << endl;
	}
	else
		cout << "���˲��Ƕ�������״̬����Чָ��" << endl;

	if (students.find(stu1_name) != students.end())				//�洢�ı���ѧ��һ��Ϣ
		students[stu1_name] = stu1;
	else if (del_students.find(stu1_name) != del_students.end())
		del_students[stu1_name] = stu1;

	if (students.find(stu2_name) != students.end())				//�洢�ı���ѧ������Ϣ
		students[stu2_name] = stu2;
	else if (del_students.find(stu2_name) != del_students.end())
		del_students[stu2_name] = stu2;
}