#include "common_header.h"
using namespace std;
//����ʽ������飨�������������ӡ�������ݹ飩
extern string grammar[maxnum];
extern int lines;
//���еķ��ս��
extern vector<char> nonT;
//ÿһ������ʽ�� first ���ϣ�ע�� '$' '@'
extern vector<char> firstP[maxnum];
//ÿһ�����ս���� first ���ϣ�ע�� '$' '@'
extern vector<char> firstN[maxnum];
//���� ���ս�� �� first ��
void getfirst(char NonTer)
{
	//�ҵ�������ս���� nonT �е��±�
	int index_NonTer = indexOfNonT(NonTer);
	for (int j = 0; j < lines; j++) //��������ʽ 
	{
		//�������ʽ���󲿲���������ս����������
		if (grammar[j][0] != NonTer)
			continue;
		bool keep = true;// �Ƿ���������
		//��������ʽ�Ҳ���3�������������󲿺͡�->��
		for (char c : grammar[j].substr(3)) {
			if (!keep)
				break;
			//������ս����ֱ�Ӽ���first��
			if (typeOf(c) == Terminator) {
				add_unique_item(firstN[index_NonTer], c);
				keep = false;
			}
			//����Ƿ��ս�����ݹ����
			else { // ���ս��
				keep = false;
				getfirst(c); // ��֮ǰ�ȵݹ����һ��
				for (char b : firstN[indexOfNonT(c)]) {
					if (b == '@')
						keep = true;
					else
						add_unique_item(firstN[index_NonTer], b);
				}
			}
		}
		// ������ keep ��Ϊ true, ��˵�� �Ҳ��ɿ�
		if (keep)
			add_unique_item(firstN[index_NonTer], '@');
	}
}
//������з��ս����first��
void getFirstN()
{
	//�������з��ս�������ÿһ�����ս����first����ע�������ǵݹ���⣬���Բ��õ����Ⱥ�˳��
	for_each(nonT.begin(), nonT.end(), getfirst);
}
//������в���ʽ�Ҳ���first�� 
void getFirstP()
{
	//�������в���ʽ
	for (int i = 0; i < lines; i++) {
		bool keep = true; // �Ƿ���������
		//��������ʽ�Ҳ���3�������������󲿺͡�->��
		for (char c : grammar[i].substr(3)) {
			//������ս����ֱ�Ӽ���first��
			if (!keep)
				break;
			if (typeOf(c) == Terminator) {
				add_unique_item(firstP[i], c);
				keep = false;
			}
			//����Ƿ��ս�����ݹ����
			else { 
				keep = false;
				for (char b : firstN[indexOfNonT(c)]) {
					if (b == '@')
						keep = true;
					else
						add_unique_item(firstP[i], b);
				}
			}
		}
		// ������ keep ��Ϊ true, ��˵�� ����ʽ �Ҳ��ɿ�
		if (keep)
			add_unique_item(firstP[i], '@');
	}
}