#pragma once

#include <ge211.hxx>
#include "player.hxx"
#include <iostream>

class Model
{

public:
    Model();


     void move_turn();



     bool check_possible_moves(Player player, int num);

    Player check_position(ge211::Posn<int> pos, Player play); //helper

    int find_player(Player player);

    void update();
    void really_make_move(ge211::Posn<int> pos, int num);

    void spin();

    void change_spin();

    void start_pawn_player(int i);



    bool check_win();

    Player declare_winner();




public:
    std::vector<Player> list_of_players;
public:
    int player_num_spin;
    int turn_num;
    std::vector<ge211::Posn<int>> active_board;
    int spin_num;

    bool sorry_sound;













};
