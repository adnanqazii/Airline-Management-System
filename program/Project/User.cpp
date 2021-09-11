#include "User.h"
#include "Passenger.h"
#include <iostream>
#include <string>
#include "Airline.h"
#include "Data.h"
#include <fstream>
#include <chrono>
#include <ctime>
#include "Admin.h"
#include "NetBank.h"
#include "DebitCard.h"
#include "CreditCard.h"
#include "functions.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
using namespace std;
using namespace chrono;
User* User::currentUser = 0;
class Flight;
class Airline;
//constructor
	User::User(string id, string pass, string name, int age,string CNIC) :id(id), pass(pass), name(name)
	{
		//set fields
		setAge(age);
		setCNIC(CNIC);
		setId(id);
		setPass(pass);
		setName(name);
		int i, e;
		//add user to usernames vectors
		
		User::usernames.push_back(id);
	}
	//copy constructor
	User::User(const User& u) {
		id = u.id;
		pass = u.pass;
		name = u.name;
		age = u.age;
		CNIC = u.CNIC;
	}
	//set CNIC
	void User::setCNIC(string CNIC) {
		int flag = validateCNIC(CNIC);//validate CNIC
		while (flag == 1) {//loop if CNIC does not have 13 digits
			cout << "CNIC should have 13 digits\n.type CNIC again\n";
			getline(cin,CNIC);//get CNIC input
			
			flag = validateCNIC(CNIC);//check CNIC input again
		}
		
		this->CNIC = CNIC;//set CNIC
	}
	void User::setId(string id)//set id
	{
		//id length should be positive
		if (id.length() > 0)
		{
			this->id = id;//set id
		}
		else
		{
			exit(0);
		}
	}
	//set password of positive length
	void User::setPass(string pass)
	{
		if (pass.length() > 0)
		{
			this->pass = pass;
		}
		else
		{
			exit(0);
		}
	}
	//set name of positive length
	void User::setName(string name)
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
	//id getter
	string User::getId()
	{
		return id;
	}
	//password getter
	string User::getPass()
	{
		return pass;
	}
	//name getter
	string User::getName()
	{
		return name;
	}
	//CNIC getter
	string User::getCNIC() {
		
		return CNIC;
		
	}
//validate CNIC for 13 length
	int User::validateCNIC(string CNIC) {
		if (CNIC.length() != 13) {
			return 1;
		}
		else {
			return 0;
		}
	}
	//user menu
	void  User::userChoice() {
		int x = 0, choice;
		while (x != 5) {
			system("CLS");
			int l = airlines.size();
			int k;
			p_list::iterator pt;
			p_list::iterator pe;
			time_t rawtime;
			struct tm* timeinfo;
			time(&rawtime);
			timeinfo = localtime(&rawtime);//current time
			Flight* f;
			vector<Passenger*> reservations;
			for (int i = 0; i < l; i++) {//loop through airlines 
				k = airlines[i]->flights.size();
				for (int j = 0; j < k; j++) {//loop through flights in a airline
					pt = airlines[i]->flights[j]->passengers.begin();
					while (pt != airlines[i]->flights[j]->passengers.end()) {//loop through passengers in a flight
						if (pt->second->getCNIC() == User::currentUser->getCNIC()) {//if user CNIC found
							f = airlines[i]->flights[j];//flight in loop
							reservations.push_back(pt->second);//add reservation to vector
							//if there are 5 or less minutes in flight then notify user
							if (timeinfo->tm_year == f->getDepartureTime().tm_year && timeinfo->tm_mon == f->getDepartureTime().tm_mon && timeinfo->tm_mday == f->getDepartureTime().tm_mday && timeinfo->tm_hour == f->getDepartureTime().tm_hour && (f->getDepartureTime().tm_min - timeinfo->tm_min) <= 5 && (f->getDepartureTime().tm_min - timeinfo->tm_min) >= 0) {
								cout << "There are " << f->getDepartureTime().tm_min - timeinfo->tm_min << " minutes in below flight\n";
								cout << pt->second->print();
								cout << "Seat: " << pt->second->getSeat() << endl;
								cout << "Meal: " << pt->second->getMeal() << endl;
								cout << "Reservation No: " << pt->second->getReservation() << endl;
								cout << endl;
							}
							break;

						}
						pt++;
					}
				}
			}
			cout << "Enter your choice:\n";
			cout << "1: Make Reservation\n";
			cout << "2: Cancel Reservation\n";
			cout << "3: See Reservation Status\n";
			cout << "4: Change seat\n";
			cout << "5: Exit\n";
			cin >> choice;//getting user choice
			cin.ignore();

			switch (choice)
			{
			case 1:
				makeReservation();//make reservation
				output();//output to files
				break;
			case 2:
				cancelReservation();//cancel reservation
				output();//output to files
				break;
			case 3:
				reservationStatus(reservations);//passing vector to print reservations of user
				break;

			case 4:
				changeSeat();//change seat
				output();//output to files
				break;
			case 5://exit
				x = 5;
				break;
			}
			system("PAUSE");
	}
	
	}
	//change seat
	void User::changeSeat() {
		int l = airlines.size();
		int k;
		int flag = 0;
		Flight* flight2;
		p_list::iterator pt;
		p_list::iterator pe;
		vector<Flight*> allFlights;
		int z = 1;
		for (int i = 0; i < l; i++) {//loop through airlines
			k = airlines[i]->flights.size();
			for (int j = 0; j < k; j++) {//loop through flights in a airline
				pt = airlines[i]->flights[j]->passengers.begin();
				pe = airlines[i]->flights[j]->passengers.end();
				while (pt != pe) {//loop through passengers in a flight
					if (pt->second->getCNIC() == User::currentUser->getCNIC()) {//if user CNIC found then print reservation
						flag++;
						if (flag == 1) {
							cout << "Your current reservations:\n";
						}
						allFlights.push_back(pt->second->flight);//add flight of reservation to vector
						cout << z << ":" << endl;
						cout << pt->second->print();//print reservation info
						cout << endl;
						z++;
						break;
					}
					pt++;
				}
			}
		}
		if (flag != 0)//if there was any flight
		{
			int no;
			Passenger* p;
			cout << "Enter reservation no\n";
			cin >> no;//getting reservation no
			int seat;
			cin.ignore();
			try {
				flight2 = allFlights[no - 1];//flight of reservation
				p_iterator i = flight2->passengers.begin();
				p_iterator ie = flight2->passengers.end();
				while (i != ie) {//loop through passengers in the reservation flight
					if (i->second->getCNIC() == User::currentUser->getCNIC()) {//if user CNIC found
						p = i->second;
						cout << "Your seat no is " << p->getSeat() << endl;
						cout << "Type your new seat no\n";
						cin >> seat;//getting new seat no
						cin.ignore();
						p->changeSeat(seat);//changing seat
						break;
					}
					i++;
				}
			}
			//catching exception
			catch (out_of_range& e) {
				cout << e.what() << endl;
			}
			catch (exception& e) {
				cout << e.what() << endl;
			}
			catch (...) {
				cout << "process terminated unexpectedly\n";
			}
		}
		else {//if no flight found of user
			cout << "no flight found of you\n";
		}
	}
	//cancel reservation
	void User::cancelReservation() {
		system("CLS");
		int l = airlines.size();
		int k;
		Flight* flight2;
		int flag = 0;
		p_list::iterator pt;
		p_list::iterator pe;
		vector<Flight*> allFlights;
		int z = 1;
		for (int i = 0; i < l; i++) {//loop through airlines
			k = airlines[i]->flights.size();
			for (int j = 0; j < k; j++) {//loop through flights in a airline
				pt = airlines[i]->flights[j]->passengers.begin();
				pe = airlines[i]->flights[j]->passengers.end();
				while (pt != pe) {//loop through passengers in a flight
					if (pt->second->getCNIC() == User::currentUser->getCNIC()) {//if user CNIC found then print reservation
						flag++;
						if (flag == 1) {
							cout << "Your current reservations:\n";
						}
						allFlights.push_back(pt->second->flight);//add flight of reservation to vector
						cout << z << ":" << endl;
						cout << pt->second->print();//print reservation
						cout << endl;
						z++;
						break;
					}
					pt++;
				}
			}
		}
		if (flag != 0)//if flight found of user then get reservation no
		{
			int no;
			cout << "Enter reservation no to cancel\n";
			cin >> no;//getting reservation no
			cin.ignore();
			try {
				flight2 = allFlights.at(no - 1);//flight of reservation
				p_iterator i = flight2->passengers.begin();
				p_iterator ie = flight2->passengers.end();
				while (i != ie) {//loop through  passengers in the reservation flight
					if (i->second->getCNIC() == User::currentUser->getCNIC()) {//if user CNIC found
						flight2->passengers.erase(i);//delete reservation
						break;
					}
					i++;
				}
				p_iterator_a ia = flight2->airline->passengers.find(User::currentUser->getCNIC());//find reservation in airline's passengers vector
				flight2->airline->passengers.erase(ia);//delete reservation 
				Admin::revenue -= flight2->getFee();//subtract revenue or pay user
			}
			//catch exception
			catch (out_of_range& e) {
				cout << e.what() << endl;
			}
			catch (exception& e) {
				cout << e.what() << endl;
			}
			catch (...) {
				cout << "process terminated unexpectedly\n";
			}
		}

	}
	//print all reservations of user
	void User::reservationStatus(vector<Passenger*>& reservations) {
		int j = reservations.size();

		if (j == 0) {
			cout << "You have no current flight\n";
		}
		else {
			system("CLS");
			cout << "Your current reservations:\n";
			for (int i = 0; i < j; i++) {
				cout << reservations[i]->print() << endl;
			}
		}
	}
	//login
	void User::login() {
		int c;
		int flag = 3;
		cout << "press 1 to login\n";
		cout << "press other key to create account\n";
		cin >> c;//getting  choice
		cin.ignore();
		int x = 0;
		int choice = 0;

		string id, pass;
		if (c == 1) {//login
			cout << "id\n";
			getline(cin, id);//getting id
			cout << "pass\n";
			getline(cin, pass);//getting password
			for (int i = 0; i < users.size(); i++) {//loop through users
				if ((users[i]->getId() == id) && (users[i]->getPass() == pass)) {//if id and pass are correct
					User::currentUser = users[i];//set variable to that user
					flag = 1;//set flag
					if (User::currentUser->getAdmin()) {//if current user is admin
						Admin::instance = dynamic_cast<Admin*>(User::currentUser);//set variable after dynamic cast
						Admin::adminChoice();//admin menu
					}
					else {//if current user is not admin
						User::userChoice();//user choice
					}
					break;
				}
			}
		}
		else//create account
		{
			string name, CNIC;
			int age;
			cout << "Username?\n";
			getline(cin, id);//getting username/id
			cout << "Password?\n";
			getline(cin, pass);//getting password
			cout << "Name?\n";
			getline(cin, name);//getting name
			cout << "Age?\n";
			cin >> age;//getting age
			cin.ignore();
			cout << "CNIC?\n";
			getline(cin, CNIC);//getting CNIC
			User::currentUser = addUser(id, pass, name, age, CNIC);//adding user
			flag = 1;
			User::userChoice();//user menu
		}
		if (flag == 3) {//if login id and password were invalid
			cout << "incorrect username or password\n";
		}
	}
	//add user
	User* User::addUser(string id, string pass, string name, int age, string CNIC) {
		int e = users.size();
		int flag = 0;
		for (int i = 0; i < e; i++) {//loop through users
			if (id == users[i]->getId()) {//if user id alreay found
				cout << "Username " << id << " already exists\nplease login with that username\n";
				flag = 1;
				break;
			}
		}
		if (flag == 0) {//if user id not found
			User* user = new User(id, pass, name, age, CNIC);
			users.push_back(user);//add to users vector
			return user;
		}
		else {
			return 0;
		}
	}
	//interface to make reservation
	void User::makeReservation() {
		system("CLS");
		vector<Flight*> allFlights;
		int air = airlines.size();
		int flights;
		int flag;
		int flag2 = 0;
		int l = 1;
		Flight* flight;
		Flight* flight2 = 0;
		cout << "1:National\n2:International\n";
		int x;
		cin >> x;//getting choice
		cin.ignore();
		switch (x) {
		case 1://for National flights
			for (int i = 0; i < air; i++) {//loop through airlines
				flights = airlines[i]->flights.size();
				flag = 0;
				for (int j = 0; j < flights; j++) {//loop through flights in a airline
					//if flight is national and CNIC not found in airline then can make reservation
					if (!airlines[i]->flights[j]->searchCNIC(User::currentUser->getCNIC()) && airlines[i]->flights[j]->getMode() == "National") {

						flight = airlines[i]->flights[j];
						flag2++;
						if (flag2 == 1) {
							cout << "\nAvailable flights:\n";
						}
						cout << endl << l << ":\n";
						cout << flight->print() << endl;//print flight info

						l++;
						allFlights.push_back(flight);//add flight to vector
					}
				}
			}
			break;
		case 2://for International flights
			for (int i = 0; i < air; i++) {//loop through airlines
				flights = airlines[i]->flights.size();
				flag = 0;
				for (int j = 0; j < flights; j++) {//loop through flights in a airline
					//if user CNIC not found in airline and flight is international then can make reservation
					if (!airlines[i]->flights[j]->searchCNIC(User::currentUser->getCNIC()) && airlines[i]->flights[j]->getMode() == "International") {

						flight = airlines[i]->flights[j];
						flag2++;
						if (flag2 == 1) {
							cout << "\nAvailable flights:\n";
						}
						cout << endl << l << ":\n";
						cout << flight->print() << endl;//print flight info

						l++;
						allFlights.push_back(flight);//add flight to vector
					}
				}
			}
			break;
		default://wrong choice
			cout << "wrong choice\n";
			break;
		}

		if (flag2 != 0) {//if flight was available
			int no;
			cout << "Enter flight no\n";
			cin >> no;//getting flight no
			cin.ignore();
			try {
				flight2 = allFlights.at(no - 1);
				cout << "enter seat no\n";
				cin >> no;//getting seat no
				cin.ignore();
				cout << "Meal:\n";
				cout << "1: vegeterian\n2:non vegeterian\n3:no meal\n";
				int meal;
				string meale;
				cin >> meal;//getting meal choice
				cin.ignore();
				if (meal == 1) {
					meale = "vegeterian";
				}
				else if (meal == 2) {
					meale = "non vegeterian";
				}
				else if (meal == 3) {
					meale = "no meal";
				}
				int choice;
				cout << "Payment method:\n";
				cout << "1: Credit Card\n2: Debit Card\n3: Net banking\n";
				cin >> choice;//getting payment method choice
				cin.ignore();
				Account* account = 0;
				string ac;
				int f1 = 0;
				if (choice == 1) {//credit card
					do {
						if (f1 != 0) {
							cout << "card no should have no. of digits between 16-19\n";
						}
						cout << "credit card no:\n";
						getline(cin, ac);//getting card no
						f1++;
					} while (validateAccount(ac));//validating card no then continue loop accordingly

					account = new CreditCard(ac);
				}
				else if (choice == 2) {//debit card
					do {
						if (f1 != 0) {
							cout << "card no should have no. of digits between 16-19\n";
						}
						cout << "debit card no:\n";
						getline(cin, ac);//getting credit card no
						f1++;
					} while (validateAccount(ac));//validating card no then continue loop accordingly
					account = new DebitCard(ac);
				}
				else if (choice == 3) {//net banking
					do {
						if (f1 != 0) {
							cout << "phone no should have 10 digits\n";
						}
						cout << "phone no:\n";
						getline(cin, ac);//getting phone no
						f1++;
					} while (validatePhone(ac));//validating phone no then continue loop accordingly
					account = new NetBank(ac);
				}
				else {//wrong choice
					exit(0);
				}
				Passenger* p = User::currentUser->makeReservation(no, flight2, meale, account);//make reservation
				flight2->CNICs.push_back(User::currentUser->getCNIC());//add user cnic to Flight's CNICs vector
				system("CLS");
				cout << "Ticket:\n";
				cout << p->print();
			}
			//catch exception
			catch (out_of_range& e) {
				cout << e.what() << endl;
			}
			catch (exception& e) {
				cout << e.what() << endl;
			}
			catch (...) {
				cout << "process terminated unexpectedly\n";
			}
		}
		else {//if no flight available
			cout << "no flight found\n";
		}
	}
	//validate phone no which should have 10 digits
	int User::validatePhone(string& phone) {
		if (phone.length() != 10) {
			return 1;
		}
		else {
			return 0;
		}
	}
	//validate account no which should have length of 16-19
	int User::validateAccount(string& ac) {
		if ((ac.length() >= 16) && (ac.length() <= 19)) {
			return 0;
		}
		else {
			return 1;
		}
	}

	Passenger* User::makeReservation(int seat, Flight* flight,string meal,Account* account) {//make reservation
		User *u = this;
		int air = airlines.size();
		int flights;
		Passenger* p=new Passenger(u, seat, flight,meal,account);
		ofstream file("p_registration.txt",ios::app);
		file << p->print();//add reservation to reservations log
		time_t t = system_clock::to_time_t(system_clock::now());
		file << ctime(&t) << endl;//add current time to log
		file.close();
		return p;
	
	}
	//set age which should be positive
	void User::setAge(int age)
	{
		if (age > 0)
		{
			this->age = age;
		}
		else {
			exit(0);
		}
	}
	//age getter
	int User::getAge() {
		return age;
	}

	
	vector<string> User::usernames = {};
	//to recognize admin
	bool User::getAdmin() {
		return false;
	}
