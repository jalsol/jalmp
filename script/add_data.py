import csv
from datetime import timedelta
from sqlalchemy import create_engine, text

WRITE_TO_DB = True
DB_URL = ''

engine = create_engine(DB_URL)
conn = engine.connect()

class Track:
    def __init__(self, id, title, key, duration, cover):
        self.id = id
        self.title = title
        self.key = key
        self.duration = duration
        self.cover = cover

        self.cover_url = f"/assets/cover/{self.cover}"
        self.url = f"/assets/audio/{self.key}.mp3"


    def write_to_db(self):
        query = text(f"REPLACE INTO track (id, title, duration, cover_url, url) VALUES ({self.id}, '{self.title}', {self.duration}, '{self.cover_url}', '{self.url}')")
        print(query)
        if WRITE_TO_DB:
            conn.execute(query)
            conn.commit()

class Artist:
    def __init__(self, id, name, key):
        self.id = id
        self.name = name
        self.key = key
        self.cover_url = f"/assets/artist_cover/{self.key}.jpg"

    def write_to_db(self):
        query = text(f"REPLACE INTO artist (id, name, cover_url) VALUES ({self.id}, '{self.name}', '{self.cover_url}')")
        print(query)
        if WRITE_TO_DB:
            conn.execute(query)
            conn.commit()

class Playlist:
    def __init__(self, id, name, key):
        self.id = id
        self.name = name
        self.key = key
        self.cover_url = f"/assets/cover/{self.key}.jpg"

    def write_to_db(self):
        query = text(f"REPLACE INTO playlist (id, name, cover_url) VALUES ({self.id}, '{self.name}', '{self.cover_url}')")
        print(query)
        if WRITE_TO_DB:
            conn.execute(query)
            conn.commit()

def convert_time(time):
    time = time.split(':')
    delta = timedelta(minutes=int(time[0]), seconds=int(time[1]))
    return int(delta.total_seconds()) * 1000

tracks = []
artists = []
playlists = []

def insert_entities():
    with open('track.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        next(csv_reader)

        for i, row in enumerate(csv_reader):
            tracks.append(Track(id=i+1, title=row[0], key=row[1], duration=convert_time(row[2]), cover=row[3]))

    with open('artist.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        next(csv_reader)

        for i, row in enumerate(csv_reader):
            artists.append(Artist(id=i+1, name=row[0], key=row[1]))

    with open('playlist.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        next(csv_reader)

        for i, row in enumerate(csv_reader):
            playlists.append(Playlist(id=i+1, name=row[0], key=row[1]))

    for track in tracks:
        track.write_to_db()

    for artist in artists:
        artist.write_to_db()

    for playlist in playlists:
        playlist.write_to_db()

def find_artist_id(key):
    for artist in artists:
        if artist.key == key:
            return artist.id

    return None

def find_track_id(key):
    for track in tracks:
        if track.key == key:
            return track.id

    return None

def find_playlist_id(key):
    for playlist in playlists:
        if playlist.key == key:
            return playlist.id

    return None


def insert_relationships():
    with open('artist_track.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        next(csv_reader)

        for row in csv_reader:
            artist_id = find_artist_id(row[0])
            track_id = find_track_id(row[1])

            query = text(f"REPLACE INTO artist_track (artist_id, track_id, artist_priority, track_priority) VALUES ({artist_id}, {track_id}, {row[2]}, {row[3]})")
            print(query)
            if WRITE_TO_DB:
                conn.execute(query)
                conn.commit()

    with open('artist_playlist.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        next(csv_reader)

        for row in csv_reader:
            artist_id = find_artist_id(row[0])
            playlist_id = find_playlist_id(row[1])

            query = text(f"REPLACE INTO artist_playlist (artist_id, playlist_id, playlist_priority) VALUES ({artist_id}, {playlist_id}, {row[2]})")
            print(query)
            if WRITE_TO_DB:
                conn.execute(query)
                conn.commit()

    with open('playlist_track.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        next(csv_reader)

        for row in csv_reader:
            playlist_id = find_playlist_id(row[0])
            track_id = find_track_id(row[1])

            query = text(f"REPLACE INTO playlist_track (playlist_id, track_id, track_priority) VALUES ({playlist_id}, {track_id}, {row[2]})")
            print(query)
            if WRITE_TO_DB:
                conn.execute(query)
                conn.commit()

insert_entities()
insert_relationships()

conn.close()
