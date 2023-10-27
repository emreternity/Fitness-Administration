#include "User.h"
#include <string>
#include <stdexcept>
#include <chrono>
#include <algorithm>

User::User(string _fname, string _lname, int _age, float _weight, float _height, string _email, float _balance = 0, int _xp = 0) {
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
	// TODO: Üyenin database'teki siliniþini gerçekleþtirecek kod yazýlacak.
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
	_usertype = transform(_usertype.begin(), _usertype.end(), _usertype.begin(), ::tolower);
	if (_usertype != "silver" || _usertype != "gold" || _usertype != "platinum" || _usertype != "diamond"){
		throw invalid_argument("Uyelik tipi mevcut degil.")
	}
	else {
		usertype = _usertype;
	}
}

string User::getUserType() {
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

// TODO: Günlerin aya ve yýla göre sýnýrlandýrýlmasý saðlanacak, þubat ayýnýn 29 çektiði günler gibi özel durumlar göz önünde bulundurularak kodlanacak.
// ! Solved: Doðrulama main içerisinde, chrono kullanýlarak parametre üzerinde yapýlacak.
// void User::setRegdate(string _regyear) { }

void User::setRegdate() {
	const auto now = chrono::system_clock::now();
	const time_t t_c = chrono::system_clock::to_time_t(now);
	regdate = ctime(&t_c);
}
 
string User::getRegdate() const { 
	return regdate;
}

void User::setEmail(string _email) {

	// TODO: Girilen email deðerinin _________@____.com þeklindeki geleneksel email formatýna uyup uymadýðýný belirleyen doðrulama kodlanacak.
	// ! Solved: Email doðrulamasý main.cpp içerisinde, parametre üzerinde regex ile yapýlacak. bkz. https://www.geeksforgeeks.org/check-if-given-email-address-is-valid-or-not-in-cpp/ | https://www.geeksforgeeks.org/regex-regular-expression-in-c/

	if (_email.length() > 256 || _email.length() < 1) {
		throw invalid_argument("Gecersiz email uzunlugu.");
	}
	else {
		email = _email;
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

// Switch Case kullan?larak, verilen level de?erine kar??l?k gelen xp de?eri setXP fonk. ile ayarlanacak.
// void User::setLevel(int _level) { }

// Switch Case kullan?larak, sahip olunan XP de?erine kar??l?k gelen alt taban level de?eri return edilecek.
// int User::getLevel() const { }

string User::getName() const {
	return fname + " " + lname; // TODO: De?er do?ru mu kontrol edilecek.
}
