#include "OrderJSONSerializer.h"

//Converts Order obj to JSON
void to_json(nlohmann::json& j, const Order& ord) {
    Order order = ord;
    j["id"] = order.getId();
    j["dateTime"] = nullptr;
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
