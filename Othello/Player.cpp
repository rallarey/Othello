/*
 * Player.cpp
 *
 *  Created on: Sep 15, 2020
 *      Author: Ryan Allarey
 */
#include "Player.hpp"
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

Player::Player(){
	name = 'computer';
	int x = rand()%1;
	if (x == 0){
		piece = 'O';
	} else {
		piece = 'B';
	}
}

Player::Player(string Name, char Piece){
	name = Name;
	piece = Piece;
}



