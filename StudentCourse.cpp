#include"StudentCourse.h"
#include<fstream>
#include<sstream>
StudentCourse::StudentCourse(string FileName) {
	ifstream File(FileName);
	if (File) {
		string line;
		while (getline(File, line))
		{
			//������һ��
			if (line[0] == '#')
				continue;
			istringstream text(line);
			string words[6];
			//����Ѱ�Ҳ���ֵCourse������
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
			//ʹ����������������һ��Course
			Course CourseLine(id, course, credits, score);

			//����ɼ���
			Set_Course.insert(CourseLine);

			//�Կ�Ŀ��Ϊ�ؼ���ӳ��ɼ�������ScoreΪ�Ƚ�����
			Map_CourName_StuCour[course].insert(CourseLine);

			//��ѧ��idΪ�ؼ���ӳ��ѧ���ܳɼ�
			Map_Id_TotalScore[id] += CourseLine.GetCourScore();

			//��ѧ��idΪ�ؼ���ӳ��ѧ������ѧ��
			if (CourseLine.CanGetCredits())
				Map_Id_TotalCredits[id] += credits;
			else
				Map_Id_TotalCredits[id] += 0;

		}
	}
}
