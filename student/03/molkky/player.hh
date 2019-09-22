#ifndef PLAYER_HH
#define PLAYER_HH
#include <string>

using namespace std;

class Player{
public:
  Player(string nimi);
  string get_name() const;
  bool has_won();
  int get_points();
  int add_points(int pts);
private:
  string nimi_;
  int    points_;
};

#endif // PLAYER_HH
