# womf

A c++ static library audio player based on [**miniaudio**](https://github.com/mackron/miniaudio)

### Features
Play wave, ogg, mp3 and flac audio files.
CMake file to build a static library.
No external dependencies, all is included.

### Usage
#### 1. Include header
```cpp
#include <womf/MusicStream.hpp>
```
### 2. Load an audio file
```cpp
music.loadFromFile("song.mp3");
```
### 2. Play
```cpp
music.play();
```

### Todo
- Documentation (doxygen)
- Spatialization for sound
- Faders (in and out)