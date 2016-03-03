#include "Game.h"
#include "GameState.h"
#include "ResourcePath.hpp"

void Game::pushState(GameState* state) {
    this->states.push(state);

    return;
}

void Game::popState() {
    //delete this->states.top();
    this->states.pop();

    return;
}

void Game::changeState(GameState* state) {
    if(!this->states.empty())
        popState();
    pushState(state);

    return;
}

GameState* Game::peekState() {
    if(this->states.empty()) return nullptr;
    return this->states.top();
}

void Game::gameLoop() {
    sf::Clock clock;

    while(this->window.isOpen()) {

        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        if(peekState() == nullptr) continue;
        peekState()->handleInput();
        peekState()->update(dt);
        peekState()->draw(dt);
    }
}

// ------------------------------------------

Game::Game() {
    this->window.create(sf::VideoMode(800, 600), "Xadribol", sf::Style::Close);

    this->window.setFramerateLimit(60);
    
    #ifdef _WIN32
    gameFont.loadFromFile("Xadribol/resources/inconsolata.otf");
    #elif __APPLE__
    gameFont.loadFromFile(resourcePath() + "inconsolata.otf");
    #endif // __APPLE__

    texmgr.loadTexture("card_kick_b", "card_chutar_b.png");
    texmgr.loadTexture("card_defend_r", "card_defender_r.png");
    texmgr.loadTexture("card_dribble_b", "card_driblar_b.png");
    texmgr.loadTexture("card_move_b", "card_mover_b.png");
    texmgr.loadTexture("card_endturn_r", "card_passar_r.png"); // take note
    texmgr.loadTexture("card_steal_r", "card_roubar_r.png");
    texmgr.loadTexture("card_pass_b", "card_tocar_b.png");

    texmgr.loadTexture("fieldcard_bl", "fieldcard_blank.png"); // bl for blank
    texmgr.loadTexture("fieldcard_cc", "fieldcard_cc.png");
    texmgr.loadTexture("fieldcard_cd", "fieldcard_cd.png");
    texmgr.loadTexture("fieldcard_cu", "fieldcard_cu.png");
    texmgr.loadTexture("fieldcard_d", "fieldcard_d.png");
    texmgr.loadTexture("fieldcard_lc", "fieldcard_lc.png");
    texmgr.loadTexture("fieldcard_ld", "fieldcard_ld.png");
    texmgr.loadTexture("fieldcard_lu", "fieldcard_lu.png");
    texmgr.loadTexture("fieldcard_rc", "fieldcard_rc.png");
    texmgr.loadTexture("fieldcard_rd", "fieldcard_rd.png");
    texmgr.loadTexture("fieldcard_ru", "fieldcard_ru.png");
    texmgr.loadTexture("fieldcard_u", "fieldcard_u.png");

    texmgr.loadTexture("player_b", "player_b.png");
    texmgr.loadTexture("player_r", "player_r.png");
    texmgr.loadTexture("playerhalo_b", "playerhalo_b.png");
    texmgr.loadTexture("playerhalo_r", "playerhalo_r.png");

    texmgr.loadTexture("ball", "ball.png");
    texmgr.loadTexture("roulette", "roulette.png");
    texmgr.loadTexture("roulette_needle", "needle.png");

    texmgr.loadTexture("cursorhelper_invalid", "cursorhelper_invalid.png");

    cursorHelper.setTexture(texmgr.getRef("cursorhelper_invalid"));
    cursorHelper.setTextureRect(sf::IntRect(0, 0, 11, 12));
}

Game::~Game()
{
    while(!this->states.empty()) popState();
}

void Game::updateCursorHelper(bool show, sf::Vector2i mousePos) {
    if(show) {
        cursorHelper.setPosition(sf::Vector2f(mousePos.x + CURSORHELPER_OFFSET_X,
                                              mousePos.y + CURSORHELPER_OFFSET_Y));
        cursorHelper.setColor(sf::Color(255, 255, 255, 255));
    } else {
        cursorHelper.setColor(sf::Color::Transparent);
    }
}
