#include "gtp_game.h"

#include <string>
#include <thread>

namespace gogowq {

GtpGame::GtpGame(std::unique_ptr<GtpPlayer> black, std::unique_ptr<GtpPlayer> white)
    : black_(std::move(black)), white_(std::move(white)) {}

GtpGame::~GtpGame() {}

void GtpGame::SwitchSides() {
  black_.swap(white_);
}

std::string GtpGame::Start(size_t board_size, float komi, size_t handicap) {
  black_->ClearBoard();
  black_->SetRole(GtpPlayer::Role::BLACK);
  black_->SetBoardSize(board_size);
  black_->SetKomi(komi);
  black_->SetHandicap(handicap);

  white_->ClearBoard();
  white_->SetRole(GtpPlayer::Role::WHITE);
  white_->SetBoardSize(board_size);
  white_->SetKomi(komi);
  white_->SetHandicap(handicap);

  GtpPlayer* cur = black_.get();
  GtpPlayer* next = white_.get();
  while (true) {
    auto coord = cur->GenMove();
    // TODO: Detect resign.
    next->Play(coord);
    auto temp = cur;
    cur = next;
    next = temp;
  }

  return "";
}

void GtpGame::Interrupt() {
}

}  // namespace gogowq
