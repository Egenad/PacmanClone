/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Casilla.h
 * Author: angel
 *
 * Created on 17 de febrero de 2018, 10:56
 */

#ifndef CASILLA_H
#define CASILLA_H
#include <SFML/Graphics.hpp>

class Casilla {
    
public:
    Casilla(int, float, float, bool);
    Casilla(const Casilla& orig);
    virtual ~Casilla();
    bool getHidden();
    void comprobarCasilla();
    int tipoCasilla();
    void drawCasilla(sf::RenderWindow& window);
    int getTipo();
    void setHidden(sf::RenderWindow& window);
    sf::RectangleShape returnShape();
    sf::CircleShape returnCircleShape();
    void setHiddenTrue();
private:
    bool hidden;
    int tipo;
    float coordx;
    float coordy;
    int v1;
    int v2;
    int v3;
    int v4;
    sf::RectangleShape rectangle;
    sf::CircleShape circle;
};

#endif /* CASILLA_H */

