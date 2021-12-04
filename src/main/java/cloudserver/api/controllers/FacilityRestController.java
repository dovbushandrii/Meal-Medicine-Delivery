package cloudserver.api.controllers;

import cloudserver.dbfillers.DBFiller;
import cloudserver.model.daos.FacilityDAO;
import cloudserver.model.entities.Facility;
import cloudserver.model.jsonparsers.ParserJSON;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.web.bind.annotation.*;

import javax.transaction.Transactional;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

@RestController
@RequestMapping("/facilities")
public class FacilityRestController {

    private final FacilityDAO dao;
    private final ParserJSON parser;

    @Autowired
    public FacilityRestController(@Qualifier("facilityDAO") FacilityDAO dao,
                                  @Qualifier("JSONParser") ParserJSON parser,
                                  @Qualifier("DBFiller") DBFiller filler) {
        this.dao = dao;
        this.parser = parser;
        try{
            filler.resetDB();
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }

    @Transactional
    @PostMapping()
    public Facility saveFacility(@RequestBody String json) {
        return dao.create((Facility) parser.parse(json,Facility.class));
    }

    @Transactional
    @GetMapping("/{id}")
    public Facility getFacility(@PathVariable("id") Long id) {
        return dao.read(id);
    }

    @Transactional
    @GetMapping("/ids")
    public List<Long> getFacilitiesID(){
        List<Facility> facilities = dao.read();
        return facilities.stream().map(Facility::getId).collect(Collectors.toList());
    }

    @Transactional
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

    @Transactional
    @PatchMapping()
    public Facility updateFacility(@RequestBody String json) {
        return dao.update((Facility) parser.parse(json,Facility.class));
    }

    @Transactional
    @DeleteMapping("/{id}")
    public void deleteFacility(@PathVariable("id") Long id) {
        dao.delete(id);
    }

    @Transactional
    @DeleteMapping()
    public void deleteFacilities() {
        dao.delete();
    }
}
