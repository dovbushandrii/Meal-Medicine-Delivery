#ifndef _CLIENT_JSON_SERIAL_H_
#define _CLIENT_JSON_SERIAL_H_

#include <string>
#include <nlohmann/json.hpp>
#include "../entities/Client.h"

//Converts Allergen obj to JSON
void to_json(nlohmann::json& j, const Allergen& al);

//Converts JSON to Allergen obj
void from_json(const nlohmann::json& j, Allergen& al);

//Converts Client obj to JSON
void to_json(nlohmann::json& j, const Client& cl);

//Converst JSON to Client obj
void from_json(const nlohmann::json& j, Client& client);

#endif // !_CLIENT_JSON_SERIAL_H_
