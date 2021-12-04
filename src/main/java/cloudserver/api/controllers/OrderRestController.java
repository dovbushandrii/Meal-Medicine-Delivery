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
import cloudserver.model.entities.Facility;
import cloudserver.model.entities.SystemOrder;
import cloudserver.model.jsonparsers.ParserJSON;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

@RestController
@RequestMapping("/orders")
public class OrderRestController {

    final private OrderDAO dao;
    final private ParserJSON parser;

    @Autowired
    public OrderRestController(@Qualifier("orderDAO") OrderDAO dao,
                               @Qualifier("JSONParser") ParserJSON parser) {
        this.dao = dao;
        this.parser = parser;
    }

    @PostMapping()
    public SystemOrder saveOrder(@RequestBody String json) {
        return dao.create((SystemOrder) parser.parse(json,SystemOrder.class));
    }

    @GetMapping("/{id}")
    public SystemOrder getOrder(@PathVariable("id") Long id) {
        return dao.read(id);
    }

    @GetMapping("/ids")
    public List<Long> getOrdersID(){
        List<SystemOrder> orders = dao.read();
        return orders.stream().map(SystemOrder::getId).collect(Collectors.toList());
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
    public SystemOrder updateOrder(@RequestBody String json) {
        return dao.update((SystemOrder) parser.parse(json,SystemOrder.class));
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
