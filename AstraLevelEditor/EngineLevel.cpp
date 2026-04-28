#include "EngineLevel.h"
#include "Global.h"

#include <random>


EngineLevel::EngineLevel(sf::RenderWindow& window, Global& var_) {
    backgroundTexture.loadFromFile("level/class.png");

	oof.openFromFile("sound/hurt.mp3");
	oof.setLooping(false);
	oof.setVolume(50.f);

    wasMousePressed = false;
    dialog = new Dialog(window, "", true, 0);

    backgroundSprite = new sf::Sprite(backgroundTexture);

    sf::Vector2u texSize = backgroundTexture.getSize();
    sf::Vector2u winSize = window.getSize();
    backgroundSprite->setScale({ static_cast<float>(winSize.x) / texSize.x, static_cast<float>(winSize.y) / texSize.y });

    alexTexture.loadFromFile("sprite/alexneutre.png");
    alexSprite = new sf::Sprite(alexTexture);

    sf::Vector2u alexTexSize = alexTexture.getSize();
    alexSprite->setOrigin({ alexTexSize.x / 2.f, alexTexSize.y / 2.f });
    alexSprite->setPosition({ winSize.x / 2.f, winSize.y / 2.f + 50 });

    cursor = new CustomCursor(window, "sprite/pushpush.png", "sprite/feather.png");

    buttonFont.openFromFile("font/Pixellettersfull-BnJ5.ttf");

    featherButton.setSize({ 200.f, 200.f });
    featherButton.setPosition({ 20.f, 20.f });
	featherButtonTexture.loadFromFile("sprite/feather_and_hand.png");
	featherButton.setTexture(&featherButtonTexture);

    handButton.setSize({ 200.f, 200.f });
    handButton.setPosition({ 320.f, 20.f });
	handButtonTexture.loadFromFile("sprite/hand.png");
	handButton.setTexture(&handButtonTexture);

    jokeButton.setSize({ 200.f, 200.f });
    jokeButton.setPosition({ 620.f, 20.f });
	jokeButtonTexture.loadFromFile("sprite/insulte.png");
	jokeButton.setTexture(&jokeButtonTexture);

    teaseButton.setSize({ 200.f, 200.f });
    teaseButton.setPosition({ 920.f, 20.f });
	teaseButtonTexture.loadFromFile("sprite/blague.png");
	teaseButton.setTexture(&teaseButtonTexture);    

    wasMousePressed = false;
}

EngineLevel::~EngineLevel() {
    delete dialog;
    dialog = nullptr;
    delete backgroundSprite;
    backgroundSprite = nullptr;
    delete alexSprite;
    alexSprite = nullptr;
    delete cursor;
    cursor = nullptr;
}

void EngineLevel::onComputerDialogFinished() {
}

void EngineLevel::onChoiceMade(ChoiceDialog::Choice choice) {
}

void EngineLevel::update(const bool* keys, float dt) {
    dialog->updateDial(dt);
    if (alexIsSad) {
        alexSadTimer += dt;
        if (alexSadTimer >= 1.0f) {
            alexIsSad = false;
            alexSadTimer = 0.0f;
            alexTexture.loadFromFile("sprite/alexneutre.png");
            alexSprite->setTexture(alexTexture);
            triste = false;
        }
    }
}

void EngineLevel::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    sf::Vector2i mousePosPerm = sf::Mouse::getPosition(window);
    if (const auto* mp = event.getIf<sf::Event::MouseButtonPressed>()) {
        if (mp->button == sf::Mouse::Button::Left) {
            sf::Vector2f mousePos(static_cast<float>(mp->position.x), static_cast<float>(mp->position.y));

            if (featherButton.getGlobalBounds().contains(mousePos)) {
                cursor->setMode(CustomCursor::Mode::Feather);
            }
            else if (handButton.getGlobalBounds().contains(mousePos)) {
                cursor->setMode(CustomCursor::Mode::Hand);
            }
            else if (jokeButton.getGlobalBounds().contains(mousePos)) {
                int randomDialog = std::rand() % 4;
                dialog->setDialog(randomDialog);
                dialog->setText();
                dialog->isActive = true;
            }
            else if (teaseButton.getGlobalBounds().contains(mousePos)) {
                int randomDialog = 4 + std::rand() % 4;
                dialog->setDialog(randomDialog);
                dialog->setText();
                dialog->isActive = true;
            }
            else if (alexSprite->getGlobalBounds().contains(mousePos) && !triste ) {
                alexIsSad = !alexIsSad;
                if (alexIsSad) {
                    alexTexture.loadFromFile("sprite/alextriste.png");
                    triste = true;
					oof.play();
                }
                alexSprite->setTexture(alexTexture);
            }
        } 
    }  
    else if (alexSprite->getGlobalBounds().contains(sf::Vector2f(mousePosPerm)) && !triste && cursor->getMode() == CustomCursor::Mode::Feather) {
       alexIsSad = !alexIsSad;
       if (alexIsSad) {
            alexTexture.loadFromFile("sprite/alextriste.png");
            triste = true;
       }
       alexSprite->setTexture(alexTexture);
    }
    
}

void EngineLevel::displayScene(sf::RenderWindow& window) {
    window.draw(*backgroundSprite);
    window.draw(*alexSprite);

    window.draw(featherButton);
    window.draw(handButton);
    window.draw(jokeButton);
    window.draw(teaseButton);

    dialog->renderDial(window);
    cursor->update(window);
    cursor->draw(window);
}

void EngineLevel::nextScene(SceneState& currentScene, keys* _myKeys, sf::RenderWindow& window) {
}