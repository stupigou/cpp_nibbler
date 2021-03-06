//
// Snake.cpp for nibbler in /home/tran_0/rendu/cpp_nibbler/src
//
// Made by David Tran
// Login   <tran_0@epitech.net>
//
// Started on  Fri Mar 27 00:10:35 2015 David Tran
// Last update Sun Apr  5 22:24:03 2015 Jean-Baptiste Grégoire
//

#include "Snake.hpp"

Snake::Snake(int maxX, int maxY) : direction(WEST), nbPoints(0)
{
  int						i;
  std::vector<std::pair<double, double> *>	snak;

  i = 0;
  while (i < 4)
    {
      std::pair<double, double>	*coor = new std::pair<double, double>;
      coor->first = maxX / 2 - 2 + i;
      coor->second = maxY / 2;
      snak.push_back(coor);
      i++;
    }
  snake = snak;
}

void	Snake::turnLeft()
{
  direction = (Way)((direction + 1) % 4);
}

void	Snake::turnRight()
{
  direction = (Way)((direction - 1) >= 0 ? direction - 1 : 3);
}

void	Snake::moveAhead()
{
  std::vector<std::pair<double, double> *>::iterator	it = snake.begin();
  std::pair<double, double>				*coor = new std::pair<double, double>;
  std::pair<double, double>				*last = new std::pair<double, double>;

  coor->first = (*it)->first;
  coor->second = (*it)->second;
  it++;
  while (it != snake.end())
    {
      last->first = (*it)->first;
      last->second = (*it)->second;
      (*it)->first = coor->first;
      (*it)->second = coor->second;
      coor->first = last->first;
      coor->second = last->second;
      it++;
    }
  it = snake.begin();
  if (direction == NORTH)
    (*it)->second -= 1;
  else if (direction == WEST)
    (*it)->first -= 1;
  else if (direction == SOUTH)
    (*it)->second += 1;
  else
    (*it)->first += 1;
}

void	Snake::isAlive(int maxX, int maxY) const
{
  std::vector<std::pair<double, double> *>::const_iterator	it = snake.begin();
  std::pair<double, double>				*first;

  if ((*it)->first < 0 || (*it)->first >= maxX || (*it)->second < 0 || (*it)->second >= maxY)
    throw Nibbler_Error_Lib("Snake ate the wall.. Exiting");
  first = *it;
  it++;
  while (it < snake.end())
    {
      if (first->first == (*it)->first && first->second == (*it)->second)
	throw Nibbler_Error_Lib("Snake ate himself.. Exiting");
      it++;
    }
}

Way	Snake::getDirection() const
{
  return (direction);
}

void	Snake::addQueue()
{
  std::pair<double, double>		*add = new std::pair<double, double>;
  std::vector<std::pair<double, double> *>::iterator	it;

  it = snake.end() - 1;
  add->first = (*it)->first;
  add->second = (*it)->second;
  snake.push_back(add);
}

Snake::~Snake()
{}
