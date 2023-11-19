#include "Member.h"
#include <string>
#include <stdexcept>
#include <chrono>
#include <regex> 
#include <algorithm>

#include "sqlstuff.h"

Member::Member(string _fname, string _lname, int _age, float _weight, float _height,string _birthdate, string _membertype,string _email, float _wgoal, float _balance, int _xp) : Person(_fname, _lname, _age, _weight, _height, _birthdate) {
	tryCon();
	schemaFunc();

	pstmt = con->prepareStatement("INSERT INTO member(fname,lname,age,weight,height,birthdate,membertype,email,wgoal,balance,xp) VALUES(?,?,?,?,?,?,?,?,?,?,?)");
	pstmt->setString(1, _fname);
	pstmt->setString(2, _lname);
	pstmt->setInt(3, _age);
	pstmt->setDouble(4, _weight);
	pstmt->setDouble(5, _height);
	pstmt->setString(6, _birthdate);
	pstmt->setString(7, _membertype);
	pstmt->setString(8, _email);
	pstmt->setDouble(9, _wgoal);
	pstmt->setDouble(10, _balance);
	pstmt->setDouble(11, _xp);
	pstmt->execute();

	delete pstmt;

	pstmt = con->prepareStatement("SELECT MAX(id) FROM member;");
	result = pstmt->executeQuery();
	while (result->next())
		id = result->getInt(1);

	delete result;
	delete pstmt;
}

Member::~Member() {
	pstmt = con->prepareStatement("DELETE FROM member WHERE id = ?");
	pstmt->setInt(1, id);

	delete pstmt;
}


void Member::setMemberType(string _membertype) {
	transform(_membertype.begin(), _membertype.end(), _membertype.begin(), ::tolower);
	if (_membertype != "silver" || _membertype != "gold" || _membertype != "platinum" || _membertype != "diamond"){
		throw invalid_argument("Uyelik tipi mevcut degil.");
	}
	else {
		pstmt = con->prepareStatement("UPDATE member SET membertype = ? WHERE id = ?");
		pstmt->setString(1, _membertype);
		pstmt->setInt(2, id);
		pstmt->executeQuery();
		delete pstmt;
	}
}

string Member::getMemberType() const{
	pstmt = con->prepareStatement("SELECT membertype FROM member WHERE id = ?;");
	pstmt->setInt(1, id);
	result = pstmt->executeQuery();
	while (result->next())
		return result->getString(1);
	delete result;
}

void Member::setRegdate(string _regdate) { 
	pstmt = con->prepareStatement("UPDATE member SET regdate = ? WHERE id = ?");
	pstmt->setString(1, _regdate);
	pstmt->setInt(2, id);
	pstmt->executeQuery();
	delete pstmt;
}

void Member::setRegdate() {
	time_t t = time(nullptr);
	char mbstr[11];
	strftime(mbstr, sizeof(mbstr), "%d/%m/%Y", localtime(&t));
	pstmt = con->prepareStatement("UPDATE member SET regdate = ? WHERE id = ?");
	pstmt->setString(1, mbstr);
	pstmt->setInt(2, id);
	pstmt->executeQuery();
	delete pstmt;
}
 
string Member::getRegdate() const { 
	pstmt = con->prepareStatement("SELECT regdate FROM member WHERE id = ?;");
	pstmt->setInt(1, id);
	result = pstmt->executeQuery();
	while (result->next())
		return result->getString(1);
	delete result;
}

const regex emailpattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

void Member::setEmail(string _email) {

	if (_email.length() > 256 || _email.length() < 1) {
		throw invalid_argument("Gecersiz email uzunlugu.");
	}
	else {
		if (regex_match(_email, emailpattern)){
			pstmt = con->prepareStatement("UPDATE member SET email = ? WHERE id = ?");
			pstmt->setString(1, _email);
			pstmt->setInt(2, id);
			pstmt->executeQuery();
			delete pstmt;
		}
		else {
			throw invalid_argument("Gecersiz e-posta formati.");
		}
	}
}

string Member::getEmail() const {
	pstmt = con->prepareStatement("SELECT email FROM member WHERE id = ?;");
	pstmt->setInt(1, id);
	result = pstmt->executeQuery();
	while (result->next())
		return result->getString(1);
	delete result;
}

void Member::setBalance(float _balance) {
	if (_balance > 0) {
		pstmt = con->prepareStatement("UPDATE member SET balance = ? WHERE id = ?");
		pstmt->setDouble(1, _balance);
		pstmt->setInt(2, id);
		pstmt->executeQuery();
		delete pstmt;
	}
	else {
		throw invalid_argument("Bakiye sifirdan kucuk olamaz.");
	}
}

float Member::getBalance() const {
	pstmt = con->prepareStatement("SELECT balance FROM member WHERE id = ?;");
	pstmt->setInt(1, id);
	result = pstmt->executeQuery();
	while (result->next())
		return result->getDouble(1);
	delete result;
}

void Member::setWeightGoal(float _wgoal) {
	if (_wgoal > 0 && _wgoal < 200) {
		pstmt = con->prepareStatement("UPDATE member SET wgoal = ? WHERE id = ?");
		pstmt->setDouble(1, _wgoal);
		pstmt->setInt(2, id);
		pstmt->executeQuery();
		delete pstmt;
	}
	else {
		throw invalid_argument("Gecersiz hedef kilo degeri girdiniz.");
	}
}

float Member::getWeightGoal() const {
	pstmt = con->prepareStatement("SELECT wgoal FROM member WHERE id = ?;");
	pstmt->setInt(1, id);
	result = pstmt->executeQuery();
	while (result->next())
		return result->getDouble(1);
	delete result;
}

void Member::setXP(int _xp) {
	if (_xp > 0) {
		pstmt = con->prepareStatement("UPDATE member SET xp = ? WHERE id = ?");
		pstmt->setDouble(1, _xp);
		pstmt->setInt(2, id);
		pstmt->executeQuery();
		delete pstmt;
	}
	else {
		throw invalid_argument("Tecrube puani sifirdan kucuk olamaz.");
	}
}

int Member::getXP() const {
	pstmt = con->prepareStatement("SELECT xp FROM member WHERE id = ?;");
	pstmt->setInt(1, id);
	result = pstmt->executeQuery();
	while (result->next())
		return result->getInt(1);
	delete result;
}

void Member::setLevel(int _level) {
	if (_level < 1) {
		throw invalid_argument("Lutfen seviye icin birden buyuk bir deger giriniz.");
	}
	else {
		int prexp = 0;
		for (int i = 2; i <= _level; i++) {
			prexp += i * 50;
		}
		pstmt = con->prepareStatement("UPDATE member SET xp = ? WHERE id = ?");
		pstmt->setDouble(1, prexp);
		pstmt->setInt(2, id);
		pstmt->executeQuery();
		delete pstmt;
	}
}

int Member::getLevel() const {
	int xp = getXP();

	int i = 0;
	int level = 1;
	while (i + ((level + 1) * 50) <= xp) {
		level++;
		i += level * 50;
	}
	return level;

	delete result;
}

