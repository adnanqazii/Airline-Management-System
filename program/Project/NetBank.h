#pragma once
#ifndef NETBANK_H
#define NETBANK_H
#include "Account.h"
#include <boost/serialization/export.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/string.hpp>
class NetBank :
	public Account
{
	string phoneNo;//phone no
	friend class boost::serialization::access;//boost requirement for serialization
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) { //boost requirement for serialization
		ar& boost::serialization::base_object<Account>(*this);//boost requirement for inherited class
		ar& phoneNo;//field
	}
public:
	//constructors
	NetBank(string ac);
	NetBank();
};
#endif

