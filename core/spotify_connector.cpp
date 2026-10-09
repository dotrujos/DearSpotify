//
// Created by gabrielaraujo on 06/10/2026.
//

#include "spotify_connector.h"

#define API_URL "https://api.spotify.com"

using json = nlohmann::json;

std::optional<SpotifyAuthResponse> spotify_connector::authenticate(const std::string &client_id, const std::string &client_secret) {
    cpr::Response r = cpr::Post(
        cpr::Url{"https://accounts.spotify.com/api/token"},
        cpr::Payload{
        {"client_id", client_id},
        {"client_secret", client_secret}
    });

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::authenticate status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_auth_response(r.text);
}

std::optional<SpotifyArtistResponse> spotify_connector::get_artist(const std::string& artist_id, const std::string& access_token) {
    std::string full_url = API_URL + std::string("/v1/artists/") + artist_id;

    cpr::Response r = cpr::Get(
        cpr::Url{full_url},
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::get_artist status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_get_artist_response(r.text);
}

std::optional<SpotifyGetAlbumsResponse> spotify_connector::get_artist_albums(const std::string& artist_id, const std::string& access_token) {
    std::string full_url = API_URL + std::string("/artists/") + artist_id + std::string("/albums");

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::get_artist_albums status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_get_artist_albums_response(r.text);
}