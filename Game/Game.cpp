#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
using namespace sf;

namespace game {

    class Draw : public sf::Sprite {
    public:

        Draw() {}

        Draw(double sc, double w, double h, int m, int n, sf::Texture *tex) : sf::Sprite(*tex) {

            setPosition(h * m, h * n);
            setScale(sc, sc);

        }


    };


    class Resource : public Draw {
    public:
        int n, m;
        int wood = 0;
        int stone = 0;
        int fish = 0;

        Resource() {}

        Resource(double sc, double w, double h, int m, int n, sf::Texture *tex) : Draw(sc, w, h, n, m, tex) {}

    };

    class Tree : public Resource {
    public:

        Tree(double sc, double w, double h, int m, int n, sf::Texture *tex) : Resource(sc, w, h, n, m, tex) {}

        ~Tree() {


        }


    };

    class Stone : public Resource {
    public:

        Stone(double sc, double w, double h, int m, int n, sf::Texture *tex) : Resource(sc, w, h, n, m, tex) {}

    };

    class Grass : public Resource {
    public:
        Grass(double sc, double w, double h, int m, int n, sf::Texture *tex) : Resource(sc, w, h, n, m, tex) {}

    };


/*class Lake : public Resource
{
public:
    int check = 0;

    Lake(double w, double h, int m, int n,  sf::Color C): Resource(w, h, n, m, C){}

    void get_fish(Resource* R)
    {
        if (std::rand()%3 == 1) R->fish += 1;
    }
};
*/
    class Storehouse : public Draw {
    public:

        int MaxResource = 50;
        int Health = 100;

        Storehouse(double sc, double w, double h, int m, int n, sf::Texture *tex) : Draw(sc, w, h, n, m, tex) {}


    };

    int main() {
        int n = 30; // �����
        int m = 30; // ��������
        int h = 20; // ������ ������

        Resource R;


        sf::RenderWindow window(sf::VideoMode(h * m, h * n), "SFML works!");


        Texture texTree;
        texTree.loadFromFile("D:\\Game\\Tree2.png");

        Texture texStone;
        texStone.loadFromFile("D:\\Game\\Stone.png");

        Texture texGrass;
        texGrass.loadFromFile("D:\\Game\\Grass3.png");

        Texture texStore;
        texStore.loadFromFile("D:\\Game\\Store.png");


        vector<vector<Draw *>> v;
        for (int i = 0; i < n; i++) {
            vector<Draw *> v1(m, nullptr);
            v.push_back(v1);
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                v[i][j] = new Grass(0.9, h, h, i, j, &texGrass);
            }

        }

        for (int i = 0; i < 20; i++) {
            int rand1 = std::rand() % 20;
            int rand = std::rand() % 20;
            v[rand1][rand] = new Tree(0.2, h, h, rand1, rand, &texTree);
        }

        for (int i = 0; i < 30; i++) {
            int rand1 = std::rand() % 20;
            int rand = std::rand() % 20;
            if ((rand1 > 5) and (dynamic_cast<Tree *>(v[rand1 - 5][rand]) == nullptr))
                v[rand1][rand] = new Stone(0.2, h, h, rand1, rand, &texStone);
        }
/*

    for (int i = 40 ; i < 50 ; i++)
    {
        for (int j = 0; j < 10; j++)
        {
             v[i][j] = new Lake(h,h, i, j, sf::Color::Blue);

        }
    }


*/

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.mouseButton.button == sf::Mouse::Right) {
                    int Mouse_n = event.mouseButton.y / h;
                    int Mouse_m = event.mouseButton.x / h;
                    if (dynamic_cast<Tree *>(v[Mouse_m][Mouse_n]) != nullptr) {
                        v[Mouse_m][Mouse_n] = new Grass(0.9, h, h, Mouse_m, Mouse_n, &texGrass);
                        R.wood++;
                    }


                    if (dynamic_cast<Stone *>(v[Mouse_m][Mouse_n]) != nullptr) {
                        v[Mouse_m][Mouse_n] = new Grass(0.9, h, h, Mouse_m, Mouse_n, &texGrass);
                        R.stone++;
                    }

                    /*
                     if (dynamic_cast<Lake*>(v[Mouse_m][Mouse_n]) != nullptr )
                    {
                        dynamic_cast<Lake*>(v[Mouse_m][Mouse_n]) ->get_fish(&R);
                    }
                    */


                }

                // build Storehouse

                if (event.mouseButton.button == sf::Mouse::Left and R.wood >= 5) {
                    int Mouse_n = event.mouseButton.y / h;
                    int Mouse_m = event.mouseButton.x / h;

                    v[Mouse_n][Mouse_m] = new Storehouse(0.9, 2 * h, h, Mouse_n, Mouse_m, &texStore);
                    R.wood -= 5;

                }


                if (sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::R) {
                        cout << "Recource: Wood " << R.wood << " Stone " << R.stone << " Fish " << R.fish << endl;
                    }
                }
            }


            window.clear(sf::Color::Green);

            for (int i = m - 1; i >= 0; i--) {
                for (int j = n - 1; j >= 0; j--) {
                    if (dynamic_cast<Grass *>(v[i][j]) != nullptr) {

                        window.draw(*(v[i][j]));

                    }
                }

            }

            for (int i = m - 1; i >= 0; i--) {
                for (int j = n - 1; j >= 0; j--) {
                    if (dynamic_cast<Grass *>(v[i][j]) == nullptr) {

                        window.draw(*(v[i][j]));

                    }
                }

            }


            window.display();

        }

        return 0;
    }

}