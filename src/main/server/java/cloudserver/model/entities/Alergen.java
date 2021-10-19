package cloudserver.model.entities;

import lombok.Data;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.validation.constraints.NotBlank;
import javax.validation.constraints.NotNull;

@Data
@Entity
public class Alergen {
    @Id
    @GeneratedValue
    private Long id;

    @NotNull
    @NotBlank
    private String name;
}
