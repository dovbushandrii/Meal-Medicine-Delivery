/**
 * @file MedicineDAO.java
 * @author Andrii Dovbush
 * @brief Medicine Data Access Object
 * <p>
 * Part of Meal-Medicine Delivery System.
 * This file contains Medicine Data Access Object class.
 */

package cloudserver.model.daos;

import cloudserver.model.entities.Medicine;
import cloudserver.model.repos.MedicineRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import org.springframework.transaction.annotation.Transactional;

import java.util.List;
import java.util.NoSuchElementException;

@Component("medicineDAO")
public class MedicineDAO {

    private MedicineRepository repo;

    @Autowired
    public MedicineDAO(MedicineRepository repo) {
        this.repo = repo;
    }

    @Transactional
    public Medicine create(Medicine medicine) {
        return repo.save(medicine);
    }

    @Transactional
    public Medicine read(Long id) {
        return repo.findById(id).get();
    }

    @Transactional
    public List<Medicine> read() {
        return repo.findAll();
    }

    public Medicine upsert(Medicine medicine) {
        repo.deleteById(medicine.getId());
        return repo.save(medicine);
    }

    public Medicine update(Medicine medicine) {
        if (repo.findById(medicine.getId()).isPresent()) {
            repo.deleteById(medicine.getId());
            return repo.save(medicine);
        }
        throw new NoSuchElementException("There is no Medicine with ID: " + medicine.getId());
    }

    public void delete(Long id) {
        repo.deleteById(id);
    }

    public void delete() {
        repo.deleteAll();
    }
}
