#pragma once
#ifndef GUARD_QUERY
#define GUARD_QUERY

#include<iostream>
#include<algorithm>
#include<iomanip>
#include"student_info.h"

using std::cout; using std::cin; using std::ostream; using std::map; using std::endl; 
using std::sort; using std::setw; using std::setfill;

void query_state_ch();
void query_charm(ostream& out, int begin, int end, string sex);
void query_money(ostream& out, int begin, int end, string sex);
void query_weight(ostream& out, int begin, int end, string sex);
void query_knowledge(ostream& out, int begin, int end, string sex);
void query_dorm(ostream& out);
void query_stu(ostream& out);
void query_lover_ch(ostream& out);
void query_lover_most(ostream& out);
void query_lover_charm(ostream& out);

#endif