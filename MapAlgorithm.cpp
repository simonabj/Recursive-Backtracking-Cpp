// MapAlgorithm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>																										   
#include <vector>

using namespace std;

enum DIRECTIONS { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 }; // Used to reference the different directions reperesented by integers

class Cell {
private:
	string cell_struct = "";
	char floor = '-';
	char wall = '#';
public:
	// Initializes the cell and builds the base structure!
	Cell::Cell() {
		int i = 0;

		// Create upper row (y=0)
		for (i = 0; i < 3; i++) {
			this->cell_struct += this->wall;
		}

		// Create middlerow (y=1)
		for (i = 0; i < 3; i++) {
			if (i == 1 && this->_visited) this->cell_struct += this->floor;
			else this->cell_struct += this->wall;
		}

		// Create bottom row
		for (i = 0; i < 3; i++) {
			this->cell_struct += this->wall;
		}
	}
	
	// Rebuilds the cell. NB! All changes done to the cell will be lost!
	void Cell::rebuild() {
		this->cell_struct = "";
		int i = 0;

		// Create upper row (y=0)
		for (i = 0; i < 3; i++) {
			this->cell_struct += this->wall;
		}

		// Create middlerow (y=1)
		for (i = 0; i < 3; i++) {
			if (i == 1) this->cell_struct += this->floor;
			else this->cell_struct += this->wall;
		}

		// Create bottom row
		for (i = 0; i < 3; i++) {
			this->cell_struct += this->wall;
		}
	}
	
	// Sets the Wall-Char. NB! Rebuilds the cell! All changes done to the cell will be lost!
	void Cell::setWallChar(char newChar)
	{
		this->wall = newChar;
		rebuild();
	}

	// Sets the Floor-Char. NB! Rebuilds the cell! All changes done to the cell will be lost!
	void Cell::setFloorChar(char newChar)
	{
		this->floor = newChar;
		rebuild();
	}

	// Toggles one of the sides of the cell. Changes are lost if cell is rebuilt!
	void Cell::toggleSide(int side, bool state /*true is floor, false is wall*/) {
		switch (side)
		{
		case(UP):
			if (state) { this->cell_struct[1] = this->floor; }
			else {this->cell_struct[1] = this->wall;}
			break;
		case(DOWN):
			if (state) { this->cell_struct[7] = this->floor; }
			else { this->cell_struct[7] = this->wall; }
			break;
		case(LEFT):
			if (state) { this->cell_struct[3] = this->floor; }
			else { this->cell_struct[3] = this->wall; }
			break;
		case(RIGHT):
			if (state) { this->cell_struct[5] = this->floor; }
			else { this->cell_struct[5] = this->wall; }
			break;
		}
	}

	// Gets the char at a specific position in the cell
	char Cell::getCharAtPos(int x, int y) {
		return this->cell_struct[(y * 3) + x];
	}

	// Used for generation algorithems. Used to determine if the cell has been visited or not.
	bool _visited = false;

	void Cell::setVisited(bool state) { this->_visited = state; this->cell_struct[4] = '-'; }

	// Dangerous function! Use at own risk!
	void Cell::setCellStructure(string structure) {
		this->cell_struct = structure;
	}

	// Returns the structe of the cell reperisented in a string
	string Cell::getCellStruct() { return this->cell_struct; }

	// Gets a vector of all the chars in a row
	vector<char> Cell::getCellRow(int rowIndex)
	{
		vector<char> result(3);
		for (int i = 0; i < 3; i++) {
			result[i] = this->cell_struct[(rowIndex * 3) + i];
		}

		return result;
	}

	// Draws the cell induvidually
	void drawCell()
	{
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				cout << this->cell_struct[(3 * y) + x];
			}
			cout << endl;
		}
	}
};

class Map {
private:
	unsigned int size_x, size_y; // Declaration for the size of the map
	vector< vector<Cell>> map_grid; // The map itself
public:
	// Just a constructer
	Map::Map(unsigned int sizeX, unsigned int sizeY) {
		this->size_x = sizeX; this->size_y = sizeY;	  // Set the private fields size_x and size_y to the sepsified parameters.
		this->map_grid = vector< vector<Cell>>(this->size_y, vector<Cell>(this->size_x));   // Initialize the map_grid with 
		                                                                                    //2. dimensional vectors containing cell-objects
		for (int i = 0; i < this->map_grid.size(); i++) // Loop through the virst vector
		{
			vector<Cell>::iterator it = this->map_grid[i].begin(); // Create an iterator to loop through second vector
			for (; it < this->map_grid[i].end(); ++it) 	// Loop through iterator
			{
				*it = Cell(); // Set the iterator's referenced value to a new cell-object
			}
		}
	}
	Map::~Map() { cout << "Deleting map!" << endl; }	// Just a destructor

	// Returns the cell at a spesified position in the map. (X and Y values)
	Cell Map::getCellAtPos(int x, int y)
	{
		return this->map_grid.at(y).at(x);	// Using .at() instead of Operator[] to throw exceptions and bypass errors!
	}

	// Draws an induvidual cell at a spesific point in the grid
	void Map::drawCellAtPos(int x, int y) {
		this->map_grid.at(y).at(x).drawCell();	// Draws the cell at a posistion in the map_grid.
	}

	// Simply draws the hole map and all of it's cell-data
	void Map::drawMap() {
		int mapX, mapY, cellRow = 0;  // Initialize the loop-counters. Optional!
		for (mapY = 0; mapY < this->size_y; mapY++) {   // Loop through map_grid rows
			// cout << "Map Y: " << mapY << endl;	 // For debugging 
			for (cellRow = 0; cellRow < 3; cellRow++) {   // Loop through the cellRows within each map_grid.
				for (mapX = 0; mapX < this->size_x; mapX++) {   // Loop through the colums in the map_grid
					vector<char> temp_char = this->map_grid[mapY][mapX].getCellRow(cellRow); // Get the char_vector of the first row in cell
					vector<char>::iterator it = temp_char.begin();	// Create iterator pointer at the begining of vector
					for (; it < temp_char.end(); ++it)	// Loop through vector using the iterator
					{
						cout << *it; // Print out the value of the iterator
					}
					cout << "";  // Used for debug-purposes!
				}
				cout << endl; // Newline for new cellrow
			}
			cout << "";
		}
	}

	// Cell-change functions
	void Map::setCellStructureAtPos(int x, int y, string newCellStruct) {
		this->map_grid[y][x].setCellStructure(newCellStruct);
	}
	
	void Map::toggleCellSideAtPos(int x, int y, int side, bool state) {
		this->map_grid[y][x].toggleSide(side, state);
	}
	
	// Marks cell to be visited.
	void Map::visitCell(int x, int y) {
		this->map_grid[y][x].setVisited(true);
	}

	// Checks if the cell is visited.
	bool Map::cellVisited(int x, int y) { 
		return this->map_grid.at(y).at(x)._visited;   // Using .at() insted of Operator[] to throw exceptions needed to bypass errors!
	}
};

void recursive_backtracking(int * start_pos, Map * grid) {
	// Create vector for recursive-backtracking history.
	bool running = true;
	vector<pair<int, int>> history;
	int c = start_pos[0];
	int r = start_pos[1];

	history.push_back({ start_pos[0], start_pos[1] }); // Start at the startingposistion
	(*grid).setCellStructureAtPos(start_pos[0], start_pos[1], "---------");

	// Recursive backtracing starts here!
	while (running) {

		(*grid).visitCell(c, r);
		cout << "Visited: [" << c << "][" << r << "]   \t|| ";

		vector<int> check;

		// Check blocks!
		// Check Right
		try {
			if (!(*grid).cellVisited(c + 1, r)) {
				check.push_back(RIGHT);
			}
		}
		catch (const out_of_range& e) { e.what(); }

		// Check Left
		try {
			if (!(*grid).cellVisited(c - 1, r)) {
				check.push_back(LEFT);
			}
		}
		catch (const out_of_range& e) { e.what(); }

		// Check Up
		try {
			if (!(*grid).cellVisited(c, r - 1)) {
				check.push_back(UP);
			}
		}
		catch (const out_of_range& e) { e.what(); }

		// Check Down
		try {
			if (!(*grid).cellVisited(c, r + 1)) {
				check.push_back(DOWN);
			}
		}
		catch (const out_of_range& e) { e.what(); }

		// Choose one of the options!
		cout << "Avalable options:" << check.size() << "   \t|| ";
		if (check.size() > 0) {

			history.push_back({ c , r });
			int move_direction = check[rand() % check.size()];	 // Randomly pick a cell! For use of hash-functions, put stuff here!

			cout << "Moving:  " << move_direction << "   !!!";
			if (move_direction == UP)
			{
				(*grid).toggleCellSideAtPos(c, r, UP, true);
				--r;
				(*grid).toggleCellSideAtPos(c, r, DOWN, true);
			}
			else if (move_direction == DOWN) {

				(*grid).toggleCellSideAtPos(c, r, DOWN, true);
				++r;
				(*grid).toggleCellSideAtPos(c, r, UP, true);
			}
			else if (move_direction == LEFT) {

				(*grid).toggleCellSideAtPos(c, r, LEFT, true);
				--c;
				(*grid).toggleCellSideAtPos(c, r, RIGHT, true);
			}
			else if (move_direction == RIGHT) {
				(*grid).toggleCellSideAtPos(c, r, RIGHT, true);
				++c;
				(*grid).toggleCellSideAtPos(c, r, LEFT, true);
			}
		}
		else {
			if (history.size() > 1) {
				cout << "Backtracking !!!";
				history.pop_back();
				c = history.back().first;
				r = history.back().second;
			}
			else {
				cout << "\nDONE!" << endl;
				running = false;
			}
		}
		cout << endl;
	}

}

int main()
{
	int size_x = 38;	   // Size of map's width. (Multiply by 3 to get width in chars!)
	int size_y = 20;	   // Size of map's height. (Multiply by 3 to get height in chars!)
	// Recommended X-size = 38
	Map grid = Map(size_x, size_y);
	// [0] = x; [1] = y
	int start_pos[2] = { 2,2 }; // Start backtracking from cell [0,3]

	recursive_backtracking(start_pos, &grid);

/* // Cell Debug!
    Cell newCell = Cell();
	cout << "Pure Cell:\n";
	newCell.drawCell();

	cout << "Rebuilt visited cell:\n";
	newCell.setVisited(true);
	newCell.rebuild();
	newCell.drawCell();

	cout << "Opened top and bottom cell:\n";
	newCell.toggleSide(UP, true);
	newCell.toggleSide(DOWN, true);
	newCell.drawCell();

	cout << "Rebuilt cell:\n";
	newCell.rebuild();
	newCell.drawCell();
  */
	grid.drawMap();
	cout << endl;

	return 0;
}
