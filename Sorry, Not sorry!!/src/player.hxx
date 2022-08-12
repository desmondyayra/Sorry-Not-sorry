#include "ge211.hxx"
#include <vector>
#include <iostream>
#include <unordered_map>



class Player{
public:
    Player(const char* color,
           ge211::Posn<int> start_position,
           ge211::Posn<int> end_possiton);


public:
    const char* color;

    ge211::Posn<int> start_position;
private:
    ge211::Posn<int> end_position;

public:
    int start_pawn_num;
private:
    int end_pawn_num;
public:
    std::vector<ge211::Posn<int>> list_of_pawns;
private:

    int vec_to_num(ge211::Posn<int> vec);


    ge211::Posn<int> num_to_vec(int num);
public:
    bool win;

public:
    ge211::Posn<int> make_active_move(ge211::Posn<int> pos, int num);
    //given a position and a num,
    //it makes a move on the pawn at that positon

    void reset_pawn(ge211::Posn<int> pos);

    void start_pawn(int i);

    void check_win();























};