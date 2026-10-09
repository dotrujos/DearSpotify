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

struct SpotifyAlbumRestrictions {
    std::string reason;
};

struct SpotifySimplifiedArtist {
    SpotifyExternalUrl external_urls;
    std::string href;
    std::string id;
    std::string name;
    std::string type;
    std::string uri;
};

struct SpotifyAlbum {
    std::string album_type;
    int total_tracks;
    std::vector<std::string> available_markets;
    SpotifyExternalUrl external_urls;
    std::string href;
    std::string id;
    std::vector<SpotifyArtistImages> images;
    std::string name;
    std::string release_date;
    std::string release_date_precision;
    std::optional<SpotifyAlbumRestrictions> restrictions;  
    std::string type;
    std::string uri;
    std::vector<SpotifySimplifiedArtist> artists;
    std::string album_group;
};

struct SpotifyGetAlbumsResponse {
    std::string href;
    int limit;
    std::string next;       
    int offset;
    std::string previous;   
    int total;
    std::vector<SpotifyAlbum> items;
};

#endif //DEARSPOTIFY_SPOTIFY_TYPES_H
