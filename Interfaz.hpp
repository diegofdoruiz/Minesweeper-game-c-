/*
 * Interfaz.hpp
 *
 *  Created on: 11/09/2018
 *      Author: diegoruiz
 */
#include "Logic.hpp"
#ifndef INTERFAZ_HPP_
#define INTERFAZ_HPP_

class Interfaz {
public:
	Interfaz();
	virtual ~Interfaz();
	void helloWorld(void);
	void welcomeToGame();
	void setInitParameters();
	void initGame();
	void printBoard();
	void playingGame();

private:
	Logic * logic;

};

#endif /* INTERFAZ_HPP_ */
