#pragma once
#ifndef USER_H
#define USER_H
#include <iostream>
#include <vector>
#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/assume_abstract.hpp>
using namespace std;
class Flight;
class Airline;
class Passenger;
class Account;
class User
{
	string id;//id
	string pass;//password
	string name;//name
	int age;//age
	string CNIC;//CNIC
	
	static vector<string>usernames;//usernames of all users
	static User* currentUser;//currently logged in user
	
	friend class boost::serialization::access;//boost requirement for serialization
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {//boost requirement for serialization
		//fields
		ar& id;
		ar& pass;
		ar& name;
		ar& age;
		ar& CNIC;
	}

public:

	void static login();//login
	
	User(string id, string pass, string name, int age, string CNIC);//constructor
	int getAge();//age getter
	void setAge(int age);//age setter
	void setCNIC(string CNIC);//CNIC setter
	void setId(string id);//id setter
	User(const User& u);//copy constructor
	void setPass(string pass);//password setter

	void setName(string name);//name setter
	string getId();//id getter

	string getPass();//password getter

	string getName();//name getter
	string getCNIC();//CNIC getter

	int static validatePhone(string& phone);//validating phone input
	void  static userChoice();//menu for user
	void static makeReservation();//flight registration interface
	static User* addUser(string id, string pass, string name, int age, string CNIC);//register user
	User() {}//constructor
	int validateCNIC(string CNIC);//validate CNIC input
	Passenger* makeReservation(int seat, Flight* flight,string meal,Account* account);//flight registration
	virtual bool getAdmin();//virtual function to recognize admin
	friend class Passenger;
	int static validateAccount(string& ac);//validate credit/debit card no input
	void static changeSeat();//change seat
	void static reservationStatus(vector<Passenger*>& reservations);//reservations of user
	void static cancelReservation();//cancel reservation
};

#endif
