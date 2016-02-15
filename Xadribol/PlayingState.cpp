#include "PlayingState.h"

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
}