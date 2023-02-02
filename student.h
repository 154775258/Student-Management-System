#pragma once
#include<iostream>
#include<fstream>
#include<unordered_map>
#include<vector>
#include<string>

using namespace std;

class student {
	public:
        student(){}
        inline void pushData();//��������
        inline void writeData();//������������
        inline void enterClass(string tmp);//�����༶
        inline void createClass(string tmp);//�����༶
        inline void addStudentInClass(string _class,string nums);//���༶����ѧ��
        inline void eraseStudentInClass(string _class,string id);//�Ƴ�ѧ��
        inline void addStudent(string nums,string name);//����ѧ����Ϣ
        inline void eraseStudent(string id);//ɾ��ѧ����Ϣ
        inline void eraseClass(string _class);//ɾ���༶
        inline void addDiscipline(string _class,string Discipline);//���ӿ�Ŀ
        inline int findDiscipline(string _class, string a);
        inline void eraseClassDiscipline(string _class,string Dis);//ɾ���༶��Ŀ
        inline void reviseStudentScores(string id,string Discipline,string nums1);//�޸�ѧ���ɼ�
        inline int findClassId(string id,string tmp) {
			for (int i = 0; i < classStudentId[tmp].size(); i++) {
				if (classStudentId[tmp][i] == id)return i;
			}
			return -1;
		}

        inline bool check(string& a) {
			if (a.size() < 2) {
				cout << "�༶����������������\n";
				return 0;
			}
			else if (a.size() > 16) {
				cout << "�༶����������������\n";
				return 0;
			}
			else if (classStudentId.count(a)) {
				cout << "�ð༶���Ѵ�������������\n";
				return 0;
			}
			return 1;
		}

	ofstream writeFile;//�������ļ�ָ��
	ifstream putFile;//ȡ�����ļ�ָ��
	vector<string> classId;//���༶�ĵط�
	unordered_map<string, vector<string>> classStudentId;//ÿ���༶������Щѧ��
	unordered_map<string, vector<string>> classDiscipline;//ÿ���༶������Щ��Ŀ
	unordered_map<string, string> studentClass;//ÿ��ѧ�����ڰ༶
	unordered_map<string, vector<string>>studentScores;//ÿ��ѧ���ĳɼ� ѧ�Ŷ�Ӧ�ɼ�
	unordered_map<string, vector<string>>studentName;//ѧ�������Լ��������ǵ�ѧ��
	unordered_map<string, string>nameId;//ѧ�Ŷ�Ӧ����
};

inline void student::pushData() {
	writeFile.open("allStudent.dat", ios::app);
	writeFile.close();
	putFile.open("allStudent.dat");
	string id;
	int use = 1;
	while (!putFile.eof()) {
		putFile >> id;
		if (id == "#") {
			use++;
			continue;
		}
		if (use == 1) {
			classId.push_back(id);
		}
		else if (use == 2) {
			auto index = id.find('.');
			string tmp2 = id.substr(0, index);
			//cout << tmp2 << " "  << id << '\n';
			while (id.find('.',index+1) != string::npos) {
				auto t = index;
				index = id.find('.',index+1);
				string tmp1 = id.substr(t + 1, (index - t - 1));
				classStudentId[tmp2].push_back(tmp1);
				studentClass[tmp1] = tmp2;
				//cout << tmp2 << ' ' << tmp1 << '\n';
			}
		}
		else if (use == 3) {
			auto index = id.find('.');
			string tmp2 = id.substr(0, index);
			while (id.find('.', index + 1) != id.npos) {
				auto t = index;
				index = id.find('.', index + 1);
				classDiscipline[tmp2].push_back(id.substr(t + 1, (index - t - 1)));
			}
		}
		else if (use == 4) {
			auto index = id.find('.');
			string tmp2 = id.substr(0, index);
			while (id.find('.', index + 1) != id.npos) {
				auto t = index;
				index = id.find('.', index + 1);
				string tmp1 = id.substr(t + 1, (index - t - 1));
				studentScores[tmp2].push_back(tmp1);
			}
		}
		else if (use == 5) {
			auto index = id.find('.');
			string tmp2 = id.substr(0, index);
			while (id.find('.', index + 1) != id.npos) {
				auto t = index;
				index = id.find('.', index + 1);
				string tmp1 = id.substr(t + 1, (index - t - 1));
				//cout << index - t << '\n';
				studentName[tmp2].push_back(tmp1);
				nameId[tmp1] = tmp2;
				//cout << tmp1 << " " << tmp2 << '\n';
			}
		}
		//cout << use << '\n';
		//cout << id << '\n';
	}
	putFile.close();
	system("cls");
}

inline void student::writeData() {
	writeFile.open("allStudent.dat");
	for (int i = 0; i < classId.size(); i++) {
		writeFile << classId[i] << '\n';
	}
	writeFile << "#" << '\n';
	for (auto& tmp : classStudentId) {
		string t = tmp.first;
		t += '.';
		for (int i = 0; i < tmp.second.size(); i++) {
			t += tmp.second[i];
			t += '.';
		}
		writeFile << t << '\n';
	}
	writeFile << "#\n";
	for (auto& tmp : classDiscipline) {
		string t = tmp.first;
		t += '.';
		for (int i = 0; i < tmp.second.size(); i++) {
			t += tmp.second[i];
			t += '.';
		}
		writeFile << t << '\n';
	}
	writeFile << "#\n";
	for (auto& tmp : studentScores) {
		string t = tmp.first;
		t += '.';
		for (int i = 0; i < tmp.second.size(); i++) {
			t += tmp.second[i];
			t += '.';
		}
		writeFile << t << '\n';
	}
	writeFile << "#\n";
	for (auto& tmp : studentName) {
		string t = tmp.first;
		t += '.';
		for (int i = 0; i < tmp.second.size(); i++) {
			t += tmp.second[i];
			t += '.';
		}
		writeFile << t << '\n';
	}
	writeFile << "#\n";
}

inline void student::enterClass(string tmp) {
	for (int i = 0; i < classStudentId[tmp].size(); i++) {
		string t1 = classStudentId[tmp][i];
		cout << "ѧ��:" << t1 << " " << "����:" << nameId[t1] << " ";
		for (int j = 0; j < studentScores[t1].size(); j++) {
			cout << "��Ŀ:" << classDiscipline[tmp][j] << ":" << studentScores[t1][j] << "   ";
		}
		cout << '\n';
	}
}

inline void student::addDiscipline(string _class,string Discipline) {
	classDiscipline[_class].push_back(Discipline);
	for (int i = 0; i < classStudentId[_class].size(); i++) {
		studentScores[classStudentId[_class][i]].push_back("-1");
	}
}

inline void student::createClass(string tmp) {
	classId.push_back(tmp);
	classStudentId[tmp].push_back("text");
}

inline void student::addStudentInClass(string _class,string nums) {
	if (classStudentId[_class][0] == "text")classStudentId[_class][0] = nums;
	else
	classStudentId[_class].push_back(nums);
	//cout << classStudentId[_class][0] << '\n';
	studentClass[nums] = _class;
	studentScores[_class].resize(classDiscipline[_class].size(), "-1");
	cout << "���ӳɹ�\n";
}



inline void student::eraseStudentInClass(string _class,string id) {
	auto it = classStudentId[_class].begin();
	it += findClassId(id, _class);
	classStudentId[_class].erase(it);
	studentScores.erase(id);
	studentClass.erase(id);
}

inline void student::addStudent(string nums,string name) {
	nameId[nums] = name;
	studentName[name].push_back(nums);
}

inline void student::eraseStudent(string id) {
	string name = nameId[id];
	nameId.erase(id);
	auto it = studentName[name].begin();
	for (; it != studentName[name].end(); ++it)
		if (*it == id)break;
	studentName[name].erase(it);
	//cout << 1 << '\n';
	if(studentClass.count(id))
    eraseStudentInClass(studentClass[id],id);
	studentScores.erase(id);
	studentClass.erase(id);
}


inline void student::eraseClass(string _class) {
	auto it = classId.begin();
	for (; it != classId.end(); it++)
		if (*it == _class)break;
	classId.erase(it);
	classDiscipline.erase(_class);
	for (auto& q : classStudentId[_class]) {
		studentClass.erase(q);
	}
	classStudentId.erase(_class);
}

inline int student::findDiscipline(string _class,string a) {
	for (int i = 0; i < classDiscipline[_class].size(); i++) {
		if (classDiscipline[_class][i] == a)return i;
	}
	return -1;
}

inline void student::eraseClassDiscipline(string _class,string Discipline) {
	int t = findDiscipline(_class, Discipline);
	auto it = classDiscipline[_class].begin();
	it += t;
	classDiscipline[_class].erase(it);
	for (int i = 0; i < classStudentId[_class].size(); i++) {
		it = studentScores[classStudentId[_class][i]].begin();
		it += t;
		studentScores[classStudentId[_class][i]].erase(it);
	}
}

inline void student::reviseStudentScores(string id,string Discipline,string nums1) {
	int t = findDiscipline(studentClass[id], Discipline);
	auto it = studentScores[id].begin();
	it += t;
	*it = nums1;
}
