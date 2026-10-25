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

    std::optional<SpotifyAlbumResponse> get_album(
        const std::string& album_id,
        const std::string& access_token,
        const std::optional<std::string>& market = std::nullopt
    );

    std::optional<SpotifyGetAlbumTracksResponse> get_album_tracks(
        const std::string& album_id,
        const std::string& access_token,
        const std::optional<std::string>& market = std::nullopt,
        std::optional<int> limit = std::nullopt,
        std::optional<int> offset = std::nullopt
    );

    std::optional<SpotifyArtistResponse> get_artist(
        const std::string& artist_id,
        const std::string& access_token
    );

    std::optional<SpotifyGetAlbumsResponse> get_artist_albums(
        const std::string& artist_id,
        const std::string& access_token,
        const std::optional<std::string>& include_groups = std::nullopt,
        const std::optional<std::string>& market = std::nullopt,
        std::optional<int> limit = std::nullopt,
        std::optional<int> offset = std::nullopt
    );

    std::optional<SpotifyShow> get_show(
        const std::string& show_id,
        const std::string& access_token,
        const std::optional<std::string>& market = std::nullopt
    );

    std::optional<SpotifyPagingSimplifiedEpisode> get_show_episodes(
        const std::string& show_id,
        const std::string& access_token,
        const std::optional<std::string>& market = std::nullopt,
        std::optional<int> limit = std::nullopt,
        std::optional<int> offset = std::nullopt
    );

    std::optional<SpotifyEpisode> get_episode(
        const std::string& episode_id,
        const std::string& access_token,
        const std::optional<std::string>& market = std::nullopt
    );

    std::optional<SpotifyAudiobook> get_audiobook(
        const std::string& audiobook_id,
        const std::string& access_token,
        const std::optional<std::string>& market = std::nullopt
    );

    std::optional<SpotifyPagingSimplifiedChapter> get_audiobook_chapters(
        const std::string& audiobook_id,
        const std::string& access_token,
        const std::optional<std::string>& market = std::nullopt,
        std::optional<int> limit = std::nullopt,
        std::optional<int> offset = std::nullopt
    );

    std::optional<SpotifyPagingSimplifiedAudiobook> get_saved_audiobooks(
        const std::string& access_token,
        std::optional<int> limit = std::nullopt,
        std::optional<int> offset = std::nullopt
    );

    std::optional<SpotifyChapter> get_chapter(
        const std::string& chapter_id,
        const std::string& access_token,
        const std::optional<std::string>& market = std::nullopt
    );

    std::optional<SpotifyTrackResponse> get_track(
        const std::string& track_id,
        const std::string& access_token,
        const std::optional<std::string>& market = std::nullopt
    );

    std::optional<SpotifySearchResponse> search(
        const std::string& q,
        const std::string& type,
        const std::string& access_token,
        const std::optional<std::string>& market = std::nullopt,
        std::optional<int> limit = std::nullopt,
        std::optional<int> offset = std::nullopt,
        const std::optional<std::string>& include_external = std::nullopt
    );

    std::optional<SpotifyPrivateUser> get_current_user(
        const std::string& access_token
    );

    std::optional<SpotifyPlaylist> get_playlist(
        const std::string& playlist_id,
        const std::string& access_token,
        const std::optional<std::string>& market = std::nullopt,
        const std::optional<std::string>& fields = std::nullopt,
        const std::optional<std::string>& additional_types = std::nullopt
    );

    bool change_playlist_details(
        const std::string& playlist_id,
        const SpotifyChangePlaylistDetailsRequest& body,
        const std::string& access_token
    );

    std::optional<SpotifyPagingPlaylistTrack> get_playlist_items(
        const std::string& playlist_id,
        const std::string& access_token,
        const std::optional<std::string>& market = std::nullopt,
        const std::optional<std::string>& fields = std::nullopt,
        std::optional<int> limit = std::nullopt,
        std::optional<int> offset = std::nullopt,
        const std::optional<std::string>& additional_types = std::nullopt
    );

    std::optional<SpotifySnapshotResponse> add_playlist_items(
        const std::string& playlist_id,
        const SpotifyAddPlaylistItemsRequest& body,
        const std::string& access_token,
        std::optional<int> position = std::nullopt,
        const std::optional<std::string>& uris = std::nullopt
    );

    std::optional<SpotifySnapshotResponse> update_playlist_items(
        const std::string& playlist_id,
        const SpotifyUpdatePlaylistItemsRequest& body,
        const std::string& access_token,
        const std::optional<std::string>& uris = std::nullopt
    );

    std::optional<SpotifySnapshotResponse> remove_playlist_items(
        const std::string& playlist_id,
        const SpotifyRemovePlaylistItemsRequest& body,
        const std::string& access_token
    );

    std::optional<SpotifyPagingPlaylist> get_current_user_playlists(
        const std::string& access_token,
        std::optional<int> limit = std::nullopt,
        std::optional<int> offset = std::nullopt
    );

    std::optional<SpotifyPlaylist> create_playlist(
        const SpotifyCreatePlaylistRequest& body,
        const std::string& access_token
    );

    bool save_library_items(
        const std::string& uris,
        const std::string& access_token
    );

    bool remove_library_items(
        const std::string& uris,
        const std::string& access_token
    );

    std::optional<std::vector<bool>> check_library_contains(
        const std::string& uris,
        const std::string& access_token
    );

    std::optional<SpotifyPagingSavedAlbum> get_saved_albums(
        const std::string& access_token,
        std::optional<int> limit = std::nullopt,
        std::optional<int> offset = std::nullopt,
        const std::optional<std::string>& market = std::nullopt
    );

    std::optional<SpotifyPagingSavedTrack> get_saved_tracks(
        const std::string& access_token,
        const std::optional<std::string>& market = std::nullopt,
        std::optional<int> limit = std::nullopt,
        std::optional<int> offset = std::nullopt
    );

    std::optional<SpotifyPagingSavedEpisode> get_saved_episodes(
        const std::string& access_token,
        const std::optional<std::string>& market = std::nullopt,
        std::optional<int> limit = std::nullopt,
        std::optional<int> offset = std::nullopt
    );

    std::optional<SpotifyPagingSavedShow> get_saved_shows(
        const std::string& access_token,
        std::optional<int> limit = std::nullopt,
        std::optional<int> offset = std::nullopt
    );

    std::optional<SpotifyGetTopItemsResponse> get_top_items(
        const std::string& type,
        const std::string& access_token,
        const std::optional<std::string>& time_range = std::nullopt,
        std::optional<int> limit = std::nullopt,
        std::optional<int> offset = std::nullopt
    );

    std::optional<std::vector<SpotifyImage>> get_playlist_cover(
        const std::string& playlist_id,
        const std::string& access_token
    );

    bool upload_playlist_cover(
        const std::string& playlist_id,
        const std::string& image_base64,
        const std::string& access_token
    );

    std::optional<SpotifyFollowedArtistsResponse> get_followed_artists(
        const std::string& type,
        const std::string& access_token,
        const std::optional<std::string>& after = std::nullopt,
        std::optional<int> limit = std::nullopt
    );

    // 204 (nothing playing) is not an error: it returns std::nullopt without logging
    std::optional<SpotifyPlaybackState> get_playback_state(
        const std::string& access_token,
        const std::optional<std::string>& market = std::nullopt,
        const std::optional<std::string>& additional_types = std::nullopt
    );

    bool transfer_playback(
        const SpotifyTransferPlaybackRequest& body,
        const std::string& access_token
    );

    std::optional<SpotifyAvailableDevicesResponse> get_available_devices(
        const std::string& access_token
    );

    std::optional<SpotifyPlaybackState> get_currently_playing(
        const std::string& access_token,
        const std::optional<std::string>& market = std::nullopt,
        const std::optional<std::string>& additional_types = std::nullopt
    );

    bool start_playback(
        const SpotifyStartPlaybackRequest& body,
        const std::string& access_token,
        const std::optional<std::string>& device_id = std::nullopt
    );

    bool pause_playback(
        const std::string& access_token,
        const std::optional<std::string>& device_id = std::nullopt
    );

    bool skip_to_next(
        const std::string& access_token,
        const std::optional<std::string>& device_id = std::nullopt
    );

    bool skip_to_previous(
        const std::string& access_token,
        const std::optional<std::string>& device_id = std::nullopt
    );

    bool seek_to_position(
        long long position_ms,
        const std::string& access_token,
        const std::optional<std::string>& device_id = std::nullopt
    );

    bool set_repeat_mode(
        const std::string& state,
        const std::string& access_token,
        const std::optional<std::string>& device_id = std::nullopt
    );

    bool set_playback_volume(
        int volume_percent,
        const std::string& access_token,
        const std::optional<std::string>& device_id = std::nullopt
    );

    bool set_shuffle(
        bool state,
        const std::string& access_token,
        const std::optional<std::string>& device_id = std::nullopt
    );

    std::optional<SpotifyCursorPagingPlayHistory> get_recently_played(
        const std::string& access_token,
        std::optional<int> limit = std::nullopt,
        std::optional<long long> after = std::nullopt,
        std::optional<long long> before = std::nullopt
    );

    std::optional<SpotifyQueue> get_queue(
        const std::string& access_token
    );

    bool add_to_queue(
        const std::string& uri,
        const std::string& access_token,
        const std::optional<std::string>& device_id = std::nullopt
    );

};


#endif //DEARSPOTIFY_SPOTIFY_CONNECTOR_H
