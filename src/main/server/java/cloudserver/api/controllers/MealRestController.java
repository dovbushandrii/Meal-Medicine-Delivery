/**
 * @file MealRestController.java
 * @author Andrii Dovbush
 * @brief REST Controller for Meal objects
 * <p>
 * Part of Meal-Medicine Delivery System.
 * This file contains REST Controller for Meal objects.
 */

package cloudserver.api.controllers;

import cloudserver.model.daos.MealDAO;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class MealRestController {

    private MealDAO dao;

    @Autowired
    public MealRestController(@Qualifier("mealDAO") MealDAO dao) {
        this.dao = dao;
    }
}
