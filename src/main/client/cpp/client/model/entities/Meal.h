/**
* @file Meal.h
* @author Andrii Dovbush
* @brief Meal class declaration
* 
* Part of Meal-Medicine Delivery System
* This file contains Meal class declaration.
*/

#ifndef _MEAL_H_
#define _MEAL_H_

#include <string>

class Meal {

	long id;

	std::string description;

	double price;

	//Represents weight in grams.
	unsigned weight;

public:

	Meal() {}

	Meal(long id,
		std::string description,
		double price,
		unsigned weight) {

		this->id = id;
		this->description = description;
		this->price = price;
		this->weight = weight;
	}

	long getId() {
		return this->id;
	}

	std::string getDescription() {
		return this->description;
	}
	void setDescription(std::string description) {
		this->description = description;
	}

	double getPrice() {
		return this->price;
	}
	void setPrice(double price) {
		this->price = price;
	}

	unsigned getWeight() {
		return this->weight;
	}
	void setWeight(unsigned weight) {
		this->weight = weight;
	}

};

#endif // !_MEAL_H_