#ifndef _ORDER_JSON_SERIAL_H_
#define _ORDER_JSON_SERIAL_H_

#include <string>
#include <nlohmann/json.hpp>
#include "Order.h"
#include "MealJSONSerializer.h"
#include "MedicineJSONSerializer.h"
#include "ClientJSONSerializer.h"

//Converts Order obj to JSON
void to_json(nlohmann::json& j, const Order& ord) {
	Order order = ord;
	j["id"] = order.getId();
	tm dateTime = order.getDateAndTime();
	j["dateTime"] = {dateTime.tm_year, 
		dateTime.tm_mon, 
		dateTime.tm_mday, 
		dateTime.tm_hour, 
		dateTime.tm_min, 
		dateTime.tm_sec};
	j["client"] = order.getClient();
	j["meals"] = order.getMeals();
	j["medicines"] = order.getMedicines();
}

//Converts JSON to Order obj
void from_json(const nlohmann::json& j, Order& ord) {
	ord.setId(j["id"].get<long>());
	tm dateTime;
	std::vector<int> data = j["dateTime"].get<std::vector<int>>();
	dateTime.tm_year = data[0];
	dateTime.tm_mon = data[1];
	dateTime.tm_mday = data[2];
	dateTime.tm_hour = data[3];
	dateTime.tm_min = data[4];
	dateTime.tm_sec = data[5];
	ord.setDateAndTime(dateTime);
	ord.setClient(j["client"].get<Client>());
	ord.setMeals(j["meals"].get<std::vector<Meal>>());
	ord.setMedicines(j["medicines"].get<std::vector<Medicine>>());
}

#endif // !_ORDER_JSON_SERIAL_H_

