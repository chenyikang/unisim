#include"student_info.h"

using std::getline; using std::istringstream; using std::cout; using std::endl;

extern map<string, common>students;
extern map<string, common> del_students;
extern map<string, double> config;
extern map<string, string> formula;

int read_instruction(istream& is, vector<string>& instructions)
{
	string temp, tmp;														//������ʱ�洢�ַ���
	string str_num;															//�����洢�������ֵ��ַ���
	is >> temp;																//�ȶ�ȡ��һ���ַ���
	
	//�����һ���ַ�����ADD�Ļ��������ADDָ���ƥ��
	if (temp == "ADD")
	{
		instructions.push_back(temp);										//�������������vector��
		is >> str_num >> temp;												//������������ַ��������ж�
		if (atoi(str_num.c_str()) >= 1 && atoi(str_num.c_str()) < 99)		//���ֵ���1-99֮��
		{
			if (temp == "FLOOR(s)" || temp == "FLOOR")						//ƥ��floor(s)
			{
				instructions.push_back(str_num);							//���Ҫadd¥�������
				instructions.push_back(temp);								//���"FLOOR"
				return 1;													//����1����ʾ����FLOOR
			}
			else if (temp == "ROOM(s)" || temp == "ROOM")					//ƥ��room(s)
			{
				instructions.push_back(str_num);							//���Ҫadd���������
				instructions.push_back(temp);								//���"ROOM"
				is >> temp >> str_num >> tmp;
				if (temp == "TO" && tmp == "FLOOR")							//ƥ��TO FLOOR
				{
					instructions.push_back(str_num);						//��������ӷ����¥����
					instructions.push_back(tmp);							//���"FLOOR"
					return 2;												//����2����ʾ����ROOM
				}
				else
				{
					return 0;												//����0,��ʾ��Чָ��
				}
			}
			else if (temp == "BED(s)" || temp == "BED")						//ƥ��room(s)
			{
				instructions.push_back(str_num);							//���Ҫadd��λ������
				instructions.push_back(temp);								//���"BED"
				is >> tmp;
				if (tmp == "TO")											//ƥ��TO
				{
					is >> str_num;											
					instructions.push_back(str_num);						//��������ӵķ���� XX-XX
					return 3;												//����3����ʾ����BED
				}
				else
				{
					return 0;												//����0����ʾ��Чָ��
				}
			}
			else
			{
				return 0;													//����0����ʾ��Чָ��
			}
		}
		else
		{
			return 0;														//����0����ʾ��Чָ��
		}
	}

	//�����һ���ַ������ڶ�ѧ���е������������EAT WORK STUDY ENROL QUIT MOVEָ��ƥ��
	else if (students.find(temp) != students.end())							
	{
		instructions.push_back(temp);										//���Ҫ�����ѧ������
		is >> tmp;															//��ȡ��һ���ַ���
		if (tmp == "EAT" || tmp == "STUDY" || tmp == "WORK")				//ƥ��EAT STUDY WORK
		{
			instructions.push_back(tmp);									//�����Ӧ�ĺ�������
			is >> str_num;													//��ȡ��һ���������ֵ��ַ���
			if (atoi(str_num.c_str()) >= 1 && atoi(str_num.c_str()) <= 100)	//Ҫ��������1-100֮��
				instructions.push_back(str_num);							
			if (getline(is, tmp))											//��ȡʣ�µ�һ���ַ���
			{
				istringstream in(tmp);										//ת��Ϊ�ַ�����
				while ((instructions.size() < 7) && (in >> temp))			//���ָ��û����3�����ܶ����ʱ�����������ָ��
				{
					if (temp == "EAT" || temp == "STUDY" || temp == "WORK")
					{
						instructions.push_back(temp);
						in >> str_num;
						if (atoi(str_num.c_str()) >= 1 && atoi(str_num.c_str()) <= 100)
							instructions.push_back(str_num);
					}
					else if (temp == "QUIT")								//һ������QUITָ����instructions�У�Ȼ���˳�����
					{
						instructions.push_back(temp);
						return 4;											//����4����ʾ����EAT/WORK/STUDY/QUIT
					}
				}
				return 4;
			}
			else															//ѭ������������4����ʾ����EAT/WORK/STUDY/QUIT
				return 4;
		}
		else if (tmp == "QUIT")
		{
			instructions.push_back(tmp);
			return 4;														//����4����ʾ����EAT/WORK/STUDY/QUIT
		}
		else if (tmp == "MOVE")												//ƥ��MOVEָ��
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
					return 5;												//����5����ʾ����MOVE
				}
				else
					return 0;												//����0����ʾ��Чָ��
			}
			else
			{
				return 0;													//����0����ʾ��Чָ��
			}
		}
		else if (tmp == "WOO")
		{
			instructions.push_back(tmp);
			is >> tmp;
			if (students.find(tmp) != students.end() || del_students.find(tmp) != del_students.end())		//�󰮵Ķ���Ҳ���ҵõ��Ļ�
			{
				instructions.push_back(tmp);
				return 7;									//����7����ʾ����WOO
			}
			else
			{
				return 0;									//�Ҳ����Ļ�������0,��Чָ��
			}
		}
		else if (students.find(tmp) != students.end() || del_students.find(tmp) != del_students.end())		//�ڶ����ַ�����ѧ�����֣������break upָ��ƥ��
		{
			instructions.push_back(tmp);
			is >> tmp >> temp;
			if (tmp == "BREAK" && temp == "UP")				//ƥ�� break up ָ��
			{
				instructions.push_back(tmp);
				instructions.push_back(temp);
				return 8;									//ƥ��ɹ�������8, ��ʾ����BREAK UP
			}
			else
				return 0;									//ƥ��ʧ�ܣ�����0����Чָ��
		}
		else												//�����������Ϊ��Чָ��
		{
			return 0;
		}
	}

	//�����һ���ַ�������ѧѧ�������е����������ж��Ƿ���WOO����BREAK UPָ��
	else if(del_students.find(temp) != del_students.end())
	{
		instructions.push_back(temp);						//���Ҫ�����ѧ������
		is >> tmp;
		if (tmp == "WOO")																					//�ڶ����ַ�����WOO�������wooָ��ƥ��
		{
			instructions.push_back(tmp);
			is >> tmp;
			if (students.find(tmp) != students.end() || del_students.find(tmp) != del_students.end())		//�󰮵Ķ���Ҳ���ҵõ��Ļ�
			{
				instructions.push_back(tmp);
				return 7;									//����7����ʾ����WOO
			}
			else
			{
				return 0;									//�Ҳ����Ļ�������0,��Чָ��
			}
		}
		else if (students.find(tmp) != students.end() || del_students.find(tmp) != del_students.end())		//�ڶ����ַ�����ѧ�����֣������break upָ��ƥ��
		{
			instructions.push_back(tmp);
			is >> tmp >> temp;
			if (tmp == "BREAK" && temp == "UP")				//ƥ�� break up ָ��
			{
				instructions.push_back(tmp);
				instructions.push_back(temp);
				return 8;									//ƥ��ɹ�������8, ��ʾ����BREAK UP
			}
			else
				return 0;									//ƥ��ʧ�ܣ�����0����Чָ��
		}
		else if(tmp == "��" || tmp == "Ů")																	//�ڶ����ַ������Ա������enrolָ��ƥ��
		{
			instructions.push_back(tmp);
			is >> temp;
			if (temp == "ENROL")
			{
				instructions.push_back(temp);
				is >> str_num;
				instructions.push_back(str_num);
				return 6;									//����6����ʾ����ENROL
			}
			else
			{
				return 0;
			}
		}
		else																								//�����������Ϊ��Чָ��
		{
			return 0;
		}
	}

	//�����һ���ַ�������ѧ�������е����������ж��Ƿ�����ѧָ��
	else
	{
		instructions.push_back(temp);
		is >> tmp;
		if (tmp == "��" || tmp == "Ů")
		{
			instructions.push_back(tmp);
			is >> temp;
			if (temp == "ENROL")
			{
				instructions.push_back(temp);
				is >> str_num;
				instructions.push_back(str_num);
				return 6;													//����6����ʾ����ENROL
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;														//����0����ʾ��Чָ��
		}		
	}
}

istream& read_show_instructions(istream& is, vector<floor_info>& dorm)
{
	string line;

	while (getline(is, line) && is )										//ȡÿһ�н��д���
	{
		if (line.empty())													//���Կ���
			continue;
		else																//��Ϊ����ʱ
		{
			vector<string> instructions;									//ָ��˳������
			int ch;															//ѡ��
			istringstream record(line);										//��һ���ַ���ת��Ϊ�ַ���������
			ch = read_instruction(record, instructions);					//��read_instruction����ÿһ��
			switch (ch)
			{
			case 0:
				cout << "��Чָ��" << endl;
				break;
			case 1:															//��� ����floor ��ָ��
				cout << "������" << instructions[0] << endl;
				cout << "����" << instructions[2] << endl;
				cout << "������" << instructions[1] << endl;
				add_floor(dorm, atoi(instructions[1].c_str()));
				break;
			case 2:															//��� ����room ��ָ��
				cout << "������" << instructions[0] << endl;
				cout << "����" << instructions[2] << endl;
				cout << "λ�ã�" << instructions[3] << " " << instructions[4] << endl;
				cout << "������" << instructions[1] << endl;
				add(dorm, atoi(instructions[1].c_str()), instructions[2], atoi(instructions[3].c_str()), instructions[4]);
				break;
			case 3:															//��� ����bed ��ָ��
				cout << "������" << instructions[0] << endl;
				cout << "����" << instructions[2] << endl;
				cout << "λ�ã�" << instructions[3] << endl;
				cout << "������" << instructions[1] << endl;
				add(dorm, atoi(instructions[1].c_str()), instructions[2], 0, instructions[3]);
				break;
			case 4:															//��� study/work/eat/quitָ��
				cout << "����" << instructions[0] << endl;
				for (auto i = 1; i != instructions.size(); i++)
				{
					if ((i % 2) == 1)
						cout << "������" << instructions[i] << endl;
					if ((i % 2) == 0)
						cout << "������" << instructions[i] << endl;
				}
				state(instructions);
				break;
			case 5:															//��� move ָ��
				cout << "����" << instructions[0] << endl;
				cout << "������" << instructions[1] << endl;
				cout << "�ӣ�" << instructions[2] << endl;
				cout << "����" << instructions[3] << endl;
				move(dorm, instructions);
				break;
			case 6:															//����˹�ѧ�� enrol ָ��
				cout << "����" << instructions[0] << endl;
				cout << "�Ա�" << instructions[1] << endl;
				cout << "������" << instructions[2] << endl;
				cout << "λ�ã�" << instructions[3] << endl;
				enrol(dorm, instructions);
				break;
			case 7:															//��� woo ָ��
				cout << "����" << instructions[0] << endl;
				cout << "������" << instructions[1] << endl;
				cout << "����" << instructions[2] << endl;
				woo(instructions);
				break;
			case 8:															//��� break up ָ��
				cout << "����" << instructions[0] << endl;
				cout << "������" << instructions[2] << " " << instructions[3] << endl;
				cout << "����" << instructions[1] << endl;
				breakup(instructions);
				break;
			}
			cout << endl;
		}
	}
	return is;
}