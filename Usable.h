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
		explicit Usable(int _capacity, string _name, Member _reserver, string _usableType = "equipment", string _accessLevel = "silver", bool _isReservable = true, bool _isReserved = false);
		~Usable();
		void setCapacity(int _capacity);
		void setName(string _name);
		void setUsableType(string _usableType);
		void setAccessLevel(string _accessLevel);
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
