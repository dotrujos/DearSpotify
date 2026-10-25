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
        {"grant_type", "client_credentials"},
        {"client_id", client_id},
        {"client_secret", client_secret}
    });

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::authenticate status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_auth_response(r.text);
}

std::optional<SpotifyAlbumResponse> spotify_connector::get_album(const std::string& album_id, const std::string& access_token, const std::optional<std::string>& market) {
    std::string full_url = API_URL + std::string("/v1/albums/") + album_id;

    cpr::Parameters parameters;
    if (market)
        parameters.Add({"market", *market});

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::get_album status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_get_album_response(r.text);
}

std::optional<SpotifyGetAlbumTracksResponse> spotify_connector::get_album_tracks(const std::string& album_id, const std::string& access_token, const std::optional<std::string>& market, std::optional<int> limit, std::optional<int> offset) {
    std::string full_url = API_URL + std::string("/v1/albums/") + album_id + std::string("/tracks");

    cpr::Parameters parameters;
    if (market)
        parameters.Add({"market", *market});
    if (limit)
        parameters.Add({"limit", std::to_string(*limit)});
    if (offset)
        parameters.Add({"offset", std::to_string(*offset)});

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::get_album_tracks status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_get_album_tracks_response(r.text);
}

std::optional<SpotifyArtistResponse> spotify_connector::get_artist(const std::string& artist_id, const std::string& access_token) {
    std::string full_url = API_URL + std::string("/v1/artists/") + artist_id;

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
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

std::optional<SpotifyGetAlbumsResponse> spotify_connector::get_artist_albums(const std::string& artist_id, const std::string& access_token, const std::optional<std::string>& include_groups, const std::optional<std::string>& market, std::optional<int> limit, std::optional<int> offset) {
    std::string full_url = API_URL + std::string("/v1/artists/") + artist_id + std::string("/albums");

    cpr::Parameters parameters;
    if (include_groups)
        parameters.Add({"include_groups", *include_groups});
    if (market)
        parameters.Add({"market", *market});
    if (limit)
        parameters.Add({"limit", std::to_string(*limit)});
    if (offset)
        parameters.Add({"offset", std::to_string(*offset)});

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        parameters,
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

std::optional<SpotifyShow> spotify_connector::get_show(const std::string& show_id, const std::string& access_token, const std::optional<std::string>& market) {
    std::string full_url = API_URL + std::string("/v1/shows/") + show_id;

    cpr::Parameters parameters;
    if (market)
        parameters.Add({"market", *market});

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::get_show status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_get_show_response(r.text);
}

std::optional<SpotifyPagingSimplifiedEpisode> spotify_connector::get_show_episodes(const std::string& show_id, const std::string& access_token, const std::optional<std::string>& market, std::optional<int> limit, std::optional<int> offset) {
    std::string full_url = API_URL + std::string("/v1/shows/") + show_id + std::string("/episodes");

    cpr::Parameters parameters;
    if (market)
        parameters.Add({"market", *market});
    if (limit)
        parameters.Add({"limit", std::to_string(*limit)});
    if (offset)
        parameters.Add({"offset", std::to_string(*offset)});

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::get_show_episodes status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_get_show_episodes_response(r.text);
}

std::optional<SpotifyEpisode> spotify_connector::get_episode(const std::string& episode_id, const std::string& access_token, const std::optional<std::string>& market) {
    std::string full_url = API_URL + std::string("/v1/episodes/") + episode_id;

    cpr::Parameters parameters;
    if (market)
        parameters.Add({"market", *market});

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::get_episode status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_get_episode_response(r.text);
}

std::optional<SpotifyAudiobook> spotify_connector::get_audiobook(const std::string& audiobook_id, const std::string& access_token, const std::optional<std::string>& market) {
    std::string full_url = API_URL + std::string("/v1/audiobooks/") + audiobook_id;

    cpr::Parameters parameters;
    if (market)
        parameters.Add({"market", *market});

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::get_audiobook status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_get_audiobook_response(r.text);
}

std::optional<SpotifyPagingSimplifiedChapter> spotify_connector::get_audiobook_chapters(const std::string& audiobook_id, const std::string& access_token, const std::optional<std::string>& market, std::optional<int> limit, std::optional<int> offset) {
    std::string full_url = API_URL + std::string("/v1/audiobooks/") + audiobook_id + std::string("/chapters");

    cpr::Parameters parameters;
    if (market)
        parameters.Add({"market", *market});
    if (limit)
        parameters.Add({"limit", std::to_string(*limit)});
    if (offset)
        parameters.Add({"offset", std::to_string(*offset)});

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::get_audiobook_chapters status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_get_audiobook_chapters_response(r.text);
}

std::optional<SpotifyPagingSimplifiedAudiobook> spotify_connector::get_saved_audiobooks(const std::string& access_token, std::optional<int> limit, std::optional<int> offset) {
    std::string full_url = API_URL + std::string("/v1/me/audiobooks");

    cpr::Parameters parameters;
    if (limit)
        parameters.Add({"limit", std::to_string(*limit)});
    if (offset)
        parameters.Add({"offset", std::to_string(*offset)});

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::get_saved_audiobooks status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_get_saved_audiobooks_response(r.text);
}

std::optional<SpotifyChapter> spotify_connector::get_chapter(const std::string& chapter_id, const std::string& access_token, const std::optional<std::string>& market) {
    std::string full_url = API_URL + std::string("/v1/chapters/") + chapter_id;

    cpr::Parameters parameters;
    if (market)
        parameters.Add({"market", *market});

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::get_chapter status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_get_chapter_response(r.text);
}

std::optional<SpotifyTrackResponse> spotify_connector::get_track(const std::string& track_id, const std::string& access_token, const std::optional<std::string>& market) {
    std::string full_url = API_URL + std::string("/v1/tracks/") + track_id;

    cpr::Parameters parameters;
    if (market)
        parameters.Add({"market", *market});

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::get_track status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_get_track_response(r.text);
}

std::optional<SpotifySearchResponse> spotify_connector::search(const std::string& q, const std::string& type, const std::string& access_token, const std::optional<std::string>& market, std::optional<int> limit, std::optional<int> offset, const std::optional<std::string>& include_external) {
    std::string full_url = API_URL + std::string("/v1/search");

    cpr::Parameters parameters;
    parameters.Add({"q", q});
    parameters.Add({"type", type});
    if (market)
        parameters.Add({"market", *market});
    if (limit)
        parameters.Add({"limit", std::to_string(*limit)});
    if (offset)
        parameters.Add({"offset", std::to_string(*offset)});
    if (include_external)
        parameters.Add({"include_external", *include_external});

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::search status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_search_response(r.text);
}

std::optional<SpotifyPrivateUser> spotify_connector::get_current_user(const std::string& access_token) {
    std::string full_url = API_URL + std::string("/v1/me");

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::get_current_user status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_get_current_user_response(r.text);
}

std::optional<SpotifyPlaylist> spotify_connector::get_playlist(const std::string& playlist_id, const std::string& access_token, const std::optional<std::string>& market, const std::optional<std::string>& fields, const std::optional<std::string>& additional_types) {
    std::string full_url = API_URL + std::string("/v1/playlists/") + playlist_id;

    cpr::Parameters parameters;
    if (market)
        parameters.Add({"market", *market});
    if (fields)
        parameters.Add({"fields", *fields});
    if (additional_types)
        parameters.Add({"additional_types", *additional_types});

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::get_playlist status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_get_playlist_response(r.text);
}

bool spotify_connector::change_playlist_details(const std::string& playlist_id, const SpotifyChangePlaylistDetailsRequest& body, const std::string& access_token) {
    std::string full_url = API_URL + std::string("/v1/playlists/") + playlist_id;

    cpr::Response r = cpr::Put(
        cpr::Url{ full_url },
        cpr::Header{
            {"Authorization", "Bearer " + access_token},
            {"Content-Type", "application/json"}
        },
        cpr::Body{ spotify_mapper::from_change_playlist_details_request_to_json(body) }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::change_playlist_details status code = " << r.status_code << std::endl;
        return false;
    }

    return true;
}

std::optional<SpotifyPagingPlaylistTrack> spotify_connector::get_playlist_items(const std::string& playlist_id, const std::string& access_token, const std::optional<std::string>& market, const std::optional<std::string>& fields, std::optional<int> limit, std::optional<int> offset, const std::optional<std::string>& additional_types) {
    std::string full_url = API_URL + std::string("/v1/playlists/") + playlist_id + std::string("/items");

    cpr::Parameters parameters;
    if (market)
        parameters.Add({"market", *market});
    if (fields)
        parameters.Add({"fields", *fields});
    if (limit)
        parameters.Add({"limit", std::to_string(*limit)});
    if (offset)
        parameters.Add({"offset", std::to_string(*offset)});
    if (additional_types)
        parameters.Add({"additional_types", *additional_types});

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::get_playlist_items status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_get_playlist_items_response(r.text);
}

std::optional<SpotifySnapshotResponse> spotify_connector::add_playlist_items(const std::string& playlist_id, const SpotifyAddPlaylistItemsRequest& body, const std::string& access_token, std::optional<int> position, const std::optional<std::string>& uris) {
    std::string full_url = API_URL + std::string("/v1/playlists/") + playlist_id + std::string("/items");

    cpr::Parameters parameters;
    if (position)
        parameters.Add({"position", std::to_string(*position)});
    if (uris)
        parameters.Add({"uris", *uris});

    cpr::Response r = cpr::Post(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token},
            {"Content-Type", "application/json"}
        },
        cpr::Body{ spotify_mapper::from_add_playlist_items_request_to_json(body) }
    );

    if (r.status_code != 201) {
        std::cerr << "err: spotify_connector::add_playlist_items status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_add_playlist_items_response(r.text);
}

std::optional<SpotifySnapshotResponse> spotify_connector::update_playlist_items(const std::string& playlist_id, const SpotifyUpdatePlaylistItemsRequest& body, const std::string& access_token, const std::optional<std::string>& uris) {
    std::string full_url = API_URL + std::string("/v1/playlists/") + playlist_id + std::string("/items");

    cpr::Parameters parameters;
    if (uris)
        parameters.Add({"uris", *uris});

    cpr::Response r = cpr::Put(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token},
            {"Content-Type", "application/json"}
        },
        cpr::Body{ spotify_mapper::from_update_playlist_items_request_to_json(body) }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::update_playlist_items status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_update_playlist_items_response(r.text);
}

std::optional<SpotifySnapshotResponse> spotify_connector::remove_playlist_items(const std::string& playlist_id, const SpotifyRemovePlaylistItemsRequest& body, const std::string& access_token) {
    std::string full_url = API_URL + std::string("/v1/playlists/") + playlist_id + std::string("/items");

    cpr::Response r = cpr::Delete(
        cpr::Url{ full_url },
        cpr::Header{
            {"Authorization", "Bearer " + access_token},
            {"Content-Type", "application/json"}
        },
        cpr::Body{ spotify_mapper::from_remove_playlist_items_request_to_json(body) }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::remove_playlist_items status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_remove_playlist_items_response(r.text);
}

std::optional<SpotifyPagingPlaylist> spotify_connector::get_current_user_playlists(const std::string& access_token, std::optional<int> limit, std::optional<int> offset) {
    std::string full_url = API_URL + std::string("/v1/me/playlists");

    cpr::Parameters parameters;
    if (limit)
        parameters.Add({"limit", std::to_string(*limit)});
    if (offset)
        parameters.Add({"offset", std::to_string(*offset)});

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::get_current_user_playlists status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_get_current_user_playlists_response(r.text);
}

std::optional<SpotifyPlaylist> spotify_connector::create_playlist(const SpotifyCreatePlaylistRequest& body, const std::string& access_token) {
    std::string full_url = API_URL + std::string("/v1/me/playlists");

    cpr::Response r = cpr::Post(
        cpr::Url{ full_url },
        cpr::Header{
            {"Authorization", "Bearer " + access_token},
            {"Content-Type", "application/json"}
        },
        cpr::Body{ spotify_mapper::from_create_playlist_request_to_json(body) }
    );

    if (r.status_code != 201) {
        std::cerr << "err: spotify_connector::create_playlist status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_create_playlist_response(r.text);
}

bool spotify_connector::save_library_items(const std::string& uris, const std::string& access_token) {
    std::string full_url = API_URL + std::string("/v1/me/library");

    cpr::Parameters parameters;
    parameters.Add({"uris", uris});

    cpr::Response r = cpr::Put(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        },
        cpr::Body{ "" }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::save_library_items status code = " << r.status_code << std::endl;
        return false;
    }

    return true;
}

bool spotify_connector::remove_library_items(const std::string& uris, const std::string& access_token) {
    std::string full_url = API_URL + std::string("/v1/me/library");

    cpr::Parameters parameters;
    parameters.Add({"uris", uris});

    cpr::Response r = cpr::Delete(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        },
        cpr::Body{ "" }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::remove_library_items status code = " << r.status_code << std::endl;
        return false;
    }

    return true;
}

std::optional<std::vector<bool>> spotify_connector::check_library_contains(const std::string& uris, const std::string& access_token) {
    std::string full_url = API_URL + std::string("/v1/me/library/contains");

    cpr::Parameters parameters;
    parameters.Add({"uris", uris});

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::check_library_contains status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_check_library_contains_response(r.text);
}

std::optional<SpotifyPagingSavedAlbum> spotify_connector::get_saved_albums(const std::string& access_token, std::optional<int> limit, std::optional<int> offset, const std::optional<std::string>& market) {
    std::string full_url = API_URL + std::string("/v1/me/albums");

    cpr::Parameters parameters;
    if (limit)
        parameters.Add({"limit", std::to_string(*limit)});
    if (offset)
        parameters.Add({"offset", std::to_string(*offset)});
    if (market)
        parameters.Add({"market", *market});

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::get_saved_albums status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_get_saved_albums_response(r.text);
}

std::optional<SpotifyPagingSavedTrack> spotify_connector::get_saved_tracks(const std::string& access_token, const std::optional<std::string>& market, std::optional<int> limit, std::optional<int> offset) {
    std::string full_url = API_URL + std::string("/v1/me/tracks");

    cpr::Parameters parameters;
    if (market)
        parameters.Add({"market", *market});
    if (limit)
        parameters.Add({"limit", std::to_string(*limit)});
    if (offset)
        parameters.Add({"offset", std::to_string(*offset)});

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::get_saved_tracks status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_get_saved_tracks_response(r.text);
}

std::optional<SpotifyPagingSavedEpisode> spotify_connector::get_saved_episodes(const std::string& access_token, const std::optional<std::string>& market, std::optional<int> limit, std::optional<int> offset) {
    std::string full_url = API_URL + std::string("/v1/me/episodes");

    cpr::Parameters parameters;
    if (market)
        parameters.Add({"market", *market});
    if (limit)
        parameters.Add({"limit", std::to_string(*limit)});
    if (offset)
        parameters.Add({"offset", std::to_string(*offset)});

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::get_saved_episodes status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_get_saved_episodes_response(r.text);
}

std::optional<SpotifyPagingSavedShow> spotify_connector::get_saved_shows(const std::string& access_token, std::optional<int> limit, std::optional<int> offset) {
    std::string full_url = API_URL + std::string("/v1/me/shows");

    cpr::Parameters parameters;
    if (limit)
        parameters.Add({"limit", std::to_string(*limit)});
    if (offset)
        parameters.Add({"offset", std::to_string(*offset)});

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::get_saved_shows status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_get_saved_shows_response(r.text);
}

std::optional<SpotifyGetTopItemsResponse> spotify_connector::get_top_items(const std::string& type, const std::string& access_token, const std::optional<std::string>& time_range, std::optional<int> limit, std::optional<int> offset) {
    std::string full_url = API_URL + std::string("/v1/me/top/") + type;

    cpr::Parameters parameters;
    if (time_range)
        parameters.Add({"time_range", *time_range});
    if (limit)
        parameters.Add({"limit", std::to_string(*limit)});
    if (offset)
        parameters.Add({"offset", std::to_string(*offset)});

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::get_top_items status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_get_top_items_response(r.text);
}

std::optional<std::vector<SpotifyImage>> spotify_connector::get_playlist_cover(const std::string& playlist_id, const std::string& access_token) {
    std::string full_url = API_URL + std::string("/v1/playlists/") + playlist_id + std::string("/images");

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::get_playlist_cover status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_get_playlist_cover_response(r.text);
}

bool spotify_connector::upload_playlist_cover(const std::string& playlist_id, const std::string& image_base64, const std::string& access_token) {
    std::string full_url = API_URL + std::string("/v1/playlists/") + playlist_id + std::string("/images");

    cpr::Response r = cpr::Put(
        cpr::Url{ full_url },
        cpr::Header{
            {"Authorization", "Bearer " + access_token},
            {"Content-Type", "image/jpeg"}
        },
        cpr::Body{ image_base64 }
    );

    if (r.status_code != 202) {
        std::cerr << "err: spotify_connector::upload_playlist_cover status code = " << r.status_code << std::endl;
        return false;
    }

    return true;
}

std::optional<SpotifyFollowedArtistsResponse> spotify_connector::get_followed_artists(const std::string& type, const std::string& access_token, const std::optional<std::string>& after, std::optional<int> limit) {
    std::string full_url = API_URL + std::string("/v1/me/following");

    cpr::Parameters parameters;
    parameters.Add({"type", type});
    if (after)
        parameters.Add({"after", *after});
    if (limit)
        parameters.Add({"limit", std::to_string(*limit)});

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::get_followed_artists status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_get_followed_artists_response(r.text);
}

std::optional<SpotifyPlaybackState> spotify_connector::get_playback_state(const std::string& access_token, const std::optional<std::string>& market, const std::optional<std::string>& additional_types) {
    std::string full_url = API_URL + std::string("/v1/me/player");

    cpr::Parameters parameters;
    if (market)
        parameters.Add({"market", *market});
    if (additional_types)
        parameters.Add({"additional_types", *additional_types});

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code == 204)
        return std::nullopt;

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::get_playback_state status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_get_playback_state_response(r.text);
}

bool spotify_connector::transfer_playback(const SpotifyTransferPlaybackRequest& body, const std::string& access_token) {
    std::string full_url = API_URL + std::string("/v1/me/player");

    cpr::Response r = cpr::Put(
        cpr::Url{ full_url },
        cpr::Header{
            {"Authorization", "Bearer " + access_token},
            {"Content-Type", "application/json"}
        },
        cpr::Body{ spotify_mapper::from_transfer_playback_request_to_json(body) }
    );

    if (r.status_code != 204) {
        std::cerr << "err: spotify_connector::transfer_playback status code = " << r.status_code << std::endl;
        return false;
    }

    return true;
}

std::optional<SpotifyAvailableDevicesResponse> spotify_connector::get_available_devices(const std::string& access_token) {
    std::string full_url = API_URL + std::string("/v1/me/player/devices");

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::get_available_devices status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_get_available_devices_response(r.text);
}

std::optional<SpotifyPlaybackState> spotify_connector::get_currently_playing(const std::string& access_token, const std::optional<std::string>& market, const std::optional<std::string>& additional_types) {
    std::string full_url = API_URL + std::string("/v1/me/player/currently-playing");

    cpr::Parameters parameters;
    if (market)
        parameters.Add({"market", *market});
    if (additional_types)
        parameters.Add({"additional_types", *additional_types});

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::get_currently_playing status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_get_currently_playing_response(r.text);
}

bool spotify_connector::start_playback(const SpotifyStartPlaybackRequest& body, const std::string& access_token, const std::optional<std::string>& device_id) {
    std::string full_url = API_URL + std::string("/v1/me/player/play");

    cpr::Parameters parameters;
    if (device_id)
        parameters.Add({"device_id", *device_id});

    cpr::Response r = cpr::Put(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token},
            {"Content-Type", "application/json"}
        },
        cpr::Body{ spotify_mapper::from_start_playback_request_to_json(body) }
    );

    if (r.status_code != 204) {
        std::cerr << "err: spotify_connector::start_playback status code = " << r.status_code << std::endl;
        return false;
    }

    return true;
}

bool spotify_connector::pause_playback(const std::string& access_token, const std::optional<std::string>& device_id) {
    std::string full_url = API_URL + std::string("/v1/me/player/pause");

    cpr::Parameters parameters;
    if (device_id)
        parameters.Add({"device_id", *device_id});

    cpr::Response r = cpr::Put(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        },
        cpr::Body{ "" }
    );

    if (r.status_code != 204) {
        std::cerr << "err: spotify_connector::pause_playback status code = " << r.status_code << std::endl;
        return false;
    }

    return true;
}

bool spotify_connector::skip_to_next(const std::string& access_token, const std::optional<std::string>& device_id) {
    std::string full_url = API_URL + std::string("/v1/me/player/next");

    cpr::Parameters parameters;
    if (device_id)
        parameters.Add({"device_id", *device_id});

    cpr::Response r = cpr::Post(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        },
        cpr::Body{ "" }
    );

    if (r.status_code != 204) {
        std::cerr << "err: spotify_connector::skip_to_next status code = " << r.status_code << std::endl;
        return false;
    }

    return true;
}

bool spotify_connector::skip_to_previous(const std::string& access_token, const std::optional<std::string>& device_id) {
    std::string full_url = API_URL + std::string("/v1/me/player/previous");

    cpr::Parameters parameters;
    if (device_id)
        parameters.Add({"device_id", *device_id});

    cpr::Response r = cpr::Post(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        },
        cpr::Body{ "" }
    );

    if (r.status_code != 204) {
        std::cerr << "err: spotify_connector::skip_to_previous status code = " << r.status_code << std::endl;
        return false;
    }

    return true;
}

bool spotify_connector::seek_to_position(long long position_ms, const std::string& access_token, const std::optional<std::string>& device_id) {
    std::string full_url = API_URL + std::string("/v1/me/player/seek");

    cpr::Parameters parameters;
    parameters.Add({"position_ms", std::to_string(position_ms)});
    if (device_id)
        parameters.Add({"device_id", *device_id});

    cpr::Response r = cpr::Put(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        },
        cpr::Body{ "" }
    );

    if (r.status_code != 204) {
        std::cerr << "err: spotify_connector::seek_to_position status code = " << r.status_code << std::endl;
        return false;
    }

    return true;
}

bool spotify_connector::set_repeat_mode(const std::string& state, const std::string& access_token, const std::optional<std::string>& device_id) {
    std::string full_url = API_URL + std::string("/v1/me/player/repeat");

    cpr::Parameters parameters;
    parameters.Add({"state", state});
    if (device_id)
        parameters.Add({"device_id", *device_id});

    cpr::Response r = cpr::Put(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        },
        cpr::Body{ "" }
    );

    if (r.status_code != 204) {
        std::cerr << "err: spotify_connector::set_repeat_mode status code = " << r.status_code << std::endl;
        return false;
    }

    return true;
}

bool spotify_connector::set_playback_volume(int volume_percent, const std::string& access_token, const std::optional<std::string>& device_id) {
    std::string full_url = API_URL + std::string("/v1/me/player/volume");

    cpr::Parameters parameters;
    parameters.Add({"volume_percent", std::to_string(volume_percent)});
    if (device_id)
        parameters.Add({"device_id", *device_id});

    cpr::Response r = cpr::Put(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        },
        cpr::Body{ "" }
    );

    if (r.status_code != 204) {
        std::cerr << "err: spotify_connector::set_playback_volume status code = " << r.status_code << std::endl;
        return false;
    }

    return true;
}

bool spotify_connector::set_shuffle(bool state, const std::string& access_token, const std::optional<std::string>& device_id) {
    std::string full_url = API_URL + std::string("/v1/me/player/shuffle");

    cpr::Parameters parameters;
    parameters.Add({"state", state ? "true" : "false"});
    if (device_id)
        parameters.Add({"device_id", *device_id});

    cpr::Response r = cpr::Put(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        },
        cpr::Body{ "" }
    );

    if (r.status_code != 204) {
        std::cerr << "err: spotify_connector::set_shuffle status code = " << r.status_code << std::endl;
        return false;
    }

    return true;
}

std::optional<SpotifyCursorPagingPlayHistory> spotify_connector::get_recently_played(const std::string& access_token, std::optional<int> limit, std::optional<long long> after, std::optional<long long> before) {
    std::string full_url = API_URL + std::string("/v1/me/player/recently-played");

    cpr::Parameters parameters;
    if (limit)
        parameters.Add({"limit", std::to_string(*limit)});
    if (after)
        parameters.Add({"after", std::to_string(*after)});
    if (before)
        parameters.Add({"before", std::to_string(*before)});

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::get_recently_played status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_get_recently_played_response(r.text);
}

std::optional<SpotifyQueue> spotify_connector::get_queue(const std::string& access_token) {
    std::string full_url = API_URL + std::string("/v1/me/player/queue");

    cpr::Response r = cpr::Get(
        cpr::Url{ full_url },
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        }
    );

    if (r.status_code != 200) {
        std::cerr << "err: spotify_connector::get_queue status code = " << r.status_code << std::endl;
        return std::nullopt;
    }

    return spotify_mapper::from_json_to_get_queue_response(r.text);
}

bool spotify_connector::add_to_queue(const std::string& uri, const std::string& access_token, const std::optional<std::string>& device_id) {
    std::string full_url = API_URL + std::string("/v1/me/player/queue");

    cpr::Parameters parameters;
    parameters.Add({"uri", uri});
    if (device_id)
        parameters.Add({"device_id", *device_id});

    cpr::Response r = cpr::Post(
        cpr::Url{ full_url },
        parameters,
        cpr::Header{
            {"Authorization", "Bearer " + access_token}
        },
        cpr::Body{ "" }
    );

    if (r.status_code != 204) {
        std::cerr << "err: spotify_connector::add_to_queue status code = " << r.status_code << std::endl;
        return false;
    }

    return true;
}
