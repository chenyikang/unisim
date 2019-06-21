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
		if (line.substr(0,2)=="//" || line.empty())							//����"//"��ͷ���кͿ���								
		{
			continue;
		}
		else
		{
			auto pos=line.find_first_of(":��");								//��һ�����ܷ��ҵ�'��'��':'  
			if (pos != string::npos)										//�ҵ��Ļ����Ͷ���config����������
			{
				//SAVE_FILE_NAME: GAME.SAV �������':'�������ַ�������ʱ���formula
				if (line.substr(0, pos) == "SAVE_FILE_NAME")
					formula[line.substr(0, pos)] = line.substr(pos + 1, line.size());
				else
					//�ؼ�����posǰ����ַ�����ֵ��pos������ַ�������atof��������ַ���ת��Ϊfloat
					config[line.substr(0, pos)] = atof(((line.substr(pos + 1, line.size()))).c_str());
			}

			pos = line.find_first_of("=");									//��һ�����ܷ��ҵ�'='
			if (pos != string::npos)										//�ҵ��Ļ����Ͷ���formula����������
			{
				//�ؼ�����posǰ����ַ�����ֵ��pos������ַ���
				formula[line.substr(0, pos - 1)] = line.substr(pos + 1, line.size());
			}
		}
	}

	return is;
}
