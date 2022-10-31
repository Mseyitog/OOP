#ifndef UTIL_HPP
# define UTIL_HPP

#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum class tetrominos_type{
	TetI,
	TetO,
	TetT,
	TetJ,
	TetL,
	TetS,
	TetZ
};

class Merge;

class Tetromino
{
	public :
	Tetromino(tetrominos_type);
	void print() const; //printing the original tetromino string
	void rotate(char pos); // rotating the tetromino string to the right everytime it has called and modifies the original tetromino string
	bool canFit(Merge); // checks if next tetromino fits in the previous ones
	void clearX(); // creates and modifies the original tetromino string from the rotate string
	static int heightt(); // tetrominos height
	static int width(); // tetrominos width
	vector<string> &getClear() {return clearTet;} // gives the original tetromino string
	tetrominos_type getType() {return type;} // gives the type of tetromino

	private :
	tetrominos_type type; // type of tetromino
	vector<string> tetrominos; // holds the rotate string for the tetromino
	vector<int> rotIndex; // origin point in the vector
	vector<string> clearTet; // original tetromino string
	
	void initIndex(); // initializes the origin point for the rotate tetromino string
	void createTet(); // creates the rotate tetromino string
	void rotatePieces(int x, int y, vector<string> &ret, char pos); // rotate every index of the rotate tetromino string
};

class Merge
{
	public:
	Merge(Tetromino init); // adds first tetromino to the merged string
	void tetMerge(Tetromino &tet2); //adds other tetrominos at the  end of the string
	void bestFit(vector<Tetromino>); //searches for the best fit
	void shift(); // shifts if there is a space between tetroominos
	vector<string> getMerge() {return merge;} //returns the merged string
	int getColumn() {return column;} //returns the height of the merged string
	string widthSpace(int width); //returns a string full of spaces with merged string width size
	void print(); // print the merged string

	private :
	vector<string> merge; //holds the final resut of fitted tetrominos
	int row; // holds merge width
	int column; // holds merge height

	void initCheck(Tetromino &init); // checks if the first tetromino is in its best rotated position for the best fit
};

#endif