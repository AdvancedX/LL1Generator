#include "common_header.h"
using namespace std;
//产生式存放数组（不含公共左因子、不含左递归）
extern string grammar[maxnum];
extern int lines;
//所有的非终结符
extern vector<char> nonT;
//每一个产生式的 first 集合，注意 '$' '@'
extern vector<char> firstP[maxnum];
//每一个非终结符的 first 集合，注意 '$' '@'
extern vector<char> firstN[maxnum];
//单个 非终结符 的 first 集
void getfirst(char NonTer)
{
	//找到这个非终结符在 nonT 中的下标
	int index_NonTer = indexOfNonT(NonTer);
	for (int j = 0; j < lines; j++) //遍历产生式 
	{
		//如果产生式的左部不是这个非终结符，就跳过
		if (grammar[j][0] != NonTer)
			continue;
		bool keep = true;// 是否继续向后检查
		//遍历产生式右部，3的作用是跳过左部和“->”
		for (char c : grammar[j].substr(3)) {
			if (!keep)
				break;
			//如果是终结符，直接加入first集
			if (typeOf(c) == Terminator) {
				add_unique_item(firstN[index_NonTer], c);
				keep = false;
			}
			//如果是非终结符，递归求解
			else { // 非终结符
				keep = false;
				getfirst(c); // 收之前先递归求解一下
				for (char b : firstN[indexOfNonT(c)]) {
					if (b == '@')
						keep = true;
					else
						add_unique_item(firstN[index_NonTer], b);
				}
			}
		}
		// 如果最后 keep 仍为 true, 则说明 右部可空
		if (keep)
			add_unique_item(firstN[index_NonTer], '@');
	}
}
//求解所有非终结符的first集
void getFirstN()
{
	//遍历所有非终结符，求解每一个非终结符的first集，注意这里是递归求解，所以不用担心先后顺序
	for_each(nonT.begin(), nonT.end(), getfirst);
}
//求解所有产生式右部的first集 
void getFirstP()
{
	//遍历所有产生式
	for (int i = 0; i < lines; i++) {
		bool keep = true; // 是否继续向后检查
		//遍历产生式右部，3的作用是跳过左部和“->”
		for (char c : grammar[i].substr(3)) {
			//如果是终结符，直接加入first集
			if (!keep)
				break;
			if (typeOf(c) == Terminator) {
				add_unique_item(firstP[i], c);
				keep = false;
			}
			//如果是非终结符，递归求解
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
		// 如果最后 keep 仍为 true, 则说明 产生式 右部可空
		if (keep)
			add_unique_item(firstP[i], '@');
	}
}