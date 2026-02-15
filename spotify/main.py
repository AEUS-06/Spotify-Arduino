import os
import time
import serial
import spotipy
from dotenv import load_dotenv
from spotipy.oauth2 import SpotifyOAuth

load_dotenv()

CLIENT_ID = os.getenv("SPOTIFY_CLIENT_ID")
CLIENT_SECRET = os.getenv("SPOTIFY_CLIENT_SECRET")
REDIRECT_URI = os.getenv("SPOTIFY_REDIRECT_URI")
SERIAL_PORT = os.getenv("SERIAL_PORT")

sp = spotipy.Spotify(auth_manager=SpotifyOAuth(
    client_id=CLIENT_ID,
    client_secret=CLIENT_SECRET,
    redirect_uri=REDIRECT_URI,
    scope="user-read-currently-playing"
))

arduino = serial.Serial(SERIAL_PORT, 115200, timeout=1)

time.sleep(3)

print("Servidor de Spotify iniciado...")

last_song = ""

def clean_text(text):
    return text.replace("|", "").replace("\n", "").replace("\r", "")

while True:
    try:
        current = sp.current_user_playing_track()

        if current and current["item"]:
            track = current["item"]

            song = clean_text(track["name"])
            artist = clean_text(track["artists"][0]["name"])

            full_track = f"{song} - {artist}"

            if full_track != last_song:
                message = f"{song}|{artist}\n"
                arduino.write(message.encode("utf-8"))
                print(f"Enviado: {full_track}")
                last_song = full_track

        time.sleep(2)

    except Exception as e:
        print("Error:", e)
        time.sleep(5)
