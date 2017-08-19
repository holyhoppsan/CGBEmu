#include <iostream>
#include "Player.h"


int main() {
	Player user;
	user.set_values();
	std::cout << "area: " << user.area;
	return 0;
}