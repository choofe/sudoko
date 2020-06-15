#include <iostream>
#include <vector>
#include "Block.h"
#include "BlockGrid.h"
#include "GridRow.h"
#include "GridCol.h"
#include "Position.h"

using position_t = std::vector<Position>; 

std::ostream& operator<<(std::ostream& out, const block_t& b)   //overloading << operator to print out a block of 1~9
{
	for (size_t  i{ 0 }; i < b.size(); ++i)
	{
		for (size_t j{ 0 }; j < b.at(i).size(); ++j)
		{
			out << b.at(i).at(j) << " ";
		}
		out << '\n';
	}
	out << '\n';
	return out;
}
//fill random cells of 'grid' with random value 1~9 and checks if it is acceptable in terms of sudoko 
//to form an initial puzzle. there is a magic number on line 32 >> determines how many 
//initial cells to be filled initially
void fillRandom(BlockGrid& grid)
{
	static std::mt19937 rand{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
	static std::uniform_int_distribution digit{ 1,9 };//uniform distribution bet
	static std::uniform_int_distribution cell{ 0,80 };//uniform distribution bet
	// magic number! i < VVVV determines how many initial cells would be prefilled in puzzle
	for (int i{ 1 }; i <= 20; ++i)
	{
		int randValue{ digit(rand) };			//random value to inset on grid
		int randCell{ cell(rand) };				//random position from 0~80 representing cells
		int gridRowNum{ randCell / 27 };		// block row position in block grid vector
		int gridColNum{ (randCell % 9) / 3 };	//block col position in block grid vector
		int cellRow{ (randCell / 9) % 3 };		//cell row in block vector
		int cellCol{ (randCell % 9) % 3 };		//cell col in block vector
		int totalRowIndex{ randCell / 9 };		//index of row in block grid
		int totalColIndex{ randCell % 9 };		//index of col in block grid

		//check if there is already a number and the rules are not broken if
		//fill the cell with randValue
		if (grid.getBlock(gridRowNum, gridColNum).memberAccess(cellRow, cellCol)== 0 &&
			grid.getBlock(gridRowNum, gridColNum).blockCheck(randValue) &&
			GridRow(grid, totalRowIndex).gridRowCheck(randValue) &&
			GridCol(grid, totalColIndex).gridColCheck(randValue))
		{
			grid.getBlock(gridRowNum, gridColNum).memberSet({ cellRow,cellCol }, randValue); //fill cell with randValue
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
	grid_t b{ grid.getGrid() };
	position_t init;
	
	init.reserve(81);//increase vector to 82 to reduce resizings
	
	for (size_t i{ 0 }; i <81; ++i) //fill initial values with 0 as empty cells
		init.push_back({ Position(i, 0) }); 

	for (size_t i{ 0 };i<init.size();++i)
	{
		///////////////////////////////////////////////////////////
		// fetch the value on grid in "i"th position . 
		//"i" have been already converted to grid row and cell and cell row and 
		//col and stored in i th member of vector init
		//////////////////////////////////////////////////////////
		int value{ b.at(init.at(i).getGridRowNum()).at(init.at(i).getGridColNum()). 
			getBlock().at(init.at(i).getCellRow()).at(init.at(i).getCellCol()) };   
		
		if (value != 0)// if there is an initial number in cell
		{
			init.at(i).setValue(value); //store the value

			init.at(i).setIsInitNum(true); //mark the position as initial.
		}
	}
	return init;
}

//checks the rules of sudoko 
//checks if 'checkingNum' in cell with 'posIndex' in 'grid' is a correct answer
//returns true id it is and false if it isn't
bool areRulesMet(BlockGrid& grid, position_t& pos, int posIndex, int checkingNum)
{
	Position curPos{ pos.at(posIndex) };
	return (
		checkingNum <= 9 
		&& grid.getBlock(curPos.getGridRowNum(), curPos.getGridColNum()).blockCheck(checkingNum) 
		&& GridRow(grid, curPos.getTotalRowIndex()).gridRowCheck(checkingNum) 
		&& GridCol(grid, curPos.getTotalColIndex()).gridColCheck(checkingNum)
		);
}
int counting{ 0 }; //global variable for counting checking times. no other use. could be ignored!
constexpr int CHECKISOVER = 81; //magic number for end checking whether solvable or not

//main checking algorithm
//if 'curPos' is marked as initial go to next cell if posIndex > 80 it means all cells are checked and chech is over
//make check from 1
//posIndex is the linear position for cells 0~80
//check is the number to check in cell
//
//the algorithms is as fallows
//if after some checking posIndex goes negative it means all possible numbers checked 
//in first cell there is no acceptable solution. return CHECKISOVER
//if 'curPos' isn't marked as initial check if check is correct in curPos position
//if it doen't and there is more number to check (check < 9) increase check by 1
//if there is no more number to check (check > 9) clear value of this cell go back to 
//previus NON initial cell (reduce posIndex by at least 1) and increase that cell's value by one!
//if curPos isn't initial marked abd check is a possible correct number
//chenge the value of posIndex member of pos and update grid (put the possible answer in grid)
//goto next posIndex and make check from 1
//
void isCorrect(BlockGrid& grid, position_t& pos, int& posIndex, int& check)
{
	++counting;
	if (posIndex < 0)
	{
		posIndex = CHECKISOVER;
		return;
	}
	Position* curPos{ new Position }; //currentPosition
	*curPos = pos.at(posIndex);
	if (!curPos->getIsInit())
	{
		if (!areRulesMet(grid, pos, posIndex, check))//if current check failed
		{
			if (!(check > 9)) //check if there is more number
			{
				delete curPos;
				++check;
				return;
			}
			else //run out of numbers go back to 1st previus non initial marked cell
			{
				Position* cPos{ new Position };
				*cPos = pos.at(posIndex);
				pos.at(posIndex).setValue(0);
				grid.getBlock(cPos->getGridRowNum(), cPos->getGridColNum()).memberSet({ cPos->getCellRow(), cPos->getCellCol() }, 0);
				delete cPos;
				--posIndex;
				if ((posIndex < 0))
				{
					posIndex = CHECKISOVER;
					return;
				}

				while (pos.at(posIndex).getIsInit()) // go back to previus NON initial
				{
					--posIndex;
					if ((posIndex < 0))
					{
						posIndex = CHECKISOVER;
						return;
					}
				}
				//std::cout << grid;
				check = pos.at(posIndex).getValue() + 1; //increase previus non initial cell by 1
				delete curPos;
				return;
			}
		}
		else  //if current check succeed
		{
			pos.at(posIndex).setValue(check);
			grid.getBlock(curPos->getGridRowNum(), curPos->getGridColNum()).memberSet({ curPos->getCellRow(), curPos->getCellCol() }, check);
			delete curPos;
			check = 1;
			++posIndex;
			return;
		}
	}
	else //if posIndex is initial marked
	{
		if (posIndex == 80) //if check is over
		{
			posIndex = CHECKISOVER;
			return;
		}

		delete curPos; //if check goes on
		++posIndex;
		check = 1;
		return;
	}
}

bool isSolvable(BlockGrid& grid, position_t& pos, int& posIndex, int& check)
{
	while (pos.at(posIndex).getIndex() <= 80)
	{
		isCorrect(grid, pos, posIndex, check);
		if ((posIndex < 0 || posIndex == CHECKISOVER))
		{
			posIndex = CHECKISOVER;
			break;
		}

	}
	bool allDone{ true };
	for (auto i : pos) //check if all cells are filled!
		if (i.getValue() == 0) allDone = false;
	if (allDone) return true;
	else return false;
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
	position_t positions(initaialPositions(test)); //initializing every cell data withe the initial puzzle
	int check{ 1 }; //starting check number it will change throgh the process
	int posIndex{ 0 };//starting the checks from the first cell
	{// finding first non initial empty cell on grid
		int firstEmpty{ 0 };
		while (positions.at(firstEmpty).getIsInit() == true) ++firstEmpty;
		posIndex = firstEmpty;
	}
	if (isSolvable(test,positions,posIndex,check)) //calling checking loop!
	{
		std::cout << "You have done it" << '\n' << "takes " << counting << " checking\n";
		std::cout << test;
	}
	else
		std::cout << "may be no resolution";

	return 0;
}