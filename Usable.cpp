#include "Usable.h"
#include <string>
#include <stdexcept>
#include <algorithm>

Usable::Usable(int _capacity, string _name, Member _reserver, string _usableType, string _accessLevel, bool _isReservable, bool _isReserved) 
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

void Usable::setName(string _name){
	name = _name;
}

void Usable::setUsableType(string _usableType){
	transform(_usableType.begin(), _usableType.end(), _usableType.begin(), ::tolower);

	if (_usableType == "equipment" || _usableType == "pool" || _usableType == "sauna"){
		usableType = _usableType;
	}
	else {
		throw invalid_argument("Gecersiz tip girisi.");
	}
}

void Usable::setAccessLevel(string _accessLevel){
	transform(_accessLevel.begin(), _accessLevel.end(), _accessLevel.begin(), ::tolower);
	if (_accessLevel == "silver" || _accessLevel == "gold" || _accessLevel == "platinum" || _accessLevel == "diamond" || _accessLevel == "employee"){
		accessLevel = _accessLevel;
	}
	else {
		throw invalid_argument("Erisim leveli mevcut degil.");
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

int Usable::getID() const {
	return id;
}


void Usable::seeValues() const{
	cout<<"Name: "<<getName()<<endl;
	cout<<"Type: "<<getUsableType()<<endl;
	cout<<"Acc. Level: "<<getAccessLevel()<<endl;
	cout<<"Capacity: "<<getCapacity()<<endl;
	cout<<"Is Reservable? "<<getIsReservable()<<endl;
	cout<<"Is Reserved? "<<getIsReserved()<<endl;
	cout<<"Reserver Name: "<<reserver.getName()<<endl;
	cout<<"Test Over."<<endl<<endl;
}

void Usable::insertSQL(Connection* con){
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;
	
	pstmt = con->prepareStatement("INSERT INTO usable(capacity,name,reserverName,usableType,accessLevel,isReservable,isReserved) VALUES(?,?,?,?,?,?,?);");
	pstmt->setInt(1, capacity);
	pstmt->setString(2, name);
	pstmt->setString(3, reserver.getName());
	pstmt->setString(4, usableType);
	pstmt->setString(5, accessLevel);
	pstmt->setBoolean(6, isReservable);
	pstmt->setBoolean(7, isReserved);
	pstmt->execute();
	
	pstmt = con->prepareStatement("SELECT MAX(id) FROM usable;");
	result = pstmt->executeQuery();
	while (result->next())
	id = result->getInt(1);

	delete pstmt;
	delete result;
}

void Usable::updateSQL(Connection* con){
	sql::PreparedStatement* pstmt;
		
	pstmt = con->prepareStatement("UPDATE usable SET capacity = ?,name = ?,reserverName = ?,usableType = ?,accessLevel = ? ,isReservable = ?, isReserved = ? WHERE id = ?");
	pstmt->setInt(1, _capacity);
	pstmt->setString(2, _name);
	pstmt->setString(3, _reserver.getName());
	pstmt->setString(4, _usableType);
	pstmt->setString(5, _accessLevel);
	pstmt->setBoolean(6, _isReservable);
	pstmt->setBoolean(7, _isReserved);
	pstmt->setInt(8, id);
	pstmt->executeQuery();
	
	delete pstmt;
}
