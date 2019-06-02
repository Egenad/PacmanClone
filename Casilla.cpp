/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Casilla.cpp
 * Author: angel
 * 
 * Created on 17 de febrero de 2018, 10:56
 */

#include "Casilla.h"
#include <SFML/Graphics.hpp>

Casilla::Casilla(int t, float x, float y, bool hid) {
    
    tipo = t;
    coordx = x+0.3;
    coordy = y+1.5;
    hidden = hid;

    //Tipo 1 = punto
    //Tipo 2 = wall (pacman no se puede mover a esa posicion)
    //Tipo 3 = fruta (pacman la coje y se la guarda)
    //Tipo 4 = casilla por donde salen los monstruos
    //Tipo 5 = casilla de teletransporte (laterales)
    //Tipo 6 = vacio
    //Tipo 7 = buff
   
}

Casilla::Casilla(const Casilla& orig) {
}

int Casilla::tipoCasilla(){
    return tipo;
}

void Casilla::drawCasilla(sf::RenderWindow& window){

    switch(tipo){
        //dibujo cuadrado si no está hidden     
        case 1:{   
            rectangle.setSize(sf::Vector2f(5, 5));
            if(hidden == true){      
                rectangle.setFillColor(sf::Color::Yellow);
                rectangle.setPosition(40.5*coordx, 40.5*coordy);
                rectangle.setOrigin(-16,-16);
                window.draw(rectangle); 
            }
        }
        break;
        case 2:{   
            rectangle.setSize(sf::Vector2f(37,37));
            rectangle.setFillColor(sf::Color::Blue);
            rectangle.setPosition(40.5*coordx, 40.5*coordy);
            window.draw(rectangle);           
        }
        break;
        case 7:{
            circle.setRadius(10);
            if(hidden == true){
                circle.setFillColor(sf::Color::Yellow);
                circle.setPosition(40.5*coordx, 40.5*coordy);
                circle.setOrigin(-8,-8);
                window.draw(circle);
            }
        }
        break;
        case 8:
            rectangle.setSize(sf::Vector2f(37,10));
            rectangle.setFillColor(sf::Color::White);
            rectangle.setPosition(40.5*coordx, 42*coordy);
            window.draw(rectangle); 
        break;
    }
}
int Casilla::getTipo(){
    return tipo;
}

void Casilla::setHiddenTrue(){
    hidden = true;
}

void Casilla::setHidden(sf::RenderWindow& window){
    hidden = false;
    drawCasilla(window);
}
bool Casilla::getHidden(){
    return hidden;
}
sf::RectangleShape Casilla::returnShape(){
    return rectangle;
}
sf::CircleShape Casilla::returnCircleShape(){
    return circle;
}
Casilla::~Casilla() {
}

