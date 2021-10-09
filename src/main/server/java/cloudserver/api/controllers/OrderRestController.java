/**
 * @file OrderRestController.java
 * @author Andrii Dovbush
 * @brief REST Controller for Order objects
 * <p>
 * Part of Meal-Medicine Delivery System.
 * This file contains REST Controller for Order objects.
 */

package cloudserver.api.controllers;

import cloudserver.model.daos.OrderDAO;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class OrderRestController {

    private OrderDAO dao;

    @Autowired
    public OrderRestController(@Qualifier("orderDAO") OrderDAO dao) {
        this.dao = dao;
    }
}
