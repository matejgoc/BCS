#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <chrono>

using namespace std;
//doesnt need to be a float lol fix later
sf::Vector2f window_size = sf::Vector2f{1000.f,1000.f};

//some functions I wish SFML had. Easier to define here than switch between glm and sfml all the time
double v_len(sf::Vector2f v){
	return std::sqrt(pow(v.x,2) + pow(v.y,2));
}

void norm(sf::Vector2f& v){
	double len = v_len(v);
	v = sf::Vector2f{v.x / (float)len,v.y / (float)len}; //casting it just to avoid compilation fluff
}

sf::Vector2f s_m(sf::Vector2f v, float n){
	return sf::Vector2f{v.x*n,v.y*n};
}

void collide(double m_1, sf::Vector2f& v_1, double m_2, sf::Vector2f& v_2){
	//Simplifying physics to optimize for speed
	sf::Vector2f nv_1, nv_2;
	double s1 = v_len(v_1);
	double s2 = v_len(v_2);

	//std::srand(std::chrono::duration_cast<std::chrono::milliseconds>);

	nv_1.x = (1- (2* (double)rand() / (double)RAND_MAX));

	std::cerr << to_string((1- (2* (double)rand() / (double)RAND_MAX))) << '\n';
	//std::srand(std::chrono::duration_cast<std::chrono::milliseconds>);

	nv_1.y = (1- (2* (double)rand() / (double)RAND_MAX));

	norm(nv_1);

	nv_1.x *= s1;
	nv_1.y *= s1;

	nv_2.x = -1 * nv_1.x;
	nv_2.y = -1 * nv_1.y;
	// nv_1.x = v_1.x * random * s1;
	// nv_2.y = v_2.y * (1-random) * s2;
	//
	// nv_2.x = (m_1*v_1.x + m_2*v_2.x - m_1*nv_1.x)/m_2;
	// nv_1.y = (m_1*v_1.y + m_2*v_2.y - m_2*nv_2.y)/m_1;
	//
	v_1 = nv_1;
	v_2 = nv_2;

}

class molecule
{
public:

	int entity_id = 100;
	double m_size = 20.0;
	double m_mass = 18.02;
	sf::Vector2f m_pos = sf::Vector2f{50.0,50.0};
	sf::Vector2f m_v = sf::Vector2f{0.1,0.2};
	sf::Color m_color = sf::Color::Green;
	sf::CircleShape rendered_entity;
	sf::CircleShape tensor_entity;

	molecule() : rendered_entity(m_size),tensor_entity(m_size/10.f) {
		rendered_entity.setFillColor(m_color);
		tensor_entity.setFillColor(m_color);
	}

	void move(){
		m_pos += m_v;
		rendered_entity.setPosition(m_pos);
		tensor_entity.setPosition(s_m(m_pos, 0.1));
		std::cerr << std::to_string(m_v.x) << std::to_string(m_v.y) << '\n';


		if (m_pos.x > window_size.x || m_pos.y > window_size.y || m_pos.x < 0 || m_pos.y < 0){
			//std::cerr << "collision detected" << '\n';
			sf::Vector2f& elastic_v = m_v;
			collide(m_mass,m_v,m_mass,elastic_v);
		}
		//std::cerr << std::to_string(m_pos.x) <<  std::to_string(m_pos.y) << '\n';
	}


};



int main (int argc, const char * argv[]) {


	sf::RenderWindow sim_window(sf::VideoMode(window_size.x,window_size.y), "Simulation");
	sf::RenderWindow tensor_window(sf::VideoMode(window_size.x/10.f,window_size.y/10.f), "Tensor Field");

	molecule num1;


	while (sim_window.isOpen()){
		sf::Event event;
		while (sim_window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				sim_window.close();
		}

		num1.move();

		sim_window.clear();
		tensor_window.clear();
		sim_window.draw(num1.rendered_entity);
		tensor_window.draw(num1.tensor_entity);
		sim_window.display();
		tensor_window.display();
	}

	return 0;
}
