# guess_color
《世界游戏大全51》上有一个游戏，猜颜色。一共6种颜色，可以放在四个位置上，你每猜一次会告诉你你猜的答案与正确答案相比有几个全对，有几个半对。全对是指位置与颜色都对，半对是只有颜色对而位置不对。
我写了个程序帮我玩这个游戏，维护一个包含所有情况集合，我每输入一个猜测和对应的结果（全对/半对），程序就排除掉当前集合中不符合的情况，这样我就能从剩下的可能情况中选一个输入switch得到结果，然后重复此过程直到找到正确答案。
提问：有没有一种方法使得我猜到正确答案所需要的次数最少（平均来说）。

设全对个数为x，半对个数为y，将（x，y）视为一个符号。当剩余N种情况时，分别计算第i种情况与其余N-1种情况的x和y。符号（x，y）的概率为1/（N-1）×上述计算中对应x，y的个数。计算该信源的信息量，作为情况i的信息量。利用信息量对所有情况排序，选最大的作为下一轮的猜测。
运行程序，根据提示玩游戏就可以啦~~~
你可以下载源.cpp进行编译，也可以[点击此处下载程序](https://github.com/caoqiming/guess_color/releases/download/1.0/guess_color.exe)。
*输入数字1到6代表6个颜色，每个输入之间要有空格*
