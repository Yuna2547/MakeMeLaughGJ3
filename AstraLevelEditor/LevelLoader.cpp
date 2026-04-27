#include "LevelLoader.h"
#include "Camera.h"

void LevelLoader::load(const std::string& collider_path, const std::string& render_path, sf::RenderWindow& window, float tileX, float tileY)
{
    std::ifstream file(collider_path);

    actualX = 0;
    actualY = 0;

    std::string line;
    int size = 50;

    int id;
    while (std::getline(file, line))
    {
        actualX = 0;

        for (char c : line)
        {
            if (c == '1')
            {
                colliders.push_back(new Collider(window, actualX, actualY, size, size, "sprite/Debug/Collider_DebugTX.png"));
            }

            actualX += size;
        }

        actualY += size;
    }

    //GridFill();   // Pas encore au point aucune dif sur les perf jusque la

    back = new BGstatic(window, render_path, tileX * 50, tileY * 50);
}

void LevelLoader::GridFill() {
    for (int i = 0; i < colliders.size(); i++)
    {
        Collider* A = colliders[i];

        for (int j = 0; j < colliders.size(); j++)
        {
            if (i == j) continue;

            Collider* B = colliders[j];

            if (A->pos.y == B->pos.y)
            {
                if (A->pos.x + A->size.x == B->pos.x)
                {
                    A->size.x += B->size.x;
                    A->rect.setSize(A->size);

                    delete B;
                    colliders.erase(colliders.begin() + j);

                    j--;

                }
            }
            if (A->pos.x == B->pos.x)
            {
                if (A->pos.y + A->size.y == B->pos.y)
                {
                    A->size.y += B->size.y;
                    A->rect.setSize(A->size);

                    delete B;
                    colliders.erase(colliders.begin() + j);

                    j--;

                }
            }
        }
    }
}

void LevelLoader::TileLoad(const std::string& path, const std::string& collpath, sf::RenderWindow& window)
{
    // Load render
    std::ifstream file(path);

    actualX = 0;
    actualY = 0;

    int size = 50;

    char c;
    while (file.get(c))
    {
        switch (c)
        {
        case 'A': Display.push_back(new DisplayEntity(window, actualX, actualY, size, size, "sprite/Testing/forest001.png")); break;


        default:
            break;
        }

        // Gestion du placement
        actualX += size;

        // Si on atteint la fin de ligne → retour à la ligne
        if (file.peek() == '\n')
        {
            file.get(); // consomme le '\n'
            actualY += size;
            actualX = 0;
        }
    }

    std::string line;
    int id;
    while (std::getline(file, line))
    {
        actualX = 0;

        for (char c : line)
        {
            if (c == '1')
            {
                colliders.push_back(new Collider(window, actualX, actualY, size, size, "sprite/Debug/Collider_DebugTX.png"));
            }

            actualX += size;
        }

        actualY += size;
    }
}

void LevelLoader::render(sf::RenderWindow& window, Camera* cam) {
    back->renderCam(window, *cam);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N)) {
        for (Collider* c : colliders) {
            if ((c->pos.x > cam->CamPos.x && c->pos.x < (cam->CamPos.x + 1920)) && (c->pos.y > cam->CamPos.y && c->pos.y < (cam->CamPos.y + 1080)) ) {
                c->render(window);
            }
        }
    }
}

void LevelLoader::TileRender(sf::RenderWindow& window, Camera* cam) {
    for (auto& c : Display) {
        c->render(window);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N)) {
        for (Collider* c : colliders) {
            c->render(window);
        }
    }
}

void LevelLoader::update(float dt, PlayerEX& player) {
    // Do i really need this ?
}

LevelLoader::~LevelLoader()  {
    for (auto& c : colliders) {
        delete c;
        c = nullptr;
    }
    for (auto& y : Display) {
        delete y;
        y = nullptr;
    }

    colliders.clear();
    Display.clear();

    delete back;
    back = nullptr;
}