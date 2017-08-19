#include <iostream>
class Player
{
	int width;
	int height;
public:
	Player();
	~Player();
	void set_values();
	int area() { return width*height; }
};

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