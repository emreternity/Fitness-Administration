#include "Usable.h"
#include <string>
#include <stdexcept>
#include <algorithm>

Usable::Usable(int _capacity, const string &_name, Member _reserver, const string &_usableType = "equipment", const string &_accessLevel = "silver", bool _isReservable = true, bool _isReserved = false) 
	: isReserved(_isReserved), reserver(_reserver)
{
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
	transform(_usableType.begin(), _usableType.end(), _usableType.begin(), ::tolower);

	if (_usableType == "equipment" || _usableType == "pool" || _usableType == "sauna"){
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
	if (isReservable == true && isReserved == false) {
		isReserved = true;
		reserver = _reserver;
	}
	else {
		throw logic_error("Nesne rezerve edilmeye uygun degil.");
	}
}


void Usable::unreserve(Member _nullreserver){
	isReserved = false;
	reserver = _nullreserver;
}
