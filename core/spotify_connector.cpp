//
// Created by gabrielaraujo on 06/10/2026.
//

#include "spotify_connector.h"

#include "cpr/api.h"
#include "cpr/response.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

SpotifyAuthResponse spotify_connector::authenticate(const std::string &client_id, const std::string &client_secret) {
    cpr::Response r = cpr::Post(
        cpr::Url{"https://accounts.spotify.com/api/token"},
        cpr::Payload{
        {"client_id", client_id},
        {"client_secret", client_secret}
    });

    if (r.status_code != 200) {
        return SpotifyAuthResponse{.access_token = "", .token_type = "", .expires_in = -1};
    }

    auto j = json::parse(r.text);

    std::string access_token = j["access_token"].get<std::string>();
    std::string token_type = j["token_type"].get<std::string>();
    long expires_in = j["expires_in"].get<long>();

    return SpotifyAuthResponse{.access_token = access_token, .token_type = token_type, .expires_in = expires_in};
}
