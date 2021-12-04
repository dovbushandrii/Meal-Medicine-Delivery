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
import cloudserver.model.entities.Client;
import cloudserver.model.entities.Meal;
import cloudserver.model.jsonparsers.ParserJSON;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

@RestController
@RequestMapping("/meals")
public class MealRestController {

    final private MealDAO dao;
    final private ParserJSON parser;

    @Autowired
    public MealRestController(@Qualifier("mealDAO") MealDAO dao,
                              @Qualifier("JSONParser") ParserJSON parser) {
        this.dao = dao;
        this.parser = parser;
    }

    @PostMapping()
    public Meal saveMeal(@RequestBody String json) {
        return dao.create((Meal) parser.parse(json,Meal.class));
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
    public Meal updateMeal(@RequestBody String json) {
        return dao.update((Meal) parser.parse(json,Meal.class));
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
