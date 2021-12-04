/**
 * @file MealDAO.java
 * @author Andrii Dovbush
 * @brief Meal Data Access Object
 * <p>
 * Part of Meal-Medicine Delivery System.
 * This file contains Meal Data Access Object class.
 */

package cloudserver.model.daos;

import cloudserver.model.entities.Meal;
import cloudserver.model.repos.MealRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.NoSuchElementException;

@Component("mealDAO")
public class MealDAO {

    private MealRepository repo;

    @Autowired
    public MealDAO(MealRepository repo) {
        this.repo = repo;
    }

    @Transactional
    public Meal create(Meal meal) {
        return repo.save(meal);
    }

    @Transactional
    public Meal read(Long id) {
        return repo.findById(id).get();
    }

    @Transactional
    public List<Meal> read() {
        return repo.findAll();
    }

    public Meal upsert(Meal meal) {
        repo.deleteById(meal.getId());
        return repo.save(meal);
    }

    public Meal update(Meal meal) {
        if (repo.findById(meal.getId()).isPresent()) {
            repo.deleteById(meal.getId());
            return repo.save(meal);
        }
        throw new NoSuchElementException("There is no Meal with ID: " + meal.getId());
    }

    public void delete(Long id) {
        repo.deleteById(id);
    }

    public void delete() {
        repo.deleteAll();
    }
}
