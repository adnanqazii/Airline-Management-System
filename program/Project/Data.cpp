#pragma once
#include "Data.h"
#include "User.h"
#include "Airline.h"
#include "Admin.h"
#include <iostream>
#include <fstream>
using namespace std;
using namespace chrono;
//airlines and users
 vector<User*> users = {};
 vector<Airline*> airlines = {};
void load() {
	//clearing vectors
	airlines.clear();
	users.clear();
	fstream file("airlines.txt", ios::in);
	ifstream filet;
	string name;
	Airline* airline;
	if (file) {
		while (true) {//opening airline files according to file names stored in airlines.txt and loading data
			file >> name;//getting airline file name
			if (file.eof()) {
				break;
			}
			else {
				filet.open(name + ".bin");
				boost::archive::text_iarchive ia{ filet };
				ia >> airline;//deserializing airline object
				airlines.push_back(airline);//adding airline to airlines vector
				filet.close();
			}
			for (int i = 0; i < airline->getFlights().size(); i++) {//adding revenue of all flights in a airline
				Admin::addRevenue(airline->getFlights()[i]->getFee());
			}
		}
	}
	file.close();
	file.open("users.txt", ios::in);
	int i = 0, no;
	if (file) {
		ifstream file2("users.bin");
		boost::archive::text_iarchive ia{ file2 };
		User* user;
		file >> no;//getting users count from users.txt
		while (i < no) {//loading users till their count taken from users.txt
			ia >> user;
			users.push_back(user);
			i++;
		}
		file2.close();
	}
	file.close();
	tm departureTime, arrivalTime;
	time_t tp = system_clock::to_time_t(system_clock::now());
	tm t = *localtime(&tp);//current time
	vector<Flight*>::iterator it;
	vector<Flight*>::iterator ib;
	for (int i = 0; i < airlines.size(); i++) {//loop through airlines 
		it = airlines[i]->flights.begin();
		ib = airlines[i]->flights.end();
		while (it != ib) {//iterate through flights in a airline
			departureTime = (*it)->getDepartureTime();
			arrivalTime = (*it)->getArrivalTime();
			//erase flight if flight's departure time is not in future
			if (!((departureTime.tm_year > t.tm_year) || (departureTime.tm_mon > t.tm_mon && departureTime.tm_year == t.tm_year) || (departureTime.tm_mday > t.tm_mday && departureTime.tm_mon == t.tm_mon && departureTime.tm_year == t.tm_year) || (departureTime.tm_hour > t.tm_hour &&departureTime.tm_mday==t.tm_mday&& departureTime.tm_mon == t.tm_mon && departureTime.tm_year == t.tm_year)||(departureTime.tm_hour==t.tm_hour&&departureTime.tm_min>departureTime.tm_min&&departureTime.tm_mday==t.tm_mday&& departureTime.tm_mon == t.tm_mon && departureTime.tm_year == t.tm_year) || (departureTime.tm_sec > t.tm_sec && departureTime.tm_min == t.tm_min && departureTime.tm_hour == t.tm_hour && departureTime.tm_mday == t.tm_mday && departureTime.tm_mon == t.tm_mon && departureTime.tm_year == t.tm_year))) {
				airlines[i]->flights.erase(it);
				it = airlines[i]->flights.begin();
				ib = airlines[i]->flights.end();
				continue;
			}
			it++;
		}
			
		
	}
}
void output() {
	string name;
	int i = 0;
	ofstream file("airlines.txt", ios::out);
	ofstream airline;
	while (i < airlines.size()) {//serializing airline objects to respective files
		name = airlines[i]->getName();
		airline.open(name + ".bin", ios::out);
		boost::archive::text_oarchive oa{ airline };
		oa << airlines[i];
		file << name << endl;//writing airline file names in airlines.txt
		airline.close();
		i++;
	}
	file.close();
	file.open("users.txt");
	file << users.size() << endl;//outputting users no to users.txt
	file.close();
	ofstream file2("users.bin");
	boost::archive::text_oarchive oa{ file2 };
	User* user;
	int j = users.size();
	i = 0;
	while (i < j) {//serializing all users to users.bin
		oa << users[i];
		i++;
	}
	file.close();
}