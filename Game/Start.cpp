#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

void menu (RenderWindow & window, float w, float h) {
	Texture menuTexture1, menuTexture2, menuTexture3,menuTexture4,menuTexture5, menuTexture6, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("background1.png");
	menuTexture2.loadFromFile("background2.png");
	menuTexture3.loadFromFile("background3.png");
	menuTexture4.loadFromFile("background3.png");
	menuTexture5.loadFromFile("cloud1.png");
	menuTexture6.loadFromFile("cloud7.png");

    sf::Font font;// класс шрифта
    font.loadFromFile("CyrilicOld.TTF");
    Text text1;
    text1.setFont(font);
    text1.setCharacterSize(20);
    text1.setFillColor(sf::Color::White);


    text1.setString(" Начало");
    text1.setPosition (w/2 - w/8  , h/4);


	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), menu4(menuTexture4), menu5(menuTexture5), menu6(menuTexture6), cloud1(menuTexture5), cloud2 (menuTexture6);
	bool isMenu(true);
	int check = 0;
	menu1.setPosition(0, 0);
	menu2.setPosition(0, 0);
	menu3.setPosition(0, 0);
    cloud1.setPosition(w - 100, 0);
	cloud2.setPosition(0,0);



	//////////////////////////////МЕНЮ///////////////////
    //while (window.isOpen())
	while (isMenu)
	{
		//menu1.setColor(Color::White);
		//menu2.setColor(Color::White);
		//menu3.setColor(Color::White);

		if (IntRect(w/2 - w/8, h/4, w/8, h/8).contains(Mouse::getPosition(window)))
        {
            text1.setColor(Color::Blue);
            check = 1;
        }
        else
        {
            text1.setColor(Color::White);
            check = 0;
        }


		sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::MouseButtonPressed)
                if (check == 1)
                {
                    isMenu = false;//если нажали первую кнопку, то выходим из меню
                    window.close();
                }
        }

		window.clear(Color(129, 181, 221));

		//window.draw(menuBg);
		//window.draw(menu1);
		//window.draw(menu2);
		//window.draw(menu3);
		//window.draw(cloud1);
		//window.draw(cloud2);
        window.draw(text1);

		window.display();
	}
	////////////////////////////////////////////////////
}
