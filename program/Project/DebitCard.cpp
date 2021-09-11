#include "DebitCard.h"
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/base_object.hpp>

using namespace std;
//constructors
DebitCard::DebitCard(string ac) {
	accNo = ac;
}
DebitCard::DebitCard( ) {
	
}