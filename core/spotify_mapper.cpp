#include "spotify_mapper.h"

using json = nlohmann::json;

namespace {
    bool has(const json& j, const char* key) {
        return j.contains(key) && !j.at(key).is_null();
    }

    template <typename T>
    T get_or(const json& j, const char* key) {
        return has(j, key) ? j.at(key).get<T>() : T{};
    }

    template <typename T>
    std::optional<T> get_optional(const json& j, const char* key) {
        if (!has(j, key))
            return std::nullopt;

        return j.at(key).get<T>();
    }

    template <typename T, typename F>
    SpotifyPaging<T> map_paging(const json& j, F map_item) {
        SpotifyPaging<T> r;

        r.href = j.at("href").get<std::string>();
        r.limit = j.at("limit").get<int>();
        r.offset = j.at("offset").get<int>();
        r.total = j.at("total").get<int>();

        r.next = get_or<std::string>(j, "next");
        r.previous = get_or<std::string>(j, "previous");

        const auto& items = j.at("items");
        r.items.reserve(items.size());

        for (const auto& item : items)
            r.items.push_back(map_item(item));

        return r;
    }

    template <typename T, typename F>
    SpotifyCursorPaging<T> map_cursor_paging(const json& j, F map_item) {
        SpotifyCursorPaging<T> r;

        r.href = get_or<std::string>(j, "href");
        r.limit = get_or<int>(j, "limit");
        r.next = get_or<std::string>(j, "next");
        r.total = get_or<int>(j, "total");

        if (has(j, "cursors")) {
            r.cursors.after = get_or<std::string>(j.at("cursors"), "after");
            r.cursors.before = get_or<std::string>(j.at("cursors"), "before");
        }

        if (has(j, "items")) {
            for (const auto& item : j.at("items"))
                r.items.push_back(map_item(item));
        }

        return r;
    }

    SpotifyExternalUrl map_SpotifyExternalUrl(const json& j) {
        SpotifyExternalUrl r;

        r.spotify = get_or<std::string>(j, "spotify");

        return r;
    }

    SpotifyImage map_SpotifyImage(const json& j) {
        SpotifyImage r;

        r.url = j.at("url").get<std::string>();
        r.height = get_optional<int>(j, "height");
        r.width = get_optional<int>(j, "width");

        return r;
    }

    SpotifyAlbumRestrictions map_SpotifyAlbumRestrictions(const json& j) {
        SpotifyAlbumRestrictions r;

        r.reason = get_or<std::string>(j, "reason");

        return r;
    }

    SpotifySimplifiedArtist map_SpotifySimplifiedArtist(const json& j) {
        SpotifySimplifiedArtist r;

        if (has(j, "external_urls"))
            r.external_urls = map_SpotifyExternalUrl(j.at("external_urls"));
        r.href = get_or<std::string>(j, "href");
        r.id = get_or<std::string>(j, "id");
        r.name = get_or<std::string>(j, "name");
        r.type = get_or<std::string>(j, "type");
        r.uri = get_or<std::string>(j, "uri");

        return r;
    }

    SpotifyTrackRestrictions map_SpotifyTrackRestrictions(const json& j) {
        SpotifyTrackRestrictions r;

        r.reason = get_or<std::string>(j, "reason");

        return r;
    }

    SpotifySimplifiedTrack map_SpotifySimplifiedTrack(const json& j) {
        SpotifySimplifiedTrack r;

        if (has(j, "artists")) {
            for (const auto& e : j.at("artists"))
                r.artists.push_back(map_SpotifySimplifiedArtist(e));
        }
        r.disc_number = get_or<int>(j, "disc_number");
        r.duration_ms = get_or<int>(j, "duration_ms");
        r.is_explicit = get_or<bool>(j, "explicit");
        if (has(j, "external_urls"))
            r.external_urls = map_SpotifyExternalUrl(j.at("external_urls"));
        r.href = get_or<std::string>(j, "href");
        r.id = get_or<std::string>(j, "id");
        r.is_playable = get_or<bool>(j, "is_playable");
        if (has(j, "restrictions"))
            r.restrictions = map_SpotifyTrackRestrictions(j.at("restrictions"));
        r.name = get_or<std::string>(j, "name");
        r.track_number = get_or<int>(j, "track_number");
        r.type = get_or<std::string>(j, "type");
        r.uri = get_or<std::string>(j, "uri");
        r.is_local = get_or<bool>(j, "is_local");

        return r;
    }

    SpotifyGetAlbumTracksResponse map_SpotifyGetAlbumTracksResponse(const json& j) {
        return map_paging<SpotifySimplifiedTrack>(j, map_SpotifySimplifiedTrack);
    }

    SpotifyCopyright map_SpotifyCopyright(const json& j) {
        SpotifyCopyright r;

        r.text = get_or<std::string>(j, "text");
        r.type = get_or<std::string>(j, "type");

        return r;
    }

    SpotifyExternalIds map_SpotifyExternalIds(const json& j) {
        SpotifyExternalIds r;

        r.isrc = get_or<std::string>(j, "isrc");
        r.ean = get_or<std::string>(j, "ean");
        r.upc = get_or<std::string>(j, "upc");

        return r;
    }

    SpotifyAlbumResponse map_SpotifyAlbumResponse(const json& j) {
        SpotifyAlbumResponse r;

        r.album_type = j.at("album_type").get<std::string>();
        r.total_tracks = j.at("total_tracks").get<int>();
        r.external_urls = map_SpotifyExternalUrl(j.at("external_urls"));
        r.href = j.at("href").get<std::string>();
        r.id = j.at("id").get<std::string>();
        for (const auto& e : j.at("images"))
            r.images.push_back(map_SpotifyImage(e));
        r.name = j.at("name").get<std::string>();
        r.release_date = j.at("release_date").get<std::string>();
        r.release_date_precision = j.at("release_date_precision").get<std::string>();
        if (has(j, "restrictions"))
            r.restrictions = map_SpotifyAlbumRestrictions(j.at("restrictions"));
        r.type = j.at("type").get<std::string>();
        r.uri = j.at("uri").get<std::string>();
        for (const auto& e : j.at("artists"))
            r.artists.push_back(map_SpotifySimplifiedArtist(e));
        r.tracks = map_SpotifyGetAlbumTracksResponse(j.at("tracks"));
        for (const auto& e : j.at("copyrights"))
            r.copyrights.push_back(map_SpotifyCopyright(e));
        r.external_ids = map_SpotifyExternalIds(j.at("external_ids"));

        return r;
    }

    SpotifyArtistResponse map_SpotifyArtistResponse(const json& j) {
        SpotifyArtistResponse r;

        if (has(j, "external_urls"))
            r.external_urls = map_SpotifyExternalUrl(j.at("external_urls"));
        r.href = get_or<std::string>(j, "href");
        r.id = get_or<std::string>(j, "id");
        if (has(j, "images")) {
            for (const auto& e : j.at("images"))
                r.images.push_back(map_SpotifyImage(e));
        }
        r.name = get_or<std::string>(j, "name");
        r.type = get_or<std::string>(j, "type");
        r.uri = get_or<std::string>(j, "uri");

        return r;
    }

    SpotifyAlbum map_SpotifyAlbum(const json& j) {
        SpotifyAlbum r;

        r.album_type = j.at("album_type").get<std::string>();
        r.total_tracks = j.at("total_tracks").get<int>();
        r.external_urls = map_SpotifyExternalUrl(j.at("external_urls"));
        r.href = j.at("href").get<std::string>();
        r.id = j.at("id").get<std::string>();
        for (const auto& e : j.at("images"))
            r.images.push_back(map_SpotifyImage(e));
        r.name = j.at("name").get<std::string>();
        r.release_date = j.at("release_date").get<std::string>();
        r.release_date_precision = j.at("release_date_precision").get<std::string>();
        if (has(j, "restrictions"))
            r.restrictions = map_SpotifyAlbumRestrictions(j.at("restrictions"));
        r.type = j.at("type").get<std::string>();
        r.uri = j.at("uri").get<std::string>();
        for (const auto& e : j.at("artists"))
            r.artists.push_back(map_SpotifySimplifiedArtist(e));

        return r;
    }

    SpotifyGetAlbumsResponse map_SpotifyGetAlbumsResponse(const json& j) {
        return map_paging<SpotifyAlbum>(j, map_SpotifyAlbum);
    }

    SpotifyResumePoint map_SpotifyResumePoint(const json& j) {
        SpotifyResumePoint r;

        r.fully_played = get_or<bool>(j, "fully_played");
        r.resume_position_ms = get_or<int>(j, "resume_position_ms");

        return r;
    }

    SpotifyEpisodeRestriction map_SpotifyEpisodeRestriction(const json& j) {
        SpotifyEpisodeRestriction r;

        r.reason = get_or<std::string>(j, "reason");

        return r;
    }

    SpotifySimplifiedEpisode map_SpotifySimplifiedEpisode(const json& j) {
        SpotifySimplifiedEpisode r;

        r.description = j.at("description").get<std::string>();
        r.html_description = j.at("html_description").get<std::string>();
        r.duration_ms = j.at("duration_ms").get<int>();
        r.is_explicit = j.at("explicit").get<bool>();
        r.external_urls = map_SpotifyExternalUrl(j.at("external_urls"));
        r.href = j.at("href").get<std::string>();
        r.id = j.at("id").get<std::string>();
        for (const auto& e : j.at("images"))
            r.images.push_back(map_SpotifyImage(e));
        r.is_externally_hosted = j.at("is_externally_hosted").get<bool>();
        r.is_playable = j.at("is_playable").get<bool>();
        r.languages = j.at("languages").get<std::vector<std::string>>();
        r.name = j.at("name").get<std::string>();
        r.release_date = j.at("release_date").get<std::string>();
        r.release_date_precision = j.at("release_date_precision").get<std::string>();
        if (has(j, "resume_point"))
            r.resume_point = map_SpotifyResumePoint(j.at("resume_point"));
        r.type = j.at("type").get<std::string>();
        r.uri = j.at("uri").get<std::string>();
        if (has(j, "restrictions"))
            r.restrictions = map_SpotifyEpisodeRestriction(j.at("restrictions"));

        return r;
    }

    SpotifyPagingSimplifiedEpisode map_SpotifyPagingSimplifiedEpisode(const json& j) {
        return map_paging<SpotifySimplifiedEpisode>(j, map_SpotifySimplifiedEpisode);
    }

    SpotifyShow map_SpotifyShow(const json& j) {
        SpotifyShow r;

        for (const auto& e : j.at("copyrights"))
            r.copyrights.push_back(map_SpotifyCopyright(e));
        r.description = j.at("description").get<std::string>();
        r.html_description = j.at("html_description").get<std::string>();
        r.is_explicit = j.at("explicit").get<bool>();
        r.external_urls = map_SpotifyExternalUrl(j.at("external_urls"));
        r.href = j.at("href").get<std::string>();
        r.id = j.at("id").get<std::string>();
        for (const auto& e : j.at("images"))
            r.images.push_back(map_SpotifyImage(e));
        r.is_externally_hosted = j.at("is_externally_hosted").get<bool>();
        r.languages = j.at("languages").get<std::vector<std::string>>();
        r.media_type = j.at("media_type").get<std::string>();
        r.name = j.at("name").get<std::string>();
        r.type = j.at("type").get<std::string>();
        r.uri = j.at("uri").get<std::string>();
        r.total_episodes = j.at("total_episodes").get<int>();
        r.episodes = map_SpotifyPagingSimplifiedEpisode(j.at("episodes"));

        return r;
    }

    SpotifySimplifiedShow map_SpotifySimplifiedShow(const json& j) {
        SpotifySimplifiedShow r;

        for (const auto& e : j.at("copyrights"))
            r.copyrights.push_back(map_SpotifyCopyright(e));
        r.description = j.at("description").get<std::string>();
        r.html_description = j.at("html_description").get<std::string>();
        r.is_explicit = j.at("explicit").get<bool>();
        r.external_urls = map_SpotifyExternalUrl(j.at("external_urls"));
        r.href = j.at("href").get<std::string>();
        r.id = j.at("id").get<std::string>();
        for (const auto& e : j.at("images"))
            r.images.push_back(map_SpotifyImage(e));
        r.is_externally_hosted = j.at("is_externally_hosted").get<bool>();
        r.languages = j.at("languages").get<std::vector<std::string>>();
        r.media_type = j.at("media_type").get<std::string>();
        r.name = j.at("name").get<std::string>();
        r.type = j.at("type").get<std::string>();
        r.uri = j.at("uri").get<std::string>();
        r.total_episodes = j.at("total_episodes").get<int>();

        return r;
    }

    SpotifyEpisode map_SpotifyEpisode(const json& j) {
        SpotifyEpisode r;

        r.description = j.at("description").get<std::string>();
        r.html_description = j.at("html_description").get<std::string>();
        r.duration_ms = j.at("duration_ms").get<int>();
        r.is_explicit = j.at("explicit").get<bool>();
        r.external_urls = map_SpotifyExternalUrl(j.at("external_urls"));
        r.href = j.at("href").get<std::string>();
        r.id = j.at("id").get<std::string>();
        for (const auto& e : j.at("images"))
            r.images.push_back(map_SpotifyImage(e));
        r.is_externally_hosted = j.at("is_externally_hosted").get<bool>();
        r.is_playable = j.at("is_playable").get<bool>();
        r.languages = j.at("languages").get<std::vector<std::string>>();
        r.name = j.at("name").get<std::string>();
        r.release_date = j.at("release_date").get<std::string>();
        r.release_date_precision = j.at("release_date_precision").get<std::string>();
        if (has(j, "resume_point"))
            r.resume_point = map_SpotifyResumePoint(j.at("resume_point"));
        r.type = j.at("type").get<std::string>();
        r.uri = j.at("uri").get<std::string>();
        if (has(j, "restrictions"))
            r.restrictions = map_SpotifyEpisodeRestriction(j.at("restrictions"));
        r.show = map_SpotifySimplifiedShow(j.at("show"));

        return r;
    }

    SpotifyAuthor map_SpotifyAuthor(const json& j) {
        SpotifyAuthor r;

        r.name = get_or<std::string>(j, "name");

        return r;
    }

    SpotifyNarrator map_SpotifyNarrator(const json& j) {
        SpotifyNarrator r;

        r.name = get_or<std::string>(j, "name");

        return r;
    }

    SpotifyChapterRestriction map_SpotifyChapterRestriction(const json& j) {
        SpotifyChapterRestriction r;

        r.reason = get_or<std::string>(j, "reason");

        return r;
    }

    SpotifySimplifiedChapter map_SpotifySimplifiedChapter(const json& j) {
        SpotifySimplifiedChapter r;

        r.chapter_number = j.at("chapter_number").get<int>();
        r.description = j.at("description").get<std::string>();
        r.html_description = j.at("html_description").get<std::string>();
        r.duration_ms = j.at("duration_ms").get<int>();
        r.is_explicit = j.at("explicit").get<bool>();
        r.external_urls = map_SpotifyExternalUrl(j.at("external_urls"));
        r.href = j.at("href").get<std::string>();
        r.id = j.at("id").get<std::string>();
        for (const auto& e : j.at("images"))
            r.images.push_back(map_SpotifyImage(e));
        r.is_playable = j.at("is_playable").get<bool>();
        r.languages = j.at("languages").get<std::vector<std::string>>();
        r.name = j.at("name").get<std::string>();
        r.release_date = j.at("release_date").get<std::string>();
        r.release_date_precision = j.at("release_date_precision").get<std::string>();
        if (has(j, "resume_point"))
            r.resume_point = map_SpotifyResumePoint(j.at("resume_point"));
        r.type = j.at("type").get<std::string>();
        r.uri = j.at("uri").get<std::string>();
        if (has(j, "restrictions"))
            r.restrictions = map_SpotifyChapterRestriction(j.at("restrictions"));

        return r;
    }

    SpotifyPagingSimplifiedChapter map_SpotifyPagingSimplifiedChapter(const json& j) {
        return map_paging<SpotifySimplifiedChapter>(j, map_SpotifySimplifiedChapter);
    }

    SpotifyAudiobook map_SpotifyAudiobook(const json& j) {
        SpotifyAudiobook r;

        for (const auto& e : j.at("authors"))
            r.authors.push_back(map_SpotifyAuthor(e));
        for (const auto& e : j.at("copyrights"))
            r.copyrights.push_back(map_SpotifyCopyright(e));
        r.description = j.at("description").get<std::string>();
        r.html_description = j.at("html_description").get<std::string>();
        r.edition = get_or<std::string>(j, "edition");
        r.is_explicit = j.at("explicit").get<bool>();
        r.external_urls = map_SpotifyExternalUrl(j.at("external_urls"));
        r.href = j.at("href").get<std::string>();
        r.id = j.at("id").get<std::string>();
        for (const auto& e : j.at("images"))
            r.images.push_back(map_SpotifyImage(e));
        r.languages = j.at("languages").get<std::vector<std::string>>();
        r.media_type = j.at("media_type").get<std::string>();
        r.name = j.at("name").get<std::string>();
        for (const auto& e : j.at("narrators"))
            r.narrators.push_back(map_SpotifyNarrator(e));
        r.type = j.at("type").get<std::string>();
        r.uri = j.at("uri").get<std::string>();
        r.total_chapters = j.at("total_chapters").get<int>();
        r.chapters = map_SpotifyPagingSimplifiedChapter(j.at("chapters"));

        return r;
    }

    SpotifySimplifiedAudiobook map_SpotifySimplifiedAudiobook(const json& j) {
        SpotifySimplifiedAudiobook r;

        for (const auto& e : j.at("authors"))
            r.authors.push_back(map_SpotifyAuthor(e));
        for (const auto& e : j.at("copyrights"))
            r.copyrights.push_back(map_SpotifyCopyright(e));
        r.description = j.at("description").get<std::string>();
        r.html_description = j.at("html_description").get<std::string>();
        r.edition = get_or<std::string>(j, "edition");
        r.is_explicit = j.at("explicit").get<bool>();
        r.external_urls = map_SpotifyExternalUrl(j.at("external_urls"));
        r.href = j.at("href").get<std::string>();
        r.id = j.at("id").get<std::string>();
        for (const auto& e : j.at("images"))
            r.images.push_back(map_SpotifyImage(e));
        r.languages = j.at("languages").get<std::vector<std::string>>();
        r.media_type = j.at("media_type").get<std::string>();
        r.name = j.at("name").get<std::string>();
        for (const auto& e : j.at("narrators"))
            r.narrators.push_back(map_SpotifyNarrator(e));
        r.type = j.at("type").get<std::string>();
        r.uri = j.at("uri").get<std::string>();
        r.total_chapters = j.at("total_chapters").get<int>();

        return r;
    }

    SpotifyPagingSimplifiedAudiobook map_SpotifyPagingSimplifiedAudiobook(const json& j) {
        return map_paging<SpotifySimplifiedAudiobook>(j, map_SpotifySimplifiedAudiobook);
    }

    SpotifyChapter map_SpotifyChapter(const json& j) {
        SpotifyChapter r;

        r.chapter_number = j.at("chapter_number").get<int>();
        r.description = j.at("description").get<std::string>();
        r.html_description = j.at("html_description").get<std::string>();
        r.duration_ms = j.at("duration_ms").get<int>();
        r.is_explicit = j.at("explicit").get<bool>();
        r.external_urls = map_SpotifyExternalUrl(j.at("external_urls"));
        r.href = j.at("href").get<std::string>();
        r.id = j.at("id").get<std::string>();
        for (const auto& e : j.at("images"))
            r.images.push_back(map_SpotifyImage(e));
        r.is_playable = j.at("is_playable").get<bool>();
        r.languages = j.at("languages").get<std::vector<std::string>>();
        r.name = j.at("name").get<std::string>();
        r.release_date = j.at("release_date").get<std::string>();
        r.release_date_precision = j.at("release_date_precision").get<std::string>();
        if (has(j, "resume_point"))
            r.resume_point = map_SpotifyResumePoint(j.at("resume_point"));
        r.type = j.at("type").get<std::string>();
        r.uri = j.at("uri").get<std::string>();
        if (has(j, "restrictions"))
            r.restrictions = map_SpotifyChapterRestriction(j.at("restrictions"));
        r.audiobook = map_SpotifySimplifiedAudiobook(j.at("audiobook"));

        return r;
    }

    SpotifySimplifiedAlbum map_SpotifySimplifiedAlbum(const json& j) {
        SpotifySimplifiedAlbum r;

        r.album_type = j.at("album_type").get<std::string>();
        r.total_tracks = j.at("total_tracks").get<int>();
        r.external_urls = map_SpotifyExternalUrl(j.at("external_urls"));
        r.href = j.at("href").get<std::string>();
        r.id = j.at("id").get<std::string>();
        for (const auto& e : j.at("images"))
            r.images.push_back(map_SpotifyImage(e));
        r.name = j.at("name").get<std::string>();
        r.release_date = j.at("release_date").get<std::string>();
        r.release_date_precision = j.at("release_date_precision").get<std::string>();
        if (has(j, "restrictions"))
            r.restrictions = map_SpotifyAlbumRestrictions(j.at("restrictions"));
        r.type = j.at("type").get<std::string>();
        r.uri = j.at("uri").get<std::string>();
        for (const auto& e : j.at("artists"))
            r.artists.push_back(map_SpotifySimplifiedArtist(e));

        return r;
    }

    SpotifyTrackResponse map_SpotifyTrackResponse(const json& j) {
        SpotifyTrackResponse r;

        if (has(j, "album"))
            r.album = map_SpotifySimplifiedAlbum(j.at("album"));
        if (has(j, "artists")) {
            for (const auto& e : j.at("artists"))
                r.artists.push_back(map_SpotifySimplifiedArtist(e));
        }
        r.disc_number = get_or<int>(j, "disc_number");
        r.duration_ms = get_or<int>(j, "duration_ms");
        r.is_explicit = get_or<bool>(j, "explicit");
        if (has(j, "external_ids"))
            r.external_ids = map_SpotifyExternalIds(j.at("external_ids"));
        if (has(j, "external_urls"))
            r.external_urls = map_SpotifyExternalUrl(j.at("external_urls"));
        r.href = get_or<std::string>(j, "href");
        r.id = get_or<std::string>(j, "id");
        r.is_playable = get_or<bool>(j, "is_playable");
        if (has(j, "restrictions"))
            r.restrictions = map_SpotifyTrackRestrictions(j.at("restrictions"));
        r.name = get_or<std::string>(j, "name");
        r.track_number = get_or<int>(j, "track_number");
        r.type = get_or<std::string>(j, "type");
        r.uri = get_or<std::string>(j, "uri");
        r.is_local = get_or<bool>(j, "is_local");

        return r;
    }

    SpotifyPagingTrack map_SpotifyPagingTrack(const json& j) {
        return map_paging<SpotifyTrackResponse>(j, map_SpotifyTrackResponse);
    }

    SpotifyPagingArtist map_SpotifyPagingArtist(const json& j) {
        return map_paging<SpotifyArtistResponse>(j, map_SpotifyArtistResponse);
    }

    SpotifyPagingSimplifiedAlbum map_SpotifyPagingSimplifiedAlbum(const json& j) {
        return map_paging<SpotifySimplifiedAlbum>(j, map_SpotifySimplifiedAlbum);
    }

    SpotifyPlaylistOwner map_SpotifyPlaylistOwner(const json& j) {
        SpotifyPlaylistOwner r;

        if (has(j, "external_urls"))
            r.external_urls = map_SpotifyExternalUrl(j.at("external_urls"));
        r.href = get_or<std::string>(j, "href");
        r.id = get_or<std::string>(j, "id");
        r.type = get_or<std::string>(j, "type");
        r.uri = get_or<std::string>(j, "uri");
        r.display_name = get_or<std::string>(j, "display_name");

        return r;
    }

    SpotifyPlaylistTracksRef map_SpotifyPlaylistTracksRef(const json& j) {
        SpotifyPlaylistTracksRef r;

        r.href = get_or<std::string>(j, "href");
        r.total = get_or<int>(j, "total");

        return r;
    }

    SpotifySimplifiedPlaylist map_SpotifySimplifiedPlaylist(const json& j) {
        SpotifySimplifiedPlaylist r;

        r.collaborative = get_or<bool>(j, "collaborative");
        r.description = get_or<std::string>(j, "description");
        if (has(j, "external_urls"))
            r.external_urls = map_SpotifyExternalUrl(j.at("external_urls"));
        r.href = get_or<std::string>(j, "href");
        r.id = get_or<std::string>(j, "id");
        if (has(j, "images")) {
            for (const auto& e : j.at("images"))
                r.images.push_back(map_SpotifyImage(e));
        }
        r.name = get_or<std::string>(j, "name");
        if (has(j, "owner"))
            r.owner = map_SpotifyPlaylistOwner(j.at("owner"));
        r.is_public = get_or<bool>(j, "public");
        r.snapshot_id = get_or<std::string>(j, "snapshot_id");
        if (has(j, "items"))
            r.items = map_SpotifyPlaylistTracksRef(j.at("items"));
        r.type = get_or<std::string>(j, "type");
        r.uri = get_or<std::string>(j, "uri");

        return r;
    }

    SpotifyPagingPlaylist map_SpotifyPagingPlaylist(const json& j) {
        return map_paging<SpotifySimplifiedPlaylist>(j, map_SpotifySimplifiedPlaylist);
    }

    SpotifyPagingSimplifiedShow map_SpotifyPagingSimplifiedShow(const json& j) {
        return map_paging<SpotifySimplifiedShow>(j, map_SpotifySimplifiedShow);
    }

    SpotifySearchResponse map_SpotifySearchResponse(const json& j) {
        SpotifySearchResponse r;

        if (has(j, "tracks"))
            r.tracks = map_SpotifyPagingTrack(j.at("tracks"));
        if (has(j, "artists"))
            r.artists = map_SpotifyPagingArtist(j.at("artists"));
        if (has(j, "albums"))
            r.albums = map_SpotifyPagingSimplifiedAlbum(j.at("albums"));
        if (has(j, "playlists"))
            r.playlists = map_SpotifyPagingPlaylist(j.at("playlists"));
        if (has(j, "shows"))
            r.shows = map_SpotifyPagingSimplifiedShow(j.at("shows"));
        if (has(j, "episodes"))
            r.episodes = map_SpotifyPagingSimplifiedEpisode(j.at("episodes"));
        if (has(j, "audiobooks"))
            r.audiobooks = map_SpotifyPagingSimplifiedAudiobook(j.at("audiobooks"));

        return r;
    }

    SpotifyPrivateUser map_SpotifyPrivateUser(const json& j) {
        SpotifyPrivateUser r;

        r.account_id = get_or<std::string>(j, "account_id");
        r.display_name = get_or<std::string>(j, "display_name");
        if (has(j, "external_urls"))
            r.external_urls = map_SpotifyExternalUrl(j.at("external_urls"));
        r.href = get_or<std::string>(j, "href");
        r.id = get_or<std::string>(j, "id");
        if (has(j, "images")) {
            for (const auto& e : j.at("images"))
                r.images.push_back(map_SpotifyImage(e));
        }
        r.type = get_or<std::string>(j, "type");
        r.uri = get_or<std::string>(j, "uri");

        return r;
    }

    SpotifyPlaylistUser map_SpotifyPlaylistUser(const json& j) {
        SpotifyPlaylistUser r;

        if (has(j, "external_urls"))
            r.external_urls = map_SpotifyExternalUrl(j.at("external_urls"));
        r.href = get_or<std::string>(j, "href");
        r.id = get_or<std::string>(j, "id");
        r.type = get_or<std::string>(j, "type");
        r.uri = get_or<std::string>(j, "uri");

        return r;
    }

    SpotifyTrackOrEpisode map_SpotifyTrackOrEpisode(const json& j) {
        const auto type = j.at("type").get<std::string>();

        if (type == "track")
            return map_SpotifyTrackResponse(j);
        if (type == "episode")
            return map_SpotifyEpisode(j);

        return std::monostate{};
    }

    SpotifyPlaylistTrack map_SpotifyPlaylistTrack(const json& j) {
        SpotifyPlaylistTrack r;

        r.added_at = get_or<std::string>(j, "added_at");
        if (has(j, "added_by"))
            r.added_by = map_SpotifyPlaylistUser(j.at("added_by"));
        r.is_local = get_or<bool>(j, "is_local");
        if (has(j, "item"))
            r.item = map_SpotifyTrackOrEpisode(j.at("item"));

        return r;
    }

    SpotifyPagingPlaylistTrack map_SpotifyPagingPlaylistTrack(const json& j) {
        return map_paging<SpotifyPlaylistTrack>(j, map_SpotifyPlaylistTrack);
    }

    SpotifyPlaylist map_SpotifyPlaylist(const json& j) {
        SpotifyPlaylist r;

        r.collaborative = get_or<bool>(j, "collaborative");
        r.description = get_or<std::string>(j, "description");
        if (has(j, "external_urls"))
            r.external_urls = map_SpotifyExternalUrl(j.at("external_urls"));
        r.href = get_or<std::string>(j, "href");
        r.id = get_or<std::string>(j, "id");
        if (has(j, "images")) {
            for (const auto& e : j.at("images"))
                r.images.push_back(map_SpotifyImage(e));
        }
        r.name = get_or<std::string>(j, "name");
        if (has(j, "owner"))
            r.owner = map_SpotifyPlaylistOwner(j.at("owner"));
        r.is_public = get_or<bool>(j, "public");
        r.snapshot_id = get_or<std::string>(j, "snapshot_id");
        if (has(j, "items"))
            r.items = map_SpotifyPagingPlaylistTrack(j.at("items"));
        r.type = get_or<std::string>(j, "type");
        r.uri = get_or<std::string>(j, "uri");

        return r;
    }

    SpotifySnapshotResponse map_SpotifySnapshotResponse(const json& j) {
        SpotifySnapshotResponse r;

        r.snapshot_id = get_or<std::string>(j, "snapshot_id");

        return r;
    }

    SpotifySavedAlbum map_SpotifySavedAlbum(const json& j) {
        SpotifySavedAlbum r;

        r.added_at = get_or<std::string>(j, "added_at");
        if (has(j, "album"))
            r.album = map_SpotifyAlbumResponse(j.at("album"));

        return r;
    }

    SpotifyPagingSavedAlbum map_SpotifyPagingSavedAlbum(const json& j) {
        return map_paging<SpotifySavedAlbum>(j, map_SpotifySavedAlbum);
    }

    SpotifySavedTrack map_SpotifySavedTrack(const json& j) {
        SpotifySavedTrack r;

        r.added_at = get_or<std::string>(j, "added_at");
        if (has(j, "track"))
            r.track = map_SpotifyTrackResponse(j.at("track"));

        return r;
    }

    SpotifyPagingSavedTrack map_SpotifyPagingSavedTrack(const json& j) {
        return map_paging<SpotifySavedTrack>(j, map_SpotifySavedTrack);
    }

    SpotifySavedEpisode map_SpotifySavedEpisode(const json& j) {
        SpotifySavedEpisode r;

        r.added_at = get_or<std::string>(j, "added_at");
        if (has(j, "episode"))
            r.episode = map_SpotifyEpisode(j.at("episode"));

        return r;
    }

    SpotifyPagingSavedEpisode map_SpotifyPagingSavedEpisode(const json& j) {
        return map_paging<SpotifySavedEpisode>(j, map_SpotifySavedEpisode);
    }

    SpotifySavedShow map_SpotifySavedShow(const json& j) {
        SpotifySavedShow r;

        r.added_at = get_or<std::string>(j, "added_at");
        if (has(j, "show"))
            r.show = map_SpotifySimplifiedShow(j.at("show"));

        return r;
    }

    SpotifyPagingSavedShow map_SpotifyPagingSavedShow(const json& j) {
        return map_paging<SpotifySavedShow>(j, map_SpotifySavedShow);
    }

    SpotifyArtistOrTrack map_SpotifyArtistOrTrack(const json& j) {
        const auto type = j.at("type").get<std::string>();

        if (type == "artist")
            return map_SpotifyArtistResponse(j);
        if (type == "track")
            return map_SpotifyTrackResponse(j);

        return std::monostate{};
    }

    SpotifyGetTopItemsResponse map_SpotifyGetTopItemsResponse(const json& j) {
        return map_paging<SpotifyArtistOrTrack>(j, map_SpotifyArtistOrTrack);
    }

    SpotifyCursorPagingSimplifiedArtist map_SpotifyCursorPagingSimplifiedArtist(const json& j) {
        return map_cursor_paging<SpotifyArtistResponse>(j, map_SpotifyArtistResponse);
    }

    SpotifyFollowedArtistsResponse map_SpotifyFollowedArtistsResponse(const json& j) {
        SpotifyFollowedArtistsResponse r;

        r.artists = map_SpotifyCursorPagingSimplifiedArtist(j.at("artists"));

        return r;
    }

    SpotifyDevice map_SpotifyDevice(const json& j) {
        SpotifyDevice r;

        r.id = get_or<std::string>(j, "id");
        r.is_active = get_or<bool>(j, "is_active");
        r.is_private_session = get_or<bool>(j, "is_private_session");
        r.is_restricted = get_or<bool>(j, "is_restricted");
        r.name = get_or<std::string>(j, "name");
        r.type = get_or<std::string>(j, "type");
        r.volume_percent = get_optional<int>(j, "volume_percent");
        r.supports_volume = get_or<bool>(j, "supports_volume");

        return r;
    }

    SpotifyContext map_SpotifyContext(const json& j) {
        SpotifyContext r;

        r.type = get_or<std::string>(j, "type");
        r.href = get_or<std::string>(j, "href");
        if (has(j, "external_urls"))
            r.external_urls = map_SpotifyExternalUrl(j.at("external_urls"));
        r.uri = get_or<std::string>(j, "uri");

        return r;
    }

    SpotifyDisallows map_SpotifyDisallows(const json& j) {
        SpotifyDisallows r;

        r.interrupting_playback = get_or<bool>(j, "interrupting_playback");
        r.pausing = get_or<bool>(j, "pausing");
        r.resuming = get_or<bool>(j, "resuming");
        r.seeking = get_or<bool>(j, "seeking");
        r.skipping_next = get_or<bool>(j, "skipping_next");
        r.skipping_prev = get_or<bool>(j, "skipping_prev");
        r.toggling_repeat_context = get_or<bool>(j, "toggling_repeat_context");
        r.toggling_shuffle = get_or<bool>(j, "toggling_shuffle");
        r.toggling_repeat_track = get_or<bool>(j, "toggling_repeat_track");
        r.transferring_playback = get_or<bool>(j, "transferring_playback");

        return r;
    }

    SpotifyPlaybackState map_SpotifyPlaybackState(const json& j) {
        SpotifyPlaybackState r;

        if (has(j, "device"))
            r.device = map_SpotifyDevice(j.at("device"));
        r.repeat_state = get_or<std::string>(j, "repeat_state");
        r.shuffle_state = get_or<bool>(j, "shuffle_state");
        if (has(j, "context"))
            r.context = map_SpotifyContext(j.at("context"));
        r.timestamp = get_or<long long>(j, "timestamp");
        r.progress_ms = get_or<int>(j, "progress_ms");
        r.is_playing = get_or<bool>(j, "is_playing");
        if (has(j, "item"))
            r.item = map_SpotifyTrackOrEpisode(j.at("item"));
        r.currently_playing_type = get_or<std::string>(j, "currently_playing_type");
        if (has(j, "actions"))
            r.actions = map_SpotifyDisallows(j.at("actions"));

        return r;
    }

    SpotifyAvailableDevicesResponse map_SpotifyAvailableDevicesResponse(const json& j) {
        SpotifyAvailableDevicesResponse r;

        for (const auto& e : j.at("devices"))
            r.devices.push_back(map_SpotifyDevice(e));

        return r;
    }

    SpotifyPlayHistory map_SpotifyPlayHistory(const json& j) {
        SpotifyPlayHistory r;

        if (has(j, "track"))
            r.track = map_SpotifyTrackResponse(j.at("track"));
        r.played_at = get_or<std::string>(j, "played_at");
        if (has(j, "context"))
            r.context = map_SpotifyContext(j.at("context"));

        return r;
    }

    SpotifyCursorPagingPlayHistory map_SpotifyCursorPagingPlayHistory(const json& j) {
        return map_cursor_paging<SpotifyPlayHistory>(j, map_SpotifyPlayHistory);
    }

    SpotifyQueue map_SpotifyQueue(const json& j) {
        SpotifyQueue r;

        if (has(j, "currently_playing"))
            r.currently_playing = map_SpotifyTrackOrEpisode(j.at("currently_playing"));
        if (has(j, "queue")) {
            for (const auto& e : j.at("queue"))
                r.queue.push_back(map_SpotifyTrackOrEpisode(e));
        }

        return r;
    }

    json to_json_SpotifyChangePlaylistDetailsRequest(const SpotifyChangePlaylistDetailsRequest& r) {
        json j = json::object();

        if (r.name)
            j["name"] = *r.name;
        if (r.is_public)
            j["public"] = *r.is_public;
        if (r.collaborative)
            j["collaborative"] = *r.collaborative;
        if (r.description)
            j["description"] = *r.description;

        return j;
    }

    json to_json_SpotifyAddPlaylistItemsRequest(const SpotifyAddPlaylistItemsRequest& r) {
        json j = json::object();

        if (r.uris)
            j["uris"] = *r.uris;
        if (r.position)
            j["position"] = *r.position;

        return j;
    }

    json to_json_SpotifyUpdatePlaylistItemsRequest(const SpotifyUpdatePlaylistItemsRequest& r) {
        json j = json::object();

        if (r.uris)
            j["uris"] = *r.uris;
        if (r.range_start)
            j["range_start"] = *r.range_start;
        if (r.insert_before)
            j["insert_before"] = *r.insert_before;
        if (r.range_length)
            j["range_length"] = *r.range_length;
        if (r.snapshot_id)
            j["snapshot_id"] = *r.snapshot_id;

        return j;
    }

    json to_json_SpotifyRemovePlaylistItemsRequestItems(const SpotifyRemovePlaylistItemsRequestItems& r) {
        json j = json::object();

        if (r.uri)
            j["uri"] = *r.uri;

        return j;
    }

    json to_json_SpotifyRemovePlaylistItemsRequest(const SpotifyRemovePlaylistItemsRequest& r) {
        json j = json::object();

        j["items"] = json::array();
        for (const auto& e : r.items)
            j["items"].push_back(to_json_SpotifyRemovePlaylistItemsRequestItems(e));
        if (r.snapshot_id)
            j["snapshot_id"] = *r.snapshot_id;

        return j;
    }

    json to_json_SpotifyCreatePlaylistRequest(const SpotifyCreatePlaylistRequest& r) {
        json j = json::object();

        j["name"] = r.name;
        if (r.is_public)
            j["public"] = *r.is_public;
        if (r.collaborative)
            j["collaborative"] = *r.collaborative;
        if (r.description)
            j["description"] = *r.description;

        return j;
    }

    json to_json_SpotifyTransferPlaybackRequest(const SpotifyTransferPlaybackRequest& r) {
        json j = json::object();

        j["device_ids"] = r.device_ids;
        if (r.play)
            j["play"] = *r.play;

        return j;
    }

    json to_json_SpotifyStartPlaybackRequest(const SpotifyStartPlaybackRequest& r) {
        json j = json::object();

        if (r.context_uri)
            j["context_uri"] = *r.context_uri;
        if (r.uris)
            j["uris"] = *r.uris;
        if (r.offset)
            j["offset"] = json::parse(*r.offset);
        if (r.position_ms)
            j["position_ms"] = *r.position_ms;

        return j;
    }

}

SpotifyAuthResponse spotify_mapper::from_json_to_auth_response(const std::string& response) {
    auto j = json::parse(response);

    std::string access_token = j.at("access_token").get<std::string>();
    std::string token_type = j.at("token_type").get<std::string>();
    long expires_in = j.at("expires_in").get<long>();

    return SpotifyAuthResponse{.access_token = access_token, .token_type = token_type, .expires_in = expires_in};
}

SpotifyAlbumResponse spotify_mapper::from_json_to_get_album_response(const std::string& response) {
    return map_SpotifyAlbumResponse(json::parse(response));
}

SpotifyGetAlbumTracksResponse spotify_mapper::from_json_to_get_album_tracks_response(const std::string& response) {
    return map_SpotifyGetAlbumTracksResponse(json::parse(response));
}

SpotifyArtistResponse spotify_mapper::from_json_to_get_artist_response(const std::string& response) {
    return map_SpotifyArtistResponse(json::parse(response));
}

SpotifyGetAlbumsResponse spotify_mapper::from_json_to_get_artist_albums_response(const std::string& response) {
    return map_SpotifyGetAlbumsResponse(json::parse(response));
}

SpotifyShow spotify_mapper::from_json_to_get_show_response(const std::string& response) {
    return map_SpotifyShow(json::parse(response));
}

SpotifyPagingSimplifiedEpisode spotify_mapper::from_json_to_get_show_episodes_response(const std::string& response) {
    return map_SpotifyPagingSimplifiedEpisode(json::parse(response));
}

SpotifyEpisode spotify_mapper::from_json_to_get_episode_response(const std::string& response) {
    return map_SpotifyEpisode(json::parse(response));
}

SpotifyAudiobook spotify_mapper::from_json_to_get_audiobook_response(const std::string& response) {
    return map_SpotifyAudiobook(json::parse(response));
}

SpotifyPagingSimplifiedChapter spotify_mapper::from_json_to_get_audiobook_chapters_response(const std::string& response) {
    return map_SpotifyPagingSimplifiedChapter(json::parse(response));
}

SpotifyPagingSimplifiedAudiobook spotify_mapper::from_json_to_get_saved_audiobooks_response(const std::string& response) {
    return map_SpotifyPagingSimplifiedAudiobook(json::parse(response));
}

SpotifyChapter spotify_mapper::from_json_to_get_chapter_response(const std::string& response) {
    return map_SpotifyChapter(json::parse(response));
}

SpotifyTrackResponse spotify_mapper::from_json_to_get_track_response(const std::string& response) {
    return map_SpotifyTrackResponse(json::parse(response));
}

SpotifySearchResponse spotify_mapper::from_json_to_search_response(const std::string& response) {
    return map_SpotifySearchResponse(json::parse(response));
}

SpotifyPrivateUser spotify_mapper::from_json_to_get_current_user_response(const std::string& response) {
    return map_SpotifyPrivateUser(json::parse(response));
}

SpotifyPlaylist spotify_mapper::from_json_to_get_playlist_response(const std::string& response) {
    return map_SpotifyPlaylist(json::parse(response));
}

SpotifyPagingPlaylistTrack spotify_mapper::from_json_to_get_playlist_items_response(const std::string& response) {
    return map_SpotifyPagingPlaylistTrack(json::parse(response));
}

SpotifySnapshotResponse spotify_mapper::from_json_to_add_playlist_items_response(const std::string& response) {
    return map_SpotifySnapshotResponse(json::parse(response));
}

SpotifySnapshotResponse spotify_mapper::from_json_to_update_playlist_items_response(const std::string& response) {
    return map_SpotifySnapshotResponse(json::parse(response));
}

SpotifySnapshotResponse spotify_mapper::from_json_to_remove_playlist_items_response(const std::string& response) {
    return map_SpotifySnapshotResponse(json::parse(response));
}

SpotifyPagingPlaylist spotify_mapper::from_json_to_get_current_user_playlists_response(const std::string& response) {
    return map_SpotifyPagingPlaylist(json::parse(response));
}

SpotifyPlaylist spotify_mapper::from_json_to_create_playlist_response(const std::string& response) {
    return map_SpotifyPlaylist(json::parse(response));
}

std::vector<bool> spotify_mapper::from_json_to_check_library_contains_response(const std::string& response) {
    return json::parse(response).get<std::vector<bool>>();
}

SpotifyPagingSavedAlbum spotify_mapper::from_json_to_get_saved_albums_response(const std::string& response) {
    return map_SpotifyPagingSavedAlbum(json::parse(response));
}

SpotifyPagingSavedTrack spotify_mapper::from_json_to_get_saved_tracks_response(const std::string& response) {
    return map_SpotifyPagingSavedTrack(json::parse(response));
}

SpotifyPagingSavedEpisode spotify_mapper::from_json_to_get_saved_episodes_response(const std::string& response) {
    return map_SpotifyPagingSavedEpisode(json::parse(response));
}

SpotifyPagingSavedShow spotify_mapper::from_json_to_get_saved_shows_response(const std::string& response) {
    return map_SpotifyPagingSavedShow(json::parse(response));
}

SpotifyGetTopItemsResponse spotify_mapper::from_json_to_get_top_items_response(const std::string& response) {
    return map_SpotifyGetTopItemsResponse(json::parse(response));
}

std::vector<SpotifyImage> spotify_mapper::from_json_to_get_playlist_cover_response(const std::string& response) {
    std::vector<SpotifyImage> result;

    for (const auto& e : json::parse(response))
        result.push_back(map_SpotifyImage(e));

    return result;
}

SpotifyFollowedArtistsResponse spotify_mapper::from_json_to_get_followed_artists_response(const std::string& response) {
    return map_SpotifyFollowedArtistsResponse(json::parse(response));
}

SpotifyPlaybackState spotify_mapper::from_json_to_get_playback_state_response(const std::string& response) {
    return map_SpotifyPlaybackState(json::parse(response));
}

SpotifyAvailableDevicesResponse spotify_mapper::from_json_to_get_available_devices_response(const std::string& response) {
    return map_SpotifyAvailableDevicesResponse(json::parse(response));
}

SpotifyPlaybackState spotify_mapper::from_json_to_get_currently_playing_response(const std::string& response) {
    return map_SpotifyPlaybackState(json::parse(response));
}

SpotifyCursorPagingPlayHistory spotify_mapper::from_json_to_get_recently_played_response(const std::string& response) {
    return map_SpotifyCursorPagingPlayHistory(json::parse(response));
}

SpotifyQueue spotify_mapper::from_json_to_get_queue_response(const std::string& response) {
    return map_SpotifyQueue(json::parse(response));
}

std::string spotify_mapper::from_change_playlist_details_request_to_json(const SpotifyChangePlaylistDetailsRequest& request) {
    return to_json_SpotifyChangePlaylistDetailsRequest(request).dump();
}

std::string spotify_mapper::from_add_playlist_items_request_to_json(const SpotifyAddPlaylistItemsRequest& request) {
    return to_json_SpotifyAddPlaylistItemsRequest(request).dump();
}

std::string spotify_mapper::from_update_playlist_items_request_to_json(const SpotifyUpdatePlaylistItemsRequest& request) {
    return to_json_SpotifyUpdatePlaylistItemsRequest(request).dump();
}

std::string spotify_mapper::from_remove_playlist_items_request_to_json(const SpotifyRemovePlaylistItemsRequest& request) {
    return to_json_SpotifyRemovePlaylistItemsRequest(request).dump();
}

std::string spotify_mapper::from_create_playlist_request_to_json(const SpotifyCreatePlaylistRequest& request) {
    return to_json_SpotifyCreatePlaylistRequest(request).dump();
}

std::string spotify_mapper::from_transfer_playback_request_to_json(const SpotifyTransferPlaybackRequest& request) {
    return to_json_SpotifyTransferPlaybackRequest(request).dump();
}

std::string spotify_mapper::from_start_playback_request_to_json(const SpotifyStartPlaybackRequest& request) {
    return to_json_SpotifyStartPlaybackRequest(request).dump();
}
