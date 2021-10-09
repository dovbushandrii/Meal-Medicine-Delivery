/**
* @file OrderDAO.h
* @author Andrii Dovbush
* @brief OrderDAO class declaration
*
* Part of Meal-Medicine Delivery System
* This file contains Meal Data Access Object class declaration.
*/

#ifndef _MEAL_DAO_H_
#define _MEAL_DAO_H_

#include "../entities/Meal.h"
#include <vector>

class MealDAO {
public:

	void createMeal(Meal meal);

	std::vector<Meal> readMeals();

	Meal readMeal(long id);

	void updateMeal(Meal meal);

	void deleteMeal(Meal meal);

	void deleteMealById(long id);

	void deleteMeals();
};

#endif // !_MEAL_DAO_H_
