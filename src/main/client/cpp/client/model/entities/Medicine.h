/**
* @file Medicine.h
* @author Andrii Dovbush
* @brief Medicine class declaration
* 
* Part of Meal-Medicine Delivery System
* This file contains Medicine class declaration.
*/

#ifndef _MEDICINE_H_
#define _MEDICINE_H_

#include <string>

class Medicine {

	long id;

	std::string description;

	double price;

public:

	Medicine() {}

	Medicine(long id,
		std::string description,
		double price) {

		this->id = id;
		this->description = description;
		this->price = price;
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

};

#endif // !_MEDICINE_H_
