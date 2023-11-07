#include "Employee.h"
#include "Person.h"
#include <string>
#include <stdexcept>


#include <iostream>

using namespace std;

float Employee::temizlikcisalary = 15000;
float Employee::gorevlisalary = 25000;
float Employee::ptsalary = 35000;

Employee::Employee(const string &_fname, const string &_lname, int _age, float _weight, float _height, const string &_birthdate, const string& _startingdate, int _workdays, const string& _leavingdate = "N/A", float _basesalary = 11402.32, const string& _employeetype = "Gorevli") : Person(_fname, _lname, _age, _weight, _height, _birthdate) {
	setFirstName(_fname);
	setLastName(_lname);
	setAge(_age);
	setWeight(_weight);
	setHeight(_height);
	setBirthdate(_birthdate);
    setStartingDate(_startingdate);
    setWorkDays(_workdays);
    setLeavingDate(_leavingdate);
    setBaseSalary(_basesalary);
    setEmployeeType(_employeetype); 
}

 Employee::~Employee(){
 	
 }
 
 void Employee::setBaseSalary(float _basesalary = 11402.32){
 	
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
 
 void Employee::setStartingDate(const string &_startingdate){
 	
 	startingdate = _startingdate;
 	
 }
 
 string Employee::getStartingDate() const{
 	return startingdate;
 }
 
 void Employee::setLeavingDate(const string &_leavingdate = "N/A") {
 	
 	leavingdate= _leavingdate;
 	
 }
 
 string Employee::getLeavingDate() const{
 	return leavingdate;
 }
 
 void Employee::setOffDays(int _offdays){
 	if (_offdays > 0) {
		offdays = _offdays;
	}
	else {
		throw invalid_argument("Offday sayisi sifirdan buyuk olmali.");
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
  
 void Employee::setEmployeeType(const string &_employeetype = "Gorevli") {
 	
     if (_employeetype != "Gorevli" || _employeetype != "Temizlikci" || _employeetype != "Egitmen") {
         throw invalid_argument("Gecersiz calisan tipi girdiniz.");
    }
     else {
         employeetype = _employeetype;
         if (_employeetype == "Gorevli") {
             basesalary = gorevlisalary;
         }
         else if (_employeetype == "Temizlikci") {
             basesalary = temizlikcisalary;
         }
         else if (_employeetype == "Egitmen") {
             basesalary = ptsalary;
         }
     }
 	
 }
 
 string Employee::getEmployeeType() const{
 	return employeetype;
 }
 
 float Employee::calculateSalary() {
     return basesalary - ((basesalary / workdays) * offdays);
 }

 void Employee::setDefaultSalaries(float _temizlikcisalary, float _gorevlisalary, float _ptsalary) {
     temizlikcisalary = _temizlikcisalary;
     gorevlisalary = _gorevlisalary;
     ptsalary = _ptsalary;
 }






