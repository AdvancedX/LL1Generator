#include "common_header.h"
using namespace std;
//产生式存放数组（不含公共左因子、不含左递归）
extern string grammar[maxnum];
//开始符号, 默认第一个文法的第一个字母为开始符号
extern char start_char;
//非终结符 与 终结符 的数量, 产生式个数
extern int cnt_nonT;
extern int cnt_term;
extern int lines;
//所有的非终结符
extern vector<char> nonT;
//所有的终结符
extern vector<char> term;

void input_grammar() {
    lines = 0;
    string line;
    while (getline(cin, line)) {
        string processedLine;
        for (char c : line) {
            if (c != ' ') { // 如果当前字符不是空格，则添加到处理后的字符串中
                processedLine += c;
            }
        }
        if (!processedLine.empty()) {
            grammar[lines++] = processedLine; // 保存处理后的产生式
        }
    }
    cin.clear();
}
// 提取非终结符 和 终结符, 保存到 nonT 和 term 中
void pick_up() {
    bool vis[256] = { 0 };
    for (int i = 0; i < lines; i++) {
        char cur = grammar[i][0];
        if (!vis[(int)cur]) {
            nonT.push_back(cur);
            vis[(int)cur] = true;
        }
    }
    // 不是非终结符的都是终结符
    for (int i = 0; i < lines; i++) {
        int n = grammar[i].length();
        for (int j = 3; j < n; j++) {
            char cur = grammar[i][j];
            if (!vis[(int)cur]) {
                term.push_back(cur);
                vis[(int)cur] = true;
            }
        }
    }
    term.push_back('$');
    cnt_nonT = nonT.size();
    cnt_term = term.size();
    start_char = grammar[0][0];

}
// 消除左递归
void eliminateLeftRecursion() {
    vector<string> new_grammar;
    bool has_left_recursion = false;

    for (int i = 0; i < cnt_nonT; i++) {
        char A = nonT[i];
        vector<string> alpha, beta;
        for (int j = 0; j < lines; j++) {
            if (grammar[j][0] == A) {
                string rhs = grammar[j].substr(3);
                if (rhs[0] == A) {
                    alpha.push_back(rhs.substr(1));
                }
                else {
                    beta.push_back(rhs);
                }
            }
        }
        if (!alpha.empty()) {
            has_left_recursion = true;
            char new_nonT = A + ('`' - 'A');  // 新的非终结符
            for (const auto& b : beta) {
                new_grammar.push_back(string(1, A) + "->" + b + new_nonT);
            }
            for (const auto& a : alpha) {
                new_grammar.push_back(string(1, new_nonT) + "->" + a + new_nonT);
            }
            new_grammar.push_back(string(1, new_nonT) + "->@");
        }
        else {
            for (int j = 0; j < lines; j++) {
                if (grammar[j][0] == A) {
                    new_grammar.push_back(grammar[j]);
                }
            }
        }
    }

    if (has_left_recursion) {
        grammar->clear();
        lines = new_grammar.size();
        for (int i = 0; i < lines; i++) {
            grammar[i] = new_grammar[i];
        }
        cout << "消除左递归后的新文法：" << endl;
        for (int i = 0; i < lines; i++) {
            cout << grammar[i] << endl;
        }
    }
    else {
        cout << "输入的文法不存在左递归。" << endl;
    }
}