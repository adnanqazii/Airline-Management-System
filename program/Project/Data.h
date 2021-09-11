#pragma once
#ifndef DATA_H
#define DATA_H
#include <vector>
#include "Airline.h"
#include "User.h"

//airlines and users
extern vector<User*> users;
extern vector<Airline*> airlines;
//	friend class Passenger;
	 void load();
	 void output();


#endif