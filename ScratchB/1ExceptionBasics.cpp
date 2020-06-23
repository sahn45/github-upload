#include<iostream>
#include<string>
using namespace std;

void mightGoWrong() {

	bool error1 = 0;
	bool error2 = 1;

	if (error1) {
		throw 5;
	}
	if (error2) {
		throw "Something went wrong...";
	}

}


int main() {
	try {
		mightGoWrong();
	}
	catch (int e) {
		cout << "Error code: " << e << endl;
	}
	catch (const char& e) {
		cout << "Error code: " << e << endl;
	}
	catch (string& e) {
		cout << "Error code: " << e << endl;
	}


	cout << "Still running..." << endl;

	return 0;
}