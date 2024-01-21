//
// Created by candas on 1/19/24.
//

#include "gtest/gtest.h"
#include "../src/CurlRequest.h"


TEST(RequestTest, sendGet) {
    CurlCookies cookies;
    cookies.setCookie("freeform", "value1");
    CurlRequest request("https://httpbin.org/get", "", cookies, "", 10);
    const std::string header = "accept: application/json";
    request.setHeader(header);
    std::unique_ptr<CurlResponse> response = request.sendGet();
    ASSERT_EQ(response->getStatus(), 200);
    json headersObj = response->getHeaders();
    printf("body:\n%s\n", response->getBody().c_str());
    printf("headers:\n%s\n", headersObj.dump().c_str());
    ASSERT_EQ(headersObj["content-type"], "application/json");
}


//TEST(RequestTest, sendHead)
//{
//    CurlRequest request("https://httpbin.org/get", "HEAD", "accept: application/json", "", 10);
//    std::unique_ptr<CurlResponse> response = request.sendHead();
//    ASSERT_EQ(response->getStatus(), 200);
//    json headersObj = response->getHeaders();
//    printf("body:\n%s\n", response->getBody().c_str());
//    printf("headers:\n%s\n", headersObj.dump().c_str());
//    ASSERT_EQ(headersObj["content-type"], "application/json");
//}
//
//TEST(RequestTest, sendOptions)
//{
//    CurlRequest request("https://httpbin.org/get", "OPTIONS", "accept: application/json", "", 10);
//    std::unique_ptr<CurlResponse> response = request.sendOptions();
//    ASSERT_EQ(response->getStatus(), 200);
//    json headersObj = response->getHeaders();
//    printf("body:\n%s\n", response->getBody().c_str());
//    printf("headers:\n%s\n", headersObj.dump().c_str());
//    ASSERT_EQ(headersObj["content-type"], "application/json");
//}
//
//TEST(RequestTest, sendPost)
//{
//    CurlRequest request("https://httpbin.org/post", "POST", "accept: application/json", "hello world", 10);
//    std::unique_ptr<CurlResponse> response = request.sendPost();
//    ASSERT_EQ(response->getStatus(), 200);
//    json headersObj = response->getHeaders();
//    printf("body:\n%s\n", response->getBody().c_str());
//    printf("headers:\n%s\n", headersObj.dump().c_str());
//    ASSERT_NE(response->getBody().find("hello world"), std::string::npos);
//}
//
//TEST(RequestTest, sendPut)
//{
//    CurlRequest request("https://httpbin.org/put", "PUT", "accept: application/json", "hello world", 10);
//    std::unique_ptr<CurlResponse> response = request.sendPut();
//    ASSERT_EQ(response->getStatus(), 200);
//    json headersObj = response->getHeaders();
//    printf("body:\n%s\n", response->getBody().c_str());
//    printf("headers:\n%s\n", headersObj.dump().c_str());
//    ASSERT_NE(response->getBody().find("hello world"), std::string::npos);
//}
//
//TEST(RequestTest, sendDelete)
//{
//    CurlRequest request("https://httpbin.org/delete", "DELETE", "accept: application/json", "", 10);
//    std::unique_ptr<CurlResponse> response = request.sendDelete();
//    ASSERT_EQ(response->getStatus(), 200);
//    json headersObj = response->getHeaders();
//    printf("body:\n%s\n", response->getBody().c_str());
//    printf("headers:\n%s\n", headersObj.dump().c_str());
//}
//
//TEST(RequestTest, sendPatch)
//{
//    CurlRequest request("https://httpbin.org/patch", "PATCH", "accept: application/json", "hello world", 10);
//    std::unique_ptr<CurlResponse> response = request.sendPatch();
//    ASSERT_EQ(response->getStatus(), 200);
//    json headersObj = response->getHeaders();
//    printf("body:\n%s\n", response->getBody().c_str());
//    printf("headers:\n%s\n", headersObj.dump().c_str());
//    ASSERT_NE(response->getBody().find("hello world"), std::string::npos);
//}