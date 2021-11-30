/**
* @file ClientDAO.h
* @author Andrii Dovbush
* @brief ClientDAO class declaration
*
* Part of Meal-Medicine Delivery System
* This file contains Client Data Access Object class declaration.
*/

#ifndef _CLIENT_DAO_H_
#define _CLIENT_DAO_H_

#include "ServerURLs.h"
#include "ClientJSONSerializer.h"
#include "HTTPSender.h"
#include <vector>

class ClientDAO {
public:
	//DONE
	bool createClient(Client client) {
		nlohmann::json  j{};
		to_json(j, client);
		std::string json = j.dump();

		HTTPSender send;
		HTTPResponse* response = send.doMethodWithJSONBody(CLIENTS_URL, HTTPMethod::HTTP_POST, json);
		bool returns = response->getStatusCode() == 200;

		delete response;
		return returns;
	}

	//DONE
	std::vector<Client> readClients() {
		HTTPSender send;
		HTTPResponse * response = send.doRequest(CLIENTS_URL, HTTPMethod::HTTP_GET);
		std::vector<Client> clients;

		if (response->getStatusCode() == 200) {
			nlohmann::json  j = nlohmann::json::parse(response->getResponse());
			j.get_to<std::vector<Client>>(clients);
		}

		delete response;
		return clients;
	}

	//DONE
	Client* readClient(long id) {
		std::string URL = CLIENTS_URL"/" + std::to_string(id);

		HTTPSender send;
		HTTPResponse* response = send.doRequest(URL, HTTPMethod::HTTP_GET);

		if (response->getStatusCode() == 200) {
			Client* client = new Client();
			nlohmann::json  j = nlohmann::json::parse(response->getResponse());
			*client = j.get<Client>();
			delete response;
			return client;
		}

		delete response;
		return nullptr;
	}

	//DONE
	bool updateClient(Client client) {
		nlohmann::json  j{};
		to_json(j, client);
		std::string json = j.dump();

		HTTPSender send;
		HTTPResponse* response = send.doMethodWithJSONBody(CLIENTS_URL, HTTPMethod::HTTP_PATCH, json);
		bool returns = response->getStatusCode() == 200;

		delete response;
		return returns;
	}

	//DONE
	void deleteClient(Client client) {
		this->deleteClientById(client.getId());
	}

	//DONE
	void deleteClientById(long id) {
		std::string URL = CLIENTS_URL"/" + std::to_string(id);

		HTTPSender send;
        send.doRequest(URL, HTTPMethod::HTTP_DELETE);
	}

	//DONE
	void deleteClients() {
		HTTPSender send;
        send.doRequest(CLIENTS_URL, HTTPMethod::HTTP_DELETE);
	}
};



#endif // !_CLIENT_DAO_H_
