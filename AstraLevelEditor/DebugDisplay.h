#pragma once
#include <SFML/Graphics.hpp>

class DebugDisplay
{
public:
	sf::Font font;
	sf::Text* fpstext;

	int framecount = 0;
	double time = 0;

public:
	DebugDisplay();
	~DebugDisplay();

	void update(float dt);
	void render(sf::RenderWindow& window);
};

