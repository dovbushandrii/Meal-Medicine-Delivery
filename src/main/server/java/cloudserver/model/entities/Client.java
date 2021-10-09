/**
 * @file Client.java
 * @author Andrii Dovbush
 * @brief Client class for server
 * <p>
 * Part of Meal-Medicine Delivery System.
 * This file contains Client class.
 */

package cloudserver.model.entities;

import lombok.Data;

import javax.persistence.*;
import javax.validation.constraints.Email;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;
import java.util.List;

@Data
@Entity
public class Client {
    @Id
    @GeneratedValue
    private Long id;

    @NotNull
    @Size(max = 30, message = "Name must be up to 30 characters")
    private String name;

    @NotNull
    @Size(max = 30, message = "Surname must be up to 30 characters")
    private String surname;

    @NotNull
    @Size(min = 9, max = 13, message = "Number must be valid")
    private String phoneNumber;

    @Email(message = "Email should be valid")
    private String email;

    @OneToMany(fetch = FetchType.LAZY)
    private List<Order> orders;
}
