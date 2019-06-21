#include "student_info.h"

using std::istream; using std::getline; using std::istringstream;

extern map<string, string> formula;
extern map<string, double> config;

istream& read_config(istream& is)
{
	string line;
	string config_name;
	while (is && getline(is, line))
	{
		if (line.substr(0,2)=="//" || line.empty())							//忽略"//"开头的行和空行								
		{
			continue;
		}
		else
		{
			auto pos=line.find_first_of(":：");								//在一行中能否找到'：'或':'  
			if (pos != string::npos)										//找到的话，就读进config关联容器中
			{
				//SAVE_FILE_NAME: GAME.SAV 特殊情况':'后面是字符串，暂时存进formula
				if (line.substr(0, pos) == "SAVE_FILE_NAME")
					formula[line.substr(0, pos)] = line.substr(pos + 1, line.size());
				else
					//关键字是pos前面的字符串，值是pos后面的字符串，用atof将后面的字符串转化为float
					config[line.substr(0, pos)] = atof(((line.substr(pos + 1, line.size()))).c_str());
			}

			pos = line.find_first_of("=");									//在一行中能否找到'='
			if (pos != string::npos)										//找到的话，就读进formula关联容器中
			{
				//关键字是pos前面的字符串，值是pos后面的字符串
				formula[line.substr(0, pos - 1)] = line.substr(pos + 1, line.size());
			}
		}
	}

	return is;
}
