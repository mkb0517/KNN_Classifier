#pragma once
#ifndef CAR_H
#define CAR_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Car {
	double buying, maint, doors, person, lug_boot, safety;
	int class_desc;
public:
	/**
	 * Default Constructor for Car class. Initilizes everything to 0
	 */
	Car();
	/**
	 * Overloaded Constructfor for Car Class.
	 * Pre: Requires a standardized values for six attributes and a string for the class
	 * Post: Returns a populated object with overloaded values.
	 */
	Car(double, double, double, double, double, double, int);

	/**
	 * Mutator function for the Buying attribute
	 * Pre: Instantiated Car object and a value to change to
	 * Post: Modifies the buying attribute to the passed value
	 */
	void setBuying(double);

	/**
	* Mutator function for the Maintance attribute
	* Pre: Instantiated Car object and a value to change to
	* Post: Modifies the maintenance attribute to the passed value
	*/
	void setMaint(double);

	/**
	* Mutator function for the doors attribute
	* Pre: Instantiated Car object and a value to change to
	* Post: Modifies the doors attribute to the passed value
	*/
	void setDoors(double);

	/**
	* Mutator function for the person attribute
	* Pre: Instantiated Car object and a value to change to
	* Post: Modifies the person attribute to the passed value
	*/
	void setPerson(double);

	/**
	* Mutator function for the lug_boot attribute
	* Pre: Instantiated Car object and a value to change to
	* Post: Modifies the lug_boot attribute to the passed value
	*/
	void setLug_boot(double);

	/**
	* Mutator function for the safety attribute
	* Pre: Instantiated Car object and a value to change to
	* Post: Modifies the safety attribute to the passed value
	*/
	void setSafety(double);

	/**
	* Mutator function for the Class_desc attribute
	* Pre: Instantiated Car object and a value to change to
	* Post: Modifies the Class_desc attribute to the passed value
	*/
	void setClass_desc(int);

	/**
	* Accessor function to return the value of the Class_desc attribute
	* Pre: Instantiated Car object
	* Post: Returns the value of the Class_desc attribute
	*/
	int getClass_desc(void);

	/**
	 * friend function to parse the car data
	 * Pre: takes a csv file with car attributes and an empty car vector
	 * Post: Populates a vector of cars with the attributes from the file
	 */
	friend void parse_cars(string,vector<Car>&);

	/**
	 * Function to calculate the Euclidean distance between objects
	 * Pre: takes a test vector and a training vector of type Car
	 * Post: Returns the Euclidean distance between the two Car objects
	 */
	friend double Euclidean(Car, Car);

	/**
	* Function to calculate the Cosine Similarity between objects
	* Pre: takes a test vector and a training vector of type Car
	* Post: Returns the Cosine Similarity of the two Car objects
	*/
	friend double CosSim(Car, Car);

	/**
	* Function to calculate the Pearson Correlation between objects
	* Pre: takes a test vector and a training vector of type Car
	* Post: Returns the Pearson Correlation of the two Car objects
	*/
	friend double Pearson(Car, Car);
};

#endif