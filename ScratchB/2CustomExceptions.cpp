#include<iostream>
#include<string>
#include<exception>
using namespace std;

//3.Standard Exceptions

class canGoWrong {
public:
	canGoWrong() {
		char* pMemory = new char[99999999999999999];
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

}

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