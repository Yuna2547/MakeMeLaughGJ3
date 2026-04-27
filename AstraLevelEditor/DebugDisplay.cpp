#include "DebugDisplay.h"

DebugDisplay::DebugDisplay() {
	font.openFromFile("font/Pixellettersfull-BnJ5.ttf");
	fpstext = new sf::Text(font, "FPS: 0", 24);

	fpstext->setFillColor(sf::Color::Red);
	fpstext->setPosition({ 10, 10 });
}

DebugDisplay::~DebugDisplay() {

}

void DebugDisplay::update(float dt) {
	time += dt;
	++framecount;

	if (time >= 1) {
		fpstext->setString("FPS: " + std::to_string(framecount));
		time = 0;
		framecount = 0;
	}
}

void DebugDisplay::render(sf::RenderWindow& window) {
	//window.draw(*fpstext);
}