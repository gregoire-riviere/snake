#include "../hd/snake.hpp"
#include "../hd/constantes.hpp"
#include <iostream>
#include <iterator>


Snake::Snake(int x, int y){
	snake_text = new sf::Texture();
	sf::Sprite s1;
	s1.setPosition(x, y);
	sf::Sprite s2;
	s2.setPosition(x, y);
	if(!snake_text->loadFromFile("img/image_snake.jpg")){
		std::cout << "Erreur de chargement des textures (snake)" << std::endl;
		s1.setColor(sf::Color(100, 250, 50));
		s2.setColor(sf::Color(100, 250, 50));
	}
	else{
		s1.setTexture(*snake_text);
		s2.setTexture(*snake_text);
	}
	s1.setTextureRect(sf::IntRect(10, 10, PART_SZ, PART_SZ));
	s2.setTextureRect(sf::IntRect(10, 10, PART_SZ, PART_SZ));
	file.push_back(s1);
	file.push_back(s2);
}

Snake::~Snake(){
	delete snake_text;
}

void Snake::affichage(sf::RenderWindow* w){
	std::deque<sf::Sprite>::iterator it;
	for(it = file.begin(); it!= file.end(); it++)
		w->draw(*it);
}

Retour Snake::moove(Dir direction, int fd_x, int fd_y){
	//On retient la position qu'aura le nouveau
	sf::Sprite s;
	int posx = file[file.size()-1].getPosition().x;
	int posy = file[file.size()-1].getPosition().y;
	switch(direction){
		case RIGHT:
			posx += PART_SZ;
		break;
		case LEFT:
			posx -= PART_SZ;
		break;
		case UP:
			posy -= PART_SZ;
		break;
		case DOWN:
			posy += PART_SZ;
		break;
	}
	
	//On teste s'il sort de l'écran
	if(posx >= WIND_SZ || posy >= WIND_SZ || posx < 0 || posy < 0 || !check_position(posx, posy))
		return FIN;
		
	bool ajout = (posx == fd_x && posy == fd_y);
	//Le premier devient le dernier
	if(!ajout){
		s = file[0];
		file.pop_front();
	}
	else{
		s.setTexture(*snake_text);
		s.setTextureRect(sf::IntRect(10, 10, PART_SZ, PART_SZ));
	}
	s.setPosition(sf::Vector2f(posx, posy));
	file.push_back(s);
	if(!ajout)
		return OK;
	else
		return FOOD;
}

bool Snake::check_position(int x, int y){
	bool retour = true;
	std::deque<sf::Sprite>::iterator it;
	for(it = file.begin(); it!= file.end(); it++)
		retour &= (it->getPosition().x != x || it->getPosition().y != y);
	return retour;

}

