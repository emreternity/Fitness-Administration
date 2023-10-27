#ifndef USER_H
#define USER_H



#include <string>

using namespace std;

class User {
private:
	string fname;
	string lname;
	string usertype;
	int age;
	float weight;
	float height;
	int regday;
	int regmonth;
	int regyear;
	int xp;
	string email;
	float balance;
public:
	explicit User(string _fname, string _lname, string _usertype, int _age, float _weight, float _height, string _email, float _balance = 0, int _xp = 0);
	~User();

	void setFirstName(string _fname);
	string getFirstName() const;
	void setLastName(string _lname);
	string getLastName() const;
	void setUserType(string _usertype);
	string getUserType() const;
	void setAge(int _age);
	int getAge() const;
	void setWeight(float _weight);
	float getWeight() const;
	void setHeight(float _height);
	float getHeight() const;
	void setRegday(int _regday);
	int getRegday() const;
	void setRegmonth(int _regmonth);
	int getRehmonth() const;
	void setRegyear(int _regyear);
	int getRegyear() const;
	void setXP(int _xp);
	int getXP() const;
	void setEmail(string _email);
	string getEmail() const;
	void setBalance(float _balance);
	float getBalance() const;

	string getName() const;

	void setRegdate(int _regday, int _regmonth, int _regyear);
	void setRegdate();
	string getRegdate() const;
	
	int getLevel() const;
	void setLevel(int _level);
};

#endif // !USER_H
