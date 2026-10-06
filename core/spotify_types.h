//
// Created by gabrielaraujo on 06/10/2026.
//

#ifndef DEARSPOTIFY_SPOTIFY_TYPES_H
#define DEARSPOTIFY_SPOTIFY_TYPES_H

#include <string>
#include <vector>

struct SpotifyAuthResponse {
    std::string access_token;
    std::string token_type;
    long expires_in;
};

struct SpotifyArtistResponse {
    SpotifyExternalUrl external_urls;
    SpotifyArtistFollwers followers;
    std::vector<std::string> genres;
    std::string href;
    std::string id;
    std::string name;
    int popularity;
    std::vector<SpotifyArtistImages> images;
    std::string type;
    std::string uri;
};

struct SpotifyArtistImages {
    long height;
    std::string url;
    long width;
};

struct SpotifyArtistFollwers {
    std::string href;
    long total;
};

struct SpotifyExternalUrl {
    std::string spotify;
};

#endif //DEARSPOTIFY_SPOTIFY_TYPES_H
