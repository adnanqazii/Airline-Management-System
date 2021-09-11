#pragma once
#ifndef FLIGHT_H
#define FLIGHT_H
#include <iostream>
#include <string>
#include <vector>
#include "Passenger.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <chrono>
#include <ctime>
#include <boost/serialization/map.hpp>
#include "typedef.h"
#include <boost/serialization/string.hpp>
using namespace std;
class Airline;
namespace boost { 
	namespace serialization {

		template<class Archive>
		void serialize(Archive& ar, tm& g, const unsigned int version) //boost requirement for serialization
		{
			ar& g.tm_sec;
			ar& g.tm_min;
			ar& g.tm_hour;
			ar& g.tm_mday;
			ar& g.tm_mon;
			ar& g.tm_year;
			ar& g.tm_wday;
			ar& g.tm_yday;
			ar& g.tm_isdst;
		}

	} //defining function outside class
}
class Flight
{
	string arrival;//flight arrival place
	string departure;//flight departure place
	struct tm arrivalTime;//flight arrival time
	struct tm departureTime;//departure time
	string type;//flight class
	p_list passengers;//map of Passenger* pointers with seat keys
	int no = 0;//maximum passengers
	string mode;//national or international
	double fee;//fee of flight
	Airline* airline;//flight's airline
	
	 vector<string>CNICs;//CNICs of all users
	friend class boost::serialization::access;//boost requirement for serialization
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version)//boost requirement for serialization
	{
		ar& arrival;
		ar& departure;
		ar& arrivalTime;
		ar& departureTime;
		ar& type;
		ar& airline;
		ar& no;
		ar& fee;
		ar& passengers;
		ar& mode;
		ar& CNICs;
	}

	

//restricting them to prevent shallow copy
private:
	Flight(const Flight& flight);
	void operator=(const Flight& flight);
public:
	double getFee();//fee getter
	friend class Admin;
	friend class Passenger;
	friend class User;

	int searchCNIC(string CNIC);
	
	string getMode();//returns national or international
	Flight();//constructor
	int* checkSeat(int seat);
	Flight(string arrival, string departure, tm arrivalTime, tm departureTime, int no, string type, double fee, Airline* airline,string mode);//constructor
	void addPassenger(Passenger* passenger);//add passenger

	 tm getArrivalTime();//arrival time getter

	 tm getDepartureTime();//departure time getter
	 int getNo();//maximum passengers getter
	void setArrival(string arrival);//arrival place setter

	void setDeparture(string departure);//departure place setter

	void setArrivalTime(tm arrivalTime);//arrival time setter

	void setDepartureTime(tm departureTime);//departure time setter

	string getArrival();//arrival place getter

	string getDeparture();//departure place getter
	string getType();//flight class getter
	string print();//print flight information
	~Flight();//destructor
};

#endif

