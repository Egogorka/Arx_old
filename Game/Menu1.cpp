#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

void menu (RenderWindow & window, float w, float h) {


    sf::Font font;// ����� ������
    font.loadFromFile("CyrilicOld.TTF");
    Text text1;
    text1.setFont(font);
    text1.setCharacterSize(20);
    text1.setFillColor(sf::Color::White);


    text1.setString(" ���������");
    text1.setPosition (w/2 - w/8  , h/4);



	bool isMenu(true);




	//////////////////////////////����///////////////////
	while (isMenu)
	{

		window.clear(Color(0, 181, 221));

        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }




        window.draw(text1);
		window.display();
	}
	////////////////////////////////////////////////////
}

