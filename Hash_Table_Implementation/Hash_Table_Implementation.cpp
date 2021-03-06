// Hash_Table_Implementation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HashTable.h"
#include <iostream>
using namespace std;

//FLAG: FUNCTION PROTOTYPES
int promptChoice();
int promptSize();

int main()
{
	//declaring variables
	HashTable<int> ht(promptSize());
	int choice;

	cout << "For the purposes of this proof-of-concept: this hash table accepts only ints" << endl << endl;
	while (true)
	{
		choice = promptChoice();

		switch (choice)
		{
		case 1: //Add data
			cout << "what integer would you like to add? ";
			cin >> choice;
			ht.add(choice);
			break;
		case 2: //Remove data
			cout << "How would you like to remove your data?" << endl
				<< "1. Remove by content (search for data, and erase the first match)" << endl
				<< "2. Remove by location (given the coordinate of a piece of data, erase it)" << endl
				<< "Your choice? ";
			cin >> choice;
			while (choice < 1 || choice > 2) //input validation
			{
				cout << "Your choice? (1 or 2) ";
				cin >> choice;
			}
			if (choice == 1) //remove by content
			{
				cout << "What integer would you like to remove? ";
				cin >> choice;
				ht.remove(choice);
			}
			else //remove by location
			{
				int superIndex, subIndex;
				cout << "Coordinate format: { superIndex, subIndex }" << endl
					<< "What is the superIndex? ";
				cin >> superIndex;
				cout << "What is the subIndex? ";
				cin >> subIndex;
				ht.remove(superIndex, subIndex);
			}
			break;
		case 3: //Check if data is in the HashTable
			cout << "What integer are you looking for? ";
			cin >> choice;
			if (ht.search(choice))
				cout << choice << " is in the Hash Table";
			else
				cout << choice << " is not in the Hash Table";
			break;
		case 4: //Get the location of data within the Hash Table
			cout << "What integer are you looking for? ";
			cin >> choice;
			if (ht.search(choice)) //Target integer is in the hash table
			{
				int *arr = ht.find(choice);
				cout << choice << " can be found at: { " << arr[0] << ", " << arr[1] << " }";
			}
			else
				cout << choice << " is not in the Hash Table";
			break;
		case 5: //Get the quantity of data within the Hash Table
			cout << "The Hash Table has " << ht.size() << " elements.";
			break;
		case 6: //Print all data in the Hash Table
			cout << endl; //whitespace
			ht.print();
			break;
		case 7: //Quit the application
			return 0;
		default:
			cout << "Something went wrong: Default case called";
			break;
		}
		cout << endl;
		system("pause");
		cout << endl << endl; //white space between iterations
		
	}
	system("pause");
    return 0;
}

int promptChoice()
{
	int input;
	cout << "What would you like to do to the Hash Table?" << endl
		<< "1. Add data" << endl
		<< "2. Remove data" << endl
		<< "3. Check if data is in the Hash Table" << endl
		<< "4. Get the location of data within the Hash Table" << endl
		<< "5. Get the quantity of data within the Hash Table" << endl
		<< "6. Print all data in the Hash Table" << endl
		<< "7. Quit the application (closes the window)" << endl
		<< "Your choice? ";
	cin >> input;
	while (input < 1 || input > 7) //input validation
	{
		cout << "That is not in the range of valid choices\nPlease enter a number between 1 and 7, inclusive: ";
		cin >> input;
	}
	return input;
}

int promptSize()
{
	int input;
	cout << "What would you like the initial size of the Hash Table to be? ";
	cin >> input;
	while (input < 1) //input validation
	{
		cout << "Please enter a realistic value for an array size (a number >= 1): ";
		cin >> input;
	}
	system("CLS"); //data has been gathered and won't be needed again, might as well clear the screen.
	return input;
}