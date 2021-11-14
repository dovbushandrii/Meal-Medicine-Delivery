package cloudserver.api.controllers;

import cloudserver.model.daos.FacilityDAO;
import cloudserver.model.entities.Facility;
import cloudserver.model.jsonparsers.ParserJSON;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

@RestController
@RequestMapping("/facilities")
public class FacilityRestController {

    final private FacilityDAO dao;
    final private ParserJSON parser;

    @Autowired
    public FacilityRestController(@Qualifier("facilityDAO") FacilityDAO dao,
                                  @Qualifier("JSONParser") ParserJSON parser) {
        this.dao = dao;
        this.parser = parser;
    }

    @PostMapping()
    public Facility saveFacility(@RequestBody String json) {
        return dao.create((Facility) parser.parse(json,Facility.class));
    }

    @GetMapping("/{id}")
    public Facility getFacility(@PathVariable("id") Long id) {
        return dao.read(id);
    }

    @GetMapping()
    public List<Facility> getFacilities(@RequestParam(value = "limit", required = false) Optional<Long> limit,
                                        @RequestParam(value = "sort", required = false) Optional<String> sort) {
        List<Facility> facilities = dao.read();
        //TODO sorting
        if (limit.isPresent()) {
            facilities = facilities.stream()
                    .limit(limit.get())
                    .collect(Collectors.toList());
        }
        return facilities;
    }

    @PatchMapping()
    public Facility updateFacility(@RequestBody String json) {
        return dao.update((Facility) parser.parse(json,Facility.class));
    }

    @DeleteMapping("/{id}")
    public void deleteFacility(@PathVariable("id") Long id) {
        dao.delete(id);
    }

    @DeleteMapping()
    public void deleteFacilities() {
        dao.delete();
    }
}
