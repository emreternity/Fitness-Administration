#include "Member.h"
#include <string>
#include <stdexcept>
#include <chrono>
#include <regex> 
#include <algorithm>

Member::Member(const string &_fname, const string &_lname, int _age, float _weight, float _height,const string &_birthdate, const string &_membertype,const string &_email, float _wgoal, float _balance = 0, int _xp = 0) : Person(_fname, _lname, _age, _weight, _height, _birthdate) {
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
	if (_membertype != "silver" || _membertype != "gold" || _membertype != "platinum" || _membertype != "diamond"){
		throw invalid_argument("Uyelik tipi mevcut degil.");
	}
	else {
		membertype = _membertype;
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

void Member::setBalance(float _balance = 0) {
	if (_balance > 0) {
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

void Member::setXP(int _xp = 0) {
	if (_xp > 0) {
		xp = _xp;
	}
	else {
		throw invalid_argument("Tecrube puani sifirdan kucuk olamaz.");
	}
}

int Member::getXP() const {
	return xp;
}

void Member::setLevel(int _level = 1) {
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

