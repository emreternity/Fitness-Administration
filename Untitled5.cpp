#include <iostream>
#include "Person.h"
#include "Member.h"
#include "Usable.h"
#include "Employee.h"

using namespace std;

int main(){
	Person p1("Beyzanur","Baki",20,65.5,165.4,"15/10/2001");
	Member m1("Emre","Dolas",20,90.2,178.4,"15/09/2003","diamond","emredolas@gmail.com",85,1000,25000);
	Usable sauna1(10,"Sauna 1",m1,"sauna","gold",true,true);
	Employee e1("Ozlem","Babatutmaz",22,70.2,176,"10/02/2004","20/10/2022",15,"N/A",30000,"gorevli");
	
	cout<<p1.getName()<<endl;
	cout<<m1.getEmail()<<endl;
	cout<<sauna1.getCapacity()<<endl;
	e1.setEmployeeType("egitmen");
	cout<<e1.getEmployeeType()<<endl;
	p1.setFirstName("MagicBeyza");
	cout<<"Isim degistikten sonra: ";
	cout<<p1.getName()<<endl<<endl;
	
	cout<<m1.getLevel()<<endl;
	m1.setXP(1000);
	cout<<m1.getLevel()<<endl;
	m1.setLevel(8);
	cout<<m1.getXP()<<endl;
	cout<<m1.getLevel()<<endl;
	
	
	
}
