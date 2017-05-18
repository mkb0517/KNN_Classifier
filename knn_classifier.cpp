#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

#include "Car.h"
#include "bupa.h"

using namespace std;

/**
 * Basic input function to sanitize user input
 * Pre: Takes a variable to be populated
 * Post: Variable is populated with a correct type
 */
template<typename T>
void input(T&);

template<class T, class S>
void intro(int&, int&, int&, vector<T>&, vector<T>&, vector<S>&, vector<S>&);

/**
 * Function to sort two vectors in tandem. Used for similarity measures that want smaller differences.
 * Pre: takes two populated vectors of k neighbors, one double with attribute measures, one int with indices of data objects
 * Post: returns the sorted vectors from high to low attribute measures.
 */
void my_sort_low(int, vector<double>&, vector<int>&);

/**
 * Function to sort two vectors in tandem. Used for similarity measures that want larger (closer to 1) differences.
 * Pre: Takes two populated vectors of k neighbors, one double with attribute measures, one int with indices of data objects.
 * Post: Returns the sorted vectors from low to high attribute measures.
 */
void my_sort_high(int, vector<double>&, vector<int>&);

template<class T>
void knn(int, vector<T>&, vector<T>&, vector<int>&, int);

/**
 * Main body
 */
int main() {
	bool repeat = true;
	bool goOn = true;
	char option;

	do {
		// Variable declarations
		bool swap = false;
		int set, method, k;
		vector<Car> carTrain, carTest;
		vector<int> carClass = { 0, 1, 2, 3 };
		vector<bupa_data> bupaTrain, bupaTest;
		vector<int> bupaClass = { 0, 1 };

		intro(set, method, k, bupaTrain, bupaTest, carTrain, carTest);

		// If they choose the first set, call KNN with bupa information
		if (set == 1) {
			knn(k, bupaTrain, bupaTest, bupaClass, method);
		}
		// else call KNN with the car information.
		else knn(k, carTrain, carTest, carClass, method);

		goOn = true;
		cout << endl << "Would you like to do it again? (y or n) ";
		while (goOn) {
			input(option);
			option = tolower(option);
			if (option != 'y' && option != 'n') {
				cout << "Please enter y or n! ";
			}
			else {
				goOn = false;
			}
		}
		if (option == 'n') repeat = false;
		else cout << endl;
	} while (repeat);


	system("PAUSE");
	return 0;
}

template<typename T>
void input(T &value) {
	bool goOn = true;
	// loop until valid input is given
	while (goOn) {
		cin >> value;
		if (!cin.good()) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please enter a valid value!" << endl;
		}
		else {
			goOn = false;;
		}
	}
}

/**
 * Function to get user input to analyze the data set.
 * Pre: Asks for the data set, whether to swap the training and test set, the method to analyze, and the number of neighbors
 * Post: Sets up the data vectors for the knn function.
 */
template<class T, class S>
void intro(int &set, int &method, int &k, vector<T>&bupaTrain, vector<T>&bupaTest, vector<S>&carTrain, vector<S>&carTest) {
	bool goOn = true;
	bool swap = false;
	char option;
	int upperbound;
	// Ask user for the data set they would like to analyze
	cout << "Which data set do you want to see?" << endl;
	cout << "1. Bupa" << endl;
	cout << "2. Cars" << endl;
	while (goOn) {
		cout << "-> ";
		input(set);
		if (set != 1 && set != 2)
			cout << "Please enter 1 or 2! " << endl;
		else goOn = false;
	}

	// Ask the user if they would like to swap the training and test set
	goOn = true;
	cout << endl << "Would you like to swap the training and test set? (y or n) ";
	while (goOn) {
		input(option);
		option = tolower(option);
		if (option != 'y' && option != 'n') {
			cout << "Please enter y or n! ";
		}
		else {
			goOn = false;
		}
	}
	if (option == 'y') swap = true;
	if (!swap) {
		if (set == 1) {
			parse_bupa_data("bupa_data_trainset.csv", bupaTrain);
			parse_bupa_data("bupa_data_testset.csv", bupaTest);
			upperbound = bupaTrain.size();
		}
		else {
			parse_cars("car_data_trainset.csv", carTrain);
			parse_cars("car_data_testset.csv", carTest);
			upperbound = carTrain.size();
		}
	}
	else {
		if (set == 1) {
			parse_bupa_data("bupa_data_testset.csv", bupaTrain);
			parse_bupa_data("bupa_data_trainset.csv", bupaTest);
			upperbound = bupaTrain.size();
		}
		else {
			parse_cars("car_data_testset.csv", carTrain);
			parse_cars("car_data_trainset.csv", carTest);
			upperbound = carTrain.size();
		}
	}

	// Ask user for the method they would like to use to analyze the data set.
	goOn = true;
	cout << endl << "Which Method would you like to use to analyze the data?" << endl;
	cout << "1. Euclidean Distance - measures the distance between attributes." << endl;
	cout << "2. Cosine Similarity - measures the degree of difference between attributes." << endl;
	cout << "3. Pearson Correlation - measures the covariance between the two." << endl;
	while (goOn) {
		cout << "-> ";
		input(method);
		if (method != 1 && method != 2 && method != 3) {
			cout << "Please enter 1, 2, or 3!!" << endl;
		}
		else goOn = false;
	}

	// Ask the user how many neighbors they would like to use to analyze the data set.
	goOn = true;
	cout << endl << "How many neighbors would you like to validate the classification? ";
	while (goOn) {
		input(k);
		if (k <= 0 || k > upperbound) {
			cout << "Please enter a number that's within the range of the set!" << endl;
		}
		else goOn = false;
	}
}

void my_sort_low(int k, vector<double> &nearest, vector<int> &index) {
	bool goOn = true;
	// While we're still making changes to the vector, repeat
	while (goOn) {
		goOn = false;
		for (int i = 0; i < k-1; i++) {
			if (nearest[i] < nearest[i + 1]) {
				// swap the values of the attributes
				double temp = nearest[i];
				nearest[i] = nearest[i + 1];
				nearest[i + 1] = temp;
				// swap the values of the indices to match the attributes
				int swap = index[i];
				index[i] = index[i + 1];
				index[i + 1] = swap;
				goOn = true;
			}
		}
	}
}

void my_sort_high(int k, vector<double> &nearest, vector<int> &index) {
	bool goOn = true;
	while (goOn) {
		goOn = false;
		for (int i = 0; i < k - 1; i++) {
			// if we have a value in the front greater, move it to the back
			if (nearest[i] > nearest[i + 1]) {
				// move values of attributes
				double temp = nearest[i];
				nearest[i] = nearest[i + 1];
				nearest[i + 1] = temp;
				// move the values of the index to match
				int swap = index[i];
				index[i] = index[i + 1];
				index[i + 1] = swap;
				goOn = true;
			}
		}
	}
}

template<class T>
void knn(int k, vector<T> &trainSet, vector<T> &testSet, vector<int> &classifier, int method) {
	vector<vector<int>> neighbors, conf_matrix;
	vector<int> predicted, TP, FP, FN, TN;

	// for each item in our test set
	for (unsigned i = 0; i < testSet.size(); i++) {
		double diff;
		vector<double> nearest; // nearest keeps track of the similarity measure of a training set object.
		vector<int> index;		// index keeps track of the index in the training set that 

		// initialize our nearest and index vectors to find the k nearest neighbors.
		if (method == 1) {
			for (int i = 0; i < k; i++) {
				nearest.push_back(200.0);
				index.push_back(0);
			}
		}
		else {
			for (int i = 0; i < k; i++) {
				nearest.push_back(0.0);
				index.push_back(0);
			}
		}

		// For every object in the training set
		for (unsigned j = 0; j < trainSet.size(); j++) {
			// Run the similarity measure that the user chose
			if (method == 1)
				diff = Euclidean(testSet[i], trainSet[j]);
			else if (method == 2)
				diff = CosSim(testSet[i], trainSet[j]);
			else
				diff = Pearson(testSet[i], trainSet[j]);

			// check to see if our difference is more significant the the previous values
			for (int n = 0; n < k; n++) {
				if (method == 1) {
					if (diff < nearest[n]) {
						nearest[n] = diff;
						index[n] = j;
						break;
					}
				}
				else {
					if (diff > nearest[n]) {
						nearest[n] = diff;
						index[n] = j;
						break;
					}
				}
			}
			// Sort our current nearest neighbors in order of significance 
			if (method == 1)
				// Euclidean distances are better if they're lower
				my_sort_low(k, nearest, index);
			else
				// Pearson Correlation and Cosing Similarity want larger differences
				my_sort_high(k, nearest, index);
		}
		// store the neighbors of the i-th test vector
		neighbors.push_back(index);
	}
	
	// Classify our test vectors
	for (unsigned i = 0; i < testSet.size(); i++) {
		vector<int> trainClass;
		// initialize our current vector classifier
		for (unsigned n = 0; n < classifier.size(); n++) {
			trainClass.push_back(0);
		}

		// Sum the classes of the k closest training vectors
		for (int j = 0; j < k; j++) {
			for (unsigned n = 0; n < classifier.size(); n++) {
				if (trainSet[neighbors[i][j]].getClass_desc() == classifier[n]) {
					trainClass[n]++;
				}
			}
		}

		// Determing which training class is the greatest.
		int max = 0;
		int ind = 0;
		for (unsigned n = 0; n < classifier.size(); n++) {
			if (trainClass[n] > max) {
				max = trainClass[n];
				ind = n;
			}
		}
		// Store the predicted classfier for the i-th vector in the i-th index of a predicted vector
		predicted.push_back(classifier[ind]);
	}

	// Calculate the accuracy, precision, and recall of the set
	for (unsigned i = 0; i < classifier.size(); i++) {
		vector<int> row;
		// initialize our truth vectors and confusion matrix
		for (unsigned j = 0; j < classifier.size(); j++) {
			row.push_back(0);
			TP.push_back(0);
			FP.push_back(0);
			FN.push_back(0);
			TN.push_back(0);
		}
		conf_matrix.push_back(row);
	}
	
	// Determine our TruePositive, FalsePositive, FalseNegative, and totalTP from the test set
	int totalTP = 0;
	for (unsigned i = 0; i < predicted.size(); i++) {
		// if the predicted class matches the actual class, increment TP
		if (testSet[i].getClass_desc() == predicted[i]) {
			conf_matrix[predicted[i]][predicted[i]]++;
			TP[predicted[i]]++;
			totalTP++;
		}
		// otherwise increment the False Positive and False Negative of the corresponding vectors
		else {
			conf_matrix[testSet[i].getClass_desc()][predicted[i]]++;
			FP[predicted[i]]++;
			FN[testSet[i].getClass_desc()]++;
		}
	}
	// Calculate the True Negatives: TN = SetSize - TP - FP - FN
	for (int i = 0; i < classifier.size(); i++) {
		TN[i] = predicted.size() - TP[i] - FP[i] - FN[i];
	}
	// Calculate and output the statistics
	// TotalAccuracy = (TP + TN) / (TP + TN + FP + FN) = totalTP / set.size()
	cout << endl << "The accuracy of the set is: " << static_cast<double>(totalTP) / predicted.size() << endl << endl;
	for (unsigned i = 0; i < classifier.size(); i++) {
		// ClassAccuracy = totalTP / (totalTP + TP_i + FP_i + FN_i)
		cout << "The accuracy of the class " << i + 1 << " is: ";
		cout << static_cast<double>(TP[i]+TN[i]) / predicted.size() << endl;
		// Precision = TP_i / (TP_i + FP_i)
		cout << "The precision of the class " << i + 1 << " is: " << static_cast<double>(TP[i]) / (TP[i] + FP[i]) << endl;
		// Recall = TP_i / (TP_i + FN_i)
		cout << "The recall of the class " << i + 1 << " is: " << static_cast<double>(TP[i]) / (TP[i] + FN[i]) << endl;
		cout << endl;
	}
	cout << "Confusion Matrix" << endl;
	for (unsigned i = 0; i < conf_matrix.size(); i++) {
		for (unsigned j = 0; j < conf_matrix.size(); j++) {
			cout << conf_matrix[i][j] << "\t";
		}
		cout << endl;
	}
}