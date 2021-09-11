#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/string.hpp>
using namespace std;
class Account 
{
	friend class boost::serialization::access; //boost requirement for serialization                         
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) { //boost requirement for serialization    
		
	}
};

#endif
