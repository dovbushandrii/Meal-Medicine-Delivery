package cloudserver.api.controllers;

import cloudserver.model.daos.FacilityDAO;
import cloudserver.model.entities.Facility;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

@RestController
@RequestMapping("/facilities")
public class FacilityRestController {

    private FacilityDAO dao;

    @Autowired
    public FacilityRestController(@Qualifier("facilityDAO") FacilityDAO dao) {
        this.dao = dao;
    }

    @PostMapping()
    public Facility saveFacility(Facility meal) {
        return dao.create(meal);
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
    public Facility updateFacility(Facility facility) {
        return dao.update(facility);
    }

    @PatchMapping("/upsert")
    public Facility upsertFacility(Facility facility) {
        return dao.upsert(facility);
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
