#include "gtp_player.h"

#include <ctype.h>

#include <iostream>

namespace gogowq {

BoardCoord::BoardCoord(const std::string& str) : H('\0'), V(0) {
  if (str.size() != 2 && str.size() != 3) return;
  H = toupper(str[0]);
  if (!isdigit(str[1])) return;
  V = str[1] - '0';
  if (str.size() == 3) {
    if (!isdigit(str[2])) return;
    V *= 10;
    V += str[2] - '0';
  }
}

GtpPlayer::GtpPlayer() {}

GtpPlayer::~GtpPlayer() {}

std::string GtpPlayer::GetProtocolVersion() {
  std::string err_msg;
  const std::string version = Input("protocol_version", &err_msg);
  if (!err_msg.empty()) {
    std::cerr << "Failed to get protocol version: " << err_msg << std::endl;
  }
  return version;
}

std::string GtpPlayer::GetName() {
  std::string err_msg;
  const std::string name = Input("name", &err_msg);
  if (!err_msg.empty()) {
    std::cerr << "Failed to get name: " << err_msg << std::endl;
  }
  return name;
}

std::string GtpPlayer::GetVersion() {
  std::string err_msg;
  const std::string version = Input("version", &err_msg);
  if (!err_msg.empty()) {
    std::cerr << "Failed to get version: " << err_msg << std::endl;
  }
  return version;
}

void GtpPlayer::SetRole(Role role) {
  role_ = role;
}

bool GtpPlayer::SetBoardSize(size_t size) {
  char cmd[20];
  snprintf(cmd, sizeof(cmd), "boardsize %d", (int)size);
  std::string err_msg;
  Input(cmd, &err_msg);
  if (!err_msg.empty()) {
    std::cerr << "Failed to set board size: " << err_msg << std::endl;
    return false;
  }
  return true;
}

bool GtpPlayer::ClearBoard() {
  std::string err_msg;
  Input("clear_board", &err_msg);
  if (!err_msg.empty()) {
    std::cerr << "Failed to clear board: " << err_msg << std::endl;
    return false;
  }
  return true;
}

bool GtpPlayer::SetKomi(float komi) {
  char cmd[20];
  snprintf(cmd, sizeof(cmd), "komi %f", komi);
  std::string err_msg;
  Input(cmd, &err_msg);
  if (!err_msg.empty()) {
    std::cerr << "Failed to set komi: " << err_msg << std::endl;
    return false;
  }
  return true;
}

bool GtpPlayer::SetHandicap(size_t handicap) {
  char cmd[100];
  snprintf(cmd, sizeof(cmd), "fixed_handicap %d", (int)handicap);
  std::string err_msg;
  Input(cmd, &err_msg);
  if (!err_msg.empty()) {
    std::cerr << "Failed to set handicap: " << err_msg << std::endl;
    return false;
  }
  return true;
}

bool GtpPlayer::Play(BoardCoord coord) {
  char cmd[20];
  snprintf(cmd, sizeof(cmd), "play %c %c%d", (char)role_, coord.H, coord.V);
  std::string err_msg;
  Input(cmd, &err_msg);
  if (!err_msg.empty()) {
    std::cerr << "Failed to " << cmd << ": " << err_msg << std::endl;
    return false;
  }
  return true;
}

BoardCoord GtpPlayer::GenMove() {
  char cmd[20];
  snprintf(cmd, sizeof(cmd), "genmove %c", (char)role_);
  std::string err_msg;
  const std::string result = Input(cmd, &err_msg);
  if (!err_msg.empty()) {
    std::cerr << "Failed to " << cmd << ": " << err_msg << std::endl;
    return BoardCoord();
  }
  return BoardCoord(result);
}

bool GtpPlayer::Undo() {
  std::string err_msg;
  Input("undo", &err_msg);
  if (!err_msg.empty()) {
    std::cerr << "Failed to undo: " << err_msg << std::endl;
    return false;
  }
  return true;
}

std::string GtpPlayer::GetFinalScore() {
  std::string err_msg;
  const std::string score = Input("final_score", &err_msg);
  if (!err_msg.empty()) {
    std::cerr << "Failed to get final score: " << err_msg << std::endl;
  }
  return score;
}

bool GtpPlayer::Quit() {
  std::string err_msg;
  Input("quit", &err_msg);
  if (!err_msg.empty()) {
    std::cerr << "Failed to quit: " << err_msg << std::endl;
    return false;
  }
  return true;
}

}  // namespace gogowq
