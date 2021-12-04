#ifndef PENDINGORDER_H
#define PENDINGORDER_H

#include <string>
#include <vector>
#include "Order.h"

class PendingOrder {

    long id;

    long clientId;

    std::vector<std::pair<long,int>> mealIds;

    std::vector<std::pair<long,int>> medicineIds;

    void addItemToList(long id,std::vector<std::pair<long,int>> *list) {
        for(int i = 0; i < (int)list->size(); i++){
            if((*list)[i].first == id){
                (*list)[i].second++;
                return;
            }
        }
        list->push_back({id,1});
    }

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

    void fillFromOrder(Order order){
        this->clientId = order.getClient().getId();
        this->id = order.getId();
        std::vector<std::pair<long,int>> mealIds;
        std::vector<std::pair<long,int>> medicineIds;
        for(Meal meal : order.getMeals()) {
            addItemToList(meal.getId(),&mealIds);
        }
        for(Medicine medicine : order.getMedicines()) {
            addItemToList(medicine.getId(),&medicineIds);
        }
        this->setMealIds(mealIds);
        this->setMedicineIds(medicineIds);
    }

    Order createConfirmedOrder(){
        Order order;
        Client client;
        Meal meal;
        std::vector<Meal> meals;
        Medicine medicine;
        std::vector<Medicine> medicines;
        client.setId(clientId);
        order.setClient(client);
        for(int i = 0; i < (int)mealIds.size(); i++) {
            for(int j = 0; j < mealIds[i].second; j++) {
                meal.setId(mealIds[i].first);
                meals.push_back(meal);
            }
        }
        order.setMeals(meals);
        for(int i = 0; i < (int)medicineIds.size(); i++) {
            for(int j = 0; j < medicineIds[i].second; j++) {
                medicine.setId(medicineIds[i].first);
                medicines.push_back(medicine);
            }
        }
        order.setMedicines(medicines);
        return order;
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
