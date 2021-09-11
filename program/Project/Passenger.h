#pragma once
#ifndef PASSENGER_H
#define PASSENGER_H
#include <iostream>
#include "User.h"
#include "Account.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/export.hpp>
using namespace std;
class Flight;
class Airline;
class Passenger :
	public User
{
	int seat;//seat
	long long reservationNo;//reservation no
	string meal;//meal
	Flight* flight;//flight of passenger
	Account* account;//account of passenger
	friend class boost::serialization::access;//boost requirement for serialization
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) { //boost requirement for serialization
		ar& boost::serialization::base_object<User>(*this);//boost requirement for inherited class
		//fields
		ar& seat;
		ar& flight;
		ar& meal;
		ar& reservationNo;
		ar& account;
		
	}
public:
	
	friend class Flight;
	friend class User;
	Passenger(User* user, int seat, Flight* flight,string meal,Account* account);//constructor
	Passenger() {}//constructor
	~Passenger();//destructor
	void cancelReservation();//cancel reservation
	void changeSeat(int seat);//change seat
	int getSeat();//seat getter
	void addFlight(Flight* flight);//flight setter
	string getMeal();//meal getter
	long getReservation();//reservation no getter
	string print();//print reservation information
};


#endif
