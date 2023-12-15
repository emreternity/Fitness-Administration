#include "Employee.h"
#include <string>
#include <stdexcept>


#include <iostream>

using namespace std;

float Employee::temizlikcisalary = 15000;
float Employee::gorevlisalary = 25000;
float Employee::ptsalary = 35000;

Employee::Employee(string _fname, string _lname, int _age, float _weight, float _height, string _birthdate, string _startingdate, int _workdays, float _basesalary, string _employeetype, int _offdays, string _leavingdate) : Person(_fname, _lname, _age, _weight, _height, _birthdate) {
	setFirstName(_fname);
	setLastName(_lname);
	setAge(_age);
	setWeight(_weight);
	setHeight(_height);
	setBirthdate(_birthdate);
    setStartingDate(_startingdate);
    setWorkDays(_workdays);
    setLeavingDate(_leavingdate);
    setEmployeeType(_employeetype); 
    setBaseSalary(_basesalary);
    setOffDays(_offdays);
}

 Employee::~Employee(){
 	
 }
 
 void Employee::setBaseSalary(float _basesalary){
 	
 		if (_basesalary > 0) {
		basesalary = _basesalary;
	}
	else {
		throw invalid_argument("Baz maas 0'dan kucuk olamaz.");
	}
 	
 }
 
 float Employee::getBaseSalary() const{
 	return basesalary;
 }
 
 void Employee::setStartingDate(string _startingdate){
 	
 	startingdate = _startingdate;
 	
 }
 
 string Employee::getStartingDate() const{
 	return startingdate;
 }
 
 void Employee::setLeavingDate(string _leavingdate) {
 	
 	leavingdate= _leavingdate;
 	
 }
 
 string Employee::getLeavingDate() const{
 	return leavingdate;
 }
 
 void Employee::setOffDays(int _offdays){
 	if (_offdays >= 0) {
		offdays = _offdays;
	}
	else {
		throw invalid_argument("Offday sayisi negatif olamaz.");
	}
 }
 
 int Employee::getOffDays() const{
 	return offdays;
  }

 void Employee::setWorkDays(int _workdays) {
     if (_workdays > 0 && workdays < 31) {
         workdays = _workdays;
     }
     else {
         throw invalid_argument("Workday sayisi sifirdan buyuk olmali.");
     }
 }

 int Employee::getWorkDays() const {
     return workdays;
 }
  
 void Employee::setEmployeeType(string _employeetype) {
 	
     if (_employeetype == "gorevli" || _employeetype == "temizlikci" || _employeetype == "egitmen") {
                  employeetype = _employeetype;
         if (_employeetype == "gorevli") {
             basesalary = gorevlisalary;
         }
         else if (_employeetype == "temizlikci") {
             basesalary = temizlikcisalary;
         }
         else if (_employeetype == "egitmen") {
             basesalary = ptsalary;
         }
    }
     else {
         throw invalid_argument("Gecersiz calisan tipi girdiniz.");
     }
 	
 }
 
 string Employee::getEmployeeType() const{
 	return employeetype;
 }
 
 float Employee::calculateSalary() const{
     return basesalary - ((basesalary / workdays) * offdays);
 }

 void Employee::setDefaultSalaries(float _temizlikcisalary, float _gorevlisalary, float _ptsalary) {
     temizlikcisalary = _temizlikcisalary;
     gorevlisalary = _gorevlisalary;
     ptsalary = _ptsalary;
 }

void Employee::seeValues() const{
	cout<<"First Name: "<<getFirstName()<<endl;
	cout<<"Last Name: "<<getLastName()<<endl;
	cout<<"Full Name: "<<getName()<<endl;
	cout<<"Age: "<<getAge()<<endl;
	cout<<"Weight: "<<getWeight()<<endl;
	cout<<"Height: "<<getHeight()<<endl;
	cout<<"Birthdate: "<<getBirthdate()<<endl;
	cout<<"Starting Date: "<<getStartingDate()<<endl;
	cout<<"Leaving Date: "<<getLeavingDate()<<endl;
	cout<<"Workdays: "<<getWorkDays()<<endl;
	cout<<"Offdays: "<<getOffDays()<<endl;
	cout<<"Base Salary: "<<getBaseSalary()<<endl;
	cout<<"Calc Salary: "<<calculateSalary()<<endl;
	cout<<"Emp Type: "<<getEmployeeType()<<endl;
	cout<<"Test Over."<<endl<<endl;
}

void Employee::insertSQL(sql::Connection* con){
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;
	
	pstmt = con->prepareStatement("INSERT INTO employee(fname,lname,age,weight,height,birthdate,startingdate,workdays,leavingdate,basesalary,employeetype) VALUES(?,?,?,?,?,?,?,?,?,?,?);");
    pstmt->setString(1, fname);
    pstmt->setString(2, lname);
    pstmt->setInt(3, age);
    pstmt->setDouble(4, weight);
    pstmt->setDouble(5, height);
    pstmt->setString(6, birthdate);
    pstmt->setString(7, startingdate);
    pstmt->setInt(8, workdays);
    pstmt->setString(9, leavingdate);
    pstmt->setDouble(10, basesalary);
    pstmt->setString(11, employeetype);
    pstmt->execute();
	
	pstmt = con->prepareStatement("SELECT MAX(id) FROM employee;");
	result = pstmt->executeQuery();
	while (result->next())
	id = result->getInt(1);

	delete pstmt;
	delete result;
}

void Employee::updateSQL(sql::Connection* con){
	sql::PreparedStatement* pstmt;
		
	pstmt = con->prepareStatement("UPDATE employee SET fname = ?,lname = ?,age = ?,weight = ?,height = ? ,birthdate = ?,startingdate = ?, workdays = ?, leavingdate = ?, basesalary = ?, employeetype = ? WHERE id = ?");
    pstmt->setString(1, fname);
    pstmt->setString(2, lname);
    pstmt->setInt(3, age);
    pstmt->setDouble(4, weight);
    pstmt->setDouble(5, height);
    pstmt->setString(6, birthdate);
    pstmt->setString(7, startingdate);
    pstmt->setInt(8, workdays);
    pstmt->setString(9, leavingdate);
    pstmt->setDouble(10, basesalary);
    pstmt->setString(11, employeetype);
	pstmt->setInt(12, id);
	pstmt->executeQuery();
	
	delete pstmt;
}



