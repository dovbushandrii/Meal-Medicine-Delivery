/**
* @file Client.h
* @author Andrii Dovbush
* @brief Client class declaration
*
* Part of Meal-Medicine Delivery System
* This file contains Client class declaration.
*/

#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <string>
#include <vector>
#include "Alergen.h"

class Client {

    long id;

	//Must be up to 30 characters
	std::string name;

	//Must be up to 30 characters
	std::string surname;

	//Must contain country code
	std::string phoneNumber;

	std::string email;

	std::vector<Alergen> alergens;

public:

	Client() {}

	Client(	long getId();
	        std::string name,
			std::string surname,
			std::string phoneNumber,
			std::string email,
			std::string password,
			std::vector<Alergen> alergens) {

		this->name = name;
		this->surname = surname;
		this->phoneNumber = phoneNumber;
		this->email = email;
		this->password = password;
		this->alergens = alergens;
	}

    long getId();

	std::string getName() {
		return this->name;
	}
	void setName(std::string name) {
		this->name = name;
	}

	std::string getSurname() {
		return this->surname
	}
	void setSurname(std::string surname) {
		this->surname = surname;
	}

	std::string getPhoneNumber() {
		return this->phoneNumber;
	}
	void setPhoneNumber(std::string phoneNumber) {
		this->phoneNumber = phoneNumber;
	}

	std::string getEmail() {
		return this->email;
	}
	void setEmail(std::string email) {
		this->email = email;
	}

	std::vector<Alergen> getAlergens() {
		return this->alergens;
	}
	void setAlergens(std::vector<Alergen> alergens) {
		this->alergens = alergens;
	}
};

#endif // !_CLIENT_H_
