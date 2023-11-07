#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

using namespace std;

class Person {
	protected:
		string fname;
		string lname;
		int age;
		float weight;
		float height;
		string birthdate;
	public:
		explicit Person(const string &_fname, const string &_lname, int _age, float _weight, float _height, const string &_birthdate);
		~Person();

		void setFirstName(const string &_fname);
		string getFirstName() const;
		void setLastName(const string &_lname);
		string getLastName() const;
		void setAge(int _age);
		int getAge() const;
		void setWeight(float _weight);
		float getWeight() const;
		void setHeight(float _height);
		float getHeight() const;
		void setBirthdate(const string &_birthdate);
		string getBirthdate() const;

		string getName() const;
};


#endif // !PERSON_H
