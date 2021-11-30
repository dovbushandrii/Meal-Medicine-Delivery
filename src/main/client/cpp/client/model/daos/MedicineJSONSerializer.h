#ifndef _MEDICINE_JSON_SERIAL_H_
#define _MEDICINE_JSON_SERIAL_H_

#include <string>
#include <nlohmann/json.hpp>
#include "../entities/Medicine.h"

//Converts Medicine obj to JSON
void to_json(nlohmann::json& j, const Medicine& ml) {
	Medicine meal = ml;
	j["id"] = meal.getId();
	j["description"] = meal.getDescription();
	j["price"] = meal.getPrice();
	j["image"] = meal.getImage();
}

//Converts JSON to Medicine obj
void from_json(const nlohmann::json& j, Medicine& ml) {
	ml.setId(j["id"].get<long>());
	ml.setDescription(j["description"].get<std::string>());
	ml.setPrice(j["price"].get<double>());
	ml.setImage(j["image"].get<std::string>());
}


#endif // !_MEDICINE_JSON_SERIAL_H_
