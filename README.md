这是一个LL（1）的文法分析器，代码是基于：https://github.com/ishenmao/LL1-grammar-analyzer这位大佬写的4
我的代码主要修复了两个问题：
1.消除了输入串中不能有空格的情况，现在有空格也可以正确的识别并删除
2.可以分析并消除左递归，并显示消除左递归后的代码
还有一些新加的功能：1.保存分析的集合和分析表到本地文本文件；2.添加了一些注释
