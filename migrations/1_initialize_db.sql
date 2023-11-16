-- PRAGMA foreign_keys = ON;

CREATE TABLE IF NOT EXISTS track (
    id BIGINT NOT NULL UNIQUE,
    title TEXT NOT NULL,
    duration INT NOT NULL,
    cover_url TEXT NOT NULL,
    PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS artist (
    id BIGINT NOT NULL UNIQUE,
    name TEXT NOT NULL,
    cover_url TEXT NOT NULL,
    PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS playlist (
    id BIGINT NOT NULL UNIQUE,
    name TEXT NOT NULL,
    cover_url TEXT NOT NULL,
    PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS artist_track (
    artist_id BIGINT NOT NULL,
    track_id BIGINT NOT NULL,
    artist_priority BIGINT NOT NULL,
    track_priority BIGINT NOT NULL,
    PRIMARY KEY (artist_id, track_id),
    FOREIGN KEY (artist_id) REFERENCES artist(id) ON DELETE CASCADE,
    FOREIGN KEY (track_id) REFERENCES track(id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS playlist_track (
    playlist_id BIGINT NOT NULL,
    track_id BIGINT NOT NULL,
    track_priority BIGINT NOT NULL,
    PRIMARY KEY (playlist_id, track_id),
    FOREIGN KEY (playlist_id) REFERENCES playlist(id) ON DELETE CASCADE,
    FOREIGN KEY (track_id) REFERENCES track(id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS artist_playlist (
    artist_id BIGINT NOT NULL,
    playlist_id BIGINT NOT NULL,
    playlist_priority BIGINT NOT NULL,
    PRIMARY KEY (playlist_id, artist_id),
    FOREIGN KEY (playlist_id) REFERENCES playlist(id) ON DELETE CASCADE,
    FOREIGN KEY (artist_id) REFERENCES artist(id) ON DELETE CASCADE
);
