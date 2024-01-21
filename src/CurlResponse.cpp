//
// Created by candas on 1/19/24.
//

#include "CurlResponse.h"

#include <utility>
#include <iostream>

CurlResponse::CurlResponse(int status, const std::string& headers, std::string body)
{
    this->status = status;
    this->headers = headers;
    this->body = std::move(body);
}

int CurlResponse::getStatus() const {
    return status;
}

json CurlResponse::getHeaders()
{
    std::string toParse = setHeadersToParse(headers);
    try
    {
        json headersToReturn = json::parse(toParse);
        return headersToReturn;
    }
    catch (json::parse_error &e)
    {
        throw std::runtime_error("Failed to parse headers: " + std::string(e.what()));
    }
}

const std::string &CurlResponse::getHeadersString()
{
    return headers;
}

const std::string &CurlResponse::getBody()
{
    return body;
}

std::string CurlResponse::setHeadersToParse(const std::string& headersToParse)
{
    std::istringstream responseStream(headersToParse);
    std::string line;
    json toJsonHeaders;
    const char badChar = '\r';
    while (std::getline(responseStream, line)) {
        size_t separator = line.find(':');
        if (separator != std::string::npos) {
            std::string key = line.substr(0, separator);
            if (key.back() == badChar) {
                key.pop_back();
            }
            std::string value = line.substr(separator + 1, line.length() - separator - 1);
            if (value.front() == ' ') {
                value.erase(0, 1);
            }
            if (value.back() == badChar) {
                value.pop_back();
            }
            toJsonHeaders[key] = value;
        }
    }
    return toJsonHeaders.dump();
}