#pragma once
#ifndef AIRLINE_H
#define AIRLINE_H
#include "Flight.h"
#include "typedef.h"
#include <string>
#include <iostream>
#include <vector>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/string.hpp>
using namespace std;
class Airline
{
	friend class Admin;
	friend class Passenger;
	friend class Flight;
	friend class User;
	friend void load();
	p_list_a passengers;//map of Passenger* pointers with CNIC keys
	std::vector<Flight*> flights;
	
	string name;//airline name

	friend class boost::serialization::access;//boost requirement for serialization
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) //boost requirement for serialization
	{
		//fields of class
		ar& name;
		ar& flights;
		ar& flights;
		ar& passengers;
	}
public:
	void print();//print airline's flights
	Airline(string name);//constructor
	void setName(string name);//airline name setter
	~Airline();//destructor
	friend class Data;
	Airline();//constructor
	string getName();//name getter
	Flight* addFlight(string arrival, string departure, tm arrivalTime, tm departureTime, int no, string type, double fee,string mode);//add Flight
	vector<Flight*> getFlights();//flights getter
};

#endif

