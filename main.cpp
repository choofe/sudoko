#include <iostream>
#include <vector>
#include "Block.h"
#include "BlockGrid.h"
#include "GridRow.h"
#include "GridColumn.h"
#include "Position.h"

using position_t = std::vector<Position>; 

std::ostream& operator<<(std::ostream& out, const block_t& blockt)   //overloading << operator to print out a block of 1~9
{
	for (size_t  i{ 0 }; i < blockt.size(); ++i)
	{
		for (size_t j{ 0 }; j < blockt.at(i).size(); ++j)
		{
			out << blockt.at(i).at(j) << " ";
		}
		out << '\n';
	}
	out << '\n';
	return out;
}
//fill random cells of 'grid' with random value 1~9 and checks if it is acceptable in terms of sudoko 
//to form an initial puzzle. there is a magic number on line 32 >> determines how many 
//initial cells to be filled initially
void fillRandom(BlockGrid& grid, int initiallyFilledCellNumber = 25)
{
	static std::mt19937 rand{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
	static std::uniform_int_distribution digit{ 1,9 };//uniform distribution bet
	static std::uniform_int_distribution cell{ 0,80 };//uniform distribution bet
	// magic number! i < VVVV determines how many initial cells would be pre-filled in puzzle
	for (int i{ 1 }; i <= initiallyFilledCellNumber ; ++i)
	{
		int randValue{ digit(rand) };			//random value to inset on grid
		int randCell{ cell(rand) };				//random position from 0~80 representing cells
		int gridRowNumber{ randCell / 27 };		// block row position in block grid vector
		int gridColumnNumber{ (randCell % 9) / 3 };	//block column position in block grid vector
		int cellRow{ (randCell / 9) % 3 };		//cell row in block vector
		int cellColumn{ (randCell % 9) % 3 };		//cell column in block vector
		int totalRowIndex{ randCell / 9 };		//index of row in block grid
		int totalColumnIndex{ randCell % 9 };		//index of column in block grid

		//check if there is already a number and the rules are not broken if
		//fill the cell with randValue
		if (grid.getBlock(gridRowNumber, gridColumnNumber).memberAccess(cellRow, cellColumn)== 0 &&
			grid.getBlock(gridRowNumber, gridColumnNumber).blockCheck(randValue) &&
			GridRow(grid, totalRowIndex).gridRowCheck(randValue) &&
			GridColumn(grid, totalColumnIndex).gridColumnCheck(randValue))
		{
			grid.getBlock(gridRowNumber, gridColumnNumber).memberSet({ cellRow,cellColumn }, randValue); //fill cell with randValue
		}
		else //put counter one back because this failed iteration should not be count!
		{
			--i;
		}
		
	}
}

//fill a vector of class position with each of 81 cell data 
//in the grid.
position_t initaialPositions(const BlockGrid& grid)
{
	grid_t gridt{ grid.getGrid() };
	position_t initial;
	
	initial.reserve(81);//increase vector to 82 to reduce resizings
	
	for (size_t i{ 0 }; i <81; ++i) //fill initial values with 0 as empty cells
		initial.push_back({ Position(i, 0) }); 

	for (size_t i{ 0 };i<initial.size();++i)
	{
		///////////////////////////////////////////////////////////
		// fetch the value on grid in "i"th position . 
		//"i" have been already converted to grid row and cell and cell row and 
		//column and stored in i th member of vector initial
		//////////////////////////////////////////////////////////
		int value{ gridt.at(initial.at(i).getGridRowNumber()).at(initial.at(i).getGridColumnNumber()). 
			getBlock().at(initial.at(i).getCellRow()).at(initial.at(i).getCellColumn()) };   
		
		if (value != 0)// if there is an initial number in cell
		{
			initial.at(i).setValue(value); //store the value

			initial.at(i).setIsInitialNumber(true); //mark the position as initial.
		}
	}
	return initial;
}

//checks the rules of sudoko 
//checks if 'checkingNum' in cell with 'positionIndex' in 'grid' is a correct answer
//returns true id it is and false if it isn't
bool areRulesMet(BlockGrid& grid, position_t& position, int posIndex, int checkingNumber)
{
	Position currentPosition{ position.at(posIndex) };
	return (
		checkingNumber <= 9 
		&& grid.getBlock(currentPosition.getGridRowNumber(), currentPosition.getGridColumnNumber()).blockCheck(checkingNumber) 
		&& GridRow(grid, currentPosition.getTotalRowIndex()).gridRowCheck(checkingNumber) 
		&& GridColumn(grid, currentPosition.getTotalColumnIndex()).gridColumnCheck(checkingNumber)
		);
}
int counting{ 0 }; //global variable for counting checking times. no other use. could be ignored!
constexpr int CHECKISOVER = 81; //magic number for end checking whether solvable or not

//main checking algorithm
//if 'currentPosition' is marked as initial go to next cell if positionIndex > 80 it means all cells are checked and check is over
//make check from 1
//positionIndex is the linear position for cells 0~80
//check is the number to check in cell
//
//the algorithms is as fallows
//if after some checking positionIndex goes negative it means all possible numbers checked 
//in first cell there is no acceptable solution. return CHECKISOVER
//if 'currentPosition' isn't marked as initial check if check is correct in currentPosition position
//if it doesn't and there is more number to check (check < 9) increase check by 1
//if there is no more number to check (check > 9) clear value of this cell go back to 
//previous NON initial cell (reduce positionIndex by at least 1) and increase that cell's value by one!
//if currentPosition isn't initial marked and check is a possible correct number
//change the value of positionIndex member of position and update grid (put the possible answer in grid)
//goto next positionIndex and make check from 1
//
void isCorrect(BlockGrid& grid, position_t& position, int& positionIndex, int& check)
{
	++counting;
	if (positionIndex < 0)
	{
		positionIndex = CHECKISOVER;
		return;
	}
	Position* currentPosition{ new Position }; //currentPosition
	*currentPosition = position.at(positionIndex);
	if (!currentPosition->getIsInitial())
	{
		if (!areRulesMet(grid, position, positionIndex, check))//if current check failed
		{
			if (!(check > 9)) //check if there is more number
			{
				delete currentPosition;
				++check;
				return;
			}
			else //run out of numbers go back to 1st previous non initial marked cell
			{
				//delete whatever possibly is in current cell 
				position.at(positionIndex).setValue(0);
				grid.getBlock(currentPosition->getGridRowNumber(), currentPosition->getGridColumnNumber()).memberSet({ currentPosition->getCellRow(), currentPosition->getCellColumn() }, 0);
				
				--positionIndex;
				if ((positionIndex < 0))
				{
					positionIndex = CHECKISOVER;
					return;
				}

				while (position.at(positionIndex).getIsInitial()) // go back to previous NON initial
				{
					--positionIndex;
					if ((positionIndex < 0))
					{
						positionIndex = CHECKISOVER;
						return;
					}
				}
				//std::cout << grid;
				check = position.at(positionIndex).getValue() + 1; //increase previous non initial cell by 1
				delete currentPosition;
				return;
			}
		}
		else  //if current check succeed
		{
			position.at(positionIndex).setValue(check);
			grid.getBlock(currentPosition->getGridRowNumber(), currentPosition->getGridColumnNumber()).memberSet({ currentPosition->getCellRow(), currentPosition->getCellColumn() }, check);
			delete currentPosition;
			check = 1;
			++positionIndex;
			return;
		}
	}
	else //if positionIndex is initial marked
	{
		if (positionIndex == 80) //if check is over
		{
			positionIndex = CHECKISOVER;
			return;
		}

		delete currentPosition; //if check goes on
		++positionIndex;
		check = 1;
		return;
	}
}

bool isSolvable(BlockGrid& grid, position_t& position, int& positionIndex, int& check)
{
	while (position.at(positionIndex).getIndex() <= 80)
	{
		isCorrect(grid, position, positionIndex, check);
		if ((positionIndex < 0 || positionIndex == CHECKISOVER))
		{
			positionIndex = CHECKISOVER;
			break;
		}

	}
	bool allDone{ true };
	for (auto i : position) //check if all cells are filled!
		if (i.getValue() == 0) allDone = false;
	return (allDone) ? true : false;
}

int main()
{
	//////////////////////////////////////////////
	////this is a confirmed solvable  puzzle	//    
	////it is caught from wikipedia on sudoko	// 
	////the answer is also there				//
	//Block a{ {{5,3,0},{6,0,0},{0,9,8}} };     //   
	//Block b{ {{0,7,0},{1,9,5},{0,0,0}} };		//
	//Block c{ {{0,0,0},{0,0,0},{0,6,0}} };		//
	//Block d{ {{8,0,0},{4,0,0},{7,0,0}} };		//
	//Block e{ {{0,6,0},{8,0,3},{0,2,0}} };		//
	//Block f{ {{0,0,3},{0,0,1},{0,0,6}} };		//
	//Block g{ {{0,6,0},{0,0,0},{0,0,0}} };		//
	//Block h{ {{0,0,0},{4,1,9},{0,8,0}} };		//
	//Block i{ {{2,8,0},{0,0,5},{0,7,9}} };		//
	//											//
	////creating grid of blocks					//
	//grid_t gr{ {{a,b,c},{d,e,f},{g,h,i}} };	//
	//BlockGrid test{ gr };						//
	////to use this table uncomment out this	//
	////block and comment out the following two //
	////two lines below							//
	//////////////////////////////////////////////
	BlockGrid test(true);//create zero filled grid -- no matter true or false it just called that constructor
	fillRandom(test); // this can be used to create random initial puzzle
	std::cout << test;

	//std::cout << test[{1, 1}];
	position_t positions(initaialPositions(test)); //initializing every cell data withe the initial puzzle
	int check{ 1 }; //starting check number it will change through the process
	int positionIndex{ 0 };//starting the checks from the first cell
	{// finding first non initial empty cell on grid
		int firstEmpty{ 0 };
		while (positions.at(firstEmpty).getIsInitial() == true) ++firstEmpty;
		positionIndex = firstEmpty;
	}
	if (isSolvable(test, positions, positionIndex, check)) //calling checking loop!
	{
		std::cout << "You have done it" << '\n' << "takes " << counting << " checking\n";
		std::cout << test;
	}
	else
		std::cout << "may be no resolution. checked "<< counting<<" times\n";

	return 0;
}