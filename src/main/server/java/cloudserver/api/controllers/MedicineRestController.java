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
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class MedicineRestController {

    private MedicineDAO dao;

    @Autowired
    public MedicineRestController(@Qualifier("medicineDAO") MedicineDAO dao) {
        this.dao = dao;
    }
}
