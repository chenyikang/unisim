#include"student_info.h"

using std::cout; using std::endl;

void show_config(const map<string, double>config, const map<string, string>formula)
{
	for (const auto&w : config)				//用迭代器显示config所有的配置信息
	{
		cout << w.first << "==" << w.second << endl;	
	}
	for (const auto&w : formula)			//用迭代器显示formula所有的配置信息
	{
		cout << w.first << "==" << w.second << endl;
	}
}