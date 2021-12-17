//
// Created by ACER on 17.12.2021.
//

#include "PathTo.h"

#include "utility/Vector.h"
#include <list>
#include <vector>
#include <algorithm>

using namespace  std;


void Recursion (Vector2i in, int before, vector<vector<int>>& arr)
{
    int m = arr[0].size();
    int n = arr.size();

    if (arr[in.x()][in.y()] == -2) return;

    if (arr[in.x()][in.y()] != -1 &&
        arr[in.x()][in.y()] < before + 1 ) return ;

    auto temp = arr[in.x()][in.y()] = before + 1;
    for (int di = -1; di <= 1; di++ )
        for (int dj = -1; dj <= 1; dj++)
        {
            if( di == 0 and dj == 0 ) continue;

            Vector2i dvector {di, dj};
            if ((in + dvector).y() >= 0  and
                (in + dvector).x() >= 0  and
                (in + dvector).y() < m and
                (in + dvector).x() < n)
                Recursion(in + dvector, temp, arr);
        }
}

list <Vector2i> PathTo (Vector2i start, Vector2i end, vector<vector<int>>& array )
{
    array[start.x()][ start.y()] = 1;
    Recursion(start, 0, array);

    return {};
}
int Test()
{
    int n = 5;
    int m = 5;
    vector<vector<int>> vector_test {
        {-1,-1,-1,-1,-1},
        {-1,-2,-2,-2,-1},
        {-1,-1,-1,-1,-1},
        {-1,-2,-2,-2,-1},
        {-1,-1,-1,-1,-1}
    };
    PathTo(Vector2i {2,2},Vector2i {4,4},vector_test);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; ++j)
        {
            cout << vector_test[i][j] << ' ' ;
        }
        cout << endl;
    }




};