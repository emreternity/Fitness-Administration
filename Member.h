#ifndef MEMBER_H
#define MEMBER_H


#include "Person.h"

using namespace std;

class Member : public Person{

	friend class Usable;
	friend class PTRequest;

private:	
	string username;
	string password;
	string membertype;
	string regdate;
	int xp;
	string email;
	float balance;
	float wgoal;
	int id;
public:
	explicit Member(string _fname, string _lname, int _age, float _weight, float _height, string _birthdate, string _membertype, string _email, float _wgoal, string _username, string _password, float _balance = 0, int _xp = 0);
	~Member();

	Member& operator++();
	Member operator++(int number);
	Member& operator+=(int balanceIncrease);

	Member& operator--();
	Member operator--(int number);
	Member& operator-=(int balanceDecrease);

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
	void setUsername(string _username);
	string getUsername() const;
	void setPassword(string _password);
	string getPassword() const;

	void setRegdate(string _regdate);
	void setRegdate();
	string getRegdate() const;
	
	int getLevel() const;
	void setLevel(int _level = 1);
	void seeValues() const;
	
	float calculateBMI() const;

	void insertSQL(sql::Connection* con);
	void updateSQL(sql::Connection* con);
};

#endif // !MEMBER_H
