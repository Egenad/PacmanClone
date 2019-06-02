/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mapa.cpp
 * Author: angel
 * 
 * Created on 17 de febrero de 2018, 10:52
 */

#include "Mapa.h"
#include "Casilla.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159265

Mapa::Mapa() {
    //720/42=17'14.... 950/42=22'6...
    int valores [21][19] = {{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}, //1
                            {2,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,2}, //2
                            {2,7,2,2,1,2,2,2,1,2,1,2,2,2,1,2,2,7,2}, //3
                            {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2}, //4
                            {2,1,2,2,1,2,1,2,2,2,2,2,1,2,1,2,2,1,2}, //5
                            {2,1,1,1,1,2,1,1,1,2,1,1,1,2,1,1,1,1,2}, //6
                            {2,2,2,2,1,2,2,2,6,2,6,2,2,2,1,2,2,2,2}, //7
                            {6,6,6,2,1,2,6,6,6,6,6,6,6,2,1,2,6,6,6}, //8
                            {2,2,2,2,1,2,6,2,2,8,2,2,6,2,1,2,2,2,2}, //9
                            {5,6,6,6,1,6,6,2,4,4,4,2,6,6,1,6,6,6,5}, //10
                            {2,2,2,2,1,2,6,2,2,2,2,2,6,2,1,2,2,2,2}, //11
                            {6,6,6,2,1,2,6,6,6,6,6,6,6,2,1,2,6,6,6}, //12
                            {2,2,2,2,1,2,6,2,2,2,2,2,6,2,1,2,2,2,2}, //13
                            {2,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,2}, //14
                            {2,7,2,2,1,2,2,2,1,2,1,2,2,2,1,2,2,7,2}, //15
                            {2,1,1,2,1,1,1,1,1,6,1,1,1,1,1,2,1,1,2}, //16
                            {2,2,1,2,1,2,1,2,2,2,2,2,1,2,1,2,1,2,2}, //17
                            {2,1,1,1,1,2,1,1,1,2,1,1,1,2,1,1,1,1,2}, //18
                            {2,1,2,2,2,2,2,2,1,2,1,2,2,2,2,2,2,1,2}, //19
                            {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2}, //20
                            {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}  //21
                            }; 
                           
    for(int i=0; i<19; i++){
        for(int j=0; j<21; j++){
            casillas[i][j] = new Casilla(valores[j][i], i, j, true);
            //std::cout << valores[j][i];
        }
    }
    
    ghostinit = false;
    win = false;
    pac = new pacman();
    reset = false;
    puntuacion = 0;
    vidaextra = 0;
    reset_count = 3;
}

Mapa::Mapa(const Mapa& orig) {
}

Mapa::~Mapa() {
}

void Mapa::iniciarFantasmas(int n){
    Ghost * fantasma = new Ghost(n);
    cola.push_back(fantasma);
}

void Mapa::movLast(sf::Sprite& sprite, sf::RenderWindow& window){
    if(pac->getLastKey() != 0){
        pac->movimientoPac(sprite);
    }
}

void Mapa::panelControl(sf::Event& event, sf::Sprite& sprite, sf::RenderWindow& window){
    if(reset == false){
        switch(event.key.code) {                   
            //Mapeo del cursor
            case sf::Keyboard::Right:{
                if(win == false){
                    if(!pac->getMovimiento()){
                        pac->movimientoRIGHT(sprite); 
                        pac->setLastKey(1);
                    }
                    else{
                        pac->setNextMove(1);
                    }
                }
            }
            break;

            case sf::Keyboard::Left:
                if(win == false){
                    if(!pac->getMovimiento()){
                        pac->movimientoLEFT(sprite);
                        pac->setLastKey(2);
                    }
                    else{
                        pac->setNextMove(2);
                    }
                }
            break;

            case sf::Keyboard::Up:
                if(win == false){
                    if(!pac->getMovimiento()){
                        pac->movimientoUP(sprite);
                        pac->setLastKey(3);
                    }
                    else{
                        pac->setNextMove(3);
                    }
                }
            break;

            case sf::Keyboard::Down:
                if(win == false){
                    if(!pac->getMovimiento()){
                        pac->movimientoDOWN(sprite);
                        pac->setLastKey(4);
                    }
                    else{
                        pac->setNextMove(4);
                    }
                }
            break;

            //Tecla ESC para salir
            case sf::Keyboard::Escape:
                window.close();
            break;

            //Cualquier tecla desconocida se imprime por pantalla su código
            default:
                if(event.key.code==16){
                    window.close();        
                }
                else std::cout << event.key.code << std::endl;
            break;                   
        }
    }
}

void Mapa::ghostAI(int n, sf::Sprite& pacman){

    fantasmas[n]->moveGhost(fantasmas[n]->getLastMov().x, fantasmas[n]->getLastMov().y);
    
    bool comp = false;
    
    for(int i=0; i<19 && comp == false; i++){
        for(int j=0; j<21 && comp == false; j++){

            int tip = casillas[i][j]->getTipo();

            if(tip != 1 && tip != 6 && tip != 7){
                if(fantasmas[n]->getSGhost().getGlobalBounds().intersects(casillas[i][j]->returnShape().getGlobalBounds())){
                    //he chocao loco
                    comp = true;
                    fantasmas[n]->moveGhost(-fantasmas[n]->getLastMov().x, -fantasmas[n]->getLastMov().y);
                }
            }
        }
    }
    
    if(comp == true || fantasmas[n]->getLastMov() == sf::Vector2f(0,0)){
        
        comp = false;
        
        //calculo del angulo fantasma-pacman

        float distancia2 = fantasmas[n]->getSGhost().getPosition().y - pacman.getPosition().y;
        float distancia = sqrt(pow((fantasmas[n]->getSGhost().getPosition().x-pacman.getPosition().x),2)+pow((fantasmas[n]->getSGhost().getPosition().y-pacman.getPosition().y),2));
        float result = asin(distancia2/distancia) * 180.0 / PI;

        //std::cout << "Inicial: "<<result << std::endl;

        if(fantasmas[n]->getSGhost().getPosition().x > pacman.getPosition().x){
            if(fantasmas[n]->getSGhost().getPosition().y > pacman.getPosition().y){
                result = result + 90;
            }
            else{
                if(fantasmas[n]->getSGhost().getPosition().y < pacman.getPosition().y){
                    result = result + 270;
                }
            }   
        }
        else{
            if(fantasmas[n]->getSGhost().getPosition().y < pacman.getPosition().y){
                result = result + 360;
            }
        }

        //casos especiales

        if(fantasmas[n]->getSGhost().getPosition().x == pacman.getPosition().x && fantasmas[n]->getSGhost().getPosition().y < pacman.getPosition().y){
            result = 270;
        }
        else{
            if(fantasmas[n]->getSGhost().getPosition().y == pacman.getPosition().y && fantasmas[n]->getSGhost().getPosition().x > pacman.getPosition().x){
                result = 180;
            }
        }

        //std::cout << "Final: "<<result << std::endl;

        //Movimiento del fantasma dependiendo del angulo dado

        if(result == 0){
            fantasmas[n]->setLastMov(sf::Vector2f(1.3,0));
            if(!pac->getPacMode()){
                fantasmas[n]->setSprite(1);
                fantasmas[n]->setLastMove(1);
            }
        }
        else{
            if(result > 0 && result < 90){
                choqueGhost(fantasmas[n], 1);
            }
            else{
                if(result == 90){
                    fantasmas[n]->setLastMov(sf::Vector2f(0,-1.3));
                    if(!pac->getPacMode()){
                        fantasmas[n]->setSprite(3);
                        fantasmas[n]->setLastMove(3);
                    }
                }
                else{
                    if(result > 90 && result < 180){
                        choqueGhost(fantasmas[n], 2);
                    }
                    else{
                        if(result == 180){
                            fantasmas[n]->setLastMov(sf::Vector2f(-1.3,0));
                            if(!pac->getPacMode()){
                                fantasmas[n]->setSprite(2);
                                fantasmas[n]->setLastMove(2);
                            }
                        }
                        else{
                            if(result > 180 && result < 270){
                                choqueGhost(fantasmas[n], 3);

                            }
                            if(result == 270){
                                fantasmas[n]->setLastMov(sf::Vector2f(0,1.3));
                                if(!pac->getPacMode()){
                                    fantasmas[n]->setSprite(4);
                                    fantasmas[n]->setLastMove(4);
                                }
                            }
                            else{
                                if(result > 270 && result < 360){
                                    choqueGhost(fantasmas[n], 4);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    //std::cout << fantasmas[n]->getLastMov().x << " , " << fantasmas[n]->getLastMov().y << std::endl;

}

void Mapa::choqueGhost(Ghost* gho, int cuadrante){
    
    bool comp = false;
    
    switch(cuadrante){
        case 1:
            gho->moveGhost(0,-1.3);
            if(!pac->getPacMode()){
                gho->setSprite(3);
                gho->setLastMove(3);
            }
            gho->setLastMov(sf::Vector2f(0,-1.3));
            for(int i=0; i<19 && comp == false; i++){
                for(int j=0; j<21 && comp == false; j++){
            
                    int tip = casillas[i][j]->getTipo();
                    
                    if(tip != 1 && tip != 6 && tip != 7){
                        if(gho->getSGhost().getGlobalBounds().intersects(casillas[i][j]->returnShape().getGlobalBounds())){
                            //he chocao loco
                            comp = true;
                            gho->moveGhost(0,1.3);
                            gho->setLastMov(sf::Vector2f(0,1.3));
                        }
                    }
                }
            }
            
            if(comp){
                int contador = 0;
                while(comp == true){
                    comp = false;
                    
                    switch(contador){
                        case 0:
                            gho->moveGhost(1.3,0);
                            if(!pac->getPacMode()){
                                gho->setSprite(1);
                                gho->setLastMove(1);
                            }
                            gho->setLastMov(sf::Vector2f(1.3,0));
                            break;
                        case 1:
                            gho->moveGhost(-1.3,0);
                            if(!pac->getPacMode()){
                                gho->setSprite(2);
                                gho->setLastMove(2);
                            }
                            gho->setLastMov(sf::Vector2f(-1.3,0));
                            break;
                    }
                    
                    
                    for(int i=0; i<19 && comp == false; i++){
                        for(int j=0; j<21 && comp == false; j++){

                            int tip = casillas[i][j]->getTipo();

                            if(tip != 1 && tip != 6 && tip != 7){
                                if(gho->getSGhost().getGlobalBounds().intersects(casillas[i][j]->returnShape().getGlobalBounds())){
                                    //he chocao loco
                                    comp = true;
                                    
                                    switch(contador){
                                        case 0:
                                            gho->moveGhost(-1.3,0);
                                            gho->setLastMov(sf::Vector2f(-1.3,0));
                                            break;
                                        case 1:
                                            gho->moveGhost(1.3,0);
                                            gho->setLastMov(sf::Vector2f(1.3,0));
                                            break;
                                    } 
                                }
                            }
                        }
                    }
                    contador++;
                }
            }
            
            break;
        case 2:
            gho->moveGhost(-1.3,0);
            if(!pac->getPacMode()){
                gho->setSprite(2);
                gho->setLastMove(2);
            }
            gho->setLastMov(sf::Vector2f(-1.3,0));
            for(int i=0; i<19; i++){
                for(int j=0; j<21; j++){
            
                    int tip = casillas[i][j]->getTipo();
                    
                    if(tip != 1 && tip != 6 && tip != 7){
                        if(gho->getSGhost().getGlobalBounds().intersects(casillas[i][j]->returnShape().getGlobalBounds())){
                            //he chocao loco
                            comp = true;
                            gho->moveGhost(1.3,0);
                            gho->setLastMov(sf::Vector2f(1.3,0));
                        }
                    } 
                }
            }
            if(comp){
                int contador = 0;
                while(comp == true){
                    comp = false;
                    
                    switch(contador){
                        case 0:
                            gho->moveGhost(0,-1);
                            if(!pac->getPacMode()){
                                gho->setSprite(3);
                                gho->setLastMove(3);
                            }
                            gho->setLastMov(sf::Vector2f(0,-1.3));
                            break;
                        case 1:
                            gho->moveGhost(0,1);
                            if(!pac->getPacMode()){
                                gho->setSprite(4);
                                gho->setLastMove(4);
                            }
                            gho->setLastMov(sf::Vector2f(0,1.3));
                            break;
                    }
                    
                    
                    for(int i=0; i<19 && comp == false; i++){
                        for(int j=0; j<21 && comp == false; j++){

                            int tip = casillas[i][j]->getTipo();

                            if(tip != 1 && tip != 6 && tip != 7){
                                if(gho->getSGhost().getGlobalBounds().intersects(casillas[i][j]->returnShape().getGlobalBounds())){
                                    //he chocao loco
                                    comp = true;
                                    
                                    switch(contador){
                                        case 0:
                                            gho->moveGhost(0,-1.3);
                                            gho->setLastMov(sf::Vector2f(0,-1.3));
                                            break;
                                        case 1:
                                            gho->moveGhost(0,1.3);
                                            gho->setLastMov(sf::Vector2f(0,1.3));
                                            break;
                                    } 
                                }
                            }
                        }
                    }
                    contador++;
                }
            }
            break;
        case 3:
            gho->moveGhost(0,1.3);
            if(!pac->getPacMode()){
                gho->setSprite(4);
                gho->setLastMove(4);
            }
            gho->setLastMov(sf::Vector2f(0,1.3));
            for(int i=0; i<19; i++){
                for(int j=0; j<21; j++){
            
                    int tip = casillas[i][j]->getTipo();
                    
                    if(tip != 1 && tip != 6 && tip != 7){
                        if(gho->getSGhost().getGlobalBounds().intersects(casillas[i][j]->returnShape().getGlobalBounds())){
                            //he chocao loco
                            comp = true;
                            gho->moveGhost(0,-1.3);
                            gho->setLastMov(sf::Vector2f(0,-1.3));
                        }
                    }   
                }
            }
            if(comp){
                int contador = 0;
                while(comp == true){
                    comp = false;
                    
                    switch(contador){
                        case 0:
                            gho->moveGhost(-1.3,0);
                            if(!pac->getPacMode()){
                                gho->setSprite(2);
                                gho->setLastMove(2);
                            }
                            gho->setLastMov(sf::Vector2f(-1.3,0));
                            break;
                        case 1:
                            gho->moveGhost(1.3,0);
                            if(!pac->getPacMode()){
                                gho->setSprite(1);
                                gho->setLastMove(1);
                            }
                            gho->setLastMov(sf::Vector2f(1.3,0));
                            break;
                    }

                    for(int i=0; i<19 && comp == false; i++){
                        for(int j=0; j<21 && comp == false; j++){

                            int tip = casillas[i][j]->getTipo();

                            if(tip != 1 && tip != 6 && tip != 7){
                                if(gho->getSGhost().getGlobalBounds().intersects(casillas[i][j]->returnShape().getGlobalBounds())){
                                    //he chocao loco
                                    comp = true;
                                    
                                    switch(contador){
                                        case 0:
                                            gho->moveGhost(1.3,0);
                                            gho->setLastMov(sf::Vector2f(1.3,0));
                                            break;
                                        case 1:
                                            gho->moveGhost(-1.3,0);
                                            gho->setLastMov(sf::Vector2f(-1.3,0));
                                            break;
                                    } 
                                }
                            }
                        }
                    }
                    contador++;
                }
            }
            break;
        case 4:
            gho->moveGhost(1,0);
            if(!pac->getPacMode()){
                gho->setSprite(1);
                gho->setLastMove(1);
            }
            gho->setLastMov(sf::Vector2f(1,0));
            for(int i=0; i<19; i++){
                for(int j=0; j<21; j++){
            
                    int tip = casillas[i][j]->getTipo();
                    
                    if(tip != 1 && tip != 6 && tip != 7){
                        if(gho->getSGhost().getGlobalBounds().intersects(casillas[i][j]->returnShape().getGlobalBounds())){
                            //he chocao loco
                            comp = true;
                            gho->moveGhost(-1,0);
                            gho->setLastMov(sf::Vector2f(-1,0));
                        }
                    }   
                }
            }
            if(comp){
                int contador = 0;
                while(comp == true){
                    comp = false;
                    
                    switch(contador){
                        case 0:
                            gho->moveGhost(0,-1);
                            if(!pac->getPacMode()){
                                gho->setSprite(3);
                                gho->setLastMove(3);
                            }
                            gho->setLastMov(sf::Vector2f(0,-1));
                            break;
                        case 1:
                            gho->moveGhost(0,1);
                            if(!pac->getPacMode()){
                                gho->setSprite(4);
                                gho->setLastMove(4);
                            }
                            gho->setLastMov(sf::Vector2f(0,1));
                            break;
                    }
                    
                    
                    for(int i=0; i<19 && comp == false; i++){
                        for(int j=0; j<21 && comp == false; j++){

                            int tip = casillas[i][j]->getTipo();

                            if(tip != 1 && tip != 6 && tip != 7){
                                if(gho->getSGhost().getGlobalBounds().intersects(casillas[i][j]->returnShape().getGlobalBounds())){
                                    //he chocao loco
                                    comp = true;
                                    
                                    switch(contador){
                                        case 0:
                                            gho->moveGhost(0,1);
                                            gho->setLastMov(sf::Vector2f(0,1));
                                            break;
                                        case 1:
                                            gho->moveGhost(0,-1);
                                            gho->setLastMov(sf::Vector2f(0,-1));
                                            break;
                                    } 
                                }
                            }
                        }
                    }
                    contador++;
                }
            }
            break;
    }
   
}

void Mapa::updateNPCS(sf::Sprite& pacman){
    
    //Compruebo que queden cocos
    
    bool ganado = true;
    
    for(int i=0; i<19; i++){
        for(int j=0; j<21; j++){
            if(casillas[i][j]->getHidden() && casillas[i][j]->getTipo() == 1){
                ganado = false;
            }
        }
    }
    
    win = ganado;
    
    if(win){
        reloj.restart();
        reset_time.restart();
    }
    
    if(reset == false && win == false){
        
        //IA de los npc's
        
        for(int i=0; i<fantasmas.size(); i++){
            ghostAI(i, pacman);
        }

        //pasados tres segundos saco un fantasma de la "bodega" XD y lo pongo a repartir lenya
        
        if(reloj.getElapsedTime().asSeconds() >= 3.5){
            reloj.restart();
            if(!cola.empty()){
                fantasmas.push_back(cola[0]);
                //std::cout << "Sacando: " << cola[0]->getColorPos() << std::endl;
                for(int i=0; i<fantasmas.size(); i++){
                    //std::cout << "Fantasmas: " << fantasmas[i]->getColorPos() << std::endl;
                    if(i==fantasmas.size()-1){
                        fantasmas[i]->setPosision(42+352, 362);
                        if(pac->getPacMode()){
                            fantasmas[i]->setAsustados();
                        }
                    }
                }
                cola.erase(cola.begin());
                
                
            }
        }
      
        //compruebo si pacman choca con algun fantasma
    
        bool tru = false;
    
        for(int i=0; i<fantasmas.size() && !tru; i++){

            if(fantasmas[i]->getSGhost().getGlobalBounds().intersects(pacman.getGlobalBounds())){
                //compruebo si pacman tiene buffo
                if(pac->getPacMode()){
                    fantasmas[i]->setNormales();
                    if(fantasmas[i]->getColorPos()!=3){
                        fantasmas[i]->getSGhost().setPosition((42*fantasmas[i]->getColorPos())+352, 443);
                    }
                    else{
                        if(cola.size() == 3){
                            fantasmas[i]->getSGhost().setPosition((42*3)+352, 443);
                        }
                        else{
                            fantasmas[i]->getSGhost().setPosition((42*cola.size())+352, 443);
                        }
                    }
                    std::cout << cola.size() << std::endl;
                    cola.push_back(fantasmas[i]);
                    fantasmas.erase(fantasmas.begin()+i);
                    if(cola.size()==1){
                        reloj.restart();
                    }
                    puntuacion = puntuacion + 50;
                    vidaextra = vidaextra + 50;
                }
                else{
                    
                    for(int j=0; j < fantasmas.size(); j++){
                        fantasmas[j]->setLastMov(sf::Vector2f(0,0));
                        if(fantasmas[j]->getColorPos() == 3){
                            fantasmas[j]->getSGhost().setPosition(42+352, 362);  
                        }
                        else{
                            fantasmas[j]->getSGhost().setPosition((42*fantasmas[j]->getColorPos())+352, 443);
                            cola.push_back(fantasmas[j]);
                            fantasmas.erase(fantasmas.begin()+j);
                        }   
                    }
                    
                    if(fantasmas.size() > 1){
                       for(int j=0; j < fantasmas.size(); j++){
                           if(fantasmas[j]->getColorPos() != 3){
                               fantasmas[j]->getSGhost().setPosition((42*fantasmas[j]->getColorPos())+352, 443);
                                cola.push_back(fantasmas[j]);
                                fantasmas.erase(fantasmas.begin()+j);
                           }
                       } 
                    }
                    
                    pacman.setPosition(395, 686);
                    tru = true;
                    reloj.restart();

                    if(pac->vidasActuales()<=1){
                        //Reseteo del juego
                        reset = true;
                        reset_time.restart();
                        puntuacion = 0;
                        vidaextra = 0;
                    }
                    pac->muerte();
                    pac->setLastKey(0);
                    pac->setNextMove(0);
                    
                }
            }
        }
        
        //Si pacman coge buffo lo reseteo a los 4 segundos
        
        if(pac->getPacMode()){
            if(super_time.getElapsedTime().asSeconds()>=5){
                super_time.restart();
                pac->normalPac();
                for(int x=0; x<fantasmas.size(); x++){
                    fantasmas[x]->setNormales();
                }
            }
        }
        
        //Si el jugador llega a una puntuacion especifica se le suma una vida
        
        if(vidaextra >= 1600){
            vidaextra = 0;
            int new_vidas = pac->vidasActuales()+1;
            pac->setVidas(new_vidas);
        }
        
        if(!pac->getPacMode()){
            if(ghostmove.getElapsedTime().asSeconds() >= 1){
                for(int f=0; f<fantasmas.size(); f++){
                    fantasmas[f]->switchsprite();
                }
                ghostmove.restart();
            }
        }
    }
}
void Mapa::drawCasillas(sf::RenderWindow& window, sf::Sprite& spripacman){
    
    try{
        sf::Texture tex[4];
        
        for(int j=0; j<4; j++){
            tex[j].loadFromFile("pacman2.png");
        }

        int vidas = pac->vidasActuales();

        for(int i=0; i<vidas; i++){
            sf::Sprite sprit(tex[i]);           
            sprit.setOrigin(42/2,42/2);
            sprit.setTextureRect(sf::IntRect(1*42, 0, 42, 42));
            sprit.setPosition((42*i)+42, 935);
            window.draw(sprit);  
        }
        
    }catch(int e){
        std::cout << "error loading lifes sprite" << std::endl;
        exit(0);
    }
    
    //std::cout << "hola1" << std::endl;
    
    if(reset){
        for(int i=0; i<19; i++){
            for(int j=0; j<21; j++){
                if(casillas[i][j]->getTipo() == 1){
                    casillas[i][j]->setHiddenTrue();
                }
            }
        }
    }
    
    for(int i=0; i<19; i++){
        for(int j=0; j<21; j++){
            casillas[i][j]->drawCasilla(window);
        }
    }
    
    if(ghostinit == false){
        for(int i=0; i<3; i++){
            iniciarFantasmas(i);
        }
        
        //std::cout << sizeof(fantasmas)/sizeof(*fantasmas) << std::endl;
        
        Ghost * newghost = new Ghost(3);
        newghost->setPosision(42+352, 362);
        fantasmas.push_back(newghost);
        
        ghostinit = true;
    }
    else{
        if(cola.size() == 4){
            for(int i=0; i<3; i++){
                cola[i]->drawGhost(window);
            }
        }
        else{
            for(int i=0; i<cola.size(); i++){
                cola[i]->drawGhost(window);
            }
        }
        for(int i=0; i<fantasmas.size(); i++){
            fantasmas[i]->drawGhost(window);       
        }
    }
    
    sf::Font font;
    if (font.loadFromFile("ArcadeClassic.ttf"))
    {
        
        sf::Text text;
        sf::Text punt;
        sf::Text up;
        sf::Text upscore;

        text.setFont(font);
        punt.setFont(font);
        up.setFont(font);
        upscore.setFont(font);
        
        std::stringstream ss;
        ss << puntuacion;
        std::string algo = ss.str();
        
        std::stringstream ss2;
        ss2 << vidaextra;
        std::string algo2 = ss2.str();
 
        //std::cout << puntuacion << std::endl;
        text.setString("High Score");
        punt.setString(algo);
        up.setString("1UP");
        upscore.setString(algo2);
        
        text.setCharacterSize(30); 
        punt.setCharacterSize(30);
        up.setCharacterSize(30);
        upscore.setCharacterSize(30);

        text.setPosition(310,0);
        punt.setPosition(380,20);
        up.setPosition(100,0);
        upscore.setPosition(120,20); 
        
        window.draw(upscore);
        window.draw(up);
        window.draw(text);
        window.draw(punt);
        
        if(reset){
            if(reset_time.getElapsedTime().asSeconds() <= 3){
                    sf::Text reset_text;
                    reset_text.setFont(font);
                    reset_text.setString("Game Over");
                    reset_text.setCharacterSize(60);
                    reset_text.setPosition(260, 450);

                    sf::Text reset_text2;
                    reset_text2.setFont(font);
                    reset_text2.setString("Restarting  in  ");
                    
                    reset_text2.setCharacterSize(20);
                    reset_text2.setPosition(310, 510);

                    sf::Text reset_text3;
                    reset_text3.setFont(font);

                    std::stringstream ss3;
                    ss3 << reset_count;
                    std::string algo3 = ss3.str();

                    reset_text3.setString(algo3);
                    reset_text3.setCharacterSize(20);
                    reset_text3.setPosition(460, 510);

                    window.draw(reset_text);
                    window.draw(reset_text2);
                    window.draw(reset_text3);
                    
                    if(reloj.getElapsedTime().asSeconds() >= 1){
                        reset_count = reset_count-1;
                        reloj.restart();
                    }
            }
            else{
                reset_time.restart();
                pac->setVidas(3);
                reset = false;
                reset_count = 3;
                reloj.restart();
            }
        }
        else{
            if(win){
                
                pac->setLastKey(0);
                pac->setNextMove(0);
                
                sf::Text reset_text;
                reset_text.setFont(font);
                reset_text.setString("You won");
                reset_text.setCharacterSize(60);
                reset_text.setPosition(290, 450);

                sf::Text reset_text2;
                reset_text2.setFont(font);
                reset_text2.setString("Press   Q   or   ESC   to   exit");

                reset_text2.setCharacterSize(20);
                reset_text2.setPosition(270, 510);

                window.draw(reset_text);
                window.draw(reset_text2);
                
            }
        }
    }
    else{
        exit(0);
    }
 
}

bool Mapa::comprobarCasilla(sf::Sprite& sprite, sf::RenderWindow& window){
    
    bool comp = true;
    
    for(int i=0; i<19 && comp!=false; i++){
        for(int j=0; j<21 && comp!=false; j++){
            
            int tip = casillas[i][j]->getTipo();
            
            if(tip == 2){
                if(sprite.getGlobalBounds().intersects(casillas[i][j]->returnShape().getGlobalBounds())){
                    //std::cout << "colision" << std::endl;
                    if(pac->getNextMove()!=0){
                        reloj2.restart();
                        switch(pac->getLastKey()){
                            case 1:
                                sprite.move(-pac->getVelocidad(),0);
                                break;
                            case 2:
                                sprite.move(pac->getVelocidad(),0);  
                                break;
                            case 3:
                                sprite.move(0, pac->getVelocidad());
                                break;
                            case 4:
                                sprite.move(0,-pac->getVelocidad());
                                break;
                        }
                        pac->setLastKey(pac->getNextMove());
                        pac->setNextMove(0);
                    }else{
                        comp = false;
                    }
                }
            }
            else{
                if(tip == 1){
                    if(sprite.getGlobalBounds().intersects(casillas[i][j]->returnShape().getGlobalBounds())){
                        if(casillas[i][j]->getHidden()){
                            casillas[i][j]->setHidden(window);
                            puntuacion = puntuacion + 10;
                            vidaextra = vidaextra + 10;
                        }
                        if(pac->getNextMove()!=0 && pac->getNextMove() != pac->getLastKey() && reloj2.getElapsedTime().asSeconds() >= 0.01){
                            reloj2.restart();
                            bool intento = false;
                            for(int h=0; h<4 && intento == false; h++){
                                switch(pac->getNextMove()){
                                    case 1:
                                        sprite.move(2,0);
                                        break;
                                    case 2:
                                        sprite.move(-2,0);
                                        break;
                                    case 3:
                                        sprite.move(0,-2);
                                        break;
                                    case 4:
                                        sprite.move(0,2);
                                        break;
                                }
                                bool aux2 = false;
                                for(int k=0; k<19 && aux2 == false; k++){
                                    for(int u=0; u<21 && aux2 == false; u++){

                                        int tip2 = casillas[k][u]->getTipo();

                                        if(tip2 != 1 && tip2 != 6 && tip2 != 7){
                                            if(sprite.getGlobalBounds().intersects(casillas[k][u]->returnShape().getGlobalBounds())){
                                                switch(pac->getNextMove()){
                                                    case 1:
                                                        sprite.move(-2,0);
                                                        break;
                                                    case 2:
                                                        sprite.move(2,0);
                                                        break;
                                                    case 3:
                                                        sprite.move(0,2);
                                                        break;
                                                    case 4:
                                                        sprite.move(0,-2);
                                                        break;
                                                }
                                                aux2 = true;
                                                intento = true;
                                            }   
                                        }   
                                    }
                                } 
                            }
                      
                            if(intento == false){
                                pac->setLastKey(pac->getNextMove());
                                pac->setNextMove(0);
                            }
                        }
                    }
                }
                else{
                    if(tip == 7){
                        //std::cout << "existo" << std::endl;
                        if(sprite.getGlobalBounds().intersects(casillas[i][j]->returnCircleShape().getGlobalBounds())){
                            //std::cout << "colision" << std::endl;
                            if(casillas[i][j]->getHidden()){
                                casillas[i][j]->setHidden(window);
                                pac->superPac();
                                super_time.restart();
                                for(int x=0; x<fantasmas.size(); x++){
                                    fantasmas[x]->setAsustados();
                                }
                            }
                            if(pac->getNextMove()!=0 && pac->getNextMove() != pac->getLastKey() && reloj2.getElapsedTime().asSeconds() >= 0.01){
                                reloj2.restart();
                                bool intento = false;
                                for(int h=0; h<4 && intento == false; h++){
                                    switch(pac->getNextMove()){
                                        case 1:
                                            sprite.move(2,0);
                                            break;
                                        case 2:
                                            sprite.move(-2,0);
                                            break;
                                        case 3:
                                            sprite.move(0,-2);
                                            break;
                                        case 4:
                                            sprite.move(0,2);
                                            break;
                                    }
                                    bool aux2 = false;
                                    for(int k=0; k<19 && aux2 == false; k++){
                                        for(int u=0; u<21 && aux2 == false; u++){

                                            int tip2 = casillas[k][u]->getTipo();

                                            if(tip2 != 1 && tip2 != 6 && tip2 != 7){
                                                if(sprite.getGlobalBounds().intersects(casillas[k][u]->returnShape().getGlobalBounds())){
                                                    switch(pac->getNextMove()){
                                                        case 1:
                                                            sprite.move(-2,0);
                                                            break;
                                                        case 2:
                                                            sprite.move(2,0);
                                                            break;
                                                        case 3:
                                                            sprite.move(0,2);
                                                            break;
                                                        case 4:
                                                            sprite.move(0,-2);
                                                            break;
                                                    }
                                                    aux2 = true;
                                                    intento = true;
                                                }   
                                            }   
                                        }
                                    } 
                                }

                                if(intento == false){
                                    pac->setLastKey(pac->getNextMove());
                                    pac->setNextMove(0);
                                }
                            }
                        }
                    }
                    else{
                        if(tip == 6){
                            if(pac->getNextMove()!=0 && pac->getNextMove() != pac->getLastKey() && reloj2.getElapsedTime().asSeconds() >= 0.01){
                                reloj2.restart();
                                bool intento = false;
                                for(int h=0; h<4 && intento == false; h++){
                                    switch(pac->getNextMove()){
                                        case 1:
                                            sprite.move(2,0);
                                            break;
                                        case 2:
                                            sprite.move(-2,0);
                                            break;
                                        case 3:
                                            sprite.move(0,-2);
                                            break;
                                        case 4:
                                            sprite.move(0,2);
                                            break;
                                    }
                                    bool aux2 = false;
                                    for(int k=0; k<19 && aux2 == false; k++){
                                        for(int u=0; u<21 && aux2 == false; u++){

                                            int tip2 = casillas[k][u]->getTipo();

                                            if(tip2 != 1 && tip2 != 6 && tip2 != 7){
                                                if(sprite.getGlobalBounds().intersects(casillas[k][u]->returnShape().getGlobalBounds())){
                                                    switch(pac->getNextMove()){
                                                        case 1:
                                                            sprite.move(-2,0);
                                                            break;
                                                        case 2:
                                                            sprite.move(2,0);
                                                            break;
                                                        case 3:
                                                            sprite.move(0,2);
                                                            break;
                                                        case 4:
                                                            sprite.move(0,-2);
                                                            break;
                                                    }
                                                    aux2 = true;
                                                    intento = true;
                                                }   
                                            }   
                                        }
                                    } 
                                }

                                if(intento == false){
                                    pac->setLastKey(pac->getNextMove());
                                    pac->setNextMove(0);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return comp;
}

void Mapa::choque(sf::Sprite& sprite){
    pac->setMovimiento(false);
    switch(pac->getLastKey()){
        case 1:
            if(pac->getPacMode()){
                sprite.move(-3,0); 
            }else{
                sprite.move(-2,0);
            }
            pac->setLastKey(0);
            break;
        case 2:
            if(pac->getPacMode()){
                sprite.move(3,0); 
            }else{
                sprite.move(2,0);
            }
            pac->setLastKey(0);
            break;
        case 3:
            if(pac->getPacMode()){
                sprite.move(0,3); 
            }else{
                sprite.move(0, 2);
            }
            pac->setLastKey(0);
            break;
        case 4:
            if(pac->getPacMode()){
                sprite.move(0,-3); 
            }else{
                sprite.move(0,-2);
            }
            pac->setLastKey(0);
            break;
    }
}