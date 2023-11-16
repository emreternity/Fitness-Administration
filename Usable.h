#ifndef USABLE_H
#define USABLE_H

#include <string>
#include "Member.h"

class Usable {
	private:
		int capacity;
		string name;
		string usableType;
		string accessLevel;
		bool isReservable;
		bool isReserved;
		Member reserver;
		
	public:
		explicit Usable(int _capacity, const string &_name, const string &_usableType = "equipment", const string &_accessLevel = "silver", bool _isReservable = true, Member _reserver = Member("N/A","N/A",20,90,50,"01/01/2000","silver","nullreserver@gmail.com",1));
		~Usable();
		void setCapacity(int _capacity);
		void setName(const string &_name);
		void setUsableType(const string &_usableType);
		void setAccessLevel(const string &_accessLevel);
		void setIsReservable(bool _isReservable);
		void setReserver(Member _reserver);
		
		int getCapacity() const;
		string getName() const;
		string getUsableType() const;
		string getAccessLevel() const;
		bool getIsReservable() const;
		bool getIsReserved() const;
		Member getReserver() const;
		
		void reserve(Member _reserver);
		void unreserve();
		string getReserverInfo() const;
};

#endif // !USABLE_H
