#include "common_header.h"
using namespace std;

//����ʽ������飨�������������ӡ�������ݹ飩
extern string grammar[maxnum];
//��ʼ����, Ĭ�ϵ�һ���ķ��ĵ�һ����ĸΪ��ʼ����
extern char start_char;
extern int cnt_nonT;
extern int cnt_term;
extern int lines;
//���еķ��ս��
extern vector<char> nonT;
//���е��ս��
extern vector<char> term;
//ÿһ������ʽ�� first ���ϣ�ע�� '$' '@'
extern vector<char> firstP[maxnum];
//ÿһ�����ս���� first ���ϣ�ע�� '$' '@'
extern vector<char> firstN[maxnum];
//ÿһ�����ս���� follow ���ϣ�ע�� '$' '@'
extern vector<char> follow[maxnum];
//��ά���飬Ԥ���������Ų���ʽ�����±꣬û�еĵط�����Ϊ -1
extern int table[maxnum][maxnum];
//��ӡ�����ս��
void printAllTerminator() {
	cout << "�ս������  ��" << cnt_term << " �ֱ�Ϊ:{";
	for (char c : term) {
		cout << " " << c;
	}
	cout << " }" << endl;
}
//��ӡ���з��ս��
void printAllNonTerminator() {
	cout << "���ս��������" << cnt_nonT << " �ֱ�Ϊ:{";
	for (char c : nonT) {
		cout << " " << c;
	}
	cout << " }" << endl;
}
//��ӡ���� firstN
void printAllFirstN() {
	cout << "���з��ս���� FIRST ����" << endl;
	for (int i = 0; i < cnt_nonT; i++) {
		cout << "FIRST(" << nonT[i] << ") = {";
		for (char fi : firstN[i]) {
			cout << " " << fi;
		}
		cout << " }" << endl;
	}
	cout << endl;
}
//��ӡ���� firstP
void printAllFirstP() {
	cout << "���в���ʽ�Ҳ��� FIRST ����" << endl;
	for (int i = 0; i < lines; i++) {
		cout << "FIRST(" << grammar[i].substr(3) << ") = {";
		for (char fi : firstP[i]) {
			cout << " " << fi;
		}
		cout << " }" << endl;
	}
	cout << endl;
}
//��ӡ���� follow
void printAllFollow() {
	cout << "���з��ս���� FOLLOW ����" << endl;
	for (int i = 0; i < cnt_nonT; i++) {
		cout << "FOLLOW(" << nonT[i] << ") = {";
		for (char fi : follow[i]) {
			cout << " " << fi;
		}
		cout << " }" << endl;
	}
	cout << endl;
}
//��ӡ Ԥ�������
void printTable() {
	int output_width = 10;
	cout << "Ԥ�������" << endl;
	cout << setw(output_width) << " ";
	for (char char_term : term) {
		if (char_term == '@')
			continue;
		cout << setw(output_width) << char_term;
	}
	cout << endl;
	for (int i = 0; i < cnt_nonT; i++) {
		cout << setw(output_width) << nonT[i];
		for (int j = 0; j < cnt_term; j++) {
			if (term[j] == '@')
				continue;
			if (table[i][j] == -1)
				cout << setw(output_width) << " ";
			else
				cout << setw(output_width) << grammar[table[i][j]];
		}
		cout << endl;
	}
}

void saveAllInfoToFile() {
	// �򿪻򴴽��ļ�
	std::ofstream outFile("grammar_analysis_info.txt", std::ios::out | std::ios::app);
	if (!outFile.is_open()) {
		std::cerr << "�޷��򿪻򴴽��ļ� grammar_analysis_info.txt" << std::endl;
		return;
	}
	string tt;
	cout << "��������⣺";
	cin >> tt;
	outFile << "���⣺" << tt << endl;
	// д���ս���������б�
	outFile << "�ս��������" << cnt_term << " �ֱ�Ϊ:{";
	for (char c : term) {
		outFile << " " << c;
	}
	outFile << " }\n";

	// д����ս���������б�
	outFile << "���ս��������" << cnt_nonT << " �ֱ�Ϊ:{";
	for (char c : nonT) {
		outFile << " " << c;
	}
	outFile << " }\n\n";

	// д��Ԥ�������
	outFile << "Ԥ�������\n";
	int output_width = 10;
	outFile << std::setw(output_width) << " ";
	for (char char_term : term) {
		if (char_term == '@') continue;
		outFile << std::setw(output_width) << char_term;
	}
	outFile << "\n";
	for (int i = 0; i < cnt_nonT; i++) {
		outFile << std::setw(output_width) << nonT[i];
		for (int j = 0; j < cnt_term; j++) {
			if (term[j] == '@') continue;
			if (table[i][j] == -1)
				outFile << std::setw(output_width) << " ";
			else
				outFile << std::setw(output_width) << grammar[table[i][j]];
		}
		outFile << endl;
	}
	outFile << endl;
	outFile << endl;
	outFile << endl;
	outFile.close();
}


