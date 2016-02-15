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
    
    gameFont.loadFromFile(resourcePath() + "inconsolata.otf");
    texmgr.loadTexture("card_kick_b", "card_chutar_b.png");
    texmgr.loadTexture("card_defend_r", "card_defender_r.png");
    texmgr.loadTexture("card_dribble_b", "card_driblar_b.png");
    texmgr.loadTexture("card_move_b", "card_mover_b.png");
    texmgr.loadTexture("card_endturn_r.png", "card_passar_r.png"); // take note
    texmgr.loadTexture("card_steal_r", "card_passar_r.png");
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
    
    texmgr.loadTexture("player_b", "fieldcard_rd.png");
    texmgr.loadTexture("player_r", "fieldcard_ru.png");
    texmgr.loadTexture("playerhalo_b", "playerhalo_b.png");
    texmgr.loadTexture("playerhalo_r", "playerhalo_r.png");
    
    texmgr.loadTexture("cursorhelper_invalid", "cursorhelper_invalid.png");
    
    fieldCards.push_back(new FieldCard(texmgr.getRef("fieldcard_lu"),   sf::Vector2i(0, 0)));
    fieldCards.push_back(new FieldCard(texmgr.getRef("fieldcard_u"),    sf::Vector2i(1, 0)));
    fieldCards.push_back(new FieldCard(texmgr.getRef("fieldcard_cu"),   sf::Vector2i(2, 0)));
    fieldCards.push_back(new FieldCard(texmgr.getRef("fieldcard_u"),    sf::Vector2i(3, 0)));
    fieldCards.push_back(new FieldCard(texmgr.getRef("fieldcard_ru"),   sf::Vector2i(4, 0)));
    fieldCards.push_back(new FieldCard(texmgr.getRef("fieldcard_lc"),   sf::Vector2i(0, 1)));
    fieldCards.push_back(new FieldCard(texmgr.getRef("fieldcard_bl"),   sf::Vector2i(1, 1)));
    fieldCards.push_back(new FieldCard(texmgr.getRef("fieldcard_cc"),   sf::Vector2i(2, 1)));
    fieldCards.push_back(new FieldCard(texmgr.getRef("fieldcard_bl"),   sf::Vector2i(3, 1)));
    fieldCards.push_back(new FieldCard(texmgr.getRef("fieldcard_rc"),   sf::Vector2i(4, 1)));
    fieldCards.push_back(new FieldCard(texmgr.getRef("fieldcard_ld"),   sf::Vector2i(0, 2)));
    fieldCards.push_back(new FieldCard(texmgr.getRef("fieldcard_d"),    sf::Vector2i(1, 2)));
    fieldCards.push_back(new FieldCard(texmgr.getRef("fieldcard_cd"),   sf::Vector2i(2, 2)));
    fieldCards.push_back(new FieldCard(texmgr.getRef("fieldcard_d"),    sf::Vector2i(3, 2)));
    fieldCards.push_back(new FieldCard(texmgr.getRef("fieldcard_rd"),   sf::Vector2i(4, 2)));
    
    sf::Vector2f pos1 = getCardPosition(sf::Vector2i(0, 0));
    for(FieldCard* card : fieldCards) {
        sf::Vector2f pos = getCardPosition(card->gameCoords);
        animationList.push_back(new Animation(card->sprite, AnimationDest::OPACITY, 0, 255, 3.0f));
        animationList.push_back(new Animation(card->sprite, AnimationDest::POS_X, pos1.x, pos.x, 3.0f));
        animationList.push_back(new Animation(card->sprite, AnimationDest::POS_Y, pos1.y, pos.y, 3.0f));
    }
}

Game::~Game()
{
    while(!this->states.empty()) popState();
}

sf::Vector2f Game::getCardPosition(sf::Vector2i gameCoords) {
    return sf::Vector2f(CARDS_ORIGIN_X + (CARD_W + 4) * gameCoords.x,
                        CARDS_ORIGIN_Y + (CARD_H + 3) * gameCoords.y);
}