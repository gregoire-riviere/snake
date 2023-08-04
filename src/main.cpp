#include <SFML/Graphics.hpp>
#include "../hd/game_hdlr.hpp"
#include "../hd/constantes.hpp"
#include <iostream>

int main()
{
    sf::Font font;
    if(!font.loadFromFile("FreeSerif.ttf"))
    	std::cout << "probleme" << std::endl;
    sf::Text text;
    text.setFont(font); // font est un sf::Font
    text.setString("Perdu!");
    text.setCharacterSize(35);
    text.setColor(sf::Color::Blue);
    text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(WIND_SZ/2-17, WIND_SZ/2-40));
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(WIND_SZ, WIND_SZ), "Snake");
    Game_hdlr game(&window);
    game.affichage();
    bool go = false, restart = true;
    sf::Clock horloge;
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type){
            	case sf::Event::Closed:
                	window.close();
                	break;
                case (sf::Event::KeyPressed):
         		if(event.key.code == sf::Keyboard::Left){
         			game.chgt_dir(LEFT);
         			go = true;
         		}
         		if(event.key.code == sf::Keyboard::Up){
         			game.chgt_dir(UP);
         			go = true;
         		}
         		if(event.key.code == sf::Keyboard::Down){
         			game.chgt_dir(DOWN);
         			go = true;
         		}
         		if(event.key.code == sf::Keyboard::Right){
         			game.chgt_dir(RIGHT);
         			go = true;
         		}
         		if(event.key.code == sf::Keyboard::R && !restart){
         			restart = true;
         			game.init();
         			game.affichage();
         			horloge.restart();
         			go = false;
         		}
         		break;
            }
        }
        if(horloge.getElapsedTime().asMilliseconds() >= 200 && go && restart){
        	if(!game.iteration()){
        		restart = false;
        		window.clear(sf::Color::Black);
    			window.draw(text);
        	}
        	horloge.restart();
        }
        window.display();
    }
    return 0;
}
