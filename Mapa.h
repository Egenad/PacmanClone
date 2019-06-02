/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mapa.h
 * Author: angel
 *
 * Created on 17 de febrero de 2018, 10:51
 */

#ifndef MAPA_H
#define MAPA_H

#include "Casilla.h"
#include "pacman.h"
#include "Ghost.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Mapa {
    
public:
    Mapa();
    Mapa(const Mapa& orig);
    virtual ~Mapa();
    void drawCasillas(sf::RenderWindow&, sf::Sprite&);
    void panelControl(sf::Event&, sf::Sprite&, sf::RenderWindow&);
    void movLast(sf::Sprite&, sf::RenderWindow&);
    bool comprobarCasilla(sf::Sprite&, sf::RenderWindow&);
    void choque(sf::Sprite&);
    void muertePacman();
    void muerteFantasma();
    void updateNPCS(sf::Sprite&);
private:
    int puntuacion;
    int vidaextra;
    Casilla * casillas[19][21]; 
    pacman * pac;
    std::vector<Ghost*> cola;
    std::vector<Ghost*> fantasmas;
    bool ghostinit;
    void iniciarFantasmas(int);
    void ghostAI(int, sf::Sprite&);
    bool reset;
    bool win;
    void choqueGhost(Ghost*, int);
    sf::Clock reloj;
    sf::Clock reloj2;
    sf::Clock super_time;
    sf::Clock ghostmove;
    sf::Clock reset_time;
    int reset_count;
};

#endif /* MAPA_H */

