#ifndef _FACILITY_JSON_SERIAL_H_
#define _FACILITY_JSON_SERIAL_H_

#include <string>
#include <nlohmann/json.hpp>
#include "Facility.h"
#include "MealJSONSerializer.h"
#include "MedicineJSONSerializer.h"

//Converts Facility obj to JSON
void to_json(nlohmann::json& j, const Facility& fac) {
	Facility facility = fac;
	j["id"] = facility.getId();
	j["name"] = facility.getName();
	j["phoneNumber"] = facility.getPhoneNumber();
	j["mealList"] = facility.getMealList();
	j["medicineList"] = facility.getMedicineList();
}

//Converts JSON to Facility obj
void from_json(const nlohmann::json& j, Facility& fac) {
	fac.setId(j["id"].get<long>());
	fac.setName(j["name"].get<std::string>());
	fac.setPhoneNumber(j["phoneNumber"].get<std::string>());
	fac.setMeals(j["mealList"].get<std::vector<Meal>>());
	fac.setMedicines(j["medicineList"].get<std::vector<Medicine>>());
}

#endif // !_FACILITY_JSON_SERIAL_H_

