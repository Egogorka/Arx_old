#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Menu1.cpp"
using namespace std;
using namespace sf;



int main()
{
    int n = 30; // �����
    int m = 30; // ��������
    int h = 20; // ������ ������


    //sf::RenderWindow window(sf::VideoMode(h*m, h*n), "SFML works!");

    RenderWindow window1 (sf::VideoMode(h*m, h*n), "Menu");
	menu(window1, h*m, h*n);//����� ����

	return 0;
}
