#ifndef PTREQUEST_H
#define PTREQUEST_H

#include "Member.h"
#include "Admin.h"
using namespace std;

class PTRequest {
private:
	int id;
	string requestdate;
	int desiredDay;
	int desiredHour;
	int desiredLength;
	bool isApproved;
	Member reserver;
	Admin chosenPT;
public:
	explicit PTRequest(int _desiredDay, int _desiredHour, int _desiredLength, Admin _chosenPT, Member _reserver, bool _isApproved = false);
	void setdesiredDay(int _desiredDay);
	int getdesiredDay() const;
	void setdesiredHour(int _desiredHour);
	int getdesiredHour() const;
	void setdesiredLength(int _desiredLength);
	int getdesiredLength() const;
	void setisApproved(bool _isApproved);
	bool getisApproved() const;
	void setReserver(Member _reserver);
	Member getReserver() const;
	void setchosenPT(Admin _chosenPT);
	Admin getchosenPT() const;
	void setrequestDate();
	string getrequestDate() const;

	void setID(int _id);
	int getID() const;

	void insertSQL(sql::Connection* con);
	void updateSQL(sql::Connection* con);
};


#endif