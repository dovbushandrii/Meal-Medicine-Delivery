/**
 * @file Order.java
 * @author Andrii Dovbush
 * @brief Order class for server
 * <p>
 * Part of Meal-Medicine Delivery System.
 * This file contains Order class.
 */

package cloudserver.model.entities;

import lombok.Data;

import javax.persistence.*;
import javax.validation.constraints.NotNull;
import java.time.LocalDateTime;
import java.util.List;

@Data
@Entity
public class Order {
    @Id
    @GeneratedValue
    private Long id;

    @NotNull
    private LocalDateTime dateTime;

    @NotNull
    @ManyToOne
    private Client client;

    @ManyToMany(fetch = FetchType.EAGER)
    private List<Meal> meals;

    @ManyToMany(fetch = FetchType.EAGER)
    private List<Medicine> medicines;
}
