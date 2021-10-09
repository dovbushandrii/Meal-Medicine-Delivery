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

#include "../entities/Client.h"
#include <vector>

class ClientDAO {
public:

	void createClient(Client client);

	std::vector<Client> readClients();

	Client readClient(long id);

	void updateClient(Client client);

	void deleteClient(Client client);

	void deleteClientById(long id);

	void deleteClients();
};



#endif // !_CLIENT_DAO_H_
