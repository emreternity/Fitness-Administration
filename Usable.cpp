#include "Usable.h"
#include <string>
#include <stdexcept>
#include <algorithm>

Usable::isReserved = false;

Usable::Usable(int _capacity, const string &_name, const string &_usableType = "equipment", const string &_accessLevel = "silver", bool _isReservable = true, Member _reserver = Member("N/A","N/A",20,90,50,"01/01/2000","silver","nullreserver@gmail.com",1){
	setCapacity(_capacity);
	setName(_name);
	setUsableType(_usableType);
	setAccessLevel(_accessLevel);
	setIsReservable(_isReservable);
}

Usable::~Usable(){
	
}

void Usable::setCapacity(int _capacity){
	if (_capacity > 0){
		capacity = _capacity;
	}
	else{
		throw invalid_argument("Kapasite degeri sifirdan buyuk olmali.");
	} 
}

void Usable::setName(const string &_name){
	name = _name;
}

void Usable::setUsableType(const string &_usableType){
	transform(_usabletype.begin(), _usabletype.end(), _usabletype.begin(), ::tolower);
	if (_usableType == "equipment" || _usableType = "pool" || _usableType = "sauna"){
		usableType = _usableType;
	}
	else {
		throw invalid_argument("Gecersiz tip girisi.");
	}
}

void Usable::setAccessLevel(const string &_accessLevel){
	transform(_accessLevel.begin(), _accessLevel.end(), _accessLevel.begin(), ::tolower);
	if (_accessLevel != "silver" || _accessLevel != "gold" || _accessLevel != "platinum" || _accessLevel != "diamond" || _accessLevel != "employee"){
		throw invalid_argument("Erisim leveli mevcut degil.");
	}
	else {
		accessLevel = _accessLevel;
	}
}

void Usable::setIsReservable(bool _isReservable){
	isReservable = _isReservable;
}

void Usable::setReserver(Member _reserver){
	if (isReservable == true){
		reserver = _reserver;
		isReserved = true;
	}
	else {
		throw logic_error("Nesne rezerve edilmeye uygun degil.");
	}
}

int Usable::getCapacity() const{
	return capacity;
}

string Usable::getName() const{
	return name;
}

string Usable::getUsableType() const{
	return usableType;
}

string Usable::getAccessLevel() const{
	return accessLevel;
}

bool Usable::getIsReservable() const{
	return isReservable;
}

bool Usable::getIsReserved() const{
	return isReserved;
}

Member Usable::getReserver() const{
	return reserver;
}

void Usable::reserve(Member _reserver){
	if (isReservable == true){
		isReserved = true;
		reserver = _reserver;
	}
	else {
		throw logic_error("Nesne rezerve edilmeye uygun degil.");
	}
}

void Usable::unreserve(){
	isReserved = false;
	reserver = Member("N/A","N/A",20,90,50,"01/01/2000","silver","nullreserver@gmail.com",1);
}

string Usable::getReserverInfo() const{
	return reserver.fname + " " + reserver.lname + " - " + reserver.membertype; 
}
