//
// Created by gabrielaraujo on 06/10/2026.
//

#ifndef DEARSPOTIFY_SPOTIFY_TYPES_H
#define DEARSPOTIFY_SPOTIFY_TYPES_H

#include <optional>
#include <string>
#include <variant>
#include <vector>

struct SpotifyAuthResponse {
    std::string access_token;
    std::string token_type;
    long expires_in;
};

template <typename T>
struct SpotifyPaging {
    std::string href;
    int limit;
    std::string next;
    int offset;
    std::string previous;
    int total;
    std::vector<T> items;
};

struct SpotifyCursors {
    std::string after;
    std::string before;
};

template <typename T>
struct SpotifyCursorPaging {
    std::string href;
    int limit;
    std::string next;
    SpotifyCursors cursors;
    int total;
    std::vector<T> items;
};

struct SpotifyExternalUrl {
    std::string spotify;
};

struct SpotifyImage {
    std::string url;
    std::optional<int> height;
    std::optional<int> width;
};

struct SpotifyAlbumRestrictions {
    std::string reason;
};

struct SpotifySimplifiedArtist {
    std::optional<SpotifyExternalUrl> external_urls;
    std::string href;
    std::string id;
    std::string name;
    std::string type;
    std::string uri;
};

struct SpotifyTrackRestrictions {
    std::string reason;
};

struct SpotifySimplifiedTrack {
    std::vector<SpotifySimplifiedArtist> artists;
    int disc_number;
    int duration_ms;
    bool is_explicit;
    std::optional<SpotifyExternalUrl> external_urls;
    std::string href;
    std::string id;
    bool is_playable;
    std::optional<SpotifyTrackRestrictions> restrictions;
    std::string name;
    int track_number;
    std::string type;
    std::string uri;
    bool is_local;
};

using SpotifyGetAlbumTracksResponse = SpotifyPaging<SpotifySimplifiedTrack>;

struct SpotifyCopyright {
    std::string text;
    std::string type;
};

struct SpotifyExternalIds {
    std::string isrc;
    std::string ean;
    std::string upc;
};

struct SpotifyAlbumResponse {
    std::string album_type;
    int total_tracks;
    SpotifyExternalUrl external_urls;
    std::string href;
    std::string id;
    std::vector<SpotifyImage> images;
    std::string name;
    std::string release_date;
    std::string release_date_precision;
    std::optional<SpotifyAlbumRestrictions> restrictions;
    std::string type;
    std::string uri;
    std::vector<SpotifySimplifiedArtist> artists;
    SpotifyGetAlbumTracksResponse tracks;
    std::vector<SpotifyCopyright> copyrights;
    SpotifyExternalIds external_ids;
};

struct SpotifyArtistResponse {
    std::optional<SpotifyExternalUrl> external_urls;
    std::string href;
    std::string id;
    std::vector<SpotifyImage> images;
    std::string name;
    std::string type;
    std::string uri;
};

struct SpotifyAlbum {
    std::string album_type;
    int total_tracks;
    SpotifyExternalUrl external_urls;
    std::string href;
    std::string id;
    std::vector<SpotifyImage> images;
    std::string name;
    std::string release_date;
    std::string release_date_precision;
    std::optional<SpotifyAlbumRestrictions> restrictions;
    std::string type;
    std::string uri;
    std::vector<SpotifySimplifiedArtist> artists;
};

using SpotifyGetAlbumsResponse = SpotifyPaging<SpotifyAlbum>;

struct SpotifyResumePoint {
    bool fully_played;
    int resume_position_ms;
};

struct SpotifyEpisodeRestriction {
    std::string reason;
};

struct SpotifySimplifiedEpisode {
    std::string description;
    std::string html_description;
    int duration_ms;
    bool is_explicit;
    SpotifyExternalUrl external_urls;
    std::string href;
    std::string id;
    std::vector<SpotifyImage> images;
    bool is_externally_hosted;
    bool is_playable;
    std::vector<std::string> languages;
    std::string name;
    std::string release_date;
    std::string release_date_precision;
    std::optional<SpotifyResumePoint> resume_point;
    std::string type;
    std::string uri;
    std::optional<SpotifyEpisodeRestriction> restrictions;
};

using SpotifyPagingSimplifiedEpisode = SpotifyPaging<SpotifySimplifiedEpisode>;

struct SpotifyShow {
    std::vector<SpotifyCopyright> copyrights;
    std::string description;
    std::string html_description;
    bool is_explicit;
    SpotifyExternalUrl external_urls;
    std::string href;
    std::string id;
    std::vector<SpotifyImage> images;
    bool is_externally_hosted;
    std::vector<std::string> languages;
    std::string media_type;
    std::string name;
    std::string type;
    std::string uri;
    int total_episodes;
    SpotifyPagingSimplifiedEpisode episodes;
};

struct SpotifySimplifiedShow {
    std::vector<SpotifyCopyright> copyrights;
    std::string description;
    std::string html_description;
    bool is_explicit;
    SpotifyExternalUrl external_urls;
    std::string href;
    std::string id;
    std::vector<SpotifyImage> images;
    bool is_externally_hosted;
    std::vector<std::string> languages;
    std::string media_type;
    std::string name;
    std::string type;
    std::string uri;
    int total_episodes;
};

struct SpotifyEpisode {
    std::string description;
    std::string html_description;
    int duration_ms;
    bool is_explicit;
    SpotifyExternalUrl external_urls;
    std::string href;
    std::string id;
    std::vector<SpotifyImage> images;
    bool is_externally_hosted;
    bool is_playable;
    std::vector<std::string> languages;
    std::string name;
    std::string release_date;
    std::string release_date_precision;
    std::optional<SpotifyResumePoint> resume_point;
    std::string type;
    std::string uri;
    std::optional<SpotifyEpisodeRestriction> restrictions;
    SpotifySimplifiedShow show;
};

struct SpotifyAuthor {
    std::string name;
};

struct SpotifyNarrator {
    std::string name;
};

struct SpotifyChapterRestriction {
    std::string reason;
};

struct SpotifySimplifiedChapter {
    int chapter_number;
    std::string description;
    std::string html_description;
    int duration_ms;
    bool is_explicit;
    SpotifyExternalUrl external_urls;
    std::string href;
    std::string id;
    std::vector<SpotifyImage> images;
    bool is_playable;
    std::vector<std::string> languages;
    std::string name;
    std::string release_date;
    std::string release_date_precision;
    std::optional<SpotifyResumePoint> resume_point;
    std::string type;
    std::string uri;
    std::optional<SpotifyChapterRestriction> restrictions;
};

using SpotifyPagingSimplifiedChapter = SpotifyPaging<SpotifySimplifiedChapter>;

struct SpotifyAudiobook {
    std::vector<SpotifyAuthor> authors;
    std::vector<SpotifyCopyright> copyrights;
    std::string description;
    std::string html_description;
    std::string edition;
    bool is_explicit;
    SpotifyExternalUrl external_urls;
    std::string href;
    std::string id;
    std::vector<SpotifyImage> images;
    std::vector<std::string> languages;
    std::string media_type;
    std::string name;
    std::vector<SpotifyNarrator> narrators;
    std::string type;
    std::string uri;
    int total_chapters;
    SpotifyPagingSimplifiedChapter chapters;
};

struct SpotifySimplifiedAudiobook {
    std::vector<SpotifyAuthor> authors;
    std::vector<SpotifyCopyright> copyrights;
    std::string description;
    std::string html_description;
    std::string edition;
    bool is_explicit;
    SpotifyExternalUrl external_urls;
    std::string href;
    std::string id;
    std::vector<SpotifyImage> images;
    std::vector<std::string> languages;
    std::string media_type;
    std::string name;
    std::vector<SpotifyNarrator> narrators;
    std::string type;
    std::string uri;
    int total_chapters;
};

using SpotifyPagingSimplifiedAudiobook = SpotifyPaging<SpotifySimplifiedAudiobook>;

struct SpotifyChapter {
    int chapter_number;
    std::string description;
    std::string html_description;
    int duration_ms;
    bool is_explicit;
    SpotifyExternalUrl external_urls;
    std::string href;
    std::string id;
    std::vector<SpotifyImage> images;
    bool is_playable;
    std::vector<std::string> languages;
    std::string name;
    std::string release_date;
    std::string release_date_precision;
    std::optional<SpotifyResumePoint> resume_point;
    std::string type;
    std::string uri;
    std::optional<SpotifyChapterRestriction> restrictions;
    SpotifySimplifiedAudiobook audiobook;
};

struct SpotifySimplifiedAlbum {
    std::string album_type;
    int total_tracks;
    SpotifyExternalUrl external_urls;
    std::string href;
    std::string id;
    std::vector<SpotifyImage> images;
    std::string name;
    std::string release_date;
    std::string release_date_precision;
    std::optional<SpotifyAlbumRestrictions> restrictions;
    std::string type;
    std::string uri;
    std::vector<SpotifySimplifiedArtist> artists;
};

struct SpotifyTrackResponse {
    std::optional<SpotifySimplifiedAlbum> album;
    std::vector<SpotifySimplifiedArtist> artists;
    int disc_number;
    int duration_ms;
    bool is_explicit;
    std::optional<SpotifyExternalIds> external_ids;
    std::optional<SpotifyExternalUrl> external_urls;
    std::string href;
    std::string id;
    bool is_playable;
    std::optional<SpotifyTrackRestrictions> restrictions;
    std::string name;
    int track_number;
    std::string type;
    std::string uri;
    bool is_local;
};

using SpotifyPagingTrack = SpotifyPaging<SpotifyTrackResponse>;

using SpotifyPagingArtist = SpotifyPaging<SpotifyArtistResponse>;

using SpotifyPagingSimplifiedAlbum = SpotifyPaging<SpotifySimplifiedAlbum>;

struct SpotifyPlaylistOwner {
    std::optional<SpotifyExternalUrl> external_urls;
    std::string href;
    std::string id;
    std::string type;
    std::string uri;
    std::string display_name;
};

struct SpotifyPlaylistTracksRef {
    std::string href;
    int total;
};

struct SpotifySimplifiedPlaylist {
    bool collaborative;
    std::string description;
    std::optional<SpotifyExternalUrl> external_urls;
    std::string href;
    std::string id;
    std::vector<SpotifyImage> images;
    std::string name;
    std::optional<SpotifyPlaylistOwner> owner;
    bool is_public;
    std::string snapshot_id;
    std::optional<SpotifyPlaylistTracksRef> items;
    std::string type;
    std::string uri;
};

using SpotifyPagingPlaylist = SpotifyPaging<SpotifySimplifiedPlaylist>;

using SpotifyPagingSimplifiedShow = SpotifyPaging<SpotifySimplifiedShow>;

struct SpotifySearchResponse {
    std::optional<SpotifyPagingTrack> tracks;
    std::optional<SpotifyPagingArtist> artists;
    std::optional<SpotifyPagingSimplifiedAlbum> albums;
    std::optional<SpotifyPagingPlaylist> playlists;
    std::optional<SpotifyPagingSimplifiedShow> shows;
    std::optional<SpotifyPagingSimplifiedEpisode> episodes;
    std::optional<SpotifyPagingSimplifiedAudiobook> audiobooks;
};

struct SpotifyPrivateUser {
    std::string account_id;
    std::string display_name;
    std::optional<SpotifyExternalUrl> external_urls;
    std::string href;
    std::string id;
    std::vector<SpotifyImage> images;
    std::string type;
    std::string uri;
};

struct SpotifyPlaylistUser {
    std::optional<SpotifyExternalUrl> external_urls;
    std::string href;
    std::string id;
    std::string type;
    std::string uri;
};

using SpotifyTrackOrEpisode = std::variant<std::monostate, SpotifyTrackResponse, SpotifyEpisode>;

struct SpotifyPlaylistTrack {
    std::string added_at;
    std::optional<SpotifyPlaylistUser> added_by;
    bool is_local;
    SpotifyTrackOrEpisode item;
};

using SpotifyPagingPlaylistTrack = SpotifyPaging<SpotifyPlaylistTrack>;

struct SpotifyPlaylist {
    bool collaborative;
    std::string description;
    std::optional<SpotifyExternalUrl> external_urls;
    std::string href;
    std::string id;
    std::vector<SpotifyImage> images;
    std::string name;
    std::optional<SpotifyPlaylistOwner> owner;
    bool is_public;
    std::string snapshot_id;
    std::optional<SpotifyPagingPlaylistTrack> items;
    std::string type;
    std::string uri;
};

struct SpotifySnapshotResponse {
    std::string snapshot_id;
};

struct SpotifySavedAlbum {
    std::string added_at;
    std::optional<SpotifyAlbumResponse> album;
};

using SpotifyPagingSavedAlbum = SpotifyPaging<SpotifySavedAlbum>;

struct SpotifySavedTrack {
    std::string added_at;
    std::optional<SpotifyTrackResponse> track;
};

using SpotifyPagingSavedTrack = SpotifyPaging<SpotifySavedTrack>;

struct SpotifySavedEpisode {
    std::string added_at;
    std::optional<SpotifyEpisode> episode;
};

using SpotifyPagingSavedEpisode = SpotifyPaging<SpotifySavedEpisode>;

struct SpotifySavedShow {
    std::string added_at;
    std::optional<SpotifySimplifiedShow> show;
};

using SpotifyPagingSavedShow = SpotifyPaging<SpotifySavedShow>;

using SpotifyArtistOrTrack = std::variant<std::monostate, SpotifyArtistResponse, SpotifyTrackResponse>;

using SpotifyGetTopItemsResponse = SpotifyPaging<SpotifyArtistOrTrack>;

using SpotifyCursorPagingSimplifiedArtist = SpotifyCursorPaging<SpotifyArtistResponse>;

struct SpotifyFollowedArtistsResponse {
    SpotifyCursorPagingSimplifiedArtist artists;
};

struct SpotifyDevice {
    std::string id;
    bool is_active;
    bool is_private_session;
    bool is_restricted;
    std::string name;
    std::string type;
    std::optional<int> volume_percent;
    bool supports_volume;
};

struct SpotifyContext {
    std::string type;
    std::string href;
    std::optional<SpotifyExternalUrl> external_urls;
    std::string uri;
};

struct SpotifyDisallows {
    bool interrupting_playback;
    bool pausing;
    bool resuming;
    bool seeking;
    bool skipping_next;
    bool skipping_prev;
    bool toggling_repeat_context;
    bool toggling_shuffle;
    bool toggling_repeat_track;
    bool transferring_playback;
};

struct SpotifyPlaybackState {
    std::optional<SpotifyDevice> device;
    std::string repeat_state;
    bool shuffle_state;
    std::optional<SpotifyContext> context;
    long long timestamp;
    int progress_ms;
    bool is_playing;
    SpotifyTrackOrEpisode item;
    std::string currently_playing_type;
    std::optional<SpotifyDisallows> actions;
};

struct SpotifyAvailableDevicesResponse {
    std::vector<SpotifyDevice> devices;
};

struct SpotifyPlayHistory {
    std::optional<SpotifyTrackResponse> track;
    std::string played_at;
    std::optional<SpotifyContext> context;
};

using SpotifyCursorPagingPlayHistory = SpotifyCursorPaging<SpotifyPlayHistory>;

struct SpotifyQueue {
    SpotifyTrackOrEpisode currently_playing;
    std::vector<SpotifyTrackOrEpisode> queue;
};

// ---- request bodies

struct SpotifyChangePlaylistDetailsRequest {
    std::optional<std::string> name;
    std::optional<bool> is_public;
    std::optional<bool> collaborative;
    std::optional<std::string> description;
};

struct SpotifyAddPlaylistItemsRequest {
    std::optional<std::vector<std::string>> uris;
    std::optional<int> position;
};

struct SpotifyUpdatePlaylistItemsRequest {
    std::optional<std::vector<std::string>> uris;
    std::optional<int> range_start;
    std::optional<int> insert_before;
    std::optional<int> range_length;
    std::optional<std::string> snapshot_id;
};

struct SpotifyRemovePlaylistItemsRequestItems {
    std::optional<std::string> uri;
};

struct SpotifyRemovePlaylistItemsRequest {
    std::vector<SpotifyRemovePlaylistItemsRequestItems> items;
    std::optional<std::string> snapshot_id;
};

struct SpotifyCreatePlaylistRequest {
    std::string name;
    std::optional<bool> is_public;
    std::optional<bool> collaborative;
    std::optional<std::string> description;
};

struct SpotifyTransferPlaybackRequest {
    std::vector<std::string> device_ids;
    std::optional<bool> play;
};

struct SpotifyStartPlaybackRequest {
    std::optional<std::string> context_uri;
    std::optional<std::vector<std::string>> uris;
    std::optional<std::string> offset;  // raw JSON object
    std::optional<int> position_ms;
};

#endif //DEARSPOTIFY_SPOTIFY_TYPES_H
