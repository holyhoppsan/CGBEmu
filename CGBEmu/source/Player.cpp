#include "Player.h"
#include <iostream>

Player::Player()
{

}

Player::~Player()
{
	
}

void Player::set_values() {

	std::cout << "Please enter width: ";
	std::cin >> width;
	std::cout << "Please enter height: ";
	std::cin >> height;
	std::cout << "area:"<< width*height;
}

int Player::area() const
{ 
	return width*height; 
}