/**
 * @file Meal.java
 * @author Andrii Dovbush
 * @brief Meal class for server
 * <p>
 * Part of Meal-Medicine Delivery System.
 * This file contains Meal class.
 */

package cloudserver.model.entities;

import lombok.Data;
import org.hibernate.annotations.Type;

import javax.persistence.*;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.PositiveOrZero;

@Data
@Entity
public class Meal {
    @Id
    @GeneratedValue
    private Long id;

    @NotNull
    private String description;

    @PositiveOrZero
    private Double price;

    @PositiveOrZero
    //In grams
    private Integer weight;

    @Lob
    @Type(type = "text")
    private String image;
}
