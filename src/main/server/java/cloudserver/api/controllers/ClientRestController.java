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
import cloudserver.model.jsonparsers.ParserJSON;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;


@RestController
@RequestMapping("/clients")
public class ClientRestController {

    final private ClientDAO dao;
    final private ParserJSON parser;

    @Autowired
    public ClientRestController(@Qualifier("clientDAO") ClientDAO dao,
                                @Qualifier("JSONParser") ParserJSON parser) {
        this.dao = dao;
        this.parser = parser;
    }

    @PostMapping()
    public Client saveClient(@RequestBody String json) {
        return dao.create((Client) parser.parse(json,Client.class));
    }

    @GetMapping("/{id}")
    public Client getClient(@PathVariable("id") Long id) {
        return dao.read(id);
    }

    @GetMapping()
    public List<Client> getClients(@RequestParam(value = "limit", required = false) Optional<Long> limit,
                                   @RequestParam(value = "sort", required = false) Optional<String> sort) {
        List<Client> clients = dao.read();
        //TODO sorting
        if (limit.isPresent()) {
            clients = clients.stream()
                    .limit(limit.get())
                    .collect(Collectors.toList());
        }
        return clients;
    }

    @PatchMapping()
    public Client updateClient(@RequestBody String json) {
        return dao.update((Client) parser.parse(json,Client.class));
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