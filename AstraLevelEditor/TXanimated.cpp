#include "TXanimated.h"

TXanimated::TXanimated() {
	Frameloc = {0, 0};
	ActualFrame = 0;

	startpoint = 0;
}

TXanimated::~TXanimated() {

}

void TXanimated::load(std::string file, float sizeX, float sizeY, float posX, float posY) {
	std::ifstream f(file);

	std::getline(f, filename);
	f >> FrameSize.x;
	f >> FrameSize.y;
	f >> TotalFrame;
	f >> FrameRate;

	offset = sf::IntRect({ 0, 0 }, {FrameSize});

	TX.loadFromFile(filename.c_str());
	size = { static_cast<int>(sizeX), static_cast<int>(sizeY) };

	rect.setTextureRect(offset); 
	ActualFrame = 1;
	rect.setSize({ sizeX, sizeY });
	rect.setPosition({ posX, posY });
	rect.setTexture(&TX);
	rect.setTextureRect(offset);
}

void TXanimated::update(float dt) {
	elapsed = clock.getElapsedTime().asMilliseconds();
	startpoint += dt;

	if (startpoint >= FrameRate) {
		Frameloc.x = ActualFrame * FrameSize.x;
		offset = sf::IntRect({ Frameloc.x, 0 }, { FrameSize.x, FrameSize.y });
		rect.setTextureRect(offset);

		ActualFrame += 1;
		if (ActualFrame >= TotalFrame) {
			ActualFrame = 0;
		}

		startpoint = 0;
	}

	clock.reset();
}

void TXanimated::render(sf::RenderWindow& window) {
	window.draw(rect);
}