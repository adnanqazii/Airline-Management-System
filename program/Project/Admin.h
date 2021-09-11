#pragma once
#ifndef ADMIN_H
#define ADMIN_H
#include "User.h"
#include "Airline.h"
#include <iostream>
#include <vector>
#include <string>
#include <boost/serialization/export.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

class Admin :
	public User
{
	static double revenue; //system revenue
	static Admin* instance; //currently logged in admin
	
	friend class boost::serialization::access;//boost requirement for serialization

	
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) //boost requirement for serialization
	{
		ar& boost::serialization::base_object<User>(*this);//boost requirement for inherited class
	}

private:
	Admin(string id, string pass, string aname, int age, string CNIC); //constructor
public:
	static double getRevenue();//revenue getter
	static void addRevenue(double x);//revenue adder
	friend class User;
	friend class Data;
	static void adminChoice();//menu for admin
	static Admin* createInstance(string id, string pass, string name, int age, string CNIC);//Admin object creator
	void search();//interface for searching flights
	Admin();//constructor
	~Admin();//destructor
	static Airline* addAirline( );//add airline
	void searchByDeparturePlace(string place);//search by departure place
	static void addFlight();//add flight
	static void subRevenue(double x);//subtract revenue
	void searchByArrivalPlace(string place);//search by arrival place
	void searchByType(string type);//search by flight class
	void delayFlight();//delay flight
	void cancelFlight();//cancel flight
	bool getAdmin();//to recognize admin
};


#endif 


