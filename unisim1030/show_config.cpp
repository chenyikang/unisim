#include"student_info.h"

using std::cout; using std::endl;

void show_config(const map<string, double>config, const map<string, string>formula)
{
	for (const auto&w : config)				//�õ�������ʾconfig���е�������Ϣ
	{
		cout << w.first << "==" << w.second << endl;	
	}
	for (const auto&w : formula)			//�õ�������ʾformula���е�������Ϣ
	{
		cout << w.first << "==" << w.second << endl;
	}
}