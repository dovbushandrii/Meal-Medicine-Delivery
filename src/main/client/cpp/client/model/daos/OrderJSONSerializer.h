#ifndef _ORDER_JSON_SERIAL_H_
#define _ORDER_JSON_SERIAL_H_

#include <string>
#include <nlohmann/json.hpp>
#include "../entities/Order.h"
#include "MealJSONSerializer.h"
#include "MedicineJSONSerializer.h"
#include "ClientJSONSerializer.h"

//Converts Order obj to JSON
void to_json(nlohmann::json& j, const Order& ord);

//Converts JSON to Order obj
void from_json(const nlohmann::json& j, Order& ord);

#endif // !_ORDER_JSON_SERIAL_H_

