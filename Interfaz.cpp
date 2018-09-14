/*
 * Interfaz.cpp
 *
 *  Created on: 11/09/2018
 *      Author: diegoruiz
 */

#include <iostream>
#include "Interfaz.hpp"

using namespace std;

Interfaz::Interfaz() {
	// TODO Auto-generated constructor stub
	logic = new Logic();
	welcomeToGame();
	setInitParameters();
	initGame();
}

Interfaz::~Interfaz() {
	// TODO Auto-generated destructor stub
}

void Interfaz::helloWorld(){
	cout << "Hello World" << endl;
}
/**
 * Welcome message
 */
void Interfaz::welcomeToGame(){
	cout << "Welcome to the MinesWeeper V1.0" << endl;
}

/**
 * Set Parameters in logic object
 */
void Interfaz::setInitParameters(){
	cout << "Input rows columns mines. eg.: 15 8 10" << endl;
	cout << "> ";
	while(!logic->validateParameters()){
		string input = "";
		getline(cin, input);
		if(input != ""){
			logic->initParameters(input);
		}
	}
}

void Interfaz::initGame(){
	if(logic->validateParameters()){
		logic->initBoard();
		printBoard();
		playingGame();
	}else{
		while(true){
			cout << "Invalid parameters, please set parameters again" << endl;
			setInitParameters();
			if(logic->validateParameters()){
				break;
			}
		}
	}
}

void Interfaz::playingGame(){
	while(!logic->getGameFinish()){
		logic->setRoundFinish(false);
		cout << "Input row column action. eg.: 1 2 U " << endl;
		cout << "> ";
		while(!logic->getRoundFinish()){
			string input = "";
			getline(cin, input);
			if(input != ""){
				logic->setShowBoard(input);
			}
		}
		printBoard();
	}
	cout << "          " << logic->getEndMessage() << endl;
}

void Interfaz::printBoard(){
	cout << endl;
	int ** board = logic->getShowBoard();
	for(int k=0; k<logic->getColumns(); k++){
		if(k == 0){
			cout << "           " << "  ";
			cout << k << "  ";
		}else{
			cout << k << "  ";
		}
	}
	cout << endl;
	for(int i=0; i<logic->getRows(); i++){
		for(int j=0; j<logic->getColumns(); j++){
			char aux;
			switch(board[i][j]){
			case -4:
				aux = '-';
				break;
			case -3:
				aux = '*';
				break;
			case -2:
				aux = 'P';
				break;
			case -1:
				aux = '.';
				break;
			default:
				aux = (char)(board[i][j]+48);
			}
			if(j == 0)
				cout << "          " << i << "  " << aux << "  ";
			else
				cout << aux << "  ";
		}
			cout << endl;
	}
	cout << endl;
}





