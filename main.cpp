#include <iostream>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <mysql_error.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <string>
#include <vector>
#include <iomanip>


#include "Person.h"
#include "Member.h"
#include "Usable.h"
#include "Employee.h"
#include "Admin.h"
#include "PTRequest.h"

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
vector<Admin> AdminList;
vector<PTRequest> PTReqList;

vector<int> MemberXPList;
vector<Member> DiscountList;
vector<PTRequest>chosenReqs;

void loginMenu();
void userMenu(Member _member);
void getLeaderboard();
void findMeGYMBuddy(Member _member);
void findTheAdmin(Admin _admin);


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

void addMember(sql::Connection* con, string _fname, string _lname, int _age, float _weight, float _height, string _birthdate, string _membertype, string _email, float _wgoal, string _username, string _password, float _balance = 0, int _xp = 0) {
	MemberList.push_back(Member(_fname, _lname, _age, _weight, _height, _birthdate, _membertype, _email, _wgoal, _username, _password, _balance, _xp));
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
		MemberList.push_back(Member(result->getString(2), result->getString(3), result->getInt(4), result->getDouble(5), result->getDouble(6), result->getString(7), result->getString(8), result->getString(11), result->getDouble(13), result->getString(14), result->getString(15), result->getDouble(12), result->getDouble(10)));
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
			pstmt->setInt(1, MemberList[i].getID()-1);
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
			pstmt->setInt(1, EmployeeList[i].getID()-1);
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

Member matchPTReqReserver(sql::Connection* con, int id) {
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;

	string reserverName;

	pstmt = con->prepareStatement("SELECT reserverName FROM ptrequest WHERE id = ?;");
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

Admin matchPTReqPT(sql::Connection* con, int id) {
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;

	string ptName;

	pstmt = con->prepareStatement("SELECT ptName FROM ptrequest WHERE id = ?;");
	pstmt->setInt(1, id);
	result = pstmt->executeQuery();
	while (result->next())
		ptName = result->getString(1);
	delete result;
	delete pstmt;

	for (int i = 0; i < AdminList.size(); i++) {
		if (AdminList[i].getName() == ptName) {
			return AdminList[i];
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

void addAdmin(sql::Connection* con, string _fname, string _lname, int _age, float _weight, float _height, string _birthdate, string _username, string _password, string _admintype) {
	AdminList.push_back(Admin(_fname, _lname, _age, _weight, _height, _birthdate, _username, _password, _admintype));
	AdminList.back().insertSQL(con);
}

void updateAdminDatas(sql::Connection* con) {
	for (int i = 0; i < AdminList.size();i++) {
		AdminList[i].updateSQL(con);
	}
}

void refreshAdminDatas(sql::Connection* con) {
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;

	int _id;

	pstmt = con->prepareStatement("SELECT * FROM admin;");
	result = pstmt->executeQuery();
	while (result->next()) {
		AdminList.push_back(Admin(result->getString(2), result->getString(3), result->getInt(4), result->getDouble(5), result->getDouble(6), result->getString(7), result->getString(8), result->getString(9), result->getString(10)));
		_id = result->getInt(1);
		AdminList.back().setID(_id);
	}
	delete pstmt;
	delete result;
}

void getAdminList() {
	for (int i = 0;i < AdminList.size();i++) {
		cout << "ID: " << AdminList[i].getID() << " | " << AdminList[i].getName() << endl;
	}
}

void getPTList() {
	for (int i = 0;i < AdminList.size();i++) {
		if (AdminList[i].getAdmintype() == "pt") {
			cout << "ID: " << AdminList[i].getID() << " | " << AdminList[i].getName() << endl;
		}
	}
}


void refreshPTReqDatas(sql::Connection* con) {
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;

	int _id;

	pstmt = con->prepareStatement("SELECT * FROM ptrequest;");
	result = pstmt->executeQuery();
	while (result->next()) {
		PTReqList.push_back(PTRequest(result->getInt(3), result->getInt(4), result->getInt(5), matchPTReqPT(con, result->getInt(1)), matchPTReqReserver(con, result->getInt(1)),result->getBoolean(6)));
		_id = result->getInt(1);
		PTReqList.back().setID(_id);
	}
	delete pstmt;
	delete result;
}

void updatePTReqDatas(sql::Connection* con) {
	for (int i = 0; i < PTReqList.size();i++) {
		PTReqList[i].updateSQL(con);
	}
}

void addPTReq(sql::Connection* con, int _desiredDay, int _desiredHour, int _desiredLength, Admin _chosenPT, Member _reserver) {
	PTReqList.push_back(PTRequest(_desiredDay, _desiredHour, _desiredLength, _chosenPT, _reserver));
	PTReqList.back().insertSQL(con);
}

void deleteAdmin(sql::Connection* con) {

	sql::PreparedStatement* pstmt;

	int _idDel;
	getAdminList();

	cout << endl << "Silmek istediginiz admin ID'sini girin: ";
	cin >> _idDel;
	for (int i = 0; i < AdminList.size(); i++) {
		if (_idDel == AdminList[i].getID()) {
			AdminList.erase(AdminList.begin() + i);
			pstmt = con->prepareStatement("DELETE FROM admin WHERE id = ?");
			pstmt->setInt(1, AdminList[i].getID());
			pstmt->executeQuery();
		}
	}
}

void registerMember() {
	string _fname;
	string _lname;
	int _age;
	float _weight;
	float _height;
	string _birthdate;
	string _username;
	string _password;
	string _membertype;
	string _email;
	float _balance;
	float _wgoal;
	cout << "(Soyad olmadan) Uye ismi: ";
	cin >> _fname;
	cout << endl << "Uye soyismi: ";
	cin >> _lname;
	cout << endl << "Uye yasi: ";
	cin >> _age;
	cout << endl << "Uye agirligi (kg): ";
	cin >> _weight;
	cout << endl << "Uye boyu (cm): ";
	cin >> _height;
	cout << endl << "Uye dogum tarihi (GG/AA/YYYY): ";
	cin >> _birthdate;
	cout << endl << "Uye kullanici adi: ";
	cin >> _username;
	cout << endl << "Uye sifresi: ";
	cin >> _password;
	cout << endl << "Uye tipi: ";
	cin >> _membertype;
	cout << endl << "Uye epostasi: ";
	cin >> _email;
	cout << endl << "Uye hedef kilosu: ";
	cin >> _wgoal;
	addMember(con, _fname, _lname, _age, _weight, _height, _birthdate, _membertype, _email, _wgoal, _username, _password);
}

void registerAdmin() {
	string _fname;
	string _lname;
	int _age;
	float _weight;
	float _height;
	string _birthdate;
	string _username;
	string _password;
	string _admintype;
	cout << "(Soyad olmadan) Yonetici ismi: ";
	cin >> _fname;
	cout << endl << "Yonetici soyismi: ";
	cin >> _lname;
	cout << endl << "Yonetici yasi: ";
	cin >> _age;
	cout << endl << "Yonetici agirligi (kg): ";
	cin >> _weight;
	cout << endl << "Yonetici boyu (cm): ";
	cin >> _height;
	cout << endl << "Yonetici dogum tarihi (GG/AA/YYYY): ";
	cin >> _birthdate;
	cout << endl << "Yonetici kullanici adi: ";
	cin >> _username;
	cout << endl << "Yonetici sifresi: ";
	cin >> _password;
	cout << endl << "Yonetici tipi: ";
	cin >> _admintype;
	addAdmin(con, _fname, _lname, _age, _weight, _height, _birthdate, _username, _password, _admintype);
}

void registerUsable() {
	int reservableChoice;
	int _capacity;
	string _name;
	string _usableType;
	string _accessLevel;
	bool _isReservable = false;
	cout << "Urun ismi: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, _name);
	cout << endl << "Urun tipi: ";
	cin >> _usableType;
	cout << endl << "Urun Erisim Seviyesi: ";
	cin >> _accessLevel;
	cout << endl << "Urun Rezerve Edilebilir mi? (1: Evet | 2: Hayir)";
	cin >> reservableChoice;
	if (reservableChoice == 1) {
		_isReservable = true;
	}
	else if (reservableChoice == 2) {
		_isReservable = false;
	}
	cout << endl << "Urun kapasitesi: ";
	cin >> _capacity;
	addUsable(con, _capacity, _name, MemberList[0], _usableType, _accessLevel, _isReservable);
}

void registerEmployee() {
	string _fname;
	string _lname;
	int _age;
	float _weight;
	float _height;
	string _birthdate;
	string _startingdate;
	string _employeetype;
	int _workdays;
	cout << "(Soyad olmadan) Calisan ismi: ";
	cin >> _fname;
	cout << endl << "Calisan soyismi: ";
	cin >> _lname;
	cout << endl << "Calisan yasi: ";
	cin >> _age;
	cout << endl << "Calisan agirligi (kg): ";
	cin >> _weight;
	cout << endl << "Calisan boyu (cm): ";
	cin >> _height;
	cout << endl << "Calisan dogum tarihi (GG/AA/YYYY): ";
	cin >> _birthdate;
	cout << endl<<"Calisan ise baslama tarihi (GG/AA/YYYY): ";
	cin >> _startingdate;
	cout << endl<< "Calisan tipi: ";
	cin >> _employeetype;
	cout << endl << "Calisan ayda kac gun calisiyor: ";
	cin >> _workdays;
	addEmployee(con, _fname, _lname, _age, _weight, _height, _birthdate, _startingdate, _workdays, 11402.32, _employeetype);
}

void ownerMenu(Admin _admin) {
	system("cls");
	int choice;
	cout << "Kurucu menusune hos geldiniz. " << endl << endl;

	cout << "Moderasyon Secenekleri (1)" << endl;
	cout << "Hesap Ayarlari (2)" << endl;
	cout << "Cikis Yap (0)" << endl << endl;

	cout << "Seciminiz: ";
	cin >> choice;
	if (choice == 1) {
		system("cls");
		int choiceone;
		cout << "Uye kaydet (1)" << endl;
		cout << "Uye kaydini sil (2)" << endl;
		cout << "Yonetici ekle (3)" << endl;
		cout << "Yonetici sil (4)" << endl;
		cout << "Urun kaydet (5)" << endl;
		cout << "Urun sil (6)" << endl;
		cout << "Calisan ekle (7)" << endl;
		cout << "Calisan sil (8)" << endl;
		cout << "Calisanlarin Maaslarini Duzenle (9)" << endl;
		cout << "Geri Gel (0)" << endl << endl;
		cout << "Seciminiz: ";
		cin >> choiceone;
		if (choiceone == 1) {
			system("cls");
			registerMember();
			ownerMenu(_admin);
		}
		else if (choiceone == 2) {
			system("cls");
			deleteMember(con);
			ownerMenu(_admin);
		}
		else if (choiceone == 3) {
			system("cls");
			registerAdmin();
			ownerMenu(_admin);
		}
		else if (choiceone == 4) {
			system("cls");
			deleteAdmin(con);
			ownerMenu(_admin);
		}
		else if (choiceone == 5) {
			system("cls");
			registerUsable();
			ownerMenu(_admin);
		}
		else if (choiceone == 6) {
			system("cls");
			deleteUsable(con);
			ownerMenu(_admin);
		}
		else if (choiceone == 7) {
			system("cls");
			registerEmployee();
			ownerMenu(_admin);
		}
		else if (choiceone == 8) {
			system("cls");
			deleteEmployee(con);
			ownerMenu(_admin);
		}
		else if (choiceone == 9) {
			system("cls");
			float temizlikcisalary;
			float gorevlisalary;
			float ptsalary;
			cout << "Temizlikcilerin maasini girin: ";
			cin >> temizlikcisalary;
			cout << endl << "Gorevlilerin maasini girin: ";
			cin >> gorevlisalary;
			cout << endl << "PT'lerin maasini girin: ";
			cin >> ptsalary;
			EmployeeList[0].setDefaultSalaries(temizlikcisalary, gorevlisalary, ptsalary);
			ownerMenu(_admin);
		}
		else if (choiceone == 0) {
			system("cls");
			ownerMenu(_admin);
		}
	}
	else if (choice == 2) {
		system("cls");
		int choicetwo;
		cout << "Kullanici Adini Degistir (1)" << endl;
		cout << "Sifreni Degistir (2)" << endl;
		cout << "Geri Gel (0)" << endl << endl;
		cout << "Seciminiz: ";
		cin >> choicetwo;
		if (choicetwo == 1) {
			system("cls");
			string _username;
			cout << "Yeni kullanici adi girin: ";
			cin >> _username;
			_admin.setUsername(_username);
			findTheAdmin(_admin);
			ownerMenu(_admin);
		}
		else if (choicetwo == 2) {
			system("cls");
			string _password;
			cout << "Yeni sifrenizi girin: ";
			cin >> _password;
			_admin.setPassword(_password);
			findTheAdmin(_admin);
			ownerMenu(_admin);
		}
		else if (choicetwo == 0) {
			system("cls");
			ownerMenu(_admin);
		}
	}
	else if (choice == 0) {
		system("cls");
	}

}

void findTheMember(Member _member) {
	for (int i = 0; i < MemberList.size();i++) {
		if (_member.getID() == MemberList[i].getID())
		{
			MemberList[i] = _member;
		}
	}
}

void findTheAdmin(Admin _admin) {
	for (int i = 0; i < AdminList.size();i++) {
		if (_admin.getID() == AdminList[i].getID())
		{
			AdminList[i] = _admin;
		}
	}
}

void modMenu(Admin _admin) {
	system("cls");
	int choice;
	cout << "Gorevli menusune hos geldiniz. " << endl << endl;

	cout << "Moderasyon Secenekleri (1)" << endl;
	cout << "Hesap Ayarlari (2)" << endl;
	cout << "Cikis Yap (0)" << endl << endl;

	cout << "Seciminiz: ";
	cin >> choice;
	if (choice == 1) {
		system("cls");
		int choiceone;
		cout << "Uye kaydet (1)" << endl;
		cout << "Uye kaydini sil (2)" << endl;
		cout << "Urun kaydet (3)" << endl;
		cout << "Urun sil (4)" << endl;
		cout << "Geri Gel (0)" << endl << endl;
		cout << "Seciminiz: ";
		cin >> choiceone;
		if (choiceone == 1) {
			system("cls");
			registerMember();
			modMenu(_admin);
		}
		else if (choiceone == 2) {
			system("cls");
			deleteMember(con);
			modMenu(_admin);
		}
		else if (choiceone == 3) {
			system("cls");
			registerUsable();
			modMenu(_admin);
		}
		else if (choiceone == 4) {
			system("cls");
			deleteUsable(con);
			modMenu(_admin);
		}
		else if (choiceone == 0) {
			system("cls");
			modMenu(_admin);
			modMenu(_admin);
		}
	}
	else if (choice == 2) {
		system("cls");
		int choicetwo;
		cout << "Kullanici Adini Degistir (1)" << endl;
		cout << "Sifreni Degistir (2)" << endl;
		cout << "Geri Gel (0)" << endl << endl;
		cout << "Seciminiz: ";
		cin >> choicetwo;
		if (choicetwo == 1) {
			system("cls");
			string _username;
			cout << "Yeni kullanici adi girin: ";
			cin >> _username;
			_admin.setUsername(_username);
			findTheAdmin(_admin);
			modMenu(_admin);
		}
		else if (choicetwo == 2) {
			system("cls");
			string _password;
			cout << "Yeni sifrenizi girin: ";
			cin >> _password;
			_admin.setPassword(_password);
			findTheAdmin(_admin);
			modMenu(_admin);
		}
		else if (choicetwo == 0) {
			system("cls");
			modMenu(_admin);
		}
	}
	else if (choice == 0) {
		system("cls");
	}
}

string PTReqapprovedStringify(PTRequest req) {
	if (req.getisApproved() == true) {
		return "Verilmis";
	}
	else {
		return "Verilmemis";
	}
}

string PTReqDayStringify(PTRequest req) {
	switch (req.getdesiredDay())
	{
	case 1:
		return "Pazartesi";
		break;
	case 2:
		return "Sali";
		break;
	case 3:
		return "Carsamba";
		break;
	case 4:
		return "Persembe";
		break;
	case 5:
		return "Cuma";
		break;
	case 6:
		return "Cumartesi";
		break;
	case 7:
		return "Pazar";
		break;
	default:
		break;
	}
}

string PTReqDayStringify(int day) {
	switch (day)
	{
	case 1:
		return "Pazartesi";
		break;
	case 2:
		return "Sali";
		break;
	case 3:
		return "Carsamba";
		break;
	case 4:
		return "Persembe";
		break;
	case 5:
		return "Cuma";
		break;
	case 6:
		return "Cumartesi";
		break;
	case 7:
		return "Pazar";
		break;
	default:
		break;
	}
}

void ptMenu(Admin _admin) {
	system("cls");
	int choice;
	cout << "PT menusune hos geldiniz. " << endl << endl;

	cout << "Ders Isteklerini Goruntule (1)" << endl;
	cout << "Haftalik Programa Gozat (2)" << endl;
	cout << "Cikis Yap (0)" << endl << endl;

	cout << "Seciminiz: ";
	cin >> choice;
	if (choice == 1) {
		system("cls");
		for (int i = 0; i < PTReqList.size(); i++) {
			if (PTReqList[i].getchosenPT().getID() == _admin.getID() && PTReqList[i].getisApproved() == false) {
				cout << "Istek ID: " << PTReqList[i].getID() << " | Istek Tarihi : " << PTReqList[i].getrequestDate() << " - Uye: " << PTReqList[i].getReserver().getName() << " | Gorusme Tarihi: " << PTReqDayStringify(PTReqList[i]) << ", " << PTReqList[i].getdesiredHour() << ":00'dan baslayarak " << PTReqList[i].getdesiredLength() << " saat" << endl;
			}
		}
		int approveChoice;
		cout << endl << "Onaylamak istediginiz istek ID (yoksa 0 girin): ";
		cin >> approveChoice;
		if (approveChoice == 0) {
			ptMenu(_admin);
		}
		else {
			for (int i = 0; i < PTReqList.size(); i++) {
				if (PTReqList[i].getID() == approveChoice) {
					PTReqList[i].setisApproved(true);
					cout << endl << "Basariyla istek onaylandi. Lutfen uyeye " << PTReqList[i].getReserver().getEmail() << " adresinden mail atarak haber veriniz." << endl;
					system("pause");
					ptMenu(_admin);
				}
			}
		}
	}
	else if (choice == 2) {
		system("cls");
		chosenReqs.clear();
		for (int i = 0; i < PTReqList.size(); i++) {
			if (PTReqList[i].getchosenPT().getID() == _admin.getID()) {
				chosenReqs.push_back(PTReqList[i]);
			}
		}
		if (chosenReqs.size() > 0) {
			for (int j = 0; j < chosenReqs.size(); j++) {
				cout << PTReqDayStringify(chosenReqs[j].getdesiredDay()) << " gununde " << chosenReqs[j].getReserver().getName() << " ile saat ";
				cout << setw(2) << setfill('0');
				cout << chosenReqs[j].getdesiredHour();
				cout << ":00'da baslayan, " << chosenReqs[j].getdesiredLength() << " saatlik bir gorusmeniz var. "<<endl;
			}
		}
		system("pause");
		ptMenu(_admin);
	}
}

void adminMenu(Admin _admin) {
	if (_admin.getAdmintype() == "owner") {
		system("cls");
		ownerMenu(_admin);
	}
	else if (_admin.getAdmintype() == "moderator") {
		system("cls");
		modMenu(_admin);
	}
	else if (_admin.getAdmintype() == "pt") {
		system("cls");
		ptMenu(_admin);
	}
}

void loginMenu() {

	string username, password;
	cout << "Kullanici Adi: ";
	cin >> username;

	for (int j = 0; j < AdminList.size(); j++) {
		if (username == AdminList[j].getUsername()) {
			cout << "Sifre : ";
			cin >> password;
			if (password == AdminList[j].getPassword()) {
				adminMenu(AdminList[j]);
			}
			else {
				system("cls");
				cout << "Sifre eslesmedi. Lutfen sifrenizi dogru girdiginize emin olun." << endl << endl;
				system("pause");
				loginMenu();
			}
		}
	}

	for (int i = 0; i < MemberList.size(); i++) {
		if (username == MemberList[i].getUsername()) {
			cout << "Sifre : ";
			cin >> password;
			if (password == MemberList[i].getPassword()) {
				userMenu(MemberList[i]);
			}
			else {
				system("cls");
				cout << "Sifre eslesmedi. Lutfen sifrenizi dogru girdiginize emin olun." << endl << endl;
				system("pause");
				loginMenu();
			}
		}
	}
}

void userMenu(Member _member) {
	system("cls");
	int choice;
	cout << "Merhaba " << _member.getFirstName() << ", kullanici menusune hos geldin." << endl << endl;
	cout << " Toplam tecrube puanin: " << _member.getXP() << " | Seviyen: " << _member.getLevel()<< endl << endl;

	cout << "Antrenman Girdisi Kaydet (1)" << endl;
	cout << "Survival of the Fit Listesini Gor (2)" << endl;
	cout << "GYM Buddy'ni Bul (3)" << endl;
	cout << "Bakiye Yukle (4)" << endl;
	cout << "Uyeligini Gelistir (5)" << endl;
	cout << "Urun Rezerve Et (Sauna, Havuz, Agirlik vs.) (6)" << endl;
	cout << "PT Rezerve Et (7)" << endl;
	cout << "Cikis Yap (0)" << endl << endl;
	cout << "Secimin: ";
	cin >> choice;
	if (choice == 1) {
		system("cls");
		int hourstrained;
		cout << "Kac saat antrenman yaptin: ";
		cin >> hourstrained;
		cout << endl << endl << "Tebrikler! Bu antrenmanla " << hourstrained * 75 << " XP kazandin!" << endl<<endl;
		int tempxp = _member.getXP() + hourstrained * 75;
		_member.setXP(tempxp);
		findTheMember(_member); //bakilacak
		system("pause");
		userMenu(_member);
	}
	else if (choice == 2) {
		system("cls");
		getLeaderboard();
		system("pause");
		userMenu(_member);
	}
	else if (choice == 3) {
		system("cls");
		findMeGYMBuddy(_member);
		system("pause");
		userMenu(_member);
	}
	else if (choice == 4) {
		system("cls");
		int balanceAddVal;
		cout << "Kac TL'lik bakiye yuklemek istiyorsun: ";
		cin >> balanceAddVal;
		_member.setBalance(_member.getBalance() + balanceAddVal);
		findTheMember(_member);
		cout << endl << "Bakiye yuklendi. Yeni bakiyen: " << _member.getBalance()<<endl<<endl;
		system("pause");
		userMenu(_member);
	}
	else if (choice == 5) {
		system("cls");
		cout << "Uyelik seviyen: " << _member.getMemberType() << endl << endl;
		if (_member.getMemberType() == "silver") {
			string memberchoicesilv;
			cout << "Su anki ayricaliklarin: 20 GYM/ay" << endl;
			cout << endl << "Sauna, Havuz ve PT gibi ayricaliklar icin seviyeni yukseltebilirsin!" << endl<<endl;

			cout << "(250 TL) Gold: 30 GYM, 5 Sauna, 5 Havuz, 3 PT seans / ay" << endl;
			cout << "(500 TL) Platinum: 30 GYM, 7 sauna, 7 havuz, 5 PT seans / ay" << endl;
			cout << "(1000 TL) Diamond: 30 GYM, 10 sauna, 10 havuz, 7 PT seans / ay" << endl;

			cout << endl << "Yukselmek istedigin seviyeyi sec: ";
			cin >> memberchoicesilv;
			transform(memberchoicesilv.begin(), memberchoicesilv.end(), memberchoicesilv.begin(), ::tolower);
			if (memberchoicesilv == "gold" && _member.getBalance() >= 250) {
				_member.setMemberType("gold");
				_member.setBalance(_member.getBalance() - 250);
				findTheMember(_member);
				system("cls");
				cout << "Artik GOLD uyesisin!" << endl << endl;
				system("pause");
				userMenu(_member);
			}
			else if (memberchoicesilv == "platinum" && _member.getBalance() >= 500) {
				_member.setMemberType("platinum");
				_member.setBalance(_member.getBalance() - 500);
				findTheMember(_member);
				system("cls");
				cout << "Artik PLATINUM uyesisin!" << endl << endl;
				system("pause");
				userMenu(_member);
			}
			else if (memberchoicesilv == "diamond" && _member.getBalance() >= 1000) {
				_member.setMemberType("diamond");
				_member.setBalance(_member.getBalance() - 1000);
				findTheMember(_member);
				system("cls");
				cout << "Artik DIAMOND uyesisin!" << endl << endl;
				system("pause");
				userMenu(_member);
			}
			else {
				system("cls");
				cout << "Yeterli bakiyeniz bulunmuyor." << endl << endl;
				system("pause");
				userMenu(_member);
			}
		}
		else if (_member.getMemberType() == "gold") {
			string memberchoicegold;
			cout << "Su anki ayricaliklarin: 30 GYM, 5 Sauna, 5 Havuz, 3 PT seans / ay" << endl;
			cout << endl << "Ayricaliklarinin artmasi icin seviyeni yukseltebilirsin!" << endl << endl;

			cout << "(500 TL) Platinum: 30 GYM, 7 sauna, 7 havuz, 5 PT seans / ay" << endl;
			cout << "(1000 TL) Diamond: 30 GYM, 10 sauna, 10 havuz, 7 PT seans / ay" << endl;

			cout << endl << "Yukselmek istedigin seviyeyi sec: ";
			cin >> memberchoicegold;
			transform(memberchoicegold.begin(), memberchoicegold.end(), memberchoicegold.begin(), ::tolower);
			if (memberchoicegold == "platinum" && _member.getBalance() >= 500) {
				_member.setMemberType("platinum");
				_member.setBalance(_member.getBalance() - 500);
				findTheMember(_member);
				system("cls");
				cout << "Artik PLATINUM uyesisin!" << endl << endl;
				system("pause");
				userMenu(_member);
			}
			else if (memberchoicegold == "diamond" && _member.getBalance() >= 1000) {
				_member.setMemberType("diamond");
				_member.setBalance(_member.getBalance() - 1000);
				findTheMember(_member);
				system("cls");
				cout << "Artik DIAMOND uyesisin!" << endl << endl;
				system("pause");
				userMenu(_member);
			}
			else {
				system("cls");
				cout << "Yeterli bakiyeniz bulunmuyor." << endl << endl;
				system("pause");
				userMenu(_member);
			}
		}
		else if (_member.getMemberType() == "platinum") {
			string memberchoiceplat;
			cout << "Su anki ayricaliklarin: 30 GYM, 7 sauna, 7 havuz, 5 PT seans / ay" << endl;
			cout << endl << "Ayricaliklarinin artmasi icin seviyeni yukseltebilirsin!" << endl << endl;

			cout << "(1000 TL) Diamond: 30 GYM, 10 sauna, 10 havuz, 7 PT seans / ay" << endl;

			cout << endl << "Yukselmek istedigin seviyeyi sec: ";
			cin >> memberchoiceplat;
			transform(memberchoiceplat.begin(), memberchoiceplat.end(), memberchoiceplat.begin(), ::tolower);
			if (memberchoiceplat == "diamond" && _member.getBalance() >= 1000) {
				_member.setMemberType("diamond");
				_member.setBalance(_member.getBalance() - 1000);
				findTheMember(_member);
				system("cls");
				cout << "Artik DIAMOND uyesisin!" << endl << endl;
				system("pause");
				userMenu(_member);
			}
			else {
				system("cls");
				cout << "Yeterli bakiyeniz bulunmuyor." << endl << endl;
				system("pause");
				userMenu(_member);
			}
		}
		else if (_member.getMemberType() == "diamond") {
			cout << "Halihazirda DIAMOND uyesiniz ve tum ayricaliklardan yararlaniyorsunuz!" << endl << endl;
			system("pause");
			userMenu(_member);
		}
	}
	else if (choice == 0) {
		system("cls");
	}
	else if (choice == 6) {
		int _idRez;
		getUsableList();

		cout << endl << "Rezerve etmek istediginiz kullanilabilir ID'sini girin: ";
		cin >> _idRez;
		for (int i = 0; i < UsableList.size(); i++) {
			if (_idRez == UsableList[i].getID()) {
				if ((UsableList[i].getAccessLevel() == "diamond" && _member.getMemberType() == "diamond") || (UsableList[i].getAccessLevel() == "platinum" && _member.getMemberType() == "diamond" || _member.getMemberType() == "platinum") || (UsableList[i].getAccessLevel() == "gold" && _member.getMemberType() == "diamond" || _member.getMemberType() == "platinum" || _member.getMemberType() == "gold") || (UsableList[i].getAccessLevel() == "silver")) {
					if (UsableList[i].getIsReservable() == true) {
						if (UsableList[i].getIsReserved() == false) {
							system("cls");
							UsableList[i].reserve(_member);
							cout << "Basariyla " << UsableList[i].getName() << " urununu adiniza rezerve ettiniz." << endl;
							system("pause");
							userMenu(_member);
						}
						else if (UsableList[i].getIsReserved() == true) {
							if (UsableList[i].getReserver().getID() == _member.getID()) {
								system("cls");
								cout << "Urun halihazirda sizin tarafinizdan rezerve edilmis halde." << endl;
								system("pause");
								userMenu(_member);
							}
							else {
								system("cls");
								cout << "Urun halihazirda " << UsableList[i].getReserver().getName() << " tarafindan rezerve edilmis." << endl;
								system("pause");
								userMenu(_member);
							}
						}
					}
					else if (UsableList[i].getIsReservable() == false) {
						system("cls");
						cout << "Bu urun rezerve edilemeyen bir urundur." << endl;
						system("pause");
						userMenu(_member);
					}
				}
				else {
					system("cls");
					cout << "Uyelik seviyeniz bu urunu rezerve etmeye yetmiyor." << endl;
					system("pause");
					userMenu(_member);
				}
			}
		}
	}
	else if (choice == 7) {
		int desiredDay;
		cout << endl << "Hangi gune rezervasyon istersiniz (Haftanin kacinci gunuyse onu girin, orn. Pazartesi (1) - Persembe (4) : ";
		cin >> desiredDay;
		int desiredHour;
		cout << endl << "Rezerve ettiginiz gorusme saat kacta baslasin istersiniz (Sadece 24 saat formatinda saati girin, orn. 23, 11, 14): ";
		cin >> desiredHour;
		int desiredLength;
		cout << endl << "Gorusmenizin kac saat surmesini istiyorsunuz: ";
		cin >> desiredLength;
		cout << "Lutfen listeden gorusme rezerve etmek istediginiz PT'nin ID'sini seciniz."<<endl;
		getPTList();
		cout << endl << "Seciminiz: ";
		int ptChoice;
		int checkifExists;
		cin >> ptChoice;
		for (int i = 0; i < AdminList.size(); i++) {
			if (ptChoice == AdminList[i].getID()) {
				for (int j = 0; j < PTReqList.size();j++) {
					checkifExists = 0;
					if ((AdminList[i].getID() == PTReqList[j].getchosenPT().getID()) && (PTReqList[j].getdesiredDay() == desiredDay) && (PTReqList[j].getdesiredHour() == desiredHour) && (PTReqList[j].getisApproved() == true)) {
						checkifExists++;
					}
				}
				if (checkifExists != 0) {
					system("cls");
					cout << "Bu egitmen bu gun ve saatte doludur. Baska tercihte bulununuz." << endl;
					system("pause");
					break;
				}
				else {
					system("cls");
					addPTReq(con, desiredDay, desiredHour, desiredLength, AdminList[i], _member);
					cout << "Talebiniz basariyla sisteme eklendi. PT'nizin onay vermesi durumunda gorusmenizi yapabileceksiniz. Maillerinizi duzenli olarak kontrol ediniz." << endl;
					system("pause");
					break;
				}
			}
		}
		userMenu(_member);
	}

}



int partition(vector<int> &arr, int start, int end)
{

	int pivot = arr[start];

	int count = 0;
	for (int i = start + 1; i <= end; i++) {
		if (arr[i] <= pivot)
			count++;
	}

	int pivotIndex = start + count;
	swap(arr[pivotIndex], arr[start]);

	int i = start, j = end;

	while (i < pivotIndex && j > pivotIndex) {

		while (arr[i] <= pivot) {
			i++;
		}

		while (arr[j] > pivot) {
			j--;
		}

		if (i < pivotIndex && j > pivotIndex) {
			swap(arr[i++], arr[j--]);
		}
	}

	return pivotIndex;
}

void quickSort(vector<int>& arr, int start, int end)
{

	if (start >= end)
		return;

	int p = partition(arr, start, end);

	quickSort(arr, start, p - 1);

	quickSort(arr, p + 1, end);
}

void getLeaderboard() {

	MemberXPList.clear();

	int tempid;

	cout << "Survival of the Fit | Uye Tecrube Siralamasi" << endl << endl;

	for (int i = 0; i < MemberList.size();i++) {
		MemberXPList.push_back(MemberList[i].getXP());
	}
	quickSort(MemberXPList, 0, MemberXPList.size()-1);
	reverse(MemberXPList.begin(), MemberXPList.end());

	for (int j = 0; j < MemberXPList.size(); j++) {
		for (int z = 0; z < MemberList.size(); z++) {
			if (MemberXPList[j] == MemberList[z].getXP() && MemberList[z].getFirstName() != "NULL" && MemberList[z].getID() != tempid) {
				cout << j+1 << ". | " << MemberList[z].getName() << " - Level: " << MemberList[z].getLevel() << " - XP: " << MemberList[z].getXP() << endl;
				tempid = MemberList[z].getID();
				break;
			}
		}
	}
}

void displayMembers() {
	for (int z = 0; z < MemberList.size(); z++) {
		if(MemberList[z].getFirstName() != "NULL")
		cout << z << " - "<< MemberList[z].getName() << endl;
	}
}

void findMeGYMBuddy(Member _member) {
	
	int diff = 9999999;
	vector<Member> chosenOne;
	chosenOne.push_back(_member);
	chosenOne.clear();
	for (int j = 0; j < MemberList.size(); j++) {
		int ref = abs(_member.getXP() - MemberList[j].getXP());
		if (ref != 0 && diff > ref && MemberList[j].getFirstName() != "NULL") {
			diff = ref;
			chosenOne[0] = MemberList[j];
		}
	}

	cout << "GYM Buddy'in bulundu! " << endl << endl;
	cout << "Senin GYM Buddy'in: " << chosenOne[0].getName() << " - Buddy'nin Seviyesi: " << chosenOne[0].getLevel() << endl;
	cout << "Ona buradan ulasabilirsin: " << chosenOne[0].getEmail()<<endl<<endl;
}

void refreshDiscountList() {
	DiscountList.clear();
	for (int i = 0; i < MemberList.size(); i++) {
		if (MemberList[i].getXP() < 700 && MemberList[i].getBalance() < 1000) {
			DiscountList.push_back(MemberList[i]);
		}
	}
}

int main() {
	tryCon();
	schemaFunc();

	refreshMemberDatas(con);
	refreshEmployeeDatas(con);
	refreshUsableDatas(con);
	refreshAdminDatas(con);
	refreshPTReqDatas(con);

	refreshDiscountList();

	//start

	loginMenu();

	//end
	updateMemberDatas(con);
	updateEmployeeDatas(con);
	updateUsableDatas(con);
	updateAdminDatas(con);
	updatePTReqDatas(con);
}