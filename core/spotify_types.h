//
// Created by gabrielaraujo on 06/10/2026.
//

#ifndef DEARSPOTIFY_SPOTIFY_TYPES_H
#define DEARSPOTIFY_SPOTIFY_TYPES_H
#include <string>

struct SpotifyAuthResponse {
    std::string access_token;
    std::string token_type;
    long expires_in;
};

#endif //DEARSPOTIFY_SPOTIFY_TYPES_H
