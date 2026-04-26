//
// Created by moinshaikh on 4/26/26.
//

#ifndef ARCHITECTURESINC___STATELESSARCHITECTURE_HPP
#define ARCHITECTURESINC___STATELESSARCHITECTURE_HPP
#include<string>
#include<drogon/drogon.h>
#include<drogon/HttpController.h>
#include<drogon/HttpRequest.h>
#include<drogon/HttpResponse.h>

#include<jsoncpp/json/json.h>
using namespace drogon;

class ProductController : public drogon::HttpController<ProductController>
{
public:
    METHOD_LIST_BEGIN
       ADD_METHOD_TO(ProductController::getProducts,  "/api/products",      drogon::Get);
    ADD_METHOD_TO(ProductController::getProduct,   "/api/products/{id}", drogon::Get);
    ADD_METHOD_TO(ProductController::createProduct,"/api/products",      drogon::Post);
    METHOD_LIST_END

    void getProducts (const HttpRequestPtr& req,
                      std::function<void(const HttpResponsePtr&)>&& cb) const;

    void getProduct  (const HttpRequestPtr& req,
                      std::function<void(const HttpResponsePtr&)>&& cb,
                      int id) const;

    void createProduct(const HttpRequestPtr& req,
                       std::function<void(const HttpResponsePtr&)>&& cb) const;

private:
    std::string extractUserId(const HttpRequestPtr& req) const;
};


#endif //ARCHITECTURESINC___STATELESSARCHITECTURE_HPP
