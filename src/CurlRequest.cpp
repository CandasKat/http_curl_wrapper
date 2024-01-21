//
// Created by candas on 1/19/24.
//

#include "CurlRequest.h"

#include <utility>
#include "CurlResponse.h"
#include "curl/curl.h"

size_t CurlRequest::WriteCallBack(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t real_size = size * nmemb;
    auto *response_string = (std::string *)userp;
    response_string->append((char *)contents, real_size);
    return real_size;
}

CurlRequest::CurlRequest(std::string url, std::string header, const CurlCookies& cookies, int timeout)
{
    this->url = std::move(url);
    this->header = std::move(header);
    this->cookies = cookies;
    this->timeout = timeout;
    curl = curl_easy_init();
    if (!curl)
    {
        throw CurlException("curl_easy_init() failed");
    }
}

CurlRequest::~CurlRequest()
{
    curl_easy_cleanup(curl);
}

std::unique_ptr<CurlResponse> CurlRequest::sendGet()
{
    std::string response_string;
    std::string response_headers;
    long response_code;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &response_headers);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        throw CurlException("curl_easy_perform() failed: " + std::string(curl_easy_strerror(res)));
    }
    else
    {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        int response_code_int = static_cast<int>(response_code);
        return std::make_unique<CurlResponse>(response_code_int, response_headers, response_string);
    }
}

std::unique_ptr<CurlResponse> CurlRequest::sendHead()
{
    std::string response_string;
    std::string response_headers;
    long response_code;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
    curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &response_headers);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    CURLcode res = curl_easy_perform(curl);


    if (res != CURLE_OK)
    {
        throw CurlException("curl_easy_perform() failed: " + std::string(curl_easy_strerror(res)));
    }
    else
    {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        int response_code_int = static_cast<int>(response_code);
        return std::make_unique<CurlResponse>(response_code_int, response_headers, response_string);
    }
}

std::unique_ptr<CurlResponse> CurlRequest::sendOptions()
{
    std::string response_string;
    std::string response_headers;
    long response_code;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "OPTIONS");
    curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &response_headers);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
        throw CurlException("curl_easy_perform() failed: " + std::string(curl_easy_strerror(res)));
    }
    else
    {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        int response_code_int = static_cast<int>(response_code);
        return std::make_unique<CurlResponse>(response_code_int, response_headers, response_string);
    }
}

std::unique_ptr<CurlResponse> CurlRequest::sendPost(std::string newBody)
{
    std::string response_string;
    std::string response_headers;
    long response_code;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    if (!newBody.empty())
    {
        body = std::move(newBody);
    }
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &response_headers);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
        throw CurlException("curl_easy_perform() failed: " + std::string(curl_easy_strerror(res)));
    }
    else
    {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        int response_code_int = static_cast<int>(response_code);
        return std::make_unique<CurlResponse>(response_code_int, response_headers, response_string);
    }
}

std::unique_ptr<CurlResponse> CurlRequest::sendPut(std::string newBody)
{
    std::string response_string;
    std::string response_headers;
    long response_code;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    if (!newBody.empty())
    {
        body = std::move(newBody);
    }
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
    curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &response_headers);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
        throw CurlException("curl_easy_perform() failed: " + std::string(curl_easy_strerror(res)));
    }
    else
    {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        int response_code_int = static_cast<int>(response_code);
        return std::make_unique<CurlResponse>(response_code_int, response_headers, response_string);
    }
}

std::unique_ptr<CurlResponse> CurlRequest::sendPatch(std::string newBody)
{
    std::string response_string;
    std::string response_headers;
    long response_code;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
    if (!newBody.empty())
    {
        body = std::move(newBody);
    }
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
    curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &response_headers);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
        throw CurlException("curl_easy_perform() failed: " + std::string(curl_easy_strerror(res)));
    }
    else
    {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        int response_code_int = static_cast<int>(response_code);
        return std::make_unique<CurlResponse>(response_code_int, response_headers, response_string);
    }
}

std::unique_ptr<CurlResponse> CurlRequest::sendDelete()
{
    std::string response_string;
    std::string response_headers;
    long response_code;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
    curl_easy_setopt(curl, CURLOPT_HEADER, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &response_headers);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK)
    {
        throw CurlException("curl_easy_perform() failed: " + std::string(curl_easy_strerror(res)));
    }
    else
    {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        int response_code_int = static_cast<int>(response_code);
        return std::make_unique<CurlResponse>(response_code_int, response_headers, response_string);
    }
}

void CurlRequest::setUrl(std::string newUrl)
{
    this->url = std::move(newUrl);
}

void CurlRequest::setHeader(std::string newHeader)
{
    this->header = std::move(newHeader);
    struct curl_slist *headers = nullptr;
    headers = curl_slist_append(headers, header.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
}

void CurlRequest::setBody(std::string newBody)
{
    this->body = std::move(newBody);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
}

void CurlRequest::setBody(std::string newBody, size_t size)
{
    this->body = std::move(newBody);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, size);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
}

void CurlRequest::setTimeout(int newTimeout)
{
    this->timeout = newTimeout;
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);
}

void CurlRequest::setCookies(const CurlCookies& newCookies)
{
    this->cookies = newCookies;
    curl_easy_setopt(curl, CURLOPT_COOKIE, cookies.getCookies().dump().c_str());
}