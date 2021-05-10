#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
#include<random>
#include<ctime>
using namespace std;
void pailie(set<vector<int> >& all, int a, int b, int c, int d) {
    vector<int>temp(4);
    for (int i = 0; i < 4; ++i) {

        temp[i] = a;
        for (int j = 0; j < 4; ++j) {
            if (j == i) {
                continue;
            }
            temp[j] = b;
            for (int k = 0; k < 4; ++k) {
                if (k == i or k == j) {
                    continue;
                }
                temp[k] = c;
                for (int m = 0; m < 4; ++m) {
                    if (m == i or m == j or m == k) {
                        continue;
                    }
                    temp[m] = d;
                    all.insert(temp);
                }
            }
        }
    }
}



pair<int, int> check(vector<int> guess, vector<int> truth) {//x半对 y全对
    int x = 0, y = 0;
    for (int i = 0; i < 4; ++i) {
        if (guess[i] == truth[i])
            ++y;
    }
    for (int i = 1; i <= 6; ++i) {
        if (count(guess.begin(), guess.end(), i) == 1 and count(truth.begin(), truth.end(), i) == 1) {
            ++x;
        }
    }
    return make_pair(x, y);
}

void paichu(set<vector<int>>& all, vector<int>guess, int x, int y) {
    auto it = all.begin();
    while (1) {
        pair<int, int>ans = check(guess, *it);
        if (x != ans.first or y != ans.second) {
            it = all.erase(it);
            if (it != all.end())
                continue;
            else
                return;
        }
        ++it;
        if (it == all.end())
            return;

    }

}

void show_all(set<vector<int>>& all) {
    int i = 0;
    for (auto& it : all) {
        cout << it[0] << " " << it[1] << " " << it[2] << " " << it[3] << "//";
        ++i;
        if (i % 5 == 0)
            cout << endl;
    }
    cout << endl;
}

int get_best(set<vector<int>>& all) {
    int n = all.size();
    if (n == 1)
        return 0;
    vector<float>information(n, 0);
    int i = 0;
    for (auto& it : all) {
        vector<vector<int>>number(5, vector<int>(5, 0));//符号频数
        for (auto& it2 : all) {//统计
            auto temp = check(it, it2);
            number[temp.first][temp.second]++;
        }

        //算信息量
        float probability = 1 / (n - static_cast<float>(1));
        float the_info = 0;//当前符号的信息量
        for (int x = 0; x < 5; ++x) {
            for (int y = 0; y <= x and y < 4; ++y) {//全对个数必然不能大于半对个数
                if (number[x][y] == 0)
                    continue;
                the_info -= probability * number[x][y] * log2(probability * number[x][y]);
            }
        }
        information[i] = the_info;
        ++i;
    }

    int index = max_element(information.begin(), information.end())- information.begin();

    return index;
}

int get_worst(set<vector<int>>& all) {
    int n = all.size();
    if (n == 1)
        return 0;
    vector<float>information(n, 0);
    int i = 0;
    for (auto& it : all) {
        vector<vector<int>>number(5, vector<int>(5, 0));//符号频数
        for (auto& it2 : all) {//统计
            auto temp = check(it, it2);
            number[temp.first][temp.second]++;
        }

        //算信息量
        float probability = 1 / (n - static_cast<float>(1));
        float the_info = 0;//当前符号的信息量
        for (int x = 0; x < 5; ++x) {
            for (int y = 0; y <= x and y < 4; ++y) {//全对个数必然不能大于半对个数
                if (number[x][y] == 0)
                    continue;
                the_info -= probability * number[x][y] * log2(probability * number[x][y]);
            }
        }
        information[i] = the_info;
        ++i;
    }

    int index = min_element(information.begin(), information.end()) - information.begin();

    return index;
}


int get_random(set<vector<int>>& all) {
    int n = all.size();
    return rand()%n;
}
float test_get_info(vector<int>& it, set<vector<int>>& all) {
    int n = all.size();
    vector<vector<int>>number(5, vector<int>(5, 0));//符号频数
    for (auto& it2 : all) {//统计
        auto temp = check(it, it2);
        number[temp.first][temp.second]++;
    }
    //算信息量
    float probability = 1 / (n - static_cast<float>(1));
    float the_info = 0;//当前符号的信息量
    for (int x = 0; x < 5; ++x) {
        for (int y = 0; y <= x and y < 4; ++y) {//全对个数必然不能大于半对个数
            if (number[x][y] == 0)
                continue;
            the_info -= probability * number[x][y] * log2(probability * number[x][y]);
        }
    }

    return the_info;

}


int main() {
    srand((int)(time(NULL)));
    set<vector<int>>all;
    pailie(all, 1, 2, 3, 4);
    pailie(all, 1, 2, 3, 5);
    pailie(all, 1, 2, 3, 6);
    pailie(all, 1, 2, 4, 5);
    pailie(all, 1, 2, 4, 6);
    pailie(all, 1, 2, 5, 6);
    pailie(all, 1, 3, 4, 5);
    pailie(all, 1, 3, 4, 6);
    pailie(all, 1, 3, 5, 6);
    pailie(all, 1, 4, 5, 6);
    pailie(all, 2, 3, 4, 5);
    pailie(all, 2, 3, 4, 6);
    pailie(all, 2, 3, 5, 6);
    pailie(all, 2, 4, 5, 6);
    pailie(all, 3, 4, 5, 6);
    cout << "初始化完毕" << endl;
    set<vector<int>>temp;
    int sum_times = 0;
    int statistic[6] = { 0 };
    for (auto &it:all) {
        vector<int> true_ans = it;
        temp = all;
        int runtime = 0;
        vector<int>guess({ 1,2,3,4 });
        bool correct = false;
        while (temp.size() > 1) {
            
            if (runtime++ != 0) {
                int index= get_best(temp);//在这里采用不同的函数测试get_best，get_worst，get_random
                auto it2 = temp.begin();
                while (index--) {
                    ++it2;
                }
                guess = *it2;
            }
            auto x_y = check(guess, true_ans);
            if (x_y.second == 4) {//直接猜对了
                correct = true;
            }
            paichu(temp, guess, x_y.first, x_y.second);
        }
        if (!correct) {//剩最后一种可能的时候，猜测次数需要加一，如果是直接猜中的就不用加
            runtime++;
        }
        //cout << runtime << endl;

        statistic[runtime - 1]++;
        sum_times += runtime;
    }
    cout << statistic[0] << " " << statistic[1] << " " << statistic[2] << " " << statistic[3] << " " << statistic[4] << " " << statistic[5] << endl;
    cout << float(sum_times) / all.size()+1;
    return 0;
}
