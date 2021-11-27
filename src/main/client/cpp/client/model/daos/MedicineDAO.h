/**
* @file MedicineDAO.h
* @author Andrii Dovbush
* @brief MedicineDAO class declaration
*
* Part of Meal-Medicine Delivery System
* This file contains Medicine Data Access Object class declaration.
*/

#ifndef _MEDICINE_DAO_H_
#define _MEDICINE_DAO_H_

#include "ServerURLs.h"
#include "MedicineJSONSerializer.h"
#include "HTTPSender.h"
#include <vector>

class MedicineDAO {
public:

	//DONE
	bool createMedicine(Medicine medicine) {
		nlohmann::json  j{};
		to_json(j, medicine);
		std::string json = j.dump();

		HTTPSender send;
		HTTPResponse* response = send.doMethodWithJSONBody(MEDICINES_URL, HTTPMethod::HTTP_POST, json);
		bool returns = response->getStatusCode() == 200;

		delete response;
		return returns;
	}

	//DONE
	std::vector<Medicine> readMedicines() {
		HTTPSender send;
		HTTPResponse* response = send.doRequest(MEDICINES_URL, HTTPMethod::HTTP_GET);
		std::vector<Medicine> medicines;

		if (response->getStatusCode() == 200) {
			nlohmann::json  j = nlohmann::json::parse(response->getResponse());
			j.get_to<std::vector<Medicine>>(medicines);
		}

		delete response;
		return medicines;
	}

	//DONE
	Medicine* readMedicine(long id) {
		std::string URL = MEDICINES_URL"/" + std::to_string(id);

		HTTPSender send;
		HTTPResponse* response = send.doRequest(URL, HTTPMethod::HTTP_GET);

		if (response->getStatusCode() == 200) {
			Medicine* medicine = new Medicine();
			nlohmann::json  j = nlohmann::json::parse(response->getResponse());
			*medicine = j.get<Medicine>();
			delete response;
			return medicine;
		}

		delete response;
		return nullptr;
	}

	//DONE
	bool updateMedicine(Medicine meal) {
		nlohmann::json  j{};
		to_json(j, meal);
		std::string json = j.dump();

		HTTPSender send;
		HTTPResponse* response = send.doMethodWithJSONBody(MEDICINES_URL, HTTPMethod::HTTP_PATCH, json);
		bool returns = response->getStatusCode() == 200;

		delete response;
		return returns;
	}

	//DONE
	void deleteMedicine(Medicine meal) {
		this->deleteMedicineById(meal.getId());
	}

	//DONE
	void deleteMedicineById(long id) {
		std::string URL = MEDICINES_URL"/" + std::to_string(id);

		HTTPSender send;
		HTTPResponse* response = send.doRequest(URL, HTTPMethod::HTTP_DELETE);
	}

	//DONE
	void deleteMedicines() {
		HTTPSender send;
		HTTPResponse* response = send.doRequest(MEDICINES_URL, HTTPMethod::HTTP_DELETE);
		bool returns = response->getStatusCode() == 200;
	}
};

#endif // !_MEDICINE_DAO_H_
