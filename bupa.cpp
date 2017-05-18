#include "bupa.h"

using namespace std;

double normalize(double max, double min, double x) {
	return (x - min) / (max - min);
}

void parse_bupa_data(string filename, vector<bupa_data> &bupaDataset) {
	ifstream fileIn;
	fileIn.open(filename);
	if (fileIn.fail()) {
		cerr << "File not found\n";
		system("pause");
		exit(1);
	}

	else {
		bupa_data tempObject;
		string line;
		while (!fileIn.eof()) {
			getline(fileIn, line);
			istringstream s(line);
			string attributeString;
			int tempCount = 0;

			// Set the attributes of each instance to an object of class bupa_data
			for (unsigned int i = 0; i < 7; i++) {
				getline(s, attributeString, ',');
				double attributeDouble = atof(attributeString.c_str());
				switch (i) {
				case(0):
					tempObject.setMcv(attributeDouble);
					break;
				case(1):
					tempObject.setAlkphos(attributeDouble);
					break;
				case(2):
					tempObject.setSgpt(attributeDouble);
					break;
				case(3):
					tempObject.setSgot(attributeDouble);
					break;
				case(4):
					tempObject.setGammagt(attributeDouble);
					break;
				case(5):
					tempObject.setDrinks(attributeDouble);
					break;
				case(6):
					int attributeInt = atoi(attributeString.c_str());
					tempObject.setSelector(attributeInt-1);
					break;
				}
			}
			bupaDataset.push_back(tempObject);
			fileIn.peek();
		}
	}
}

void normalize_bupa_data(vector<bupa_data> bupaDataset) {
	double max, min;
	// tempVector stores 
	vector<double> tempVector;

	// Outer loop: iterate through list of attributes
	for (int a = 0; a < 6; a++) {
		// Inner loop: iterates at every attribute through dataset
		for (unsigned int line = 0; line < bupaDataset.size(); line++) {
			// Store the current attribute of the current object to a temporary vector
			switch (a) {
			case(0):
				tempVector.push_back(bupaDataset[line].mcv);
				break;
			case(1):
				tempVector.push_back(bupaDataset[line].alkphos);
				break;
			case(2):
				tempVector.push_back(bupaDataset[line].sgpt);
				break;
			case(3):
				tempVector.push_back(bupaDataset[line].sgot);
				break;
			case(4):
				tempVector.push_back(bupaDataset[line].gammagt);
				break;
			case(5):
				tempVector.push_back(bupaDataset[line].drinks);
				break;
			}
		}
		// Find the max and min values out of the dataset's current attribute index
		max = *max_element(tempVector.begin(), tempVector.end());
		min = *min_element(tempVector.begin(), tempVector.end());
		tempVector.clear();

		// After finding the max and min values, normalize value
		for (unsigned int line = 0; line < bupaDataset.size(); line++) {
			double n;
			switch (a) {
			case(0):
				n = normalize(max, min, bupaDataset[line].mcv);
				bupaDataset[line].setMcv(n);
				break;
			case(1):
				n = normalize(max, min, bupaDataset[line].alkphos);
				bupaDataset[line].setAlkphos(n);
				break;
			case(2):
				n = normalize(max, min, bupaDataset[line].sgpt);
				bupaDataset[line].setSgpt(n);
				break;
			case(3):
				n = normalize(max, min, bupaDataset[line].sgot);
				bupaDataset[line].setSgot(n);
				break;
			case(4):
				n = normalize(max, min, bupaDataset[line].gammagt);
				bupaDataset[line].setGammagt(n);
				break;
			case(5):
				n = normalize(max, min, bupaDataset[line].drinks);
				bupaDataset[line].setDrinks(n);
				break;
			}
		}
	}
}

void bupa_data::setMcv(double m) {
	mcv = m;
}

void bupa_data::setAlkphos(double a) {
	alkphos = a;
}

void bupa_data::setSgpt(double s) {
	sgpt = s;
}

void bupa_data::setSgot(double s) {
	sgot = s;
}

void bupa_data::setGammagt(double g) {
	gammagt = g;
}

void bupa_data::setDrinks(double d) {
	drinks = d;
}

void bupa_data::setSelector(int s) {
	selector = s;
}

int bupa_data::getClass_desc() {
	return selector;
}

double Euclidean(bupa_data A, bupa_data B) {
	double m = pow(A.mcv - B.mcv, 2.0);
	double a = pow(A.alkphos - B.alkphos, 2.0);
	double sp = pow(A.sgpt - B.sgpt, 2.0);
	double so = pow(A.sgot - B.sgot, 2.0);
	double g = pow(A.gammagt - B.gammagt, 2.0);
	double d = pow(A.drinks - B.drinks, 2.0);
	double dist = sqrt(m + a + sp + so + g + d);

	return dist;
}

double CosSim(bupa_data x, bupa_data y) {
	double d, den;	// denominator
	double dot = 0.0; // dot product of vector x and y
	double mag_x = 0.0; // magnitude of vector x
	double mag_y = 0.0; // magnitude of vector y

	// Calculate the dot product
	dot = (x.mcv * y.mcv) + (x.alkphos * y.alkphos) + (x.sgpt * y.sgpt) + (x.sgot * y.sgot) + (x.gammagt * y.gammagt) + (x.drinks * y.drinks);
	mag_x = (x.mcv * x.mcv) + (x.alkphos * x.alkphos) + (x.sgpt * x.sgpt) + (x.sgot * x.sgot) + (x.gammagt * x.gammagt) + (x.drinks * x.drinks);
	mag_y = (y.mcv * y.mcv) + (y.alkphos * y.alkphos) + (y.sgpt * y.sgpt) + (y.sgot * y.sgot) + (y.gammagt * y.gammagt) + (y.drinks * y.drinks);

	// Calculate the magnitude of x and y
	mag_x = sqrt(mag_x);
	mag_y = sqrt(mag_y);

	// Calculate the bottom of the cosine similarity equation
	den = mag_x * mag_y;

	// Return false if mag_x or mag_y were 0
	if (den == 0) {
		d = 0;
		return 0;
	}
	// else store the cosine similarity in d and return true
	else {
		d = dot / den;
		return d;
	}
}

double Pearson(bupa_data x, bupa_data y) {
	double avg_x, avg_y, var_x, var_y, covar, stdev_x, stdev_y, den, corr;
	avg_x = avg_y = var_x = var_y = covar = stdev_x = stdev_y = 0.0;

	// Calculate the average for x and y
	avg_x = (x.mcv + x.alkphos + x.sgpt + x.sgot + x.gammagt + x.drinks) / 6.0;
	avg_y = (y.mcv + y.alkphos + y.sgpt + y.sgot + y.gammagt + y.drinks) / 6.0;

	// Calculate the variance and covariance of x and y
	var_x = pow((x.mcv - avg_x), 2.0) + pow(x.alkphos - avg_x, 2.0) + pow(x.sgpt - avg_x, 2.0);
	var_x += pow(x.sgot - avg_x, 2.0) + pow(x.gammagt - avg_x, 2.0) + pow(x.drinks - avg_x, 2.0);
	var_y = pow((y.mcv - avg_y), 2.0) + pow(y.alkphos - avg_y, 2.0) + pow(y.sgpt - avg_y, 2.0);
	var_y += pow(y.sgot - avg_y, 2.0) + pow(y.gammagt - avg_y, 2.0) + pow(y.drinks - avg_y, 2.0);
	covar = ((x.mcv - avg_x)*(y.mcv - avg_y) + (x.alkphos - avg_x)*(y.alkphos - avg_y) + (x.sgpt - avg_x)*(y.sgpt - avg_y));
	covar += ((x.sgot - avg_x)*(y.sgot - avg_y) + (x.gammagt - avg_x)*(y.gammagt - avg_y) + (x.drinks - avg_x)*(y.drinks - avg_y));

	var_x /= 5;
	var_y /= 5;
	covar /= 5;

	// Calculate the standard deviation of x and y from their respective variance
	stdev_x = sqrt(var_x);
	stdev_y = sqrt(var_y);

	// Calculate the bottom of the correlation equation
	den = stdev_x*stdev_y;

	// If stdev_x or stdev_y were 0, return false
	if (den == 0) {
		corr = 0;
	}
	// else store the correlation in corr and return true
	else {
		corr = covar / den;
	}
	return corr;
}