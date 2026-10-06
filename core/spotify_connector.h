//
// Created by gabrielaraujo on 06/10/2026.
//

#ifndef DEARSPOTIFY_SPOTIFY_CONNECTOR_H
#define DEARSPOTIFY_SPOTIFY_CONNECTOR_H

#include "spotify_types.h"

class spotify_connector {
public:
    SpotifyAuthResponse authenticate(
        const std::string& client_id,
        const std::string& client_secret);

    SpotifyArtistResponse get_artist(
        const std::string& artist_id,
        const std::string& access_token);
};


#endif //DEARSPOTIFY_SPOTIFY_CONNECTOR_H
