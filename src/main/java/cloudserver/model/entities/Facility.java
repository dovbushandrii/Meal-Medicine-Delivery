/**
 * @file Facility.java
 * @author Andrii Dovbush
 * @brief Facility class for server
 * <p>
 * Part of Meal-Medicine Delivery System.
 * This file contains Facility class.
 */

package cloudserver.model.entities;

import lombok.Data;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.OneToMany;
import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;
import java.util.List;

@Data
@Entity
public class Facility {
    @Id
    @GeneratedValue
    private Long id;

    @NotNull
    @NotBlank
    private String name;

    @NotNull
    @Size(min = 9, max = 13, message = "Number must be valid")
    private String phoneNumber;

    @OneToMany
    private List<Meal> mealList;

    @OneToMany
    private List<Medicine> medicineList;
}
