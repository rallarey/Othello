/*
 * Othello.cpp
 *
 *  Created on: Sep 15, 2020
 *      Author: Ryan Allarey
 */
#include "Othello.hpp"
#include "Player.hpp"
#include <string.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

Othello::Othello(){
	player1 = Player();
	player2 = Player();
	if(player2.piece == player1.piece){
		if (player2.piece == 'B'){
				player1.piece = 'O';
			} else if (player2.piece == 'O'){
				player1.piece = 'B';
		}
	}
	numplayer = 0;
}

Othello::Othello(string Name, char Piece){
	player1 = Player(Name, Piece);
	player2 = Player();
	if (Piece == player2.piece){
		if (Piece == 'B'){
			player2.piece = 'O';
		} else if (Piece == 'O'){
			player2.piece = 'B';
		}
	}
	numplayer = 1;
}

Othello::Othello(string Name1, char Piece1, string Name2, char Piece2){
	player1 = Player(Name1, Piece1);
	player2 = Player(Name2, Piece2);
	if(Piece1 == Piece2){
		if (Piece1 == 'B'){
				Piece2 = 'O';
			} else if (Piece1 == 'O'){
				Piece2 = 'B';
		}
	}
	numplayer = 2;
}

void Othello::makemat(){
	for (int i = 0; i < boardsize; i++){
		for (int x = 0; x < boardsize; x++){
			if(((i==3) && (x==3)) || ((i==4) && (x==4))){
				board[i][x] = 'B';
			} else if (((i==3) && (x==4)) || ((i==4) && (x==3))){
				board[i][x] = 'O';
			} else {
				board[i][x] = '_';
			}
		}
	}
//	printmat();
}

void Othello::printmat(){
/*
	char testboard[3][3];
	for(int i = 0; i < 3; i++){
		for(int z = 0; z < 3; z++){
			testboard[i][z] = '_';
		}
	}
*/

	for (int z = 0; z < boardsize; z++){
		if (z == (boardsize -1)){
			cout<<'	'<< z << endl;
		} else {
			cout<<'	'<< z;
		}
	}
	for (int i = 0; i != boardsize; i++){
		cout << i <<'	';
		for (int x = 0; x != boardsize ; x++){
			if (x == (boardsize -1)){
				cout << board[i][x] << endl;
			} else {
				cout << board[i][x]	<<'	';
			}
		}
	}
	cout << endl;
//	ckwin();
}

void Othello::placepiece(Player p){
	int x;
	int y;
	bool flip = true;
	cout<<"enter the x coordinate on the board: ";
	cin >> x;
	cout<<"enter the y coordinate on the board: ";
	cin >> y;
	if ((x < 0 || x > 7) || (y < 0 || y > 7)) {
		cout<<"invalid coordinates"<<endl;
		placepiece(p);
	}
	if (board[x][y] != '_'){
		cout<<"there is already a piece there"<<endl;
		placepiece(p);
	}
	board[x][y] = p.piece;

	// x,y order is down then right
	// y,x order is right then down

	if (countandflippieces(x, y, p, flip) == 0){
		cout<<"Player forfeits turn"<<endl;
			board[x][y] = '_';
	}
}

int Othello::countandflippieces(int x, int y, Player player, bool flip){
	int count = 0;
	int tempX;
	int tempY;
	char oppositePiece;

	if(player.piece == 'B'){
		oppositePiece = 'O';
	} else {
		oppositePiece = 'B';
	}
	// Left check
	if (y != 0 && board[x][y-1] == oppositePiece){
		tempY = y - 1;
		// creating a temporary variable that is 1 to the left of the current y value
		while (tempY >= 0){
			if(board[x][tempY] == player.piece){
				// if this coordinate on the board has your current piece, do the loop below.
				for(int i = tempY; i < y; i++){
					// all values from tempY to Y, change all values in the board to the current players piece
					if (flip == true){
						board[x][i] = player.piece;
					}
					// increment count (the total flipped pieces)
					count++;
				}
				// break the loop
				break;
			}
			if (board[x][tempY] == '_'){
				// if the board spot next to the currently placed piece is empty, break the loop
				break;
			}
			if (board[x][tempY] == oppositePiece){
				// if this position is filled with the opposite piece, decrement the y and restart the loop
				tempY -= 1;
			}
		}
		// same logic applied to all directions
	}
	// Right check
	if (y != (boardsize -1) && board[x][y+1] == oppositePiece) {
		tempY = y + 1;
		while (tempY < boardsize){
			if (board[x][tempY] == player.piece){
				for (int i = tempY; i > y; i--){
					if(flip == true){
						board[x][i] = player.piece;
					}
					count++;
				}
				break;
			}
			if (board[x][tempY] == '_'){
				break;
			}
			if (board[x][tempY] == oppositePiece){
				tempY += 1;
			}
		}
	}
	// Up check
	if (x != 0 && board[x-1][y] == oppositePiece){
		tempX = x - 1;
		while(tempX >= 0){
			if (board[tempX][y] == player.piece){
				for(int i = tempX; i < x; i++){
					if(flip == true){
						board[i][y] = player.piece;
					}
					count++;
				}
				break;
			}
			if (board[tempX][y] == '_'){
				break;
			}
			if (board[tempX][y] == oppositePiece){
				tempX -= 1;
			}
		}
	}
	// Down check
	if (x != (boardsize-1) && board[x+1][y] == oppositePiece){
		tempX = x + 1;
		while (tempX < boardsize){
			if (board[tempX][y] == player.piece){
				for (int i = tempX; i > x; i--){
					if (flip == true){
						board[i][y] = player.piece;
					}
					count++;
				}
				break;
			}
			if (board[tempX][y] == '_'){
				break;
			}
			if (board[tempX][y] == oppositePiece){
				tempX += 1;
			}
		}
	}
	// UpLeft check
	if (x != 0 && y != 0 && board[x-1][y-1] == oppositePiece){
		tempX = x-1;
		tempY = y-1;
		while (tempX >= 0 && tempY >= 0){
			if (board[tempX][tempY] == player.piece){
				int z = tempY;
				for (int i = tempX; i < x && z < y; i++, z++){
					if (flip == true){
						board[i][z] = player.piece;
					}
					count++;
				}
				break;
			}
			if (board[tempX][tempY] == '_'){
				break;
			}
			if (board[tempX][tempY] == oppositePiece){
				tempX -= 1;
				tempY -= 1;
			}
		}
	}
	// UpRight check
	if (x != 0 && y != (boardsize-1) && board[x-1][y+1] == oppositePiece){
		tempX = x-1;
		tempY = y+1;
		while(tempX >= 0 && tempY < boardsize){
			if (board[tempX][tempY] == player.piece){
				int z = tempY;
				for (int i= tempX; i < x && z > y; i++, z--){
					if (flip == true){
						board[i][z] = player.piece;
					}
					count++;
				}
				break;
			}
			if (board[tempX][tempY] == '_'){
				break;
			}
			if (board[tempX][tempY] == oppositePiece){
				tempX -= 1;
				tempY += 1;
			}
		}
	}
	// DownLeft check
	if (x != (boardsize - 1) && y != 0 && board[x+1][y-1] == oppositePiece){
		tempX = x + 1;
		tempY = y - 1;
		while (tempX < boardsize && tempY >= 0){
			if (board[tempX][tempY] == player.piece){
				int z = tempY;
				for(int i = tempX; i > x && z < y; i--, z++){
					if (flip == true){
						board[i][z] = player.piece;
					}
					count++;
				}
				break;
			}
			if (board[tempX][tempY] == '_'){
				break;
			}
			if (board[tempX][tempY] == oppositePiece){
				tempX += 1;
				tempY -= 1;
			}
		}
	}
	// DownRight check
	if (x != (boardsize-1) && y != (boardsize-1) && board[x+1][y+1] == oppositePiece){
		tempX = x + 1;
		tempY = y + 1;
		while (tempX < boardsize && tempY < boardsize){
			if (board[tempX][tempY] == player.piece){
				int z = tempY;
				for (int i = tempX; i > x && z > y; i--, z--){
					if (flip == true){
						board[i][z] = player.piece;
					}
					count++;
				}
				break;
			}
			if (board[tempX][tempY] == '_'){
				break;
			}
			if (board[tempX][tempY] == oppositePiece){
				tempX += 1;
				tempY += 1;
			}
		}
	}

// the code below was complicated, and didn't work
/*	int x = current_x + 1;
	int y = current_y + 1;
	int left_x = current_x - 1;
	int up_y = current_y - 1;
	bool flip = false;
	// right check
	for(x; x < boardsize && board[x][current_y] != '_'; x++){
		if(board[x][current_y] != player.piece){
			flip = true;
		} else if (board[x][current_y] == player.piece){
			if(flip == false){
				break;
			} else if(flip == true){
				for(x; x < current_x; x--){
					if(player.piece == 'B'){
						board[x][current_y] = 'O';
						count = count + 1;
						flip = false;
					} else if (player.piece == 'O'){
						board[x][current_y] = 'B';
						count = count + 1;
						flip = false;
					}
				}
				break;
			}
		}
	}
	// left check
	for(left_x; left_x > 0 && board[left_x][current_y] != '_'; x--){
		if (board[left_x][current_y] != player.piece){
			flip = true;
		} else if (board[left_x][current_y] == player.piece){
			if (flip == false){
				break;
			} else if (flip == true){
				for(left_x; left_x > current_x; left_x++){
					if(player.piece == 'B'){
						board[left_x][current_y] = 'O';
						count = count + 1;
						flip = false;
					} else if(player.piece == 'O'){
						board[left_x][current_y] = 'B';
						count = count + 1;
						flip = false;
					}
				}
				break;
			}
		}
	}
	// down check
	for(y; y < boardsize && board[current_x][y] != '_'; y++){
		if (board[current_x][y] != player.piece){
			flip = true;
		} else if (board[current_x][y] == player.piece){
			if (flip == false){
				break;
			} else if (flip == true){
				for(y; y < current_y; y--){
					if(player.piece == 'B'){
						board[current_x][y] = 'O';
						count = count + 1;
						flip = false;
					} else if (player.piece == 'O'){
						board[current_x][y] = 'B';
						count = count + 1;
						flip = false;
					}
				}
				break;
			}
		}
	}
	// up check
	for (up_y; up_y > 0 && board[current_x][up_y] != '_'; up_y--){
		if (board[current_x][up_y] != player.piece){
			flip = true;
		} else if (board[current_x][up_y] == player.piece){
			if (flip == false){
				break;
			} else if (flip == true){
				for(up_y; up_y > current_y; up_y++){
					if(player.piece == 'B'){
						board[current_x][up_y] = 'O';
						count = count + 1;
						flip = false;
					} else if (player.piece == 'O'){
						board[current_x][up_y] = 'B';
						count = count + 1;
						flip = false;
					}
				}
				break;
			}
		}
	}
	// bottom right diagonal check (south-east)
	for(x; x < boardsize; x++){
		for(y; y < boardsize && board[x][y] != '_'; y++){
			if (board[x][y] != player.piece){
				flip = true;
			} else if (board[x][y] == player.piece){
				if (flip == false){
					break;
				} else if (flip == true){
					for(x; x < current_x; x--){
						for(y; y < current_y; y--){
							if(player.piece == 'B'){
								board[x][y] = 'O';
								count = count + 1;
								flip = false;
							} else if (player.piece == 'O'){
								board[x][y] = 'B';
								count = count + 1;
								flip = false;
							}
						}
					}
					break;
				}
			}
		}
	}
	// top right diagonal check (north-east)
	for(x; x < boardsize; x++){
		for(up_y; up_y > 0 && board[x][up_y] != '_'; up_y--){
			if (board[x][up_y] != player.piece){
				flip = true;
			} else if (board[x][up_y] == player.piece){
				if(flip == false){
					break;
				} else if(flip == true){
					for(x; x < current_x; x--){
						for(up_y; y > current_y; up_y++){
							if(player.piece == 'B'){
								board[x][up_y] = 'O';
								count = count + 1;
								flip = false;
							} else if (player.piece == 'O'){
								board[x][up_y]= 'B';
								count = count + 1;
								flip = false;
							}
						}
					}
					break;
				}
			}
		}
	}
	// bottom left diagonal check (south west)
	for(left_x; left_x > 0; left_x--){
		for (y; y < boardsize && board[left_x][y] != '_'; y++){
			if (board[left_x][y] != player.piece){
				flip = true;
			} else if (board[left_x][y] == player.piece){
				if(flip == false){
					break;
				} else if (flip == true){
					for(left_x; left_x > current_x; left_x++){
						for(y; y < current_y; y--){
							if(player.piece == 'B'){
								board[left_x][y] = 'O';
								count = count + 1;
								flip = false;
							} else if (player.piece == 'O'){
								board[left_x][y] = 'B';
								count = count + 1;
								flip = false;
							}
						}
					}
					break;
				}
			}
		}
	}
	// top left diagonal check (north west)
	for (left_x; left_x > 0; left_x--){
		for (up_y; up_y > 0 && board[left_x][up_y] != '_'; up_y--){
			if (board[left_x][up_y] != player.piece){
				flip = true;
			} else if (board[left_x][up_y] == player.piece){
				if(flip == false){
					break;
				} else if (flip== true){
					for(left_x; left_x > current_x; left_x++){
						for(up_y; up_y > current_y; up_y++){
							if(player.piece == 'B'){
								board[left_x][up_y] = 'O';
								count = count + 1;
								flip = false;
							} else if (player.piece == 'O'){
								board[left_x][up_y] = 'B';
								count = count + 1;
								flip = false;
							}
						}
					}
					break;
				}
			}
		}
	}*/
	return count;
}


void Othello::ckwin(){
	int Bcount = 0;
	int Ocount = 0;
	for (int i = 0; i < boardsize; i++){
		for (int x = 0; x < boardsize; x++){
			if (board[i][x] == 'B'){
				Bcount = Bcount + 1;
			} else if (board[i][x]== 'O'){
				Ocount = Ocount + 1;
			}
		}
	}
	if (player1.piece == 'B'){
		if (Bcount > Ocount){
			cout << player1.name << " won with: "<< Bcount << " versus "<< Ocount << endl;
		} else if (Ocount > Bcount){
			cout << player2.name << " won with: "<< Ocount << " versus "<< Bcount << endl;
		} else {
			cout << "it was a tie: "<< Bcount << " versus "<< Ocount << endl;
		}
	} else if (player1.piece == 'O'){
		if (Bcount > Ocount){
			cout << player2.name << " won with: "<< Bcount << " versus "<< Ocount << endl;
		} else if (Ocount > Bcount){
			cout << player1.name << " won with: "<< Ocount << "  versus "<< Bcount << endl;
		} else {
			cout << "it was a tie: "<< Bcount << " versus "<< Ocount << endl;
		}
	}
}

void Othello::compplacepiece(Player p){
	int xcoord[60];
	int ycoord[60];
	int max = 0;
	int j = 0;
	bool flip = false;
	for (int i = 0; i < boardsize; i++){
		for (int z = 0; z < boardsize; z++){
			if(board[i][z] == '_'){
				if(countandflippieces(i,z,p, flip) > max){
					max = countandflippieces(i,z,p, flip);
				}
			}
		}
	}
	for (int i = 0; i < boardsize; i++){
		for (int z = 0; z < boardsize; z++){
			if(countandflippieces(i,z,p,flip) == max){
				xcoord[j] = i;
				ycoord[j] = z;
				j++;
			}
		}
	}
	int r = rand()%j;
	flip = true;
	board[xcoord[r]][ycoord[r]] = p.piece;
	countandflippieces(xcoord[r],ycoord[r],p, flip);

}

void Othello::playGame(){
	makemat();
	printmat();
	bool play = true;
	int fullsqrs = 0;
	Player p = player1;
	bool whichp = true;
	bool turn = true;

	if (rand()%2 == 0) { // p1 plays first
		p = player2;
		turn = false;
		whichp = false;
	}

	while ((play) && (fullsqrs < 64)){
		cout << endl << p.name <<" ("<<p.piece<<") choose your square: "<< endl;
		if ((numplayer == 2) || ((numplayer == 1) && turn)){
			placepiece(p);
		}
		else if ((numplayer == 0) || ((numplayer == 1) && (turn == false))){
			compplacepiece(p);
		}
		turn = !turn;
		printmat();
		if (whichp) {
			p = player2;
			whichp = false;
		}
		else {
			p=player1;
			whichp = true;
		}
			fullsqrs+=1;
	}
ckwin();
}





