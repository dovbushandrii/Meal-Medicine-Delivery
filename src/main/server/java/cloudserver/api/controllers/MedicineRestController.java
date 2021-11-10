/**
 * @file MedicineRestController.java
 * @author Andrii Dovbush
 * @brief REST Controller for Medicine objects
 * <p>
 * Part of Meal-Medicine Delivery System.
 * This file contains REST Controller for Medicine objects.
 */

package cloudserver.api.controllers;

import cloudserver.model.daos.MedicineDAO;
import cloudserver.model.entities.Meal;
import cloudserver.model.entities.Medicine;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

@RestController
@RequestMapping("/medicines")
public class MedicineRestController {

    private MedicineDAO dao;

    @Autowired
    public MedicineRestController(@Qualifier("medicineDAO") MedicineDAO dao) {
        this.dao = dao;
    }

    @PostMapping()
    public Medicine saveMedicine(Medicine medicine) {
        return dao.create(medicine);
    }

    @GetMapping("/{id}")
    public Medicine getMedicine(@PathVariable("id") Long id) {
        return dao.read(id);
    }

    @GetMapping()
    public List<Medicine> getMedicines(@RequestParam(value = "limit", required = false) Optional<Long> limit,
                                       @RequestParam(value = "sort", required = false) Optional<String> sort) {
        List<Medicine> medicines = dao.read();
        //TODO sorting
        if (limit.isPresent()) {
            medicines = medicines.stream()
                    .limit(limit.get())
                    .collect(Collectors.toList());
        }
        return medicines;
    }

    @PatchMapping()
    public Medicine updateMedicine(Medicine medicine) {
        return dao.update(medicine);
    }

    @PatchMapping("/upsert")
    public Medicine upsertMedicine(Medicine medicine) {
        return dao.upsert(medicine);
    }

    @DeleteMapping("/{id}")
    public void deleteMedicine(@PathVariable("id") Long id) {
        dao.delete(id);
    }

    @DeleteMapping()
    public void deleteMedicine() {
        dao.delete();
    }
}
