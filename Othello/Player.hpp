/*
 * Player.hpp
 *
 *  Created on: Sep 15, 2020
 *      Author: Ryan Allarey
 */

#ifndef PLAYER_HPP_
#define PLAYER_HPP_
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

class Player {
		friend class Othello;
		string name;
		char piece;
	public:
		Player();
		Player(string, char);
}; //Player header

#endif /* PLAYER_HPP_ */
