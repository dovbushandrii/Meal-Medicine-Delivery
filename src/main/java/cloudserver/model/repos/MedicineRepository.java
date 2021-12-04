/**
 * @file MedicineRepository.java
 * @author Andrii Dovbush
 * @brief Medicine JPA Repository
 * <p>
 * Part of Meal-Medicine Delivery System.
 * This file contains MedicineRepository interface.
 */

package cloudserver.model.repos;

import cloudserver.model.entities.Medicine;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface MedicineRepository extends JpaRepository<Medicine,Long> {
}
