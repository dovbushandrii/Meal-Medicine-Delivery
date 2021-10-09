/**
 * @file OrderRepository.java
 * @author Andrii Dovbush
 * @brief Order JPA Repository
 * <p>
 * Part of Meal-Medicine Delivery System
 * This file contains OrderRepository interface.
 */

package cloudserver.model.repos;

import cloudserver.model.entities.Order;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface OrderRepository extends JpaRepository<Order,Long> {
}
