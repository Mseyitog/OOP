#include "util.hpp"

/*header file has each functions and variables detailed explanation
for algorithm descriptions you can look at this file*/

void Tetromino::createTet()
{
	switch (type)
	{
		case tetrominos_type::TetI:
		tetrominos = {"XXXXX", "XXXXX","XIIII", "XXXXX", "XXXXX"};
		break;
		case tetrominos_type::TetO:
		tetrominos = {"XOO", "XOO", "XXX"};
		break;
		case tetrominos_type::TetT:
		tetrominos = {"TTT", " T ", "XXX"};
		break;
		case tetrominos_type::TetJ:
		tetrominos = {"X JXX", "X JXX", "XJJXX", "XXXXX", "XXXXX"};
		break;
		case tetrominos_type::TetL:
		tetrominos = {"XXL X", "XXL X", "XXLLX", "XXXXX", "XXXXX"};
		break;
		case tetrominos_type::TetS:
		tetrominos = {" SS", "SS ", "XXX"};
		break;
		case tetrominos_type::TetZ:
		tetrominos = {"ZZ ", " ZZ", "XXX"};
		break;
	}
	clearX();
	initIndex();
}

void Tetromino::initIndex(){
	switch (type)
	{
		case tetrominos_type::TetI : case tetrominos_type::TetJ: case tetrominos_type::TetL:
		rotIndex = {2, 2};
		break;
		case tetrominos_type::TetO : case tetrominos_type::TetS: case tetrominos_type::TetZ: case tetrominos_type::TetT:
		rotIndex = {1, 1};
		break;
	}
}

Tetromino::Tetromino(tetrominos_type typeValue)
{
	type = typeValue;
	createTet();
}

void Tetromino::print() const
{
	for (auto i : clearTet)
		cout << i << endl;
}

/* 	The rotation made by using rotation matrix
	| cosa  -sina | | x |   | x'|
	|       	  | |   | = |   |
	| sina   cosa | | y |   | y'|

	since the rotation angle a is 90 for right rotation we can modify this matris like this
	| 0  -1 | | x |
	| 1   0 | | y |

	and rotatioon angle for left rotation is -90 so we modify this matris like this
	| 0  1 | | x |
	| -1   0 | | y |
*/
void Tetromino::rotate(char pos)
{
	vector<string> ret = tetrominos;

	for(int i=0; i<tetrominos.size(); i++)
	{
		for(int j=0; j<tetrominos[i].size(); j++)
			rotatePieces(j, i, ret, pos);
	}

	tetrominos = ret;
	clearX();
}

void Tetromino::rotatePieces(int x, int y, vector<string> &ret, char pos)
{
	int tempx = x - rotIndex[0];
	int tempy = y - rotIndex[1];
	int newx, newy;

	if (pos == 'r')
	{
		newx = -tempy + rotIndex[0];
		newy = tempx + rotIndex[1];

		ret[newy][newx] = tetrominos[y][x];
	}
	else if (pos == 'l')
	{
		newx = tempy + rotIndex[0];
		newy = -tempx + rotIndex[1];

		ret[newy][newx] = tetrominos[y][x];
	}
}

void Tetromino::clearX()
{
	string temp;
	int flag = 0;

	clearTet.clear();
	for (auto i : tetrominos)
	{
		for (auto j : i)
		{
			if (j != 'X')
			{
				temp += j;
				flag = 1;
			}
		}
		if (flag == 1)
			clearTet.push_back(temp);
		temp.clear();
		flag = 0;
	}
}

int heightt(const vector<string>& s)
{
	int height = 0;

	for (auto i : s)
		++height;
	return (height);
}

int width(const vector<string>& s)
{
	int width = 0;

	for (auto i : s[0])
		++width;
	
	return (width);
}

Merge::Merge(Tetromino init)
{
	initCheck(init);
}

//loops till the last column of the initial tetromino has no spaces except the s and z tetromios and assigns it to the merged vector
void Merge::initCheck(Tetromino &init)
{
	int flag;
	do
	{
		flag = 0;
		column = heightt(init.getClear()); 
		row = width(init.getClear());
		for (auto i : init.getClear()[column - 1])
		{
			if (i == ' ' && init.getType() != tetrominos_type::TetS && init.getType() != tetrominos_type::TetZ)
				flag = 1;
		}
		if (flag == 1)
			init.rotate('r');
	} while(flag == 1);
	merge = init.getClear();
}

string Merge::widthSpace(int width)
{
	string s;

	for(int i = 0; i<width; i++)
		s.push_back(' ');
	return s;
}

void Merge::tetMerge(Tetromino &tet)
{
	int myHeight = heightt(merge), otherHeight = heightt(tet.getClear());
	int height = ((myHeight > otherHeight) ? myHeight : otherHeight);
	column = height; //updates the height for the merged tetromino

	/*
	these if statements make sure that every tetromino fitted in the gorund
	*/
	if (myHeight < otherHeight)
	{
		//inserts additional lines at the beginning of the vector if the tetromino we try to add has higher height than our merged array
		for (int i = 0; i < otherHeight-myHeight; i++)
			merge.insert(merge.begin(), widthSpace(width(merge)));
	}

	int a = 0;
	if (otherHeight < myHeight)
	{
		//adds lines full of space if the tetromino we add has lower height than our merged array
		for (a = 0; a < myHeight-otherHeight; a++)
			merge[a] += (widthSpace(width(tet.getClear())));
	}

	//adds the tetromino at the right end of the vector
	for (int k = 0; k < tet.getClear().size(); k++, a++)
		merge[a] += tet.getClear()[k];

	row += width(tet.getClear());//updates the row size
}

/*
	cheks if there is a space we could erase so we could shift the tetrominos by one
	looks for the spaces upper column to see if there is a space there too then deletes them
*/
void Merge::shift()
{
	for (int i = 1; i < row; i++)
	{
		if(merge[column - 1][i] == ' ' && (merge[column - 2][i - 1] == ' ' || merge[column - 2][i + 1] == ' ' || merge[column - 2][i] == ' '))
		{
			int k;
			merge[column - 1].erase(merge[column - 1].begin() + i);
			if (merge[column - 2][i - 1] == ' ') 
			{
				merge[column - 2].erase(merge[column - 2].begin() + i - 1);
				k = i - 1;
			}
			else if (merge[column - 2][i + 1] == ' ')
			{
				merge[column - 2].erase(merge[column - 2].begin() + i + 1);
				k = i + 1;
			}
			else if (merge[column - 2][i] == ' ')
			{
				merge[column - 2].erase(merge[column - 2].begin() + i);
				k = i;
			}
			for(int j = column - 3; j >= 0; j--)
			{
				if (merge[j][k] == ' ')
					merge[j].erase(merge[j].begin() + k);
				else if (merge[j][k + 1] == ' ')
				{
					merge[j].erase(merge[j].begin() + k + 1);
					k = k + 1;
				}
				else if (merge[j][k - 1] == ' ')
				{
					merge[j].erase(merge[j].begin() + k - 1);
					k = k - 1;
				}
			}
			--row;
		}
	}
}

//checks if the final column has any spaces if there is return false
bool Tetromino::canFit(Merge ret)
{
	ret.tetMerge(*this);
	ret.shift();

	bool first = true;
	vector<string> temp = ret.getMerge();
	for (auto &i : temp[ret.getColumn() - 1])
	{
		if (i == ' ' && &i != &temp[ret.getColumn() - 1].back() && first == false)
			return false;
		if (first == true)
			first = false;
	}
	return true;
}

//try to find the best fit if there is none exits
void Merge::bestFit(vector<Tetromino> tets)
{
	int rotateNum = 0;

	for (int i = 1; i<tets.size(); i++)
	{
		while(!tets[i].canFit(*this) && rotateNum < 4)
		{
			tets[i].rotate('r');
			++rotateNum;
		}
		if (rotateNum != 4)
		{
			tetMerge(tets[i]);
			shift();
		}
		else
		{
			cout << "Couldn't fit the tetromino!" << endl;
			exit(1);
		}
		rotateNum = 0;
	}
}

void Merge::print()
{
	for (auto i : merge)
		cout << i << endl;
}
