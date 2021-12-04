/**
 * @file ClientRepository.java
 * @author Andrii Dovbush
 * @brief Client JPA Repository
 * <p>
 * Part of Meal-Medicine Delivery System.
 * This file contains ClientRepository interface.
 */

package cloudserver.model.repos;

import cloudserver.model.entities.Client;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface ClientRepository extends JpaRepository<Client,Long> {
}
