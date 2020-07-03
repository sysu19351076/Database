#pragma once
#include"StudentCourse.h"
#include"StudentInfo.h"
using namespace std;
//����������ǽ������������
class ConsolePlotform :public StudentCourse, public StudentInfo {
public:

	ConsolePlotform(string Filename1, string Filename2);
	//��ѧ��idΪ�ؼ���ӳ��ѧ��ƽ����
	map<int, double> Map_Id_AverScore;
	//��ѧ��ƽ����Ϊ�ؼ���ӳ��ѧ��id
	multimap<double, int> Map_AverScore_Id;
	//��ѧ������ѧ��Ϊ�ؼ���ӳ��ѧ��id
	multimap<double, int> Map_TotalCredits_Id;
	//���ܳɼ�Ϊ�ؼ���ӳ��ѧ��ѧ��id
	multimap<double, int> Map_TotalScore_Id;
	//�Կ�Ŀ��Ϊ�ؼ���ӳ��ѧ�����Ƴɼ���ѧ����Ϣ
	map<string, multimap<double, Student>>Map_CourName_ScoreToInfo;

	//��ӡ������print���壬Ҫ��ʽָ��Ҫ�����ĸ�����
	void print() {
		StudentInfo::print();
		StudentCourse::print();
	}
	//��������setʹ���˻���ıȽ���
	set<Student, ComName> SortByName();
	set<Student, CompBirthday> SortByBirthday();
	set<Student, ComSchoolYear> SortBySchoolYear();
	multimap<double, Student> SortByTotal();
	multimap<double, Student> SortByAverage();
	set<Course, ComScore> SortByCourse(string);
	multimap<double, Student> SortByCredits();

	/*
	������Ϣ��ѯ
	(_KeyName��ʾ�ؼ��ֵ�Сд������"id"��"birthday")
	(_Key��ʾҪ��ѯ��ֵ���޶��ķ�Χ����"10905"��"<=2000/10/9")
	*/
	set<Student> FindStudent1
	(string _KeyName, string _Key);
	//������Ϣ��ѯ
	set<Student> FindStudent2
	(string _KeyName1, string _Key1,
		string _KeyName2, string _Key2);
	//������Ϣ��ѯ
	set<Student> FindStudent3
	(string _KeyName1, string _Key1,
		string _KeyName2, string _Key2,
		string _KeyName3, string _Key3);
	//ɾ��ѧ����������ѧ����Ϣ���βο��Ե���Find����ʵ�ַ�Χ��ѯɾ����
	set<Student> RemoveStudent(set<Student>);
};