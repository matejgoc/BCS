#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
//doesnt need to be a float lol fix later
sf::Vector2f window_size = sf::Vector2f{1000.f,1000.f};

class molecule
{
public:

	double molecule_size = 20.0;
	sf::Vector2f position = sf::Vector2f{50.0,50.0};
	sf::Vector2f velocity = sf::Vector2f{1.0,0.5};
	sf::Color color = sf::Color::Green;
	sf::CircleShape rendered_entity;

	molecule() : rendered_entity(molecule_size) {
		rendered_entity.setFillColor(color);
	}

	void move(){
		position += velocity;
		rendered_entity.setPosition(position);

	}
};



int main (int argc, const char * argv[]) {


	sf::RenderWindow sim_window(sf::VideoMode(window_size.x,window_size.y), "Simulation");
	//sf::RenderWindow tensor_window(sf::VideoMode(window_size.x,window_size.y), "Tensor Field");

	molecule num1;


	while (sim_window.isOpen()){
		sf::Event event;
		while (sim_window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				sim_window.close();
		}

		num1.move();

		sim_window.clear();
		sim_window.draw(num1.rendered_entity);
		sim_window.display();
	}

	return 0;
}
