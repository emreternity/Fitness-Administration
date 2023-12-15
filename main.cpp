#include <iostream>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <mysql_error.h>
#include <iostream>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <string>


#include "Person.h"
#include "Member.h"
#include "Usable.h"
#include "Employee.h"

sql::Driver* driver;
sql::Connection* con;
sql::Statement* stmt;
sql::PreparedStatement* pstmt;
sql::ResultSet* result;

const string server = "tcp://127.0.0.1:3306";
const string username = "root";
const string password = "mysqlsifre123";

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

using namespace std;

int main() {
	tryCon();
	schemaFunc();
	Member nullreserver("NULL", "NULL", 20, 100, 180, "01/01/0001", "platinum", "nullemail@gmail.com", 100, 0, 0);
	nullreserver.insertSQL(con);
	Member m1("Emre", "Emreto", 20, 89, 178, "15/09/2003", "platinum", "emremreto@gmail.com", 70, 5000, 150000);
	m1.insertSQL(con);
	Usable u1(100, "Weight 1", nullreserver, "equipment", "silver", true, false);
	u1.insertSQL(con);
}