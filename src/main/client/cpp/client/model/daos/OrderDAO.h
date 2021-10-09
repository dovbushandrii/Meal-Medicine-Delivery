/**
* @file OrderDAO.h
* @author Andrii Dovbush
* @brief OrderDAO class declaration
*
* Part of Meal-Medicine Delivery System
* This file contains Order Data Access Object class declaration.
*/

#ifndef _ORDER_DAO_H_
#define _ORDER_DAO_H_

#include "../entities/Order.h"
#include <vector>

class OrderDAO {
public:

	void createOrder(Order order);

	std::vector<Order> readOrders();

	Order readOrder(long id);

	void updateOrder(Order order);

	void deleteOrder(Order order);

	void deleteOrderById(long id);

	void deleteOrders();
};


#endif // !_ORDER_DAO_H_
