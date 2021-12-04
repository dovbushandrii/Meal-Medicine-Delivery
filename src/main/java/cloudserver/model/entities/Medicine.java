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
import org.hibernate.annotations.Type;

import javax.persistence.*;
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

    @Lob
    @Type(type = "text")
    private String image;
}
