#ifndef PENDINGORDER_H
#define PENDINGORDER_H

#include <string>
#include <vector>

class PendingOrder {

    long id;

    long clientId;

    std::vector<std::pair<long,int>> mealIds;

    std::vector<std::pair<long,int>> medicineIds;

public:

    PendingOrder() {}

    PendingOrder(long id,
        long clientId,
        std::vector<std::pair<long,int>> mealIds,
        std::vector<std::pair<long,int>> medicineIds) {

        this->id = id;
        this->clientId = clientId;
        this->mealIds = mealIds;
        this->medicineIds = medicineIds;

    }

    long getId() {
        return this->id;
    }
    void setId(long id) {
        this->id = id;
    }

    long getClientId() {
        return this->clientId;
    }
    void setClientId(long clientId) {
        this->clientId = clientId;
    }

    std::vector<std::pair<long,int>> getMealIds() {
        return this->mealIds;
    }
    void setMealIds( std::vector<std::pair<long,int>> mealIds) {
        this->mealIds = mealIds;
    }

    std::vector<std::pair<long,int>> getMedicineIds() {
        return this->medicineIds;
    }
    void setMedicineIds( std::vector<std::pair<long,int>> medicineIds) {
        this->medicineIds = medicineIds;
    }

};

#endif // PENDINGORDER_H
