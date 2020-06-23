#include<iostream>
#include<string>
using namespace std;

void mightGoWrong() {

	bool error1 = true;
	bool error2 = true;

	if (error1) {
		throw "Something went wrong...";
	}
	if (error2) {
		throw string("Something went wrong...");
	}

}


int main() {
	try {
		mightGoWrong();
	}
	catch (int e) {
		cout << "Error code: " << e << endl;
	}
	catch (const char* e) {
		cout << "Error code: " << e << endl;
	}
	catch (string& e) {
		cout << "Error code: " << e << endl;
	}


	cout << "Still running..." << endl;

	return 0;
}