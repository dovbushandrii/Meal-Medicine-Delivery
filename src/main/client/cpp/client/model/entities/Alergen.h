/**
* @file Alergen.h
* @author Andrii Dovbush
* @brief Alergen class declaration
*
* Part of Meal-Medicine Delivery System
* This file contains Alergen class declaration.
*/

#ifndef _ALERGEN_H_
#define _ALERGEN_H_

#include <string>

class Alergen {
	std::string name;
public:
	Alergen() {}

	Alergen(std::string name) {
		this->name = name;
	}

    std::string getName() {
		return this->name;
	}
	void setName(std::string name) {
        this->name = name;
	}
};

#endif //!_ALERGEN_H_
