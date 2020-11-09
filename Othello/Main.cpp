/*
 * Main.cpp
 *
 *  Created on: Sep 15, 2020
 *      Author: Ryan Allarey
 */

/* *************************************************************************
and code for the main function, which should be in its own file with a .cpp
extension, located in the same project folder as your Othello Class and your Player
Class files
****************************************************************************/
#include <iostream>
#include <stdlib.h>
#include "Othello.hpp"
#include "Player.hpp"
#include <time.h>
#include <string.h>

using namespace std;

int main() {
	srand(time(NULL));
	Othello game("b1",'B',"s1",'O');
	Othello game2("b1",'B');
	Othello game3;
	game2.playGame();
}



