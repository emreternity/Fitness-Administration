#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "Person.h"
#include <string>

using namespace std;

class Employee : public Person {

private:
	float basesalary;
	string startingdate;
	string leavingdate;
	string employeetype;
	int offdays;
	int workdays;
	static float temizlikcisalary;
	static float gorevlisalary;
	static float ptsalary;

public:
	explicit Employee(string _fname, string _lname, int _age, float _weight, float _height, string _birthdate, string _startingdate, int _workdays, float _basesalary = 11402.32, string _employeetype = "gorevli", int _offdays = 0, string _leavingdate = "N/A");
	~Employee();

	void setBaseSalary(float _basesalary = 11402.32);
	float getBaseSalary() const;

	void setStartingDate(string _startingdate);
	string getStartingDate() const;

	void setLeavingDate(string _leavingdate = "N/A");
	string getLeavingDate() const;

	void setEmployeeType(string _employeetype = "Gorevli");
	string getEmployeeType()  const;

	void setOffDays(int _offdays = 0);
	int getOffDays() const;

	void setWorkDays(int _workdays = 1);
	int getWorkDays() const;

	float calculateSalary() const;

	static void setDefaultSalaries(float _temizlikcisalary, float _gorevlisalary, float _ptsalary);
	
	void seeValues() const;

	void insertSQL(sql::Connection* con);
	void updateSQL(sql::Connection* con);
};


#endif// !EMPLOYEE_H
