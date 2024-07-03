#include "common_header.h"
#define bufsize 300
using namespace std;
char sentence[bufsize];
int main() {
	cout << "请输入文法，每行一个，在行首按 Ctrl+Z 结束。第一个文法的首字符将被视为开始符号" << endl;
	input_grammar();
	pick_up();
	eliminateLeftRecursion();
	getFirstN();
	getFirstP();
	getFollow();
	generateTable();
	saveAllInfoToFile();
	printAllTerminator();
	printAllNonTerminator();
	printAllFirstN();
	printAllFirstP();
	printAllFollow();
	printTable();
	cout << "---句子测试---" << endl;
	while (true) {
		cout << "请输入一个句子：（中间不含空格，回车结束, 退出请输入 quit）" << endl;
		cin >> sentence;
		if (strcmp("quit", sentence) == 0)
			break;
		analyze(sentence);
	}

}