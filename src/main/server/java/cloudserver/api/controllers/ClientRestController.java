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
import cloudserver.model.entities.Client;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.web.bind.annotation.*;

import java.util.List;


@RestController
@RequestMapping("/clients")
public class ClientRestController {

    private ClientDAO dao;

    @Autowired
    public ClientRestController(@Qualifier("clientDAO") ClientDAO dao) {
        this.dao = dao;
    }

    @PostMapping()
    public Client saveClient(Client client) {
        return dao.create(client);
    }

    @GetMapping("/{id}")
    public Client getClient(@PathVariable("id") Long id) {
        return dao.read(id);
    }

    @GetMapping()
    public List<Client> getClients() {
        return dao.read();
    }

    @PatchMapping()
    public Client updateClient(Client client) {
        return dao.update(client);
    }

    @PatchMapping("/upsert")
    public Client upsertClient(Client client) {
        return dao.upsert(client);
    }

    @DeleteMapping("/{id}")
    public void deleteClient(@PathVariable("id") Long id) {
        dao.delete(id);
    }

    @DeleteMapping()
    public void deleteClients() {
        dao.delete();
    }
}