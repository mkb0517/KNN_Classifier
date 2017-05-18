/**
*	bupa.h
*	header file for bupa dataset
*/

#pragma once
#ifndef BUPA_H
#define BUPA_H
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>
using namespace std;

/**
*	class for bupa dataset
*	stores dataset attributes as private member variables
*/
class bupa_data {
private:
	double mcv, alkphos, sgpt, sgot, gammagt, drinks;
	int selector;
public:
	/**
	 * Mutator function for the mcv attribute.
	 * Pre: Takes a double to set the value to.
	 * Post: Sets the value of mcv to the passed value.
	 */
	void setMcv(double);

	/**
	* Mutator function for the alkphos attribute.
	* Pre: Takes a double to set the value to.
	* Post: Sets the value of alkphos to the passed value.
	*/
	void setAlkphos(double);

	/**
	* Mutator function for the sgpt attribute.
	* Pre: Takes a double to set the value to.
	* Post: Sets the value of sgpt to the passed value.
	*/
	void setSgpt(double);

	/**
	* Mutator function for the sgot attribute.
	* Pre: Takes a double to set the value to.
	* Post: Sets the value of sgot to the passed value.
	*/
	void setSgot(double);

	/**
	* Mutator function for the gammagt attribute.
	* Pre: Takes a double to set the value to.
	* Post: Sets the value of gammagt to the passed value.
	*/
	void setGammagt(double);

	/**
	* Mutator function for the drinks attribute.
	* Pre: Takes a double to set the value to.
	* Post: Sets the value of drinks to the passed value.
	*/
	void setDrinks(double);

	/**
	* Mutator function for the selector.
	* Pre: Takes a double to set the value to.
	* Post: Sets the value of selector to the passed value.
	*/
	void setSelector(int);

	/**
	* Accessor function for the selector attribute.
	* Pre: needs a bupa object to call from
	* Post: Returns the value of selector
	*/
	int getClass_desc(void);

	/**
	*	Function to read and parse bupa dataset
	*	Pre: Takes a filename and an empty vector
	*	Post: Stores parsed attributes into vector of objects
	*/
	friend void parse_bupa_data(string, vector<bupa_data>&);
	/**
	*	Function to begin normalizing bupa dataset
	*	Pre: Sends a populated vector containing attribute values from bupa dataset
	*	Post: Sets normalized value to each object
	*/
	friend void normalize_bupa_data(vector<bupa_data>);

	/**
	* Function to calculate the euclidean Euclidean between two vectors of data
	* Pre: Takes two populated vectors and their size
	* Post: Returns the Euclidean
	*/
	friend double Euclidean(bupa_data, bupa_data);

	/**
	* Function to calculate the cosine similarity between two vectors of data
	* Pre: Takes two populated vectors and their size
	* Post: Returns true if there is no division by zero and stores the value in a passed parameter
	*/
	friend double CosSim(bupa_data, bupa_data);

	/**
	* Function to calculate the Pearson correlation between two vectors of data
	* Pre: Takes two populated vectors and their size
	* Post: Returns true if there is no division by zero and stores the value in a passed parameter
	*/
	friend double Pearson(bupa_data, bupa_data);
};

/**
*	Function to return a normalized value
*	Pre: Takes the max value, min value, and the current index value
*	Post: Returns normalized value of index value
*/
double normalize(double, double, double);

#endif