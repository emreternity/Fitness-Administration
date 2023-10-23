#include "User.h"
#include <string>
#include <stdexcept>
#include <ctime>
#include <chrono>

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
// void User::setRegdate(int _regday, int _regmonth, int _regyear) { }

// TODO: Bilgisayardan tarih verisini alan ve regday, regmonth, regyear verilerine ayrý ayrý dolduran setRegdate fonksiyonu kodlanacak.
// void User::setRegdate() { } 
// string User::getRegdate() const { }

void User::setEmail(string _email) {

	// TODO: Girilen email deðerinin _________@____.com þeklindeki geleneksel email formatýna uyup uymadýðýný belirleyen doðrulama kodlanacak.

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

// Switch Case kullanýlarak, verilen level deðerine karþýlýk gelen xp deðeri setXP fonk. ile ayarlanacak.
// void User::setLevel(int _level) { }

// Switch Case kullanýlarak, sahip olunan XP deðerine karþýlýk gelen alt taban level deðeri return edilecek.
// int User::getLevel() const { }

string User::getName() const {
	return fname + " " + lname; // TODO: Deðer doðru mu kontrol edilecek.
}