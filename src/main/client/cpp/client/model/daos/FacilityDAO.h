/**
* @file FacilityDAO.h
* @author Andrii Dovbush
* @brief FacilityDAO class declaration
*
* Part of Meal-Medicine Delivery System
* This file contains Facility Data Access Object class declaration.
*/

#ifndef _FACILITY_DAO_H_
#define __FACILITY_DAO_H_

#include "ServerURLs.h"
#include "FacilityJSONSerializer.h"
#include "HTTPSender.h"
#include <vector>

class FacilityDAO {
public:

	//DONE
	bool createFacility(Facility facility) {
		nlohmann::json  j{};
		to_json(j, facility);
		std::string json = j.dump();

		HTTPSender send;
		HTTPResponse* response = send.doMethodWithJSONBody(FACILITIES_URL, HTTPMethod::HTTP_POST, json);
		bool returns = response->getStatusCode() == 200;

		delete response;
		return returns;
	}

	//DONE
	std::vector<Facility> readFacilities() {
		HTTPSender send;
		HTTPResponse* response = send.doRequest(FACILITIES_URL, HTTPMethod::HTTP_GET);
		std::vector<Facility> facilities;

		if (response->getStatusCode() == 200) {
			nlohmann::json  j = nlohmann::json::parse(response->getResponse());
			j.get_to<std::vector<Facility>>(facilities);
		}

		delete response;
		return facilities;
	}

	//DONE
	Facility* readFacility(long id) {
		std::string URL = FACILITIES_URL"/" + std::to_string(id);

		HTTPSender send;
		HTTPResponse* response = send.doRequest(URL, HTTPMethod::HTTP_GET);

		if (response->getStatusCode() == 200) {
			Facility* facility = new Facility();
			nlohmann::json  j = nlohmann::json::parse(response->getResponse());
			*facility = j.get<Facility>();
			delete response;
			return facility;
		}

		delete response;
		return nullptr;
	}

	//DONE
	bool updateFacility(Facility facility) {
		nlohmann::json  j{};
		to_json(j, facility);
		std::string json = j.dump();

		HTTPSender send;
		HTTPResponse* response = send.doMethodWithJSONBody(FACILITIES_URL, HTTPMethod::HTTP_PATCH, json);
		bool returns = response->getStatusCode() == 200;

		delete response;
		return returns;
	}

	//DONE
	void deleteFacility(Facility facility) {
		this->deleteFacilityById(facility.getId());
	}

	//DONE
	void deleteFacilityById(long id) {
		std::string URL = FACILITIES_URL"/" + std::to_string(id);

		HTTPSender send;
        send.doRequest(URL, HTTPMethod::HTTP_DELETE);
	}

	//DONE
	void deleteFacilities() {
		HTTPSender send;
        send.doRequest(FACILITIES_URL, HTTPMethod::HTTP_DELETE);
	}
};


#endif // !__FACILITY_DAO_H_
