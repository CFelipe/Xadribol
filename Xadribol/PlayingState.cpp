#include "PlayingState.h"
#include <iostream>
#include <algorithm>
#include "ActionCard.h"

PlayingState::PlayingState(Game* game)
    : task(Task::Placement),
    turn(0),
    scoreRed(0),
    scoreBlue(0),
    selectedPlayer(nullptr),
    ballPlayer(nullptr)
{
    this->game = game;

    std::srand(std::time(0));

    /*
    Try to set up drawables here as they're drawn from top to bottom

    If they're drawn on top of each other (like players and cards) add what's behind

    So I recommend  Visible - Invisible (cursorHelper) / Top - Bottom / Back - Front

    When pushing to drawableEntities, mind the order as entities are drawn in the order they're added

    Don't forget to add drawables to drawableEntities when they're created, of course
    */

    redBar.setSize(sf::Vector2f(800, 7));
    redBar.setPosition(0, 50);
    redBar.setFillColor(red);
    blueBar.setSize(sf::Vector2f(400, 7));
    blueBar.setPosition(0, 50);
    blueBar.setFillColor(blue);
    actionBar.setPosition(0, 57);
    actionBar.setSize(sf::Vector2f(800, 178));
    actionBar.setFillColor(dark);

    roulette.setTextureRect(sf::IntRect(0, 0, 68, 68));
    roulette.setTexture(game->texmgr.getRef("roulette"));
    roulette.setPosition(sf::Vector2f(400 - 68 / 2, 141));

    rouletteNeedle.setTextureRect(sf::IntRect(0, 0, 10, 30));
    game->texmgr.getRef("roulette_needle").setSmooth(true);
    rouletteNeedle.setTexture(game->texmgr.getRef("roulette_needle"));
    rouletteNeedle.setPosition(sf::Vector2f(400, 175));
    rouletteNeedle.setOrigin(sf::Vector2f(5, 21));
    rouletteNeedle.setRotation(0);

    // Use sf::String(L"String"); for accents etc
    playButton = new TextButton(sf::String(L"Começar"), 32, game->gameFont, light, dark);
    playButton->setPosition(sf::Vector2f(400, 100));

    textScore = new Text(sf::String(scoreBlue + " X " + scoreRed), 32, game->gameFont, light, dark);
    textScore->setPosition(sf::Vector2f(400, 10));

    textAP = new Text(sf::String(actionPoints), 32, game->gameFont, light, dark);
    textAP->setPosition(sf::Vector2f(700, 90));

    drawableEntities.push_back(&redBar);
    drawableEntities.push_back(&blueBar);
    drawableEntities.push_back(&actionBar);
    drawableEntities.push_back(&roulette);
    drawableEntities.push_back(&rouletteNeedle);
    drawableEntities.push_back(playButton);
    drawableEntities.push_back(textScore);
    drawableEntities.push_back(textAP);

    selectedAction = nullptr;
    selectedFieldCard = nullptr;
    
    endTurnCard = new EndTurnCard(game->texmgr.getRef("card_endturn_r"));
    moveCard = new MoveCard(game->texmgr.getRef("card_move_b"));
    passCard = new PassCard(game->texmgr.getRef("card_pass_b"));
    kickCard = new KickCard(game->texmgr.getRef("card_kick_b"));
    defendCard = new DefendCard(game->texmgr.getRef("card_defend_r"));
    stealCard = new StealCard(game->texmgr.getRef("card_steal_r"));
    dribbleCard = new DribbleCard(game->texmgr.getRef("card_dribble_b"));

    // Field cards
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
    players.push_back(new Player(game->texmgr.getRef("player_b"),   sf::Vector2i(1, 0), Team::BLUE, true));
    players.push_back(new Player(game->texmgr.getRef("player_b"),   sf::Vector2i(2, 1), Team::BLUE, false));
    players.push_back(new Player(game->texmgr.getRef("player_b"),   sf::Vector2i(1, 2), Team::BLUE, true));
    players.push_back(new Player(game->texmgr.getRef("player_b"),   sf::Vector2i(0, 1), Team::BLUE, false, true));
    
    players.push_back(new Player(game->texmgr.getRef("player_r"),   sf::Vector2i(3, 0), Team::RED, true));
    players.push_back(new Player(game->texmgr.getRef("player_r"),   sf::Vector2i(2, 1), Team::RED, false));
    players.push_back(new Player(game->texmgr.getRef("player_r"),   sf::Vector2i(3, 2), Team::RED, true));
    players.push_back(new Player(game->texmgr.getRef("player_r"),   sf::Vector2i(4, 1), Team::RED, false, true));

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

    //sf::Vector2f pos1 = getCardPosition(sf::Vector2i(0, 0));
    for(FieldCard* card : fieldCards) {
        sf::Vector2f pos = getCardPosition(card->gameCoords);
        card->sprite.setPosition(pos);

        // Pompous introduction
        //animations.push_back(new PosAnimation(card->sprite, pos, 1.0f));
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
            if(task != Task::PlacementTransition) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Vector2i(event.mouseButton.x,
                                                         event.mouseButton.y);

                    if(playButton->contains(mousePos)) {
                        finishPlacement();
                        return;
                    }

                    for(Player* player : players) {
                        if(player->contains(mousePos)) {
                            if(task == Task::PassPlayerSelection) {
                                if(player->getSelectable()) {
                                    selectPlayer(player);
                                    selectedAction->action(this);
                                }
                            } else if(player->getSelectable()) {
                                selectPlayer(player);
                                return;
                            }
                        }
                    }

                    for(FieldCard* card : fieldCards) {
                        if(card->contains(mousePos)) {
                            if(task == Task::Placement) {
                                if(card->available) {
                                    moveSelectedPlayer(card->gameCoords);
                                    return;
                                }
                            } else if(task == Task::FieldCardSelection && card->available) {
                                selectedFieldCard = card;
                                selectedAction->action(this);
                            }
                        }
                    }

                    for(ActionCard* card : currentCards) {
                        if(card->contains(mousePos) && task == Task::ActionSelection) {
                            if(card->getCostAP() < actionPoints) {
                                actionPoints -= card->getCostAP();
                                updateTextAP();
                                card->action(this);
                                return;
                            }
                        }
                    }
                }
            }
        }
    }
}

void PlayingState::update(const float dt) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(game->window);
    game->updateCursorHelper(task == Task::PlacementTransition, mousePos);

    std::list<Animation*>::iterator i = animations.begin();
    while(i != animations.end()) {
        if((*i)->update(dt) == false) {
            i = animations.erase(i);
        } else {
            ++i;
        }
    }

    playButton->contains(mousePos);

    for(Player* player : players) {
        if(player->contains(mousePos)) {
            if(!player->getSelectable()) {
                game->updateCursorHelper(true, mousePos);
            }
        }
    }

    for(FieldCard* card : fieldCards) {
        card->contains(sf::Mouse::getPosition(game->window));
    }


    for(ActionCard* card : currentCards) {
        card->contains(sf::Mouse::getPosition(game->window));
    }

    if(task == Task::PlacementTransition) {
        needleRotation += needleVel * dt;
        if(needleRotation > 360) needleRotation -= 360;

        rouletteNeedle.setRotation(needleRotation);
        if(needleVel > 0) {
            needleVel -= 1000.0f * dt;
        } else {
            needleVel = 0;
            Team selectedTeam = (needleRotation >= 180.0f) ? Team::BLUE : Team::RED;

            animations.push_back(new PosAnimation(*playButton,
                                                  playButton->getPosition() + sf::Vector2f(600.0f, 0.0f),
                                                  2.0f, Easing::INOUT));
            animations.push_back(new PosAnimation(roulette,
                                                  roulette.getPosition() + sf::Vector2f(600.0f, 0.0f),
                                                  2.2f, Easing::INOUT));
            animations.push_back(new PosAnimation(rouletteNeedle,
                                                  rouletteNeedle.getPosition() + sf::Vector2f(600.0f, 0.0f),
                                                  2.2f, Easing::INOUT));

            for(Player* player : players) {
                if(player->gameCoords == sf::Vector2i(2, 1) && selectedTeam == player->team) {
                    moveBallToPlayer(player);
                    task = Task::ActionSelection;
                    changeTurn(selectedTeam);
                    return;
                }
            }
        }
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

    // The method checks if the card is in the list so don't worry
        removeActionCardFromList(*moveCard);
        removeActionCardFromList(*passCard);
        removeActionCardFromList(*kickCard);
        removeActionCardFromList(*dribbleCard);
        removeActionCardFromList(*defendCard);
        removeActionCardFromList(*stealCard);

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
        } else if(task == Task::ActionSelection) {
            if(player->goalie == false) {
                addActionCardToList(*moveCard);   
            }
            
            if(player->team == ballPlayer->team && player == ballPlayer) {
                // Player has ball
                for(Player* player2 : players) {
                    if(player->gameCoords == player2->gameCoords &&
                       player->team != player2->team &&
                       player != player2) {
                        removeActionCardFromList(*moveCard);
                        addActionCardToList(*dribbleCard);
                        break;
                    }
                }
                
                addActionCardToList(*passCard);
                addActionCardToList(*kickCard);
            } else if(ballPlayer->team != player->team){
                // Defense-specific cards
                if(player->gameCoords == ballPlayer->gameCoords) {
                    addActionCardToList(*stealCard);
                }
            }
            
            if(player->goalie) {
                addActionCardToList(*defendCard);
            }
        }
    } else {
        
        playerHalo.setColor(sf::Color::Transparent);
        for(FieldCard* card : fieldCards) {
            card->available = true;
        }

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
            
            if(player->gameCoords == sf::Vector2i(0, 1) && !player->goalie) {
                offsetX += 40;
            }
            
            if(player->goalie == false) {
                offsetY += blueMap[idx] * PLAYER_VSPACE;
                blueMap[idx]++;
            } else {
                offsetY = 40;
            }
        } else {
            offsetX = CARD_W - PLAYER_W - PLAYER_MARGIN_X;
            
            if(player->gameCoords == sf::Vector2i(4, 1) && !player->goalie) {
                offsetX -= 40;
            }
            
            if(player->goalie == false) {
                offsetY += redMap[idx] * PLAYER_VSPACE;
                redMap[idx]++;
            } else {
                offsetY = 40;
            }
            
            //offsetY += redMap[idx] * PLAYER_VSPACE;
            //redMap[idx]++;
        }

        sf::Vector2f pos(offsetX + CARDS_ORIGIN_X + (CARD_W + 4) * player->gameCoords.x,
                         offsetY + CARDS_ORIGIN_Y + (CARD_H + 3) * player->gameCoords.y);

        if(player == ballPlayer) {
            sf::Vector2f ballPos = sf::Vector2f(pos.x,
                                                pos.y + 12);
            
            ballPos.x += (player->team == Team::BLUE) ? 8 : -2;
            
            if(animate) {
                animations.push_back(new PosAnimation(ball, ballPos, 0.8f, Easing::OUT));
            } else {
                ball.setPosition(ballPos);
            }
        }
        
        if(animate) {
            // TODO: Check if position changed and animate only if it did!
            animations.push_back(new PosAnimation(player->sprite, pos, 0.8f, Easing::INOUT));
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

void PlayingState::makeFieldCardsAvailable(bool available) {
    for(FieldCard* card : fieldCards) {
        card->available = available;
    }
}

void PlayingState::moveBallToPlayer(Player* player, bool animate) {
    sf::Vector2f pos = sf::Vector2f(player->sprite.getPosition().x,
                                    player->sprite.getPosition().y + 12);

    pos.x += (player->team == Team::BLUE) ? 8 : -2;

    if(animate) {
        animations.push_back(new PosAnimation(ball, pos, 1.0f, Easing::INOUT));
    } else {
        ball.setPosition(pos);
    }

    ballPlayer = player;
}

void PlayingState::finishPlacement() {
    selectPlayer(nullptr);
    task = Task::PlacementTransition;
    playButton->disable();

    needleVel = 1500.0f + (std::rand() % 300);
}

void PlayingState::changeTurn() {
    changeTurn((turnTeam == Team::BLUE) ? Team::RED : Team::BLUE);
}

void PlayingState::changeTurn(Team team) {
    for(ActionCard* card : currentCards) {
        drawableEntities.remove(&card->sprite);
    }
    
    currentCards.clear();
    
    selectPlayer(nullptr);
    turnTeam = team;
    addActionCardToList(*endTurnCard);

    sf::Vector2f blueBarScale((turnTeam == Team::BLUE) ? 2.0f : 0.0f, 1.0f);
    animations.push_back(new ScaleAnimation(blueBar, blueBarScale, 2.0f, Easing::INOUT));

    for(Player* player : players) {
        player->setSelectable(player->team == turnTeam);
    }

    actionPoints = 5;
}

void PlayingState::updateTextScore() {
    textScore->setString(sf::String(scoreBlue + " X " + scoreRed))
}

void PlayingState::updateTextAP() {
    textAP->setString(sf::String(actionPoints));
}

void PlayingState::addActionCardToList(ActionCard& card) {
    if(std::find(currentCards.begin(), currentCards.end(), &card) == currentCards.end()) {
        sf::Vector2f cardPos(20 + (110 * currentCards.size()), 76);
        card.sprite.setPosition(cardPos - sf::Vector2f(0, -10.0f));
        animations.push_back(new PosAnimation(card.sprite, cardPos, 0.5f, Easing::OUT));
        currentCards.push_back(&card);
        drawableEntities.push_back(&card.sprite);
    }
}

void PlayingState::removeActionCardFromList(ActionCard& card) {
        currentCards.remove(&card);
        drawableEntities.remove(&card.sprite);
}

void PlayingState::hideActionCards() {
    for(ActionCard* card : currentCards) {
        if(card != selectedAction) {
            drawableEntities.remove(&card->sprite);
        } else {
            sf::Vector2f cardPos(20, 76);
            animations.push_back(new PosAnimation(card->sprite, cardPos, 0.5f, Easing::OUT));
        }
    }
}

void PlayingState::endAction() {
    drawableEntities.push_back(&endTurnCard->sprite);
}