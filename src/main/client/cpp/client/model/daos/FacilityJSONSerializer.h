#ifndef _FACILITY_JSON_SERIAL_H_
#define _FACILITY_JSON_SERIAL_H_

#include <string>
#include <nlohmann/json.hpp>
#include "../entities/Facility.h"
#include "MealJSONSerializer.h"
#include "MedicineJSONSerializer.h"

//Converts Facility obj to JSON
void to_json(nlohmann::json& j, const Facility& fac);

//Converts JSON to Facility obj
void from_json(const nlohmann::json& j, Facility& fac);

#endif // !_FACILITY_JSON_SERIAL_H_

