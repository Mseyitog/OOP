#include "util.hpp"

int main()
{
	vector<Tetromino> test;
	int numOfTet;
	char typee;
	enum tetrominos_type enumType;
	
	cout << "How many tetrominos?" << endl;
	cin >> numOfTet;

	cout << "What are the types?" << endl;
	for (int i = 0; i < numOfTet; i++)
	{
		cin >> typee;
		//initializes every member of the class tetromino vector
		switch (typee)
		{
			case 'I': 
			test.push_back(Tetromino(tetrominos_type::TetI));
			break;
			case 'J': 
			test.push_back(Tetromino(tetrominos_type::TetJ));
			break;
			case 'L':
			test.push_back(Tetromino(tetrominos_type::TetL));
			break;
			case 'O': 
			test.push_back(Tetromino(tetrominos_type::TetO));
			break;
			case 'S': 
			test.push_back(Tetromino(tetrominos_type::TetS));
			break;
			case 'Z': 
			test.push_back(Tetromino(tetrominos_type::TetZ));
			break;
			case 'T':
			test.push_back(Tetromino(tetrominos_type::TetT));
			break;
		}
	}

	cout << endl << "Your tetrominos" << endl;
	for (auto i : test)
	{
		i.print();
		cout << endl;
	}

	cout << "Horizontally best-fit tetrominos" << endl;
	Merge ret(test[0]);
	ret.bestFit(test);
	ret.print();
}