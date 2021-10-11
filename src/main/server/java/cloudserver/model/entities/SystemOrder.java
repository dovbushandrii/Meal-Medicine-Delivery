/**
 * @file SystemOrder.java
 * @author Andrii Dovbush
 * @brief Order class for server
 * <p>
 * Part of Meal-Medicine Delivery System.
 * This file contains SystemOrder class.
 */

package cloudserver.model.entities;

import lombok.Data;

import javax.persistence.*;
import javax.validation.constraints.NotNull;
import java.time.LocalDateTime;
import java.util.List;

@Data
@Entity
public class SystemOrder {
    @Id
    @GeneratedValue
    private Long id;

    @NotNull
    private LocalDateTime dateTime;

    @NotNull
    @ManyToOne
    private Client client;

    @ManyToMany
    private List<Meal> meals;

    @ManyToMany
    private List<Medicine> medicines;
}
