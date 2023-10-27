#include "User.h"
#include <string>
#include <stdexcept>
#include <chrono>
#include <regex> 
#include <algorithm>

User::User(string _fname, string _lname, string _usertype, int _age, float _weight, float _height, string _email, float _balance = 0, int _xp = 0) {
	setFirstName(_fname);
	setLastName(_lname);
	setAge(_age);
	setWeight(_weight);
	setHeight(_height);
	setRegdate();
	setEmail(_email);
	setBalance(_balance);
	setXP(_xp);
}

User::~User() {
	
}

void User::setFirstName(string _fname) {
	if (_fname.length() < 1 || _fname.length() > 18)
	{
		throw invalid_argument("Isim cok uzun ya da cok kisa.");
	}
	else {
		fname = _fname;
	}
}

string User::getFirstName() const {
	return fname;
}

void User::setLastName(string _lname) {
	if (_lname.length() < 1 || _lname.length() > 18)
	{
		throw invalid_argument("Soyisim cok uzun ya da cok kisa.");
	}
	else {
		lname = _lname;
	}
}

string User::getLastName() const {
	return lname;
}

void User::setUserType(string _usertype) {
	transform(_usertype.begin(), _usertype.end(), _usertype.begin(), ::tolower);
	if (_usertype != "silver" || _usertype != "gold" || _usertype != "platinum" || _usertype != "diamond"){
		throw invalid_argument("Uyelik tipi mevcut degil.");
	}
	else {
		usertype = _usertype;
	}
}

string User::getUserType() const{
	return usertype;
}

void User::setAge(int _age) {
	if (_age < 14 || _age > 65) {
		throw invalid_argument("GYM uyeligimiz icin yasiniz uygun degildir.");
	}
	else {
		age = _age;
	}
}

int User::getAge() const {
	return age;
}

void User::setWeight(float _weight) {
	if (_weight < 30 || _weight > 300) {
		throw invalid_argument("Lutfen gecerli bir kilo degeri giriniz.");
	}
	else {
		weight = _weight;
	}
}

float User::getWeight() const {
	return weight;
}

void User::setHeight(float _height) {
	if (_height < 100 || _height > 250) {
		throw invalid_argument("Lutfen gecerli bir boy degeri giriniz.");
	}
	else {
		height = _height;
	}
}

float User::getHeight() const {
	return height;
}

void User::setRegdate(string _regdate) { 
	regdate = _regdate;
}

void User::setRegdate() {
	time_t t = time(nullptr);
	char mbstr[11];
	strftime(mbstr, sizeof(mbstr), "%d/%m/%Y", localtime(&t));
	regdate = mbstr;
}
 
string User::getRegdate() const { 
	return regdate;
}

const regex emailpattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

void User::setEmail(string _email) {

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

string User::getEmail() const {
	return email;
}

void User::setBalance(float _balance) {
	if (_balance > 0) {
		balance = _balance;
	}
	else {
		throw invalid_argument("Bakiye sifirdan kucuk olamaz.");
	}
}

float User::getBalance() const {
	return balance;
}

void User::setXP(int _xp) {
	if (_xp > 0) {
		xp = _xp;
	}
	else {
		throw invalid_argument("Tecrube puani sifirdan kucuk olamaz.");
	}
}

int User::getXP() const {
	return xp;
}

void User::setLevel(int _level) {
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

int User::getLevel() const { 
	int i = 0;
	int level = 1;
	while (i + ((level + 1) * 50) <= xp) {
		level++;
		i += level * 50;
	}
	return level;
}

string User::getName() const {
	return fname + " " + lname;
}
