/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pacman.cpp
 * Author: angel
 * 
 * Created on 9 de febrero de 2018, 13:26
 */
#include <iostream>
#include "pacman.h"
#include "Mapa.h"
#include <SFML/Graphics.hpp>

pacman::pacman() {
    velocidad = 2;
    super = false;
    contador = 0;
    vidas = 3;
    en_movimiento = false;
    nextmove = 0;
    lastkey = 0;
}

void pacman::superPac(){
    super = true;
    velocidad = 3;
}
void pacman::normalPac(){
    super = false;
    velocidad = 2;
}
bool pacman::getPacMode(){
    return super;
}
void pacman::setLastKey(int key){
    lastkey = key;
}
int pacman::getLastKey(){
    return lastkey;
}
void pacman::movimientoUP(sf::Sprite& sprite){
    en_movimiento = true;
    sprite.setTextureRect(sf::IntRect(2*42, 0, 42, 42));
    sprite.move(0,-velocidad);
}

void pacman::movimientoDOWN(sf::Sprite& sprite){
    en_movimiento = true;
    sprite.setTextureRect(sf::IntRect(6*41.5, 0, 42, 42));
    sprite.move(0,velocidad);
}

void pacman::movimientoLEFT(sf::Sprite& sprite){
    en_movimiento = true;
    sprite.setTextureRect(sf::IntRect(1*42, 0, 42, 42));
    sprite.move(-velocidad,0);
    if(sprite.getPosition().x < -10){
        sprite.setPosition(800, sprite.getPosition().y);
    }
}

void pacman::movimientoRIGHT(sf::Sprite& sprite){
    en_movimiento = true;
    sprite.setTextureRect(sf::IntRect(5*41.5, 0, 42, 42));
    sprite.move(velocidad,0);
    if(sprite.getPosition().x > 800){
        sprite.setPosition(-10, sprite.getPosition().y);
    }
}

void pacman::movimientoPac(sf::Sprite& sprite){
    en_movimiento = true;
    switch(lastkey){
        case 1:
            sprite.move(velocidad,0);
            if(contador < 5){
                sprite.setTextureRect(sf::IntRect(7*41.5, 0, 42, 42));
            }
            else{
               sprite.setTextureRect(sf::IntRect(0, 0, 42, 42));
                if(contador > 10){
                    sprite.setTextureRect(sf::IntRect(5*41.5, 0, 42, 42));
                    if(contador > 15)
                    contador = 0;               
                }
            }
            if(sprite.getPosition().x > 800){
                sprite.setPosition(-10, sprite.getPosition().y);
            }
        break;
        case 2:
            sprite.move(-velocidad,0);
            if(contador < 5){
                sprite.setTextureRect(sf::IntRect(3*42, 0, 42, 42));
            }
            else{
               sprite.setTextureRect(sf::IntRect(0, 0, 42, 42));
                if(contador > 10){
                    sprite.setTextureRect(sf::IntRect(1*42, 0, 42, 42));
                    if(contador > 15)
                    contador = 0;               
                }
            }
            if(sprite.getPosition().x < -10){
                sprite.setPosition(800, sprite.getPosition().y);
            }
        break;
        case 3:
           
            sprite.move(0,-velocidad);
            if(contador < 5){
                sprite.setTextureRect(sf::IntRect(4*41.5, 0, 42, 42));
            }
            else{
                sprite.setTextureRect(sf::IntRect(0, 0, 42, 42));
                if(contador > 10){
                    sprite.setTextureRect(sf::IntRect(2*41.5, 0, 42, 42));
                    if(contador > 15)
                    contador = 0;               
                }
            }      
        break;
        case 4:  
            sprite.move(0,velocidad);
            if(contador < 5){
                sprite.setTextureRect(sf::IntRect(8*41.5, 0, 42, 42));
            }
            else{
               sprite.setTextureRect(sf::IntRect(0, 0, 42, 42));
                if(contador > 10){
                    sprite.setTextureRect(sf::IntRect(6*41.5, 0, 42, 42));
                    if(contador > 15)
                    contador = 0;               
                }
            }         
        break;
    }  
    //std::cout << contador << std::endl;
    contador++;
}

void pacman::muerte(){
    vidas--;
}

int pacman::vidasActuales(){
    return vidas;
}

int pacman::getVelocidad(){
    return velocidad;
}

void pacman::setMovimiento(bool n){
    en_movimiento = n;
}

bool pacman::getMovimiento(){
    return en_movimiento;
}

int pacman::getNextMove(){
    return nextmove;
}

void pacman::setNextMove(int n){
    nextmove = n;
}

void pacman::setVidas(int n){
    vidas = n;
}

pacman::pacman(const pacman& orig) {
}

pacman::~pacman() {
}

