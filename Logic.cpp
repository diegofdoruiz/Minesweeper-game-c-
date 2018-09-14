/*
 * Logic.cpp
 *
 *  Created on: 11/09/2018
 *      Author: diegoruiz
 */

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <random>
#include "Logic.hpp"

Logic::Logic() {
	// TODO Auto-generated constructor stub
	rows = 0;
	columns = 0;
	mines = 0;
	game_finish = false;
	round_finish = false;
	board = NULL;
	show_board = NULL;
	uncovers = 0;
	end_message = "";
}

Logic::~Logic() {
	// TODO Auto-generated destructor stub
}

//set the number of rows
void Logic::setRows(int rows){
	this->rows = rows;
}

//set the number of columns
void Logic::setColumns(int columns){
	this->columns = columns;
}

//set the number of mines
void Logic::setMines(int mines){
	this->mines = mines;
}

//set state of finalization of game
void Logic::setRoundFinish(bool round_finish){
	this->round_finish = round_finish;
}

//get the number of rows
int Logic::getRows(void){
	return rows;
}

//get the number of columns
int Logic::getColumns(void){
	return columns;
}

//get the number of mines
int Logic::getMines(void){
	return mines;
}

//get game state
bool Logic::getGameFinish(void){
	return game_finish;
}

//get round state
bool Logic::getRoundFinish(void){
	return round_finish;
}

//get the vector of mines positions
vector<string> Logic::getMinesPosVector(){
	return mines_positions;
}

//Return the boar for show in the interfaz
int ** Logic::getShowBoard(){
	return show_board;
}

//Return finish message
string Logic::getEndMessage(void){
	return end_message;
}

/**
* initParameters @string
* "15 8 10", rows, columns, mines
* set vector<int> vector_position
**/
void Logic::initParameters(string parameters){
	vector<string> vector_position;
	stringstream ss(parameters);
	string token;
	while (getline(ss, token, ' ')) {
		vector_position.push_back(token);
	}
	rows = atoi(vector_position[0].c_str());
	columns = atoi(vector_position[1].c_str());
	mines = atoi(vector_position[2].c_str());
}

/*
* Check if the parametrers are valid
*/
bool Logic::validateParameters(void){
	if(rows > 0 && columns > 0 && mines <= rows * columns){
		return true;
	}else{
		return false;
	}
}

/*
* set main board and show board
* set mines to board
* set show board with NONE all
*/
void Logic::initBoard(){
	board = new int*[rows];
	for(int i=0; i<rows; i++){
		board[i] = new int[columns];
		for(int j=0; j<columns; j++){
			board[i][j] = NONE;
		}
	}

	//Put mines in the main board
	setMinesToBoard("board");

	for(int i=0; i<rows; i++){
		for(int j=0; j<columns; j++){
			if(board[i][j] != MINE){
				int mines = 0;
				//Up left
				if(i-1 >= 0 && j-1 >= 0)
					if(board[i-1][j-1] == MINE)
						mines++;
				//Up
				if(i-1 >= 0)
					if(board[i-1][j] == MINE)
						mines++;
				//Up right
				if(i-1 >= 0 && j+1 < columns)
					if(board[i-1][j+1] == MINE)
						mines++;
				//Left
				if(j-1 >= 0)
					if(board[i][j-1] == MINE)
						mines++;
				//Rigth
				if(j+1 < columns)
					if(board[i][j+1] == MINE)
						mines++;
				//Button left
				if(i+1 < rows && j-1 >= 0)
					if(board[i+1][j-1] == MINE)
						mines++;
				//Button
				if(i+1 < rows)
					if(board[i+1][j] == MINE)
						mines++;
				//Button right
				if(i+1 < rows && j+1 < columns)
					if(board[i+1][j+1] == MINE)
						mines++;
				//Set number of mines
				if(mines > 0)
					board[i][j] = mines;
			}
			//cout<<board[i][j]<<'\t';
		}
			//cout<<endl;
	}

	//Init show_board array
	show_board = new int*[rows];
	for(int i=0; i<rows; i++){
		show_board[i] = new int[columns];
		for(int j=0; j<columns; j++){
			show_board[i][j] = NONE;
		}
	}


}

/*
* set vector<string> builtVectorMinesPositions
* with random numbers
*/
void Logic::builtVectorMinesPositions(void){
	vector<string> all_positions;
	vector<string> random_positions;
	/*Set array with all positions of the matrix as string*/
	for(int i=0; i<rows; i++){
		for(int j=0; j<columns; j++){
			all_positions.push_back(to_string(i)+"-"+to_string(j));
		}
	}

	/* initialize random seed: */
	srand (time(NULL));

	for(int j=0; j<mines; j++){
		/* generate random number between 0 and all_positions.size()-1: */
		int random_number = rand() % (int)all_positions.size();

		/* add value of the pos select to randoms numbers*/
		mines_positions.push_back(all_positions[random_number]);

		// erase the random position of vector all_positions
		all_positions.erase(all_positions.begin() + random_number);
	}
}

/*
* Method for set mines to main board
*/
void Logic::setMinesToBoard(string board_name){
	if(board_name == "board"){
		builtVectorMinesPositions();
	}
	for(int k=0; k<(int)mines_positions.size(); k++){
		vector<string> vector_position;
		stringstream ss(mines_positions[k]);
		string token;
		while (getline(ss, token, '-')) {
			vector_position.push_back(token);
		}
		int row = atoi(vector_position[0].c_str());
		int column = atoi(vector_position[1].c_str());
		if(board_name == "board"){
			board[row][column] = MINE;
		}else{
			show_board[row][column] = MINE;
		}
	}
}

/*
* Receive the position in the round and eval, modify the show
* board
*/
void Logic::setShowBoard(string position){
	vector<string> vector_position;
	stringstream ss(position);
	string token;
	while (getline(ss, token, ' ')) {
		vector_position.push_back(token);
	}
	int row = atoi(vector_position[0].c_str());
	int column = atoi(vector_position[1].c_str());
	char action = vector_position[2][0];

	if(action == 'U' || action == 'u'){
		if((board[row][column] > 0 && show_board[row][column] == FLAG) || (board[row][column] == NONE && show_board[row][column] == FLAG) || (board[row][column] == MINE && show_board[row][column] == FLAG)){
			round_finish = true;
		}else if(board[row][column] == MINE){ // Game over
			end_message = "** Game over! **";
			setMinesToBoard("show_board");
			round_finish = true; 
			game_finish = true; //Finish game
		}else if(board[row][column] > 0){
			show_board[row][column] = board[row][column];
			uncovers++;
			round_finish = true; //Finish round
			evaluateBoard();
		}else if(board[row][column == NONE]){
			uncover(row, column);
			round_finish = true;
			evaluateBoard();
		}
	}else if(action == 'M' || action == 'm'){
		if(show_board[row][column] == NONE || show_board[row][column] == FLAG){
			if(show_board[row][column] == FLAG){
				show_board[row][column] = NONE;
			}else{
				show_board[row][column] = FLAG;
			}
		}
		round_finish = true;
	}else{
		round_finish = true;
	}
}

/*
* Metods  uncover and uncoverNextCell for uncover free free neighbors
*/
void Logic::uncover(int row, int column){
	uncoverNextCell(row - 1, column - 1);
	uncoverNextCell(row - 1, column);
	uncoverNextCell(row - 1, column + 1);
	uncoverNextCell(row + 1, column);

	uncoverNextCell(row, column - 1);
	uncoverNextCell(row, column + 1);
	uncoverNextCell(row + 1, column - 1);
	uncoverNextCell(row + 1, column + 1);
}

void Logic::uncoverNextCell(int row, int column){
	if(row < 0 || row >= rows || column < 0 || column >= columns){
		return;
	}
	if (board[row][column] == NONE && show_board[row][column] == NONE){
		show_board[row][column] = DISABLED;
		uncovers ++;
		uncover(row, column);
		return;
	}else if(board[row][column] > 0 && show_board[row][column] == NONE){
		show_board[row][column] = board[row][column];
		uncovers++;
		return;
	}else{
		return;
	}
}

/*
* Count uncovers, if uncovers + mines == rows*columns. 
* there are win
*/
void Logic::evaluateBoard(){
	if((uncovers + mines_positions.size()) == rows*columns){
		end_message = "***** You win! *****";
		game_finish = true; // Finish game
	}
}






