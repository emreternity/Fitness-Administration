#include "Member.h"
#include <string>
#include <stdexcept>
#include <chrono>
#include <regex> 
#include <algorithm>

Member::Member(string _fname, string _lname, int _age, float _weight, float _height,string _birthdate, string _membertype,string _email, float _wgoal, float _balance, int _xp) : Person(_fname, _lname, _age, _weight, _height, _birthdate) {
	setMemberType(_membertype);
	setEmail(_email);
	setWeightGoal(_wgoal);
	setBalance(_balance);
	setRegdate();
	setXP(_xp);
}

Member::~Member() {
	
}


void Member::setMemberType(string _membertype) {
	transform(_membertype.begin(), _membertype.end(), _membertype.begin(), ::tolower);
	if (_membertype == "silver" || _membertype == "gold" || _membertype == "platinum" || _membertype == "diamond"){
		membertype = _membertype;
	}
	else {
		throw invalid_argument("Uyelik tipi mevcut degil.");
	}
}

string Member::getMemberType() const{
	return membertype;
}

void Member::setRegdate(string _regdate) { 
	regdate = _regdate;
}

void Member::setRegdate() {
	time_t t = time(nullptr);
	char mbstr[11];
	strftime(mbstr, sizeof(mbstr), "%d/%m/%Y", localtime(&t));
	regdate = mbstr;
}
 
string Member::getRegdate() const { 
	return regdate;
}

const regex emailpattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

void Member::setEmail(string _email) {

	if (_email.length() > 256 || _email.length() < 1) {
		throw invalid_argument("Gecersiz email uzunlugu.");
	}
	else {
		if (regex_match(_email, emailpattern)){
			email = _email;
		}
		else {
			throw invalid_argument("Gecersiz e-posta formati.");
		}
	}
}

string Member::getEmail() const {
	return email;
}

void Member::setBalance(float _balance) {
	if (_balance >= 0) {
		balance = _balance;
	}
	else {
		throw invalid_argument("Bakiye sifirdan kucuk olamaz.");
	}
}

float Member::getBalance() const {
	return balance;
}

void Member::setWeightGoal(float _wgoal) {
	if (_wgoal > 0 && _wgoal < 200) {
		wgoal = _wgoal;
	}
	else {
		throw invalid_argument("Gecersiz hedef kilo degeri girdiniz.");
	}
}

float Member::getWeightGoal() const {
	return wgoal;
}

void Member::setXP(int _xp) {
	if (_xp >= 0) {
		xp = _xp;
	}
	else {
		throw invalid_argument("Tecrube puani sifirdan kucuk olamaz.");
	}
}

int Member::getXP() const {
	return xp;
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
		xp = prexp;
	}
}

int Member::getLevel() const { 
	int i = 0;
	int level = 1;
	while (i + ((level + 1) * 50) <= xp) {
		level++;
		i += level * 50;
	}
	return level;
}

int Member::calculateBMI() const {
	int heightinmeters = height / 100;
	return weight / (heightinmeters * heightinmeters);
}

void Member::seeValues() const {
	cout<<"First Name: "<<getFirstName()<<endl;
	cout<<"Last Name: "<<getLastName()<<endl;
	cout<<"Full Name: "<<getName()<<endl;
	cout<<"Age: "<<getAge()<<endl;
	cout<<"Weight: "<<getWeight()<<endl;
	cout<<"Height: "<<getHeight()<<endl;
	cout<<"Birthdate: "<<getBirthdate()<<endl;
	cout<<"Membertype: "<<getMemberType()<<endl;
	cout<<"Regdate: "<<getRegdate()<<endl;
	cout<<"Email: "<<getEmail()<<endl;
	cout<<"Balance: "<<getBalance()<<endl;
	cout<<"Weight Goal: "<<getWeightGoal()<<endl;
	cout<<"XP: "<<getXP()<<endl;
	cout<<"Level: "<<getLevel()<<endl;
	
	cout<<"Test Over."<<endl<<endl;
}

void Member::insertSQL(sql::Connection* con){
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;
	
	pstmt = con->prepareStatement("INSERT INTO member(fname,lname,age,weight,height,birthdate,membertype,email,wgoal,balance,xp) VALUES(?,?,?,?,?,?,?,?,?,?,?);");
	pstmt->setString(1, fname);
	pstmt->setString(2, lname);
	pstmt->setInt(3, age);
	pstmt->setDouble(4, weight);
	pstmt->setDouble(5, height);
	pstmt->setString(6, birthdate);
	pstmt->setString(7, membertype);
	pstmt->setString(8, email);
	pstmt->setDouble(9, wgoal);
	pstmt->setDouble(10, balance);
	pstmt->setDouble(11, xp);
	pstmt->execute();
	
	pstmt = con->prepareStatement("SELECT MAX(id) FROM member;");
	result = pstmt->executeQuery();
	while (result->next())
	id = result->getInt(1);

	delete pstmt;
	delete result;
}

void Member::updateSQL(sql::Connection* con){
	sql::PreparedStatement* pstmt;
		
	pstmt = con->prepareStatement("UPDATE member SET fname = ?,lname = ?,age = ?,weight = ?,height = ? ,birthdate = ?,membertype = ?, email = ?, wgoal = ?, balance = ?, xp = ? WHERE id = ?");
	pstmt->setString(1, fname);
	pstmt->setString(2, lname);
	pstmt->setInt(3, age);
	pstmt->setDouble(4, weight);
	pstmt->setDouble(5, height);
	pstmt->setString(6, birthdate);
	pstmt->setString(7, membertype);
	pstmt->setString(8, email);
	pstmt->setDouble(9, wgoal);
	pstmt->setDouble(10, balance);
	pstmt->setDouble(11, xp);
	pstmt->setInt(12, id);
	pstmt->executeQuery();
	
	delete pstmt;
}
