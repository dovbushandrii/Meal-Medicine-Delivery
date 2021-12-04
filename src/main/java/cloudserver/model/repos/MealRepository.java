/**
 * @file MealRepository.java
 * @author Andrii Dovbush
 * @brief Meal JPA Repository
 * <p>
 * Part of Meal-Medicine Delivery System.
 * This file contains MealRepository interface.
 */

package cloudserver.model.repos;

import cloudserver.model.entities.Meal;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface MealRepository extends JpaRepository<Meal,Long> {
}
