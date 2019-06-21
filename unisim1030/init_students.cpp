#include"student_info.h"

extern map<string, student_info> students;
extern map<string, double> config;

void init_students()
{
	for (auto map_it = students.begin(); map_it != students.end(); map_it++)
	{
		map_it->second.money = config["MONEY"];				//初始化money
		map_it->second.charm = config["CHARM"];				//初始化charm
		map_it->second.knowledge = config["KNOWLEDGE"];		//初始化knowledge
		map_it->second.weight = config["WEIGHT"];			//初始化weight
		map_it->second.islove = 0;
	}
}