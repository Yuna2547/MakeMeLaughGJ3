#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>


class Dialog {
public:
	sf::Music dial;
	std::string faceChar;
	int dialog;
	bool box;
	bool isActive = false;

	bool justFinished = false;
	float timer = 0.0f;
	const float duration = 3.0f;

	sf::RectangleShape rectDial;
	sf::Texture textureDial;

	sf::RectangleShape rectFace;
	sf::Texture textureFace;

	sf::Font textDial;
	sf::Text* text;
	std::string fullText;
	int visibleChars = 0;
	float charTimer = 0.0f;
	const float charDelay = 0.05f;
	bool isTyping = false;


public:
	Dialog(sf::RenderWindow& window, std::string face, bool dialogBox, int dialogID);
	~Dialog();
	void setText();
	void updateDial(float dt);
	void renderDial(sf::RenderWindow& window);
};

class ChoiceDialog {
public:
	enum class Choice { None, PlayALittle, Work };

	bool visible = false;
	bool prevPressed = false;
	Choice chosen = Choice::None;

	sf::RectangleShape panel;
	sf::Texture texturePanel;

	sf::RectangleShape buttonPlay;
	sf::RectangleShape buttonWork;
	sf::Texture textureButtonPlay;
	sf::Texture textureButtonWork;

	sf::Font font;
	sf::Text* lblPlay = nullptr;
	sf::Text* lblWork = nullptr;
	sf::Text* prompt = nullptr;


	sf::FloatRect playBounds;
	sf::FloatRect workBounds;

public:
	ChoiceDialog();

	void init(unsigned int winW, unsigned int winH);

	bool isVisible() const;
	void show();
	void hide();
	Choice getChoice() const;

	Choice update(const sf::RenderWindow& window);

	void render(sf::RenderWindow& window);
};