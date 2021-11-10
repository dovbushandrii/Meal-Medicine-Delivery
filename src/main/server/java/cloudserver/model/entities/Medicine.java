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

import javax.persistence.*;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.PositiveOrZero;
import java.util.List;

@Data
@Entity
public class Medicine {
    @Id
    @GeneratedValue
    private Long id;

    @ManyToOne
    private Facility facility;

    @NotNull
    private String description;

    @PositiveOrZero
    private Double price;

    @ManyToMany
    private List<SystemOrder> systemOrders;

    private String image;
}
