/**
 * @file Medicine.java
 * @author Andrii Dovbush
 * @brief Medicine class for server
 * <p>
 * Part of Meal-Medicine Delivery System.
 * This file contains Medicine class.
 */

package cloudserver.model.entities;

import lombok.Data;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.PositiveOrZero;

@Data
@Entity
public class Medicine {
    @Id
    @GeneratedValue
    private Long id;

    @NotNull
    private String description;

    @PositiveOrZero
    private Double price;
}
