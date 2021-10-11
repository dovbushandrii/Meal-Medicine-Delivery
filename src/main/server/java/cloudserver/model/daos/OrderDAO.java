/**
 * @file OrderDAO.java
 * @author Andrii Dovbush
 * @brief Order Data Access Object
 * <p>
 * Part of Meal-Medicine Delivery System.
 * This file contains Order Data Access Object class.
 */

package cloudserver.model.daos;

import cloudserver.model.entities.Order;
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

    public Order create(Order order) {
        return repo.save(order);
    }

    public Order read(Long id) {
        return repo.findById(id).get();
    }

    public List<Order> read() {
        return repo.findAll();
    }

    public Order upsert(Order order) {
        repo.deleteById(order.getId());
        return repo.save(order);
    }

    public Order update(Order order) {
        if (repo.findById(order.getId()).isPresent()) {
            repo.deleteById(order.getId());
            return repo.save(order);
        }
        throw new NoSuchElementException("There is no Client with ID: " + order.getId());
    }

    public void delete(Long id) {
        repo.deleteById(id);
    }

    public void delete() {
        repo.deleteAll();
    }
}
