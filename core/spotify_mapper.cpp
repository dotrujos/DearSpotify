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

SpotifyGetAlbumsResponse spotify_mapper::from_json_to_get_artist_albums_response(const std::string& response) {
    auto j = json::parse(response);

    SpotifyGetAlbumsResponse result;
    result.href = j.at("href").get<std::string>();
    result.limit = j.at("limit").get<int>();
    result.offset = j.at("offset").get<int>();
    result.total = j.at("total").get<int>();
   
    result.next = j.at("next").is_null() ? "" : j.at("next").get<std::string>();
    result.previous = j.at("previous").is_null() ? "" : j.at("previous").get<std::string>();

    const auto& items = j.at("items");
    result.items.reserve(items.size());

    for (const auto& item : items) {
        SpotifyAlbum album;

        album.album_type = item.at("album_type").get<std::string>();
        album.total_tracks = item.at("total_tracks").get<int>();
        album.available_markets = item.at("available_markets").get<std::vector<std::string>>();
        album.external_urls.spotify = item.at("external_urls").at("spotify").get<std::string>();
        album.href = item.at("href").get<std::string>();
        album.id = item.at("id").get<std::string>();
        album.name = item.at("name").get<std::string>();
        album.release_date = item.at("release_date").get<std::string>();
        album.release_date_precision = item.at("release_date_precision").get<std::string>();
        album.type = item.at("type").get<std::string>();
        album.uri = item.at("uri").get<std::string>();
        album.album_group = item.at("album_group").get<std::string>();

        for (const auto& img : item.at("images")) {
            SpotifyArtistImages image;
            
            image.height = img.at("height").get<long>();
            image.url = img.at("url").get<std::string>();
            image.width = img.at("width").get<long>();

            album.images.push_back(std::move(image));
        }

        for (const auto& art : item.at("artists")) {
            SpotifySimplifiedArtist artist;

            artist.external_urls.spotify = art.at("external_urls").at("spotify").get<std::string>();
            artist.href = art.at("href").get<std::string>();
            artist.id = art.at("id").get<std::string>();
            artist.name = art.at("name").get<std::string>();
            artist.type = art.at("type").get<std::string>();
            artist.uri = art.at("uri").get<std::string>();

            album.artists.push_back(std::move(artist));
        }

        if (item.contains("restrictions")) {
            SpotifyAlbumRestrictions r;
            r.reason = item.at("restrictions").at("reason").get<std::string>();
            album.restrictions = std::move(r);
        }            

        result.items.push_back(std::move(album));
    }

    return result;
}