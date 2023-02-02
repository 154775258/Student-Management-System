#pragma once
#include<iostream>
#include<fstream>
#include<unordered_map>
#include<string>
using namespace std;


class ID {
	public:
        ID(){pushData();}//��ʼ��
        bool usedId(string id) {//id�ظ�����1���ظ�����0
			return idPassword.count(id);
		}
		
        void NewId(string idTemp,string password){
            wirteFile.open("IDandPassword.txt",ios::app);
			idPassword[idTemp] = password;
			wirteFile << idTemp << '\n';
			wirteFile << password << '\n';
			wirteFile.close();
		}

		bool check(string a,string b) {
			if(idPassword.count(a)){
				return idPassword[a] == b;
			}
			return 0;
		}
        void pushData() {
            putFile.open("IDandPassword.txt");
            string id, password;
            while (!putFile.eof()) {
                putFile >> id;
                putFile >> password;
                if (usedId(id))continue;
                else idPassword[id] = password;
			}
			putFile.close();
		}
	private:
	unordered_map<string, string> idPassword;//�ù�ϣ�����˺��Լ�����
	ofstream wirteFile;//�������ļ�ָ��
    ifstream putFile;//ȡ�����ļ�ָ��

};
