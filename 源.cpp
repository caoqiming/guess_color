#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
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



pair<int, int> check(vector<int> guess, vector<int> truth) {//x��� yȫ��
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

void get_best(set<vector<int>>& all) {
    int n = all.size();
    if (n == 1)
        return;
    vector<float>information(n, 0);
    int i = 0;
    for (auto& it : all) {
        vector<vector<int>>number(5, vector<int>(5, 0));//����Ƶ��
        for (auto& it2 : all) {//ͳ��
            auto temp = check(it, it2);
            number[temp.first][temp.second]++;
        }
        /*
        for (int x = 0; x < 5; ++x) {//���Ƶ��
            for (int y = 0; y <= x and y < 4; ++y) {
                cout << number[x][y]<<" ";
            }
            cout << endl;
        }
        */
        //����Ϣ��
        float probability = 1 / (n-static_cast<float>(1));
        float the_info=0;//��ǰ���ŵ���Ϣ��
        for (int x = 0; x < 5; ++x) {
            for (int y = 0; y <= x and y<4; ++y) {//ȫ�Ը�����Ȼ���ܴ��ڰ�Ը���
                if (number[x][y] == 0)
                    continue;
                the_info -= probability * number[x][y] * log2(probability * number[x][y]);
            }
        }
        information[i] = the_info;
        ++i;
    }
    
    float best_info = *max_element(information.begin(), information.end());
    i = 0;
    int j = 0;//�������ƻ���
    cout << "���²²���Ի�������Ϣ����"<< best_info<<"bit" <<endl;
    for (auto& it : all) {
        if (information[i++] == best_info) {
            cout << it[0] << " " << it[1] << " " << it[2] << " " << it[3] << "//";
            ++j;
            if (j % 5 == 0)
                cout << endl;
        }
    }
    cout << endl;
}


float test_get_info(vector<int>& it,set<vector<int>>& all) {
    int n = all.size();
    vector<vector<int>>number(5, vector<int>(5, 0));//����Ƶ��
    for (auto& it2 : all) {//ͳ��
        auto temp = check(it, it2);
        number[temp.first][temp.second]++;
    }
    /*
    for (int x = 0; x < 5; ++x) {//���Ƶ��
        for (int y = 0; y <= x and y < 4; ++y) {
            cout << number[x][y]<<" ";
        }
        cout << endl;
    }
    */
    //����Ϣ��
    float probability = 1 / (n - static_cast<float>(1));
    float the_info = 0;//��ǰ���ŵ���Ϣ��
    for (int x = 0; x < 5; ++x) {
        for (int y = 0; y <= x and y < 4; ++y) {//ȫ�Ը�����Ȼ���ܴ��ڰ�Ը���
            if (number[x][y] == 0)
                continue;
            the_info -= probability * number[x][y] * log2(probability * number[x][y]);
        }
    }
 
    return the_info;

}


int main() {
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
    cout << "��ʼ�����" << endl;
    vector<int>test({1,1,2,2});

    int runtime = 1;
    while (all.size() > 0) {
        cout << "��ǰʣ�����" << all.size() << "�֣�" << endl;
        if (runtime++ == 1) {
            cout << "ֻҪ��4����ͬ�����־Ϳ��Ի�������Ϣ����2.74189bit" << endl;//1 1 2 2 ֻ��0.512668������Ϣ��
        }
        else {
            show_all(all);
            //������Ѳ²�
            get_best(all);
        }

        

        vector<int>temp(4);
        cout << "������²�:" << endl;
        cin >> temp[0] >> temp[1] >> temp[2] >> temp[3];
        cout << "�������Ӧ���ȫ�ԡ���ԣ���Ը���������ȫ�Ը�����:" << endl;
        int x, y;
        cin >> y >> x;
        x += y;
        paichu(all, temp, x, y);
    }
    cout << "�����ڿ��ܵĽ�";
    return 0;
}
