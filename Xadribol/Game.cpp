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

Game::Game()
    : task(Task::Placement),
      turn(0),
      scoreRed(0),
      scoreBlue(0),
      selectedPlayer(nullptr)
{
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
    
    texmgr.loadTexture("player_b", "player_b.png");
    texmgr.loadTexture("player_r", "player_r.png");
    texmgr.loadTexture("playerhalo_b", "playerhalo_b.png");
    texmgr.loadTexture("playerhalo_r", "playerhalo_r.png");
    
    texmgr.loadTexture("cursorhelper_invalid", "cursorhelper_invalid.png");
    
    // Cards
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
    
    // Playas
    players.push_back(new Player(texmgr.getRef("player_b"),   sf::Vector2i(1, 0), Team::BLUE));
    players.push_back(new Player(texmgr.getRef("player_b"),   sf::Vector2i(2, 1), Team::BLUE, false));
    players.push_back(new Player(texmgr.getRef("player_b"),   sf::Vector2i(1, 2), Team::BLUE));
    players.push_back(new Player(texmgr.getRef("player_r"),   sf::Vector2i(3, 0), Team::RED));
    players.push_back(new Player(texmgr.getRef("player_r"),   sf::Vector2i(2, 1), Team::RED, false));
    players.push_back(new Player(texmgr.getRef("player_r"),   sf::Vector2i(3, 2), Team::RED));
    
    sf::Vector2f pos1 = getCardPosition(sf::Vector2i(0, 0));
    for(FieldCard* card : fieldCards) {
        sf::Vector2f pos = getCardPosition(card->gameCoords);
        card->sprite.setPosition(pos);
        
        // Pompous introduction
        //animationList.push_back(new Animation(card->sprite, AnimationDest::OPACITY, 0, 255, 1.0f));
        //animationList.push_back(new Animation(card->sprite, AnimationDest::POS_X, pos1.x, pos.x, 1.0f));
        //animationList.push_back(new Animation(card->sprite, AnimationDest::POS_Y, pos1.y, pos.y, 1.0f));
    }
    
    cursorHelper.setTexture(texmgr.getRef("cursorhelper_invalid"));
    cursorHelper.setTextureRect(sf::IntRect(0, 0, 11, 12));
    updateCursorHelper(true);
    
    playerHalo.setTextureRect(sf::IntRect(0, 0, 40, 40));
    playerHalo.setColor(sf::Color::Transparent);
    
    updatePlayerPositions();
}

Game::~Game()
{
    while(!this->states.empty()) popState();
}

void Game::selectPlayer(Player *player) {
    if(player != nullptr) {
        selectedPlayer = player;
        playerHalo.setTexture(player->team == Team::BLUE ? texmgr.getRef("playerhalo_b") :
                                                           texmgr.getRef("playerhalo_r"));
        playerHalo.setColor(sf::Color(255, 255, 255, 255));
        playerHalo.setPosition(player->sprite.getPosition() + sf::Vector2f(-7, -7));
    
        if(task == Task::Placement) {
            for(FieldCard* card : fieldCards) {
                bool dim = ((selectedPlayer->team == Team::BLUE && card->gameCoords.x <= 2) ||
                            (selectedPlayer->team == Team::RED && card->gameCoords.x >= 2));
                card->available = dim;
            }
        }
    
    }
}

void Game::updatePlayerPositions(bool animate) {
    char blueMap[15] = {0};
    char redMap[15] = {0};
    
    for(Player* player : players) {
        unsigned short offsetX = 0;
        unsigned short offsetY = PLAYER_MARGIN_Y;
        
        const char idx = (player->gameCoords.y * 5) + player->gameCoords.x;
        
        if(player->team == Team::BLUE) {
            offsetX = PLAYER_MARGIN_X;
            offsetY += blueMap[idx] * PLAYER_VSPACE;
            blueMap[idx]++;
        } else {
            offsetX = CARD_W - PLAYER_W - PLAYER_MARGIN_X;
            offsetY += redMap[idx] * PLAYER_VSPACE;
            redMap[idx]++;
        }
        
        sf::Vector2f pos(offsetX + CARDS_ORIGIN_X + (CARD_W + 4) * player->gameCoords.x,
                         offsetY + CARDS_ORIGIN_Y + (CARD_H + 3) * player->gameCoords.y);
        
        if(animate) {
            animations.push_back(new Animation(player->sprite, AnimationDest::POS_X, pos.x, 1.0f));
            animations.push_back(new Animation(player->sprite, AnimationDest::POS_Y, pos.y, 1.0f));
        } else {
            player->sprite.setPosition(pos);
        }
        
    }
}

sf::Vector2f Game::getCardPosition(sf::Vector2i gameCoords) {
    return sf::Vector2f(CARDS_ORIGIN_X + (CARD_W + 4) * gameCoords.x,
                        CARDS_ORIGIN_Y + (CARD_H + 3) * gameCoords.y);
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

void moveSelectedPlayer(sf::Vector2i gameCoords) {
    
}