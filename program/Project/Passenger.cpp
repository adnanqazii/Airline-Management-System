#include "Passenger.h"
#include "User.h"
#include "Airline.h"
#include "Flight.h"
#include "Admin.h"
#include "typedef.h"
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include "Account.h"
#include <boost/serialization/export.hpp>
BOOST_CLASS_EXPORT_GUID(Passenger, "Passenger")
using namespace std;
string Passenger::getMeal() {//meal getter
	return meal;
}
long Passenger::getReservation() {//reservation no getter
	return reservationNo;
}
//constructor
	Passenger::Passenger(User* user, int seat, Flight* flight,string meal,Account* account):User(*user)
	{
		//generating random reservation no
		srand((unsigned)time(0));
		reservationNo = rand() % (99999999) + 10000000;
		int* seats = flight->checkSeat(seat);
		while (seats != 0) {//getting requested seat.loop continues if requested seat was occupied
			cout << "seat not available\nseats occupied are\n";
			int len = flight->getNo();
			for (int i = 0; i < len; i++) {//printing occupied seats
				if (seats[i] == 1) {
					cout << i << " ";
				}
			}
			cout << "\ntype another seat no\n";
			cin >> seat;//getting another seat no
			seats = flight->checkSeat(seat);//checking if seat is occupied
		}
		delete seats;//delete seats array
		seats = 0;
		//set fields
		this->seat = seat;
		this->flight = flight;
		this->meal = meal;
		this->account = account;
		flight->addPassenger(this);//add passenger to flight
	}
	//destructor
	Passenger::~Passenger() {
		delete account;
	}
	//cancel reservation
	void Passenger::cancelReservation() {
		p_iterator i = flight->passengers.find(seat);//find passenger in flight  by seat key
		flight->passengers.erase(i);//delete
		p_iterator_a ia = flight->airline->passengers.find(CNIC);//find passenger in airline by CNIC key
		flight->airline->passengers.erase(ia);//delete
		Admin::subRevenue(this->flight->getFee());//subtract revenue or pay passenger
		delete this;//destroy passenger object
	}
	void Passenger::changeSeat(int seat) {//change seat
		p_iterator i = flight->passengers.find(seat);
		if (i != flight->passengers.end()) {//check if seat was occupied using seat key above
			cout << "seat is occupied\n";
		}
		else {//if seat not occupied
			i = flight->passengers.find(this->seat);//find passenger by seat key in flight
			flight->passengers.erase(i);//delete seat-passenger pair in flight's passengers
			flight->passengers[seat] = this;//add passenger using new seat key
			this->seat = seat;//set seat field
		}
	}
	
	int Passenger::getSeat() {//get seat
		return seat;
	}
	
	void Passenger::addFlight(Flight* flight)//set flight field
	{
		this->flight = flight;
	}

	//generates passenger info
	string Passenger::print() {
		stringstream s;
		string ss;
		s << "Name: " << getName() << endl;
		s << "Age: " << getAge() << endl;
		s << "Seat no: " << seat << endl;
		s << "Flight information: \n";
	
		ss = flight->print();
		s << ss;
		ss = s.str();
		return ss;
	}


