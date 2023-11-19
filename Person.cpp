#include "Person.h"
#include <string>
#include <iostream>

#include "sqlstuff.h"


using namespace std;


Person::Person(string _fname, string _lname, int _age, float _weight, float _height, string _birthdate) {

	tryCon();
	schemaFunc();

	pstmt = con->prepareStatement("INSERT INTO person(fname,lname,age,weight,height,birthdate) VALUES(?,?,?,?,?,?)");
	pstmt->setString(1, _fname);
	pstmt->setString(2, _lname);
	pstmt->setInt(3, _age);
	pstmt->setDouble(4, _weight);
	pstmt->setDouble(5, _height);
	pstmt->setString(6, _birthdate);
	pstmt->execute();

	delete pstmt;

	pstmt = con->prepareStatement("SELECT MAX(id) FROM person;");
	result = pstmt->executeQuery();
	while (result->next())
	id = result->getInt(1);

	delete result;
	delete pstmt;
}

Person::~Person() {
	pstmt = con->prepareStatement("DELETE FROM person WHERE id = ?");
	pstmt->setInt(1, id);
	
	delete pstmt;
}

void Person::setFirstName(string _fname) {
	if (_fname.length() < 1 || _fname.length() > 18)
	{
		throw invalid_argument("Isim cok uzun ya da cok kisa.");
	}
	else {
		pstmt = con->prepareStatement("UPDATE person SET fname = ? WHERE id = ?");
		pstmt->setString(1, _fname);
		pstmt->setInt(2, id);
		pstmt->executeQuery();
		delete pstmt;
	}
}

string Person::getFirstName() const {
	pstmt = con->prepareStatement("SELECT fname FROM person WHERE id = ?;");
	pstmt->setInt(1, id);
	result = pstmt->executeQuery();
	while (result->next())
	return result->getString(1);
	delete result;
}

void Person::setLastName(string _lname) {
	if (_lname.length() < 1 || _lname.length() > 18)
	{
		throw invalid_argument("Soyisim cok uzun ya da cok kisa.");
	}
	else {
		pstmt = con->prepareStatement("UPDATE person SET lname = ? WHERE id = ?");
		pstmt->setString(1, _lname);
		pstmt->setInt(2, id);
		pstmt->executeQuery();
		delete pstmt;
	}
}

string Person::getLastName() const {
	pstmt = con->prepareStatement("SELECT lname FROM person WHERE id = ?;");
	pstmt->setInt(1, id);
	result = pstmt->executeQuery();
	while (result->next())
	return result->getString(1);
	delete result;
}

void Person::setAge(int _age) {
	if (_age < 14 || _age > 65) {
		throw invalid_argument("GYM uyeligimiz icin yasiniz uygun degildir.");
	}
	else {
		pstmt = con->prepareStatement("UPDATE person SET age = ? WHERE id = ?");
		pstmt->setInt(1, _age);
		pstmt->setInt(2, id);
		pstmt->executeQuery();
		delete pstmt;
	}
}

int Person::getAge() const {
	pstmt = con->prepareStatement("SELECT age FROM person WHERE id = ?;");
	pstmt->setInt(1, id);
	result = pstmt->executeQuery();
	while (result->next())
	return result->getInt(1);
	delete result;
}

void Person::setWeight(float _weight) {
	if (_weight < 30 || _weight > 300) {
		throw invalid_argument("Lutfen gecerli bir kilo degeri giriniz.");
	}
	else {
		pstmt = con->prepareStatement("UPDATE person SET weight = ? WHERE id = ?");
		pstmt->setDouble(1, _weight);
		pstmt->setInt(2, id);
		pstmt->executeQuery();
		delete pstmt;
	}
}

float Person::getWeight() const {
	pstmt = con->prepareStatement("SELECT weight FROM person WHERE id = ?;");
	pstmt->setInt(1, id);
	result = pstmt->executeQuery();
	while (result->next())
	return result->getDouble(1);
	delete result;
}

void Person::setHeight(float _height) {
	if (_height < 100 || _height > 250) {
		throw invalid_argument("Lutfen gecerli bir boy degeri giriniz.");
	}
	else {
		pstmt = con->prepareStatement("UPDATE person SET height = ? WHERE id = ?");
		pstmt->setDouble(1, _height);
		pstmt->setInt(2, id);
		pstmt->executeQuery();
		delete pstmt;
	}
}

float Person::getHeight() const {
	pstmt = con->prepareStatement("SELECT height FROM person WHERE id = ?;");
	pstmt->setInt(1, id);
	result = pstmt->executeQuery();
	while (result->next())
	return result->getDouble(1);
	delete result;
}

void Person::setBirthdate(string _birthdate) {
	pstmt = con->prepareStatement("UPDATE person SET birthday = ? WHERE id = ?");
	pstmt->setString(1, _birthdate);
	pstmt->setInt(2, id);
	pstmt->executeQuery();
	delete pstmt;
}

string Person::getBirthdate() const {
	pstmt = con->prepareStatement("SELECT birthdate FROM person WHERE id = ?;");
	pstmt->setInt(1, id);
	result = pstmt->executeQuery();
	while (result->next())
	return result->getString(1);
	delete result;
}

string Person::getName() const {
	pstmt = con->prepareStatement("SELECT fname,lname FROM person WHERE id = ?;");
	pstmt->setInt(1, id);
	result = pstmt->executeQuery();
	while (result->next())
	return result->getString(1) + result->getString(2);
	delete result;
}


void Person::setID(int _id) {
	pstmt = con->prepareStatement("UPDATE person SET id = ? WHERE id = ?");
	pstmt->setInt(1, _id);
	pstmt->setInt(2, id);
	pstmt->executeQuery();
	delete pstmt;
	id = _id;
}

int Person::getID() const {
	return id;
}