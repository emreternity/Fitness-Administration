#include "Admin.h"
#include <string>
#include <stdexcept>
#include <chrono>
#include <regex> 
#include <algorithm>
#include <math.h>

Admin::Admin(string _fname, string _lname, int _age, float _weight, float _height, string _birthdate, string _username, string _password, string _admintype) : Person(_fname, _lname, _age, _weight, _height, _birthdate) {
	setUsername(_username);
	setPassword(_password);
	setAdmintype(_admintype);
}

void Admin::setAdmintype(string _admintype) {
	transform(_admintype.begin(), _admintype.end(), _admintype.begin(), ::tolower);
	if (_admintype == "owner" || _admintype == "moderator" || _admintype == "pt") {
		admintype = _admintype;
	}
	else {
		throw invalid_argument("Yonetici tipi mevcut degil.");
	}
}

string Admin::getAdmintype() const {
	return admintype;
}

void Admin::setUsername(string _username) {
	username = _username;
}

string Admin::getUsername() const {
	return username;
}

void Admin::setPassword(string _password) {
	password = _password;
}

string Admin::getPassword() const {
	return password;
}

void Admin::insertSQL(sql::Connection* con) {
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;

	pstmt = con->prepareStatement("INSERT INTO admin(fname,lname,age,weight,height,birthdate,username,password,admintype) VALUES(?,?,?,?,?,?,?,?,?);");
	pstmt->setString(1, fname);
	pstmt->setString(2, lname);
	pstmt->setInt(3, age);
	pstmt->setDouble(4, weight);
	pstmt->setDouble(5, height);
	pstmt->setString(6, birthdate);
	pstmt->setString(7, username);
	pstmt->setString(8, password);
	pstmt->setString(9, admintype);

	pstmt->execute();

	pstmt = con->prepareStatement("SELECT MAX(id) FROM admin;");
	result = pstmt->executeQuery();
	while (result->next())
		id = result->getInt(1);

	delete pstmt;
	delete result;
}

void Admin::updateSQL(sql::Connection* con) {
	sql::PreparedStatement* pstmt;

	pstmt = con->prepareStatement("UPDATE admin SET fname = ?,lname = ?,age = ?,weight = ? ,height = ?,birthdate = ?, username = ?, password = ?, admintype = ? WHERE id = ?;");
	pstmt->setString(1, fname);
	pstmt->setString(2, lname);
	pstmt->setInt(3, age);
	pstmt->setDouble(4, weight);
	pstmt->setDouble(5, height);
	pstmt->setString(6, birthdate);
	pstmt->setString(7, username);
	pstmt->setString(8, password);
	pstmt->setString(9, admintype);
	pstmt->setInt(10, getID());
	pstmt->executeUpdate();

	delete pstmt;
}

