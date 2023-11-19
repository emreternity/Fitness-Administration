#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "Person.h"
#include <string>

class Employee : public Person {
private:
	static float temizlikcisalary;
	static float gorevlisalary;
	static float ptsalary;

public:
	explicit Employee(string _fname, string _lname, int _age, float _weight, float _height, string _birthdate, string _startingdate, int _workdays, string _leavingdate = "N/A", float _basesalary = 11402.32, string _employeetype = "Gorevli");
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

	float calculateSalary();

	static void setDefaultSalaries(float _temizlikcisalary, float _gorevlisalary, float _ptsalary);

};


#endif// !EMPLOYEE_H
