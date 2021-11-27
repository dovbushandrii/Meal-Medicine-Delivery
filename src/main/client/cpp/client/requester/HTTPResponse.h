/**
* @file HTTPResponce.h
* @author Andrii Dovbush
* @brief HTTPResponce class declaration
*
* Part of Meal-Medicine Delivery System
* This file contains HTTPResponce class declaration.
*/

#ifndef _HTTP_RESPONCE_H_
#define _HTTP_RESPONCE_H_

#include <string>
#include <curl/curl.h>

class HTTPResponse {
private:

	long status;

	std::string response;

public:

	HTTPResponse(long code,
		std::string response) {
		this->status = code;
		this->response = response;
	}

	long getStatusCode() {
		return this->status;
	}

	std::string getResponse() {
		return this->response;
	}
};

#endif // !_HTTP_RESPONCE_H_
