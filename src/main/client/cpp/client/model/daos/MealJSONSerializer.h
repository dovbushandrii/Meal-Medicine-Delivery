#ifndef _MEAL_JSON_SERIAL_H_
#define _MEAL_JSON_SERIAL_H_

#include <string>
#include <nlohmann/json.hpp>
#include "../entities/Meal.h"

//Converts Meal obj to JSON
void to_json(nlohmann::json& j, const Meal& ml);

//Converts JSON to Meal obj
void from_json(const nlohmann::json& j, Meal& ml);

#endif // !_MEAL_JSON_SERIAL_H_

