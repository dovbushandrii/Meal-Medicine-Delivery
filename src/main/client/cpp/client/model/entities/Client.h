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

class Client {

    long id;

	//Must be up to 30 characters
	std::string name;

	//Must be up to 30 characters
	std::string surname;

	//Must contain country code
	std::string phoneNumber;

	std::string email;

public:

	Client() {}

	Client(	long getId();
	        std::string name,
			std::string surname,
			std::string phoneNumber,
			std::string email,
			std::string password) {

		this->name = name;
		this->surname = surname;
		this->phoneNumber = phoneNumber;
		this->email = email;
		this->password = password;
	}

    long getId();

	std::string getName();
	void setName(std::string name);

	std::string getSurname();
	void setSurname(std::string surname);

	std::string getPhoneNumber();
	void setPhoneNumber(std::string phoneNumber);

	std::string getEmail();
	void setEmail(std::string email);
};

#endif // !_CLIENT_H_
