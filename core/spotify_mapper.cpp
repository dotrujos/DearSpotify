#include <nlohmann/json.hpp>

#include "spotify_mapper.h"

using json = nlohmann::json;

SpotifyAuthResponse spotify_mapper::from_json_to_auth_response(const std::string& response) {
    auto j = json::parse(response);

    std::string access_token = j["access_token"].get<std::string>();
    std::string token_type = j["token_type"].get<std::string>();
    long expires_in = j["expires_in"].get<long>();

    return SpotifyAuthResponse{.access_token = access_token, .token_type = token_type, .expires_in = expires_in};
}