package cloudserver.api.controllers;

import cloudserver.model.daos.FacilityDAO;
import cloudserver.model.entities.Facility;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.web.bind.annotation.*;

import java.util.List;

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
    public List<Facility> getFacilities() {
        return dao.read();
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
