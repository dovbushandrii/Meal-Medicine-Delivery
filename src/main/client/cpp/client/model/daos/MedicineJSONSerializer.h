#ifndef _MEDICINE_JSON_SERIAL_H_
#define _MEDICINE_JSON_SERIAL_H_

#include <string>
#include <nlohmann/json.hpp>
#include "../entities/Medicine.h"

//Converts Medicine obj to JSON
void to_json(nlohmann::json& j, const Medicine& ml);

//Converts JSON to Medicine obj
void from_json(const nlohmann::json& j, Medicine& ml);


#endif // !_MEDICINE_JSON_SERIAL_H_
