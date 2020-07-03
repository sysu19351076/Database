#pragma once
#include<iostream>
#include<string>
#include<iomanip>
#include<map>
#include<set>
#include"StudentInfo.h"
using namespace std;
//����Ϊһ�гɼ�
class Course {
private:
	int mId;
	string mCourse;
	double mCredits;
	double mScore;
	//�����ж��Ƿ��ܷ���ѧ��
	bool mCanGet;
public:
	Course() {}
	Course(int aId, string aCourse, double aCredits, double aScore) :
		mId(aId), mCourse(aCourse), mCredits(aCredits), mScore(aScore) {
		//�ж��Ƿ��ܷ���ѧ��
		if (aScore >= 60)
			mCanGet = 1;
		else
			mCanGet = 0;
	}
	~Course() {}
	//������������Ա�set����ʱ����Ԫ�رȽϵķ���
	bool operator < (const Course&AnotherCour) const {
		if (mCourse != AnotherCour.GetCourName())
			return mCourse < AnotherCour.GetCourName();
		else
			return mId < AnotherCour.GetCourId();
	}
	//���һ�гɼ�������
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
	//�����ϸ���������IdΨһ��ÿ��·�����з���ֵ
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

	//�ɼ���
	set<Course>Set_Course;

	//��ѧ��Ϊ�ؼ���ӳ��ɼ�������ScoreΪ�Ƚ�����
	map<Student, set<Course, ComScore>>Map_Stu_StuCour;
	//�Կ�Ŀ��Ϊ�ؼ���ӳ��ɼ�������ScoreΪ�Ƚ�����
	map<string, set<Course, ComScore>>Map_CourName_StuCour;
	//��ѧ��idΪ�ؼ���ӳ��ѧ���ܳɼ�
	map<int, double>Map_Id_TotalScore;
	//��ѧ��idΪ�ؼ���ӳ��ѧ��ƽ����
	map<int, double> Map_Id_AverScore;
	//��ѧ��idΪ�ؼ���ӳ��ѧ������ѧ��
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