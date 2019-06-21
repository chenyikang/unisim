#include"student_info.h"

extern map<string, student_info> students;
extern map<string, double> config;

void init_students()
{
	for (auto map_it = students.begin(); map_it != students.end(); map_it++)
	{
		map_it->second.money = config["MONEY"];				//��ʼ��money
		map_it->second.charm = config["CHARM"];				//��ʼ��charm
		map_it->second.knowledge = config["KNOWLEDGE"];		//��ʼ��knowledge
		map_it->second.weight = config["WEIGHT"];			//��ʼ��weight
		map_it->second.islove = 0;
	}
}