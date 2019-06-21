#include<iostream>
#include<fstream>
#include "student_info.h"
#include "menu.h"

using std::cout; using std::endl; using std::ifstream; using std::setw; using std::setfill; using std::cerr;
using std::ofstream;

map<string, double> config;							//存储配置信息的关联容器（关键字：配置名字 值：配置值）
map<string, string> formula;						//存储配置公式的关联容器（关键字：配置公式名字 值：配置公式）
map<string, common> students;					//存储在读学生信息的关联容器（关键字：学生名字 值：学生信息结构）
map<string, common> del_students;				//存储退学学生信息的关联容器（关键字：学生名字 值：学生信息结构）
map<string, map<string, int>> students_woo_times;	//存储在恋爱学生被求爱的次数的关联容器（关键字：学生名字 值：被求爱次数）

int main()
{

	cout << "*------------------------Welcome to Unisim.--------------------------*" << endl;
	/*------------------------初始化定义----------------------------------*/	
	ifstream in;
	ofstream out;
	string file;
	vector<string> instructions;						//存储指令的顺序容器
	/*------------------------读取配置信息文件----------------------------*/
	cout << "*------------------------读取配置信息文件----------------------------*" << endl;
	cout << "开始读取配置文件信息" << endl;
	in.open("sample_config.txt");
	if (in)
	{
		read_config(in);				//读取配置函数
		cout << "读取成功" << endl;
	}
	else
	{
		cerr << "打开配置文件失败" << endl;
	}
	in.close();

	show_config(config, formula);						//显示配置函数
	/*------------------------读取宿舍信息文件并初始化----------------------------*/
	cout << "*------------------------读取宿舍信息文件并初始化--------------------*" << endl;

	vector<floor_info> dorm(config["FLOOR"]+1, floor_info(config["ROOM"]+1));

	cout << "开始读取宿舍配置信息" << endl;
	in.open("dispatch.txt");
	if (in)
	{
		read_dispatch(in, dorm);				//读取宿舍函数
		cout << "读取成功" << endl;
	}
	else
	{
		cerr << "打开宿舍配置文件失败" << endl;
	}
	in.close();

	show_dorm(cout, dorm);							//显示宿舍函数


	/*------------------------读取指令信息文件并执行----------------------------*/
	cout << "*------------------------读取指令信息文件并显示----------------------*" << endl;
	cout << "开始读取指令信息" << endl;
	open:
	cout << "请输入要读取的指令文件：" ;
	cin >> file;
	in.open(file);
	if (in)
	{
		read_show_instructions(in, dorm);				//读取并显示指令函数
		cout << "读取成功" << endl;
	}
	else
	{
		cerr << "打开指令文件失败" << endl;
		goto open;
	}
	in.close();

	/*------------------------保存学生信息文件----------------------------*/
	cout << "*------------------------保存学生信息文件----------------------------*" << endl;

	out.open(formula["SAVE_FILE_NAME"]);
	if (out)
	{
		show_students(out);
		cout << "保存成功" << endl;
	}
	else
	{
		cerr << "打开文件失败" << endl;
	}
	out.close();

	/*------------------------展示查询系统界面----------------------------*/
	
	display_menu();
}