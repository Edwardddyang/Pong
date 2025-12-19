
#include "Player.h"

#include <iostream>
#include <string>

#include "Ball.h"
#include "Globals.h"
#include "Screen.h"
#include "io.h"

using namespace std;

Player::Player() {
  x = 0;
  y = 0;
  height = 3;
  width = 3;
}

Player::Player(double x, double y, int height) {
  this->x = x;
  this->y = y;
  this->height = height;
  width = 1;
}

double Player::getX() { return x; }

double Player::getY() { return y; }

int Player::getHeight() { return height; }

int Player::getWidth() { return width; }

void Player::decreaseHeight(int delta_to_decrease_by) {
  if (height - delta_to_decrease_by > 3) {
    height -= delta_to_decrease_by;
  } else
    height = 3;
}

void Player::update(char c) {
  if (c == 'A') {
    if (y + height + 2 >= HEIGHT - 1)
      y = HEIGHT - height;
    else
      y += 2;
  } else if (c == 'B') {
    if (y - 2 < 0)
      y = 0;
    else
      y -= 2;
  }
}

void Player::draw(Screen& screen_to_draw_to) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      screen_to_draw_to.addPixel(x + j, y + i, '#');
    }
  }
}
