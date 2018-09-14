/*
 * Logic.hpp
 *
 *  Created on: 11/09/2018
 *      Author: diegoruiz
 */

#ifndef LOGIC_HPP_
#define LOGIC_HPP_
#include<vector>
#include <string>

#define DISABLED -4
#define MINE -3
#define FLAG -2
#define NONE -1
using namespace std;

class Logic {
public:
	Logic();
	virtual ~Logic();
	void setRows(int rows);
	void setColumns(int columns);
	void setMines(int mines);
	void setRoundFinish(bool round_finish);
	int getRows(void);
	int getColumns(void);
	int getMines(void);
	bool getGameFinish(void);
	bool getRoundFinish(void);
	vector <string> getMinesPosVector(void);
	int ** getShowBoard(void);
	string getEndMessage(void);
	void initParameters(string parameters);
	bool validateParameters(void);
	void initBoard(void);
	void builtVectorMinesPositions(void);
	void setMinesToBoard(string board_name);
	void setShowBoard(string position);
	void uncover(int row, int column);
	void uncoverNextCell(int row, int column);
	void evaluateBoard();

private:
	int rows;
	int columns;
	int mines;
	int ** board;
	int ** show_board;
	bool game_finish;
	bool round_finish;
	vector<string> mines_positions;
	int uncovers;
	string end_message;
};

#endif /* LOGIC_HPP_ */
