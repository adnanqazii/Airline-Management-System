#include "Admin.h"
#include "typedef.h"
#include "User.h"
#include "Airline.h"
#include <iostream>
#include <vector>
#include "functions.h"
#include <windows.h>
#include <string>
#include <fstream>
#include <list>
#include "Data.h"
#include "Flight.h"
#include <chrono>
#include <ctime>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/string.hpp>
using namespace std;
using namespace chrono;
BOOST_CLASS_EXPORT_GUID(Admin, "Admin")//boost requirement for virtual function
	void Admin::searchByType(string type) {//search by flight class
		int i, j, k;
		string n;
		for (i = 0; i < (airlines).size(); i++) {//loop through airlines
			k = airlines[i]->flights.size();
			for (j = 0; j < k; j++) {//loop through flights in a airline 
				n = ((airlines)[i]->flights)[j]->getType();//getting class of flight
				if (n.find(type) != string::npos) {//print flight if characters match that of flight's class string
					cout<<airlines[i]->flights[j]->print();
				}
			}
		}
	}
	
	Admin::Admin(string id, string pass, string aname, int age, string CNIC) :User(id, pass, aname, age, CNIC)//constructor
	{
	}
	void Admin::search() {//search interface
		int choice;
		cout << "Searching:\ntype 1 for arrival place\n2 for departure place\n3 for class\n";
		cin >> choice;
		cin.ignore();
		string search;
		switch (choice) {
		case 1:
			cout << "type arrival place for search\n";
			getline(cin, search);// input for arrival place
			searchByArrivalPlace(search);//search
			break;
		case 2:
			cout << "type departure place for search\n";
			getline(cin, search);// input for departure place
			searchByDeparturePlace(search);//search
			break;
		case 3:
			cout << "type class for search\n";
			getline(cin, search);// input for flight class
			searchByType(search);//search
			break;
		default:
			cout << "wrong choice\n";
		}
	}
	void Admin::delayFlight() {//delay flight
		tm arrivalTime{}, departureTime{};
		int year, month, hour;
		int i, j, k,l=1;
		int no;
		Flight *f[1000];
		time_t tp;
		tm t;
		for (i = 0; i < airlines.size(); i++) { //loop through airlines
			k = airlines[i]->flights.size();
			for (j = 0; j < k; j++) { //loop through flights in a airline
				f[l] = airlines[i]->flights[j];
				cout << endl;
				cout << l << ": ";

				cout<<airlines[i]->flights[j]->print();//printing flight
				cout << endl;
				l++;
			}
		}
		if (l != 1) {//if there was any flight
			cout << "Enter your flight no\n";
			
				cin >> no;//getting flight no
				cin.ignore();
				while (true) {//input for arrival and departure time
					cout << "Time format: day month year hour minute second(all integers)\n";
					cout << "hour is 0-23\n";
					cout << "Arrival Time:\n";
					cin >> arrivalTime.tm_mday >> month >> year >> hour >> arrivalTime.tm_min >> arrivalTime.tm_sec;
					//validating time format
					if (!(hour >= 0 && hour <= 23) && (arrivalTime.tm_min >= 0 && arrivalTime.tm_min <= 59) && (arrivalTime.tm_sec >= 0 && arrivalTime.tm_sec <= 59)) {
						cout << "invalid time format\n";
						continue;
					}
					arrivalTime.tm_mon = month - 1;
					arrivalTime.tm_year = year - 1900;
					arrivalTime.tm_hour = hour;
					arrivalTime.tm_wday = dayofweek(arrivalTime.tm_mday, month, year);
					cout << "Departure Time:\n";
					cin >> departureTime.tm_mday >> month >> year >> hour >> departureTime.tm_min >> departureTime.tm_sec;
					//validating time format
					if (!(hour >= 0 && hour <= 23) && (departureTime.tm_min >= 0 && departureTime.tm_min <= 59) && (departureTime.tm_sec >= 0 && departureTime.tm_sec <= 59)) {
						cout << "invalid time format\n";
						continue;
					}
					departureTime.tm_mon = month - 1;
					departureTime.tm_year = year - 1900;
					departureTime.tm_hour = hour;
					departureTime.tm_wday = dayofweek(departureTime.tm_mday, month, year);
					cin.ignore();
					t = f[no]->getDepartureTime();
					 //new departure time should be later than present departure time
					 int z = 0;
					 if (((departureTime.tm_year > t.tm_year) || (departureTime.tm_mon > t.tm_mon && departureTime.tm_year == t.tm_year) || (departureTime.tm_mday > t.tm_mday && departureTime.tm_mon == t.tm_mon && departureTime.tm_year == t.tm_year) || (departureTime.tm_hour > t.tm_hour && departureTime.tm_mday == t.tm_mday && departureTime.tm_mon == t.tm_mon && departureTime.tm_year == t.tm_year) || (departureTime.tm_hour == t.tm_hour && departureTime.tm_min > departureTime.tm_min && departureTime.tm_mday == t.tm_mday && departureTime.tm_mon == t.tm_mon && departureTime.tm_year == t.tm_year) || (departureTime.tm_sec > t.tm_sec && departureTime.tm_min == t.tm_min && departureTime.tm_hour == t.tm_hour && departureTime.tm_mday == t.tm_mday && departureTime.tm_mon == t.tm_mon && departureTime.tm_year == t.tm_year))) {
						 //arrival time should be later than departure time
						 if (((arrivalTime.tm_year > departureTime.tm_year) || (arrivalTime.tm_mon > departureTime.tm_mon && arrivalTime.tm_year == departureTime.tm_year) || (arrivalTime.tm_mday > departureTime.tm_mday && arrivalTime.tm_mon == departureTime.tm_mon && arrivalTime.tm_year == departureTime.tm_year) || (arrivalTime.tm_hour > departureTime.tm_hour && arrivalTime.tm_mday == departureTime.tm_mday && arrivalTime.tm_mon == departureTime.tm_mon && arrivalTime.tm_year == departureTime.tm_year) || (arrivalTime.tm_hour == departureTime.tm_hour && arrivalTime.tm_min > departureTime.tm_min && arrivalTime.tm_mday == departureTime.tm_mday && arrivalTime.tm_mon == departureTime.tm_mon && arrivalTime.tm_year == departureTime.tm_year) || (arrivalTime.tm_sec > departureTime.tm_sec && arrivalTime.tm_min == departureTime.tm_min && arrivalTime.tm_hour == departureTime.tm_hour && arrivalTime.tm_mday == departureTime.tm_mday && arrivalTime.tm_mon == departureTime.tm_mon && arrivalTime.tm_year == departureTime.tm_year)))
						 { z = 1;
						 break;//conditions satified
					 }

				}
					if (z == 0) {//if input did not satify above conditions
						cout << "input was invalid\n";
					}
				}
				//setting times
				f[no]->setArrivalTime(arrivalTime);
				f[no]->setDepartureTime(departureTime);
				//serializing airline object
				ofstream file(f[no]->airline->getName() + ".bin");
				boost::archive::text_oarchive oa{ file };
				oa << f[no]->airline;
				file.close();
		}
		
	}
	void Admin::cancelFlight() {
		int i, j, k, l = 1;
		int no;
		Flight* g;
		Flight* f[1000];
		for (i = 0; i < airlines.size(); i++) {//loop through airlines
			k = airlines[i]->flights.size();
			for (j = 0; j < k; j++) {//loop through flights in a airline
				f[l] =airlines[i]->flights[j];
				cout << endl;
				cout << l << ": ";

				cout<<airlines[i]->flights[j]->print();//print flight info
				cout << endl;
				l++;
			}
		}
		if (l != 1) {//if there was any flight
			cout << "Enter your flight no\n";
			cin >> no;//input for flight no
			cin.ignore();
			Flight flight;
			string n;
			if (no >= 1 && no <= (l - 1)) {
				//opening airline file
				g = f[no];
				n = g->airline->getName();
				ofstream flight_f(n + ".bin");
				boost::archive::text_oarchive oa(flight_f);
				//iteraotrs
				vector<Flight*>::iterator it = f[no]->airline->flights.begin();
				vector<Flight*>::iterator ib = f[no]->airline->flights.end();
				while (it != ib) {
					if (*it == f[no]) {//delete flight if found in loop
						f[no]->airline->flights.erase(it);
						break;
					}
					it++;
				}
				//serializing airline object
				oa << f[no]->airline;
				flight_f.close();
				j = (f[no]->passengers).size();
				//subtracting revenue/paying users according to passengers in deleted flights
				for (int i = 0; i < j; i++) {
					
					revenue -= f[no]->fee;
				}
			}
			else {
				cout << "process terminated unexpectedly\n";
			}
		}
		
		
	}

	void Admin::searchByDeparturePlace(string place) {//search by departure place
		int i, j, k;
		string n;
		for (i = 0; i < airlines.size(); i++) {//loop through airlines
			k = airlines[i]->flights.size();
			for (j = 0; j < k; j++) {//loop through flights in a airline
				n = airlines[i]->flights[j]->getDeparture();
				if (n.find(place) != string::npos) {//if characters match flight's departure place then print flight info
					cout << airlines[i]->flights[j]->print();
				}
			}
		}
	}
	void Admin::searchByArrivalPlace(string place) {//search by arrival place
		int i, j, k;
		string n;
		for (i = 0; i < airlines.size(); i++) {//loop through airlines
			k = airlines[i]->flights.size();
			for (j = 0; j < k; j++) {//loop through flights in a airline
				n = airlines[i]->flights[j]->getArrival();
				if (n.find(place) != string::npos) {//print flight info if characters match flight's arrival place string
					cout << airlines[i]->flights[j]->print();
				}
			}
		}
	}
	double Admin::getRevenue() {//revenue getter
		return revenue;
	}
	void Admin::adminChoice() {//menu for admin
		int x = 0, choice;
		int z = 0;
		ifstream file;
		while (x != 5) {
			system("CLS");
			cout << "Admin menu\n";
			cout << "Enter your choice:\n";
			cout << "1: Search Flights\n";
			cout << "2: Cancel Flight\n";
			cout << "3: Delay Flight\n";
			cout << "4: Log of reservations\n";
			cout << "5: Log of flights\n";
			cout << "6: Display all flights\n";
			cout << "7: Add Airline\n";
			cout << "8: Add Flight\n";
			cout << "9: View System Revenue\n";
			cout << "10: Exit\n";
			cin >> choice;
			cin.ignore();

			switch (choice)
			{
			case 1:
				Admin::instance->search();//search flights
				break;
			case 2:
				Admin::instance->cancelFlight();//cancel flight
				output();//output to files
				break;
			case 3:
				Admin::instance->delayFlight();//delay flight
				output();//output to files
				break;

			case 4://print passenger registrations
				file.open("p_registration.txt");
				while (true) {
					string s;
					getline(file, s);
					if (file.eof()) {
						break;
					}
					cout << s<<endl;
				}
				file.close();
				break;
			case 5://print flight registrations
				file.open("f_registration.txt");
				while (true) {
					string s;
					getline(file, s);
					if (file.eof()) {
						break;
					}
					cout << s<<endl;
				}
				file.close();
				break;
			case 6://view flights
				system("CLS");
				z = airlines.size();
				for (int i = 0; i < z; i++) {
					airlines[i]->print();
					system("PAUSE");
					system("CLS");
				}
				break;
			case 7://add airline
				addAirline();
				output();//output to files
				break;
			case 8://add flight
				addFlight();
				output();//output to files
				break;
			case 9:
				cout << "System Revenue: Rs" << Admin::getRevenue() << endl;//revenue print
				break;
			case 10://exit
				x = 5;
				break;
			default:
				cout << "Incorrect choice\n";
				break;
			}

			system("PAUSE");
		}
	}
	void Admin::addRevenue(double x) {//add revenue
		revenue += x;
	}
	Admin* Admin::createInstance(string id, string pass, string name,int age,string CNIC)//create admin instance
	{
		if (!Admin::instance)//if there is no admin registered till now  then create admin
		{
			
			Admin::instance = new Admin(id, pass, name,age,CNIC);
			users.push_back(Admin::instance);//add to users vector
			output();//output to files
		}
		else {
			cout << "There is admin already\n";
		}
		return instance;
	}
	Admin::~Admin()//destructor
	{
		int len = airlines.size();
		for (int i=0; i < len; i++) {
			delete airlines[i];
		}
	}
	Admin::Admin() {//constructor

	}
	void Admin::subRevenue(double x) {//subtract revenue
		revenue -= x;
	}
	
	
	bool Admin::getAdmin() {//recognize admin
		return true;
	}
	Airline* Admin::addAirline( )//add airline
	{
		cout << "airline name:\n";
		string name;
		getline(cin, name);//getting airline name
		int flag = 0;
		for (int j = 0; j < static_cast<int>((airlines).size()); j++)
		{
			if (name == (airlines)[j]->getName())//if airline found then end loop
			{
				flag = 1;
				break;
			}
		}
		if (flag != 1)//if airline not found then add airline
		{
			Airline* airline = new Airline(name);
			(airlines).push_back(airline);//add to airlines vector
			return airline;
		}
		else
		{
			cout << "Airline present already\n";
			return 0;
		}
	}
	void  Admin::addFlight()//add flight
	{
		
		string arrival, departure, type, airline;
		tm arrivalTime{}, departureTime{};
		int no;
		double fee;
		int month, year, hour;
		string time;
		cout << "Airline:\n";
		getline(cin, airline);//get airline name
		int c;
		cout << "Choose:\n1: national\n2:international\n";

		string mode;
		int a;
		while (true) {//choosing national or international 
			cin >> c;
			cin.ignore();
			if (c == 1) {
				mode = "National";
			}
			else if (c == 2) {
				mode = "International";
			}
			else {//if wrong choice then continue loop
				continue;
			}
			break;
		}

		int x = 1;
		do {//getting arrival place
			cout << "Arrival Place:\n";
			getline(cin, arrival);
			if (arrival.length() == 0) {//if input is empty
				cout << "please dont leave empty\n";
			}
			else {
				x = 0;//end loop if input not empty
			}
		} while (x == 1);
		x = 1;
		do {//getting departure place
			cout << "Departure Place:\n";
			getline(cin, departure);
			if (arrival.length() == 0) {//if input is empty
				cout << "please dont leave empty\n";
			}
			else {
				x = 0;//end loop if input not empty
			}
		} while (x == 1);
		x = 1;
		do {//getting max passengers no
			cout << "Maximum passengers:\n";
			cin >> no;
			cin.ignore();
			if (no <= 0) {//if negative or zero then it is invalid
				cout << "please give valid value\n";
			}
			else {
				x = 0;//end loop if input not wrong
			}
		} while (x == 1);
		time_t tp;
		tm t;
		//getting arrival and departure times
		int z = 0;
		
			while (true) {//input for arrival and departure time
				cout << "Time format: day month year hour minute second(all integers)\n";
				cout << "hour is 0-23\n";
				cout << "Arrival Time:\n";
				cin >> arrivalTime.tm_mday >> month >> year >> hour >> arrivalTime.tm_min >> arrivalTime.tm_sec;
				//validating time format
				if (!(hour >= 0 && hour <= 23)&&(arrivalTime.tm_min>=0&&arrivalTime.tm_min<=59)&&(arrivalTime.tm_sec >= 0 && arrivalTime.tm_sec <= 59)) {
					cout << "invalid time format\n";
					continue;
				}
				arrivalTime.tm_mon = month - 1;
				arrivalTime.tm_year = year - 1900;
				arrivalTime.tm_hour = hour;
				arrivalTime.tm_wday = dayofweek(arrivalTime.tm_mday, month, year);
				cout << "Departure Time:\n";
				cin >> departureTime.tm_mday >> month >> year >> hour >> departureTime.tm_min >> departureTime.tm_sec;
				//validating time format
				if (!(hour >= 0 && hour <= 23) && (departureTime.tm_min >= 0 && departureTime.tm_min <= 59) && (departureTime.tm_sec >= 0 && departureTime.tm_sec <= 59)) {
					cout << "invalid time format\n";
					continue;
				}
				departureTime.tm_mon = month - 1;
				departureTime.tm_year = year - 1900;
				departureTime.tm_hour = hour;
				departureTime.tm_wday = dayofweek(departureTime.tm_mday, month, year);
				tp = system_clock::to_time_t(system_clock::now());
				t = *localtime(&tp);//current time
				//departure time should be later than present time

				if (((departureTime.tm_year > t.tm_year) || (departureTime.tm_mon > t.tm_mon && departureTime.tm_year == t.tm_year) || (departureTime.tm_mday > t.tm_mday && departureTime.tm_mon == t.tm_mon && departureTime.tm_year == t.tm_year) || (departureTime.tm_hour > t.tm_hour && departureTime.tm_mday == t.tm_mday && departureTime.tm_mon == t.tm_mon && departureTime.tm_year == t.tm_year) || (departureTime.tm_hour == t.tm_hour && departureTime.tm_min > departureTime.tm_min && departureTime.tm_mday == t.tm_mday && departureTime.tm_mon == t.tm_mon && departureTime.tm_year == t.tm_year) || (departureTime.tm_sec > t.tm_sec && departureTime.tm_min == t.tm_min && departureTime.tm_hour == t.tm_hour && departureTime.tm_mday == t.tm_mday && departureTime.tm_mon == t.tm_mon && departureTime.tm_year == t.tm_year))) {
					//arrival time should be later than departure time
					if (((arrivalTime.tm_year > departureTime.tm_year) || (arrivalTime.tm_mon > departureTime.tm_mon && arrivalTime.tm_year == departureTime.tm_year) || (arrivalTime.tm_mday > departureTime.tm_mday && arrivalTime.tm_mon == departureTime.tm_mon && arrivalTime.tm_year == departureTime.tm_year) || (arrivalTime.tm_hour > departureTime.tm_hour && arrivalTime.tm_mday == departureTime.tm_mday && arrivalTime.tm_mon == departureTime.tm_mon && arrivalTime.tm_year == departureTime.tm_year) || (arrivalTime.tm_hour == departureTime.tm_hour && arrivalTime.tm_min > departureTime.tm_min && arrivalTime.tm_mday == departureTime.tm_mday && arrivalTime.tm_mon == departureTime.tm_mon && arrivalTime.tm_year == departureTime.tm_year) || (arrivalTime.tm_sec > departureTime.tm_sec && arrivalTime.tm_min == departureTime.tm_min && arrivalTime.tm_hour == departureTime.tm_hour && arrivalTime.tm_mday == departureTime.tm_mday && arrivalTime.tm_mon == departureTime.tm_mon && arrivalTime.tm_year == departureTime.tm_year)))
					{
						z = 1;
						break;//conditions satified
					}

				}
				if (z == 0) {//if input did not satify above conditions
					cout << "input was invalid\n";
				}
			}
			cin.ignore();
			cout << "Flight class:\n";
			getline(cin, type);//getting flight class
			x = 1;
			do {//getting fee which should not be negative or zero
				cout << "fee:\n";
				cin >> fee;
				cin.ignore();
				if (fee <= 0) {
					cout << "please enter valid value\n";
				}
				else {
					x = 0;
				}
			} while (x == 1);
			int i;
			for ( i = 0; i < static_cast<int>((airlines).size()); i++)//finding airline and then adding flight in airline
			{
				if ((airlines)[i]->getName() == airline)
				{
					Flight* flight = (airlines)[i]->addFlight(arrival, departure, arrivalTime, departureTime, no, type, fee, mode);
					ofstream file("f_registration.txt", ios::app);
					//adding flight in flight registration log with current time
					file << flight->print();
					time_t t = system_clock::to_time_t(system_clock::now());//current time
					file << ctime(&t) << endl;
					file.close();
				}
			}
			if (i == 0) {//if no airline found
				cout << "no airline found as typed\n";
			}
			

		
		
		
	}

Admin* Admin::instance = 0;
double Admin::revenue = 0;
