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
import java.util.Optional;
import java.util.stream.Collectors;

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
    public List<Meal> getMeals(@RequestParam(value = "limit", required = false) Optional<Long> limit,
                               @RequestParam(value = "sort", required = false) Optional<String> sort) {

        List<Meal> meals = dao.read();
        //TODO sorting
        if (limit.isPresent()) {
            meals = meals.stream()
                    .limit(limit.get())
                    .collect(Collectors.toList());
        }
        return meals;
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
