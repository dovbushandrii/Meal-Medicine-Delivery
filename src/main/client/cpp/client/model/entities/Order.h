/**
* @file Order.h
* @author Andrii Dovbush
* @brief Order class declaration
* 
* Part of Meal-Medicine Delivery System
* This file contains Order class declaration.
*/

#ifndef _ORDER_H_
#define _ORDER_H_

#include <string>
#include <vector>
#include <ctime>

#include "Client.h"
#include "Meal.h"
#include "Medicine.h"

class Order {

	long id;

	tm dateAndTime;

	double totalSum;

	Client client;

	std::vector<Meal> meals;

	std::vector<Medicine> medicines;

	double calculateSum(std::vector<Meal> meals,
		std::vector<Medicine> medicines);
public:

	Order() {}

	Order(long id,
		tm dateAndTime,
		Client client,
		std::vector<Meal> meals,
		std::vector<Medicine> medicines) {

		this->id = id;
        this->dateAndTime = dateAndTime;
		this->totalSum = calculateSum(meals, medicines);
		this->client = client;
		this->meals = meals;
		this->medicines = medicines;

	}

	long getId() {
		return this->id;
	}
	void setId(long id) {
		this->id = id;
	}

	tm getDateAndTime() {
		return this->dateAndTime;
	}
	void setDateAndTime(tm dateAndTime) {
		this->dateAndTime = dateAndTime;
	}

	double getTotalSum() {
		return this->totalSum;
	}
	void updateTotalSum() {
		this->totalSum = 0.0;
        for (size_t i = 0; i < this->meals.size(); i++) {
			this->totalSum += this->meals[i].getPrice();
		}
        for (size_t i = 0; i < this->medicines.size(); i++) {
			this->totalSum += this->medicines[i].getPrice();
		}
	}

	Client getClient() {
		return this->client;
	}
	void setClient(Client client) {
		this->client = client;
	}

	std::vector<Meal> getMeals() {
		return this->meals;
	}
	void setMeals(std::vector<Meal> meals) {
		this->meals = meals;
	}

	std::vector<Medicine> getMedicines() {
		return this->medicines;
	}
	void setMedicines(std::vector<Medicine> medicines) {
		this->medicines = medicines;
	}

};

#endif // !_ORDER_H_
