/**
* @file Facility.h
* @author Andrii Dovbush
* @brief Facility class declaration
*
* Part of Meal-Medicine Delivery System
* This file contains Facility class declaration.
*/

#ifndef _FACILITY_H_
#define _FACILITY_H_

#include <string>
#include <vector>
#include "Meal.h"
#include "Medicine.h"

class Facility {

	long id;

	std::string name;

	std::string phoneNumber;

	std::vector<Meal> mealList;

	std::vector<Medicine> medicineList;

public:

	Facility() {}

	Facility(long id,
		std::string name,
		std::string phoneNumber,
		std::vector<Meal> mealList,
		std::vector<Medicine> medicineList) {

		this->id = id;
		this->name = name;
		this->phoneNumber = phoneNumber;
		this->mealList = mealList;
		this->medicineList = medicineList;
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

	std::string getPhoneNumber() {
		return this->phoneNumber;
	}
	void setPhoneNumber(std::string phoneNumber) {
		this->phoneNumber = phoneNumber;
	}

	std::vector<Meal> getMealList() {
		return this->mealList;
	}
	void setMeals(std::vector<Meal> mealList) {
		this->mealList = mealList;
	}

	std::vector<Medicine> getMedicineList() {
		return this->medicineList;
	}
	void setMedicines(std::vector<Medicine> medicineList) {
		this->medicineList = medicineList;
	}
};

#endif // !_MEAL_H_
