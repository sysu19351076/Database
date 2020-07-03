#pragma once
#include<iostream>
#include<string>
#include<iomanip>
#include<map>
#include<set>
using namespace std;
class Date {
private:
	int mYear;
	int mMonth;
	int mDay;
public:
	Date(int aYear = 0, int aMonth = 0, int aDay = 0) :
		mYear(aYear), mMonth(aMonth), mDay(aDay) {}
	~Date() {}
	//设置年月日
	void SetYear(const int& aYear) {
		mYear = aYear;
	}
	void SetMonth(const int& aMonth) {
		mMonth = aMonth;
	}
	void SetDay(const int& aDay) {
		mDay = aDay;
	}
	//返回年月日
	int GetYear()const {
		return mYear;
	}
	int GetMonth()const {
		return mMonth;
	}
	int GetDay()const {
		return mDay;
	}
	//重载运算符,实现日期的比较
	bool operator<(const Date&AnotherDate)const {
		if (this->mYear < AnotherDate.mYear)
			return true;
		else if (this->mYear > AnotherDate.mYear)
			return false;
		else
		{
			if (this->mMonth < AnotherDate.mMonth)
				return true;
			else if (this->mMonth > AnotherDate.mMonth)
				return false;
			else
			{
				if (this->mDay < AnotherDate.mDay)
					return true;
				else
					return false;
			}
		}
	}
	bool operator==(const Date&AnotherDate)const
	{
		if (this->mYear == AnotherDate.mYear)
		{
			if (this->mMonth == AnotherDate.mMonth)
			{
				if (this->mDay == AnotherDate.mDay)
				{
					return true;
				}
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;
	}
	bool operator!=(const Date&AnotherDate)const
	{
		if (this->mYear == AnotherDate.mYear)
		{
			if (this->mMonth == AnotherDate.mMonth)
			{
				if (this->mDay == AnotherDate.mDay)
				{
					return false;
				}
				else
					return true;
			}
			else
				return true;
		}
		else
			return true;
	}

	void DatePrint()const {
		cout << setw(4) << mYear << '/'
			<< setw(2) << mMonth << '/'
			<< setw(3) << mDay;
	}
};

class Student {
private:
	int mId;
	string mName;
	//0为男，1为女
	bool mSex;
	Date mBirthday;
	int mSchoolYear;
	string mBirthplace;
public:
	//重载运算符，以便set排序时，有元素比较的方法
	bool operator<(const Student& AnotherStu) const {
		return mId < AnotherStu.mId;
	}
	//学生的构造函数
	Student() {};
	Student(int aId, string aName, bool aSex,
		int aYear, int aMonth, int aDay,
		int aSchoolYear, string aBirthplace) :
		mId(aId), mName(aName), mSex(aSex),
		mBirthday(aYear, aMonth, aDay),
		mSchoolYear(aSchoolYear), mBirthplace(aBirthplace) {}
	~Student() {}
	//打印一个学生的信息
	void StuPrint()const {
		cout << left << setw(6) << mId
			<< setw(9) << mName;
		if (mSex == 0)
			cout << left << setw(7) << "Female";
		else
			cout << left << setw(7) << "Male";
		mBirthday.DatePrint();
		cout << left << setw(12) << mSchoolYear
			<< left << setw(12) << mBirthplace << endl;
	}
	//返回一个学生的属性
	int GetStuId()const {
		return mId;
	}
	string GetStuName() const {
		return mName;
	}
	bool GetStuSex()const {
		return mSex;
	}
	Date GetStuBirthday()const {
		return mBirthday;
	}
	int GetStuSchoolYear() {
		return mSchoolYear;
	}
	string GetStuBirthplace() {
		return mBirthplace;
	}
};

class StudentInfo {
	friend class Student;
public:
	//定义严格弱序，由于Id唯一，每条路径都有返回值
	struct CompBirthday {
		bool operator()(class Student left, class Student right)
		{
			if (left.GetStuBirthday() != right.GetStuBirthday())
				return left.GetStuBirthday() < right.GetStuBirthday();
			else
				return left.GetStuId() < right.GetStuId();
		}
	};
	struct ComName {
		bool operator()(class Student left, class Student right) {
			if (left.GetStuName() != right.GetStuName())
				return left.GetStuName() < right.GetStuName();
			else
				return left.GetStuId() < right.GetStuId();
		}
	};
	struct ComSchoolYear {
		bool operator()(class Student left, class Student right) {
			if (left.GetStuSchoolYear() != right.GetStuSchoolYear())
				return left.GetStuSchoolYear() < right.GetStuSchoolYear();
			else return left.GetStuId() < right.GetStuId();
		}
	};

	//名单
	set<Student> Set_StuInfo;

	//以Id为关键字映射学生
	map<int, Student> Map_Id_Student;

	//以Name为关键字映射学生
	map<string, set<Student>> Map_Name_Student;

	//以Date为关键字映射学生
	map<Date, set<Student>> Map_Date_Student;

	//以Sex为关键字映射学生
	map<bool, set<Student>>Map_Sex_Student;

	//以SchoolYear为关键字映射学生
	map<int, set<Student>> Map_SchoolYear_Student;

	//以Birthplace为关键字映射学生
	map<string, set<Student>> Map_Birthplace_Student;

	//构造函数
	StudentInfo(string FileName);

	void print()
	{
		cout << left
			<< setw(6) << "#Id"
			<< setw(9) << "Name"
			<< setw(7) << "Sex"
			<< setw(11) << "Birthday"
			<< setw(12) << "SchoolYear"
			<< setw(12) << "Birthplace" << endl;
		for (auto memb : Map_Id_Student)
		{
			memb.second.StuPrint();
		}
	}
};