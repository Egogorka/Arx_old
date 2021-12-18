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
#include <queue>

template <typename T>
T& get_at(Vector2i start, vector<vector<T>>& array){
    return array[start.x()][start.y()];
}

void search_width (Vector2i start, vector<vector<int>>& array /*vector<vector<Vector2i>>& parents*/){

    int m = array[0].size();
    int n = array.size();
    std::queue<Vector2i> check;

    check.push(start);
    get_at(start,array) = 1;

    while (!check.empty()){
        auto current = check.front();
        check.pop();

        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if(i == 0 && j == 0) continue;
                auto next = current + Vector2i{i,j};

                //Check borders
                if(next.x() < 0 || next.y() < 0 ||
                   next.x() >= n || next.y() >= m) continue;

                // Skip obstacles
                if(get_at(next, array) == -2) continue;

                // Skip ones that have less length of path
                if (get_at(next, array) != -1 ) continue;

                get_at(next, array) = get_at(current, array) + 1;
                check.push(next);
//                get_at(next, parents) = current;
            }
        }
    }
}

void search_width (Vector2i start, vector<vector<int>>& array, vector<vector<Vector2i>>& parents){

    int m = array[0].size();
    int n = array.size();
    std::queue<Vector2i> check;

    check.push(start);
    get_at(start,array) = 1;

    while (!check.empty()){
        auto current = check.front();
        check.pop();

        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if(i == 0 && j == 0) continue;
                auto next = current + Vector2i{i,j};

                //Check borders
                if(next.x() < 0 || next.y() < 0 ||
                   next.x() >= n || next.y() >= m) continue;

                // Skip obstacles
                if(get_at(next, array) == -2) continue;

                // Skip ones that have less length of path
                if (get_at(next, array) != -1 ) continue;

                get_at(next, array) = get_at(current, array) + 1;
                check.push(next);
                get_at(next, parents) = current;
            }
        }
    }
}


list <Vector2i> PathTo (Vector2i start, Vector2i end, vector<vector<int>>& array )
{
    array[start.x()][ start.y()] = 1;
    // a little splint so path could lead to obstacle at end-point
    get_at(end, array) = -1;
    int m = array[0].size();
    int n = array.size();


//    vector<vector<Vector2i>> parents(n);
//    for(auto& item : parents){
//        item = vector<Vector2i>(m,Vector2i{-1,-1});
//    }
//
//    search_width(start, array, parents);
    search_width(start, array);

    if(get_at(end, array) == -1) return {};

//    Vector2i current = end;
//    list <Vector2i> path;
//    while (current.x() != start.x() and current.y() != start.y())
//    {
//        path.push_back(current);
//        current = get_at(current, parents);
//    }

    Vector2i current = end;
    list <Vector2i> path;
    Vector2i nextposition = current;
    path.push_back(end);
    int minemum = 10000;
    while (current.x() != start.x() and current.y() != start.y())
    {
        minemum = 10000;
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (i == 0 && j == 0) continue;

                Vector2i newposition = current + Vector2i {i,j};

                if (newposition.x() < 0 || newposition.y() < 0 || newposition.x() >= n || newposition.y() >= m) continue;
                if (array[newposition.x()][newposition.y()] == -2 ) continue;
                if (array[newposition.x()][ newposition.y()] < minemum)
                {
                    nextposition = newposition;
                    minemum = array[newposition.x()][ newposition.y()];
                }
            }
        }
        current = nextposition;
        path.push_back(current);
//        cout << current << endl;

    }

    path.push_back(start);
    path.reverse();

    cout << path.size() << endl;

    return path;

    return {};
}
int Test()
{
    int n = 5;
    int m = 5;
   list<Vector2i> list1;
    vector<vector<int>> vector_test {
        {-1,-1,-1,-1,-1},
        {-1,-2,-2,-2,-1},
        {-1,-1,-1,-1,-1},
        {-1,-2,-2,-2,-1},
        {-1,-1,-1,-1,-1}
    };

    list1 = PathTo(Vector2i {0,0},Vector2i {4,4},vector_test);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; ++j)
        {
            cout << vector_test[i][j] << ' ' ;
        }
        cout << endl;
    }
    cout << endl;

    for (auto &x : list1)
    {
        cout  << x << endl;
    }


    return 0;
};