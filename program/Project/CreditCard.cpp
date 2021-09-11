#include "CreditCard.h"
#include "Account.h"
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/base_object.hpp>

using namespace std;
//constructors
CreditCard::CreditCard(string ac) {
	accNo = ac;
}
CreditCard::CreditCard() {

}
