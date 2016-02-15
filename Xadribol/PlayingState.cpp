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
        }
    }
}

void PlayingState::update(const float dt) {
}

void PlayingState::draw(const float dt) {
    game->window.clear(game->light);
    
    for(FieldCard* card : game->fieldCards) {
        game->window.draw(card->sprite);
    }
    
    game->window.display();
}