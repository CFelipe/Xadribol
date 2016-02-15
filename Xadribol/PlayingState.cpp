#include "PlayingState.h"
#include <iostream>

PlayingState::PlayingState(Game* game) {
    this->game = game;
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
                for(Player* player : game->players) {
                    if(player->contains(mousePos)) {
                        if(player->selectable) {
                            game->selectPlayer(player);
                            return;
                        }
                    }
                }
                
                for(FieldCard* card : game->fieldCards) {
                    if(card->contains(mousePos)) {
                        if(card->available) {
                            game->moveSelectedPlayer(card->gameCoords);
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
    
    std::list<Animation*>::iterator i = game->animations.begin();
    while(i != game->animations.end()) {
        if((*i)->update(dt) == false) {
            i = game->animations.erase(i);
        } else {
            ++i;
        }
    }
    
    for(Player* player : game->players) {
        if(player->contains(mousePos)) {
            if(!player->selectable) {
                game->updateCursorHelper(true, mousePos);
            }
        }
    }
    
    for(FieldCard* card : game->fieldCards) {
        card->contains(sf::Mouse::getPosition(game->window));
    }
}

void PlayingState::draw(const float dt) {
    game->window.clear(game->light);
    
    for(FieldCard* card : game->fieldCards) {
        game->window.draw(card->sprite);
    }
    
    game->window.draw(game->playerHalo);
    
    for(Player* player : game->players) {
        game->window.draw(player->sprite);
    }
    
    
    game->window.draw(game->cursorHelper);
    
    game->window.display();
}