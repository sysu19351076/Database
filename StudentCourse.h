#pragma once
#include<iostream>
#include<string>
#include<iomanip>
#include<map>
#include<set>
#include"StudentInfo.h"
using namespace std;
//此类为一行成绩
class Course {
private:
	int mId;
	string mCourse;
	double mCredits;
	double mScore;
	//用于判断是否能否获得学分
	bool mCanGet;
public:
	Course() {}
	Course(int aId, string aCourse, double aCredits, double aScore) :
		mId(aId), mCourse(aCourse), mCredits(aCredits), mScore(aScore) {
		//判断是否能否获得学分
		if (aScore >= 60)
			mCanGet = 1;
		else
			mCanGet = 0;
	}
	~Course() {}
	//重载运算符，以便set排序时，有元素比较的方法
	bool operator < (const Course&AnotherCour) const {
		if (mCourse != AnotherCour.GetCourName())
			return mCourse < AnotherCour.GetCourName();
		else
			return mId < AnotherCour.GetCourId();
	}
	//获得一行成绩的属性
	int GetCourId() const {
		return mId;
	}
	string GetCourName() const {
		return mCourse;
	}
	double GetCourCredit()const {
		return mCredits;
	}
	double GetCourScore()const {
		return mScore;
	}
	bool CanGetCredits()const {
		return mCanGet;
	}
	void CourPrint() const {
		cout << left
			<< setw(6) << mId
			<< setw(23) << mCourse
			<< setw(9) << mCredits
			<< setw(7) << mScore << endl;
	}
};

class StudentCourse {
	friend class Course;
public:
	//定义严格弱序，由于Id唯一，每条路径都有返回值
	struct ComScore {
		bool operator()(class Course left, class Course right) {
			if (left.GetCourScore() != right.GetCourScore())
				return left.GetCourScore() < right.GetCourScore();
			else if (left.GetCourId() != right.GetCourId())
				return left.GetCourId() < right.GetCourId();
			else
				return (left.GetCourId() < right.GetCourId());
		}
	};
	StudentCourse(string FileName);

	//成绩单
	set<Course>Set_Course;

	//以学生为关键字映射成绩单（以Score为比较器）
	map<Student, set<Course, ComScore>>Map_Stu_StuCour;
	//以科目名为关键字映射成绩单（以Score为比较器）
	map<string, set<Course, ComScore>>Map_CourName_StuCour;
	//以学生id为关键字映射学生总成绩
	map<int, double>Map_Id_TotalScore;
	//以学生id为关键字映射学生平均分
	map<int, double> Map_Id_AverScore;
	//以学生id为关键字映射学生已修学分
	map<int, double> Map_Id_TotalCredits;
	void print()const {
		cout << left
			<< setw(6) << "#Id"
			<< setw(23) << "Course"
			<< setw(9) << "Credits"
			<< setw(7) << "Score" << endl;
		for (auto memb : Set_Course)
		{
			memb.CourPrint();
		}
	}
};