#include "Employee.h"
#include "Person.h"
#include <string>
#include <stdexcept>
#include <iostream>
#include <algorithm>

#include "sqlstuff.h"

using namespace std;

float Employee::temizlikcisalary = 15000;
float Employee::gorevlisalary = 25000;
float Employee::ptsalary = 35000;

Employee::Employee(string _fname, string _lname, int _age, float _weight, float _height, string _birthdate, string _startingdate, int _workdays, string _leavingdate, float _basesalary, string _employeetype) : Person(_fname, _lname, _age, _weight, _height, _birthdate) {
    tryCon();
    schemaFunc();

    pstmt = con->prepareStatement("INSERT INTO employee(fname,lname,age,weight,height,birthdate,startingdate,workdays,leavingdate,basesalary,employeetype) VALUES(?,?,?,?,?,?,?,?,?,?,?)");
    pstmt->setString(1, _fname);
    pstmt->setString(2, _lname);
    pstmt->setInt(3, _age);
    pstmt->setDouble(4, _weight);
    pstmt->setDouble(5, _height);
    pstmt->setString(6, _birthdate);
    pstmt->setString(7, _startingdate);
    pstmt->setInt(8, _workdays);
    pstmt->setString(9, _leavingdate);
    pstmt->setDouble(10, _basesalary);
    pstmt->setString(11, _employeetype);
    pstmt->execute();

    delete pstmt;

    pstmt = con->prepareStatement("SELECT MAX(id) FROM employee;");
    result = pstmt->executeQuery();
    while (result->next())
        id = result->getInt(1);

    delete result;
    delete pstmt;
}

 Employee::~Employee(){
     pstmt = con->prepareStatement("DELETE FROM employee WHERE id = ?");
     pstmt->setInt(1, id);

     delete pstmt;
 }
 
 void Employee::setBaseSalary(float _basesalary){
 	
 		if (_basesalary > 0) {
            pstmt = con->prepareStatement("UPDATE employee SET basesalary = ? WHERE id = ?");
            pstmt->setDouble(1, _basesalary);
            pstmt->setInt(2, id);
            pstmt->executeQuery();
            delete pstmt;
	}
	else {
		throw invalid_argument("Baz maas 0'dan kucuk olamaz.");
	}
 	
 }
 
 float Employee::getBaseSalary() const{
     pstmt = con->prepareStatement("SELECT basesalary FROM employee WHERE id = ?;");
     pstmt->setInt(1, id);
     result = pstmt->executeQuery();
     while (result->next())
         return result->getDouble(1);
     delete result;
 }
 
 void Employee::setStartingDate(string _startingdate){
 	
     pstmt = con->prepareStatement("UPDATE employee SET startingdate = ? WHERE id = ?");
     pstmt->setString(1, _startingdate);
     pstmt->setInt(2, id);
     pstmt->executeQuery();
     delete pstmt;
 	
 }
 
 string Employee::getStartingDate() const{
     pstmt = con->prepareStatement("SELECT startingdate FROM employee WHERE id = ?;");
     pstmt->setInt(1, id);
     result = pstmt->executeQuery();
     while (result->next())
         return result->getString(1);
     delete result;
 }
 
 void Employee::setLeavingDate(string _leavingdate) {
 	
     pstmt = con->prepareStatement("UPDATE employee SET leavingdate = ? WHERE id = ?");
     pstmt->setString(1, _leavingdate);
     pstmt->setInt(2, id);
     pstmt->executeQuery();
     delete pstmt;
 	
 }
 
 string Employee::getLeavingDate() const{
     pstmt = con->prepareStatement("SELECT leavingdate FROM employee WHERE id = ?;");
     pstmt->setInt(1, id);
     result = pstmt->executeQuery();
     while (result->next())
         return result->getString(1);
     delete result;
 }
 
 void Employee::setOffDays(int _offdays){
 	if (_offdays > 0) {
        pstmt = con->prepareStatement("UPDATE employee SET offdays = ? WHERE id = ?");
        pstmt->setInt(1, _offdays);
        pstmt->setInt(2, id);
        pstmt->executeQuery();
        delete pstmt;
	}
	else {
		throw invalid_argument("Offday sayisi sifirdan buyuk olmali.");
	}
 }
 
 int Employee::getOffDays() const{
     pstmt = con->prepareStatement("SELECT offdays FROM employee WHERE id = ?;");
     pstmt->setInt(1, id);
     result = pstmt->executeQuery();
     while (result->next())
         return result->getInt(1);
     delete result;
  }

 void Employee::setWorkDays(int _workdays) {
     if (_workdays > 0 && _workdays < 31) {
         pstmt = con->prepareStatement("UPDATE employee SET workdays = ? WHERE id = ?");
         pstmt->setInt(1, _workdays);
         pstmt->setInt(2, id);
         pstmt->executeQuery();
         delete pstmt;
     }
     else {
         throw invalid_argument("Workday sayisi sifirdan buyuk olmali.");
     }
 }

 int Employee::getWorkDays() const {
     pstmt = con->prepareStatement("SELECT workdays FROM employee WHERE id = ?;");
     pstmt->setInt(1, id);
     result = pstmt->executeQuery();
     while (result->next())
         return result->getInt(1);
     delete result;
 }
  
 void Employee::setEmployeeType(string _employeetype) {
     transform(_employeetype.begin(), _employeetype.end(), _employeetype.begin(), ::tolower);
     if (_employeetype != "gorevli" || _employeetype != "temizlikci" || _employeetype != "egitmen") {
         throw invalid_argument("Gecersiz calisan tipi girdiniz.");
    }
     else {
         pstmt = con->prepareStatement("UPDATE employee SET employeetype = ? WHERE id = ?");
         pstmt->setString(1, _employeetype);
         pstmt->setInt(2, id);
         pstmt->executeQuery();
         delete pstmt;

         if (_employeetype == "gorevli") {
             pstmt = con->prepareStatement("UPDATE employee SET basesalary = ? WHERE id = ?");
             pstmt->setDouble(1, gorevlisalary);
             pstmt->setInt(2, id);
             pstmt->executeQuery();
             delete pstmt;
         }
         else if (_employeetype == "temizlikci") {
             pstmt = con->prepareStatement("UPDATE employee SET basesalary = ? WHERE id = ?");
             pstmt->setDouble(1, temizlikcisalary);
             pstmt->setInt(2, id);
             pstmt->executeQuery();
             delete pstmt;
         }
         else if (_employeetype == "egitmen") {
             pstmt = con->prepareStatement("UPDATE employee SET basesalary = ? WHERE id = ?");
             pstmt->setDouble(1, ptsalary);
             pstmt->setInt(2, id);
             pstmt->executeQuery();
             delete pstmt;
         }
     }
 	
 }
 
 string Employee::getEmployeeType() const{
     pstmt = con->prepareStatement("SELECT employeetype FROM employee WHERE id = ?;");
     pstmt->setInt(1, id);
     result = pstmt->executeQuery();
     while (result->next())
         return result->getString(1);
     delete result;
 }
 
 float Employee::calculateSalary() {
     float tbasesalary = getBaseSalary();
     int tworkdays = getWorkDays();
     int toffdays = getOffDays();

     return tbasesalary - ((tbasesalary / tworkdays) * toffdays);
 }

 void Employee::setDefaultSalaries(float _temizlikcisalary, float _gorevlisalary, float _ptsalary) {
     temizlikcisalary = _temizlikcisalary;
     gorevlisalary = _gorevlisalary;
     ptsalary = _ptsalary;
 }






