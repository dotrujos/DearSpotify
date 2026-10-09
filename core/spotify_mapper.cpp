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

SpotifyArtistResponse spotify_mapper::from_json_to_get_artist_response(const std::string& response) {
    auto j = json::parse(response);

    SpotifyArtistResponse artist;

    artist.external_urls.spotify = j.at("external_urls").at("spotify").get<std::string>();

    const auto& followers = j.at("followers");
   
    if (followers.contains("href") && !followers["href"].is_null())
        artist.followers.href = followers["href"].get<std::string>();

    artist.followers.total = followers.at("total").get<long>();

    artist.genres = j.at("genres").get<std::vector<std::string>>();
    artist.href = j.at("href").get<std::string>();
    artist.id = j.at("id").get<std::string>();
    artist.name = j.at("name").get<std::string>();
    artist.popularity = j.at("popularity").get<int>();
    artist.type = j.at("type").get<std::string>();
    artist.uri = j.at("uri").get<std::string>();

    for (const auto& img : j.at("images")) {
        SpotifyArtistImages image;
        
        image.height = img.at("height").get<long>();
        image.url = img.at("url").get<std::string>();
        image.width = img.at("width").get<long>();

        artist.images.push_back(std::move(image));
    }

    return artist;
}