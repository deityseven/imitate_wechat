#include "client.h"

#include <http/httplib.h>
#include <json/json.hpp>

HttpClient::HttpClient(std::string serverHost, unsigned int serverPort)
{
    this->client = new httplib::Client(serverHost, serverPort);
}

HttpClient::~HttpClient()
{
    if (this->client != nullptr) delete this->client;
}

bool HttpClient::serverOnline()
{
    auto result = this->client->Post("/api/serverOnline");

    if (result && (result->status == 200))
        return true;

    return false;
}

bool HttpClient::accountVerify(const std::string userInfo, std::string& response)
{
    auto result = this->client->Post("/api/accountVerify", userInfo, "application/json");

    if (result && (result->status == 200))
    {
        auto resJson = nlohmann::json::parse(result->body);

        auto statu = resJson["statu"].get<bool>();

        if (statu == true)
        {
            response = resJson["data"].dump();
            return true;
        }
        else response = resJson["message"].get<std::string>();
    }

    return false;
}

void HttpClient::setReadTimeout(unsigned int millisecond)
{
    this->client->set_read_timeout(0, millisecond);

}

void HttpClient::setWriteTimeout(unsigned int millisecond)
{
    this->client->set_write_timeout(0, millisecond);
}

bool HttpClient::accountUniqueCheck(std::string userName)
{
    nlohmann::json root;
    nlohmann::json data;
    data["user_name"] = userName;
    root["data"] = data;

    httplib::Params param;
    param.insert(std::make_pair("data", data.dump()));
    auto result = this->client->Post("/api/accountUniqueCheck", param);
    if (result && result->status == 200)
    {
        std::string response = result->body;

        auto responseJson = nlohmann::json::parse(response);

        auto statuJson = responseJson["statu"];
        if (!statuJson.is_null())
        {
            return statuJson.get<bool>();
        }
    }

    return false;
}
