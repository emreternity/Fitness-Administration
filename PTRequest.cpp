#include "PTRequest.h"
#include <chrono>

using namespace std;

PTRequest::PTRequest(int _desiredDay, int _desiredHour, int _desiredLength, Admin _chosenPT, Member _reserver, bool _isApproved) : chosenPT(_chosenPT), reserver(_reserver) {
	setdesiredDay(_desiredDay);
	setdesiredHour(_desiredHour);
	setdesiredLength(_desiredLength);
	setisApproved(_isApproved);
	setrequestDate();
}

void PTRequest::setdesiredDay(int _desiredDay) {
	if (_desiredDay > 0 && _desiredDay <= 7) {
		desiredDay = _desiredDay;
	}
	else {
		throw logic_error("Secilen gun mevcut degil.");
	}
}

int PTRequest::getdesiredDay() const {
	return desiredDay;
}

void PTRequest::setdesiredHour(int _desiredHour) {
	if (_desiredHour > 0 && _desiredHour <= 23) {
		desiredHour = _desiredHour;
	}
	else {
		throw logic_error("Secilen saat mevcut degil.");
	}
}

int PTRequest::getdesiredHour() const {
	return desiredHour;
}

void PTRequest::setdesiredLength(int _desiredLength) {
	int maxLength = 24 - desiredHour;
	if (_desiredLength < maxLength) {
		desiredLength = _desiredLength;
	}
	else {
		throw logic_error("Secilen uzunluk gunu asiyor.");
	}
}

int PTRequest::getdesiredLength() const {
	return desiredLength;
}

void PTRequest::setisApproved(bool _isApproved) {
	isApproved = _isApproved;
}

bool PTRequest::getisApproved() const {
	return isApproved;
}

void PTRequest::setReserver(Member _reserver) {
	reserver = _reserver;
}
Member PTRequest::getReserver() const {
	return reserver;
}

void PTRequest::setchosenPT(Admin _chosenPT) {
	chosenPT = _chosenPT;
}

Admin PTRequest::getchosenPT() const {
	return chosenPT;
}

void PTRequest::setrequestDate() {
	time_t t = time(nullptr);
	char mbstr[22];
	strftime(mbstr, sizeof(mbstr), "%d/%m/%Y - %T", localtime(&t));
	requestdate = mbstr;
}

string PTRequest::getrequestDate() const {
	return requestdate;
}

void PTRequest::setID(int _id) {
	id = _id;
}

int PTRequest::getID() const {
	return id;
}


void PTRequest::insertSQL(sql::Connection* con) {
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;

	pstmt = con->prepareStatement("INSERT INTO ptrequest(requestdate,desiredDay,desiredHour,desiredLength,isApproved,reserverName, ptName) VALUES(?,?,?,?,?,?,?);");
	pstmt->setString(1, requestdate);
	pstmt->setInt(2, desiredDay);
	pstmt->setInt(3, desiredHour);
	pstmt->setInt(4, desiredLength);
	pstmt->setBoolean(5, isApproved);
	pstmt->setString(6, reserver.getName());
	pstmt->setString(7, chosenPT.getName());
	pstmt->execute();

	pstmt = con->prepareStatement("SELECT MAX(id) FROM ptrequest;");
	result = pstmt->executeQuery();
	while (result->next())
		id = result->getInt(1);

	delete pstmt;
	delete result;
}


void PTRequest::updateSQL(sql::Connection* con) {
	sql::PreparedStatement* pstmt;

	pstmt = con->prepareStatement("UPDATE ptrequest SET requestdate = ?, desiredDay = ?,desiredHour = ?,desiredLength = ?,isApproved = ?,reserverName = ?, ptName = ? WHERE id = ?;");
	pstmt->setString(1, requestdate);
	pstmt->setInt(2, desiredDay);
	pstmt->setInt(3, desiredHour);
	pstmt->setInt(4, desiredLength);
	pstmt->setBoolean(5, isApproved);
	pstmt->setString(6, reserver.getName());
	pstmt->setString(7, chosenPT.getName());
	pstmt->setInt(8, getID());
	pstmt->executeUpdate();

	delete pstmt;
}

