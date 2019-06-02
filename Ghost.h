/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Ghost.h
 * Author: angel
 *
 * Created on 19 de marzo de 2018, 11:33
 */

#ifndef GHOST_H
#define GHOST_H
#include <SFML/Graphics.hpp>

class Ghost {
public:
    Ghost(int);
    Ghost(const Ghost& orig);
    virtual ~Ghost();
    void setAsustados();
    void setNormales();
    void drawGhost(sf::RenderWindow&);
    void setPosision(float,float);
    void moveGhost(float, float);
    sf::Sprite& getSGhost();
    sf::Vector2f getLastMov();
    void setLastMov(sf::Vector2f);
    int getColorPos();
    void setSprite(int);
    void setLastMove(int);
    void switchsprite();
private:
    int lastmove;
    int switchs;
    int color;
    sf::Texture tex;
    sf::Sprite sprite;
    sf::Vector2f lastmov;
};

#endif /* GHOST_H */

