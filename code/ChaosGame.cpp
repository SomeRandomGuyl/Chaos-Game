// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

double generateScale(int numVertices)
{
	const double PI = 3.14159;

	if (numVertices == 4)
		return 0.667;

	if (numVertices % 4 == 0)
		return (1 / (1 + tan(PI / numVertices)));
	else if (numVertices % 4 == 2)
		return (1 / (1 + sin(PI / numVertices)));
	else
		return (1 / (1 + 2 * sin(PI / (2 * numVertices))));
}

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);

	sf::Font font;
	sf::Text text;
	text.setFont(font);
	if (!font.loadFromFile("Comic Sans MS.ttf"))
		throw runtime_error("Could not find Font");

	text.setString("Left click to add vertices, Right click to run.");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	window.draw(text);

	
	//vector<Vector2f> vertices;
	vector<Vector2f> points;
	int verts = 0;
	double scale;
	bool doneClicking = false;
	

	srand(time(0));

	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
		    if (event.type == Event::Closed)
		    {
				// Quit the game when the window is closed
				window.close();
		    }
		    if (event.type == sf::Event::MouseButtonPressed)
		    {
				if (event.mouseButton.button == sf::Mouse::Left && !doneClicking)
				{
			    	std::cout << "the left button was pressed" << std::endl;
			    	std::cout << "mouse x: " << event.mouseButton.x << std::endl;
			    	std::cout << "mouse y: " << event.mouseButton.y << std::endl;

					points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					verts++;
				}

				if (event.mouseButton.button == sf::Mouse::Right)
				{
					scale = generateScale(verts);
					doneClicking = true;
				}
		    }
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/
	
		if(doneClicking)
		{
		    ///generate more point(s)
		    ///select random vertex
		    ///calculate midpoint between random vertex and the last point in the vector
		    ///push back the newly generated coord.
			Vector2f p1 = points[rand() % points.size()];
			Vector2f p2 = points[rand() % verts];
			Vector2f pt;

			int dx, dy;
			dx = p2.x - p1.x;
			dy = p2.y - p1.y;

			pt.x = p1.x + scale * dx;
			pt.y = p1.y + scale * dy;

			points.push_back(pt);

			//window.clear();
			CircleShape circ(2);
		    circ.setPosition(Vector2f(pt.x, pt.y));
		    circ.setFillColor(Color::White);
		    window.draw(circ);
			window.display();

			//cout << "Debug: " << points.size() << endl;
		}
	
		/*
		****************************************
		Draw
		****************************************
		*/
		//window.clear();
		for(int i = 0; i < verts; i++)
		{
		    CircleShape circ(5);
		    circ.setPosition(Vector2f(points[i].x, points[i].y));
		    circ.setFillColor(Color::Blue);
		    window.draw(circ);
		}
		window.display();
	}
}

