//
// Created by moinshaikh on 4/25/26.
//

#include<drogon/drogon.h>
#include<drogon/HttpController.h>
#include<drogon/HttpRequest.h>
#include<drogon/HttpResponse.h>
#include<drogon/Session.h>
#include<functional>
#include<atomic>
#include<jsoncpp/json/json.h>
#ifndef ARCHITECTURESINC___STATEFULARCHITECTURE_H
#define ARCHITECTURESINC___STATEFULARCHITECTURE_H

class CartController : public drogon::HttpController<CartController>
{
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(CartController::getCart,    "/api/cart",         drogon::Get);
    ADD_METHOD_TO(CartController::addItem,    "/api/cart/items",   drogon::Post);
    ADD_METHOD_TO(CartController::removeItem, "/api/cart/items/{productId}", drogon::Delete);
    ADD_METHOD_TO(CartController::clearCart,  "/api/cart",         drogon::Delete);
    METHOD_LIST_END

    void getCart(const drogon::HttpRequestPtr& req,
                std::function<void(const drogon::HttpResponsePtr&)>&& cb);

    void addItem(const drogon::HttpRequestPtr& req,
                    std::function<void(const drogon::HttpResponsePtr&)>&& cb);

    void removeItem(const drogon::HttpRequestPtr& req,
                    std::function<void(const drogon::HttpResponsePtr&)>&& cb,
                    int productId);

    void clearCart(const drogon::HttpRequestPtr& req,
                    std::function<void(const drogon::HttpResponsePtr&)>&& cb);
private:
    Json::Value getCartFromSession(const drogon::SessionPtr &session) const;

};


#endif //ARCHITECTURESINC___STATEFULARCHITECTURE_H
