#include <SFML/Graphics.hpp>
#include <iostream>
#include <array>
#include <vector>

using namespace sf;
using namespace std;
int main()
{
	RenderWindow window(sf::VideoMode(640, 480), "Lesson 7. kychka-pc.ru");


    std::vector<int> m(2000,6);
    std::vector<int> m1(2000,2);
    m.insert( m.end(), m1.begin(), m1.end() );

    int i = 0;
	Texture herotexture;
	herotexture.loadFromFile("D:\\Game\\Enemy.png");

	Sprite herosprite;
	herosprite.setTexture(herotexture);
	herosprite.setTextureRect(IntRect(0, 192, 96, 96));
	herosprite.setPosition(250, 250);

	float CurrentFrame = 0;//хранит текущий кадр
	Clock clock;

	while (window.isOpen())
	{


		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
            //int i = 4;

        if (m[i] == 4)
        {
            CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
			herosprite.move(-0.1*time, 0);//происходит само движение персонажа влево
			i++;

        }
        if (m[i] == 6)
        {
            CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96

			herosprite.move(0.1*time, 0);//происходит само движение персонажа вправо
            i++;
        }
        if (m[i]== 2)
        {
            CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
			herosprite.move(0, 0.1*time);//происходит само движение персонажа вниз
			i++;

        }

        ///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) { //если нажата клавиша стрелка влево или англ буква А
			CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
			herosprite.move(-0.1*time, 0);//происходит само движение персонажа влево
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
			CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96

			herosprite.move(0.1*time, 0);//происходит само движение персонажа вправо

		}


		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
			CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
			herosprite.move(0, -0.1*time);//происходит само движение персонажа вверх
		}

		if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
			CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
			herosprite.move(0, 0.1*time);//происходит само движение персонажа вниз
		}

		window.clear();
		window.draw(herosprite);
		window.display();
	}

	return 0;
}
