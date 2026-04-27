#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Collider {
public:
	sf::Vector2f pos;
	sf::Vector2f size;

	sf::RectangleShape rect;
	sf::Texture texture;

	Collider(sf::RenderWindow& window, float posX_, float posY_, float sizeX_, float sizeY_, std::string image);
	~Collider();

	void render(sf::RenderWindow& window);
};
