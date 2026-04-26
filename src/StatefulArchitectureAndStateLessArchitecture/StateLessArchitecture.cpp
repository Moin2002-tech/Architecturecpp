//
// Created by moinshaikh on 4/26/26.
//


#include "../../include/StatefulArchitectureAndStateLessArchitecture/StateLessArchitecture.hpp"
#include <drogon/orm/DbClient.h>
#include <json/json.h>


// Helper: decode a minimal JWT claim (production code would use a real JWT lib)
std::string ProductController::extractUserId(const HttpRequestPtr& req) const
{
    auto auth = req->getHeader("Authorization");
    if (auth.empty() || auth.substr(0, 7) != "Bearer ") return {};

    // In real code: verify signature, decode payload, extract "sub" claim.
    // Here we mock it — the token itself carries all the identity information.
    // No session table, no in-memory map, just the signed token.
    return "user_from_jwt";
}

// GET /api/products
// Completely stateless: reads from DB, returns JSON. No cookies, no sessions.
void ProductController::getProducts(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& cb) const
{
    auto userId = extractUserId(req);
    if (userId.empty()) {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k401Unauthorized);
        cb(resp);
        return;
    }

    auto dbClient = drogon::app().getDbClient();
    if (!dbClient)                                 
    {
        Json::Value err;
        err["error"]   = "no database configured";
        err["message"] = "add a db_clients block to config.json";
        auto resp = HttpResponse::newHttpJsonResponse(err);
        resp->setStatusCode(k503ServiceUnavailable);
        cb(resp);
        return;
    }

    // Async DB query — result arrives on a Drogon IO thread, no blocking.
    //auto dbClient = drogon::app().getDbClient();
    dbClient->execSqlAsync(
        "SELECT id, name, price FROM products LIMIT 20",
        [cb](const drogon::orm::Result& result)
        {
            Json::Value products(Json::arrayValue);
            for (const auto& row : result)
            {
                Json::Value p;
                p["id"]    = row["id"].as<int>();
                p["name"]  = row["name"].as<std::string>();
                p["price"] = row["price"].as<double>();
                products.append(p);
            }
            auto resp = HttpResponse::newHttpJsonResponse(products);
            cb(resp);
        },
        [cb](const drogon::orm::DrogonDbException& e)
        {
            Json::Value err;
            err["error"] = e.base().what();
            auto resp = HttpResponse::newHttpJsonResponse(err);
            resp->setStatusCode(k500InternalServerError);
            cb(resp);
        }
    );
}

// GET /api/products/{id}
void ProductController::getProduct(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& cb,
    int id) const
{
    if (extractUserId(req).empty())
    {
        cb(HttpResponse::newHttpResponse()); // 200 default — set 401 in real code
        return;
    }

    auto dbClient = drogon::app().getDbClient();
    dbClient->execSqlAsync(
        "SELECT id, name, price FROM products WHERE id = $1",
        [cb](const drogon::orm::Result& result) {
            if (result.empty())
            {
                Json::Value err; err["error"] = "not found";
                auto resp = HttpResponse::newHttpJsonResponse(err);
                resp->setStatusCode(k404NotFound);
                cb(resp);
                return;
            }
            Json::Value p;
            p["id"]    = result[0]["id"].as<int>();
            p["name"]  = result[0]["name"].as<std::string>();
            p["price"] = result[0]["price"].as<double>();
            cb(HttpResponse::newHttpJsonResponse(p));
        },
        [cb](const drogon::orm::DrogonDbException& e)
        {
            Json::Value err; err["error"] = e.base().what();
            auto resp = HttpResponse::newHttpJsonResponse(err);
            resp->setStatusCode(k500InternalServerError);
            cb(resp);
        },
        id
    );
}

// POST /api/products
void ProductController::createProduct(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& cb) const
{
    if (extractUserId(req).empty())
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k401Unauthorized);
        cb(resp);
        return;
    }

    auto body = req->getJsonObject();
    if (!body || !(*body)["name"] || !(*body)["price"])
    {
        Json::Value err; err["error"] = "name and price required";
        auto resp = HttpResponse::newHttpJsonResponse(err);
        resp->setStatusCode(k400BadRequest);
        cb(resp);
        return;
    }

    std::string name  = (*body)["name"].asString();
    double      price = (*body)["price"].asDouble();

    auto dbClient = drogon::app().getDbClient();
    dbClient->execSqlAsync(
        "INSERT INTO products (name, price) VALUES ($1, $2) RETURNING id",
        [cb, name, price](const drogon::orm::Result& r)
        {
            Json::Value resp;
            resp["id"]    = r[0]["id"].as<int>();
            resp["name"]  = name;
            resp["price"] = price;
            auto res = HttpResponse::newHttpJsonResponse(resp);
            res->setStatusCode(k201Created);
            cb(res);
        },
        [cb](const drogon::orm::DrogonDbException& e) {
            Json::Value err; err["error"] = e.base().what();
            auto resp = HttpResponse::newHttpJsonResponse(err);
            resp->setStatusCode(k500InternalServerError);
            cb(resp);
        },
        name, price
    );
}