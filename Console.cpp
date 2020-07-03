#include"Console.h"
#include<algorithm>
#include<iterator>
#include<cctype>
/*
��Ϣ����̨�Ĺ��캯��
���˳�ʼ�������Map�⣬����Ҫ��ʼ�������޷�ʵ�ֵ�Map
�����Map����Ԫ��һ�㶼��������ͬ�����pair��
������Ҫ������ͳ�Ƶ�����
����ƽ���֣���ΪPython���ſ�ֻ�в�����ѡ����Ҫ�����ʼ�������鿴course��size��
*/
ConsolePlotform::ConsolePlotform(string Filename1, string Filename2) :
	StudentInfo(Filename1), StudentCourse(Filename2)
{
	for (auto memb : Set_Course)
		//��ѧ��Ϊ�ؼ��ִ洢ѧ���ɼ���
		Map_Stu_StuCour[Map_Id_Student[memb.GetCourId()]].insert(memb);
	for (auto memb : Set_Course) {
		//�Կ�Ŀ��Ϊ�ؼ��ִ洢ѧ�����Ƴɼ���ѧ����Ϣ
		Map_CourName_ScoreToInfo[memb.GetCourName()].insert
		({ memb.GetCourScore(),Map_Id_Student[memb.GetCourId()] });
		//���ܳɼ�Ϊ�ؼ���ӳ��ѧ��ѧ��id
		Map_TotalScore_Id.insert
		({ Map_Id_TotalScore[memb.GetCourId()],memb.GetCourId() });
		//��ѧ��idΪ�ؼ���ӳ��ѧ��ƽ����
		Map_Id_AverScore[memb.GetCourId()] =
			(double)Map_Id_TotalScore[memb.GetCourId()] /(double)
			(Map_Stu_StuCour[Map_Id_Student[memb.GetCourId()]].size());
		//��ѧ��ƽ����Ϊ�ؼ���ӳ��ѧ��id
		Map_AverScore_Id.insert
		({ Map_Id_AverScore[memb.GetCourId()] ,memb.GetCourId() });
		//��ѧ������ѧ��Ϊ�ؼ���ӳ��ѧ��id
		Map_TotalCredits_Id.insert
		({ Map_Id_TotalCredits[memb.GetCourId()],memb.GetCourId() });
	}
}

//ɾ����������������ͨ������Findϵ�к���ʵ�ַ�Χɾ����
set<Student> ConsolePlotform::RemoveStudent(set<Student> aSet_Target) {
	for (auto memb : aSet_Target) {
		Set_StuInfo.erase(memb);
	}
	return aSet_Target;
}

//������
set<Student, ConsolePlotform::ComName>
ConsolePlotform::SortByName() {
	set<Student, ComName> Temp(Set_StuInfo.begin(), Set_StuInfo.end());
	return Temp;
}

set<Student, ConsolePlotform::CompBirthday>
ConsolePlotform::SortByBirthday() {
	set<Student, CompBirthday> Temp(Set_StuInfo.begin(), Set_StuInfo.end());
	return Temp;
}

set<Student, ConsolePlotform::ComSchoolYear>
ConsolePlotform::SortBySchoolYear() {
	set<Student, ComSchoolYear> Temp(Set_StuInfo.begin(), Set_StuInfo.end());
	return Temp;
}

multimap<double, Student>
ConsolePlotform::SortByTotal() {
	multimap<double, Student> Temp;
	for (auto memb : Map_Id_TotalScore) {
		Temp.insert({ memb.second,Map_Id_Student[memb.first] });
	}
	return Temp;
}

multimap<double, Student>
ConsolePlotform::SortByAverage() {
	multimap<double, Student> Temp;
	for (auto memb : Map_Id_TotalScore) {
		//�ܳɼ�����Ŀ��ƽ����
		Temp.insert
		({ memb.second / (double)Map_Stu_StuCour[Map_Id_Student[memb.first]].size(),
			Map_Id_Student[memb.first] });
	}
	return Temp;
}

set<Course, ConsolePlotform::ComScore>
ConsolePlotform::SortByCourse(string course) {
	if (Map_CourName_ScoreToInfo.count(course))
		return Map_CourName_StuCour[course];
	else {
		cout << "No Found!" << endl;
		set<Course, ConsolePlotform::ComScore> Temp;
		return Temp;
	}
}

multimap<double, Student>
ConsolePlotform::SortByCredits() {
	multimap<double, Student> Temp;
	for (auto memb : Map_Id_TotalCredits) {
		Temp.insert({ memb.second,Map_Id_Student[memb.first] });
	}
	return Temp;
}

//������Ϣ
set<Student>
ConsolePlotform::FindStudent1(string _KeyName, string _Key) {
	set<Student> Target;
	//id�ɱȽϣ�����Χ��ѯ
	if (_KeyName == "id") {
		//������Ƿ�Χ
		if (Map_Id_Student.count(stoi(_Key))) {
			set<Student> Temp;
			Temp.insert(Map_Id_Student[stoi(_Key)]);
			return Temp;
		}
		//����Ƿ�Χ������"<10908"
		else if (_Key[0] == '<')
		{
			if (_Key[2] != '=')
			{
				string sCriValue = _Key.substr(1, _Key.size() - 1);
				int CriValue = stoi(sCriValue);
				auto iter = Map_Id_Student.begin();

				while (iter != Map_Id_Student.lower_bound(CriValue)) {
					Target.insert(iter->second);
					iter++;
				}
			}
			else if (_Key[2] == '=') {
				string sCriValue = _Key.substr(2, _Key.size() - 2);
				int CriValue = stoi(sCriValue);
				auto iter = Map_Id_Student.begin();
				while (iter != Map_Id_Student.upper_bound(CriValue)) {
					Target.insert(iter->second);
					iter++;
				}
			}
		}
		//��Χ������">10908"
		else if (_Key[0] == '>')
		{
			if (_Key[2] != '=')
			{
				string sCriValue = _Key.substr(1, _Key.size() - 1);
				int CriValue = stoi(sCriValue);
				auto iter = Map_Id_Student.upper_bound(CriValue);
				while (iter != Map_Id_Student.end()) {
					Target.insert(iter->second);
					iter++;
				}
			}
			else if (_Key[2] == '=') {
				string sCriValue = _Key.substr(2, _Key.size() - 2);
				int CriValue = stoi(sCriValue);
				auto iter = Map_Id_Student.lower_bound(CriValue);
				while (iter != Map_Id_Student.end()) {
					Target.insert(iter->second);
					iter++;
				}
			}
		}
	}
	//sex���ɱȽϣ�������Χ��ѯ
	else if (_KeyName == "sex") {
		if (Map_Sex_Student.count(stoi(_Key)))
			return Map_Sex_Student[stoi(_Key)];
	}
	//birthday�ɱȽϣ�����Χ��ѯ
	else if (_KeyName == "birthday") {
		string syear, smonth, sday;
		syear = _Key.substr(_Key.find_first_of('/') - 4, 4);
		smonth = _Key.substr(_Key.find_first_of('/') + 1,
			_Key.find_last_of('/') - _Key.find_first_of('/') - 1);
		sday = _Key.substr(_Key.find_last_of('/') + 1, 2);
		int year, month, day;
		year = stoi(syear);
		month = stoi(smonth);
		day = stoi(sday);
		Date birthday(year, month, day);
		//����Ƿ�Χ��Ϣ����"<1998/3/5"
		if (_Key[0] == '<')
		{
			if (_Key[2] != '=')
			{
				auto iter = Map_Date_Student.begin();
				while (iter != Map_Date_Student.lower_bound(birthday)) {
					Target.insert(iter->second.begin(), iter->second.end());
					iter++;
				}
			}
			else if (_Key[2] == '=')
			{
				auto iter = Map_Date_Student.begin();
				while (iter != Map_Date_Student.upper_bound(birthday)) {
					Target.insert(iter->second.begin(), iter->second.end());
					iter++;
				}
			}
		}
		//��Χ��Ϣ����">1998/3/5"
		else if (_Key[0] == '>')
		{
			if (_Key[2] != '=')
			{
				auto iter = Map_Date_Student.upper_bound(birthday);
				while (iter != Map_Date_Student.end()) {
					Target.insert(iter->second.begin(), iter->second.end());
					iter++;
				}
			}
			else if (_Key[2] == '=')
			{
				auto iter = Map_Date_Student.lower_bound(birthday);
				while (iter != Map_Date_Student.end()) {
					Target.insert(iter->second.begin(), iter->second.end());
					iter++;
				}
			}
		}
		//�����׼ȷ��Ϣ
		else if (Map_Date_Student.count(birthday))
		{
			return Map_Date_Student[birthday];
		}
	}
	//schoolyear�ɱȽϣ�����Χ��ѯ
	else if (_KeyName == "schoolyear") {
		//��Χ��Ϣ����"<2020"
		if (_Key[0] == '<')
		{

			if (_Key[2] != '=')
			{
				int CriValue = stoi(_Key.substr(1, 4));
				auto iter = Map_SchoolYear_Student.begin();
				while (iter != Map_SchoolYear_Student.lower_bound(CriValue)) {
					Target.insert(iter->second.begin(), iter->second.end());
					iter++;
				}
			}
			else if (_Key[2] == '=')
			{
				int CriValue = stoi(_Key.substr(2, 4));
				auto iter = Map_SchoolYear_Student.begin();
				while (iter != Map_SchoolYear_Student.upper_bound(CriValue)) {
					Target.insert(iter->second.begin(), iter->second.end());
					iter++;
				}
			}
		}
		//��Χ��Ϣ����">2016"
		else if (_Key[0] == '>')
		{
			if (_Key[2] != '=')
			{
				int CriValue = stoi(_Key.substr(1, 4));
				auto iter = Map_SchoolYear_Student.upper_bound(CriValue);
				while (iter != Map_SchoolYear_Student.end()) {
					Target.insert(iter->second.begin(), iter->second.end());
					iter++;
				}
			}
			else if (_Key[2] == '=')
			{
				int CriValue = stoi(_Key.substr(2, 4));
				auto iter = Map_SchoolYear_Student.lower_bound(CriValue);
				while (iter != Map_SchoolYear_Student.end()) {
					Target.insert(iter->second.begin(), iter->second.end());
					iter++;
				}
			}
		}
		else if (Map_SchoolYear_Student.count(stoi(_Key)))
			return Map_SchoolYear_Student[stoi(_Key)];
	}
	//birthplace���ɱȽϣ�������Χ��ѯ
	else if (_KeyName == "birthplace") {
		if (Map_Birthplace_Student.count(_Key))
			return Map_Birthplace_Student[_Key];
	}
	//��Ŀ����Ӧ�ĳɼ��ɱȽϣ�����Χ��ѯ
	else if (Map_CourName_StuCour.count(_KeyName))
	{
		//������Ƿ�Χ
		if (isdigit(_Key[0])) {
			auto iter = Map_CourName_StuCour[_KeyName].begin();
			while (iter != Map_CourName_StuCour[_KeyName].end()) {
				if (iter->GetCourScore() == stof(_Key))
				{
					Target.insert(Map_Id_Student[iter->GetCourId()]);
					break;
				}
				iter++;
			}
		}
		//����Ƿ�Χ������"<90"
		else if (_Key[0] == '<')
		{
			if (_Key[2] != '=')
			{
				string sCriValue = _Key.substr(1, _Key.size() - 1);
				double CriValue = stof(sCriValue);
				auto iter = Map_CourName_StuCour[_KeyName].begin();
				while (iter != Map_CourName_StuCour[_KeyName].end()) {
					if (iter->GetCourScore() < CriValue)
					{
						Target.insert(Map_Id_Student[iter->GetCourId()]);
					}
					iter++;
				}
			}
			else if (_Key[2] == '=') {
				string sCriValue = _Key.substr(2, _Key.size() - 2);
				double CriValue = stof(sCriValue);
				auto iter = Map_CourName_StuCour[_KeyName].begin();
				while (iter != Map_CourName_StuCour[_KeyName].end()) {
					if (iter->GetCourScore() <= CriValue)
					{
						Target.insert(Map_Id_Student[iter->GetCourId()]);
						break;
					}
					iter++;
				}
			}
		}
		//��Χ������">80"
		else if (_Key[0] == '>')
		{
			if (_Key[2] != '=')
			{
				string sCriValue = _Key.substr(1, _Key.size() - 1);
				double CriValue = stoi(sCriValue);
				auto iter = Map_CourName_StuCour[_KeyName].begin();
				while (iter != Map_CourName_StuCour[_KeyName].end()) {
					if (iter->GetCourScore() > stoi(sCriValue))
					{
						Target.insert(Map_Id_Student[iter->GetCourId()]);
						break;
					}
					iter++;
				}
			}
			else if (_Key[2] == '=') {
				string sCriValue = _Key.substr(2, _Key.size() - 2);
				double CriValue = stoi(sCriValue);
				auto iter = Map_CourName_StuCour[_KeyName].begin();
				while (iter != Map_CourName_StuCour[_KeyName].end()) {
					if (iter->GetCourScore() >= stoi(sCriValue))
					{
						Target.insert(Map_Id_Student[iter->GetCourId()]);
						break;
					}
					iter++;
				}
			}
		}
	}
	//AverScore�ɱȽϣ�������֧�ַ�Χ��ѯ
	else if (_KeyName == "averagescore")
	{
		//��Χ��Ϣ����"<90.5"
		if (_Key[0] == '<')
		{

			if (_Key[2] != '=')
			{
				double CriValue = stof(_Key.substr(1, _Key.size() - 1));
				auto iter = Map_AverScore_Id.begin();
				while (iter != Map_AverScore_Id.lower_bound(CriValue)) {
					Target.insert(Map_Id_Student[iter->second]);
					iter++;
				}
			}
			else if (_Key[2] == '=')
			{
				double CriValue = stof(_Key.substr(2, _Key.size() - 2));
				auto iter = Map_AverScore_Id.begin();
				while (iter != Map_AverScore_Id.upper_bound(CriValue)) {
					Target.insert(Map_Id_Student[iter->second]);
					iter++;
				}
			}
		}
		//��Χ��Ϣ����">80.3"
		else if (_Key[0] == '>')
		{
			if (_Key[2] != '=')
			{
				double CriValue = stof(_Key.substr(1, _Key.size() - 1));
				auto iter = Map_AverScore_Id.upper_bound(CriValue);
				while (iter != Map_AverScore_Id.end()) {
					Target.insert(Map_Id_Student[iter->second]);
					iter++;
				}
			}
			else if (_Key[2] == '=')
			{
				double CriValue = stof(_Key.substr(2, _Key.size() - 2));
				auto iter = Map_AverScore_Id.lower_bound(CriValue);
				while (iter != Map_AverScore_Id.end()) {
					Target.insert(Map_Id_Student[iter->second]);
					iter++;
				}
			}
		}
	}
	//TotalScore�ɱȽϣ�������֧�ַ�Χ��ѯ
	else if (_KeyName == "totalscore")
	{
		//��Χ��Ϣ����"<250"
		if (_Key[0] == '<')
		{

			if (_Key[2] != '=')
			{
				double CriValue = stof(_Key.substr(1, _Key.size() - 1));
				auto iter = Map_TotalScore_Id.begin();
				while (iter != Map_TotalScore_Id.lower_bound(CriValue)) {
					Target.insert(Map_Id_Student[iter->second]);
					iter++;
				}
			}
			else if (_Key[2] == '=')
			{
				double CriValue = stof(_Key.substr(2, _Key.size() - 2));
				auto iter = Map_TotalScore_Id.begin();
				while (iter != Map_TotalScore_Id.upper_bound(CriValue)) {
					Target.insert(Map_Id_Student[iter->second]);
					iter++;
				}
			}
		}
		//��Χ��Ϣ����">200"
		else if (_Key[0] == '>')
		{
			if (_Key[2] != '=')
			{
				double CriValue = stof(_Key.substr(1, _Key.size() - 1));
				auto iter = Map_TotalScore_Id.upper_bound(CriValue);
				while (iter != Map_TotalScore_Id.end()) {
					Target.insert(Map_Id_Student[iter->second]);
					iter++;
				}
			}
			else if (_Key[2] == '=')
			{
				double CriValue = stof(_Key.substr(2, _Key.size() - 2));
				auto iter = Map_TotalScore_Id.lower_bound(CriValue);
				while (iter != Map_TotalScore_Id.end()) {
					Target.insert(Map_Id_Student[iter->second]);
					iter++;
				}
			}
		}
	}
	//TotalCredits�ɱȽϣ�������֧�ַ�Χ��ѯ
	else if (_KeyName == "totalcredits")
	{
		//��Χ��Ϣ����"<25"
		if (_Key[0] == '<')
		{

			if (_Key[2] != '=')
			{
				double CriValue = stof(_Key.substr(1, _Key.size() - 1));
				auto iter = Map_TotalCredits_Id.begin();
				while (iter != Map_TotalCredits_Id.lower_bound(CriValue)) {
					Target.insert(Map_Id_Student[iter->second]);
					iter++;
				}
			}
			else if (_Key[2] == '=')
			{
				double CriValue = stof(_Key.substr(2, _Key.size() - 2));
				auto iter = Map_TotalCredits_Id.begin();
				while (iter != Map_TotalCredits_Id.upper_bound(CriValue)) {
					Target.insert(Map_Id_Student[iter->second]);
					iter++;
				}
			}
		}
		//��Χ��Ϣ����">20"
		else if (_Key[0] == '>')
		{
			if (_Key[2] != '=')
			{
				double CriValue = stof(_Key.substr(1, _Key.size() - 1));
				auto iter = Map_TotalCredits_Id.upper_bound(CriValue);
				while (iter != Map_TotalCredits_Id.end()) {
					Target.insert(Map_Id_Student[iter->second]);
					iter++;
				}
			}
			else if (_Key[2] == '=')
			{
				double CriValue = stof(_Key.substr(2, _Key.size() - 2));
				auto iter = Map_TotalCredits_Id.lower_bound(CriValue);
				while (iter != Map_TotalCredits_Id.end()) {
					Target.insert(Map_Id_Student[iter->second]);
					iter++;
				}
			}
		}
	}

	return Target;
}
//������Ϣ
set<Student>
ConsolePlotform::FindStudent2
(string _KeyName1, string _Key1,
	string _KeyName2, string _Key2) {
	set<Student>StuSet1 = FindStudent1(_KeyName1, _Key1);
	set<Student>StuSet2 = FindStudent1(_KeyName2, _Key2);
	set<Student>FinalSet;
	//ȡ���߽���
	set_intersection(StuSet1.begin(), StuSet1.end(),
		StuSet2.begin(), StuSet2.end(),
		inserter(FinalSet, FinalSet.begin()));
	return FinalSet;
}
//������Ϣ
set<Student> ConsolePlotform::FindStudent3
(string _KeyName1, string _Key1,
	string _KeyName2, string _Key2,
	string _KeyName3, string _Key3) {
	set<Student>StuSet1 = FindStudent1(_KeyName1, _Key1);
	set<Student>StuSet2 = FindStudent2(_KeyName2, _Key2, _KeyName3, _Key3);
	set<Student>FinalSet;
	//ȡ���߽���
	set_intersection(StuSet1.begin(), StuSet1.end(),
		StuSet2.begin(), StuSet2.end(),
		inserter(FinalSet, FinalSet.begin()));
	return FinalSet;
}