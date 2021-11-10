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
import cloudserver.model.entities.Medicine;
import cloudserver.model.entities.SystemOrder;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

@RestController
@RequestMapping("/orders")
public class OrderRestController {

    private OrderDAO dao;

    @Autowired
    public OrderRestController(@Qualifier("orderDAO") OrderDAO dao) {
        this.dao = dao;
    }

    @PostMapping()
    public SystemOrder saveOrder(SystemOrder systemOrder) {
        return dao.create(systemOrder);
    }

    @GetMapping("/{id}")
    public SystemOrder getOrder(@PathVariable("id") Long id) {
        return dao.read(id);
    }

    @GetMapping()
    public List<SystemOrder> getOrders(@RequestParam(value = "limit", required = false) Optional<Long> limit,
                                       @RequestParam(value = "sort", required = false) Optional<String> sort) {
        List<SystemOrder> orders = dao.read();
        //TODO sorting
        if (limit.isPresent()) {
            orders = orders.stream()
                    .limit(limit.get())
                    .collect(Collectors.toList());
        }
        return orders;
    }

    @PatchMapping()
    public SystemOrder updateOrder(SystemOrder systemOrder) {
        return dao.update(systemOrder);
    }

    @PatchMapping("/upsert")
    public SystemOrder upsertOrder(SystemOrder systemOrder) {
        return dao.upsert(systemOrder);
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
