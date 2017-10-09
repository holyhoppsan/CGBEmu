#include "Player.h"
#include <iostream>

Player::Player()
	:pos_x(0)
	, pos_y(0)
{

}

Player::Player(int x, int y, int w,int h)
	: pos_x(x)
	, pos_y(y)
	, width(w)
	, height(h)
{

}

Player::~Player()
{

}
int Player::get_x() {
	return pos_x;
}
int Player::get_y() {
	return pos_y;
}
int Player::get_width() {
	return width;
}
int Player::get_height() {
	return height;
}
void Player::move_left() {
	pos_x--;
	if (pos_x < 0) {
		pos_x = 0;
	}
}
void Player::move_right() {
	pos_x++;
}
void Player::move_up() {
	pos_y--;
	if (pos_y < 0) {
		pos_y = 0;
	}
}
void Player::move_down() {
	pos_y++;
}
void Player::set_values() {

	std::cout << "Please enter width: ";
	std::cin >> width;
	std::cout << "Please enter height: ";
	std::cin >> height;
	std::cout << "area: " << width*height << std::endl;
}
void Player::set_coordinates() {

	std::cout << "Please enter coordinate x: ";
	std::cin >> pos_x;
	std::cout << "Coordinate x: " << pos_x << std::endl;
	std::cout << "Please enter coordinate y: ";
	std::cin >> pos_y;
	std::cout << "Coordinate y: " << pos_y << std::endl;
}