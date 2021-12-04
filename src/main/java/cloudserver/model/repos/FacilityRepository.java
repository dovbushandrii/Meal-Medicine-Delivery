/**
 * @file FacilityRepository.java
 * @author Andrii Dovbush
 * @brief Facility JPA Repository
 * <p>
 * Part of Meal-Medicine Delivery System.
 * This file contains FacilityRepository interface.
 */
package cloudserver.model.repos;

import cloudserver.model.entities.Facility;
import org.springframework.data.jpa.repository.JpaRepository;

public interface FacilityRepository extends JpaRepository<Facility, Long> {
}
