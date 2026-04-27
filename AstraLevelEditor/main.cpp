#include <SFML/Graphics.hpp>
#include <optional>
#include <string>
#include <random>
#include <ctime>

#include "SceneManager.h"
#include "KeyStruct.h"

int main() { 

    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "Astra Engine", sf::State::Fullscreen);
    SceneManager sM = SceneManager(window);
    SceneManager::Instance = &sM;   //Ne pas supprimer, mis par Benoit
    keys myKeys;
    sf::Clock clock;

    while (window.isOpen()) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        float dt = clock.restart().asSeconds();
        dt = std::min(dt, 0.05f);
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
			sM.MyLevel->handleEvent(*event, window);
        }

        myKeys.initKeys(myKeys.myKeys);
        sM.manageState(&myKeys, window);
        sM.updateState(myKeys.myKeys, dt, window);

        window.clear();

        sM.displayState(window);

        window.display();
    }
}