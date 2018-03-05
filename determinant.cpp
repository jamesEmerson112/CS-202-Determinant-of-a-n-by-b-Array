/* An Thien Vo, CS 202 - 1001
* Homework #6
* This program will have a recursive function to
* find the determinant of an arbitrary n by n dynamic
* array.
*/

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

void printAuthorInfo();

double determinantFunction(double **, int);

int main()
{
	printAuthorInfo();

	double **array;						// declare the double pointer
	double temp;						// variable to hold the value to be written into the double pointer
	int size;							// variable to hold size of the dynamic array, the double pointer
	int coefficient_a = 0;				// variable to hold the column for the array
	int coefficient_b = 0;				// variable to hold the row for the array
	double answer = 0;					// variable to hold the supposed answer of the determinant of the array

	string filename;				
	cout << "Please enter the data name: " << endl;		// prompt the user to enter the name of the input files
	cin >> filename;
	ifstream input;										// declare the ifstream input
	input.open(filename.c_str());						// open input file

    input >> size;										// get size of the dynamic array
	if (size < 2)										// If size is less than 2, display the error message and end the program
	{
		cout << "The size must be greater than 1.";
		return (1);
	}

	array = new double*[size];							// construct the dynamic array

	for (int i = 0; i < size; i++)						// construct the dynamic array
		array[i] = new double[size];

	// initializing the dynamic array
	for (int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			array[i][j] = 0;

	// take the inputs for the dynamic array
	for (int i = 0; i < size*size; i++)
	{
		input >> temp;									// put input into variable temp
		array[coefficient_a][coefficient_b] = temp;		// array[column][row] = temp
		coefficient_b++;								// row++
		if (coefficient_b == size)						// if row == size, column++, row = 0
		{
			coefficient_a++;
			coefficient_b = 0;
		}
	}

	// display the dimension of the dynamic array to the user
	cout << "The array is an " << size << " by " << size
		 << " dynamic array. It is " << endl;

	// print the array so the user can see how the array looks like
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << array[i][j] << "\t";
		}
		cout << endl;
	}

	// print the determinant of this array
	cout << endl;
	cout << "The calculated determinant of this array is " << endl;
	cout << determinantFunction(array, size) << endl;

	// deconstruct the array
	for (int i = 0; i < size; i++)
		delete[] array[i];
	delete[] array;

	input.close();
	return 0;
}

/***************************************************************/
double determinantFunction(double **array, int size)
// The function determinantFunction has an argument of a double pointer
// and an integer size, which is the size of the dynamic array.
// This receursive function will find the determinant if size is either 1 or 2
// else it will create a double pointer array temp to hold the value of 
// the "smaller arrays" so that the determinantFunction can find the determinant
// of it. Then the resulted determinants will be multiplied with the first coefficient.
// The multiplication will be added with the next multiplication in the formula
// a[0][0] * (-1)^0 * determinantFunction + a[0][1] * (-1)^1 * determinantFunction + ...
// a[0][n] * (-1)^n * determinantFunction
{
	double determinant = 0;														// declare determinant
	double **temp;																// declare a two dimension array
	int coefficient_a;															// declare coefficient a
	int coefficient_b;															// declare coefficient b

	if (size == 1)																// if size == 1, return array[0][0]
		return array[0][0];
	else if (size == 2)															// if size == 2, return
	{
		determinant = array[0][0] * array[1][1] - array[0][1] * array[1][0];
		return array[0][0] * array[1][1] - array[0][1] * array[1][0];			// 00 * 11 - 01*10
	}
	else
	{

		// construct **temp
		temp = new double*[size];
		for (int i = 0; i < size; i++)
			temp[i] = new double[size];

		for (int primary = 0; primary < size; primary++)						// where primary stands for a[0][primary] * p^(-1) * determinantfunction....
		{		
			coefficient_a = 0;													// a represents the first coefficient of the temp array
			coefficient_b = 0;													// b represents the second coefficient of the temp array

			// These for loops will copy values from **array to temp[size][size]
			for (int i = 1; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					if (j == primary)
					{
						continue;												// this "continue" is to skip all coefficient that is the same as p, the removing
																				//	coefficient process
					} // end if statement
				//	else 
					// use the double pointer temp to hold the smaller array 
					// after removing coefficients process
						temp[coefficient_a][coefficient_b] = array[i][j];		// if j = 0, primary = 0,  temp[0][0] = array[1][1]
						coefficient_b++;										// so that next loop will be temp[0][1] = array[1][1]
						if (coefficient_b == size - 1)							// if b = size
						{
							coefficient_a++;									// a++, temp[1][size - 1]
							coefficient_b = 0;									// b = 0, temp[0][1]
						}
				} // end for loop
			} // end for loop
			
			// The indirect recursive process takes place.
				// a[0][0] * (-1)^0 * determinantFunction + a[0][1] * (-1)^1 * determinantFunction + ...
				// a[0][n] * (-1)^n * determinantFunction
			determinant = determinant
						  + array[0][primary] * pow(-1, primary) * determinantFunction(temp, size - 1);
		} // end for

		// deconstruct **temp
		for (int i = 0; i < size; i++)
			delete[] temp[i];
		delete[] temp;
		return determinant;
	} // end else
} // end determinantFunction

void printAuthorInfo()
// This function prints out the author's info
{
		//Print out the author's info
	cout << "An Thien Vo, CS 202 - 1001" << endl;
	cout << "Homework #6: This program will have a recursive function "
	     << endl
	     << "to find the determinant of an arbitrary n by n"
	     << endl
	     << "dynamic array."
	     << endl << endl;
}
