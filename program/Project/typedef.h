#pragma once
#ifndef TYPEDEF_H
#define TYPEDEF_H
#include <iostream>
#include <map>
#include "User.h"
using namespace std;
class Passenger;
//short aliases
typedef map<int, Passenger*> p_list;
typedef map<string, Passenger*> p_list_a;
typedef p_list::iterator p_iterator;
typedef p_list_a::iterator p_iterator_a;
typedef pair<int, Passenger*> addPair;
typedef pair<string, Passenger*> addPair_a;

#endif



