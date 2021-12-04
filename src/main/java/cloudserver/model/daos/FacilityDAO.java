/**
 * @file FacilityDAO.java
 * @author Andrii Dovbush
 * @brief Facility Data Access Object
 * <p>
 * Part of Meal-Medicine Delivery System.
 * This file contains Facility Data Access Object class.
 */

package cloudserver.model.daos;

import cloudserver.model.entities.Facility;
import cloudserver.model.repos.FacilityRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.NoSuchElementException;

@Component("facilityDAO")
public class FacilityDAO {

    private FacilityRepository repo;

    @Autowired
    public FacilityDAO(FacilityRepository repo) {
        this.repo = repo;
    }

    @Transactional
    public Facility create(Facility facility) {
        return repo.save(facility);
    }

    @Transactional
    public Facility read(Long id) {
        return repo.findById(id).get();
    }

    @Transactional
    public List<Facility> read() {
        return repo.findAll();
    }

    public Facility upsert(Facility facility) {
        repo.deleteById(facility.getId());
        return repo.save(facility);
    }

    public Facility update(Facility facility) {
        if (repo.findById(facility.getId()).isPresent()) {
            repo.deleteById(facility.getId());
            return repo.save(facility);
        }
        throw new NoSuchElementException("There is no Facility with ID: " + facility.getId());
    }

    public void delete(Long id) {
        repo.deleteById(id);
    }

    public void delete() {
        repo.deleteAll();
    }
}
