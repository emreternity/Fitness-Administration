#include "Person.h"
#include <string>
#include <iostream>
#include <stdexcept>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <mysql_error.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

using namespace std;

Person::Person(string _fname, string _lname, int _age, float _weight, float _height, string _birthdate) {
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

int Person::getID() const {
	return id;
}

void Person::seeValues() const{
	cout<<"First Name: "<<getFirstName()<<endl;
	cout<<"Last Name: "<<getLastName()<<endl;
	cout<<"Full Name: "<<getName()<<endl;
	cout<<"Age: "<<getAge()<<endl;
	cout<<"Weight: "<<getWeight()<<endl;
	cout<<"Height: "<<getHeight()<<endl;
	cout<<"Birthdate: "<<getBirthdate()<<endl;
	cout<<"Test Over."<<endl<<endl;
}

void Person::insertSQL(Connection* con){
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;
	pstmt = con->prepareStatement("INSERT INTO person(fname,lname,age,weight,height,birthdate) VALUES(?,?,?,?,?,?);");
	pstmt->setString(1, fname);
	pstmt->setString(2, lname);
	pstmt->setInt(3, age);
	pstmt->setDouble(4, weight);
	pstmt->setDouble(5, height);
	pstmt->setString(6, birthdate);
	pstmt->execute();
	
	pstmt = con->prepareStatement("SELECT MAX(id) FROM person;");
	result = pstmt->executeQuery();
	while (result->next())
	id = result->getInt(1);

	delete pstmt;
	delete result;
}

void Person::updateSQL(Connection* con){
	sql::PreparedStatement* pstmt;
		
	pstmt = con->prepareStatement("UPDATE person SET fname = ?,lname = ?,age = ?,weight = ?,height = ? ,birthdate = ? WHERE id = ?");
	pstmt->setString(1, fname);
	pstmt->setString(2, lname);
	pstmt->setInt(3, age);
	pstmt->setDouble(4, weight);
	pstmt->setDouble(5, height);
	pstmt->setString(6, birthdate);
	pstmt->setInt(7, id);
	pstmt->executeQuery();
	
	delete pstmt;
}
