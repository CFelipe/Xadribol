#include "PlayingState.h"
#include <iostream>

PlayingState::PlayingState(Game* game)
    : task(Task::Placement),
    turn(0),
    scoreRed(0),
    scoreBlue(0),
    selectedPlayer(nullptr)
{
    this->game = game;
    
    /*
    Try to set up drawables here as they're drawn from top to bottom
     
    If they're drawn on top of each other (like players and cards) add what's behind
        
    So I recommend  Visible - Invisible (cursorHelper) / Top - Bottom / Back - Front
        
    When pushing to drawableEntities, mind the order as entities are drawn in the order they're added
     
    Don't forget to add drawables to drawableEntities when they're created, of course
    */
    
    blueBar.setSize(sf::Vector2f(400, 4));
    blueBar.setPosition(0, 50);
    blueBar.setFillColor(blue);
    redBar.setSize(sf::Vector2f(400, 4));
    redBar.setPosition(400, 50);
    redBar.setFillColor(red);
    actionBar.setPosition(0, 54);
    actionBar.setSize(sf::Vector2f(800, 180));
    actionBar.setFillColor(dark);
    
    roulette.setTextureRect(sf::IntRect(0, 0, 68, 68));
    roulette.setTexture(game->texmgr.getRef("roulette"));
    roulette.setPosition(sf::Vector2f(400 - 68 / 2, 100));
    
    rouletteNeedle.setTextureRect(sf::IntRect(0, 0, 10, 30));
    rouletteNeedle.setTexture(game->texmgr.getRef("roulette_needle"));
    rouletteNeedle.setPosition(sf::Vector2f(400, 134));
    rouletteNeedle.setOrigin(sf::Vector2f(5, 21));
    rouletteNeedle.setRotation(0);
    
    playButton = new TextButton("Jogar", 32, game->gameFont, light);
    playButton->setPosition(sf::Vector2f(400, 100));
    
    drawableEntities.push_back(&blueBar);
    drawableEntities.push_back(&redBar);
    drawableEntities.push_back(&actionBar);
    drawableEntities.push_back(&roulette);
    drawableEntities.push_back(&rouletteNeedle);
    drawableEntities.push_back(playButton);
    
    // Cards
    fieldCards.push_back(new FieldCard(game->texmgr.getRef("fieldcard_lu"),   sf::Vector2i(0, 0)));
    fieldCards.push_back(new FieldCard(game->texmgr.getRef("fieldcard_u"),    sf::Vector2i(1, 0)));
    fieldCards.push_back(new FieldCard(game->texmgr.getRef("fieldcard_cu"),   sf::Vector2i(2, 0)));
    fieldCards.push_back(new FieldCard(game->texmgr.getRef("fieldcard_u"),    sf::Vector2i(3, 0)));
    fieldCards.push_back(new FieldCard(game->texmgr.getRef("fieldcard_ru"),   sf::Vector2i(4, 0)));
    fieldCards.push_back(new FieldCard(game->texmgr.getRef("fieldcard_lc"),   sf::Vector2i(0, 1)));
    fieldCards.push_back(new FieldCard(game->texmgr.getRef("fieldcard_bl"),   sf::Vector2i(1, 1)));
    fieldCards.push_back(new FieldCard(game->texmgr.getRef("fieldcard_cc"),   sf::Vector2i(2, 1)));
    fieldCards.push_back(new FieldCard(game->texmgr.getRef("fieldcard_bl"),   sf::Vector2i(3, 1)));
    fieldCards.push_back(new FieldCard(game->texmgr.getRef("fieldcard_rc"),   sf::Vector2i(4, 1)));
    fieldCards.push_back(new FieldCard(game->texmgr.getRef("fieldcard_ld"),   sf::Vector2i(0, 2)));
    fieldCards.push_back(new FieldCard(game->texmgr.getRef("fieldcard_d"),    sf::Vector2i(1, 2)));
    fieldCards.push_back(new FieldCard(game->texmgr.getRef("fieldcard_cd"),   sf::Vector2i(2, 2)));
    fieldCards.push_back(new FieldCard(game->texmgr.getRef("fieldcard_d"),    sf::Vector2i(3, 2)));
    fieldCards.push_back(new FieldCard(game->texmgr.getRef("fieldcard_rd"),   sf::Vector2i(4, 2)));
    
    for(FieldCard* card : fieldCards) {
        drawableEntities.push_back(&card->sprite);
    }
    
    // Playas
    players.push_back(new Player(game->texmgr.getRef("player_b"),   sf::Vector2i(1, 0), Team::BLUE));
    players.push_back(new Player(game->texmgr.getRef("player_b"),   sf::Vector2i(2, 1), Team::BLUE, false));
    players.push_back(new Player(game->texmgr.getRef("player_b"),   sf::Vector2i(1, 2), Team::BLUE));
    players.push_back(new Player(game->texmgr.getRef("player_r"),   sf::Vector2i(3, 0), Team::RED));
    players.push_back(new Player(game->texmgr.getRef("player_r"),   sf::Vector2i(2, 1), Team::RED, false));
    players.push_back(new Player(game->texmgr.getRef("player_r"),   sf::Vector2i(3, 2), Team::RED));
    
    playerHalo.setTextureRect(sf::IntRect(0, 0, 40, 40));
    playerHalo.setColor(sf::Color::Transparent);
    drawableEntities.push_back(&playerHalo);
    
    
    for(Player* player : players) {
        drawableEntities.push_back(&player->sprite);
    }
    
    ball.setTextureRect(sf::IntRect(0, 0, 18, 18));
    ball.setTexture(game->texmgr.getRef("ball"));
    ball.setPosition(getCardPosition(sf::Vector2i(2, 1)) + sf::Vector2f(67, 45));
    drawableEntities.push_back(&ball);
    
    drawableEntities.push_back(&game->cursorHelper);
    
    // ----------------------------------------------
    
    sf::Vector2f pos1 = getCardPosition(sf::Vector2i(0, 0));
    for(FieldCard* card : fieldCards) {
        sf::Vector2f pos = getCardPosition(card->gameCoords);
        card->sprite.setPosition(pos);
        
        // Pompous introduction
        //animationList.push_back(new Animation(card->sprite, AnimationDest::OPACITY, 0, 255, 1.0f));
        //animationList.push_back(new Animation(card->sprite, AnimationDest::POS_X, pos1.x, pos.x, 1.0f));
        //animationList.push_back(new Animation(card->sprite, AnimationDest::POS_Y, pos1.y, pos.y, 1.0f));
    }

    game->updateCursorHelper(false);
    updatePlayerPositions(false);
}

void PlayingState::handleInput() {
    sf::Event event;
        
    while(game->window.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            game->window.close();
        } else if(event.type == sf::Event::MouseButtonPressed) {
            if(event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Vector2i(event.mouseButton.x,
                                                     event.mouseButton.y);
                
                if(playButton->contains(mousePos)) {
                    vel = 1500.0f;
                    return;
                }
                
                for(Player* player : players) {
                    if(player->contains(mousePos)) {
                        if(player->selectable) {
                            selectPlayer(player);
                            return;
                        }
                    }
                }
                
                for(FieldCard* card : fieldCards) {
                    if(card->contains(mousePos)) {
                        if(card->available) {
                            moveSelectedPlayer(card->gameCoords);
                            return;
                        }
                    }
                }
            }
        }
    }
}

void PlayingState::update(const float dt) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(game->window);
    game->updateCursorHelper(false);
    
    std::list<Animation*>::iterator i = animations.begin();
    while(i != animations.end()) {
        if((*i)->update(dt) == false) {
            i = animations.erase(i);
        } else {
            ++i;
        }
    }
    
    for(Player* player : players) {
        if(player->contains(mousePos)) {
            if(!player->selectable) {
                game->updateCursorHelper(true, mousePos);
            }
        }
    }
    
    for(FieldCard* card : fieldCards) {
        card->contains(sf::Mouse::getPosition(game->window));
    }
    
    iads += vel * dt;
    rouletteNeedle.setRotation(iads);
    
    if(vel > 0) {
        vel -= 500.0f * dt;
    } else {
        vel = 0;
    }
    
    updatePlayerHalo();
}

void PlayingState::draw(const float dt) {
    game->window.clear(light);
    
    // We're only rendering sf::Drawables so we can do that:
    for(sf::Drawable* entity : drawableEntities) {
        game->window.draw(*entity);
    }
    
    game->window.display();
}


void PlayingState::selectPlayer(Player* player) {
    selectedPlayer = player;
    
    if(player != nullptr) {
        playerHalo.setTexture(player->team == Team::BLUE ? game->texmgr.getRef("playerhalo_b") :
                                                           game->texmgr.getRef("playerhalo_r"));
        playerHalo.setColor(sf::Color(255, 255, 255, 255));
        
        if(task == Task::Placement) {
            for(FieldCard* card : fieldCards) {
                bool dim = ((selectedPlayer->team == Team::BLUE && card->gameCoords.x <= 2) ||
                            (selectedPlayer->team == Team::RED && card->gameCoords.x >= 2));
                card->available = dim;
            }
        }
    } else {
        playerHalo.setColor(sf::Color::Transparent);
    }
}

void PlayingState::updatePlayerPositions(bool animate) {
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
            animations.push_back(new Animation(player->sprite, AnimationDest::POS_X, pos.x, 0.5f));
            animations.push_back(new Animation(player->sprite, AnimationDest::POS_Y, pos.y, 0.5f));
        } else {
            player->sprite.setPosition(pos);
        }
        
    }
}

void PlayingState::updatePlayerHalo() {
    if(selectedPlayer != nullptr) {
        playerHalo.setPosition(selectedPlayer->sprite.getPosition() + sf::Vector2f(-7, -7));
    }
}

sf::Vector2f PlayingState::getCardPosition(sf::Vector2i gameCoords) {
    return sf::Vector2f(CARDS_ORIGIN_X + (CARD_W + 4) * gameCoords.x,
                        CARDS_ORIGIN_Y + (CARD_H + 3) * gameCoords.y);
}

void PlayingState::moveSelectedPlayer(sf::Vector2i gameCoords) {
    if(selectedPlayer != nullptr) {
        players.remove(selectedPlayer);
        players.push_back(selectedPlayer);
        selectedPlayer->gameCoords = gameCoords;
        updatePlayerPositions();
        selectPlayer(nullptr);
        makeFieldCardsAvailable();
    }
}

void PlayingState::makeFieldCardsAvailable() {
    for(FieldCard* card : fieldCards) {
        card->available = true;
    }
}