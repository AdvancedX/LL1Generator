#include "common_header.h"
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

// �ķ�����
extern string grammar[maxnum];
// Ԥ���������Ų���ʽ�����±꣬û�еĵط�����Ϊ -1
extern int table[maxnum][maxnum];
// ��ʼ����
extern char start_char;

// ��ӡ��ǰ״̬
void printCurrentStatus(const char* s1, const char* s2, const string& s3) {
    cout << setw(Table_width) << s1 << setw(Table_width) << s2 << setw(Table_width) << s3 << endl;
}

// ��������
void analyze(const char* sentence, int len) {
    char str[300];
    strcpy(str, sentence);
    if (len == -1)
        len = strlen(str);
    str[len++] = '$'; // ��ĩβ���� '$'
    str[len] = 0;
	//���������Ǹ����봮ĩβ����'$'���Ա����ж��Ƿ����
    char stk[200]; // ����ģ��ջ
    int pos = 0;
    stk[pos++] = '$';
    stk[pos++] = start_char;
    stk[pos] = '\0';
	//���������ǳ�ʼ��ջ����ջ������Ϊ'$'��ջ������Ϊ��ʼ����
    cout << setw(Table_width) << "ջ" << setw(Table_width) << "����" << setw(Table_width) << "����" << endl;
    printCurrentStatus(stk, str, string("��ʼ"));
	//����Ĵ�����ʹ��ջ���з���
    for (int input_idx = 0; input_idx < len;) {
        char top = stk[--pos];
        stk[pos] = '\0';
		// ջ��Ϊ'$'�����봮ҲΪ'$'������
        if (top == '$') {
            if (str[input_idx] == '$') {
                printCurrentStatus("$", "$", string("����"));
                cout << "�����ɹ���" << endl;
                break;
            }
			// ջ��Ϊ'$'�����봮��Ϊ'$'������
            else {
                printCurrentStatus(stk, str + input_idx, string("����"));
                cerr << "����ջջ��Ϊ'$'������������δ������" << endl;
                return;
            }
        }

        int current_type = typeOf(top);
		// ջ��Ϊ�ս��
        if (current_type == Terminator) {
            if (top == str[input_idx]) {
				input_idx++; // ƥ��ɹ������봮ָ�����
                string res("ƥ�� ");
                printCurrentStatus(stk, str + input_idx, res + top);
            }
			// ջ���ս����������Ų�ƥ�䣬����
            else {
                printCurrentStatus(stk, str + input_idx, string("����"));
                cerr << "����ջջ��Ϊ�ս�� '" << top << "'�������������Ϊ '" << str[input_idx] << "'" << endl;
                return;
            }
        }
		// ջ��Ϊ���ս��
        else if (current_type == NonTerminator) {
            int g_index = table[indexOfNonT(top)][indexOfTerm(str[input_idx])];
			// ���������ж�Ӧ��
            if (g_index != -1) {
                // ������ʽ�Ҳ����ݵ�����ջ
                for (int j = grammar[g_index].size() - 1; j >= 3; j--) {
                    stk[pos++] = grammar[g_index][j];
                }
                stk[pos] = '\0';
                printCurrentStatus(stk, str + input_idx, grammar[g_index]);
            }
			// ��������û�ж�Ӧ�����
            else {
                printCurrentStatus(stk, str + input_idx, string("����"));
                cerr << "������ table[" << top << "][" << str[input_idx] << "] ��Ϊ�ա�" << endl;
                return;
            }
        }
        else {
            cerr << "��������" << endl;
            return;
        }
    }
}
