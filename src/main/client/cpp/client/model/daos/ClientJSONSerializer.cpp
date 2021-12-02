#include "ClientJSONSerializer.h"

//Converts Allergen obj to JSON
void to_json(nlohmann::json& j, const Allergen& al) {
    Allergen algen = al;
    j["name"] = algen.getName();
    j["id"] = algen.getId();
}

//Converts JSON to Allergen obj
void from_json(const nlohmann::json& j, Allergen& al) {
    al.setName(j["name"].get<std::string>());
    al.setId(j["id"].get<long>());
}

//Converts Client obj to JSON
void to_json(nlohmann::json& j, const Client& cl) {
    Client client = cl;
    j["id"] = client.getId();
    j["name"] = client.getName();
    j["surname"] = client.getSurname();
    j["phoneNumber"] = client.getPhoneNumber();
    j["email"] = client.getEmail();
    j["allergens"] = client.getAllergens();
}

//Converst JSON to Client obj
void from_json(const nlohmann::json& j, Client& client) {
    client.setId(j["id"].get<long>());
    client.setName(j["name"].get<std::string>());
    client.setSurname(j["surname"].get<std::string>());
    client.setPhoneNumber(j["phoneNumber"].get<std::string>());
    client.setEmail(j["email"].get<std::string>());
    std::vector<Allergen> allergens;
    j["allergens"].get_to <std::vector<Allergen>>(allergens);
    client.setAllergens(allergens);
}
