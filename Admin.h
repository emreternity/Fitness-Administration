#ifndef ADMIN_H
#define ADMIN_H

#include "Person.h"
#include <string>
using namespace std;

class Admin : public Person {

	friend class PTRequest;

private:
	string username;
	string password;
	string admintype;
	int id;
public:
	explicit Admin(string _fname, string _lname, int _age, float _weight, float _height, string _birthdate, string _username, string _password, string _admintype);


	void setUsername(string _username);
	string getUsername() const;
	void setPassword(string _password);
	string getPassword() const;
	void setAdmintype(string _admintype);
	string getAdmintype() const;

	void insertSQL(sql::Connection* con);
	void updateSQL(sql::Connection* con);
};

#endif