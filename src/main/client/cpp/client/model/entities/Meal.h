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

	long getId();

	std::string getDescription();
	void setDescription(std::string description);

	double getPrice();
	void setPrice(double price);

	unsigned getWeight();
	void setWeight(unsigned weight);

};

#endif // !_MEAL_H_