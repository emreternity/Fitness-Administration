#include "Usable.h"
#include <string>
#include <stdexcept>
#include <algorithm>

#include "sqlstuff.h"

Usable::Usable(int _capacity, string _name, Member _reserver, string _usableType, string _accessLevel, bool _isReservable, bool _isReserved) 
	: reserver(_reserver)
{
	tryCon();
	schemaFunc();

	pstmt = con->prepareStatement("INSERT INTO usable(capacity,name,reserverName,usableType,accessLevel,isReservable,isReserved) VALUES(?,?,?,?,?,?,?)");
	pstmt->setInt(1, _capacity);
	pstmt->setString(2, _name);
	pstmt->setString(3, _reserver.getName());
	pstmt->setString(4, _usableType);
	pstmt->setString(5, _accessLevel);
	pstmt->setBoolean(6, _isReservable);
	pstmt->setBoolean(7, _isReserved);
	pstmt->execute();

	delete pstmt;

	pstmt = con->prepareStatement("SELECT MAX(id) FROM usable;");
	result = pstmt->executeQuery();
	while (result->next())
		id = result->getInt(1);

	delete result;
	delete pstmt;
}

Usable::~Usable(){
	pstmt = con->prepareStatement("DELETE FROM usable WHERE id = ?");
	pstmt->setInt(1, id);

	delete pstmt;
}

void Usable::setCapacity(int _capacity){
	if (_capacity > 0){
		pstmt = con->prepareStatement("UPDATE usable SET capacity = ? WHERE id = ?");
		pstmt->setInt(1, _capacity);
		pstmt->setInt(2, id);
		pstmt->executeQuery();
		delete pstmt;
	}
	else{
		throw invalid_argument("Kapasite degeri sifirdan buyuk olmali.");
	} 
}

void Usable::setName(string _name){
	pstmt = con->prepareStatement("UPDATE usable SET name = ? WHERE id = ?");
	pstmt->setString(1, _name);
	pstmt->setInt(2, id);
	pstmt->executeQuery();
	delete pstmt;
}

void Usable::setUsableType(string _usableType){
	transform(_usableType.begin(), _usableType.end(), _usableType.begin(), ::tolower);

	if (_usableType == "equipment" || _usableType == "pool" || _usableType == "sauna"){
		pstmt = con->prepareStatement("UPDATE usable SET usableType = ? WHERE id = ?");
		pstmt->setString(1, _usableType);
		pstmt->setInt(2, id);
		pstmt->executeQuery();
		delete pstmt;
	}
	else {
		throw invalid_argument("Gecersiz tip girisi.");
	}
}

void Usable::setAccessLevel(string _accessLevel){
	transform(_accessLevel.begin(), _accessLevel.end(), _accessLevel.begin(), ::tolower);
	if (_accessLevel != "silver" || _accessLevel != "gold" || _accessLevel != "platinum" || _accessLevel != "diamond" || _accessLevel != "employee"){
		throw invalid_argument("Erisim leveli mevcut degil.");
	}
	else {
		pstmt = con->prepareStatement("UPDATE usable SET accessLevel = ? WHERE id = ?");
		pstmt->setString(1, _accessLevel);
		pstmt->setInt(2, id);
		pstmt->executeQuery();
		delete pstmt;
	}
}

void Usable::setIsReservable(bool _isReservable){
	pstmt = con->prepareStatement("UPDATE usable SET isReservable = ? WHERE id = ?");
	pstmt->setBoolean(1, _isReservable);
	pstmt->setInt(2, id);
	pstmt->executeQuery();
	delete pstmt;
}

int Usable::getCapacity() const{
	pstmt = con->prepareStatement("SELECT capacity FROM usable WHERE id = ?;");
	pstmt->setInt(1, id);
	result = pstmt->executeQuery();
	while (result->next())
		return result->getInt(1);
	delete result;
}

string Usable::getName() const{
	pstmt = con->prepareStatement("SELECT name FROM usable WHERE id = ?;");
	pstmt->setInt(1, id);
	result = pstmt->executeQuery();
	while (result->next())
		return result->getString(1);
	delete result;
}

string Usable::getUsableType() const{
	pstmt = con->prepareStatement("SELECT usableType FROM usable WHERE id = ?;");
	pstmt->setInt(1, id);
	result = pstmt->executeQuery();
	while (result->next())
		return result->getString(1);
	delete result;
}

string Usable::getAccessLevel() const{
	pstmt = con->prepareStatement("SELECT accessLevel FROM usable WHERE id = ?;");
	pstmt->setInt(1, id);
	result = pstmt->executeQuery();
	while (result->next())
		return result->getString(1);
	delete result;
}

bool Usable::getIsReservable() const{
	pstmt = con->prepareStatement("SELECT isReservable FROM usable WHERE id = ?;");
	pstmt->setInt(1, id);
	result = pstmt->executeQuery();
	while (result->next())
		return result->getBoolean(1);
	delete result;
}

bool Usable::getIsReserved() const{
	pstmt = con->prepareStatement("SELECT isReserved FROM usable WHERE id = ?;");
	pstmt->setInt(1, id);
	result = pstmt->executeQuery();
	while (result->next())
		return result->getBoolean(1);
	delete result;
}

Member Usable::getReserver() const{
	return reserver;
}

void Usable::reserve(Member _reserver){

	pstmt = con->prepareStatement("SELECT isReservable, isReserved FROM employee WHERE id = ?;");
	pstmt->setInt(1, id);
	result = pstmt->executeQuery();
	while (result->next());
		bool tisReservable = result->getBoolean(1);
		bool tisReserved = result->getBoolean(2);
	delete result;


	if (tisReservable == true && tisReserved == false){

		pstmt = con->prepareStatement("UPDATE usable SET isReserved = ? WHERE id = ?");
		pstmt->setBoolean(1, true);
		pstmt->setInt(2, id);
		pstmt->executeQuery();
		delete pstmt;

		reserver = _reserver;
		pstmt = con->prepareStatement("UPDATE usable SET reserverName = ? WHERE id = ?");
		pstmt->setString(1, _reserver.getName());
		pstmt->setInt(2, id);
		pstmt->executeQuery();
		delete pstmt;
	}
	else {
		throw logic_error("Nesne rezerve edilmeye uygun degil.");
	}
}


void Usable::unreserve(Member _nullreserver){
	pstmt = con->prepareStatement("UPDATE usable SET isReserved = ? WHERE id = ?");
	pstmt->setBoolean(1, false);
	pstmt->setInt(2, id);
	pstmt->executeQuery();
	delete pstmt;
	reserver = _nullreserver;
}
