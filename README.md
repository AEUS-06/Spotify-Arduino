# Spotify-Arduino

**Muestra la canción que se está reproduciendo en Spotify en un OLED 128×64 conectado a un Arduino.**

Estado: ❗ Experimental

---

## 📌 Descripción rápida

Este repositorio está dividido en dos partes: el firmware para el Arduino (pantalla OLED) y el servicio en Python que consulta la API de Spotify y envía la información por puerto serial.

- `pantalla-arduino/` — firmware (PlatformIO / Arduino) para mostrar título/artista en SSD1306.
- `spotify/` — script Python que obtiene la pista actual y la envía al Arduino.

---

## 📑 Índice

- [Características](#-características)
- [Estructura](#-estructura-del-proyecto)
- [Requisitos](#-requisitos)
- [Instalación](#-instalación)
- [Configuración](#-configuración)
- [Conexiones (wiring)](#-conexiones-wiring)
- [Uso](#-uso)
- [Contribuir](#-contribuir)
- [Autor y licencia](#-autor-y-licencia)

---

## ✅ Características

- Muestra título y artista en un OLED 128×64 (SSD1306).
- Comunicación entre Python (Spotify API) y Arduino vía puerto serie.
- Scroll automático para textos largos.

---

## 🗂️ Estructura del proyecto

```
Spotify-Arduino/
├── pantalla-arduino/        # Firmware (PlatformIO)
│   ├── include/
│   ├── lib/
│   ├── platformio.ini
│   └── src/main.cpp
├── spotify/                 # Servicio Python + configuración
│   ├── main.py
│   └── requirements.txt
└── README.md
```

---

## 🧾 Requisitos

- Arduino compatible con pantalla SSD1306 (I2C)
- Pantalla OLED 128×64
- Python 3.8+
- Librerías Python: `spotipy`, `python-dotenv`, `pyserial`
- Cuenta de Spotify con permiso `user-read-currently-playing`

---

## 🛠️ Instalación

1. Instala dependencias de Python:

```bash
pip install -r spotify/requirements.txt
```

2. Abre y sube el firmware desde `pantalla-arduino/` usando PlatformIO o Arduino IDE.

---

## ⚙️ Configuración

Crea un archivo `.env` dentro de la carpeta `spotify/` con estos valores:

```env
SPOTIFY_CLIENT_ID=tu_client_id
SPOTIFY_CLIENT_SECRET=tu_client_secret
SPOTIFY_REDIRECT_URI=http://localhost:8888/callback
SERIAL_PORT=COM3   # en Windows, por ejemplo COM3; en Linux /dev/ttyUSB0
```

- Asegúrate de que `SERIAL_PORT` coincide con el puerto donde está el Arduino.
- Registra la app en el Dashboard de Spotify y asigna el scope `user-read-currently-playing`.

---

## 🔌 Conexiones (wiring)

Ejemplo de conexión I2C (Arduino Uno):

- VCC → 5V (o 3.3V según módulo)
- GND → GND
- SDA → A4
- SCL → A5

## ▶️ Uso

1. Subir el firmware al Arduino (desde `pantalla-arduino/`).
2. Ejecutar el servicio Python:

```bash
cd spotify
python main.py
```

## 🤝 Contribuir

Pull requests y mejoras son bienvenidas. Para cambios mayores, abre un issue primero para discutir la propuesta.

---

## 👤 Autor y licencia

- Autor: Atekokoli
- Licencia: MIT 