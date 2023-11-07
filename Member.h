#ifndef MEMBER_H
#define MEMBER_H


#include "Person.h"
#include <string>

using namespace std;

class Member : public Person{
private:
	string membertype;
	string regdate;
	int xp;
	string email;
	float balance;
	float wgoal;
public:
	explicit Member(const string &_fname, const string &_lname, int _age, float _weight, float _height, const string &_birthdate, const string &_membertype, const string &_email, float _wgoal, float _balance = 0, int _xp = 0);
	~Member();

	void setMemberType(string _membertype);
	string getMemberType() const;
	void setXP(int _xp = 0);
	int getXP() const;
	void setEmail(string _email);
	string getEmail() const;
	void setBalance(float _balance = 0);
	float getBalance() const;
	void setWeightGoal(float _wgoal);
	float getWeightGoal() const;

	void setRegdate(string _regdate);
	void setRegdate();
	string getRegdate() const;
	
	int getLevel() const;
	void setLevel(int _level = 1);
};

#endif // !MEMBER_H
