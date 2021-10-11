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
import cloudserver.model.entities.Order;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
public class OrderRestController {

    private OrderDAO dao;

    @Autowired
    public OrderRestController(@Qualifier("orderDAO") OrderDAO dao) {
        this.dao = dao;
    }

    @PostMapping()
    public Order saveOrder(Order order) {
        return dao.create(order);
    }

    @GetMapping("/{id}")
    public Order getOrder(@PathVariable("id") Long id) {
        return dao.read(id);
    }

    @GetMapping()
    public List<Order> getOrders() {
        return dao.read();
    }

    @PatchMapping()
    public Order updateOrder(Order order) {
        return dao.update(order);
    }

    @PatchMapping("/upsert")
    public Order upsertOrder(Order order) {
        return dao.upsert(order);
    }

    @DeleteMapping("/{id}")
    public void deleteOrder(@PathVariable("id") Long id) {
        dao.delete(id);
    }

    @DeleteMapping()
    public void deleteOrder() {
        dao.delete();
    }
}
