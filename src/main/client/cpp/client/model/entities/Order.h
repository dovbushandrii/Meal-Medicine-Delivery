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
		this->dateAndTime;
		this->totalSum = calculateSum(meals, medicines);
		this->client = client;
		this->meals = meals;
		this->medicines = medicines;

	}

	long getId();

	tm getDateAndTime();
	void setDateAndTime(tm dateAndTime);

	double getTotalSum();
	void updateTotalSum();

	Client getClient();
	void setClient(Client client);

	std::vector<Meal> getMeals();
	void setMeals(std::vector<Meal> meals);

	std::vector<Medicine> getMedicines();
	void setMedicines(std::vector<Medicine> medicines);

};

#endif // !_ORDER_H_