#include <iostream>
#include <string>
#include "player.hh"

using namespace std;

Player::Player(string nimi):
    nimi_(nimi), points_(0){

}
string Player::get_name() const{
    return nimi_;
}
bool Player::has_won(){
    if (points_ == 50){
        return true;
    }else{
        return false;
    }
}
int Player::get_points(){
    return points_;
}
int Player::add_points(int pts){
    points_ += pts;
    if (points_ >50){
        points_ =25;
    }
    return 0;
}
