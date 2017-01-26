#ifndef AREACODES_H
#define AREACODES_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct AreaCodes
{
	AreaCodes();
	string getCity(const string &);
	string getState(const string &);
	void getCityState(const string&, string &, string &);
	string *lookUpByCity(const string &, int &);
	int sizeAllocator(const string&);//get the number of matches
	string *findMultCity(const string &, int &);
	bool phoneNumberValidate(const string &, string &);
	string binarySearch(const string &, int &);
	string areacodes[316];
	string cities[316];
	string states[316];
	string sortedByCityAreaCodes[316];
	string sortedByCityCities[316];
	string sortedByCityStates[316];
	int size = 316;
	void sortByCity();
	int numMatches;
};
#endif
