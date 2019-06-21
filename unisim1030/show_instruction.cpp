#include"student_info.h"

using std::cout; using std::endl;

void show_instruction(const vector<vector<string>> instructions)
{
	int k = 1;
	for (auto i = instructions.begin(); i != instructions.end(); i++)
	{
		for (auto j = (*i).begin(); j != (*i).end(); j++)
		{
			if (j == (*i).begin())
			{
				cout << "ЦёБо" << k << ": ";
			}
			cout << *j <<" ";
			if (j == (*i).end()-1)
			{
				cout << endl;
			}
		}
		k++;
	}
}