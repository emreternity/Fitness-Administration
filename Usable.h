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
		explicit Usable(int _capacity, const string &_name, Member _reserver, const string &_usableType = "equipment", const string &_accessLevel = "silver", bool _isReservable = true, bool _isReserved = false);
		~Usable();
		void setCapacity(int _capacity);
		void setName(const string &_name);
		void setUsableType(const string &_usableType);
		void setAccessLevel(const string &_accessLevel);
		void setIsReservable(bool _isReservable);
		
		int getCapacity() const;
		string getName() const;
		string getUsableType() const;
		string getAccessLevel() const;
		bool getIsReservable() const;
		bool getIsReserved() const;
		Member getReserver() const;
		
		void reserve(Member _reserver);
		void unreserve(Member _nullreserver);
};

#endif // !USABLE_H
