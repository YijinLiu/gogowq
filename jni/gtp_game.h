#ifndef GTP_GAME_H_
#define GTP_GAME_H_

#include <memory>

#include "gtp_player.h"

namespace gogowq {

class GtpGame {
 public:
  GtpGame(std::unique_ptr<GtpPlayer> black, std::unique_ptr<GtpPlayer> white);
  virtual ~GtpGame();

  void SwitchSides();

  // Returns when it finishes or interrupted.
  std::string Start(size_t board_size, float komi, size_t handicap);

  void Interrupt();

  const GtpPlayer& black_player() const {
    return *black_;
  }

  const GtpPlayer& white_player() const {
    return *white_;
  }

 private:
  std::unique_ptr<GtpPlayer> black_;
  std::unique_ptr<GtpPlayer> white_;
};

}  // namespace gogowq

#endif  // GTP_CONTROLLER_H_
