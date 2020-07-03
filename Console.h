#pragma once
#include"StudentCourse.h"
#include"StudentInfo.h"
using namespace std;
//该类的作用是将两个表格链接
class ConsolePlotform :public StudentCourse, public StudentInfo {
public:

	ConsolePlotform(string Filename1, string Filename2);
	//以学生id为关键字映射学生平均分
	map<int, double> Map_Id_AverScore;
	//以学生平均分为关键字映射学生id
	multimap<double, int> Map_AverScore_Id;
	//以学生已修学分为关键字映射学生id
	multimap<double, int> Map_TotalCredits_Id;
	//以总成绩为关键字映射学生学生id
	multimap<double, int> Map_TotalScore_Id;
	//以科目名为关键字映射学生单科成绩及学生信息
	map<string, multimap<double, Student>>Map_CourName_ScoreToInfo;

	//打印函数，print多义，要显式指明要调用哪个基类
	void print() {
		StudentInfo::print();
		StudentCourse::print();
	}
	//排序，其中set使用了基类的比较器
	set<Student, ComName> SortByName();
	set<Student, CompBirthday> SortByBirthday();
	set<Student, ComSchoolYear> SortBySchoolYear();
	multimap<double, Student> SortByTotal();
	multimap<double, Student> SortByAverage();
	set<Course, ComScore> SortByCourse(string);
	multimap<double, Student> SortByCredits();

	/*
	单条信息查询
	(_KeyName表示关键字的小写名，如"id"、"birthday")
	(_Key表示要查询的值或限定的范围，如"10905"、"<=2000/10/9")
	*/
	set<Student> FindStudent1
	(string _KeyName, string _Key);
	//两条信息查询
	set<Student> FindStudent2
	(string _KeyName1, string _Key1,
		string _KeyName2, string _Key2);
	//三条信息查询
	set<Student> FindStudent3
	(string _KeyName1, string _Key1,
		string _KeyName2, string _Key2,
		string _KeyName3, string _Key3);
	//删除学生，并返回学生信息（形参可以调用Find函数实现范围查询删除）
	set<Student> RemoveStudent(set<Student>);
};