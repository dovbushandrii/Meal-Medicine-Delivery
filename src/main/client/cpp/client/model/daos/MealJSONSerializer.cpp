#include "MealJSONSerializer.h"

#include <string>
#include <nlohmann/json.hpp>
#include "../entities/Meal.h"

//Converts Meal obj to JSON
void to_json(nlohmann::json& j, const Meal& ml) {
    Meal meal = ml;
    j["id"] = meal.getId();
    j["description"] = meal.getDescription();
    j["price"] = meal.getPrice();
    j["weight"] = meal.getWeight();
    j["image"] = meal.getImage();
}

//Converts JSON to Meal obj
void from_json(const nlohmann::json& j, Meal& ml) {
    ml.setId(j["id"].get<long>());
    ml.setDescription(j["description"].get<std::string>());
    ml.setPrice(j["price"].get<double>());
    ml.setWeight(j["weight"].get<unsigned>());
    ml.setImage(j["image"].get<std::string>());
}
