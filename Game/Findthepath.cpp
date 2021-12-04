#include<iostream>
#include<vector>
#include <list>
#include <algorithm>
#include <array>
using namespace std;

const int  Max = 1000000000;
 int minimum(int a, int b)
 {
    if (min(a, b) == 0 and  max (a, b) == 0 ) return Max ;
    if (min (a,b) == 0 and max (a,b) != 0) return max(a,b);
    if (min (a,b) != 0) return min(a,b);

 }
void Alg ( vector<vector<int>>  v, int starn, int starm)
{
    int endm = 2;
    int endn = 2;
    int i = starn;
    int j = starm;


    /*
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {1, 1, 0, 1}
    */

    for (int i = 0 ; i < 3; i++ )
    {
        for (int j = 0; j < 4; j++)
        {

            if (i != 0 and i != 2 and j!= 0 and j!= 3)
            {


                list<int> elem{v[i-1][j], v[i][j-1],v[i+1][j], v[i][j+1]};

                elem.remove_if([](int n){return (n == 0 or n == 1);});
                // нужно пон€ть что делать если все элементы удалены
                elem.sort();
                v[i][j] = elem.front();
            }



        }
    }


   for (int i = 0 ; i < 3; i++ )
    {
        for (int j = 0; j < 4; j++)
        {
            cout << v[i][j] << ' ';
        }
    cout << endl;

    }

}
int main()
{
    vector <vector<int> > v =
    {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {1, 1, 0, 1}
    };


    Alg(v, 1, 0);

    return 0;
}
/*  0   0   0   0
    1   1   1   0
        0   50   0
    1   1   1   60
    0   0   0   0

        78
    45      78
*/
