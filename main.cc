#include <iostream>
#include <SFML/Graphics.hpp>

#include "Mapa.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(795, 970), "P0. Fundamentos de los Videojuegos. DCCIA");
    sf::Int16 lastkey = 0;

    sf::Texture tex;
    if (!tex.loadFromFile("pacman2.png"))
    {
        std::cerr << "Error cargando la imagen pacman2.png";
        exit(0);
    }
    
    sf::Sprite sprite(tex);
    sprite.setOrigin(42/2,42/2);
    sprite.setTextureRect(sf::IntRect(1*42, 0, 42, 42));
    
    sprite.setPosition(395, 686);
    
    window.setFramerateLimit(60);
    
    Mapa map; //el mapa contiene todo (pacman, fantasmas, puntos, casillas...)
       
    //Bucle del juego
    while (window.isOpen())
    {
        //Bucle de obtención de eventos
        sf::Event event;
        while (window.pollEvent(event))
        {         
            switch(event.type){
                
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window.close();
                    break;
                //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    //Verifico si se pulsa alguna tecla de movimiento
                    map.panelControl(event, sprite, window);           
                break;
            }         
        }
        
        if(map.comprobarCasilla(sprite, window)){
            map.movLast(sprite, window);
        }
        else{
            map.choque(sprite);
        }
        
        map.updateNPCS(sprite);
        
        window.clear();
        map.drawCasillas(window, sprite);
        window.draw(sprite);
        window.display();
    }

    return 0;
}