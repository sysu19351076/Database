#include"StudentInfo.h"
#include<fstream>
#include<sstream>
//构造函数
StudentInfo::StudentInfo(string FileName) {
	ifstream File(FileName);
	if (File) {
		string line;
		while (getline(File, line))
		{
			//跳过第一行
			if (line[0] == '#')
				continue;
			istringstream text(line);
			string words[6];
			for (int i = 0; i < 6; i++) {
				text >> words[i];
			}
			//依次寻找并赋值学生的属性
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
			//使用以上数据来构造一个Student
			Student Stu(id, name, sex,
				year, month, day,
				school_year, birthplace);
			Set_StuInfo.insert(Stu);
			//以Id为关键字储存学生信息
			Map_Id_Student.insert({ Stu.GetStuId(),Stu });
			//以Name为关键字储存学生信息
			Map_Name_Student[name].insert(Stu);
			//以Sex为关键字储存学生信息
			Map_Sex_Student[sex].insert(Stu);
			//以Date为关键字储存学生信息
			Map_Date_Student[birthday].insert(Stu);
			//以SchoolYear为关键字储存学生信息
			Map_SchoolYear_Student[school_year].insert(Stu);
			//以Birthplace为关键字储存学生信息
			Map_Birthplace_Student[birthplace].insert(Stu);
		}
	}
}