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

    featherButton.setSize({ 180.f, 50.f });
    featherButton.setFillColor(sf::Color(80, 60, 120));
    featherButton.setPosition({ 20.f, 20.f });

    featherButtonText = new sf::Text(buttonFont, "Use Feather", 20);
    featherButtonText->setFillColor(sf::Color::White);
    featherButtonText->setPosition({ 30.f, 32.f });

    handButton.setSize({ 180.f, 50.f });
    handButton.setFillColor(sf::Color(60, 100, 80));
    handButton.setPosition({ 220.f, 20.f });

    handButtonText = new sf::Text(buttonFont, "Use Hand", 20);
    handButtonText->setFillColor(sf::Color::White);
    handButtonText->setPosition({ 230.f, 32.f });

    jokeButton.setSize({ 180.f, 50.f });
    jokeButton.setFillColor(sf::Color(120, 60, 60));
    jokeButton.setPosition({ 420.f, 20.f });

    jokeButtonText = new sf::Text(buttonFont, "Joke", 20);
    jokeButtonText->setFillColor(sf::Color::White);
    jokeButtonText->setPosition({ 430.f, 32.f });

    teaseButton.setSize({ 180.f, 50.f });
    teaseButton.setFillColor(sf::Color(120, 100, 40));
    teaseButton.setPosition({ 620.f, 20.f });

    teaseButtonText = new sf::Text(buttonFont, "Tease", 20);
    teaseButtonText->setFillColor(sf::Color::White);
    teaseButtonText->setPosition({ 630.f, 32.f });

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
    delete featherButtonText;
    featherButtonText = nullptr;
    delete handButtonText;
    handButtonText = nullptr;
    delete jokeButtonText;
    jokeButtonText = nullptr;
    delete teaseButtonText;
    teaseButtonText = nullptr;
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
                int randomDialog = 4 + std::rand() % 3;
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
    window.draw(*featherButtonText);
    window.draw(*handButtonText);
    window.draw(jokeButton);
    window.draw(teaseButton);
    window.draw(*jokeButtonText);
    window.draw(*teaseButtonText);

    cursor->update(window);
    cursor->draw(window);

    dialog->renderDial(window);
}

void EngineLevel::nextScene(SceneState& currentScene, keys* _myKeys, sf::RenderWindow& window) {
}