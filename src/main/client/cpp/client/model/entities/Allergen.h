/**
* @file Alergen.h
* @author Andrii Dovbush
* @brief Alergen class declaration
*
* Part of Meal-Medicine Delivery System
* This file contains Alergen class declaration.
*/

#ifndef _ALLERGEN_H_
#define _ALLERGEN_H_

#include <string>

class Allergen {
	long id;
	std::string name;
public:

	Allergen() {}

	Allergen(long id,
		std::string name) {
		this->id = id;
		this->name = name;
	}

	long getId() {
		return this->id;
	}
	void setId(long id) {
		this->id = id;
	}

	std::string getName() {
		return this->name;
	}
	void setName(std::string name) {
		this->name = name;
	}
};

#endif //!_ALLERGEN_H_