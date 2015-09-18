#ifndef GTP_PLAYER_H_
#define GTP_PLAYER_H_

#include <functional>
#include <string>

namespace gogowq {

struct BoardCoord {
  BoardCoord() : H('\0'), V(0) {}

  BoardCoord(char H, int8_t V) : H(H), V(V) {}

  explicit BoardCoord(const std::string& str);

  bool IsValid() const {
    if (H == 'I' || H < 'A' || H >= 'T') return false;
    if (V < 1 || V > 19) return false;
    return true;
  }

  char H;
  int8_t V;
};

class GtpPlayer {
 public:
  enum class Role {
    BLACK = 'b',
    WHITE = 'w',
  };

  GtpPlayer();
  virtual ~GtpPlayer();

  std::string GetProtocolVersion();
  std::string GetName();
  std::string GetVersion();

  void SetRole(Role role);

  bool SetBoardSize(size_t size);
  bool ClearBoard();
  bool SetKomi(float komi);
  bool SetHandicap(size_t handicap);

  bool Play(BoardCoord coord);
  BoardCoord GenMove();
  bool Undo();

  std::string GetFinalScore();
  bool Quit();

 protected:
  virtual std::string Input(const std::string& cmd, std::string* err_msg) = 0;

 private:
  enum Role role_;
};

}  // namespace gogowq

#endif  // GTP_PLAYER_H_
