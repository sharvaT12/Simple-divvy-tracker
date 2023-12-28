// main.cpp//

//This program inputs and handles two files of data of stations and trip. 
//
// Author: Sharva Thakur
// Project 4
// 
//



//All the variables 
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;


// Stations 
//This defines all the variables of station files: id, capacity, latitude, longitude, name
//The station id and name is stored as string so that it can have both numbers and letters
//the capacity is stored in integers because it is always going to a number and can never have decimals 
// latitude and longitude are stored as doubles because their values and be in decimals places but can never have letters.
//
struct Stations{
	string id;
	int capacity;
	double latitude;
	double longitude;
	string name;
};



//Trips
//This defines all the variables of trip file: tripID, bikeID, startID, endID, time, startTime.
//The tripID, bikeID, startID and endID are stored as strings because id can have both letters or digits. 
//startTime is stored as string because it has a semicolon to separate the hours and minutes eg. 23:00, 00:09, 10:41.
//time is stored in int because the trip duration is always in seconds which is integer and can never have a letter. 
//
struct Trips{
	string tripID;
	string bikeID;
	string startID;
	string endID; 
	int time; 
	string startTime; 
};

//
//This function takes input from the stations file and store it in Stations
//It returns a station value with all the data in the stations file with S being the number of stations
//If the file is not good or cannot be opened then the function returns nullptr which ends the whole program  
//
Stations* inputstation(string filename,int& S){
	ifstream infile;
    infile.open(filename);
	
	if (!infile.good())  // failed to open:
   {
      S = 0;
      return nullptr;
   }

	
	infile >> S; 
	
	Stations* A = new Stations[S]; 
	
	for(int i = 0; i < S ; i++){
		infile >> A[i].id;
		infile >> A[i].capacity;
		infile >> A[i].latitude;
		infile >> A[i].longitude;
		getline(infile, A[i].name);
		A[i].name.erase(0,1); 
		
	}
	infile.close();
	
	return A; 
}


//
//This function is sililar to inputstation function
//This function takes input from the trips file and store it in Trips
//It returns a station value with all the data in the stations file with T being the number of bikes
//If the file is not good or cannot be opened then the function returns nullptr which ends the whole program  
//

Trips* inputtrips(string filename,int& T){
	
	
	
	ifstream infile;
    infile.open(filename);
	
	if (!infile.good())  // failed to open:
   {
      T = 0;
      return nullptr;
   }

	
	infile >> T; 
	
	
	
	Trips* A = new Trips[T]; 
	
	for(int i = 0; i < T ; i++){
		infile >> A[i].tripID;
		infile >> A[i].bikeID;
		infile >> A[i].startID;
		infile >> A[i].endID;
		infile >> A[i].time;
		infile >> A[i].startTime;
		
	}
	infile.close();
	
	return A; 
}


//
//This is a void function which outputs the stats of the stations 
//It outputs number of stations, number of trips and the total bike capacity of all the stations
//


void stats(Stations station[], int S , int T){
	cout << "  stations: " << S << endl;
	cout << "  trips: " << T << endl;
	
	int total = 0;
	for (int a =0; a < S; a++){
		total = total + station[a].capacity; 
		
	}
	cout << "  total bike capacity: " << total <<endl; 
}



//
//This is a void function which prints number of bikes according to their duration
//This means that it finds the number of bike which took a ride of the particular duration and the prints 
//for example if a bikes takes less 30 minutes trip then it adds it to the tally of number of bikes
//Then prints the number of bikes who took less then 30 mins. Same goes for every duration i.e less than 30mins, 30-60mins, 1-2hr, 2-5hr, more than 5 hrs 
//
void duration(Trips trip[],int T){
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0; 
	int e = 0;
	
	for(int i = 0; i < T; i++){
		
		if(trip[i].time <= 1800){
			a ++;
		}
		else if (trip[i].time > 1800 && trip[i].time <= 3600){
			b++;
		}
		else if(trip[i].time > 3600 && trip[i].time <= 3600*2){
			c++;
		}
		else if(trip[i].time > 3600*2 && trip[i].time <= 3600*5){
			d++;
		}
		else if(trip[i].time > 3600*5){
			e++ ;
		}
		
	}
	
	cout << "  trips <= 30 mins: " << a << endl;
	cout << "  trips 30..60 mins: " << b << endl;
	cout << "  trips 1-2 hrs: " << c << endl;
	cout << "  trips 2-5 hrs: " << d <<endl; 
	cout << "  trips > 5 hrs: " << e << endl; 
	
}


//
// This function loops through the dynamically allocated array trip for the startTime of the biketrip
// This then breaks the startTime which is stored as string and takes the hours from the startTime
// It then converts the string into int and compares it with a valuefrom the input
// If both the values are same it adds 1 to a integer a and then returns a  
//
int numstarttime(Trips trip[], int T, int A){
	int a = 0;
	
	for(int i =0; i< T; i++){
		string z = trip[i].startTime;
		
		int b = stoi(z.substr(0,2));
		if (b == A){
			a ++; 
		}
	}
	return a;
}


//
//This function prints every hour and also number of trips in the hour
//In this function there is a for loop in which numstarttime is called which returns an integer. 
//The integer is the number of trips in that hour which is then printed
//
void starting(Trips trip[], int T){
	
	for(int i = 0; i < 24; i++){
		int a = numstarttime(trip, T, i); 
		
		cout <<"  "<< i << ": " << a <<endl;
	}
	
}




//
// distBetween2Points
//
// Returns the distance in miles between 2 points (lat1, long1) and 
// (lat2, long2).  Latitudes are positive above the equator and 
// negative below; longitudes are positive heading east of Greenwich 
// and negative heading west.  Example: Chicago is (41.88, -87.63).
//
// NOTE: you may get slightly different results depending on which 
// (lat, long) pair is passed as the first parameter.
// 
// Originally written by: Prof. Hummel, U. of Illinois, Chicago, Spring 2021
// Reference: http://www8.nau.edu/cvm/latlon_formula.html
//
double distBetween2Points(double lat1, double long1, double lat2, double long2)
{
  double PI = 3.14159265;
  double earth_rad = 3963.1;  // statue miles:

  double lat1_rad = lat1 * PI / 180.0;
  double long1_rad = long1 * PI / 180.0;
  double lat2_rad = lat2 * PI / 180.0;
  double long2_rad = long2 * PI / 180.0;

  double dist = earth_rad * acos(
    (cos(lat1_rad) * cos(long1_rad) * cos(lat2_rad) * cos(long2_rad))
    +
    (cos(lat1_rad) * sin(long1_rad) * cos(lat2_rad) * sin(long2_rad))
    +
    (sin(lat1_rad) * sin(lat2_rad))
  );

  return dist;
}

//
//This is a struct which stores distance, name and id.
//It stores distance in double as there can be no letter in distance
//Name and id in string because there can be an letter and integers in id as well as name 
//
struct A{
	double distance; 
	string name; 
	string id; 
	
};

//
//This function sorts all the values in stuct A by the distance
//This is a selection sort function 
//It returns dis which is a dynamically allocated array of A
//
A* sortbydistance(A dis[], int s){
	
	for (int i = 0; i < s-1; i++)
   {
      int minIndex = i;
      
      for (int j = i+1; j < s; j++)
      {
         if (dis[j].distance < dis[minIndex].distance)
         {
            minIndex = j;
         }
      }
      
      A temp = dis[i];
      dis[i] = dis[minIndex];
      dis[minIndex] = temp;
   }
	return dis; 
	
}


//
//This is a void function which finds the stations near the latitude and longitude which is given in the input within the radius given
//If there are no Stations it returns none found
//else this prints the station id the station name and also the distance between the coordinates and the station
//All the outputs are sorted by distance in accending order.
//
//
void nearme(Stations station[], int S){
	double lat1, long1 = 0; 
	double D = 0;
	
	cin >> lat1;
	cin >> long1;
	cin >> D;
	
	cout << "  The following stations are within " << D << " miles of (" << lat1 << ", " << long1 << "):" << endl; 
	int s = 0; 
	A* dis = new A[S]; // decalring a new dynamically allocated array
	for (int i = 0; i < S ; i++){
		double distance = 0; 
		
		distance = distBetween2Points(lat1, long1, station[i].latitude, station[i].longitude); // calling distBetween2Points function
		
		if (distance <= D){
			
			dis[s].distance = distance;
			dis[s].name = station[i].name;
			dis[s].id = station[i].id;
			
			s++ ;
		}
		
		
	}
	if (s == 0){
		cout << "  none found" << endl; //if no station is found in the radius 
	}
	else{      
		A* sorted; 
		
		sorted = sortbydistance(dis, s);// calling sortbydistance function
		
		for (int i =0; i< s ;i++){
			
			cout << "  station " << sorted[i].id << " (" << sorted[i].name << "): " << sorted[i].distance << " miles" << endl; 
			
		}
		
	}
	
	delete[] dis; 
	
}

//
//This function sorts all the values in stuct Stations by the Name
//This is a selection sort function 
//It returns dis which is a dynamically allocated array of Stations
//
Stations* sortbyname(Stations station[], int S){
	for (int i = 0; i < S-1; i++)
   {
      int minIndex = i;
      
      for (int j = i+1; j < S; j++)
      {
         if (station[j].name < station[minIndex].name)
         {
            minIndex = j;
         }
      }
      
      Stations temp = station[i];
      station[i] = station[minIndex];
      station[minIndex] = temp;
   }
	return station; 
	
}

//
//This function prints all the stations in the alphabetical order
//Also it prints the number of trips per station
//
void allstations(Stations station[], int S, Trips trip[], int T){
	
	Stations* sorted; 
	
	sorted = sortbyname(station, S);// calling sort by name function 
	
	
	for(int i = 0; i < S; i++){
		int total= 0; 
		
		for(int j =0; j < T; j++){
			
			if(sorted[i].id == trip[j].startID && sorted[i].id == trip[j].endID){
				total ++; 	
			}
			else { 
				if (sorted[i].id == trip[j].startID){
					total ++; 
				}
				else if(sorted[i].id == trip[j].endID){
					total++; 
				}
			}
			
			
		}
		cout << sorted[i].name << " (" << sorted[i].id << ") @ (" << sorted[i].latitude <<", " << sorted[i].longitude << "), ";
		cout << sorted[i].capacity << " capacity, " << total << " trips" << endl; 
		
	}
	
	
}


//
//This is a search function that searches the for the word and then returns the index of the word
//In this i am using .find function from string function
//If the word is not found -1 is returned 
//
int searchword(Stations sorted[], int i, string word){
	
	int a = 0; 
	
	a = sorted[i].name.find(word);
	return a; 
	
}



//
//This function takes input of a letters/word and then searches the word in the Station names. 
//If the letters/word is found it returns the station name, id, latitude, longitude and capacity
//This prints number of stations with the letters/words in it 
//
void findstations(Stations station[], int S, Trips trip[], int T){
	string word; 
	
	cin >> word; 
	
	Stations* sorted; 
	
	sorted = sortbyname(station, S); // using sortbyname function
	
	int iffound = 0; //a variable to determine if there exists a station 
	
	
	for(int h = 0; h <S ; h ++){
		int total = 0; 
		for(int j =0; j < T; j++){
			
			if(sorted[h].id == trip[j].startID && sorted[h].id == trip[j].endID){
				total ++; 	
			}
			else { 
				if (sorted[h].id == trip[j].startID){
					total ++; 
				}
				else if(sorted[h].id == trip[j].endID){
					total++; 
				}
			}
			
			
		}
		
		int A = searchword(sorted, h, word);//using searchword function 
		
		if(A != -1){
			cout << sorted[h].name << " (" << sorted[h].id << ") @ (" << sorted[h].latitude <<", " << sorted[h].longitude << "), ";
		    cout << sorted[h].capacity << " capacity, " << total << " trips" << endl; 
			
			iffound = 1;//if there are any stations the iffound becomes 1 
		}
		
		
	}
	// if no word is found then iffound == 0
	if(iffound == 0){
		cout << "  none found" << endl; 
	}
	
	
}


//
//This is a search function that searches the string for a particular word
//This returns the index of the word
//If not found returns -1
//
int searchword2(string word, string word1){
	
	int a = 0; 
	
	a = word.find(word1);
	return a; 
	
}


//
//This function find the index of semicolan from the startTime
//Then removes the colon 
//Then turns the string into int and returns the integer
//
int removecolon(string word){
	int a = 0; 
	a = searchword2(word, ":"); // searchword2 function called
	if (a != -1){
		word.erase(a, 1);
	}
	
	int b = 0; 
	
	b = stoi(word);
	return b ;
}

//
//This is a struct that stores id_1 and dur
//These are the id and duration 
//id is stored as string and duration as int
//
struct ST{
	string id_1; 
	int dur; 
};


//
//This function determines the trips which start between the start and the end time 
//It then stores the id of the trip as well as the duration into the struct as id_1 and dur respectively
//This returns st which is of type ST stuct
//
ST* finder(Trips trip[], int starti , int endi, int& s, ST st[], int T){
	
	
	
	for(int i = 0; i < T; i++){
		
		int c = removecolon(trip[i].startTime);//removecolon function called  
		
		if (starti > endi){ // if the start time is greater than end the clock turns to midnight and starts again from 0:00 eg duration 23:00 - 1:00
			if(c >= starti && c <= 2400){
				st[s].id_1 = trip[i].startID; 
				st[s].dur = trip[i].time; 
				s ++;
			}
			
			
			else if (c >= 0 && c <= endi){
				st[s].id_1 = trip[i].startID; 
				st[s].dur = trip[i].time; 
				s ++; 
			}		
		}
		else{
			if(c >= starti && c <= endi){
				st[s].id_1 = trip[i].startID; 
				st[s].dur = trip[i].time; 
				s ++;
			}
		}
	}
	
	return st;
}

//
//This function adds two strings
//It uses find to determine if the word already exists
//If n does not equal -1 that means the word exists in the string so it returns the original strings
//If the string doesnot exist it add the new string to original string and returns the modified string
//
string addString(string& A,string z){
	
	int n = A.find(z);
	
	if(n == -1){
		A = A + z + ", ";
	}
	return A; 
	
}

//
//This function has a nested loop
//This function loops through the data in stations and also in st 
//If the id of stations matched the id of st then it uses addString function to append the name into the new string
//Then it removes last two elements from the string because those are always , and then a space 
//It returns string A  
//
string searchid(Stations station[], int S, ST st[], int s){
	string A; 
	for(int i = 0; i < S ; i++) {
		for (int j=0; j< s ; j ++){
			
			if(station[i].id == st[j].id_1){
				string z = station[i].name;
				A = addString(A,z); // calling addString function
			}
		}
	}
	A.erase(A.size()-2,2);
	return A; 
}

//
//This function calculates the average of all of the durations of trips in the struct
//It does so in int
//Then divides by 60 to get the value in minutes
//This function returns p which is int
//
int averagecal(ST* st, int s){
	int NV = 0;
	for(int n = 0; n<s; n++){

		NV = NV + st[n].dur; 
		
	}
	
	int p = 0;
	
	p = NV/s; 
	
	p = p/60;
	
	return p; 
	
	
}

//
//This is a void function that prints number of trips, average duration and the names of the station on which the trips were made in the given timespan
//It takes keyboard input of two strings and uses removecolon to remove the colon and convert the string to int
//This the creates a new dynamically allocated array 
//Then uses finder to determine the number of trips and their data 
//If no trips are there it prints none found 
//This uses sortbyname to sort stations file by name 
//Then id is searched by searchid function to get the string which has all the names
//This then uses averagecal to calculate the average time in minutes
//Then prints number of trips, the average duration and the station names in alphabetical order
//
void triptime(Stations station[], int S, Trips trip[], int T){
	string start, end , biketime; 

	cin >> start; 
	cin >> end; 
	
	int starti = removecolon(start);//removecolon function called
	int endi = removecolon(end); //removecolon function called
	int s = 0;
	ST* st = new ST[T]; 
	st = finder(trip, starti, endi,s,st, T);//finder function called
	
	if (s == 0){
		cout << "  none found" << endl;
	}
	else{
	
		string a;

		Stations* sorted; 

		sorted = sortbyname(station, S);//sortbyname function called

		a = searchid(sorted, S, st, s);//searchid function called

		int NV = 0; 

		NV = averagecal(st, s);//averagecal function called

		cout << "  " << s << " trips found" << endl; 

		cout << "  avg duration: " << NV << " minutes" << endl; 

		cout << "  stations where trip started: " << a << endl; 
	}
	
	delete[] st; 
}




int main(){
	
	cout << "** Divvy Bike Data Analysis **" << endl; 
	
	// input stations file
	cout << "Please enter name of stations file>" << endl;
	string filename1;
	cin >> filename1; 
	
	Stations* station = nullptr;
	int S = 0;
	station = inputstation(filename1,S);
	
	if (station == nullptr) // file couldn't be opened:
   {
      cout << "** Error, unable to open stations file '" << filename1 << "'" << endl;
      return 0;
   }

	//input trips file 
	cout << "Please enter name of bike trips file>" << endl;
	string filename2;
	cin >> filename2; 
	
	Trips* trip = nullptr;
	int T = 0;
	trip = inputtrips(filename2,T);
	
	if (trip == nullptr) // file couldn't be opened:
   {
      cout << "** Error, unable to open trips file '" << filename2 << "'" << endl;
      return 0;
   }
	
	// input the command 
	string command; 
	cout << "Enter command (# to stop)> ";
    cin >> command;
	
	//If command = # then the program ends 
	while (command != "#"){
		
		
		if (command == "stats"){ //if command is stats 
			stats(station,S,T);
		}
		else if (command == "durations"){ //if command is durations
			duration(trip, T);
		}
		else if(command == "starting"){  //if command is starting
			starting(trip, T);
		}
		else if(command == "nearme"){ //if command is nearme
			nearme(station, S);
		}
		else if(command == "stations"){ //if command is stations
			allstations(station, S, trip, T);
		}
		else if(command == "find"){ //if command is find
			findstations(station, S, trip, T);
		}
		else if(command == "trips"){ //if command is trips
			triptime(station, S, trip, T);
		}
		else{
			cout << "** Invalid command, try again..." << endl;//if command is not any of the above
		}
		
		cout << "Enter command (# to stop)> " ;
		cin >> command;
	}
	cout << "** Done **" << endl; // print done in the end 

	delete[] station; //
	delete[] trip;    // delete both the dynamically allocated array 
	return 0 ;
}
