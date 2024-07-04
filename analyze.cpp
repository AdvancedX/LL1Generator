#include "common_header.h"
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

// 文法数组
extern string grammar[maxnum];
// 预测分析表，存放产生式数组下标，没有的地方设置为 -1
extern int table[maxnum][maxnum];
// 开始符号
extern char start_char;

// 打印当前状态
void printCurrentStatus(const char* s1, const char* s2, const string& s3) {
    cout << setw(Table_width) << s1 << setw(Table_width) << s2 << setw(Table_width) << s3 << endl;
}

// 分析函数
void analyze(const char* sentence, int len) {
    char str[300];
    strcpy(str, sentence);
    if (len == -1)
        len = strlen(str);
    str[len++] = '$'; // 在末尾加入 '$'
    str[len] = 0;
	//上述代码是给输入串末尾加上'$'，以便于判断是否接受
    char stk[200]; // 数组模拟栈
    int pos = 0;
    stk[pos++] = '$';
    stk[pos++] = start_char;
    stk[pos] = '\0';
	//上述代码是初始化栈，将栈底设置为'$'，栈顶设置为开始符号
    cout << setw(Table_width) << "栈" << setw(Table_width) << "输入" << setw(Table_width) << "动作" << endl;
    printCurrentStatus(stk, str, string("初始"));
	//下面的代码是使用栈进行分析
    for (int input_idx = 0; input_idx < len;) {
        char top = stk[--pos];
        stk[pos] = '\0';
		// 栈顶为'$'，输入串也为'$'，接受
        if (top == '$') {
            if (str[input_idx] == '$') {
                printCurrentStatus("$", "$", string("接受"));
                cout << "分析成功！" << endl;
                break;
            }
			// 栈顶为'$'，输入串不为'$'，错误
            else {
                printCurrentStatus(stk, str + input_idx, string("错误！"));
                cerr << "分析栈栈顶为'$'，但是输入尚未结束。" << endl;
                return;
            }
        }

        int current_type = typeOf(top);
		// 栈顶为终结符
        if (current_type == Terminator) {
            if (top == str[input_idx]) {
				input_idx++; // 匹配成功，输入串指针后移
                string res("匹配 ");
                printCurrentStatus(stk, str + input_idx, res + top);
            }
			// 栈顶终结符与输入符号不匹配，错误
            else {
                printCurrentStatus(stk, str + input_idx, string("错误！"));
                cerr << "分析栈栈顶为终结符 '" << top << "'，但是输入符号为 '" << str[input_idx] << "'" << endl;
                return;
            }
        }
		// 栈顶为非终结符
        else if (current_type == NonTerminator) {
            int g_index = table[indexOfNonT(top)][indexOfTerm(str[input_idx])];
			// 分析表中有对应项
            if (g_index != -1) {
                // 将产生式右部内容倒序入栈
                for (int j = grammar[g_index].size() - 1; j >= 3; j--) {
                    stk[pos++] = grammar[g_index][j];
                }
                stk[pos] = '\0';
                printCurrentStatus(stk, str + input_idx, grammar[g_index]);
            }
			// 分析表中没有对应项，错误
            else {
                printCurrentStatus(stk, str + input_idx, string("错误！"));
                cerr << "分析表 table[" << top << "][" << str[input_idx] << "] 项为空。" << endl;
                return;
            }
        }
        else {
            cerr << "解析错误！" << endl;
            return;
        }
    }
}
