/**
* @file OrderDAO.h
* @author Andrii Dovbush
* @brief OrderDAO class declaration
*
* Part of Meal-Medicine Delivery System
* This file contains Meal Data Access Object class declaration.
*/

#ifndef _MEAL_DAO_H_
#define _MEAL_DAO_H_

#include "ServerURLs.h"
#include "MealJSONSerializer.h"
#include "HTTPSender.h"
#include <vector>

class MealDAO {
public:
	//DONE
	bool createMeal(Meal meal) {
		nlohmann::json  j{};
		to_json(j, meal);
		std::string json = j.dump();

		HTTPSender send;
		HTTPResponse* response = send.doMethodWithJSONBody(MEALS_URL, HTTPMethod::HTTP_POST, json);
		bool returns = response->getStatusCode() == 200;

		delete response;
		return returns;
	}

	//DONE
	std::vector<Meal> readMeals() {
		HTTPSender send;
		HTTPResponse* response = send.doRequest(MEALS_URL, HTTPMethod::HTTP_GET);
		std::vector<Meal> meals;

		if (response->getStatusCode() == 200) {
			nlohmann::json  j = nlohmann::json::parse(response->getResponse());
			j.get_to<std::vector<Meal>>(meals);
		}

		delete response;
		return meals;
	}

	//DONE
	Meal* readMeal(long id) {
		std::string URL = MEALS_URL"/" + std::to_string(id);

		HTTPSender send;
		HTTPResponse* response = send.doRequest(URL, HTTPMethod::HTTP_GET);

		if (response->getStatusCode() == 200) {
			Meal* meal = new Meal();
			nlohmann::json  j = nlohmann::json::parse(response->getResponse());
			*meal = j.get<Meal>();
			delete response;
			return meal;
		}

		delete response;
		return nullptr;
	}

	//DONE
	bool updateMeal(Meal meal) {
		nlohmann::json  j{};
		to_json(j, meal);
		std::string json = j.dump();

		HTTPSender send;
		HTTPResponse* response = send.doMethodWithJSONBody(MEALS_URL, HTTPMethod::HTTP_PATCH, json);
		bool returns = response->getStatusCode() == 200;

		delete response;
		return returns;
	}

	//DONE
	void deleteMeal(Meal meal) {
		this->deleteMealById(meal.getId());
	}

	//DONE
	void deleteMealById(long id) {
		std::string URL = MEALS_URL"/" + std::to_string(id);

		HTTPSender send;
        send.doRequest(URL, HTTPMethod::HTTP_DELETE);
	}

	//DONE
	void deleteMeals() {
		HTTPSender send;
        send.doRequest(MEALS_URL, HTTPMethod::HTTP_DELETE);
	}
};

#endif // !_MEAL_DAO_H_
