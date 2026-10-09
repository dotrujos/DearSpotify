#ifndef DEARSPOTIFY_SPOTIFY_MAPPER_H
#define DEARSPOTIFY_SPOTIFY_MAPPER_H

#include "spotify_types.h"

class spotify_mapper {
private:
    spotify_mapper();
public:
    static SpotifyAuthResponse from_json_to_auth_response(const std::string& response);
    static SpotifyArtistResponse from_json_to_get_artist_response(const std::string& response);
};

#endif //DEARSPOTIFY_SPOTIFY_MAPPER_H