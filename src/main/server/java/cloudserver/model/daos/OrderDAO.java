/**
 * @file OrderDAO.java
 * @author Andrii Dovbush
 * @brief Order Data Access Object
 * <p>
 * Part of Meal-Medicine Delivery System.
 * This file contains Order Data Access Object class.
 */

package cloudserver.model.daos;

import cloudserver.model.entities.SystemOrder;
import cloudserver.model.repos.OrderRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.List;
import java.util.NoSuchElementException;

@Component("orderDAO")
public class OrderDAO {

    private OrderRepository repo;

    @Autowired
    public OrderDAO(OrderRepository repo) {
        this.repo = repo;
    }

    public SystemOrder create(SystemOrder systemOrder) {
        return repo.save(systemOrder);
    }

    public SystemOrder read(Long id) {
        return repo.findById(id).get();
    }

    public List<SystemOrder> read() {
        return repo.findAll();
    }

    public SystemOrder upsert(SystemOrder systemOrder) {
        repo.deleteById(systemOrder.getId());
        return repo.save(systemOrder);
    }

    public SystemOrder update(SystemOrder systemOrder) {
        if (repo.findById(systemOrder.getId()).isPresent()) {
            repo.deleteById(systemOrder.getId());
            return repo.save(systemOrder);
        }
        throw new NoSuchElementException("There is no Order with ID: " + systemOrder.getId());
    }

    public void delete(Long id) {
        repo.deleteById(id);
    }

    public void delete() {
        repo.deleteAll();
    }
}
