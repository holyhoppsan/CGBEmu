#include <iostream>
class Player
{
public:
	Player();
	~Player();

	void set_values();
	int area() const;

private:
	int width;
	int height;
};