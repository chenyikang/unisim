#include"student_info.h"
#include"exprtk.hpp"
#define SCL_SECURE_NO_WARNINGS

using std::cout; using std::endl;

extern map<string, string> formula;
extern map<string, double> config;

int common::expression(double food_taken, double study_time, double work_time)
{
	typedef exprtk::symbol_table<double> symbol_table_t;
	typedef exprtk::expression<double>     expression_t;
	typedef exprtk::parser<double>             parser_t;

	//��formula��ȡ��WEIGHT_INC,MONEY_INC,CHARM_INC,KNOWLEDGE_INC���ĸ���ʽ���ַ���m
	std::string expression_weight = formula["WEIGHT_INC"];					
	std::string expression_money = formula["MONEY_INC"];
	std::string expression_charm = formula["CHARM_INC"];
	std::string expression_knowledge = formula["KNOWLEDGE_INC"];

	//������������ӹ�ʽ�г��ֵı���
	symbol_table_t symbol_table;
	symbol_table.add_variable("FOOD_TAKEN",food_taken);
	symbol_table.add_variable("FOOD_WEIGHT", config["FOOD_WEIGHT"]);
	symbol_table.add_variable("STUDY_TIME", study_time);
	symbol_table.add_variable("STUDY_WEIGHT", config["STUDY_WEIGHT"]);
	symbol_table.add_variable("WORK_TIME", work_time);
	symbol_table.add_variable("WORK_WEIGHT", config["WORK_WEIGHT"]);
	symbol_table.add_variable("WORK_MONEY", config["WORK_MONEY"]);
	symbol_table.add_variable("FOOD_COST", config["FOOD_COST"]);
	symbol_table.add_variable("STUDY_KNOWLEDGE", config["STUDY_KNOWLEDGE"]);
	symbol_table.add_constants();

	//�ѱ�����ע�ᵽ��ʽ��
	expression_t expression_weight_inc;
	expression_t expression_money_inc;
	expression_t expression_charm_inc;
	expression_t expression_knowledge_inc;
	expression_weight_inc.register_symbol_table(symbol_table);
	expression_money_inc.register_symbol_table(symbol_table);
	expression_knowledge_inc.register_symbol_table(symbol_table);

	//���������빫ʽ
	parser_t parser;
	parser.compile(expression_weight, expression_weight_inc);
	parser.compile(expression_money, expression_money_inc);
	parser.compile(expression_knowledge, expression_knowledge_inc);

	//��������double���洢knowledge_inc��weight_inc��ʽ��ֵ
	double knowledge_inc=expression_knowledge_inc.value();
	double weight_inc=expression_weight_inc.value();

	//��ӵ���������
	symbol_table.add_variable("KNOWLEDGE_INC", knowledge_inc);
	symbol_table.add_variable("WEIGHT_INC", weight_inc);
	
	//ע�����������������
	expression_charm_inc.register_symbol_table(symbol_table);
	parser.compile(expression_charm, expression_charm_inc);

	//���ʹweight��money,knowledge,charmΪ����,��study/work/eatָ����Ч
	if (stu_weight + expression_weight_inc.value() < 0 ||
		stu_money + expression_money_inc.value() < 0 ||
		stu_knowledge + expression_knowledge_inc.value() < 0 ||
		stu_charm + expression_charm_inc.value() < 0)
	{
		return 0;
	}
	else
	{
		stu_weight += expression_weight_inc.value();				//�������ӹ�ʽ
		stu_money += expression_money_inc.value();					//��Ǯ���ӹ�ʽ
		stu_knowledge += expression_knowledge_inc.value();			//֪ʶ���ӹ�ʽ
		stu_charm += expression_charm_inc.value();					//�������ӹ�ʽ
		return 1;
	}

}