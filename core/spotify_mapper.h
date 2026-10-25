#ifndef DEARSPOTIFY_SPOTIFY_MAPPER_H
#define DEARSPOTIFY_SPOTIFY_MAPPER_H

#include "spotify_types.h"
#include <nlohmann/json.hpp>

class spotify_mapper {
private:
    spotify_mapper();
public:
    static SpotifyAuthResponse from_json_to_auth_response(const std::string& response);

    static SpotifyAlbumResponse from_json_to_get_album_response(const std::string& response);
    static SpotifyGetAlbumTracksResponse from_json_to_get_album_tracks_response(const std::string& response);
    static SpotifyArtistResponse from_json_to_get_artist_response(const std::string& response);
    static SpotifyGetAlbumsResponse from_json_to_get_artist_albums_response(const std::string& response);
    static SpotifyShow from_json_to_get_show_response(const std::string& response);
    static SpotifyPagingSimplifiedEpisode from_json_to_get_show_episodes_response(const std::string& response);
    static SpotifyEpisode from_json_to_get_episode_response(const std::string& response);
    static SpotifyAudiobook from_json_to_get_audiobook_response(const std::string& response);
    static SpotifyPagingSimplifiedChapter from_json_to_get_audiobook_chapters_response(const std::string& response);
    static SpotifyPagingSimplifiedAudiobook from_json_to_get_saved_audiobooks_response(const std::string& response);
    static SpotifyChapter from_json_to_get_chapter_response(const std::string& response);
    static SpotifyTrackResponse from_json_to_get_track_response(const std::string& response);
    static SpotifySearchResponse from_json_to_search_response(const std::string& response);
    static SpotifyPrivateUser from_json_to_get_current_user_response(const std::string& response);
    static SpotifyPlaylist from_json_to_get_playlist_response(const std::string& response);
    static SpotifyPagingPlaylistTrack from_json_to_get_playlist_items_response(const std::string& response);
    static SpotifySnapshotResponse from_json_to_add_playlist_items_response(const std::string& response);
    static SpotifySnapshotResponse from_json_to_update_playlist_items_response(const std::string& response);
    static SpotifySnapshotResponse from_json_to_remove_playlist_items_response(const std::string& response);
    static SpotifyPagingPlaylist from_json_to_get_current_user_playlists_response(const std::string& response);
    static SpotifyPlaylist from_json_to_create_playlist_response(const std::string& response);
    static std::vector<bool> from_json_to_check_library_contains_response(const std::string& response);
    static SpotifyPagingSavedAlbum from_json_to_get_saved_albums_response(const std::string& response);
    static SpotifyPagingSavedTrack from_json_to_get_saved_tracks_response(const std::string& response);
    static SpotifyPagingSavedEpisode from_json_to_get_saved_episodes_response(const std::string& response);
    static SpotifyPagingSavedShow from_json_to_get_saved_shows_response(const std::string& response);
    static SpotifyGetTopItemsResponse from_json_to_get_top_items_response(const std::string& response);
    static std::vector<SpotifyImage> from_json_to_get_playlist_cover_response(const std::string& response);
    static SpotifyFollowedArtistsResponse from_json_to_get_followed_artists_response(const std::string& response);
    static SpotifyPlaybackState from_json_to_get_playback_state_response(const std::string& response);
    static SpotifyAvailableDevicesResponse from_json_to_get_available_devices_response(const std::string& response);
    static SpotifyPlaybackState from_json_to_get_currently_playing_response(const std::string& response);
    static SpotifyCursorPagingPlayHistory from_json_to_get_recently_played_response(const std::string& response);
    static SpotifyQueue from_json_to_get_queue_response(const std::string& response);

    static std::string from_change_playlist_details_request_to_json(const SpotifyChangePlaylistDetailsRequest& request);
    static std::string from_add_playlist_items_request_to_json(const SpotifyAddPlaylistItemsRequest& request);
    static std::string from_update_playlist_items_request_to_json(const SpotifyUpdatePlaylistItemsRequest& request);
    static std::string from_remove_playlist_items_request_to_json(const SpotifyRemovePlaylistItemsRequest& request);
    static std::string from_create_playlist_request_to_json(const SpotifyCreatePlaylistRequest& request);
    static std::string from_transfer_playback_request_to_json(const SpotifyTransferPlaybackRequest& request);
    static std::string from_start_playback_request_to_json(const SpotifyStartPlaybackRequest& request);
};

#endif //DEARSPOTIFY_SPOTIFY_MAPPER_H
