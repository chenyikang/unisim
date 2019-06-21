#include"query.h"

extern map<string, common> students;
extern map<string, common> del_students;

/*
����:show_data����
����:�����ѯ���ѧ����Ϣ��
*/
void show_data(const vector<string>& stu, ostream& out)
{
	out << "\n----------------------------------------------------------\n";
	out << "����"<< '\t' << "�Ա�" << '\t' << "����" << '\t' << "��Ǯ" << '\t' << "֪ʶ" << '\t' << "����";
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
����:query_dorm����
����:��ѯѧ��ס�ĸ����ᡣ
*/
void query_dorm(ostream& out)
{
	string stu_name;
	cout << "\t������Ҫ��ѯ�����ѧ��������";
	cin >> stu_name;
	out << "\n----------------------------------------------------------\n";
	if (students.find(stu_name) != students.end())							//���ڶ�ѧ�����ң��ҵ������������Ϣ
	{
		out << stu_name << "�ķ����:" << students[stu_name].floor_num() << '-' << students[stu_name].room_num() << endl;
	}
	else if (del_students.find(stu_name) != del_students.end())				//����ѧѧ�����ң��ҵ������������Ϣ
	{
		out << stu_name << "��ѧǰ�ķ����:" << del_students[stu_name].floor_num() << '-' << del_students[stu_name].room_num() << endl;
	}
	else																	//���Ҳ�������ʾ�Ҳ���
	{
		out << "�Ҳ�������" << endl;
	}
	out << "----------------------------------------------------------\n";
}


/*
����:query_stu����
����:���ĳ��������ס��ѧ����Ϣ��
*/
void query_stu(ostream& out)
{
	vector<string> stu;
	string dorm;
	int floor, room, empty;
	empty = 1;
	cout << "\t������Ҫ��ѯ�����᷿��(xx-xx)��";
	cin >> dorm;
	read_room(dorm, floor, room);												//ת��xx-xxΪ����
	for (auto map_it = students.begin(); map_it != students.end(); map_it++)	//����ƥ��
	{
		if (map_it->second.floor_num() == floor && map_it->second.room_num() == room)
		{
			stu.push_back(map_it->first);
			empty = 0;
		}
	}
	if (empty == 0)																//�ҵ��Ļ������ѧ����Ϣ
	{
		show_data(stu, out);
	}
	if (empty == 1)																//�Ҳ����Ļ������������Ϣ
	{
		out << "\n----------------------------------------------------------\n";
		out << "�˷���û��ѧ���򲻴��ڴ˷���" << endl;
		out << "----------------------------------------------------------\n";
	}
}

bool cmp_charm(string a, string b)												//��������ֵ����
{
	return students[a].charm() < students[b].charm();
}

/*
����:query_lover����
����:���ĳ��ѧ��������ʷ��
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
		show_data(lover, out);													//Ĭ�ϰ�ʱ������
		break;
	case 2:
		sort(lover.begin(), lover.end());										//����������
		show_data(lover, out);
		break;
	case 3:
		sort(lover.begin(), lover.end(), cmp_charm);							//������ֵ����
		show_data(lover, out);
	default:
		query_lover_ch(out);
		break;
	}
}

/*
����:query_lover_ch����
����:��ѯѧ������ʷ��ѡ����档
*/
void query_lover_ch(ostream& out)
{
	int ch;
	string stu_name;
	cout << "\t������Ҫ��ѯ��ѧ��������";
	cin >> stu_name;
	//û�д�ѧ�����ݣ�����ʾ��ʾ��Ϣ
	if (students.find(stu_name) == students.end() && del_students.find(stu_name) == del_students.end())
	{
		out << "\n----------------------------------------------------------\n";
		out << "��ѧ������ѧУ��������ѧ������" << endl;
		out << "----------------------------------------------------------\n";
	}
	//�д�ѧ�����ݣ�����ѡ������˳��
	else
	{
		cout << "\t����������˳�� 1.ʱ������ 2.�������� 3.��������";
		cin >> ch;
		query_lover(out, stu_name, ch);
	}
}

/*
����:query_lover_most����
����:��ѯ������������ѧ����
*/
void query_lover_most(ostream& out)
{
	vector<string> lover_most;											//�洢������������ѧ�������ܶ����
	vector<string>::size_type max=0;
	//����Ѱ��ѧ����������������ѧ��
	for (auto map_it = students.begin(); map_it != students.end(); map_it++)
	{
		if (map_it->second.lover().size() == max)							//���ֵ��ȣ�����lover_most����
		{
			lover_most.push_back(map_it->first);
		}
		else if (map_it->second.lover().size() > max)						//һ���������ֵ����մ洢lover_most����
		{
			lover_most.clear();
			lover_most.push_back(map_it->first);
			max = map_it->second.lover().size();
		}
	}
	//���ѧ����Ϣ
	show_data(lover_most, out);
}

/*
����:query_lover_charm����
����:��ѯ������������ֵ��ߵ�ѧ����
*/
void query_lover_charm(ostream& out)
{
	vector<string> lover_charm;
	double max_charm = 0;
	//�����ڶ�ѧ��������ʷ
	for (auto map_it = students.begin(); map_it != students.end(); map_it++)
	{
		double max = 0;
		//��ÿ��ѧ��������ʷ�ҳ��������˵��������
		vector<string> lover = map_it->second.lover();
		for (auto i = lover.begin(); i != lover.end(); i++)
		{
			if (students[*i].charm() > max)
			{
				max = students[*i].charm();
			}
		}
		//���������������ѧ���е����ֵ������lover_charm����
		if (max == max_charm)
		{
			lover_charm.push_back(map_it->first);
		}
		//���������������ѧ���е����ֵ����ղ�����lover_charm����
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
����:query_state_ch����
����:��ѯ״̬��ѡ����档
*/
void query_state_ch()
{
	int sex_ch,charac_ch,begin,end;
	do
	{
		cout << "\t��ѡ���Ա�Χ 1.���� 2.Ů�� 3.����ѧ�� 0.�˳���";
		cin >> sex_ch;
		if (sex_ch == 0)return;
	} while (sex_ch != 1 && sex_ch != 2 && sex_ch != 3);
	do
	{
		cout << "\t������Ҫ��ѯ������ֵ 1.��Ǯ 2.���� 3.֪ʶ 4.���� 0.�˳���";
		cin >> charac_ch;
		if (charac_ch == 0)return;
	} while (sex_ch != 1 && sex_ch != 2 && sex_ch != 3);

	cout << "\t������Ҫ��ѯ�ķ�Χ����ʼֵ����ֵֹ��";
	cin >> begin >> end;
	
	switch (sex_ch)
	{
	case 1:
		switch (charac_ch)
		{
		case 1:
			query_money(cout, begin, end, "��");
			break;
		case 2:
			query_weight(cout, begin, end, "��");
			break;
		case 3:
			query_knowledge(cout, begin, end, "��");
			break;
		case 4:
			query_charm(cout, begin, end, "��");
			break;
		}
		break;
	case 2:
		switch (charac_ch)
		{
		case 1:
			query_money(cout, begin, end, "Ů");
			break;
		case 2:
			query_weight(cout, begin, end, "Ů");
			break;
		case 3:
			query_knowledge(cout, begin, end, "Ů");
			break;
		case 4:
			query_charm(cout, begin, end, "Ů");
			break;
		}
		break;
	case 3:
		switch (charac_ch)
		{
		case 1:
			query_money(cout, begin, end, "��Ů");
			break;
		case 2:
			query_weight(cout, begin, end, "��Ů");
			break;
		case 3:
			query_knowledge(cout, begin, end, "��Ů");
			break;
		case 4:
			query_charm(cout, begin, end, "��Ů");
			break;
		}
		break;
	}

}

/*
����:query_charm����
����:��ѯ������
*/
void query_charm(ostream& out,int begin, int end, string sex)
{
	vector<string> stu;
	//�����ڶ�ѧ�����ҳ����ϲ�ѯ������
	for (auto map_it = students.begin(); map_it != students.end(); map_it++)
	{
		if (map_it->second.sex().find_first_of(sex) != string::npos && map_it->second.charm() >= begin && map_it->second.charm() <= end)
		{
			stu.push_back(map_it->first);
		}
	}
	sort(stu.begin(), stu.end(), cmp_charm);			//��map����������������ֻ���ٰ�����ֵ���򼴿�
	show_data(stu, out);

}

bool cmp_money(string a, string b)						//���ڽ�Ǯ��������
{
	return students[a].money() < students[b].money();
}

/*
����:query_money����
����:��ѯ������
*/
void query_money(ostream& out, int begin, int end, string sex)
{
	vector<string> stu;
	//�����ڶ�ѧ�����ҳ����ϲ�ѯ������
	for (auto map_it = students.begin(); map_it != students.end(); map_it++)
	{
		if (map_it->second.sex().find_first_of(sex) != string::npos && map_it->second.money() >= begin && map_it->second.money() <= end)
		{
			stu.push_back(map_it->first);
		}
	}
	sort(stu.begin(), stu.end(), cmp_money);			//����Ǯֵ����
	show_data(stu, out);

}


bool cmp_weight(string a, string b)					//����������������
{
	return students[a].weight() < students[b].weight();
}

/*
����:query_weight����
����:��ѯ������
*/
void query_weight(ostream& out, int begin, int end, string sex)
{
	vector<string> stu;
	//�����ڶ�ѧ�����ҳ����ϲ�ѯ������
	for (auto map_it = students.begin(); map_it != students.end(); map_it++)
	{
		if (map_it->second.sex().find_first_of(sex) != string::npos && map_it->second.weight() >= begin && map_it->second.weight() <= end)
		{
			stu.push_back(map_it->first);
		}
	}
	sort(stu.begin(), stu.end(), cmp_weight);			//������ֵ����
	show_data(stu, out);

}

bool cmp_knowledge(string a, string b)					//����֪ʶ��������
{
	return students[a].knowledge() < students[b].knowledge();
}

/*
����:query_knowledge����
����:��ѯ������
*/
void query_knowledge(ostream& out, int begin, int end, string sex)
{
	vector<string> stu;
	//�����ڶ�ѧ�����ҳ����ϲ�ѯ������
	for (auto map_it = students.begin(); map_it != students.end(); map_it++)
	{
		if (map_it->second.sex().find_first_of(sex) != string::npos && map_it->second.knowledge() >= begin && map_it->second.knowledge() <= end)
		{
			stu.push_back(map_it->first);
		}
	}
	sort(stu.begin(), stu.end(), cmp_knowledge);		//��֪ʶֵ����
	show_data(stu, out);

}


