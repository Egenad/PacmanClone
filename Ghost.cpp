/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ghost.cpp
 * Author: angel
 * 
 * Created on 19 de marzo de 2018, 11:33
 */

#include "Ghost.h"
#include "Mapa.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Ghost::Ghost(int pos) {
    
    if (!tex.loadFromFile("blue_ghost.png"))
    {
        std::cerr << "Error cargando la imagen blue_ghost.png";
        exit(0);
    }
    
    color = pos;
    
    sprite.setTexture(tex);
    sprite.setOrigin(42/2,42/2);
    sprite.setTextureRect(sf::IntRect(0*42, 0, 42, 42)); 
    sprite.setPosition((42*pos)+352, 443);
    if(pos != 0){
        switch(pos){
            case 1:
                sprite.setColor(sf::Color(255,105,180));
            break;
            case 2:
                sprite.setColor(sf::Color::Yellow);
            break;
            case 3:
                sprite.setColor(sf::Color::Red);
            break;
        }
    }
    lastmov = sf::Vector2f(0,0);
    lastmove = 0;
    switchs = 0;
}

void Ghost::drawGhost(sf::RenderWindow& window){
    window.draw(sprite);
}

void Ghost::moveGhost(float x, float y){
    sprite.move(x,y);
}

void Ghost::setPosision(float x, float y){
    sprite.setPosition(x,y);
}

sf::Sprite& Ghost::getSGhost(){
    return sprite;
}

void Ghost::setAsustados(){
    sprite.setTextureRect(sf::IntRect(8*42-2, 0, 42, 42));
    sprite.setColor(sf::Color::White);
}

void Ghost::setNormales(){
    sprite.setTextureRect(sf::IntRect(0*42, 0, 42, 42));
    switch(color){
        case 1:
            sprite.setColor(sf::Color(255,105,180));
        break;
        case 2:
            sprite.setColor(sf::Color::Yellow);
        break;
        case 3:
            sprite.setColor(sf::Color::Red);
        break;    
    }
}

void Ghost::setSprite(int n){
    switch(n){
        case 1:
            sprite.setTextureRect(sf::IntRect((6*42)-2, 0, 42, 42)); //derecha
        break;
        case 2:
            sprite.setTextureRect(sf::IntRect(4*42, 0, 42, 42)); //izquierda
        break;
        case 3:
            sprite.setTextureRect(sf::IntRect(0*42, 0, 42, 42)); //arriba
        break;
        case 4:
            sprite.setTextureRect(sf::IntRect(2*42, 0, 42, 42)); //abajo
        break;
    }
}

void Ghost::switchsprite(){
    switch(lastmove){
        case 1: //derecha
            if(switchs == 0){
                sprite.setTextureRect(sf::IntRect((7*42)-2, 0, 42, 42));
                switchs = 1;
            }
            else{
                sprite.setTextureRect(sf::IntRect((6*42)-2, 0, 42, 42));
                switchs = 0;
            }
        break;
        case 2: //izquierda
            if(switchs == 0){
                sprite.setTextureRect(sf::IntRect(5*42, 0, 42, 42));
                switchs = 1;
            }
            else{
                sprite.setTextureRect(sf::IntRect(4*42, 0, 42, 42));
                switchs = 0;
            }
        break;
        case 3: //arriba
            if(switchs == 0){
                sprite.setTextureRect(sf::IntRect(1*42, 0, 42, 42));
                switchs = 1;
            }
            else{
                sprite.setTextureRect(sf::IntRect(0*42, 0, 42, 42));
                switchs = 0;
            }
        break;
        case 4: //abajo
            if(switchs == 0){
                sprite.setTextureRect(sf::IntRect(3*42, 0, 42, 42));
                switchs = 1;
            }
            else{
                sprite.setTextureRect(sf::IntRect(2*42, 0, 42, 42));
                switchs = 0;
            }
        break;
    }
}

void Ghost::setLastMove(int n){
    lastmove = n;
}

sf::Vector2f Ghost::getLastMov(){
    return lastmov;
}

void Ghost::setLastMov(sf::Vector2f v){
    lastmov = v;
}

int Ghost::getColorPos(){
    return color;
}

Ghost::Ghost(const Ghost& orig) {
}

Ghost::~Ghost() {
}

