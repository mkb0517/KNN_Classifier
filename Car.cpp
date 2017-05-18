#include "Car.h"

using namespace std;

Car::Car() 
	: buying(0.0), maint(0.0), doors(0.0), person(0.0), lug_boot(0.0), safety(0.0), class_desc(0) {}

Car::Car(double b, double m, double d, double p, double lb, double s, int cd) 
	: buying(b), maint(m), doors(d), person(p), lug_boot(lb), safety(s), class_desc(cd) {}

void Car::setBuying(double b) {
	buying = b;
}

void Car::setMaint(double m) {
	maint = m;
}

void Car::setDoors(double d) {
	doors = d;
}

void Car::setPerson(double p) {
	person = p;
}

void Car::setLug_boot(double lb) {
	lug_boot = lb;
}

void Car::setSafety(double s) {
	safety = s;
}

void Car::setClass_desc(int cd) {
	class_desc = cd;
}

int Car::getClass_desc(void) {
	return class_desc;
}

void parse_cars(string filename, vector<Car> &dataC) {
	string line, parsed;
	bool goOn = true;

	// Create a filestream
	ifstream inFile;
	{
		// open the file to load attribute values from
		inFile.open(filename);

		// Exit the program if the file is not there
		if (inFile.fail()) {
			cout << "File did not open" << endl;
			system("PAUSE");
			exit(-1);
		}

		// Extract information from the file
		while (goOn) {
			Car* temp = new Car;
			// Get a line from the file, each line is one car data vector
			getline(inFile, line);
			
			// Create a stringstream with the line data to parse and strip
			istringstream is(line);
			
			// Here we normalize and standardize our values to help with the data analysis
			for (int i = 0; i < 7; i++) {
				// Iterate through the stringstream and delimit using commas, as proper with a CSV
				getline(is, parsed, ',');
				// switch how we handle the parsed data based on our index
				// We can do this because the data file is preprocessed and follows a specific format
				switch (i) {
				// Case 0 is the first attribute: buying. It can have values of vhigh, high, med, and low 
				case 0:
					if (parsed.compare("vhigh") == 0) temp->setBuying(1.0);
					else if (parsed.compare("high") == 0) temp->setBuying(0.75);
					else if (parsed.compare("med") == 0) temp->setBuying(0.5);
					else if (parsed.compare("low") == 0) temp->setBuying(0.25);
					else cout << "BAD PRICE" << endl;
					break;
				// Case 1 is the second attribute: maintenance. It can have values of vhigh, high, med, and low
				case 1:
					if (parsed.compare("vhigh") == 0) temp->setMaint(1.0);
					else if (parsed.compare("high") == 0) temp->setMaint(0.75);
					else if (parsed.compare("med") == 0) temp->setMaint(0.5);
					else if (parsed.compare("low") == 0) temp->setMaint(0.25);
					else cout << "BAD MAINT" << endl;
					break;
				// Case 2 is the third attribute: doors. It can have values of 2, 3, 4, or 5more
				case 2:
					if (parsed.compare("2") == 0) temp->setDoors(1.0);
					else if (parsed.compare("3") == 0) temp->setDoors(0.75);
					else if (parsed.compare("4") == 0) temp->setDoors(0.5);
					else if (parsed.compare("5more") == 0) temp->setDoors(0.25);
					else cout << "BAD DOORS" << endl;
					break;
				// Case 3 is the fourth attribute: Person. It can have values of 2, 4, or more
				case 3:
					if (parsed.compare("2") == 0) temp->setPerson(1.0);
					else if (parsed.compare("4") == 0) temp->setPerson(2.0 / 3.0);
					else if (parsed.compare("more") == 0) temp->setPerson(1.0 / 3.0);
					else cout << "BAD PERSON" << endl;
					break;
				// case 4 is our fifth attribute: lug_boot. It can have values of small, med, big
				case 4:
					if (parsed.compare("small") == 0) temp->setLug_boot(1.0);
					else if (parsed.compare("med") == 0) temp->setLug_boot(2.0 / 3.0);
					else if (parsed.compare("big") == 0) temp->setLug_boot(1.0 / 3.0);
					else cout << "BAD LUGBOOT" << endl;
					break;
				// Case 5 is our sixth attribute: safety. It can have values of low, med and high
				case 5:
					if (parsed.compare("low") == 0) temp->setSafety(1.0);
					else if (parsed.compare("med") == 0) temp->setSafety(2.0 / 3.0);
					else if (parsed.compare("high") == 0) temp->setSafety(1.0 / 3.0);
					else cout << "BAD SAFETY" << endl;
					break;
				// Case 6 is our class. It can have values of unacc, acc, good, and vgood.
				case 6:
					if (parsed.compare("unacc") == 0) temp->setClass_desc(0);
					else if (parsed.compare("acc") == 0) temp->setClass_desc(1);
					else if (parsed.compare("good") == 0) temp->setClass_desc(2);
					else if (parsed.compare("vgood") == 0) temp->setClass_desc(3);
					else cout << "BAD CLASS" << endl;
					break;
				default:
					break;
				}
			}
			// Push back our car object into the car vector.
			dataC.push_back(*temp);
			// Check to see if we've reached the end of the file to prevent an extra iteration.
			inFile.peek();
			if (inFile.eof()) goOn = false;
		}
		inFile.close();
	}

}

double Euclidean(Car A, Car B) {
	double b = pow(A.buying - B.buying, 2.0);
	double m = pow(A.maint - B.maint, 2.0);
	double d = pow(A.doors - B.doors, 2.0);
	double p = pow(A.person - B.person, 2.0);
	double lb = pow(A.lug_boot - B.lug_boot, 2.0);
	double s = pow(A.safety - B.safety, 2.0);
	double dist = sqrt(b + m + d + p + lb + s);

	return dist;
}


double CosSim(Car x, Car y) {
	double d, den;	// denominator
	double dot = 0.0; // dot product of vector x and y
	double mag_x = 0.0; // magnitude of vector x
	double mag_y = 0.0; // magnitude of vector y

	// Calculate the dot product
	dot = (x.buying * y.buying) + (x.maint * y.maint) + (x.doors * y.doors) + (x.person * y.person) + (x.lug_boot * y.lug_boot) + (x.safety * y.safety);
	mag_x = (x.buying * x.buying) + (x.maint * x.maint) + (x.doors * x.doors) + (x.person * x.person) + (x.lug_boot * x.lug_boot) + (x.safety * x.safety);
	mag_y = (y.buying * y.buying) + (y.maint * y.maint) + (y.doors * y.doors) + (y.person * y.person) + (y.lug_boot * y.lug_boot) + (y.safety * y.safety);

	// Calculate the magnitude of x and y
	mag_x = sqrt(mag_x);
	mag_y = sqrt(mag_y);

	// Calculate the bottom of the cosine similarity equation
	den = mag_x * mag_y;

	// Return false if mag_x or mag_y were 0
	if (den == 0) {
		d = 0;
	}
	// else store the cosine similarity in d and return true
	else {
		d = dot / den;
	}
	return d;
}

double Pearson(Car x, Car y) {
	double avg_x, avg_y, var_x, var_y, covar, stdev_x, stdev_y, den, corr;
	avg_x = avg_y = var_x = var_y = covar = stdev_x = stdev_y = 0.0;

	// Calculate the average for x and y
	
	avg_x = (x.buying + x.maint + x.doors + x.person + x.lug_boot + x.safety)/6.0;
	avg_y = (y.buying + y.maint + y.doors + y.person + y.lug_boot + y.safety)/6.0;

	// Calculate the variance and covariance of x and y
	var_x = pow((x.buying - avg_x), 2.0) + pow(x.maint - avg_x, 2.0) + pow(x.doors - avg_x, 2.0);
	var_x += pow(x.person - avg_x, 2.0) + pow(x.lug_boot - avg_x, 2.0) + pow(x.safety - avg_x, 2.0);
	var_y = pow((y.buying - avg_y), 2.0) + pow(y.maint - avg_y, 2.0) + pow(y.doors - avg_y, 2.0);
	var_y += pow(y.person - avg_y, 2.0) + pow(y.lug_boot - avg_y, 2.0) + pow(y.safety - avg_y, 2.0);
	covar = ((x.buying - avg_x)*(y.buying - avg_y) + (x.maint - avg_x)*(y.maint - avg_y)+ (x.doors - avg_x)*(y.doors - avg_y));
	covar += ((x.person - avg_x)*(y.person - avg_y) + (x.lug_boot - avg_x)*(y.lug_boot - avg_y) + (x.safety - avg_x)*(y.safety - avg_y));

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