#include <iostream>
#include <string>

using std::string;
using std::cout, std::endl;
//using std::endl;

class Phone {
protected:
	string name;
	string sery;
	string date;
public:
	Phone(){};
	Phone(string n, string s, string d) :name{ n }, sery{ s }, date{ d } {}
	//Phone(const Phone& other);
	//Phone operator=(const Phone& other);
	string getName() { return name; }
	string getSery() { return sery; }
	string getDate() { return date; }
	void Info() {
		cout << "Name: " << name << endl;
		cout << "Series: " << sery << endl;
		cout << "Date: " << date << endl;
	}
};

class Android_Phone : public Phone {
	string android_verion;
public:
	Android_Phone() {};
	Android_Phone(string n, string s, string d, string a) : Phone(n, s, d), android_verion(a) {};
	Android_Phone(const Android_Phone& other) {
		name = other.name;
		sery = other.sery;
		date = other.date;
		android_verion = other.android_verion;
	};
	void Info() {
		cout << "Name: " << name << endl;
		cout << "Series: " << sery << endl;
		cout << "Date: " << date << endl;
		cout << "Version: " << android_verion << endl;
	}
};

//Phone::Phone(const Phone& other) {
//	name = other.name;
//	sery = other.sery;
//	date = other.date;
//}

//Phone Phone::operator=(const Phone& other) {
//	name = "default";
//	sery = "default";
//	date = "default";
//	return *this;
//}

int main() {
	Phone phone1("Huawei", "P50", "12/4/2020");
	auto phone2 = phone1;
	Phone phone3{ phone2 };
	Phone phone4(phone2);
	Phone phone5;
	phone5 = phone2;
	phone1.Info();
	phone2.Info();
	phone3.Info();
	phone4.Info();
	phone5.Info();

	Android_Phone aphone1("Huawei", "P50", "12/4/2020", "12.2.3");
	auto aphone2 = aphone1;
	Android_Phone aphone3(aphone1);
	Android_Phone aphone4;
	aphone4 = aphone1;
	aphone1.Info();
	aphone2.Info();
	aphone3.Info();
	aphone4.Info();


}