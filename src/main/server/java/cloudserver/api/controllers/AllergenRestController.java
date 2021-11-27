package cloudserver.api.controllers;

import cloudserver.model.daos.AllergenDAO;
import cloudserver.model.entities.Allergen;
import cloudserver.model.jsonparsers.ParserJSON;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

@RestController
@RequestMapping("/allergens")
public class AllergenRestController {

    final private AllergenDAO dao;
    final private ParserJSON parser;

    @Autowired
    public AllergenRestController(@Qualifier("allergenDAO") AllergenDAO dao,
                                @Qualifier("JSONParser") ParserJSON parser) {
        this.dao = dao;
        this.parser = parser;
    }

    @PostMapping()
    public Allergen saveAllergen(@RequestBody String json) {
        System.out.println(json);
        return dao.create((Allergen) parser.parse(json, Allergen.class));
    }

    @GetMapping()
    public List<Allergen> getAllergens(@RequestParam(value = "limit", required = false) Optional<Long> limit,
                                   @RequestParam(value = "sort", required = false) Optional<String> sort) {
        List<Allergen> allergens = dao.read();
        //TODO sorting
        if (limit.isPresent()) {
            allergens = allergens.stream()
                    .limit(limit.get())
                    .collect(Collectors.toList());
        }

        return allergens;
    }


    @GetMapping("/{id}")
    public Allergen getAllergen(@PathVariable("id") Long id) {
        return dao.read(id);
    }
}
