#include"StudentCourse.h"
#include<fstream>
#include<sstream>
StudentCourse::StudentCourse(string FileName) {
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
			//依次寻找并赋值Course的属性
			for (int i = 0; i < 6; i++) {
				words[i] = "null";
				text >> words[i];
			}
			int id = stoi(words[0]);
			string course;
			double credits, score;
			if (words[5] != "null") {
				course = words[1] + " " + words[2] + " " + words[3];
				credits = stod(words[4]);
				score = stod(words[5]);
			}
			else if (words[4] != "null") {
				course = words[1] + " " + words[2];
				credits = stod(words[3]);
				score = stod(words[4]);
			}
			else {
				course = words[1];
				credits = stod(words[2]);
				score = stod(words[3]);
			}
			//使用以上数据来构造一行Course
			Course CourseLine(id, course, credits, score);

			//储存成绩单
			Set_Course.insert(CourseLine);

			//以科目名为关键字映射成绩单（以Score为比较器）
			Map_CourName_StuCour[course].insert(CourseLine);

			//以学生id为关键字映射学生总成绩
			Map_Id_TotalScore[id] += CourseLine.GetCourScore();

			//以学生id为关键字映射学生已修学分
			if (CourseLine.CanGetCredits())
				Map_Id_TotalCredits[id] += credits;
			else
				Map_Id_TotalCredits[id] += 0;

		}
	}
}
