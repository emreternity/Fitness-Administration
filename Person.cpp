#include "Person.h"
#include <string>
#include <iostream>

using namespace std;

Person::Person(const string &_fname, const string &_lname, int _age, float _weight, float _height, const string &_birthdate) {
	setFirstName(_fname);
	setLastName(_lname);
	setAge(_age);
	setWeight(_weight);
	setHeight(_height);
	setBirthdate(_birthdate);
}

Person::~Person() {

}

void Person::setFirstName(string _fname) {
	if (_fname.length() < 1 || _fname.length() > 18)
	{
		throw invalid_argument("Isim cok uzun ya da cok kisa.");
	}
	else {
		fname = _fname;
	}
}

string Person::getFirstName() const {
	return fname;
}

void Person::setLastName(string _lname) {
	if (_lname.length() < 1 || _lname.length() > 18)
	{
		throw invalid_argument("Soyisim cok uzun ya da cok kisa.");
	}
	else {
		lname = _lname;
	}
}

string Person::getLastName() const {
	return lname;
}

void Person::setAge(int _age) {
	if (_age < 14 || _age > 65) {
		throw invalid_argument("GYM uyeligimiz icin yasiniz uygun degildir.");
	}
	else {
		age = _age;
	}
}

int Person::getAge() const {
	return age;
}

void Person::setWeight(float _weight) {
	if (_weight < 30 || _weight > 300) {
		throw invalid_argument("Lutfen gecerli bir kilo degeri giriniz.");
	}
	else {
		weight = _weight;
	}
}

float Person::getWeight() const {
	return weight;
}

void Person::setHeight(float _height) {
	if (_height < 100 || _height > 250) {
		throw invalid_argument("Lutfen gecerli bir boy degeri giriniz.");
	}
	else {
		height = _height;
	}
}

float Person::getHeight() const {
	return height;
}

void Person::setBirthdate(string _birthdate) {
	birthdate = _birthdate;
}

string Person::getBirthdate() const {
	return birthdate;
}

string Person::getName() const {
	return fname + " " + lname;
}
