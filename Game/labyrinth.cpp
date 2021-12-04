#include"Game.cpp"
#include <vector>

using namespace std;

void foo(int n, int m, vector<vector<Draw*>> v)
{

    vector<vector<int>> mas;
    for (int i =0; i < n ;i ++)
    {
        vector<int> m1(m, -1);
        mas.push_back(m1);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (v[i][j]!= nullptr ) mas[i][j] = -2;

        }

    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << mas[i][j] << ' ';

        }
        cout << endl;
    }


}
