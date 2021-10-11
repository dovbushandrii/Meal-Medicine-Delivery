/**
 * @file ClientDAO.java
 * @author Andrii Dovbush
 * @brief Client Data Access Object
 * <p>
 * Part of Meal-Medicine Delivery System.
 * This file contains Client Data Access Object class.
 */

package cloudserver.model.daos;

import cloudserver.model.entities.Client;
import cloudserver.model.repos.ClientRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.List;
import java.util.NoSuchElementException;

@Component("clientDAO")
public class ClientDAO {

    private ClientRepository repo;

    @Autowired
    public ClientDAO(ClientRepository repo) {
        this.repo = repo;
    }

    public Client create(Client client) {
        return repo.save(client);
    }

    public Client read(Long id) {
        return repo.findById(id).get();
    }

    public List<Client> read() {
        return repo.findAll();
    }

    public Client upsert(Client client) {
        repo.deleteById(client.getId());
        return repo.save(client);
    }

    public Client update(Client client) {
        if (repo.findById(client.getId()).isPresent()) {
            repo.deleteById(client.getId());
            return repo.save(client);
        }
        throw new NoSuchElementException("There is no Client with ID: " + client.getId());
    }

    public void delete(Long id) {
        repo.deleteById(id);
    }

    public void delete() {
        repo.deleteAll();
    }


}
