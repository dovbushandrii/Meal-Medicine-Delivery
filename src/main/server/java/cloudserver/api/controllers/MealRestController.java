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
import cloudserver.model.entities.Meal;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/meals")
public class MealRestController {

    private MealDAO dao;

    @Autowired
    public MealRestController(@Qualifier("mealDAO") MealDAO dao) {
        this.dao = dao;
    }

    @PostMapping()
    public Meal saveMeal(Meal meal) {
        return dao.create(meal);
    }

    @GetMapping("/{id}")
    public Meal getMeal(@PathVariable("id") Long id) {
        return dao.read(id);
    }

    @GetMapping()
    public List<Meal> getMeals() {
        return dao.read();
    }

    @PatchMapping()
    public Meal updateMeal(Meal meal) {
        return dao.update(meal);
    }

    @PatchMapping("/upsert")
    public Meal upsertMeal(Meal meal) {
        return dao.upsert(meal);
    }

    @DeleteMapping("/{id}")
    public void deleteMeal(@PathVariable("id") Long id) {
        dao.delete(id);
    }

    @DeleteMapping()
    public void deleteMeal() {
        dao.delete();
    }
}
