#include "menu.h"

int menu()
{
	int choice;
	do
	{
		system("pause");
		system("cls");
		cout << "*----------------展示查询系统界面----------------*\n\n\n" << endl;
		cout << "\t**********************************\n";
		cout << "\t*        学生养成查询系统        *\n";
		cout << "\t*================================*\n";
		cout << "\t*    1、范围查询学生属性值       *\n";
		cout << "\t*    2、查找学生所在宿舍号       *\n";
		cout << "\t*    3、查找宿舍入住学生名       *\n";
		cout << "\t*    4、查询学生恋爱史           *\n";
		cout << "\t*    5、查询恋爱次数最多学生     *\n";
		cout << "\t*    6、查询历任恋人魅力最高学生 *\n";
		cout << "\t*    0、退出管理系统             *\n";
		cout << "\t**********************************\n";
		cout << "\n\t请选择:";
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
				cout << "选择错误。" << endl;
				break;
		}
	} while (ch);
}