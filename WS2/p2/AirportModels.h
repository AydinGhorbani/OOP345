/*
 ****************************************
 Full Name  : Aydin Ghorbani
 Student ID#: 124170226
 Email      : aghorbani8@myseneca.ca
 
 
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 The parts that i searched or got help to do are mentioned.
 ****************************************
 */
#ifndef SDDS_AIRPORTMODELS_H
#define SDDS_AIRPORTMODELS_H

#include <iostream>
#include <string>
#include <map>

namespace sdds
{
	struct Airport{
        // source:https://www.geeksforgeeks.org/map-associative-containers-the-c-standard-template-library-stl/
        // the code could be in an single calss but the reason is th eoverloading the insesion operator which we had the same thing in SFT last semester.
		std::string airportCode{};
		std::string airportName{};
		std::string airportCity{};
		std::string airportState{};
		std::string airportCountry{};
		double airportLatitude = 0.0;
		double airportLongitude = 0.0;
	};
	std::ostream& operator<<(std::ostream& os, const Airport& airport);

	class AirportLog
	{
		Airport* airports{};
		size_t counter = 0;
	public:
		AirportLog();
		AirportLog(const char* fileName);
		void addAirport(Airport& airportLog);
        
		AirportLog findAirport(const char* stateName, const char* countryName);
		Airport operator[](size_t i);
		operator size_t() const;
		
        // roule of 5;
		AirportLog& operator=(const AirportLog& otherAr);
		AirportLog(const AirportLog& otherAr);
		AirportLog& operator=(AirportLog&& otherAr) noexcept;
		AirportLog(AirportLog&& otherAr) noexcept;
        ~AirportLog();
	};
}

#endif // !SDDS_AIRPORTMODELS_H
