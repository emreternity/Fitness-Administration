#include <iostream>
#include "Person.h"
#include "Member.h"
#include "Usable.h"
#include "Employee.h"

using namespace std;

int main(){
	Member nullreserver("NULL","NULL",20,100,180,"01/01/0001","platinum","nullemail@gmail.com",100,0,0);
	Member m1("Emre","Emreto",20,89,178,"15/09/2003","platinum","emremreto@gmail.com",70,5000,150000);
	Usable u1(100,"Weight 1",nullreserver,"equipment","silver",true,false);
	u1.seeValues();
	u1.setCapacity(150);
	u1.setName("Test Name");
	u1.setUsableType("pool");
	u1.setAccessLevel("platinum");
	u1.reserve(m1);
	u1.seeValues();
	
}
