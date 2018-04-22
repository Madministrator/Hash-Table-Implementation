#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector> //needed for the whole class
#include <cmath> //needed for just the hash function
#include <iostream> //needed for just the print function

template <class T>
class HashTable
{
private:
	int count; //quantity of items in the Hash Table
	int max_size;
	std::vector<T>* list; //a pointer to an array of vectors, allowing for a staggered 2D array designed to handle hash collisions
	void copyHashTable(const HashTable<T> &otherHT)
	{
		//This hash table copies the properties of the other hash table
		this->count = otherHT.count;
		this->max_size = otherHT.max_size;
		//Transfering all the data from the other list to this list
		list = new std::vector<T>[max_size];
		for (int i = 0; i < max_size; i++)
			for (int x = 0; x < otherHT.list[i].size(); x++)
				this->list[i].push_back(otherHT.list[i].at(x));
	}

	/*
	Performs a hashing function. In this implementation, the hashing function is remarkably simple,
	especially when compared to the SHA-1 or SHA-2 hashes used by Google. The possibility of a
	collision with this hash function is much higher than those hashing functions because of
	its simplicity.

	This function can only handle data types that can be directly cast to integers. If you have a 
	custom data type, or a data type that cannot be converted into an integer, you need to 
	overload the function with a hash function that handles your data type. An overload for
	strings is already provided as an example.

	In essence, hash() returns an integer in range 0-max_size which serves as a "superIndex"
	to the 2D array "list[]" which enables the add, remove, search, and find functions to work.
	*/
	int hash(T data) const
	{
		int output;
		//First step: reduce the data to an int
		output = (int)data; //direct type conversion

		//Second step: constrain the int to bounds within the index of "list"
		output = abs(output); //ensure output is a positive integer
		output = output % this->max_size;
		//Third step: return the int
		return output;
	}
	//function overload to handle strings
	int hash(std::string data) const
	{
		int output = 0;
		//First step: reduce the string to an int by a summation of the numerical
		//representation of the characters in the string
		for (int i = 0; i < data.length(); i++)
			output += (int)data[i];
		
		//Second step: constrain the int to bounds within the index of "list"
		output = abs(output); //ensure output is a positive integer
		output = output % this->max_size;
		//Third step: return the int
		return output;
	}

	///Searches the vector at index within the list for a given element.
	///Returns the index of the element, or -1 if it isn't in the vector.
	int searchVector(int index, T element) const
	{
		for (int i = 0; i < this->list[index].size(); i++)
			if (this->list[index].at(i) == element)
				return i;
		return -1;
	}

public:
	HashTable(int max_size)
	{
		if (max_size < 1) //can't use an array with no space for data
			this->max_size = 100; //default value if given bad input
		else
			this->max_size = max_size; //the higher this number is, the less likely we are to have collisions

		this->count = 0;
		list = new std::vector<T>[this->max_size];
	}

	HashTable(const HashTable<T> &otherHT) //copy constructor
	{
		copyHashTable(otherHT);
	}

	~HashTable()
	{
		delete[] list;
	}

	HashTable<T>& operator = (const HashTable<T> &otherHT) const
	{
		copyHashTable(otherHT);
	}

	HashTable<T>& operator == (const HashTable<T> &otherHT) const
	{
		//comparing the non-list variables in the conditional
		if (this->count == otherHT.count && this->max_size == otherHT.max_size)
		{
			for (int i = 0; i < max_size; i++)
			{
				if (this->list[i].size() == otherHT.list[i].size())
				{
					for (int x = 0; x < this->list[i].size(); i++)
					{
						if (this->list[i].at(x) == otherHT.list[i].at(x))
							continue;
						else
							return false;
					}
				}
				else
					return false;
			}
			return true;
		}
		else
			return false;
	}

	///Adds element to the hash table
	void add(T element)
	{
		int index = hash(element);
		list[index].push_back(element); //Automatically handles collisions
		count++;
	}
	///Removes the element from the hash table
	///Returns true if the element was removed,
	///False if the element didn't exist
	bool remove(T element)
	{
		int* arr = find(element); 
		if (arr[0] == -1 || arr[1] == -1) //couldn't find element in list
			return false;
		else //Use the location of the element from find() to remove the data
		{
			std::vector<T> *bucket = &(this->list[arr[0]]); //Accessing the vector via a pointer for readability
			bucket->erase(bucket->begin() + arr[1]);
			count--;
			return true;
		}
	}

	///Removes an element from a specific coordinate in the HashTable
	///with location { superIndex, subIndex }
	///Returns true if the element was removed
	///Returns false if the coordinates were invalid
	bool remove(int superIndex, int subIndex)
	{
		if (superIndex >= 0 && superIndex < this->max_size)
		{
			if (subIndex >= 0 && subIndex < this->list[superIndex].size())
			{
				std::vector<T> *bucket = &(this->list[superIndex]); //Accessing the vector via a pointer for readability
				bucket->erase(bucket->begin() + subIndex);
				count--;
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}

	///Returns true if the element is in the HashTable, returns false otherwise
	bool search(T element) const
	{
		int index = hash(element);
		return (searchVector(index, element) != -1);
	}

	///Returns an array with two elements, these elements being the row and column of the location of element in the HashTable
	///Returns { -1, -1 } if the element is not in the Hash Table
	int* find(T element) const
	{
		int arr[2];
		if (search(element))//Element is in the hash table
		{
			arr[0] = hash(element);
			arr[1] = searchVector(arr[0], element);
		}
		else
		{
			arr[0] = -1;
			arr[1] = -1;
		}
		return arr;
	}

	///Returns the number of elements in the HashTable
	int size() const
	{
		return count;
	}

	///Print all existing data in the array of vectors to the terminal, skipping empty vectors
	void print() const
	{
		std::cout << "Contents of the HashTable: (contents not sorted)" << std::endl;
		for (int i = 0; i < max_size; i++)
		{
			if (!list[i].empty())//test if the vector is NOT empty
			{
				std::cout << "Index " << i << ": ";
				for (int x = 0; x < list[i].size(); x++)
					cout << list[i].at(x) << " ";
				std::cout << std::endl;
			}
		}
	}
};

#endif //HASHTABLE_H