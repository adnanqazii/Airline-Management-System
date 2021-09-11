#include "Airline.h"
#include "Flight.h"
#include "typedef.h"
#include "functions.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
using namespace std;

	Airline::Airline(string name)//constructor
	{
		setName(name);//set airline name
	}
	void Airline::setName(string name)//set name which should not have length zero or negative
	{
		if (name.length() > 0)
		{
			this->name = name;
		}
		else
		{
			exit(0);
		}
	}
	string Airline::getName()//name getter
	{
		return name;
	}

	Airline::~Airline() {//destructor
		int len = flights.size();
		for (int i = 0; i < len; i++) {
			delete flights[i];
		}
	}
	void Airline::print() {//print all flights
		cout <<endl<< name << endl << endl;
		for (int i = 0; i < flights.size(); i++) {
			cout << i + 1<<":" << endl;
			cout<<flights[i]->print();
			cout << endl;
		}
	}
	Airline::Airline() {//constructor

	}
	

	Flight* Airline::addFlight(string arrival, string departure, tm arrivalTime, tm departureTime, int no, string type, double fee,string mode)//add flight
	{
		Airline* airline;
		Flight* flight;
		flight = new Flight(arrival, departure, arrivalTime, departureTime, no, type, fee, this,mode);
		flights.push_back(flight);//add flgiht to flights vector
		//update airline file
		ofstream flights_file(name + ".bin", ios::out);
		boost::archive::text_oarchive oa(flights_file);
		oa << this;//serialize object
		flights_file.close();
		return flight;
	}
	//flights getter
	vector<Flight*> Airline::getFlights() {
		return flights;
	}
	

