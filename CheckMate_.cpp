// CheckMate_.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <cctype>

//The problem: Enter the coordinates of the black king, white king, white queen, white rook, white knight.
//The program should tell if there is a way out of mate if the game starts in black.
//Solution: The game will have not case of mate if and only if the game is in blockade situation at the start.
//Օtherwise there is always a case of mate when there is one king on the board and 4 pieces by the opponent,
//even when the King of Blacks takes one of the white pieces on the first step,there is a case of mate with the remaining 3 figures.


//Because there is only 5 figure I will not generate the board.

//Program description: At first, the player will enter the coordinates of the king of Blacks.
//Then the coordinates of the imported position will be kept in the vector.
//Then the player will enter the white coordinates, which will also be stored in the vector.
//Then it will be checked that all positions around black King are in check, the position of the king is not and 
//The Black king cannot take any white pieces


//The Black King class
class Black_King
{
protected:
	std::vector<std::vector<int>> reserved_indices; //vector for reserving coordinates around black King
private:
	void input()
	{
		do {
			char index1; //The first index that is number on board
			//I want to remind that actual board does not exist, we only will check that the first index in the range of a to g and 
			//the second index in the range of 1 to 8.
			std::cout << "Enter the Black King indices:";
			std::cin >> index1 >> reserved_indices[0][1];
			reserved_indices[0][0] = tolower(index1);
			//We save coordinates of The Black King in the first element of the vector, 
			//if it is in uppercase we will convert it to lowercase.
			//when we assign int to char, it is implicitly converted to int
			//a is converted to 97 and g is converted to 104
		} while (!Range_Validator()); //Via this function, we check that indices are in the range
	}
	bool Range_Validator() const
	{
		return (reserved_indices[0][0] >= 97 && reserved_indices[0][0] <= 104 && reserved_indices[0][1] >= 1 && reserved_indices[0][1] <= 8);
	}
	//Via this function, we check that all indices around Black King are in the range, 
	//if the indices are in the range it will be added in the vector via Reserve_Around function
	bool Range_Validator(const int index1, const int index2) const
	{
		return (index1 >= 97 && index1 <= 104 && index2 >= 1 && index2 <= 8);
	}
	void Reserve_Around()
	{
		int i = 1;
		if (Range_Validator(reserved_indices[0][0], reserved_indices[0][1] + 1))
		{
			reserved_indices[i][0] = reserved_indices[0][0]; //boxes that are attached to the Black King's box (*)
			reserved_indices[i][1] = reserved_indices[0][1] + 1;//(*)
			++i;
		}
		if (Range_Validator(reserved_indices[0][0] + 1, reserved_indices[0][1] + 1))
		{
			reserved_indices[i][0] = reserved_indices[0][0] + 1;//(*)
			reserved_indices[i][1] = reserved_indices[0][1] + 1;//....
			++i;
		}
		if (Range_Validator(reserved_indices[0][0] + 1, reserved_indices[0][1]))
		{
			reserved_indices[i][0] = reserved_indices[0][0] + 1;
			reserved_indices[i][1] = reserved_indices[0][1];
			++i;
		}
		if (Range_Validator(reserved_indices[0][0] + 1, reserved_indices[0][1] - 1))
		{
			reserved_indices[i][0] = reserved_indices[0][0] + 1;
			reserved_indices[i][1] = reserved_indices[0][1] - 1;
			++i;
		}
		if (Range_Validator(reserved_indices[0][0], reserved_indices[0][1] - 1))
		{
			reserved_indices[i][0] = reserved_indices[0][0];
			reserved_indices[i][1] = reserved_indices[0][1] - 1;
			++i;
		}
		if (Range_Validator(reserved_indices[0][0] - 1, reserved_indices[0][1] - 1))
		{
			reserved_indices[i][0] = reserved_indices[0][0] - 1;
			reserved_indices[i][1] = reserved_indices[0][1] - 1;
			++i;
		}
		if (Range_Validator(reserved_indices[0][0] - 1, reserved_indices[0][1]))
		{
			reserved_indices[i][0] = reserved_indices[0][0] - 1;
			reserved_indices[i][1] = reserved_indices[0][1];
			++i;
		}
		if (Range_Validator(reserved_indices[0][0] - 1, reserved_indices[0][1] + 1))
		{
			reserved_indices[i][0] = reserved_indices[0][0] - 1;
			reserved_indices[i][1] = reserved_indices[0][1] + 1;
		}
		reserved_indices.resize(i);
	}
public:

	//Ctor for The Black King
	Black_King() :reserved_indices(9, std::vector<int>(2)) {
		input();
		Reserve_Around();
	}

};
//White pieces are inherited from the Black King, as they added the following functionality to the class of the  Black King:
//the whites can defeat the Black King
class Test :Black_King
{
private:
	//In string we store the name of the white pieces, in the vector, we store coordinates of that pieces
	std::vector<std::pair<std::string, std::vector<int>>> white_pieces;
	//Do the same as the Black_King class input only have a few additional functionalities
	//we pass parametr to indicate which chess figure is current
	void input(const int i)
	{
		bool kings_valid = true;
		if (i == 0)
		{
			kings_valid = false; //If we insert indecis of the White King we have to chack that it is not attached to the Black King's cage
		}
		do {
			char index1;
			std::cout << "Enter the " << white_pieces[i].first << " indices:";
			std::cin >> index1 >> white_pieces[i].second[1];
			index1 = tolower(index1);
			white_pieces[i].second[0] = index1;
			if (!kings_valid)
			{
				kings_valid = min_max_checking_and_testing(0, 0);//here we check kings validation
			}
			//the indices must be in the range and should not be repeated
		} while (!kings_valid || !Range_Validator(i) || !Repetition_Validator(i));
	}

	//This function checks whether the given figure is hitting the given cage
	//The coordinates of the cage are determined by the first parameter and the figure by the second parameter
	bool min_max_checking_and_testing(const int reserved_index, const int pieces_index, int k = -1) const
	{
		//determines which of the coordinates of each cage is greater and lesser
		//because we didn't keep a board
		const int& index1_max = (reserved_indices[reserved_index][0] <= white_pieces[pieces_index].second[0]) ? white_pieces[pieces_index].second[0] : reserved_indices[reserved_index][0];
		const int& index1_min = (reserved_indices[reserved_index][0] <= white_pieces[pieces_index].second[0]) ? reserved_indices[reserved_index][0] : white_pieces[pieces_index].second[0];
		const int& index2_max = (reserved_indices[reserved_index][1] <= white_pieces[pieces_index].second[1]) ? white_pieces[pieces_index].second[1] : reserved_indices[reserved_index][1];
		const int& index2_min = (reserved_indices[reserved_index][1] <= white_pieces[pieces_index].second[1]) ? reserved_indices[reserved_index][1] : white_pieces[pieces_index].second[1];
		//pieces_index determines which white figure is being observed and, accordingly, 
		//calculates that it is hitting to the cage determined by the first parameter.
		if (pieces_index == 0 || k == -2)
		{
			if (((index1_max == index1_min) && ((index2_max - index2_min) == 1)) || ((index2_max == index2_min) && ((index1_max - index1_min) == 1)) || ((index1_max == index1_min + 1) && (index2_max == index2_min + 1)))
				return false;
			else return true;
		}
		else if (pieces_index == 1 && k != -3)
		{
			if ((index1_max - index1_min) == (index2_max - index2_min))
			{
				for (int i = 0; i < 4; ++i)
				{
					if (i == 1)
						continue;
					if (white_pieces[i].second[0] > index1_min && white_pieces[i].second[0]<index1_max &&  white_pieces[i].second[1]>index2_min && white_pieces[i].second[1] < index2_max && ((white_pieces[i].second[0] - index1_min) == (white_pieces[i].second[1] - index2_min)))
					{
						return false;
					}
				}
				return true;
			}
			else
			{
				return false;
			}
		}

		else if ((pieces_index == 1 || pieces_index == 2) && k == -3)
		{
			for (int i = 0; i < 4; ++i)
			{
				if (i == 1 || i == 2)
					continue;
				if (white_pieces[i].second[0] == index1_max || white_pieces[i].second[1] == index2_max)
				{
					const int& overlapping_index = (white_pieces[i].second[0] == index1_max) ? index1_max : index2_max;
					const int& index = (white_pieces[i].second[0] == overlapping_index) ? white_pieces[i].second[1] : white_pieces[i].second[0];
					const int& max = (index1_max == overlapping_index) ? index2_max : index1_max;
					const int& min = (index1_min == overlapping_index) ? index2_min : index1_min;
					if (index > min && index < max)
						return false;
				}
			}
			return true;
		}
		else if (pieces_index == 3)
			return ((((index1_min + 2) == index1_max) && ((index2_min + 1) == index2_max)) || ((index1_min + 1 == index1_max) && (index2_min + 2 == index2_max)));
	}
	//checks whether the indices are within the board
	bool Range_Validator(const int i) const
	{
		return (white_pieces[i].second[0] >= 97 && white_pieces[i].second[0] <= 104 && white_pieces[i].second[1] >= 1 && white_pieces[i].second[1] <= 8);
	}
	//checks whether the indices are repeated or not
	bool Repetition_Validator(const int i) const
	{
		for (int j = 0; j <= i; ++j)
		{
			if (white_pieces[i].second[0] == reserved_indices[0][0] && white_pieces[i].second[1] == reserved_indices[0][1])
				return false;
			if (i != j && white_pieces[j].second[0] == white_pieces[i].second[0] && white_pieces[j].second[1] == white_pieces[i].second[1])
				return false;
		}
		return true;
	}
	//These functions determine whether there is a check by the figure in the function name
	bool in_one_line(const int reserved_index, const int pieces_index) const
	{
		return (reserved_indices[reserved_index][0] == white_pieces[pieces_index].second[0] || reserved_indices[reserved_index][1] == white_pieces[pieces_index].second[1]) && min_max_checking_and_testing(reserved_index, pieces_index, -3);
	}
	bool Check_from_white_king(const int reserved_index) const
	{
		return !min_max_checking_and_testing(reserved_index, 0);
	}
	bool Check_from_white_queen(const int reserved_index) const
	{
		if (in_one_line(reserved_index, 1))
			return true;
		return min_max_checking_and_testing(reserved_index, 1);
	}
	bool Check_from_white_rook(const int reserved_index) const
	{
		return in_one_line(reserved_index, 2);
	}
	bool Check_from_white_knight(const int reserved_index) const
	{
		return min_max_checking_and_testing(reserved_index, 3);
	}
	bool In_Checked(const int reserved_index, const int pieces_index = -1) const
	{
		if (pieces_index == 1)
		{
			return (Check_from_white_king(reserved_index) || Check_from_white_rook(reserved_index) || Check_from_white_knight(reserved_index));
		}
		else if (pieces_index == 2)
		{
			return (Check_from_white_king(reserved_index) || Check_from_white_queen(reserved_index) || Check_from_white_knight(reserved_index));

		}
		else if (pieces_index == 3)
		{
			return (Check_from_white_king(reserved_index) || Check_from_white_queen(reserved_index) || Check_from_white_rook(reserved_index));
		}
		else
		{
			return (Check_from_white_king(reserved_index) || Check_from_white_queen(reserved_index) || Check_from_white_rook(reserved_index) || Check_from_white_knight(reserved_index));
		}
	}
public:
	//ctor for white pieces
	Test() :white_pieces(4)
	{
		white_pieces[0].first = "White King";
		white_pieces[0].second.resize(2);
		input(0);
		white_pieces[1].first = "White Queen";
		white_pieces[1].second.resize(2);
		input(1);
		white_pieces[2].first = "White Rook";
		white_pieces[2].second.resize(2);
		input(2);
		white_pieces[3].first = "White Knight";
		white_pieces[3].second.resize(2);
		input(3);
	}
	//Returns true if around the Black King is checked
	bool All_Black_King_Reserved_Are_In_Checked() const
	{
		for (int reserved_index = 1; reserved_index < reserved_indices.size(); ++reserved_index)
		{
			if (!In_Checked(reserved_index))
				return false;
		}
		return true;
	}
	//Returns true if the Black King position are not checked
	bool Black_King_Position_Are_Not_Checked() const
	{
		if (!In_Checked(0))
			return true;
		return false;
	}
	//returns true if the Black King can take one of the white pieces
	bool Black_King_Have_Chance_Spoil_Situation() const
	{
		for (int pieces_index = 1; pieces_index < white_pieces.size(); ++pieces_index)
		{
			if (!min_max_checking_and_testing(0, pieces_index, -2))
			{
				for (int reserved_index = 1; reserved_index < reserved_indices.size(); ++reserved_index)
				{
					if (white_pieces[pieces_index].second[0] == reserved_indices[reserved_index][0] && white_pieces[pieces_index].second[1] == reserved_indices[reserved_index][1])
					{
						if (!In_Checked(reserved_index, pieces_index))
							return true;
					}
				}
			}
		}
		return false;
	}
};
class Chess_Game
{
private:
	Test white_pieces;
public:
	//Chess_Game() : white_pieces(){}
	//returns true if there is no case of ending the game with mat
	bool Test() const
	{

		if (white_pieces.All_Black_King_Reserved_Are_In_Checked() && white_pieces.Black_King_Position_Are_Not_Checked() && !white_pieces.Black_King_Have_Chance_Spoil_Situation())
		{
			std::cout << "Blockade situation, NO case of ending the game with MAT \n";
			return true;
		}
		else
		{
			std::cout << "The game HAS a case of MAT \n";
			return false;
		}
	}
};
int main()
{
	//test for the game
	for (int i = 0; i < 5; ++i)
	{
		Chess_Game obj;
		obj.Test();
	}
}