#include "womf/MusicStream.hpp"

#include <iostream>
#include <chrono>
#include <filesystem>
#include <thread>

int main(int argc, char** argv) {

  if (argc != 2) {
    std::cout << "No audio file to play" << std::endl;
    std::cout << "usage: womf filetoplay" << std::endl;
    return 0;
  }

  if (!std::filesystem::exists(std::filesystem::path(argv[1]))) {
    std::cout << "File " << argv[1] << " does not exists" << std::endl;
    return 0;
  }

  womf::MusicStream music;
  music.setMasterVolume(0.5f);

  if (!music.loadFromFile(argv[1])) {
    std::cout << "Error on loading file" << std::endl;
    return 0;
  }
  music.seekTo(60000);
  music.play();

  std::string cmd("");
  while (cmd.compare("q") != 0) {
    std::getline(std::cin, cmd);

    if (cmd.compare("p") == 0) {
      if (music.getState() == womf::AudioStreamState::PAUSE
          || music.getState() == womf::AudioStreamState::STOP) {
        music.play();
      }
      else if (music.getState() == womf::AudioStreamState::PLAY) {
        music.pause();
      }
    }

    if (cmd.compare("z") == 0) {
      music.seek(5000);
    }

    if (cmd.compare("a") == 0) {
      music.seek(-5000);
    }

    if (cmd.compare("s") == 0) {
      music.stop();
    }

    if (cmd.compare("i") == 0) {
      std::string state = "";
      switch (music.getState()) {
        case womf::AudioStreamState::PAUSE:
          state = "Pause";
          break;
        case womf::AudioStreamState::PLAY:
          state = "Play";
          break;
        default:
          state = "";
      }

      state.append(" ");
      state.append(std::to_string(music.getAudioPosition()));
      state.append(" / ");
      state.append(std::to_string(music.getDuration()));

      std::cout << state << std::endl;

    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  return 0;
}
