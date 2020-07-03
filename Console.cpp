#include"Console.h"
#include<algorithm>
#include<iterator>
#include<cctype>
/*
信息控制台的构造函数
除了初始化基类的Map外，还需要初始化基类无法实现的Map
这里的Map，其元素一般都是两个不同基类的pair，
或是需要基类里统计的数据
（如平均分，因为Python这门课只有部分人选，需要基类初始化结束查看course的size）
*/
ConsolePlotform::ConsolePlotform(string Filename1, string Filename2) :
	StudentInfo(Filename1), StudentCourse(Filename2)
{
	for (auto memb : Set_Course)
		//以学生为关键字存储学生成绩单
		Map_Stu_StuCour[Map_Id_Student[memb.GetCourId()]].insert(memb);
	for (auto memb : Set_Course) {
		//以科目名为关键字存储学生单科成绩及学生信息
		Map_CourName_ScoreToInfo[memb.GetCourName()].insert
		({ memb.GetCourScore(),Map_Id_Student[memb.GetCourId()] });
		//以总成绩为关键字映射学生学生id
		Map_TotalScore_Id.insert
		({ Map_Id_TotalScore[memb.GetCourId()],memb.GetCourId() });
		//以学生id为关键字映射学生平均分
		Map_Id_AverScore[memb.GetCourId()] =
			(double)Map_Id_TotalScore[memb.GetCourId()] /(double)
			(Map_Stu_StuCour[Map_Id_Student[memb.GetCourId()]].size());
		//以学生平均分为关键字映射学生id
		Map_AverScore_Id.insert
		({ Map_Id_AverScore[memb.GetCourId()] ,memb.GetCourId() });
		//以学生已修学分为关键字映射学生id
		Map_TotalCredits_Id.insert
		({ Map_Id_TotalCredits[memb.GetCourId()],memb.GetCourId() });
	}
}

//删除函数（参数可以通过调用Find系列函数实现范围删除）
set<Student> ConsolePlotform::RemoveStudent(set<Student> aSet_Target) {
	for (auto memb : aSet_Target) {
		Set_StuInfo.erase(memb);
	}
	return aSet_Target;
}

//排序函数
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
		//总成绩除科目得平均分
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

//单条信息
set<Student>
ConsolePlotform::FindStudent1(string _KeyName, string _Key) {
	set<Student> Target;
	//id可比较，允许范围查询
	if (_KeyName == "id") {
		//如果不是范围
		if (Map_Id_Student.count(stoi(_Key))) {
			set<Student> Temp;
			Temp.insert(Map_Id_Student[stoi(_Key)]);
			return Temp;
		}
		//如果是范围，比如"<10908"
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
		//范围，比如">10908"
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
	//sex不可比较，不允许范围查询
	else if (_KeyName == "sex") {
		if (Map_Sex_Student.count(stoi(_Key)))
			return Map_Sex_Student[stoi(_Key)];
	}
	//birthday可比较，允许范围查询
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
		//如果是范围信息，如"<1998/3/5"
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
		//范围信息，如">1998/3/5"
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
		//如果是准确信息
		else if (Map_Date_Student.count(birthday))
		{
			return Map_Date_Student[birthday];
		}
	}
	//schoolyear可比较，允许范围查询
	else if (_KeyName == "schoolyear") {
		//范围信息，如"<2020"
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
		//范围信息，如">2016"
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
	//birthplace不可比较，不允许范围查询
	else if (_KeyName == "birthplace") {
		if (Map_Birthplace_Student.count(_Key))
			return Map_Birthplace_Student[_Key];
	}
	//科目名对应的成绩可比较，允许范围查询
	else if (Map_CourName_StuCour.count(_KeyName))
	{
		//如果不是范围
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
		//如果是范围，比如"<90"
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
		//范围，比如">80"
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
	//AverScore可比较，但仅仅支持范围查询
	else if (_KeyName == "averagescore")
	{
		//范围信息，如"<90.5"
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
		//范围信息，如">80.3"
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
	//TotalScore可比较，但仅仅支持范围查询
	else if (_KeyName == "totalscore")
	{
		//范围信息，如"<250"
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
		//范围信息，如">200"
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
	//TotalCredits可比较，但仅仅支持范围查询
	else if (_KeyName == "totalcredits")
	{
		//范围信息，如"<25"
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
		//范围信息，如">20"
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
//两条信息
set<Student>
ConsolePlotform::FindStudent2
(string _KeyName1, string _Key1,
	string _KeyName2, string _Key2) {
	set<Student>StuSet1 = FindStudent1(_KeyName1, _Key1);
	set<Student>StuSet2 = FindStudent1(_KeyName2, _Key2);
	set<Student>FinalSet;
	//取二者交集
	set_intersection(StuSet1.begin(), StuSet1.end(),
		StuSet2.begin(), StuSet2.end(),
		inserter(FinalSet, FinalSet.begin()));
	return FinalSet;
}
//三条信息
set<Student> ConsolePlotform::FindStudent3
(string _KeyName1, string _Key1,
	string _KeyName2, string _Key2,
	string _KeyName3, string _Key3) {
	set<Student>StuSet1 = FindStudent1(_KeyName1, _Key1);
	set<Student>StuSet2 = FindStudent2(_KeyName2, _Key2, _KeyName3, _Key3);
	set<Student>FinalSet;
	//取二者交集
	set_intersection(StuSet1.begin(), StuSet1.end(),
		StuSet2.begin(), StuSet2.end(),
		inserter(FinalSet, FinalSet.begin()));
	return FinalSet;
}