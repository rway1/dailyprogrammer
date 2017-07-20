#include <iostream>
#include <vector>
#include <sstream>

using std::string;
using std::stringstream;
using std::cin;
using std::cout;
using std::endl;
using std::vector;

bool changeMade = true;
vector<vector<char> > grid;


void printGrid();
char getGridElement(int x, int y, bool flag);
void setGrid(int x, int y, bool flag, char insert);
void checkDoubles();
void checkDoubles(bool flag);
void checkRemaining();
void checkRemaining(bool flag);
void fillLast(int x, bool flag, char insert);
void oneLeft(int x , bool flag, char insert);
void rowCompare(int x, bool flag);
bool isComplete(int x, bool flag);
bool isEqual(int x, int z, bool flag);
void applyLogic();
void bruteForce();
bool checkSolution();
bool noTriples();
bool noTriples(bool flag);
bool noDuplicates();
bool noDuplicates(bool flag);
bool bruteForceInsert(int x, int y);

int main()
{
	string input;
	while(getline(cin, input))
	{
		stringstream _input;
		_input << input;
		char insert;
		vector<char> inserts;
		while(_input >> insert)
		{
			inserts.push_back(insert);
		}
		grid.push_back(inserts);
	}
	applyLogic();
//	printGrid();
	//bruteForce();
	printGrid();
}

void applyLogic()
{
	while(changeMade)
	{
		changeMade = false;
		checkDoubles();
		checkRemaining();
	}
}

bool checkSolution()
{
	return noTriples() && noDuplicates();
}

bool noTriples()
{
	return noTriples(true) && noTriples(false);
}

bool noTriples(bool flag)
{
	for(int x = 0; x < grid.size(); x++)
	{
		for(int y = 0; y < grid.size()-2; y++)
		{
			if((getGridElement(x, y, flag) == getGridElement(x, y+1, flag)) && (getGridElement(x, y+1, flag) == getGridElement(x, y+2, flag)))
			{
				return false;
			}
		}
	}
	return true;
}

bool noDuplicates()
{
	return noDuplicates(true) && noDuplicates(false);
}

bool noDuplicates(bool flag)
{
	for(int x = 0; x < grid.size(); x++)
	{
		for(int z = x+1; z < grid.size(); z++)
		{
			if(isEqual(x, z, flag))
			{
				return false;
			}
		}
	}
	return true;
}

void bruteForce()
{
	for(int x = 0; x < grid.size(); x++)
	{
		for(int y = 0; y < grid.size(); y++)
		{
			if(getGridElement(x, y, '0') == '-')
			{
				if(bruteForceInsert(x, y))
				{
					y = grid.size();
					x = grid.size();
				}
			}
		}
	}
}

bool bruteForceInsert(int x, int y)
{
	vector< vector<char> > tempGrid = grid;
	setGrid(x, y, '0', '0');
	applyLogic();
	if(checkSolution())
	{
		return true;
	}
	grid = tempGrid;
	setGrid(x, y, '0', '1');
	if(checkSolution())
	{
		return true;
	}
	grid = tempGrid;
	return false;
}

void printGrid()
{
	for(int x = 0; x < grid.size(); x++)
	{
		for(int y = 0; y < grid[x].size(); y++)
		{
			cout << grid[x][y] << " ";
		}
		cout << endl;
	}
}

char getGridElement(int x, int y, bool flag)
{
	if(flag)
	{
		return grid[y][x];
	}
	else
	{
		return grid[x][y];
	}
}

void setGrid(int x, int y, bool flag, char insert)
{
	if(insert == '1')
	{
		insert = '0';
	}
	else
	{
		insert = '1';
	}
	if(flag)
	{
		grid[y][x] = insert;
	}
	else
	{
		grid[x][y] = insert;
	}
	changeMade = true;
}

void checkDoubles()
{
	checkDoubles(false);
	checkDoubles(true);
}

void checkDoubles(bool flag)
{
	for(int x = 0; x < grid.size(); x++)
	{
		for(int y = 1; y < grid.size()-1; y++)
		{
			if(getGridElement(x, y, flag) != '-')
			{
				if((getGridElement(x, y, flag) == getGridElement(x, y+1, flag)) && (getGridElement(x, y-1, flag) == '-'))
				{
					setGrid(x, y-1, flag, getGridElement(x, y, flag));
				}
				if((getGridElement(x, y, flag) == getGridElement(x, y-1, flag)) && (getGridElement(x, y+1, flag) == '-'))
				{
					setGrid(x, y+1, flag, getGridElement(x, y, flag));
				}
			}
			else
			{
				if((getGridElement(x, y-1, flag) != '-') && (getGridElement(x, y-1, flag) == getGridElement(x, y+1, flag)))
				{
					setGrid(x, y, flag, getGridElement(x, y+1, flag));
				}
			}
		}
	}
}

void checkRemaining()
{
	checkRemaining(false);
	checkRemaining(true);
}

void checkRemaining(bool flag)
{
	for(int x = 0; x < grid.size(); x++)
	{
		int zeroes = 0;
		int ones = 0;
		for(int y = 0; y < grid.size(); y++)
		{
			switch(getGridElement(x, y, flag))
			{
				case '0':
					zeroes++;
					break;
				case '1':
					ones++;
			}
		}
		if(zeroes+ones != grid.size())
		{
			if(zeroes == grid.size()/2)
			{
				fillLast(x, flag, '0');
			}
			else if(ones == grid.size()/2)
			{
				fillLast(x, flag, '1');
			}
			else if((zeroes == grid.size()/2 -1) && (ones < zeroes))
			{
				oneLeft(x, flag, '0');
			}
			else if((ones == grid.size()/2 -1) && (zeroes < ones))
			{
				oneLeft(x, flag, '1');
			}
			else if((zeroes == ones) && (zeroes+ones == grid.size()-2))
			{
				rowCompare(x, flag);
			}
		}
	}
}

bool isComplete(int z, bool flag)
{
	for(int y = 0; y < grid.size(); y++)
	{
		if(getGridElement(z, y, flag) == '-')
		{
			return false;
		}
	}
	return true;
}

bool isEqual(int x, int z, bool flag)
{
	for(int y = 0; y < grid.size(); y++)
	{
		if((getGridElement(x, y, flag) != '-') && (getGridElement(x, y, flag) != getGridElement(z, y, flag)))
		{
			return false;
		}
	}
	return true;
}

void rowCompare(int x, bool flag)
{
	for(int z = 0; z < grid.size(); z++)
	{
		if(isComplete(z, flag))
		{
			if(isEqual(x, z, flag))
			{
				for(int y = 0; y < grid.size(); y++)
				{
					if((getGridElement(x, y, flag) == '-') && (getGridElement(z, y, flag) == '1'))
					{
						setGrid(x, y, flag, '1');
					}
					if((getGridElement(x, y, flag) == '-') && (getGridElement(z, y, flag) == '0'))
					{
						setGrid(x, y, flag, '0');
					}
				}
			}
		}
	}
}


void oneLeft(int x, bool flag, char insert)
{
	int sequence = 0;
	for(int y = 0; y < grid.size()-2; y++)
	{
		while((y+sequence < grid.size()) && (getGridElement(x, y+sequence, flag) != insert))
		{
			sequence++;
		}
		if(sequence > 2)
		{
			for(int z = 0; z < y; z++)
			{
				if(getGridElement(x, z, flag) == '-')
				{
					setGrid(x, z, flag, insert);
					z = grid.size();
					y = grid.size();
				}
			}
			for(int z = y+3; z < grid.size(); z++)
			{
				if(getGridElement(x, z, flag) == '-')
				{
					setGrid(x, z, flag, insert);
					z = grid.size();
					y = grid.size();
				}
			}
		}
		sequence = 0;
	}
}

void fillLast(int x, bool flag, char insert)
{
	for(int y = 0; y < grid.size(); y++)
	{
		if(getGridElement(x, y, flag) == '-')
		{
			setGrid(x, y, flag, insert);
		}
	}
}
