

#include "Ball.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

#include "Globals.h"
#include "Player.h"
#include "Screen.h"
#include "io.h"

using namespace std;

Ball::Ball() {
  x = 0;
  y = 0;
  velocity_x = 0;
  velocity_y = 0;
  width = 1;
  height = 1;
  id = 0;
}

Ball::Ball(double x, double y, double velocity_x, double velocity_y, int id) {
  this->x = x;
  this->y = y;
  width = 1;
  height = 1;
  this->velocity_x = velocity_x;
  this->velocity_y = velocity_y;
  this->id = id;
}

int Ball::getID() { return id; }

double Ball::getX() { return x; }

void Ball::update() {
  velocity_y = velocity_y - 0.02 * timeStep;
  x += velocity_x * timeStep;
  y += velocity_y * timeStep;
}

int Ball::overlap(Ball& b) {
  if ((x + width <= b.x) || (y + height <= b.y) || (b.x + b.width <= x) ||
      (b.y + b.height <= y))
    return NO_OVERLAP;

  double overlapX = min(x + width, b.x + width) - max(x, b.x);
  double overlapY = min(y + height, b.y + height) - max(y, b.y);

  if (overlapX > overlapY)
    return VERTICAL_OVERLAP;
  else
    return HORIZONTAL_OVERLAP;
}

int Ball::overlap(Player& p) {
  if ((p.getX() + p.getWidth() < x) || (p.getY() + p.getHeight() < y) ||
      (y < p.getY()))
    return NO_OVERLAP;

  double overlapX = min(x + width, p.getX() + p.getWidth()) - max(x, p.getX());
  double overlapY = min(y + height, p.getY() + height) - max(y, p.getY());

  if (overlapX > overlapY)
    return VERTICAL_OVERLAP;
  else
    return HORIZONTAL_OVERLAP;
}

void Ball::bounce(Ball arr[], int ballCount, Player player) {
  // Ball colliding with player
  int playerCollide = overlap(player);
  if (playerCollide == HORIZONTAL_OVERLAP) {
    velocity_y *= -1;
  } else if (playerCollide == VERTICAL_OVERLAP) {
    velocity_x *= -1;
  }

  // Ball colliding with wall
  if ((x >= WIDTH - 1)) {
    velocity_x = -1 * abs(velocity_x);
  }
  if ((y >= HEIGHT - 1)) {
    velocity_y = -1 * abs(velocity_y);
  }
  if (y <= 0) {
    velocity_y = abs(velocity_y);
  }
}

void Ball::draw(Screen& screen_to_draw_to) {
  screen_to_draw_to.addPixel(x, y, 'o');
}