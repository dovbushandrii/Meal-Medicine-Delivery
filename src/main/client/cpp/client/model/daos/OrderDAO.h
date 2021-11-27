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

#include "ServerURLs.h"
#include "OrderJSONSerializer.h"
#include "HTTPSender.h"
#include <vector>

class OrderDAO {
public:

	//DONE
	bool createOrder(Order order) {
		nlohmann::json  j{};
		to_json(j, order);
		std::string json = j.dump();

		HTTPSender send;
		HTTPResponse* response = send.doMethodWithJSONBody(ORDERS_URL, HTTPMethod::HTTP_POST, json);
		bool returns = response->getStatusCode() == 200;

		delete response;
		return returns;
	}

	//DONE
	std::vector<Order> readOrders() {
		HTTPSender send;
		HTTPResponse* response = send.doRequest(ORDERS_URL, HTTPMethod::HTTP_GET);
		std::vector<Order> orders;

		if (response->getStatusCode() == 200) {
			nlohmann::json  j = nlohmann::json::parse(response->getResponse());
			j.get_to<std::vector<Order>>(orders);
		}

		delete response;
		return orders;
	}

	//DONE
	Order* readOrder(long id) {
		std::string URL = ORDERS_URL"/" + std::to_string(id);

		HTTPSender send;
		HTTPResponse* response = send.doRequest(URL, HTTPMethod::HTTP_GET);

		if (response->getStatusCode() == 200) {
			Order* order = new Order();
			nlohmann::json  j = nlohmann::json::parse(response->getResponse());
			*order = j.get<Order>();
			delete response;
			return order;
		}

		delete response;
		return nullptr;
	}

	//DONE
	bool updateOrder(Order order) {
		nlohmann::json  j{};
		to_json(j, order);
		std::string json = j.dump();

		HTTPSender send;
		HTTPResponse* response = send.doMethodWithJSONBody(ORDERS_URL, HTTPMethod::HTTP_PATCH, json);
		bool returns = response->getStatusCode() == 200;

		delete response;
		return returns;
	}

	//DONE
	void deleteOrder(Order order) {
		this->deleteOrderById(order.getId());
	}

	//DONE
	void deleteOrderById(long id) {
		std::string URL = ORDERS_URL"/" + std::to_string(id);

		HTTPSender send;
		HTTPResponse* response = send.doRequest(URL, HTTPMethod::HTTP_DELETE);
	}

	//DONE
	void deleteOrders() {
		HTTPSender send;
		HTTPResponse* response = send.doRequest(ORDERS_URL, HTTPMethod::HTTP_DELETE);
		bool returns = response->getStatusCode() == 200;
	}
};


#endif // !_ORDER_DAO_H_
