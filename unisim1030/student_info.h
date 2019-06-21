#ifndef GUARD_student_info
#define GUARD_student_info

//student_info.h
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <iomanip>
#include <map>

using std::istream; using std::string; using std::vector; using std::map; using std::ostream;

//房间，楼层，宿舍信息结构
//vector<floor_info>代表一个宿舍结构
typedef vector<string> room_info;			//room_info代表一个房间结构
typedef vector<room_info> floor_info;		//floor_info代表一个楼层结构

//学生个体信息结构
//class student_info {
//public:
//	//构造、复制、析构、赋值
//	student_info() : cp(0) { }
//	student_info(std::istream& is) : cp(0) { read(is); }
//	student_info(const student_info&);
//	student_info& operator=(const student_info&);
//	~student_info() { delete cp; }
//
//	// 操作
//	istream& read(istream&);
//
//	string name() const {
//		if (cp) return this->name();
//		else throw std::runtime_error("uninitialized Student");
//	}
//	string sex() const {
//		if (cp) return this->sex();
//		else throw std::runtime_error("uninitialized Student");
//	}
//
//	int inschool() const {
//		if (cp) return cp->inschool();
//		else throw std::runtime_error("uninitialized Student");
//	}
//	int floor_num() const {
//		if (cp) return cp->floor_num();
//		else throw std::runtime_error("uninitialized Student");
//	}
//	int room_num() const {
//		if (cp) return cp->room_num();
//		else throw std::runtime_error("uninitialized Student");
//	}
//
//	double charm() const {
//		if (cp) return cp->charm();
//		else throw std::runtime_error("uninitialized Student");
//	}
//	double weight() const {
//		if (cp) return cp->weight();
//		else throw std::runtime_error("uninitialized Student");
//	}
//	double money() const {
//		if (cp) return cp->weight();
//		else throw std::runtime_error("uninitialized Student");
//	}
//	double knowledge() const {
//		if (cp) return cp->weight();
//		else throw std::runtime_error("uninitialized Student");
//	}
//
//	int expression(double a, double b, double c) const {
//		if (cp) return cp->expression(a, b, c);
//		else throw std::runtime_error("uninitialized Student");
//	}
//private:
//	common* cp;
//};


// common

class common {
//	friend class student_info;
	friend void state(vector<string>&);
	friend void move(vector<floor_info>&, vector<string>&);
	friend void read_room(string, int&, int&);
	friend void enrol(vector<floor_info>&, vector<string>&);
	friend void add_floor(vector<floor_info>&, int);
	friend void woo(vector<string>&);
	friend void breakup(vector<string>&);
	friend istream& read_dispatch(istream&, vector<floor_info>&);
	
public:
	//只读取此学生的信息
	string name() const { return stu_name; };   
	string sex() const { return stu_sex; };

	int inschool() const { return stu_inschool; };
	int floor_num() const { return stu_floor_num; };
	int room_num() const { return stu_room_num; };

	double charm() const { return stu_charm; };
	double weight() const { return stu_weight; };
	double money() const { return stu_money; };
	double knowledge() const { return stu_knowledge; };

	int islove() const { return stu_islove; };
	vector<string> lover() const { return stu_lover; };

	//学生信息读取函数
	istream& read(istream&);
	istream& read_common(istream&);
	istream& read_lover(istream&);

	//操作
	int expression(double, double, double);
protected:
	virtual common* clone() const { return new common(*this); }

	double stu_charm;
	double stu_weight;
	double stu_money;
	double stu_knowledge;
private:
	string stu_name;  //姓名放在句柄类中，不需要了
	string stu_sex;

	int stu_inschool;
	int stu_floor_num;
	int stu_room_num;

	int stu_islove;
	vector<string> stu_lover;
};



//派生类:男

class male :public common {
public:
	male(istream& is) { read(is); }

	istream& read(istream&);
private:
	double stu_health;
	male* clone() const { return new male(*this); }
};



//派生类:女

class female :public common {
public:
	female(istream& is) { read(is); }

	istream& read(istream&);
private:
	double stu_looks;
	female* clone() const { return new female(*this); }
};


istream& read_config(istream&);
int read_instruction(istream&, vector<string>&);

ostream& show_student(ostream& out, const common);
ostream& show_dorm(ostream&, vector<floor_info>&);
ostream& show_students(ostream&);

void show_config(const map<string, double>, const map<string, string>);

void add(vector<floor_info>&, int, string, int, string);
istream& read_show_instructions(istream&, vector<floor_info>& dorm);

#endif