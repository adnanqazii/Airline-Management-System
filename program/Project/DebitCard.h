#pragma once
#ifndef DEBITCARD_H
#define DEBITCARD_H
#include "Account.h"
#include <boost/serialization/export.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/string.hpp>
class DebitCard :
	public Account
{
	string accNo;//debit card account no
	friend class boost::serialization::access;//boost requirement for serialization
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) { //boost requirement for serialization
		ar& boost::serialization::base_object<Account>(*this); //boost requirement for inherited class
		ar& accNo;//field


	}
public:
	//constructors
	DebitCard(string ac);
	DebitCard();
};
#endif
