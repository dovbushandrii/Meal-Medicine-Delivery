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

	std::string image;

public:

	Meal() {}

	Meal(long id,
		std::string description,
		double price,
		unsigned weight,
		std::string image) {

		this->id = id;
		this->description = description;
		this->price = price;
		this->weight = weight;
		this->image = image;
	}

	long getId() {
		return this->id;
	}
	void setId(long id) {
		this->id = id;
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

	std::string getImage() {
		return this->image;
	}
	void setImage(std::string image) {
		this->image = image;
	}
};

#endif // !_MEAL_H_