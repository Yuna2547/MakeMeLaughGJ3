#include "EngineLevel.h"
#include "Global.h"

static constexpr int COMPUTER_DIALOG_INDEX = 3;

EngineLevel::EngineLevel(sf::RenderWindow& window, Global& var_) : glob(var_) {

    music.openFromFile("sound/bgmusic.mp3");
    music.setLooping(true);
    music.setVolume(50.f);
    music.play();

    loader = new LevelLoader();
    loader->load("level/collision.txt", "level/map.png", window, 60, 60);

    cam = new Camera(1920, 1080, 50 * 60, 50 * 40, 0.005);
    Machine = new StateMachine(new DummyState());

    player = new PlayerEX(window, 1, 200, 500, 120, 120, 1425, 400, "sprite/Debug/PlaceHolder.png", 1, *Machine);
    Machine->currentState = new IdleStateRight(*player);

    parralax = new BG_parralax_Full();
    parralax->addlayer("level\map.png", 0.5);

    dialogs = {
        { new Trigger(850, 300, 100, 100, true),  new Dialog(window, "", true, 0) },
        { new Trigger(1260, 270, 100, 100, true), new Dialog(window, "", true, 1) },
        { new Trigger(350, 1000, 100, 100, true), new Dialog(window, "", true, 2) },
        { new Trigger(600, 250, 100, 100, true), new Dialog(window, "", true, 3), false, true },
		{ new Trigger(450, 50, 100, 100, true), new Dialog(window, "", true, 6) },
		{ new Trigger(1400, 800, 100, 100, true), new Dialog(window, "", true, 7) },
    };

    for (auto& trigDial : dialogs) {
        triggers.push_back(trigDial.trigger);
    }

    cam->view->setCenter(player->pos);

    fps = new DebugDisplay();

    font.openFromFile("font/Pixellettersfull-BnJ5.ttf");
    fpstext = new sf::Text(font, "Press E to interact", 30);
    fpstext->setFillColor(sf::Color::Black);
    fpstext->setPosition({ 750, 300 });

    choiceOverlay.init(1920, 1080);

    followUpDialog = new Dialog(window, "", true, 4);

    win = &window;
}

EngineLevel::~EngineLevel() {
    for (auto& collide : Colliderlist) {
        delete collide;
        collide = nullptr;
    }
    Colliderlist.clear();

    for (auto& trigDial : dialogs) {
        delete trigDial.trigger;
        delete trigDial.dialog;
    }
    dialogs.clear();
    triggers.clear();

    delete followUpDialog;
    followUpDialog = nullptr;
    delete loader;
    loader = nullptr;
    delete cam;
    cam = nullptr;
    delete player;
    player = nullptr;
    delete parralax;
    parralax = nullptr;
    delete fps;
    fps = nullptr;
    delete Machine;
    Machine = nullptr;
}

void EngineLevel::onComputerDialogFinished() {
    choiceOverlay.show();
}

void EngineLevel::onChoiceMade(ChoiceDialog::Choice choice) {
    if (choice == ChoiceDialog::Choice::Work) {
        followUpDialog->dialog = 5;
    }
    else {
        followUpDialog->dialog = 4;
    }

    followUpDialog->setText();
    followUpDialog->isActive = true;
}

void EngineLevel::update(const bool* keys, float dt) {

    loader->update(dt, *player);
    player->update(dt, loader->colliders);
    cam->Update(*player);
    parralax->update(dt, *cam);

    bool anyInside = false;
    for (int i = 0; i < static_cast<int>(dialogs.size()); ++i) {
        auto& trigDial = dialogs[i];

        trigDial.trigger->update(dt, *player);
        trigDial.dialog->updateDial(dt);

        if (trigDial.dialog->justFinished) {
            if (trigDial.triggersChoice) {
                onComputerDialogFinished();
            }
            trigDial.interacted = false;
            pressed = false;
        }

        if (trigDial.trigger->inside) {
            anyInside = true;
        }

        if (trigDial.trigger->inside && !trigDial.interacted && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
            trigDial.interacted = true;
            pressed = true;
            trigDial.dialog->setText();
            trigDial.dialog->isActive = true;
        }
    }

    if (choiceOverlay.isVisible()) {
        ChoiceDialog::Choice choicedial = choiceOverlay.update(*win);
        if (choicedial != ChoiceDialog::Choice::None) {
            onChoiceMade(choicedial);
        }
    }

    if (followUpDialog && followUpDialog->isActive) {
        followUpDialog->updateDial(dt);
    }

    if (!pressed && anyInside) {
        fpstext->setString("Press E to interact");
    }

    fps->update(dt);
}

void EngineLevel::displayScene(sf::RenderWindow& window) {
    window.setView(*cam->view);

    parralax->render(window);
    loader->render(window, cam);
    Machine->currentState->render(window);
    for (auto& td : dialogs) {
        td.trigger->render(window);
    }

    window.setView(window.getDefaultView());

    fps->render(window);

    bool anyInside = false;
    for (auto& trigDial : dialogs) {
        if (trigDial.trigger->inside) { 
            anyInside = true; 
            break; 
        }
    }

    if (anyInside && !pressed) {
        window.draw(*fpstext);
    }

    for (auto& trigDial : dialogs) {
        if (trigDial.trigger->inside) {
            trigDial.dialog->renderDial(window);
        }
    }

    choiceOverlay.render(window);

    if (followUpDialog) {
        followUpDialog->renderDial(window);
    }
}

void EngineLevel::nextScene(SceneState& currentScene, keys* _myKeys, sf::RenderWindow& window) {
}