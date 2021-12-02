/**
* @file HTTPSender.h
* @author Andrii Dovbush
* @brief HTTPSender class declaration
*
* Part of Meal-Medicine Delivery System
* This file contains HTTPSender class declaration.
* HTTPSender class is needed to send and receive HTTP request/responce
*/

#ifndef _HTTP_SENDER_H_
#define _HTTP_SENDER_H_

//#define CURL_STATICLIB
#include <curl/curl.h>
#include <string>
#include "HTTPResponse.h"
#include "HTTPMethod.h"

class HTTPSender {

    static size_t getResponsetoString(void* contents, size_t size, size_t nmemb, void* userp) {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    static void curl_setMethod(CURL* curl, HTTPMethod method) {
        switch (method)
        {
        case HTTP_GET:      curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
            break;
        case HTTP_POST:     curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
            break;
        case HTTP_PUT:      curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
            break;
        case HTTP_PATCH:    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
            break;
        case HTTP_DELETE:   curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
            break;
        }
    }

    static void curl_createHTTPRequest(CURL* curl, std::string URL, HTTPMethod method) {
        curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
        curl_setMethod(curl, method);
    }

public:
    HTTPResponse* doRequest(std::string URL, HTTPMethod method) {
        CURL* curl;

        std::string str_response;
        long code = 0;

        curl = curl_easy_init();

        curl_createHTTPRequest(curl, URL, method);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, getResponsetoString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str_response);

        curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);

        curl_easy_cleanup(curl);

        HTTPResponse* response = new HTTPResponse(code, str_response);

        return response;
    }

    HTTPResponse* doMethodWithJSONBody(std::string URL, HTTPMethod method, std::string body) {
        CURL* curl;

        std::string str_response;
        long code = 0;

        curl = curl_easy_init();

        curl_createHTTPRequest(curl, URL, method);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, getResponsetoString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str_response);

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "charset: utf-8");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());

        curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);

        curl_easy_cleanup(curl);
        curl_global_cleanup();

        HTTPResponse* response = new HTTPResponse(code, str_response);

        return response;
    }
};

#endif // ! _HTTP_SENDER_H_
