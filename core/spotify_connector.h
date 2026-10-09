//
// Created by gabrielaraujo on 06/10/2026.
//

#ifndef DEARSPOTIFY_SPOTIFY_CONNECTOR_H
#define DEARSPOTIFY_SPOTIFY_CONNECTOR_H

#include "spotify_types.h"
#include "spotify_mapper.h"
#include <iostream>
#include "cpr/api.h"
#include "cpr/response.h"
#include <nlohmann/json.hpp>

class spotify_connector {
public:
    std::optional<SpotifyAuthResponse> authenticate(
        const std::string& client_id,
        const std::string& client_secret);

    std::optional<SpotifyArtistResponse> get_artist(
        const std::string& artist_id,
        const std::string& access_token);

    std::optional<SpotifyGetAlbumsResponse> get_artist_albums(
        const std::string& artist_id,
        const std::string& access_token
    );
};


#endif //DEARSPOTIFY_SPOTIFY_CONNECTOR_H
