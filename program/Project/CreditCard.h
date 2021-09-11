#pragma once
#ifndef CREDITCARD_H
#define CREDITCARD_H
#include "Account.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/export.hpp>
class CreditCard :
	public Account
{
	string accNo;//credit card no
	friend class boost::serialization::access;//boost requirement for serialization
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) { //boost requirement for serialization
		ar& boost::serialization::base_object<Account>(*this);//boost requirement for inherited class
		ar& accNo;//field
	}
	
public:
	//constructors
	CreditCard();
	CreditCard(string ac);
};
#endif

