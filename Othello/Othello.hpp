/*
 * Othello.hpp
 *
 *  Created on: Sep 15, 2020
 *      Author: Ryan Allarey
 */

#ifndef OTHELLO_HPP_
#define OTHELLO_HPP_
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "Player.hpp"

using namespace std;

class Othello {
		char board[8][8];
		int boardsize = 8;
		Player player1;
		Player player2;
		int numplayer;

	public:
		Othello();
		Othello(string, char);
		Othello(string, char, string, char);
		void makemat();
		void printmat();
		void placepiece(Player);
		int countandflippieces(int, int, Player, bool);
		void ckwin();
		void compplacepiece(Player);
		void playGame();



}; //Othello header



#endif /* OTHELLO_HPP_ */
