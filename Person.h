#ifndef PERSON_H
#define PERSON_H

#include <mysql_connection.h>
#include <mysql_driver.h>
#include <mysql_error.h>
#include <iostream>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <string>

using namespace std;

class Person {
	protected:
		int id;
		string fname;
		string lname;
		int age;
		float weight;
		float height;
		string birthdate;
	public:
		explicit Person(string _fname, string _lname, int _age, float _weight, float _height, string _birthdate);
		~Person();
		
		void setFirstName(string _fname);
		string getFirstName() const;
		void setLastName(string _lname);
		string getLastName() const;
		void setAge(int _age);
		int getAge() const;
		void setWeight(float _weight);
		float getWeight() const;
		void setHeight(float _height);
		float getHeight() const;
		void setBirthdate(string _birthdate);
		string getBirthdate() const;

		string getName() const;

		int getID() const;
		
		void seeValues() const;

		void insertSQL(sql::Connection* con);
		void updateSQL(sql::Connection* con);
};


#endif // !PERSON_H
