#include <SFML/Graphics.hpp>
#include <chrono>
#include<ctime>
#include <fstream>
# include <random>
#include <iostream>
#include <cmath>
#include <vector>
#include <iostream>
#include <sstream>

using namespace sf;
using namespace std;

class Key
{
    public:
    int x;
    int y;
};

class Rocket
{

public:
    int x;
    int y;
    int damage;

};

class Square
{
public:

        int x; // координаты центора квадрата
        int y;
        int r;// радиус описанной окружности
        int vx;
        int vy;
        int health;

};

class Barrier
{

public:
    int x;// координаты левого угла
    int y;
    int* arr;
    int dx; // длина прямоугольника
    int dy; // ширина прямоугольника

    Barrier(int inx, int iny, int indx,int indy) // конструктор
     {
        x = inx;
        y = iny;
        dx = indx;
        dy = indy;
    }

};
class Gas
{
  public:
        int x;
        int y;
        int vx;
        int vy;



};
const int H = 500; //
const int L = 500; //
const int N = 3;
const int r = 15;
const int G_up = 70;
const int G_down = 40;
const int G_left = 70;

int main()
{
    sf::Font font;// класс шрифта
    font.loadFromFile("CyrilicOld.TTF");


    int check = -1; // режим игры

    int g_up = 0; // вначале прятиваем вниз
    int g_down = G_down;
    int g_left = 0;
    srand(time(NULL));
    RenderWindow window(VideoMode(H,L), "Movement");

    int tr_r = 10;



    vector<Key>  keys;

    int g = 10;
    Key element;


    element.x = L - 50;
    element.y = 50;
    keys.push_back(element);

    element.x = 50 ;
    element.y = H - 50;
    keys.push_back(element);

    element.x = L/2;
    element.y = H/2;
    keys.push_back(element);



    Gas* mass = new Gas[N];
    //Barrier* mass_of_bar = new Barrier[4];
    vector<Barrier> v;

    Square object;
    object.r = 10;
    object.health = 1000;
    object.x = 100 ;
    object.y = 100;
    object.vy = -40;



    for (int i = 0; i < N; i++ )
    {
        (mass + i)->x = rand()%L +50;
        (mass + i)->y = rand()%H + 50 ;
        mass[i].vx = rand()%200;
        mass[i].vy = rand()%200;
    }


    // Переменные для таймера и задержки
	float timer = 0, delay = 0.1;

	// Часы (таймер)
	Clock clock;


    while(window.isOpen())
    {

        if (check == -1)
        {
            window.clear(Color:: White);
            int R = 40;
            int Button_x = L/2 - R;
            int Button_y = H/2 + R;

            CircleShape circle5(R, 4);
            circle5.setFillColor(Color(230, 0, 230));
            circle5.move(Button_x, Button_y);
            window.draw(circle5);


        Text text1;
        text1.setFont(font);
        text1.setCharacterSize(20);
        text1.setFillColor(sf::Color::Blue);


        text1.setString("Квадрат борится за справедливость! ");
        text1.setPosition (L/4  , H/4);
        window.draw(text1);



            Event event1;
            while (window.pollEvent(event1))
            {
                if (event1.type == Event::Closed) window.close();
                if (event1.type == sf::Event::MouseButtonPressed)
                {
                    if (event1.mouseButton.button == sf::Mouse::Left)
                    {
                        int Mouse_x = event1.mouseButton.x;
                        int Mouse_y = event1.mouseButton.y;
                        if ( Mouse_x < Button_x + 2*R and  Mouse_x > Button_x and Mouse_y > Button_y and  Mouse_y < Button_y + R* 2)
                        {
                            check ++;
                        }


                    }
                }


            }


        }


        if (check >= 0 and check < 3)
        {



            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;


            Event event;


        if (object.health > 0 )
        {


            while (window.pollEvent(event))
            {



                if (event.type == Event::Closed) window.close();
                //if (object.health < 0) window.close();
                if (event.key.code == Keyboard::Up)
                {
                    if (check == 0)// притяжение вниз
                    {
                        object.vy = -80;
                        g_down = G_down;
                    }

                    if (check == 1 or check == 2) // притяжение влево и вверх
                    {
                        object.y -= 2;

                    }

                }

                if (event.key.code == Keyboard::Down)
                {



                    if (check == 0 or check == 1) object.y += 2; // притяжение вниз и влева
                    if (check == 2) // притяжение вверх
                    {
                        object.vy = 80;
                        g_down = - G_down;
                    }

                }

                if (event.key.code == Keyboard::Left) object.x -= 2;
                if (event.key.code == Keyboard::Right)
                {
                    if (check == 0 ) object.x += 2; // притяжение вниз и вверх
                    if (check == 2) object.x += 2;
                    if (check == 1)
                    {
                        object.vx = -80;
                        g_left = G_left;

                    }

                }


                if (event.key.code == Keyboard::W)
                {
                    Barrier bar_up{object.x + r - 25 ,0  , 50, object.y }; // x, y, dx, dy  object.x - верхний левый угол
                    v.push_back(bar_up);
                }



                if (event.key.code == Keyboard::D)
                {
                    Barrier bar_up{object.x + 2* object.r , object.y + object.r - 25 , 4,50}; // x, y, dx, dy
                    v.push_back(bar_up);
                }

                 if (event.key.code == Keyboard::S)
                {
                    Barrier bar_up{object.x + r - 25 , object.y + 2*object.r  , 50, H - object.y}; // x, y, dx, dy  object.x - верхний левый угол
                    v.push_back(bar_up);
                }



                if (event.key.code == Keyboard::A)
                {
                    Barrier bar_up{0, object.y + r - 25  , object.x - 2*object.r ,50}; // x, y, dx, dy
                    v.push_back(bar_up);
                }

            }





            if (timer > delay )
            {

                // движение шаров
                for (int i = 0; i < N; i++)
                {


                    if ((mass[i].x  + r)>= L  or (mass[i].x - r) <= 10)
                    {
                        mass[i].vx = - mass[i].vx ;
                        mass[i].x += mass[i].vx * delay;

                    }
                    if ((mass[i].y + r) >= H   or (mass[i].y  - r) <= 10)
                    {

                        mass[i].vy = - mass[i].vy ;
                        mass[i].y += mass[i].vy * delay;

                    }


                    int dx = abs (mass[i].x - object.x);
                    int dy = abs (mass[i].y - object.y);
                    if (dx < r && dy < r) object.health += 10; // пополнение здоровья игрока

                }

                // движение шаров
                for (int i = 0; i < N; i++)
                {
                    mass[i].x += mass[i].vx * delay;
                    mass[i].y += mass[i].vy * delay ;

                }

                // движение объекта

                object.vx += g_left * delay;
                object.vy += g_down * delay;
                object.y += object.vy * delay + g_down * delay* delay/2;
                object.x -= object.vx * delay + g_left * delay* delay/2;

                //  взаимодействие объекта с барьером
                for (int i = 0; i < v.size(); i++)
                {
                    int y = (object.y + object.vy * delay + g_down * delay* delay/2 ); // координата левого угла;
                    int x = object.x - object.vx * delay + g_left * delay* delay/2;
                    if (check == 0 )
                    {
                            if ( y > v[i].y and object.x < v[i].x +  v[i].dx  and object.x > v[i].x   and  y < v[i].y  + v[i].dy)
                        {
                            object.vy = 0;
                            g_down = 0;


                        }
                        else g_down = G_down;
                    }


                    if (check == 1)
                    {

                        if (x < v[i].x + v[i].dx  and  y < v[i].y + v[i].dy and y > v[i].y)
                        {
                            object.vx = 0;
                            g_left = 0;

                        }

                        else g_left = G_left;

                    }

                    if (check == 2)
                    {

                        if ( y > v[i].y and object.x < v[i].x +  v[i].dx  and object.x > v[i].x   and  y < v[i].y  + v[i].dy)
                        {
                            object.vy = 0;
                            g_down = 0;


                        }
                        else g_down = -G_down;

                    }




                }




                // ключ и объект

                for (int i = 0; i < keys.size(); i++)
                {
                    float dx = (keys[i].x -  tr_r  - object.x + object.r);
                    float dy = (keys[i].y -  tr_r  - object.y + object.r) ;
                    if ((dx*dx + dy*dy) < 1600)
                    {

                        object.health -= 10;

                    }


                    if (abs(dx)  < 5 && abs(dy) < 5) // освобождение заложника
                    {
                        object.vx = 0;
                        object.vy = 0;
                        keys.erase(keys.begin()+i);
                        v.clear();
                        check ++;


                    }
                }

                // проверка на выход за границы
                if (object.x < 0 or object.x > L or object.y < 0 or object.y > H) object.health = 0;

                timer = 0;

            }

        }

        window.clear(Color:: White);





        if (check == 1)
        {
            g_down = 0;
            g_left = G_left;
        }

        if (check == 2)
        {
            g_down = -G_down;
            g_left = 0;

        }

       for (int i = 0; i < v.size(); i++) // барьеры
        {
            RectangleShape rectangle(Vector2f(v[i].dx, v[i].dy));
            rectangle.move(v[i].x,v[i].y );
            rectangle.setFillColor(Color(230, 230, 230));
            window.draw(rectangle);
        }

        for (int i = 0; i < keys.size(); i++ ) // ключи
        {


            CircleShape circle5(40);
            circle5.setFillColor(Color(0, 0, 230));
            circle5.move(keys[i].x + (tr_r - 40)/sqrt(2) , keys[i].y  + (tr_r - 40)/sqrt(2));
            window.draw(circle5);

            CircleShape triangle(tr_r, 3);
            triangle.setFillColor(Color(230, 230, 0));
            triangle.move(keys[i].x, keys[i].y);
            //cout << keys[i].x;
            window.draw(triangle);


        }



            for (int i = 0; i < N; i++ ) // рисую круги
        {
            CircleShape circle(r);
            circle.setFillColor(Color(0, 230, 230));
            circle.move(mass[i].x, mass[i].y);
            window.draw(circle);


        }

        // рисую объект
        CircleShape circle1(object.r, 4);
        circle1.setFillColor(Color(230, 0, 230));
        circle1.move(object.x, object.y);
        window.draw(circle1);


        // вывод на экран здоровье персонажа


        Text text;
        text.setFont(font);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Blue);

        stringstream objectHealth;
        objectHealth << object.health;
        text.setString(" Здоровье:" + objectHealth.str());
        text.setPosition (L/2, 0);
        window.draw(text);
        }

        if (object.health <= 0)
        {


            Event event1;
        while (window.pollEvent(event1))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event1.type == Event::Closed)
			{
				// тогда закрываем его
				window.close();
			}
		}

        Text text2;
        text2.setFont(font);
        text2.setCharacterSize(35);
        text2.setFillColor(sf::Color::Blue);


        text2.setString("Ты проиграл ! ");
        text2.setPosition (L/4  , H/4);
        window.draw(text2);

        }

        if (check == 3)
        {

            window.clear(Color:: White);
        Text text1;
        text1.setFont(font);
        text1.setCharacterSize(20);
        text1.setFillColor(sf::Color::Blue);


        text1.setString("Ты победил ! ");
        text1.setPosition (L/4  , H/4);
        window.draw(text1);
        Event event;
                    while (window.pollEvent(event))
            {



                if (event.type == Event::Closed) window.close();
                //if (object.health < 0) window.close();
            }

        }



		window.display();

    }



    delete[] mass;
    return 0;
}
