#include "Flight.h"
#include "Airline.h"
#include <iostream>
#include <string>
#include <vector>
#include "Passenger.h"
#include "Admin.h"
#include "typedef.h"
#include <chrono>
#include <sstream>
#include <ctime>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/map.hpp>
#include <fstream>
using namespace std;
//constructor
	Flight::Flight(string arrival, string departure, tm arrivalTime, tm departureTime, int no, string type, double fee,Airline* airline,string mode)
	{
		if (no > 0)//set max passengers variable if positive
		{
			this->no = no;
		}
		else {//default max passengers count is 10
			this->no = 10;
		}
		//setting fields
		this->mode = mode;
		setArrival(arrival);
		setDeparture(departure);
		setArrivalTime(arrivalTime);
		setDepartureTime(departureTime);
		this->airline = airline;
		//flight class should be business or economic only
		if (type == "business" || type == "economic")
		{
			this->type = type;
		}
		else
		{
			exit(0);
		}
		if (fee > 0)//fee should be positive
		{
			this->fee = fee;
		}
		else
		{
			exit(0);
		}
	}
	//constructor
	Flight::Flight() {}
	//assignment operator
	void Flight::operator=(const Flight& flight) {
		
	}
	int Flight::searchCNIC(string CNIC) {
		
		for (int i = 0; i < CNICs.size(); i++) {
			if (CNICs[i] == CNIC) {
				return 1;
			}
		}
		return 0;
	}
	//check seat function
	int* Flight::checkSeat(int seat) {
		int flag = 0;
		p_iterator p = (passengers).begin();
		p_iterator pe = (passengers).end();
		int* seats = new int[no+1];
		for (int i = 1; i <= no; i++) {
			seats[i] = 0;
		}
		while (p != pe) {
			seats[p->first] = 1;
			if (p->second->getSeat() == seat) {
				flag = 1;//set flag if seat is occupied
			}
			p++;
		}
		if (flag == 1) {
			return seats;//return seats array
		}
		else {
			delete seats;//delete seats array if requested seat is unoccupied
			return 0;
		}
	}
	void Flight::addPassenger(Passenger* passenger)//add passenger
	{
		if (static_cast<int>((passengers).size()) < no)//add if there is space in flight
		{
			(this->passengers).insert(addPair(passenger->getSeat(), passenger));//add to passengers vector
			airline->passengers.insert(addPair_a(passenger->getCNIC(), passenger));//add to airline's passengers vector
			Admin::addRevenue(fee);//add revenue
			
		}
		else {//if plane is full
			cout << "Plane is full\n";
		}
	}
	double Flight::getFee() {//get fee
		return fee;
	}
	Flight::~Flight() {//destructor
		int len=passengers.size();
		for (int i = 0; i < len; i++) {
			delete passengers[i];
		}
	}
	tm Flight::getArrivalTime()//arrival time getter
	{
		return arrivalTime;
	}
	int Flight::getNo() {//max passengers getter
		return no;
	}

	tm Flight::getDepartureTime()//departure time getter
	{
		return  departureTime;
	}
	void Flight::setArrival(string arrival)//set arrival place
	{
			this->arrival = arrival;	
	}
	void Flight::setDeparture(string departure)//set departure place
	{
		this->departure = departure;
	}
	void Flight::setArrivalTime(tm arrivalTime)//arrival time setter
	{
		this->arrivalTime = arrivalTime;
	}
	void Flight::setDepartureTime(tm departureTime)//departure time setter
	{
		this->departureTime = departureTime;
	}
	string Flight::getArrival()//arrival place getter
	{
		return arrival;
	}
	string Flight::getDeparture()//departure place getter
	{
		return departure;
	}
	string Flight::getType() {//flight class getter
		return type;
	}
	string Flight::getMode() {//returns National or International
		return mode;
	}
	string Flight::print() {//generate flight info
		stringstream s;
		s << mode << " flight\n";
			s << "Airline: " << airline->getName() << endl;
			s << "Arrival Place: " << arrival << endl;
			s << "Departure Place: " << departure << endl;
			s << "Arrival Time: " << asctime(&arrivalTime);
			s << "Departure Time: " << asctime(&departureTime);
			s << "Class: " << type << endl;
			s << "Fee: Rs" << fee << endl;
			s << "Current passengers in plane: " << (passengers).size() << endl;
			s << "Maximum passengers in plane: " << no << endl;
			string ss=s.str();
			return ss;
		}
	
