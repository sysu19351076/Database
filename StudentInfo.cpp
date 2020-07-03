#include"StudentInfo.h"
#include<fstream>
#include<sstream>
//���캯��
StudentInfo::StudentInfo(string FileName) {
	ifstream File(FileName);
	if (File) {
		string line;
		while (getline(File, line))
		{
			//������һ��
			if (line[0] == '#')
				continue;
			istringstream text(line);
			string words[6];
			for (int i = 0; i < 6; i++) {
				text >> words[i];
			}
			//����Ѱ�Ҳ���ֵѧ��������
			int id = stoi(words[0]);
			string name = words[1];
			bool sex;
			if (words[2] == "Male")
				sex = 0;
			else
				sex = 1;
			string syear, smonth, sday;
			syear = words[3].substr(words[3].find_first_of('/') - 4, 4);
			smonth = words[3].substr(words[3].find_first_of('/') + 1,
				words[3].find_last_of('/') - words[3].find_first_of('/') - 1);
			sday = words[3].substr(words[3].find_last_of('/') + 1, 2);
			int year, month, day;
			year = stoi(syear);
			month = stoi(smonth);
			day = stoi(sday);
			Date birthday(year, month, day);
			int school_year = stoi(words[4]);
			string birthplace = words[5];
			//ʹ����������������һ��Student
			Student Stu(id, name, sex,
				year, month, day,
				school_year, birthplace);
			Set_StuInfo.insert(Stu);
			//��IdΪ�ؼ��ִ���ѧ����Ϣ
			Map_Id_Student.insert({ Stu.GetStuId(),Stu });
			//��NameΪ�ؼ��ִ���ѧ����Ϣ
			Map_Name_Student[name].insert(Stu);
			//��SexΪ�ؼ��ִ���ѧ����Ϣ
			Map_Sex_Student[sex].insert(Stu);
			//��DateΪ�ؼ��ִ���ѧ����Ϣ
			Map_Date_Student[birthday].insert(Stu);
			//��SchoolYearΪ�ؼ��ִ���ѧ����Ϣ
			Map_SchoolYear_Student[school_year].insert(Stu);
			//��BirthplaceΪ�ؼ��ִ���ѧ����Ϣ
			Map_Birthplace_Student[birthplace].insert(Stu);
		}
	}
}