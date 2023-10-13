/*
 ****************************************
 Full Name  : Aydin Ghorbani
 Student ID#: 124170226
 Email      : aghorbani8@myseneca.ca
 
 
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 The parts that i searched or got help to do are mentioned.
 ****************************************
 */
#define _CRT_SECURE_NO_WARNINGS

#include "AirportModels.h"

#include <iostream>
#include <iomanip>
#include <fstream>
//#include <map>
#include <sstream>
//#include <vector>

using namespace std;

namespace sdds 
{

	AirportLog::AirportLog() : airports{ nullptr }, counter{ 0 }{}

    AirportLog::AirportLog(const char* fileName) : airports(nullptr), counter(0) {
        ifstream input(fileName);

        if (input.is_open()) {
            string line;
            getline(input, line); // Read and discard the first line

            while (getline(input, line)) {
                if (!line.empty()) {
                    istringstream iss(line);

                    // Allocate memory for the new airport.
                    Airport* newAirports = new Airport[counter + 1];
                    
                    // Copy existing airports into the new array.
                    for (size_t i = 0; i < counter; i++) {
                        newAirports[i] = airports[i];
                    }

                    // Read the comma-separated values into the new Airport object.
                    getline(iss, newAirports[counter].airportCode, ',');
                    getline(iss, newAirports[counter].airportName, ',');
                    getline(iss, newAirports[counter].airportCity, ',');
                    getline(iss, newAirports[counter].airportState, ',');
                    getline(iss, newAirports[counter].airportCountry, ',');
                    iss >> newAirports[counter].airportLatitude;
                    iss.ignore(); // Ignore the comma separator.
                    iss >> newAirports[counter].airportLongitude;
                    iss.ignore(); // Ignore the newline character.

                    counter++;

                    // Deallocate the old array and update the pointer.
                    delete[] airports;
                    airports = newAirports;
                }
            }

            input.close();
        }
    }

    std::ostream& operator<<(std::ostream& os, const Airport& airport)
    {
        if (airport.airportCode.empty()) {
            os << "Empty Airport";
        }
        else {
//            // Define a custom order for the keys
//            std::vector<std::string> keyOrder = {
//                "Airport Code", "Airport Name", "City", "State","Country",  "Latitude", "Longitude"
//            };
//
//            std::map<std::string, std::string> airportInfo;
//            airportInfo["Airport Code"] = airport.airportCode;
//            airportInfo["Airport Name"] = airport.airportName;
//            airportInfo["City"] = airport.airportCity;
//            airportInfo["Country"] = airport.airportCountry;
//            airportInfo["State"] = airport.airportState;
//            os.fill('.');
//
//            std::ostringstream latitudeStream, longitudeStream;
//            latitudeStream << std::fixed << std::setprecision(airport.airportLatitude == static_cast<int>(airport.airportLatitude) ? 0 : 4) << airport.airportLatitude;
//            longitudeStream << std::fixed << std::setprecision(airport.airportLongitude == static_cast<int>(airport.airportLongitude) ? 0 : 3) << airport.airportLongitude;
//            airportInfo["Latitude"] = latitudeStream.str();
//            airportInfo["Latitude"] = latitudeStream.str();
//            airportInfo["Longitude"] = longitudeStream.str();
//
//            for (const auto& key : keyOrder) {
//                os.width(20);
//                os << key << " : ";
//                os.setf(std::ios::left);
//                os.width(30);
//                os << airportInfo[key] << std::endl;
//                os.unsetf(std::ios::left);
//            }
//
//            os.fill(' ');
            
//*****************************************************
            
// too much effoet to make it auto, could not make the percisions properly.
            
//manual is the best.
            os.fill('.');
            os.width(20);
            os << "Airport Code" << " : ";
            os.setf(ios::left);
            os.width(30);
            os << airport.airportCode << std::endl;
            os.unsetf(ios::left);

            os.width(23);
            os << "Airport Name : ";
            os.setf(ios::left);
            os.width(30);
            os << airport.airportName << std::endl;
            os.unsetf(ios::left);

            os.width(23);
            os << "City : ";
            os.setf(ios::left);
            os.width(30);
            os << airport.airportCity << std::endl;
            os.unsetf(ios::left);

            os.width(23);
            os << "State : ";
            os.setf(ios::left);
            os.width(30);
            os << airport.airportState << std::endl;
            os.unsetf(ios::left);

            os.width(23);
            os << "Country : ";
            os.setf(ios::left);
            os.width(30);
            os << airport.airportCountry << std::endl;
            os.unsetf(ios::left);

            os.width(23);
            os << "Latitude : ";
            os.setf(ios::left);
            os.width(30);
            os << airport.airportLatitude << std::endl;
            os.unsetf(ios::left);

            os.width(23);
            os << "Longitude : ";
            os.setf(ios::left);
            os.width(30);
            os << airport.airportLongitude << std::endl;
            os.unsetf(ios::left);

            os.fill(' ');
        }

        return os;
    }

	void AirportLog::addAirport(Airport& airportLog)
	{
		Airport* tempAirport = new Airport[counter + 1];

		for (size_t i = 0; i < counter; i++) {
			tempAirport[i] = airports[i];
		}

		tempAirport[counter++] = airportLog;
		
		delete[] airports;
		airports = tempAirport;
	}

	AirportLog AirportLog::findAirport(const char* stateName, const char* countryName) 
	{
		AirportLog searchResult;

		for (size_t i = 0; i < counter; i++) 
		{
			if (airports[i].airportState == stateName && airports[i].airportCountry == countryName)
			{
				searchResult.addAirport(airports[i]);
			}
		}

		return searchResult;
	}

Airport AirportLog::operator[](size_t i) {
    return (i < counter) ? airports[i] : Airport();
}


	AirportLog::operator size_t() const{
		return counter;
	}

	AirportLog::~AirportLog(){
		delete[] airports;
	}

	AirportLog& AirportLog::operator=(const AirportLog& otherAr){
		if (this != &otherAr)
		{
			delete[] airports;
			
			counter = otherAr.counter;

			airports = new Airport[counter];
			for (size_t i = 0; i < counter; i++){
				airports[i] = otherAr.airports[i];
			}
		}

		return *this;
	}

	AirportLog::AirportLog(const AirportLog& otherAr)
    {
		if (this != &otherAr){
			*this = otherAr;
		}
	}

	AirportLog& AirportLog::operator=(AirportLog&& otherAr) noexcept
	{
		if (this != &otherAr){
			delete[] airports;

			airports = otherAr.airports;
			counter = otherAr.counter;

			otherAr.airports = nullptr;
			otherAr.counter = 0;
		}

		return *this;
	}

	AirportLog::AirportLog(AirportLog&& otherAr) noexcept
	{
		airports = otherAr.airports;
		counter = otherAr.counter;

		otherAr.airports = nullptr;
		otherAr.counter = 0;
	}
}
