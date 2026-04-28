#include "Dialog.h"

Dialog::Dialog(sf::RenderWindow& window, std::string face, bool dialogBox, int dialogID) {
	faceChar = face;
	box = dialogBox;
	dialog = dialogID;
	textDial.openFromFile("font/Pixellettersfull-BnJ5.ttf");
	text = new sf::Text(textDial, "", 60);
	text->setFillColor(sf::Color::White);
	text->setPosition({ 100, 850 });

	rectFace.setPosition({ 50, 510 });
	rectFace.setSize({ 240, 300 });

	rectDial.setPosition({ 0, 805 });
	rectDial.setSize({ 1920, 180 });
	textureDial.loadFromFile("sprite/dialogbox.png");
}

Dialog::~Dialog() {
}

void Dialog::setText() {
	timer = 0.0f;
	justFinished = false;
	visibleChars = 0;
	charTimer = 0.0f;
	isTyping = true;

	if (dialog == 0) {
		fullText = ("Espece de coin coin !");
	}
	if (dialog == 1) {
		fullText = ("Gros bot");	
	}
	if (dialog == 2) {
		fullText = ("Gros canard");
	}
	if (dialog == 3) {
		fullText = ("Bah alors ? On est soumis ? Coquinou, va !");
	}
	if (dialog == 4) {
		fullText = ("T'as plus d'appart ? Awww...");
	}
	if (dialog == 5) {
		fullText = ("Tu batteras jamais le panthéon cinq");
	}
	if (dialog == 6) {
		fullText = ("T'as dit a Youssef de rentrer chez lui ? T'es raciste en fait !");
	}
	if (dialog == 7) {
		fullText = ("Awww...");
	}
	dial.openFromFile("sound/dialog.mp3");
	dial.setLooping(false);
	dial.setVolume(50.f);
	dial.play();
	textureFace.loadFromFile("sprite/Benoit.png");
	rectFace.setTexture(&textureFace);
	rectDial.setTexture(&textureDial);
}

void Dialog::updateDial(float dt) {
	justFinished = false;
	if (!isActive) return;

	if (isTyping) {
		charTimer += dt;
		if (charTimer >= charDelay) {
			charTimer = 0.0f;
			visibleChars++;
			std::string displayed = "";
			for (int i = 0; i < visibleChars; i++) {
				displayed += fullText[i];
			}
			text->setString(displayed);

			if (visibleChars == fullText.size()) {
				isTyping = false;
				dial.stop();
			}
		}
	}
	else {
		timer += dt;
		if (timer >= duration) {
			isActive = false;
			timer = 0.0f;
			justFinished = true;
		}
	}
}

void Dialog::renderDial(sf::RenderWindow& window) {
	if (!isActive) return;
	window.draw(rectDial);
	window.draw(rectFace);
	window.draw(*text);
}

void Dialog::setDialog(int id){
	dialog = id;
}

ChoiceDialog::ChoiceDialog() {
	font.openFromFile("font/Pixellettersfull-BnJ5.ttf");

	prompt = new sf::Text(font, "What do you want to do?", 50);
	lblPlay = new sf::Text(font, "Play a little", 40);
	lblWork = new sf::Text(font, "Work", 40);

	prompt->setFillColor(sf::Color::White);
	lblPlay->setFillColor(sf::Color::White);
	lblWork->setFillColor(sf::Color::White);
}

void ChoiceDialog::init(unsigned int winW, unsigned int winH) {
	const float panelW = 600, panelH = 250;
	const float panelX = (winW - panelW) / 2;
	const float panelY = winH - panelH - 20;

	panel.setSize({ panelW, panelH });
	panel.setPosition({ panelX, panelY });

	texturePanel.loadFromFile("sprite/dialogbox.png");
	panel.setTexture(&texturePanel);

	prompt->setPosition({ panelX + 30, panelY + 20 });

	const float btnW = 240, btnH = 70;
	const float btnY = panelY + 120;

	buttonPlay.setSize({ btnW, btnH });
	buttonPlay.setPosition({ panelX + 40, btnY });
	textureButtonPlay.loadFromFile("sprite/button.png");
	buttonPlay.setTexture(&textureButtonPlay);

	buttonWork.setSize({ btnW, btnH });
	buttonWork.setPosition({ panelX + panelW - 40 - btnW, btnY });
	textureButtonWork.loadFromFile("sprite/button.png");
	buttonWork.setTexture(&textureButtonWork);

	lblPlay->setPosition({ buttonPlay.getPosition().x + 40, buttonPlay.getPosition().y });
	lblWork->setPosition({ buttonWork.getPosition().x + 60, buttonWork.getPosition().y });

	playBounds = buttonPlay.getGlobalBounds();
	workBounds = buttonWork.getGlobalBounds();
}

bool ChoiceDialog::isVisible() const {
	return visible;
}

void ChoiceDialog::show() {
	visible = true;
	chosen = Choice::None;
	prevPressed = true; 
}

void ChoiceDialog::hide() {
	visible = false;
}

ChoiceDialog::Choice ChoiceDialog::getChoice() const {
	return chosen;
}

ChoiceDialog::Choice ChoiceDialog::update(const sf::RenderWindow& window) {
	if (!visible) {
		return Choice::None;
	}

	bool curPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

	if (curPressed && !prevPressed) {
		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos, window.getDefaultView());

		if (playBounds.contains(mousePos)) {
			chosen = Choice::PlayALittle;
			visible = false;
			prevPressed = curPressed;
			return chosen;
		}
		if (workBounds.contains(mousePos)) {
			chosen = Choice::Work;
			visible = false;
			prevPressed = curPressed;
			return chosen;
		}
	}

	prevPressed = curPressed;
	return Choice::None;
}

void ChoiceDialog::render(sf::RenderWindow& window) {
	if (!visible) {
		return;
	}
	window.draw(panel);
	window.draw(*prompt);
	window.draw(buttonPlay);
	window.draw(buttonWork);
	window.draw(*lblPlay);
	window.draw(*lblWork);
}