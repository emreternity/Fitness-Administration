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
		string reserver;
		
	public:
		explicit Usable(int _capacity, const string &_name, const string &_usableType = "equipment", const string &_accessLevel = "silver", bool _isReservable = true, bool _isReserved = false, const string &_reserver = "N/A");
		~Usable();
		void setCapacity(int _capacity);
		void setName(const string &_name);
		void setUsableType(const string &_usableType);
		void setAccessLevel(const string &_accessLevel);
		void setIsReservable(bool _isReservable);
		void setReserver(const string &_reserver);
		
		int getCapacity() const;
		string getName() const;
		string getUsableType() const;
		string getAccessLevel() const;
		bool getIsReservable() const;
		bool getIsReserved() const;
		string getReserver() const;
		
		void reserve(const string &_reserver);
		void unreserve();
};

#endif // !USABLE_H
