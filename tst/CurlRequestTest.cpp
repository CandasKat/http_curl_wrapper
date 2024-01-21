//
// Created by candas on 1/19/24.
//

#include "gtest/gtest.h"
#include "../src/CurlRequest.h"


TEST(RequestTest, sendGet) {
    CurlCookies cookies;
    cookies.setCookie("freeform", "value1");
    CurlRequest request("https://httpbin.org/get", "", cookies, 10);
    const std::string header = "accept: application/json";
    request.setHeader(header);
    std::unique_ptr<CurlResponse> response = request.sendGet();
    ASSERT_EQ(response->getStatus(), 200);
    json headersObj = response->getHeaders();
    printf("body:\n%s\n", response->getBody().c_str());
    printf("headers:\n%s\n", headersObj.dump().c_str());
    ASSERT_EQ(headersObj["content-type"], "application/json");
}


TEST(RequestTest, sendHead) {
    CurlCookies cookies;
    cookies.setCookie("freeform", "value1");
    CurlRequest request("https://httpbin.org/get", "", cookies, 10);
    const std::string header = "accept: application/json";
    request.setHeader(header);
    std::unique_ptr<CurlResponse> response = request.sendHead();
    ASSERT_EQ(response->getStatus(), 200);
    json headersObj = response->getHeaders();
    printf("body:\n%s\n", response->getBody().c_str());
    printf("headers:\n%s\n", headersObj.dump().c_str());
    ASSERT_EQ(headersObj["content-type"], "application/json");
}

TEST(RequestTest, sendOptions) {
    CurlCookies cookies;
    cookies.setCookie("freeform", "value1");
    CurlRequest request("https://httpbin.org/get", "", cookies, 10);
    const std::string header = "accept: application/json";
    request.setHeader(header);
    std::unique_ptr<CurlResponse> response = request.sendOptions();
    ASSERT_EQ(response->getStatus(), 200);
    json headersObj = response->getHeaders();
    printf("body:\n%s\n", response->getBody().c_str());
    printf("headers:\n%s\n", headersObj.dump().c_str());
    ASSERT_EQ(headersObj["access-control-allow-methods"], "GET, POST, PUT, DELETE, PATCH, OPTIONS");
}

TEST(RequestTest, sendPost) {
    CurlCookies cookies;
    cookies.setCookie("freeform", "value1");
    CurlRequest request("https://httpbin.org/post", "", cookies, 10);
    const std::string header = "accept: application/json";
    request.setHeader(header);
    std::unique_ptr<CurlResponse> response = request.sendPost("hello world");
    ASSERT_EQ(response->getStatus(), 200);
    json headersObj = response->getHeaders();
    printf("body:\n%s\n", response->getBody().c_str());
    printf("headers:\n%s\n", headersObj.dump().c_str());
    ASSERT_NE(response->getBody().find("hello world"), std::string::npos);
}

TEST(RequestTest, sendPut) {
    CurlCookies cookies;
    cookies.setCookie("freeform", "value1");
    CurlRequest request("https://httpbin.org/put", "", cookies, 10);
    const std::string header = "accept: application/json";
    request.setHeader(header);
    std::unique_ptr<CurlResponse> response = request.sendPut("hello world");
    ASSERT_EQ(response->getStatus(), 200);
    json headersObj = response->getHeaders();
    printf("body:\n%s\n", response->getBody().c_str());
    printf("headers:\n%s\n", headersObj.dump().c_str());
    ASSERT_NE(response->getBody().find("hello world"), std::string::npos);
}

TEST(RequestTest, sendDelete) {
    CurlCookies cookies;
    cookies.setCookie("freeform", "value1");
    CurlRequest request("https://httpbin.org/delete", "", cookies, 10);
    const std::string header = "accept: application/json";
    request.setHeader(header);
    std::unique_ptr<CurlResponse> response = request.sendDelete();
    ASSERT_EQ(response->getStatus(), 200);
    json headersObj = response->getHeaders();
    printf("body:\n%s\n", response->getBody().c_str());
    printf("headers:\n%s\n", headersObj.dump().c_str());
}

TEST(RequestTest, sendPatch) {
    CurlCookies cookies;
    cookies.setCookie("freeform", "value1");
    CurlRequest request("https://httpbin.org/patch", "", cookies, 10);
    const std::string header = "accept: application/json";
    request.setHeader(header);
    std::unique_ptr<CurlResponse> response = request.sendPatch("hello world");
    ASSERT_EQ(response->getStatus(), 200);
    json headersObj = response->getHeaders();
    printf("body:\n%s\n", response->getBody().c_str());
    printf("headers:\n%s\n", headersObj.dump().c_str());
    ASSERT_NE(response->getBody().find("hello world"), std::string::npos);
}
