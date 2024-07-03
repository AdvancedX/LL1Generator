#include "common_header.h"
using namespace std;
//����ʽ������飨�������������ӡ�������ݹ飩
extern string grammar[maxnum];
//��ʼ����, Ĭ�ϵ�һ���ķ��ĵ�һ����ĸΪ��ʼ����
extern char start_char;
//���ս�� �� �ս�� ������, ����ʽ����
extern int cnt_nonT;
extern int cnt_term;
extern int lines;
//���еķ��ս��
extern vector<char> nonT;
//���е��ս��
extern vector<char> term;

void input_grammar() {
    lines = 0;
    string line;
    while (getline(cin, line)) {
        string processedLine;
        for (char c : line) {
            if (c != ' ') { // �����ǰ�ַ����ǿո�����ӵ��������ַ�����
                processedLine += c;
            }
        }
        if (!processedLine.empty()) {
            grammar[lines++] = processedLine; // ���洦���Ĳ���ʽ
        }
    }
    cin.clear();
}
// ��ȡ���ս�� �� �ս��, ���浽 nonT �� term ��
void pick_up() {
    bool vis[256] = { 0 };
    for (int i = 0; i < lines; i++) {
        char cur = grammar[i][0];
        if (!vis[(int)cur]) {
            nonT.push_back(cur);
            vis[(int)cur] = true;
        }
    }
    // ���Ƿ��ս���Ķ����ս��
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
// ������ݹ�
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
            char new_nonT = A + ('`' - 'A');  // �µķ��ս��
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
        cout << "������ݹ������ķ���" << endl;
        for (int i = 0; i < lines; i++) {
            cout << grammar[i] << endl;
        }
    }
    else {
        cout << "������ķ���������ݹ顣" << endl;
    }
}