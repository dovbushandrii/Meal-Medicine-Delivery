/**
 * @file ClientRestController.java
 * @author Andrii Dovbush
 * @brief REST Controller for Client objects
 * <p>
 * Part of Meal-Medicine Delivery System.
 * This file contains REST Controller for Client objects.
 */

package cloudserver.api.controllers;

import cloudserver.model.daos.ClientDAO;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class ClientRestController {

    private ClientDAO dao;

    @Autowired
    public ClientRestController(@Qualifier("clientDAO") ClientDAO dao) {
        this.dao = dao;
    }
}