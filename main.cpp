#include<iostream>
#include<fstream>
#include"StudentInfo.h"
#include"StudentCourse.h"
#include"Console.h"
ofstream out("D:/大一上学期/课程/程序设计/Visual Studio2010/C++/20200623/result.txt");
int main()
{
	void Test();
	Test();
}
void Test() {
	void print(Student Stu, ConsolePlotform Cons);
	string Filename1("D:/大一上学期/课程/程序设计/Visual Studio2010/C++/20200623/StudentInfo.txt"),
		Filename2("D:/大一上学期/课程/程序设计/Visual Studio2010/C++/20200623/StudentCourse.txt");
	ConsolePlotform console(Filename1, Filename2);
	console.print();
	if (out.is_open()) {
		out << endl;
		out << "/***查询2018级选修C语言且成绩小于60分的学生***/" << endl;
	}
	//查找符合条件的学生
	set<Student> List1 = console.FindStudent2
	("schoolyear", "2018", "C Programming Language", "<60");
	//联表打印
	for (auto memb : List1) {
		print(memb, console);
	}


	if (out.is_open()) {
		out << endl;
		out << "/***查询平均分大于80的学生***/" << endl;
	}
	//查找符合条件的学生
	set<Student> List2 = console.FindStudent1("averagescore", ">80");
	//联表打印
	for (auto memb : List2) {
		print(memb, console);
	}

	if (out.is_open()) {
		out << endl;
		out << "/***查询已修学分超过12分的同学***/" << endl;
	}
	//查找符合条件的学生
	set<Student> List3 = console.FindStudent1("totalcredits", ">12");
	for (auto memb : List3) {
		print(memb, console);
	}
	out.close();
}
//打印函数
void print(Student Stu, ConsolePlotform Cons) {
	if (out.is_open()) {
		//第一行
		out << left
			<< setw(6) << "#Id"
			<< setw(9) << "Name"
			<< setw(7) << "Sex"
			<< setw(11) << "Birthday"
			<< setw(12) << "SchoolYear"
			<< setw(12) << "Birthplace" << endl;
		//打印信息
		out << left << setw(6) << Stu.GetStuId()
			<< setw(9) << Stu.GetStuName();
		if (Stu.GetStuSex() == 0)
			out << left << setw(7) << "Female";
		else
			out << left << setw(7) << "Male";
		out << setw(4) << Stu.GetStuBirthday().GetYear() << '/'
			<< setw(2) << Stu.GetStuBirthday().GetMonth() << '/'
			<< setw(3) << Stu.GetStuBirthday().GetDay();
		out << left << setw(12) << Stu.GetStuSchoolYear()
			<< left << setw(12) << Stu.GetStuBirthplace() << endl;
	}
}