#include "Algorithm.h"


int g_counting{ 1 }; //global variable for g_counting checking times. no other use. could be ignored!

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

void isCorrect(BlockGrid& grid, position_t& position, int& positionIndex, int& check)
{
	++g_counting;
	if ((g_counting == 415))
	{
		std::cout<<"";
	}
	if (!(g_counting % 250000))
	{

		std::cout << "tried " << g_counting << " so far\n" << grid;
	}
	if (positionIndex < 0)
	{
		positionIndex = CHECKISOVER;
		return;
	}
	Position& currentPosition{ position.at(positionIndex) }; //currentPosition
	
	//int currentCheck{ currentPosition.getAvailableChecks().at(currentPosition.getCheckIndex()) };
	if (!currentPosition.getIsInitial())
	{
		if (!areRulesMet(grid, position, positionIndex, check))//if current check failed
		{
			if (currentPosition.isThereMoreNumber()) //checks if there is more number
			{
				currentPosition.goToNextCheck(); //increases checkIndex . next possible number
				check = currentPosition.getAvailableChecks().at(currentPosition.getCheckIndex());
				return;
			}
			else //run out of numbers go back to 1st previous non initial marked cell
			{
				//delete whatever possibly is in current cell 
				currentPosition.setValue(0);
				grid.getBlock(currentPosition.getGridRowNumber(), currentPosition.getGridColumnNumber()).memberSet({ currentPosition.getCellRow(), currentPosition.getCellColumn() }, 0);
				currentPosition.goToFirstCheck();
				--positionIndex;
				if ((positionIndex < 0))
				{
					positionIndex = CHECKISOVER;
					return;
				}

				while (position.at(positionIndex).getIsInitial() || !(position.at(positionIndex).isThereMoreNumber())) // go back to previous NON initial
				{
					Position& tempPosition{ position.at(positionIndex) };
					if (!tempPosition.getIsInitial())
					{
						tempPosition.setValue(0);
						tempPosition.goToFirstCheck();
						grid.getBlock(tempPosition.getGridRowNumber(), tempPosition.getGridColumnNumber()).memberSet({ tempPosition.getCellRow(),tempPosition.getCellColumn() }, 0);
					}
					--positionIndex;
					if ((positionIndex < 0))
					{
						positionIndex = CHECKISOVER;
						return;
					}
				}
				position.at(positionIndex).goToNextCheck();//next possible check on previous non initial increase previous non initial cell by 1
				check = position.at(positionIndex).getAvailableChecks().at(position.at(positionIndex).getCheckIndex());
				return;

			}
		}
		else  //if current check succeed
		{
			position.at(positionIndex).setValue(check);
			grid.getBlock(currentPosition.getGridRowNumber(), currentPosition.getGridColumnNumber()).memberSet({ currentPosition.getCellRow(), currentPosition.getCellColumn() }, check);
			++positionIndex;
			if (positionIndex == CHECKISOVER)
				return;
			check = position.at(positionIndex).getAvailableChecks().at(0);
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

		//if check goes on
		++positionIndex;
		check = position.at(positionIndex).getAvailableChecks().at(0);
		return;
	}
}


//void isCorrect(BlockGrid& grid, position_t& position, int& positionIndex, int& check)
//{
//	++g_counting;
//	/*if (counting > 250000)
//	{
//		positionIndex = CHECKISOVER;
//		return;
//	}*/
//	if (!(g_counting % 500000))
//	{
//
//		std::cout << "tried " << g_counting << " so far\n" << grid;
//	}
//	if (positionIndex < 0)
//	{
//		positionIndex = CHECKISOVER;
//		return;
//	}
//	Position* currentPosition{ new Position }; //currentPosition
//	*currentPosition = position.at(positionIndex);
//	if (!currentPosition->getIsInitial())
//	{
//		if (!areRulesMet(grid, position, positionIndex, check))//if current check failed
//		{
//			if (!(check > 9)) //check if there is more number
//			{
//				delete currentPosition;
//				++check;
//				return;
//			}
//			else //run out of numbers go back to 1st previous non initial marked cell
//			{
//				//delete whatever possibly is in current cell 
//				position.at(positionIndex).setValue(0);
//				grid.getBlock(currentPosition->getGridRowNumber(), currentPosition->getGridColumnNumber()).memberSet({ currentPosition->getCellRow(), currentPosition->getCellColumn() }, 0);
//
//				--positionIndex;
//				if ((positionIndex < 0))
//				{
//					positionIndex = CHECKISOVER;
//					return;
//				}
//
//				while (position.at(positionIndex).getIsInitial()) // go back to previous NON initial
//				{
//					--positionIndex;
//					if ((positionIndex < 0))
//					{
//						positionIndex = CHECKISOVER;
//						return;
//					}
//				}
//
//				check = position.at(positionIndex).getValue() + 1; //increase previous non initial cell by 1
//				delete currentPosition;
//				return;
//			}
//		}
//		else  //if current check succeed
//		{
//			position.at(positionIndex).setValue(check);
//			grid.getBlock(currentPosition->getGridRowNumber(), currentPosition->getGridColumnNumber()).memberSet({ currentPosition->getCellRow(), currentPosition->getCellColumn() }, check);
//			delete currentPosition;
//			check = 1;
//			++positionIndex;
//			return;
//		}
//	}
//	else //if positionIndex is initial marked
//	{
//		if (positionIndex == 80) //if check is over
//		{
//			positionIndex = CHECKISOVER;
//			return;
//		}
//
//		delete currentPosition; //if check goes on
//		++positionIndex;
//		check = 1;
//		return;
//	}
//}