/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pacman.h
 * Author: angel
 *
 * Created on 9 de febrero de 2018, 13:26
 */

#ifndef PACMAN_H
#define PACMAN_H
#include <SFML/Graphics.hpp>

class pacman {
    
public:
    pacman();
    pacman(const pacman& orig);
    virtual ~pacman();
    void superPac();
    void normalPac();
    bool getPacMode();
    void movimientoPac(sf::Sprite&);
    void movimientoUP(sf::Sprite&);
    void movimientoDOWN(sf::Sprite&);
    void movimientoLEFT(sf::Sprite&);
    void movimientoRIGHT(sf::Sprite&);
    void muerte();
    int vidasActuales();
    void setLastKey(int);
    int getLastKey();
    int getVelocidad();
    void setMovimiento(bool);
    bool getMovimiento();
    int getNextMove();
    void setVidas(int);
    void setNextMove(int);
private:
    int velocidad;
    bool super;
    int lastkey;
    int nextmove;
    int contador;
    int vidas;
    bool en_movimiento;
};

#endif /* PACMAN_H */

