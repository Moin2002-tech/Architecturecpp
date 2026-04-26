//
// Created by moinshaikh on 4/26/26.
//

#include<json/json.h>
#include"../../include/StatefulArchitectureAndStateLessArchitecture/StatefulArchitecture.h"

using namespace drogon;
Json::Value CartController::getCartFromSession(const drogon::SessionPtr &session) const
{
    // Session stores arbitrary any-typed values keyed by string.
    // We retrieve the cart JSON, or return an empty array if not set yet.
    try {
        auto val = session->get<Json::Value>("cart");
        // Extra guard: only trust it if it's actually an array
        if (val.isArray()) return val;
        return Json::Value(Json::arrayValue);
    } catch (...)
    {
        // Key absent or wrong type — return a fresh empty array
        return Json::Value(Json::arrayValue);
    }
}

void CartController::getCart(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& cb)
{
    auto session = req->session();
    if (!session)
    {
        Json::Value err;
        err["error"] = "sessions not enabled — check config.json";
        auto resp = HttpResponse::newHttpJsonResponse(err);
        resp->setStatusCode(k500InternalServerError);
        cb(resp);
        return;
    }

    auto cart = getCartFromSession(session);
    Json::Value resp;
    resp["sessionId"] = session->sessionId();
    resp["items"]     = cart;
    resp["count"]     = static_cast<int>(cart.size());
    cb(HttpResponse::newHttpJsonResponse(resp));
}

void CartController::addItem(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& cb)
{
    auto session = req->session();
    if (!session)
    {
        Json::Value err;
        err["error"] = "sessions not enabled — check config.json";
        auto resp = HttpResponse::newHttpJsonResponse(err);
        resp->setStatusCode(k500InternalServerError);
        cb(resp);
        return;
    }

    auto body = req->getJsonObject();
    if (!body || !(*body)["productId"] || !(*body)["name"])
    {
        Json::Value err;
        err["error"] = "productId and name required";
        auto resp = HttpResponse::newHttpJsonResponse(err);
        resp->setStatusCode(k400BadRequest);
        cb(resp);
        return;
    }

    auto cart     = getCartFromSession(session);
    int productId = (*body)["productId"].asInt();
    int qty       = (*body).get("quantity", 1).asInt();

    bool found = false;
    for (auto& item : cart)
    {
        if (item["productId"].asInt() == productId)
        {
            item["quantity"] = item["quantity"].asInt() + qty;
            found = true;
            break;
        }
    }
    if (!found)
    {
        Json::Value item;
        item["productId"] = productId;
        item["name"]      = (*body)["name"].asString();
        item["price"]     = (*body).get("price", 0.0).asDouble();
        item["quantity"]  = qty;
        cart.append(item);
    }

    session->insert("cart", cart);

    Json::Value resp;
    resp["message"] = "item added";
    resp["items"]   = cart;
    cb(HttpResponse::newHttpJsonResponse(resp));
}

void CartController::removeItem(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& cb,
    int productId)
{
    auto session = req->session();
    if (!session)
    {
        Json::Value err;
        err["error"] = "sessions not enabled — check config.json";
        auto resp = HttpResponse::newHttpJsonResponse(err);
        resp->setStatusCode(k500InternalServerError);
        cb(resp);
        return;
    }

    auto cart = getCartFromSession(session);
    Json::Value updated(Json::arrayValue);
    for (const auto& item : cart)
    {
        if (item["productId"].asInt() != productId)
            updated.append(item);
    }

    session->insert("cart", updated);

    Json::Value resp;
    resp["message"] = "item removed";
    resp["items"]   = updated;
    cb(HttpResponse::newHttpJsonResponse(resp));
}

void CartController::clearCart(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& cb)
{
    auto session = req->session();
    if (!session)
    {
        Json::Value err;
        err["error"] = "sessions not enabled — check config.json";
        auto resp = HttpResponse::newHttpJsonResponse(err);
        resp->setStatusCode(k500InternalServerError);
        cb(resp);
        return;
    }

    session->erase("cart");

    Json::Value resp;
    resp["message"] = "cart cleared";
    resp["items"]   = Json::Value(Json::arrayValue);
    cb(HttpResponse::newHttpJsonResponse(resp));
}