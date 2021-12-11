#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Start.cpp"
#include <memory>
using namespace std;
using namespace sf;


class Draw : public sf::Sprite
{
public:

    Draw() {}
    Draw(double sc, double w, double h, int n, int m, sf::Texture* tex): sf::Sprite(*tex)
    {

        setPosition(h*n, h*m);
        setScale(sc, sc);

    }


};



class Resource: public Draw
{
public:
    int n, m;
    int wood = 0;
    int stone = 0;
    int fish = 0;
    Resource() {}
    Resource(double sc,double w, double h, int m, int n,  sf::Texture *tex ): Draw( sc, w, h, n, m,  tex){}

};

class Tree:public Resource
{
public:

    Tree(double sc,double w, double h, int n, int m,  sf::Texture* tex): Resource(sc, w, h, n, m, tex){}
    ~Tree ()
    {


    }


};

class Stone : public Resource
{
    public:

    Stone(double sc, double w, double h, int m, int n,  sf::Texture* tex): Resource(sc, w, h, n, m, tex){}

};
class Grass : public Resource
{
public:
    Grass(double sc, double w, double h, int m, int n,  sf::Texture* tex): Resource(sc, w, h, n, m, tex){}

};



class Tower : public Draw
{
public:
     Tower(double sc,double w, double h, int m, int n, sf::Texture* tex): Draw(sc,w, h, n, m, tex) {}


};
class Storehouse : public Draw
{
public:

    int MaxResource = 50;
    int Health = 100;

    Storehouse(double sc,double w, double h, int m, int n, sf::Texture* tex): Draw(sc,w, h, n, m, tex) {}


};

vector<pair<int, int>> foo(int n, int m, vector<vector<Draw*>> v, int startn, int startm, int endn, int endm) // возращает путь от конца к началу, включая конечную и начальную точку
{

    vector<vector<int>> mas;
    vector<pair<int, int>> path;


    for (int i =0; i < n ;i ++)
    {
        vector<int> m1(m, -1);
        mas.push_back(m1);
    }
// -2 - преграда
// -1  пустота
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i< m; i++)
        {
            if ((v[j][i]) != nullptr ) mas[j][i] = -2;

        }

    }
    startm = 0;
    startn = 1;

    mas[endn][endm] = 10000;
    mas[startn][startm] = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
           cout << mas[i][j];

        }
        cout << endl;

    }
    cout << "After" << endl;

// первая то есть n это строка, вторая то есть m столбец
// волновой алгоритм
    while(mas[endn][endm] == 10000)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
               if (mas[i][j] == -1 or mas[i][j] == -2) continue;

                const int  num = mas[i][j] + 1;

                if (j > 0)
                    if (mas[i][j - 1] != -2  )
                {
                    if (mas[i][j-1] == -1)   mas[i][j - 1] = num;
                    else mas[i][j-1] = min(mas[i][j - 1], num);

                }
                if (j < n - 1)
                    if ( mas[i][j +1] != -2  )
                {
                    if (mas[i][j + 1] == -1)  mas[i][j + 1] = num;
                    else mas[i][j+1] = min(mas[i][j + 1], num);

                }

                if (i > 0)
                    if (mas[i - 1][j] != -2  )
                {
                    if (mas[i - 1][j] == -1)  mas[i - 1][j] = num;
                    else mas[i - 1][j] = min(mas[i - 1][j], num);

                }

                if (i < m - 1)
                    if (mas[i+1][j] != -2  )
                {
                    if (mas[i + 1][j] == -1)  mas[i + 1][j] = num;
                    else mas[i + 1][j] = min(mas[i + 1][j], num);

                }
            }

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

    cout << endl;


    // по жадному алгоритму нахожу путь
    int i = endn;
    int j = endm;
    int minemum = 100000;
    int i_next = 0;
    int j_next  =0;
    while( i != startn or j != startm)
    {
                path.push_back(make_pair(i,j));
                 //cout << i <<' '<<j<< endl;

                if (j > 0 and mas[i][j - 1] != -2  )
                {
                    if (mas[i][j-1] < minemum)
                    {
                        i_next = i;
                        j_next = j-1;
                        minemum = mas[i][j-1];
                    }


                }
                if (j < m - 1 and mas[i][j +1] != -2  )
                {

                    if (mas[i][j+1] < minemum)
                    {
                        i_next = i;
                        j_next = j+1;
                        minemum = mas[i][j+1];
                    }
                }

                if (i > 0 and mas[i - 1][j] != -2  )
                {

                    if (mas[i-1][j] < minemum)
                    {
                        i_next = i-1;
                        j_next = j;
                        minemum = mas[i-1][j];
                    }

                }

                if (i < n - 1 and mas[i+1][j] != -2  )
                {
                   if (mas[i+1][j] < minemum)
                    {
                        i_next = i+1;
                        j_next = j;
                        minemum = mas[i+1][j];
                    }


                }

                i = i_next;
                j = j_next;

    }
    //cout <<  startn << ' ' << startm <<  endl;
    path.push_back(make_pair(startn, startm));
    return path;
}

int main()
{
    int n = 30; // строк
    int m = 30; // столбцов
    int h = 30; // ширина клетки

    Resource R;




    sf::RenderWindow window(sf::VideoMode(h*m, h*n), "SFML works!");


    Texture texTree;
    texTree.loadFromFile("C:\\Users\\ACER\\Arx\\Game\\Texture\\Tree2.png");

    Texture texStone;
    texStone.loadFromFile("C:\\Users\\ACER\\Arx\\Game\\Texture\\Stone.png");



    Texture texStore;
    texStore.loadFromFile("C:\\Users\\ACER\\Arx\\Game\\Texture\\Store.png");

    Texture texTower;
    texTower.loadFromFile("C:\\Users\\ACER\\Arx\\Game\\Texture\\Range.png");

    Texture texBook;
    texBook.loadFromFile("C:\\Users\\ACER\\Arx\\Game\\Texture\\Book.png");
    Sprite Book(texBook);

    Book.setPosition(0,0);

    vector<vector<Draw*>> v;
    for (int i =0; i < n ;i ++)
    {
        vector<Draw*> v1(m, nullptr);
        v.push_back(v1);
    }


    v[10][0] = new Tree(0.2,h,h, 10, 0, &texTree);
    v[10][5] = new Tree(0.2,h,h,  10,  5, &texTree);
    v[15][15] = new Tree(0.2,h,h,  15,  15, &texTree);
    v[3][3] = new Tree(0.2,h,h,  3,  3, &texTree);
    v[8][3] = new Tree(0.2,h,h,  8,  3, &texTree);
    v[20][3] = new Tree(0.2,h,h,  20,  3, &texTree);
    v[7][9] = new Tree(0.2,h,h,  7,  9, &texTree);

/* for (int i = 0 ; i < 20 ; i++)
    {
            int rand1 =  std::rand()% n ;
            int rand =  std::rand()% m;
           if (dynamic_cast<Tree*>(v[rand1][rand]) == nullptr) v[rand1][rand] = new Stone(0.2, h,h, rand1, rand, &texStone);
    }

*/

/*

    for (int i = 40 ; i < 50 ; i++)
    {
        for (int j = 0; j < 10; j++)
        {
             v[i][j] = new Lake(h,h, i, j, sf::Color::Blue);

        }
    }


*/

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();







                if (event.mouseButton.button == sf::Mouse::Left )
                {
                    int Mouse_n = event.mouseButton.y/h;
                    int Mouse_m = event.mouseButton.x/h;
                    if ( 0 <=  Mouse_m  and Mouse_m < m and  0 <= Mouse_n and Mouse_n < n) foo( n, m, v,20,0, Mouse_n, Mouse_m);

                }



        }



        window.clear(sf::Color::Green);

		for (int i = m-1; i >= 0; i--)
        {
            for (int j = n-1; j >= 0; j--)
            {
                if ((v[i][j]) != nullptr)
                {

                    window.draw(*(v[i][j]));

                }
            }

        }



        window.draw(Book);

		window.display();

    }

    return 0;
}

