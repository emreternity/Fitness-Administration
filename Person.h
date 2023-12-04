#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

using namespace std;

class Person {
	protected:
		int id;
		string fname;
		string lname;
		int age;
		float weight;
		float height;
		string birthdate;
	public:
		explicit Person(string _fname, string _lname, int _age, float _weight, float _height, string _birthdate);
		~Person();
		
		void setFirstName(string _fname);
		string getFirstName() const;
		void setLastName(string _lname);
		string getLastName() const;
		void setAge(int _age);
		int getAge() const;
		void setWeight(float _weight);
		float getWeight() const;
		void setHeight(float _height);
		float getHeight() const;
		void setBirthdate(string _birthdate);
		string getBirthdate() const;

		string getName() const;

		void setID(int _id);
		int getID() const;
		
		void seeValues() const;
};


#endif // !PERSON_H
