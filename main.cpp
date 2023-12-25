#include <iostream>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <mysql_error.h>
#include <iostream>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <string>
#include <vector>


#include "Person.h"
#include "Member.h"
#include "Usable.h"
#include "Employee.h"

using namespace std;

sql::Driver* driver;
sql::Connection* con;
sql::Statement* stmt;
sql::PreparedStatement* pstmt;
sql::ResultSet* result;

const string server = "tcp://127.0.0.1:3306";
const string username = "root";
const string password = "mysqlsifre123";

vector<Member> MemberList;
vector<Usable> UsableList;
vector<Employee> EmployeeList;

void tryCon() {
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
}

void schemaFunc() {
	con->setSchema("fitness_administration");
}

void addMember(sql::Connection* con, string _fname, string _lname, int _age, float _weight, float _height, string _birthdate, string _membertype, string _email, float _wgoal, float _balance = 0, int _xp = 0) {
	MemberList.push_back(Member(_fname, _lname, _age, _weight, _height, _birthdate, _membertype, _email, _wgoal, _balance, _xp));
	MemberList.back().insertSQL(con);
}

void updateMemberDatas(sql::Connection* con) {
	for (int i = 0; i < MemberList.size();i++) {
		MemberList[i].updateSQL(con);
	}
}

void refreshMemberDatas(sql::Connection* con) {
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;

	int _id;

	pstmt = con->prepareStatement("SELECT * FROM member;");
	result = pstmt->executeQuery();
	while (result->next()){
		MemberList.push_back(Member(result->getString(2), result->getString(3), result->getInt(4), result->getDouble(5), result->getDouble(6), result->getString(7), result->getString(8), result->getString(11), result->getDouble(13), result->getDouble(12), result->getDouble(10)));
		_id = result->getInt(1);
		MemberList.back().setID(_id);
	}
	delete pstmt;
	delete result;
}

void getMemberList() {
	for (int i = 0;i < MemberList.size();i++) {
		cout << "ID: " << MemberList[i].getID() << " | " << MemberList[i].getName() << endl;
	}
}

void deleteMember(sql::Connection* con) {
	
	sql::PreparedStatement* pstmt;

	int _idDel;
	getMemberList();

	cout << endl << "Silmek istediginiz uye ID'sini girin: ";
	cin >> _idDel;
	for (int i = 0; i < MemberList.size(); i++) {
		if (_idDel == MemberList[i].getID()) {
			MemberList.erase(MemberList.begin()+i);
			pstmt = con->prepareStatement("DELETE FROM member WHERE id = ?");
			pstmt->setInt(1, MemberList[i].getID());
			pstmt->executeQuery();	
		}
	}
}

void addEmployee(sql::Connection* con, string _fname, string _lname, int _age, float _weight, float _height, string _birthdate, string _startingdate, int _workdays, float _basesalary = 11402.32, string _employeetype = "gorevli", int _offdays = 0, string _leavingdate = "N/A") {
	EmployeeList.push_back(Employee(_fname, _lname, _age, _weight, _height, _birthdate, _startingdate, _workdays, _basesalary, _employeetype, _offdays, _leavingdate));
	EmployeeList.back().insertSQL(con);
}

void updateEmployeeDatas(sql::Connection* con) {
	for (int i = 0; i < EmployeeList.size();i++) {
		EmployeeList[i].updateSQL(con);
	}
}

void refreshEmployeeDatas(sql::Connection* con) {
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;

	int _id;

	pstmt = con->prepareStatement("SELECT * FROM employee;");
	result = pstmt->executeQuery();
	while (result->next()) {
		EmployeeList.push_back(Employee(result->getString(2), result->getString(3), result->getInt(4), result->getDouble(5), result->getDouble(6), result->getString(7), result->getString(9), result->getInt(13), result->getDouble(8), result->getString(11), result->getInt(12), result->getString(10)));
		_id = result->getInt(1);
		EmployeeList.back().setID(_id);
	}
	delete pstmt;
	delete result;
}

void getEmployeeList() {
	for (int i = 0;i < EmployeeList.size();i++) {
		cout << "ID: " << EmployeeList[i].getID() << " | " << EmployeeList[i].getName() << endl;
	}
}

void deleteEmployee(sql::Connection* con) {

	sql::PreparedStatement* pstmt;

	int _idDel;
	getEmployeeList();

	cout << endl << "Silmek istediginiz calisan ID'sini girin: ";
	cin >> _idDel;
	for (int i = 0; i < EmployeeList.size(); i++) {
		if (_idDel == EmployeeList[i].getID()) {
			EmployeeList.erase(EmployeeList.begin() + i);
			pstmt = con->prepareStatement("DELETE FROM employee WHERE id = ?");
			pstmt->setInt(1, EmployeeList[i].getID());
			pstmt->executeQuery();
		}
	}
}

void addUsable(sql::Connection* con, int _capacity, string _name, Member _reserver, string _usableType = "equipment", string _accessLevel = "silver", bool _isReservable = true, bool _isReserved = false) {
	UsableList.push_back(Usable(_capacity, _name, _reserver, _usableType, _accessLevel, _isReservable, _isReserved));
	UsableList.back().insertSQL(con);
}

void updateUsableDatas(sql::Connection* con) {
	for (int i = 0; i < UsableList.size();i++) {
		UsableList[i].updateSQL(con);
	}
}

Member matchUsableReserver(sql::Connection* con, int id) {
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;

	string reserverName;

	pstmt = con->prepareStatement("SELECT reserverName FROM usable WHERE id = ?;");
	pstmt->setInt(1, id);
	result = pstmt->executeQuery();
	while (result->next())
		reserverName = result->getString(1);
	delete result;
	delete pstmt;

	for (int i = 0; i < MemberList.size(); i++) {
		if (MemberList[i].getName() == reserverName) {
			return MemberList[i];
		}
	}
}

void refreshUsableDatas(sql::Connection* con) {
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;

	int _id;

	pstmt = con->prepareStatement("SELECT * FROM usable;");
	result = pstmt->executeQuery();
	while (result->next()) {
		UsableList.push_back(Usable(result->getInt(2), result->getString(3), matchUsableReserver(con, result->getInt(1)), result->getString(4), result->getString(5), result->getBoolean(6), result->getBoolean(7)));
		_id = result->getInt(1);
		UsableList.back().setID(_id);
	}
	delete pstmt;
	delete result;
}

void getUsableList() {
	for (int i = 0;i < UsableList.size();i++) {
		cout << "ID: " << UsableList[i].getID() << " | " << UsableList[i].getName() << endl;
	}
}

void deleteUsable(sql::Connection* con) {

	sql::PreparedStatement* pstmt;

	int _idDel;
	getUsableList();

	cout << endl << "Silmek istediginiz kullanilabilir ID'sini girin: ";
	cin >> _idDel;
	for (int i = 0; i < UsableList.size(); i++) {
		if (_idDel == UsableList[i].getID()) {
			UsableList.erase(UsableList.begin() + i);
			pstmt = con->prepareStatement("DELETE FROM usable WHERE id = ?");
			pstmt->setInt(1, UsableList[i].getID());
			pstmt->executeQuery();
		}
	}
}

int main() {
	tryCon();
	schemaFunc();
	refreshMemberDatas(con);
	refreshEmployeeDatas(con);
	refreshUsableDatas(con);

	//start

	//end

	updateMemberDatas(con);
	updateEmployeeDatas(con);
	updateUsableDatas(con);

	system("pause");
}