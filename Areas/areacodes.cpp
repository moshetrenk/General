#include "areacodes.h"
#include <string>


bool AreaCodes::phoneNumberValidate(const string& phoneNum, string &info)
{
	//verify that the phone number has length 10 and only numbers
	bool checkone = 0, checktwo = 0;

	if (phoneNum.length() != 10)
	{
		checkone = 1;
		info = "You must enter exactly ten digits";
	}

	for (int i = 0; i < phoneNum.length(); i++)
	{
		if (phoneNum[i]<'0' || phoneNum[i]>'9')
			checktwo = 1;
	}

	if (checkone || checktwo)
		return false;
	else 
		return true;
}


string AreaCodes::getCity(const string& areaCode)
{
	//return the name of the city if it's in the "cities" array
	//if not, return "error" as the name of the city
	
	string city= "Error";
	
	for (int i = 0; i < size && city == "Error"; i++){
		if (areaCode == areacodes[i])
			city = cities[i];
	}

	return city;
}

string AreaCodes::getState(const string& areaCode)
{
	//return the name of the state if it's in the "states" array
	//if not, return "error" as the name of the state
	string state = "Error";

	for (int i = 0; i < size && state == "Error"; i++){
		if (areaCode == areacodes[i])
			state = states[i];
	}

	return state;
}

void AreaCodes::getCityState(const string& areaCode, string &city, string &state)
{
	//merges the getCity and getState functions, if preference is to return both
	
	bool found = false;

	for (int i = 0; i < size && !found; i++){
		if (areaCode == areacodes[i]){
			city = cities[i];
			state = states[i];
			found = true;
		}
	}
}

void AreaCodes::sortByCity()
{
	//this method is only called in the constructor
	for (int i = 0; i < size; i++)
	{
		sortedByCityAreaCodes[i] = areacodes[i];
		sortedByCityCities[i] = cities[i];
		sortedByCityStates[i] = states[i];

	}

	int index, smallest, location;
	string tempAreaCode, tempCity, tempState;

	for (index = 0; index < size - 1; index++)
	{
		smallest = index;

		for (location = index + 1; location < size; location++)
		{
			if (sortedByCityCities[location] < sortedByCityCities[smallest])
				smallest = location;
		}
		tempAreaCode = sortedByCityAreaCodes[smallest];
		sortedByCityAreaCodes[smallest] = sortedByCityAreaCodes[index];
		sortedByCityAreaCodes[index] = tempAreaCode;

		tempCity = sortedByCityCities[smallest];
		sortedByCityCities[smallest] = sortedByCityCities[index];
		sortedByCityCities[index] = tempCity;

		tempState = sortedByCityStates[smallest];
		sortedByCityStates[smallest] = sortedByCityStates[index];
		sortedByCityStates[index] = tempState;
	}
}

int AreaCodes::sizeAllocator(const string& city)
{
	numMatches = 0;
	for (int i = 0; i < size; i++)
	{
		if (sortedByCityCities[i] == city)
		{
			numMatches++;
		}
	}
	return numMatches;
}

string *AreaCodes::lookUpByCity(const string& city, int &numMatches)
{
	int x = 0;
	numMatches = sizeAllocator(city);
	string *tempArrayAreaCodes = new string[numMatches];
	string *tempArrayStates = new string[numMatches];
	for (int i = 0; i < size; i++)
	{
		if (sortedByCityCities[i] == city)
		{
			tempArrayAreaCodes[x] = sortedByCityAreaCodes[i];
			tempArrayStates[x] = sortedByCityStates[i];
			x++;
		}
	}
	x = 0;

//make this a for loop...
	if (tempArrayStates[0] == tempArrayStates[numMatches - 1])
	{
		return tempArrayAreaCodes;
	}
	else if (numMatches == 2)
	{
		tempArrayAreaCodes[x] = tempArrayAreaCodes[x] + " in " + tempArrayStates[x];
		tempArrayAreaCodes[x + 1] = tempArrayAreaCodes[x + 1] + " in " + tempArrayStates[x + 1];
	}
	else if (numMatches == 3)
	{
		tempArrayAreaCodes[x] = tempArrayAreaCodes[x] + " in " + tempArrayStates[x];
		tempArrayAreaCodes[x + 1] = tempArrayAreaCodes[x + 1] + " in " + tempArrayStates[x + 1];
		tempArrayAreaCodes[x + 2] = tempArrayAreaCodes[x + 2] + " in " + tempArrayStates[x + 2];
	}
	else
	{
		tempArrayAreaCodes[x] = tempArrayAreaCodes[x] + " in " + tempArrayStates[x];
		tempArrayAreaCodes[x + 1] = tempArrayAreaCodes[x + 1] + " in " + tempArrayStates[x + 1];
		tempArrayAreaCodes[x + 2] = tempArrayAreaCodes[x + 2] + " in " + tempArrayStates[x + 2];
		tempArrayAreaCodes[x + 3] = tempArrayAreaCodes[x + 3] + " in " + tempArrayStates[x + 3];
	}

	return tempArrayAreaCodes;
};

string *AreaCodes::findMultCity(const string& city, int &numMatches)
{
	
	int mid, first = 0, last = size - 1;
	bool found = 0;
	int x = 0;
	numMatches = sizeAllocator(city);

	if (numMatches)
	{
		string *tempArrayAreaCodes = new string[numMatches];
		string *tempArrayStates = new string[numMatches];

		string *ret;
		ret = new string[1];
		ret[0] = "not found";

		while (first <= last && !found)
		{
			mid = (first + last) / 2;

			if (sortedByCityCities[mid] == city)
			{
				found = true;
			}
			else if (sortedByCityCities[mid] > city)
			{
				last = mid - 1;
			}
			else if (sortedByCityCities[mid] < city)
			{
				first = mid + 1;
			}
		}

		binarySearch(city, numMatches);

		tempArrayAreaCodes = new string[numMatches];

		tempArrayAreaCodes[0] = sortedByCityAreaCodes[mid];
		tempArrayStates[0] = sortedByCityStates[mid];

//no location currently has more than 4 area codes
		if (sortedByCityCities[mid] == sortedByCityCities[mid - 4])
			mid -= 4;
		else if (sortedByCityCities[mid] == sortedByCityCities[mid - 3])
			mid -= 3;
		else if (sortedByCityCities[mid] == sortedByCityCities[mid - 2])
			mid -= 2;
		else if (sortedByCityCities[mid] == sortedByCityCities[mid - 1])
			mid -= 1;

		if (numMatches >= 2)
		{
			tempArrayAreaCodes[0] = sortedByCityAreaCodes[mid];
			tempArrayAreaCodes[1] = sortedByCityAreaCodes[mid + 1];
		}
		if (numMatches >= 3)
		{
			tempArrayAreaCodes[2] = sortedByCityAreaCodes[mid + 2];
		}
		if (numMatches >= 4)
		{
			tempArrayAreaCodes[3] = sortedByCityAreaCodes[mid + 3];
		}
		if (found)
			return tempArrayAreaCodes;
		else return ret;
	}

	return 0;
}

string AreaCodes::binarySearch(const string& city, int &numMatches)
{
	//more efficient version of the search
	int mid, first = 0, last = size - 1;
	bool found = 0;
	int x = 0;
	numMatches = sizeAllocator(city);

	string ret = "not found"; 
	string retCode;

	while (first <= last && !found)
	{
		mid = (first + last) / 2;

		if (sortedByCityCities[mid] == city)
		{
			found = true;
			retCode = sortedByCityAreaCodes[mid];
		}
		else if (sortedByCityCities[mid] > city)
		{
			last = mid - 1;
		}
		else if (sortedByCityCities[mid] < city)
		{
			first = mid + 1;
		}
	}

	if (found)
		return retCode;
	else return ret;
}AreaCodes::AreaCodes()
{
	//no worries, this constructor was (mostly) written by a program, avoiding using an input file

	areacodes[0] = "201";
	cities[0] = "Jersey City";
	states[0] = "NJ";
	areacodes[1] = "202";
	cities[1] = "Washington";
	states[1] = "DC";
	areacodes[2] = "203";
	cities[2] = "New Haven";
	states[2] = "CT";
	areacodes[3] = "204";
	cities[3] = "Melita";
	states[3] = "MB";
	areacodes[4] = "205";
	cities[4] = "Birmingham";
	states[4] = "AL";
	areacodes[5] = "206";
	cities[5] = "Seattle";
	states[5] = "WA";
	areacodes[6] = "207";
	cities[6] = "Portland";
	states[6] = "ME";
	areacodes[7] = "208";
	cities[7] = "Boise";
	states[7] = "ID";
	areacodes[8] = "209";
	cities[8] = "Modesto";
	states[8] = "CA";
	areacodes[9] = "210";
	cities[9] = "San Antonio";
	states[9] = "TX";
	areacodes[10] = "212";
	cities[10] = "New York";
	states[10] = "NY";
	areacodes[11] = "213";
	cities[11] = "Los Angeles";
	states[11] = "CA";
	areacodes[12] = "214";
	cities[12] = "Dallas";
	states[12] = "TX";
	areacodes[13] = "215";
	cities[13] = "Philadelphia";
	states[13] = "PA";
	areacodes[14] = "216";
	cities[14] = "Cleveland";
	states[14] = "OH";
	areacodes[15] = "217";
	cities[15] = "Champaign";
	states[15] = "IL";
	areacodes[16] = "218";
	cities[16] = "Duluth";
	states[16] = "MN";
	areacodes[17] = "219";
	cities[17] = "Gary";
	states[17] = "IN";
	areacodes[18] = "224";
	cities[18] = "Roselle";
	states[18] = "IL";
	areacodes[19] = "225";
	cities[19] = "Baton Rouge";
	states[19] = "LA";
	areacodes[20] = "228";
	cities[20] = "Gulfport";
	states[20] = "MS";
	areacodes[21] = "229";
	cities[21] = "Albany";
	states[21] = "GA";
	areacodes[22] = "231";
	cities[22] = "Muskegon";
	states[22] = "MI";
	areacodes[23] = "234";
	cities[23] = "North Lima";
	states[23] = "OH";
	areacodes[24] = "239";
	cities[24] = "Fort Myers";
	states[24] = "FL";
	areacodes[25] = "240";
	cities[25] = "Gaithersburg";
	states[25] = "MD";
	areacodes[26] = "248";
	cities[26] = "Royal Oak";
	states[26] = "MI";
	areacodes[27] = "250";
	cities[27] = "Hendrix Lake";
	states[27] = "BC";
	areacodes[28] = "251";
	cities[28] = "Mobile";
	states[28] = "AL";
	areacodes[29] = "252";
	cities[29] = "Greenville";
	states[29] = "NC";
	areacodes[30] = "253";
	cities[30] = "Tacoma";
	states[30] = "WA";
	areacodes[31] = "254";
	cities[31] = "Waco";
	states[31] = "TX";
	areacodes[32] = "256";
	cities[32] = "Huntsville";
	states[32] = "AL";
	areacodes[33] = "260";
	cities[33] = "Kendallville";
	states[33] = "IN";
	areacodes[34] = "262";
	cities[34] = "Racine";
	states[34] = "WI";
	areacodes[35] = "267";
	cities[35] = "Doylestown";
	states[35] = "PA";
	areacodes[36] = "269";
	cities[36] = "Bridgman";
	states[36] = "MI";
	areacodes[37] = "270";
	cities[37] = "Bowling Green";
	states[37] = "KY";
	areacodes[38] = "276";
	cities[38] = "Martinsville";
	states[38] = "VA";
	areacodes[39] = "281";
	cities[39] = "Houston";
	states[39] = "TX";
	areacodes[40] = "289";
	cities[40] = "Welland";
	states[40] = "ON";
	areacodes[41] = "301";
	cities[41] = "Rockville";
	states[41] = "MD";
	areacodes[42] = "302";
	cities[42] = "Wilmington";
	states[42] = "DE";
	areacodes[43] = "303";
	cities[43] = "Denver";
	states[43] = "CO";
	areacodes[44] = "304";
	cities[44] = "Charleston";
	states[44] = "WV";
	areacodes[45] = "305";
	cities[45] = "Miami";
	states[45] = "FL";
	areacodes[46] = "306";
	cities[46] = "Montmartre";
	states[46] = "SK";
	areacodes[47] = "307";
	cities[47] = "Cheyenne";
	states[47] = "WY";
	areacodes[48] = "308";
	cities[48] = "Grand Island";
	states[48] = "NE";
	areacodes[49] = "309";
	cities[49] = "Peoria";
	states[49] = "IL";
	areacodes[50] = "310";
	cities[50] = "Los Angeles";
	states[50] = "CA";
	areacodes[51] = "312";
	cities[51] = "Chicago";
	states[51] = "IL";
	areacodes[52] = "313";
	cities[52] = "Detroit";
	states[52] = "MI";
	areacodes[53] = "314";
	cities[53] = "Saint Louis";
	states[53] = "MO";
	areacodes[54] = "315";
	cities[54] = "Syracuse";
	states[54] = "NY";
	areacodes[55] = "316";
	cities[55] = "Wichita";
	states[55] = "KS";
	areacodes[56] = "317";
	cities[56] = "Indianapolis";
	states[56] = "IN";
	areacodes[57] = "318";
	cities[57] = "Shreveport";
	states[57] = "LA";
	areacodes[58] = "319";
	cities[58] = "Cedar Rapids";
	states[58] = "IA";
	areacodes[59] = "320";
	cities[59] = "Saint Cloud";
	states[59] = "MN";
	areacodes[60] = "321";
	cities[60] = "Melbourne";
	states[60] = "FL";
	areacodes[61] = "323";
	cities[61] = "Los Angeles";
	states[61] = "CA";
	areacodes[62] = "325";
	cities[62] = "Lueders";
	states[62] = "TX";
	areacodes[63] = "330";
	cities[63] = "Akron";
	states[63] = "OH";
	areacodes[64] = "331";
	cities[64] = "Oswego";
	states[64] = "IL";
	areacodes[65] = "334";
	cities[65] = "Montgomery";
	states[65] = "AL";
	areacodes[66] = "336";
	cities[66] = "Greensboro";
	states[66] = "NC";
	areacodes[67] = "337";
	cities[67] = "Lafayette";
	states[67] = "LA";
	areacodes[68] = "339";
	cities[68] = "Braintree";
	states[68] = "MA";
	areacodes[69] = "340";
	cities[69] = "Charlotte Amalie";
	states[69] = "VI";
	areacodes[70] = "347";
	cities[70] = "Ridgewood";
	states[70] = "NY";
	areacodes[71] = "351";
	cities[71] = "Danvers";
	states[71] = "MA";
	areacodes[72] = "352";
	cities[72] = "Gainesville";
	states[72] = "FL";
	areacodes[73] = "360";
	cities[73] = "Vancouver";
	states[73] = "WA";
	areacodes[74] = "361";
	cities[74] = "Corpus Christi";
	states[74] = "TX";
	areacodes[75] = "385";
	cities[75] = "Provo";
	states[75] = "UT";
	areacodes[76] = "386";
	cities[76] = "Daytona Beach";
	states[76] = "FL";
	areacodes[77] = "401";
	cities[77] = "Providence";
	states[77] = "RI";
	areacodes[78] = "402";
	cities[78] = "Omaha";
	states[78] = "NE";
	areacodes[79] = "403";
	cities[79] = "High River";
	states[79] = "AB";
	areacodes[80] = "404";
	cities[80] = "Atlanta";
	states[80] = "GA";
	areacodes[81] = "405";
	cities[81] = "Oklahoma City";
	states[81] = "OK";
	areacodes[82] = "406";
	cities[82] = "Billings";
	states[82] = "MT";
	areacodes[83] = "407";
	cities[83] = "Orlando";
	states[83] = "FL";
	areacodes[84] = "408";
	cities[84] = "San Jose";
	states[84] = "CA";
	areacodes[85] = "409";
	cities[85] = "Beaumont";
	states[85] = "TX";
	areacodes[86] = "410";
	cities[86] = "Baltimore";
	states[86] = "MD";
	areacodes[87] = "412";
	cities[87] = "Pittsburgh";
	states[87] = "PA";
	areacodes[88] = "413";
	cities[88] = "Springfield";
	states[88] = "MA";
	areacodes[89] = "414";
	cities[89] = "Milwaukee";
	states[89] = "WI";
	areacodes[90] = "415";
	cities[90] = "San Francisco";
	states[90] = "CA";
	areacodes[91] = "416";
	cities[91] = "Toronto";
	states[91] = "ON";
	areacodes[92] = "417";
	cities[92] = "Springfield";
	states[92] = "MO";
	areacodes[93] = "418";
	cities[93] = "Saint Thecle";
	states[93] = "QC";
	areacodes[94] = "419";
	cities[94] = "Toledo";
	states[94] = "OH";
	areacodes[95] = "423";
	cities[95] = "Chattanooga";
	states[95] = "TN";
	areacodes[96] = "424";
	cities[96] = "Lomita";
	states[96] = "CA";
	areacodes[97] = "425";
	cities[97] = "Kirkland";
	states[97] = "WA";
	areacodes[98] = "430";
	cities[98] = "Overton";
	states[98] = "TX";
	areacodes[99] = "432";
	cities[99] = "Comstock";
	states[99] = "TX";
	areacodes[100] = "434";
	cities[100] = "Lynchburg";
	states[100] = "VA";
	areacodes[101] = "435";
	cities[101] = "St George";
	states[101] = "UT";
	areacodes[102] = "440";
	cities[102] = "Cleveland";
	states[102] = "OH";
	areacodes[103] = "442";
	cities[103] = "Oceanside";
	states[103] = "CA";
	areacodes[104] = "443";
	cities[104] = "Pikesville";
	states[104] = "MD";
	areacodes[105] = "450";
	cities[105] = "Coteau Landing";
	states[105] = "QC";
	areacodes[106] = "458";
	cities[106] = "Oregon";
	states[106] = "OR";
	areacodes[107] = "469";
	cities[107] = "Plano";
	states[107] = "TX";
	areacodes[108] = "470";
	cities[108] = "Atlanta";
	states[108] = "GA";
	areacodes[109] = "475";
	cities[109] = "New Haven";
	states[109] = "CT";
	areacodes[110] = "478";
	cities[110] = "Macon";
	states[110] = "GA";
	areacodes[111] = "479";
	cities[111] = "Clarksville";
	states[111] = "AR";
	areacodes[112] = "480";
	cities[112] = "Mesa";
	states[112] = "AZ";
	areacodes[113] = "484";
	cities[113] = "Exton";
	states[113] = "PA";
	areacodes[114] = "501";
	cities[114] = "Little Rock";
	states[114] = "AR";
	areacodes[115] = "502";
	cities[115] = "Louisville";
	states[115] = "KY";
	areacodes[116] = "503";
	cities[116] = "Portland";
	states[116] = "OR";
	areacodes[117] = "504";
	cities[117] = "New Orleans";
	states[117] = "LA";
	areacodes[118] = "505";
	cities[118] = "Albuquerque";
	states[118] = "NM";
	areacodes[119] = "506";
	cities[119] = "Baie St Anne";
	states[119] = "NB";
	areacodes[120] = "507";
	cities[120] = "Rochester";
	states[120] = "MN";
	areacodes[121] = "508";
	cities[121] = "Worcester";
	states[121] = "MA";
	areacodes[122] = "509";
	cities[122] = "Spokane";
	states[122] = "WA";
	areacodes[123] = "510";
	cities[123] = "Oakland";
	states[123] = "CA";
	areacodes[124] = "512";
	cities[124] = "Austin";
	states[124] = "TX";
	areacodes[125] = "513";
	cities[125] = "Cincinnati";
	states[125] = "OH";
	areacodes[126] = "514";
	cities[126] = "Saint Genevieve";
	states[126] = "QC";
	areacodes[127] = "515";
	cities[127] = "Des Moines";
	states[127] = "IA";
	areacodes[128] = "516";
	cities[128] = "Lynbrook";
	states[128] = "NY";
	areacodes[129] = "517";
	cities[129] = "Lansing";
	states[129] = "MI";
	areacodes[130] = "518";
	cities[130] = "Albany";
	states[130] = "NY";
	areacodes[131] = "519";
	cities[131] = "Port Burwell";
	states[131] = "ON";
	areacodes[132] = "520";
	cities[132] = "Tucson";
	states[132] = "AZ";
	areacodes[133] = "530";
	cities[133] = "Chico";
	states[133] = "CA";
	areacodes[134] = "539";
	cities[134] = "Tulsa";
	states[134] = "OK";
	areacodes[135] = "540";
	cities[135] = "Roanoke";
	states[135] = "VA";
	areacodes[136] = "541";
	cities[136] = "Eugene";
	states[136] = "OR";
	areacodes[137] = "551";
	cities[137] = "Bayonne";
	states[137] = "NJ";
	areacodes[138] = "559";
	cities[138] = "Fresno";
	states[138] = "CA";
	areacodes[139] = "561";
	cities[139] = "West Palm Beach";
	states[139] = "FL";
	areacodes[140] = "562";
	cities[140] = "Long Beach";
	states[140] = "CA";
	areacodes[141] = "563";
	cities[141] = "Davenport";
	states[141] = "IA";
	areacodes[142] = "567";
	cities[142] = "Toledo";
	states[142] = "OH";
	areacodes[143] = "570";
	cities[143] = "Scranton";
	states[143] = "PA";
	areacodes[144] = "571";
	cities[144] = "Herndon";
	states[144] = "VA";
	areacodes[145] = "573";
	cities[145] = "Columbia";
	states[145] = "MO";
	areacodes[146] = "574";
	cities[146] = "Tippecanoe";
	states[146] = "IN";
	areacodes[147] = "575";
	cities[147] = "Las Cruces";
	states[147] = "NM";
	areacodes[148] = "580";
	cities[148] = "Lawton";
	states[148] = "OK";
	areacodes[149] = "585";
	cities[149] = "Rochester";
	states[149] = "NY";
	areacodes[150] = "586";
	cities[150] = "Roseville";
	states[150] = "MI";
	areacodes[151] = "601";
	cities[151] = "Jackson";
	states[151] = "MS";
	areacodes[152] = "602";
	cities[152] = "Phoenix";
	states[152] = "AZ";
	areacodes[153] = "603";
	cities[153] = "Manchester";
	states[153] = "NH";
	areacodes[154] = "604";
	cities[154] = "Vancouver";
	states[154] = "BC";
	areacodes[155] = "605";
	cities[155] = "Sioux Falls";
	states[155] = "SD";
	areacodes[156] = "606";
	cities[156] = "London";
	states[156] = "KY";
	areacodes[157] = "607";
	cities[157] = "Binghamton";
	states[157] = "NY";
	areacodes[158] = "608";
	cities[158] = "Madison";
	states[158] = "WI";
	areacodes[159] = "609";
	cities[159] = "Atlantic City";
	states[159] = "NJ";
	areacodes[160] = "610";
	cities[160] = "Reading";
	states[160] = "PA";
	areacodes[161] = "612";
	cities[161] = "Minneapolis";
	states[161] = "MN";
	areacodes[162] = "613";
	cities[162] = "Pembroke";
	states[162] = "ON";
	areacodes[163] = "614";
	cities[163] = "Columbus";
	states[163] = "OH";
	areacodes[164] = "615";
	cities[164] = "Nashville";
	states[164] = "TN";
	areacodes[165] = "616";
	cities[165] = "Grand Rapids";
	states[165] = "MI";
	areacodes[166] = "617";
	cities[166] = "Boston";
	states[166] = "MA";
	areacodes[167] = "618";
	cities[167] = "Belleville";
	states[167] = "IL";
	areacodes[168] = "619";
	cities[168] = "San Diego";
	states[168] = "CA";
	areacodes[169] = "620";
	cities[169] = "Hutchinson";
	states[169] = "KS";
	areacodes[170] = "623";
	cities[170] = "Phoenix";
	states[170] = "AZ";
	areacodes[171] = "626";
	cities[171] = "Alhambra";
	states[171] = "CA";
	areacodes[172] = "630";
	cities[172] = "Naperville";
	states[172] = "IL";
	areacodes[173] = "631";
	cities[173] = "Huntington";
	states[173] = "NY";
	areacodes[174] = "636";
	cities[174] = "Harvester";
	states[174] = "MO";
	areacodes[175] = "641";
	cities[175] = "Mason City";
	states[175] = "IA";
	areacodes[176] = "646";
	cities[176] = "New York";
	states[176] = "NY";
	areacodes[177] = "647";
	cities[177] = "Toronto";
	states[177] = "ON";
	areacodes[178] = "650";
	cities[178] = "San Mateo";
	states[178] = "CA";
	areacodes[179] = "651";
	cities[179] = "Saint Paul";
	states[179] = "MN";
	areacodes[180] = "657";
	cities[180] = "Huntington Beach";
	states[180] = "CA";
	areacodes[181] = "660";
	cities[181] = "Sedalia";
	states[181] = "MO";
	areacodes[182] = "661";
	cities[182] = "Bakersfield";
	states[182] = "CA";
	areacodes[183] = "662";
	cities[183] = "Tupelo";
	states[183] = "MS";
	areacodes[184] = "671";
	cities[184] = "Agana Heights";
	states[184] = "GU";
	areacodes[185] = "678";
	cities[185] = "Atlanta";
	states[185] = "GA";
	areacodes[186] = "681";
	cities[186] = "Davy";
	states[186] = "WV";
	areacodes[187] = "682";
	cities[187] = "Roanoke";
	states[187] = "TX";
	areacodes[188] = "684";
	cities[188] = "Pago Pago";
	states[188] = "AS";
	areacodes[189] = "701";
	cities[189] = "Fargo";
	states[189] = "ND";
	areacodes[190] = "702";
	cities[190] = "Las Vegas";
	states[190] = "NV";
	areacodes[191] = "703";
	cities[191] = "Alexandria";
	states[191] = "VA";
	areacodes[192] = "704";
	cities[192] = "Charlotte";
	states[192] = "NC";
	areacodes[193] = "705";
	cities[193] = "Mattice";
	states[193] = "ON";
	areacodes[194] = "706";
	cities[194] = "Augusta";
	states[194] = "GA";
	areacodes[195] = "707";
	cities[195] = "Santa Rosa";
	states[195] = "CA";
	areacodes[196] = "708";
	cities[196] = "Oak Park";
	states[196] = "IL";
	areacodes[197] = "709";
	cities[197] = "Norris Arm";
	states[197] = "NL";
	areacodes[198] = "712";
	cities[198] = "Sioux City";
	states[198] = "IA";
	areacodes[199] = "713";
	cities[199] = "Houston";
	states[199] = "TX";
	areacodes[200] = "714";
	cities[200] = "Santa Ana";
	states[200] = "CA";
	areacodes[201] = "715";
	cities[201] = "Eau Claire";
	states[201] = "WI";
	areacodes[202] = "716";
	cities[202] = "Buffalo";
	states[202] = "NY";
	areacodes[203] = "717";
	cities[203] = "Lancaster";
	states[203] = "PA";
	areacodes[204] = "718";
	cities[204] = "Brooklyn";
	states[204] = "NY";
	areacodes[205] = "719";
	cities[205] = "Colorado Springs";
	states[205] = "CO";
	areacodes[206] = "720";
	cities[206] = "Denver";
	states[206] = "CO";
	areacodes[207] = "724";
	cities[207] = "Greensburg";
	states[207] = "PA";
	areacodes[208] = "727";
	cities[208] = "Saint Petersburg";
	states[208] = "FL";
	areacodes[209] = "731";
	cities[209] = "Jackson";
	states[209] = "TN";
	areacodes[210] = "732";
	cities[210] = "Toms River";
	states[210] = "NJ";
	areacodes[211] = "734";
	cities[211] = "Ann Arbor";
	states[211] = "MI";
	areacodes[212] = "740";
	cities[212] = "Zanesville";
	states[212] = "OH";
	areacodes[213] = "747";
	cities[213] = "Los Angeles";
	states[213] = "CA";
	areacodes[214] = "754";
	cities[214] = "Fort Lauderdale";
	states[214] = "FL";
	areacodes[215] = "757";
	cities[215] = "Virginia Beach";
	states[215] = "VA";
	areacodes[216] = "760";
	cities[216] = "Vista";
	states[216] = "CA";
	areacodes[217] = "762";
	cities[217] = "Calhoun";
	states[217] = "GA";
	areacodes[218] = "763";
	cities[218] = "Minneapolis";
	states[218] = "MN";
	areacodes[219] = "765";
	cities[219] = "Muncie";
	states[219] = "IN";
	areacodes[220] = "769";
	cities[220] = "Collins";
	states[220] = "MS";
	areacodes[221] = "770";
	cities[221] = "Atlanta";
	states[221] = "GA";
	areacodes[222] = "772";
	cities[222] = "Port Saint Lucie";
	states[222] = "FL";
	areacodes[223] = "773";
	cities[223] = "Chicago";
	states[223] = "IL";
	areacodes[224] = "774";
	cities[224] = "Foxboro";
	states[224] = "MA";
	areacodes[225] = "775";
	cities[225] = "Reno";
	states[225] = "NV";
	areacodes[226] = "778";
	cities[226] = "West Vancouver";
	states[226] = "BC";
	areacodes[227] = "779";
	cities[227] = "Dekalb";
	states[227] = "IL";
	areacodes[228] = "780";
	cities[228] = "Devon";
	states[228] = "AB";
	areacodes[229] = "781";
	cities[229] = "Lynn";
	states[229] = "MA";
	areacodes[230] = "785";
	cities[230] = "Topeka";
	states[230] = "KS";
	areacodes[231] = "786";
	cities[231] = "Miami";
	states[231] = "FL";
	areacodes[232] = "787";
	cities[232] = "Trujillo Alto";
	states[232] = "PR";
	areacodes[233] = "801";
	cities[233] = "Ogden";
	states[233] = "UT";
	areacodes[234] = "802";
	cities[234] = "Burlington";
	states[234] = "VT";
	areacodes[235] = "803";
	cities[235] = "Columbia";
	states[235] = "SC";
	areacodes[236] = "804";
	cities[236] = "Richmond";
	states[236] = "VA";
	areacodes[237] = "805";
	cities[237] = "Santa Barbara";
	states[237] = "CA";
	areacodes[238] = "806";
	cities[238] = "Lubbock";
	states[238] = "TX";
	areacodes[239] = "807";
	cities[239] = "Dryden";
	states[239] = "ON";
	areacodes[240] = "808";
	cities[240] = "Honolulu";
	states[240] = "HI";
	areacodes[241] = "810";
	cities[241] = "Flint";
	states[241] = "MI";
	areacodes[242] = "812";
	cities[242] = "Evansville";
	states[242] = "IN";
	areacodes[243] = "813";
	cities[243] = "Tampa";
	states[243] = "FL";
	areacodes[244] = "814";
	cities[244] = "Erie";
	states[244] = "PA";
	areacodes[245] = "815";
	cities[245] = "Rockford";
	states[245] = "IL";
	areacodes[246] = "816";
	cities[246] = "Kansas City";
	states[246] = "MO";
	areacodes[247] = "817";
	cities[247] = "Fort Worth";
	states[247] = "TX";
	areacodes[248] = "818";
	cities[248] = "Van Nuys";
	states[248] = "CA";
	areacodes[249] = "819";
	cities[249] = "Ferme Neuve";
	states[249] = "QC";
	areacodes[250] = "828";
	cities[250] = "Asheville";
	states[250] = "NC";
	areacodes[251] = "830";
	cities[251] = "New Braunfels";
	states[251] = "TX";
	areacodes[252] = "831";
	cities[252] = "Santa Cruz";
	states[252] = "CA";
	areacodes[253] = "832";
	cities[253] = "Houston";
	states[253] = "TX";
	areacodes[254] = "843";
	cities[254] = "Charleston";
	states[254] = "SC";
	areacodes[255] = "845";
	cities[255] = "Spring Valley";
	states[255] = "NY";
	areacodes[256] = "847";
	cities[256] = "Arlington Hts";
	states[256] = "IL";
	areacodes[257] = "848";
	cities[257] = "Eatontown";
	states[257] = "NJ";
	areacodes[258] = "850";
	cities[258] = "Tallahassee";
	states[258] = "FL";
	areacodes[259] = "856";
	cities[259] = "Moorestown";
	states[259] = "NJ";
	areacodes[260] = "857";
	cities[260] = "Quincy";
	states[260] = "MA";
	areacodes[261] = "858";
	cities[261] = "San Diego";
	states[261] = "CA";
	areacodes[262] = "859";
	cities[262] = "Lexington";
	states[262] = "KY";
	areacodes[263] = "860";
	cities[263] = "Hartford";
	states[263] = "CT";
	areacodes[264] = "862";
	cities[264] = "Hopatcong";
	states[264] = "NJ";
	areacodes[265] = "863";
	cities[265] = "Lakeland";
	states[265] = "FL";
	areacodes[266] = "864";
	cities[266] = "Greenville";
	states[266] = "SC";
	areacodes[267] = "865";
	cities[267] = "Knoxville";
	states[267] = "TN";
	areacodes[268] = "867";
	cities[268] = "Pangnirtung";
	states[268] = "NU";
	areacodes[269] = "870";
	cities[269] = "Jonesboro";
	states[269] = "AR";
	areacodes[270] = "872";
	cities[270] = "Chicago";
	states[270] = "IL";
	areacodes[271] = "878";
	cities[271] = "Pittsburgh";
	states[271] = "PA";
	areacodes[272] = "901";
	cities[272] = "Memphis";
	states[272] = "TN";
	areacodes[273] = "902";
	cities[273] = "River Herbert";
	states[273] = "NS";
	areacodes[274] = "903";
	cities[274] = "Tyler";
	states[274] = "TX";
	areacodes[275] = "904";
	cities[275] = "Jacksonville";
	states[275] = "FL";
	areacodes[276] = "905";
	cities[276] = "Milton";
	states[276] = "ON";
	areacodes[277] = "906";
	cities[277] = "Marquette";
	states[277] = "MI";
	areacodes[278] = "907";
	cities[278] = "Anchorage";
	states[278] = "AK";
	areacodes[279] = "908";
	cities[279] = "Plainfield";
	states[279] = "NJ";
	areacodes[280] = "909";
	cities[280] = "San Bernardino";
	states[280] = "CA";
	areacodes[281] = "910";
	cities[281] = "Fayetteville";
	states[281] = "NC";
	areacodes[282] = "912";
	cities[282] = "Savannah";
	states[282] = "GA";
	areacodes[283] = "913";
	cities[283] = "Kansas City";
	states[283] = "KS";
	areacodes[284] = "914";
	cities[284] = "Yonkers";
	states[284] = "NY";
	areacodes[285] = "915";
	cities[285] = "El Paso";
	states[285] = "TX";
	areacodes[286] = "916";
	cities[286] = "Sacramento";
	states[286] = "CA";
	areacodes[287] = "917";
	cities[287] = "New York";
	states[287] = "NY";
	areacodes[288] = "918";
	cities[288] = "Tulsa";
	states[288] = "OK";
	areacodes[289] = "919";
	cities[289] = "Raleigh";
	states[289] = "NC";
	areacodes[290] = "920";
	cities[290] = "Green Bay";
	states[290] = "WI";
	areacodes[291] = "925";
	cities[291] = "Walnut Creek";
	states[291] = "CA";
	areacodes[292] = "928";
	cities[292] = "Yuma";
	states[292] = "AZ";
	areacodes[293] = "929";
	cities[293] = "Flushing";
	states[293] = "NY";
	areacodes[294] = "931";
	cities[294] = "Clarksville";
	states[294] = "TN";
	areacodes[295] = "936";
	cities[295] = "Conroe";
	states[295] = "TX";
	areacodes[296] = "937";
	cities[296] = "Dayton";
	states[296] = "OH";
	areacodes[297] = "938";
	cities[297] = "Red Bay";
	states[297] = "AL";
	areacodes[298] = "939";
	cities[298] = "Santurce";
	states[298] = "PR";
	areacodes[299] = "940";
	cities[299] = "Wichita Falls";
	states[299] = "TX";
	areacodes[300] = "941";
	cities[300] = "Sarasota";
	states[300] = "FL";
	areacodes[301] = "947";
	cities[301] = "Ortonville";
	states[301] = "MI";
	areacodes[302] = "949";
	cities[302] = "El Toro";
	states[302] = "CA";
	areacodes[303] = "951";
	cities[303] = "Homeland";
	states[303] = "CA";
	areacodes[304] = "952";
	cities[304] = "Minneapolis";
	states[304] = "MN";
	areacodes[305] = "954";
	cities[305] = "Fort Lauderdale";
	states[305] = "FL";
	areacodes[306] = "956";
	cities[306] = "Laredo";
	states[306] = "TX";
	areacodes[307] = "970";
	cities[307] = "Ft Collins";
	states[307] = "CO";
	areacodes[308] = "971";
	cities[308] = "Portland";
	states[308] = "OR";
	areacodes[309] = "972";
	cities[309] = "Dallas";
	states[309] = "TX";
	areacodes[310] = "973";
	cities[310] = "Newark";
	states[310] = "NJ";
	areacodes[311] = "978";
	cities[311] = "Lowell";
	states[311] = "MA";
	areacodes[312] = "979";
	cities[312] = "Bryan";
	states[312] = "TX";
	areacodes[313] = "980";
	cities[313] = "Locust";
	states[313] = "NC";
	areacodes[314] = "985";
	cities[314] = "Houma";
	states[314] = "LA";
	areacodes[315] = "989";
	cities[315] = "Saginaw";
	states[315] = "MI";
}
