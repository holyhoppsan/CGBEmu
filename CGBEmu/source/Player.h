#pragma once

#include <iostream>

class Player
{
public:
	Player();//default constructor
	Player(int x, int y, int w, int h);//additional constructor
	~Player();
	void set_values();
	int get_x();
	int get_y();
	int get_width();
	int get_height();
	void move_left();
	void move_right();
	void move_up();
	void move_down();
	void set_coordinates();

private:
	int width;
	int height;
	int pos_x;
	int pos_y;
};