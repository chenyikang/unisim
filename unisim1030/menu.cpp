#include "menu.h"

int menu()
{
	int choice;
	do
	{
		system("pause");
		system("cls");
		cout << "*----------------չʾ��ѯϵͳ����----------------*\n\n\n" << endl;
		cout << "\t**********************************\n";
		cout << "\t*        ѧ�����ɲ�ѯϵͳ        *\n";
		cout << "\t*================================*\n";
		cout << "\t*    1����Χ��ѯѧ������ֵ       *\n";
		cout << "\t*    2������ѧ�����������       *\n";
		cout << "\t*    3������������סѧ����       *\n";
		cout << "\t*    4����ѯѧ������ʷ           *\n";
		cout << "\t*    5����ѯ�����������ѧ��     *\n";
		cout << "\t*    6����ѯ���������������ѧ�� *\n";
		cout << "\t*    0���˳�����ϵͳ             *\n";
		cout << "\t**********************************\n";
		cout << "\n\t��ѡ��:";
		cin >> choice;
	} while (choice < 0 || choice > 7);
	return choice;
}

void display_menu()
{
	int ch;
	do
	{
		ch = menu();
		switch(ch)
		{
			case 1:
				query_state_ch();
				break;
			case 2:
				query_dorm(cout);
				break;
			case 3:
				query_stu(cout);
				break;
			case 4:
				query_lover_ch(cout);
				break;
			case 5:
				query_lover_most(cout);
				break;
			case 6:
				query_lover_charm(cout);
				break;
			case 0:
				break;
			default:
				cout << "ѡ�����" << endl;
				break;
		}
	} while (ch);
}