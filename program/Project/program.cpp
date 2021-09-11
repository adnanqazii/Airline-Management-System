#include "Admin.h"
#include "Airline.h"
#include "Flight.h"
#include "Passenger.h"
#include "User.h"
#include "typedef.h"
#include "functions.h"
#include <iostream>
#include <sstream>
#include <map>
#include "Data.h"
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <chrono>
#include <ctime>
#include "functions.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace std;
using namespace chrono;

int main()
{
	load();
	//Admin* admin = Admin::createInstance("gew", "re", "ghre", 22, "1796463590394");//was called for first runtime to create admin
	User::login();
}