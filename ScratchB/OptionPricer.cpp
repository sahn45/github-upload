#include<iostream>
#include<vector>
#include<math.h>
#include<iterator>
#include<algorithm>
#include<boost/math/distributions/normal.hpp>
using boost::math::normal;


template <class T>
class EuropeanOption {
private:
	T S_, K_, r_, sig_, T_;

public:
	EuropeanOption(const T &S, const T &K, const T &r, const T &sig, const T &T) {
		std::cout << "Running my constructor..." << std::endl;
		S_ = S;
		K_ = K;
		r_ = r;
		sig_ = sig;
		T_ = T;
	
	}
	~EuropeanOption() {
		std::cout << "Running my destructor..." << std::endl;
	}
	void CallPricer_BSE();
	void CallPricer_BM();

};

template <class T>
void EuropeanOption<T>::CallPricer_BM() {
	std::cout << "Running Binomial Model call pricer..." << std::endl;

	std::vector<std::vector<float>> stock_matrix;
	std::vector<std::vector<float>> price_matrix;
	std::vector<float> temp_vec;

	int gridcount = 50;
	float u, q;
	u = exp(sig_*pow(T_ / gridcount, 0.5));
	q = (exp(r_*T_ / gridcount) - (1 / u)) / (u - 1 / u);

	for (int ia = 0;ia <= gridcount;ia++) {
		std::vector<float>(gridcount-ia + 1).swap(temp_vec);
		stock_matrix.push_back(temp_vec);
		price_matrix.push_back(temp_vec);
		for (int ib = 0;ib < price_matrix[ia].size();ib++) {
			stock_matrix[ia][ib] = S_*pow(u, price_matrix[ia].size() - ib)/pow(u, ib);
			std::cout << "stock price [" << ia << "][" << ib << "]: " << stock_matrix[ia][ib] << std::endl;
			if (ia == 0) {
				price_matrix[ia][ib] = std::max(stock_matrix[ia][ib]-K_,0.0f);
				std::cout << "call price [" << ia << "][" << ib << "]: " << price_matrix[ia][ib] << std::endl;
			}
			else {
				price_matrix[ia][ib] = price_matrix[ia - 1][ib] * q + price_matrix[ia - 1][ib + 1] * (1 - q);
				std::cout << "call price: [" << ia << "][" << ib << "]: " << price_matrix[ia][ib] << std::endl;
			}
		}
	}
	std::cout << "FINAL call price : " << price_matrix[gridcount][0] << std::endl;
}

template <class T>
void EuropeanOption<T>::CallPricer_BSE() {
	std::cout << "Running BSE call pricer..." << std::endl;
	normal sn(0,1);

	float d1 = (log(S_ / K_) + (r_ + 0.5*pow(sig_, 2)*T_)) / (sig_*pow(T_, 0.5));
	float d2 = d1 - sig_ * pow(T_, 0.5);
	float  thisprice;
	std::vector<float> result;

	std::cout << "S: " << S_ << std::endl;
	std::cout << "K: " << K_ << std::endl;
	std::cout << "r: " << r_ << std::endl;
	std::cout << "sig: " << sig_ << std::endl;
	std::cout << "T: " << T_ << std::endl;
	std::cout << "d1: " << d1 << std::endl;
	std::cout << "d2: " << d2 << std::endl;
	std::cout << "cdf(d1): " << cdf(sn, d1) << std::endl;
	std::cout << "cdf(d2): " << cdf(sn, d2) << std::endl;

	thisprice = S_ * cdf(sn, d1) - K_ * exp(-r_ * T_)*cdf(sn, d2);
	std::cout << "BSE call price: " << thisprice << std::endl;
	result.push_back(thisprice);

}

int main() {

	//std::vector<double> K{ 75, 95, 100, 105, 125 };

	EuropeanOption<float> d1(100,95,0.02,0.2,1);

	d1.CallPricer_BM();
	d1.CallPricer_BSE();

	//vector<double> call = BSE(S, K, r, sig, T);
	//for (auto it = call.begin(); it != call.end(); it++) {
	//	cout << "call price " << distance(call.begin(), it) << ": " << *it << endl;
	//}

	return 0;
}


	/*
vector<double> BSE(double S, vector<double> &K, double r, double sig, double T) {

	normal sn;
	vector<double> result;
	double thisprice;

	for (auto it = K.begin(); it != K.end(); it++) {
		double d1 = (log(S / (*it)) + (r + 0.5*pow(sig, 2)*T)) / (sig*pow(T, 0.5));
		double d2 = d1 - sig * pow(T, 0.5);

		cout << "S: " << S << endl;
		cout << "K: " << (*it) << endl;
		cout << "r: " << r << endl;
		cout << "sig: " << sig << endl;
		cout << "T: " << T << endl;
		cout << "d1: " << d1 << endl;
		cout << "d2: " << d2 << endl;
		cout << "cdf(d1): " << cdf(sn, d1) << endl;
		cout << "cdf(d2): " << cdf(sn, d2) << endl;

		thisprice = S * cdf(sn, d1) - (*it) * exp(-r * T)*cdf(sn, d2);
		cout << "call price: " << S * cdf(sn, d1) - (*it) * exp(-r * T)*cdf(sn, d2) << endl;
		result.push_back(thisprice);

	}

	return result;
}
*/



/*
int main(){

	auto pGreet = [](string name) {cout << "Hello " << name << endl; };

	pGreet("James");

	testGreet(pGreet);

	auto pDivide = [](double a, double b)-> double {

		if (b == 0.0){
			return 0;
		};
		return a / b;
	};

	cout << pDivide(10, 5) << endl;
	cout << pDivide(10, 0) << endl;

	runDivide(pDivide);

	return 0;
}
*/
/*
template<typename T, typename K>
class Test {
private:
	T obj;
public:
	Test(T obj) {
		this->obj = obj;
	}
	void print() {
		cout << obj << endl;
	}
};

template<typename T>
void print(T n) {
	cout << "template version: " << n << endl;
};

void print(int n) {
	cout << "non-template version: " << n << endl;
};

int main() {

	Test<string, int> test("Hello");
	test.print();
	print<>(5);

	return 0;
}
*/

/*
class Complex {
private:
	double real;
	double imaginary;

public:

	Complex() : real(0), imaginary(0) {};
	Complex(double real, double imaginary):real(real), imaginary(imaginary) {};
	Complex(const Complex &other) {
		real = other.real;
		imaginary = other.imaginary;

	}
	const Complex &operator=(const Complex &other) {
		real = other.real;
		imaginary = other.imaginary;

		return *this;
	}
	double getReal() const { return real; };
	double getImaginary() const { return imaginary; };
	friend ostream &operator<<(ostream &out, const Complex &c) {
		out << "(" << c.getReal() << "," << c.getImaginary() << ")";
		return out;
	};
	friend Complex operator+(const Complex &c1, const Complex &c2) {
		return Complex(c1.getReal() + c2.getReal(), c1.getImaginary() + c2.getImaginary());
	}
	friend Complex operator+(const Complex &c, const double &d) {
		return Complex(c.getReal() + d, c.getImaginary() );
	}
	friend Complex operator+(const double &d, const Complex &c) {
		return Complex(c.getReal() + d, c.getImaginary());
	}
	friend bool operator==(const Complex &c1, const Complex &c2) {
		return c1.getReal() == c2.getReal() && c1.getImaginary() == c2.getImaginary();
	}
	friend bool operator!=(const Complex &c1, const Complex &c2) {
		return !(c1.getReal() == c2.getReal() && c1.getImaginary() == c2.getImaginary());
	}
};

int main() {

	Complex c1(1,4);
	Complex c2 = c1;
	Complex c3(4,5);

	c2 = c1;

	cout << c2 << c1 << endl;

	cout << c1 + c2 +c3 << endl;

	cout << c1 + 5.2 << endl;
	cout << 5.2 + c1 << endl;
	
	if (c1 != c2) {
		cout << "not equals..." << endl;
	}
	else {
		cout << "equals..." << endl;
	}

	return 0;
}
*/
/*
class Test {
private:
	int id;
	string name;

public:
	Test():id(0), name("") {

	}
	Test(int id, string name) : id(id), name(name) {

	}
	void print() {
		cout << id << ": " << name << endl;
	}
	const Test &operator=(const Test &other) {

		cout << "Assignment running..." << endl;

		id = other.id;
		name = other.name;
		return *this;
	}
	Test(const Test &other) {
		cout << "Copy constructor running..." << endl;

		*this = other;
	}
	friend ostream &operator<< (ostream &out, const Test &test) {
		out << test.id << ": " << test.name;
		return out;
	}

};


int main() {

	Test test1(10, "Mike");
	Test test2(20, "Bob");

	cout << test1 << test2 << endl;

	return 0;
}
*/
/*
class Person {
private:
	string name;
	int age;

public:
	Person() : name(""), age(0) {
	}
	Person(string name, int age) :
		name(name), age(age) {
	}

	void print() {
		cout << name << ": " << age << endl;
	}

};

int main() {

	map<int, Person> people;

	people[0] = Person("Mike", 40);
	people[1] = Person("Vicky", 30);
	people[2] = Person("Raj", 20);

	for (map<int, Person>::iterator it = people.begin(); it != people.end(); it++) {
		it->second.print();
	}
	
	return 1;
}
*/

/*
int main() {

	vector<vector<int>> grid(3, vector<int>(4, 7));

	grid[1].push_back(8);

	for (int row=0; row < grid.size(); row++) {
		for (int col=0 ; col < grid[row].size();col++) {
			cout << grid[row][col] << flush;
		}

		cout << endl;
	}

	*/
	/*
	vector<string> strings;

	vector<double>	numbers(20);

	cout << "Size: " << numbers.size() << endl;

	int capacity = numbers.capacity();
	cout << "Capacity: " << capacity << endl;

	for (int i = 0; i < 10000; i++) {

		if (numbers.capacity() != capacity){

			capacity = numbers.capacity();
			cout << "Capacity: " << capacity << endl;
			
		}

		numbers.push_back(i);

	}

	numbers.clear();
	numbers.reserve(100000);
	capacity = numbers.capacity();

	cout << "Size: " << numbers.size() << endl;
	cout << "Capacity: " << capacity << endl;
	*/

	/*
	strings.push_back("one");
	strings.push_back("two");
	strings.push_back("three");

	for (int i = 0; i < strings.size(); i++) {
		cout << strings[i] << endl;
	}

	for (vector<string>::iterator it = strings.begin(); it != strings.end(); it++) {
		cout << *it << endl;
	}
	*/
	

/*
#pragma pack(push, 1)
#pragma pack(pop)

struct Person {
	char name[50];
	int age;
	double height;
};


int main() {

	Person someone = {"Frodo", 220, 0.8};

	string fileName = "test.bin";

	//Write Binary File

	ofstream outFile;

	outFile.open(fileName, ios::binary);

	if (outFile.is_open()) {

		outFile.write(reinterpret_cast<char*>(&someone), sizeof(Person));

		outFile.close();
	}
	else {

		cout << "Could not create: " << fileName << endl;
	}
	
	// Read Binary File
	Person someoneelse = {};

	ifstream inFile;

	inFile.open(fileName, ios::binary);

	if (inFile.is_open()) {

		inFile.read(reinterpret_cast<char*>(&someoneelse), sizeof(Person));

		inFile.close();
	}
	else {

		cout << "Could not read: " << fileName << endl;
	}

	cout << someoneelse.name << "," << someoneelse.age << "," << someoneelse.height << endl;

	return 0;
}
*/

/*
//6. Exception Order
void goesWrong() {
	bool error1Detected = false;
	bool error2Detected = true;

	if (error1Detected) {
		throw bad_alloc();
	}
	if (error2Detected) {
		throw exception();
	}

};

int main() {

	try {
		goesWrong();
	}
	catch (bad_alloc &e) {
		cout << "Catching bad alloc: " << e.what() << endl;
	}
	catch (exception &e) {
		cout << "Catching exception: "<< e.what() << endl;
	}


	return 0;
}
*/

/*
//3.Standard Exceptions
class canGoWrong {
public:
	canGoWrong() {
		char* pMemory = new char[999999999999999];
		delete[] pMemory;
	}

};


int main(){

	try {
		canGoWrong wrong;
	}
	catch(bad_alloc &e){
		cout << "Caught exception: " << e.what() << endl;
	}

	cout << "Still running..." << endl;

	return 0;

}
*/

/*
//2.Custom Exeptions
class MyException : public exception {

public:
	virtual const char* what() const throw() {
		return "Something bad happened...";
	}
};

class Test {
public:
	void goesWrong() {
		throw MyException();
	}
};

int main() {

	Test test;

	try {
		test.goesWrong();
	}
	catch (MyException &e) {
		cout << e.what() << endl;
	}

	return 0;
}
*/