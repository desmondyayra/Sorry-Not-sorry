#include "model.hxx"
#include <catch.hxx>

TEST_CASE("example test (TODO: replace this)")
{
    CHECK(1 + 1 == 2);

    Model m = Model();
    //checking if the constructors work
    CHECK(m.list_of_players[m.turn_num].start_position.x == 0);

    //checking if the function possible moves work
    CHECK_FALSE(m.check_possible_moves(m.list_of_players[m.turn_num], 5) );


    //checking that check_possible_moves did not alter the position of the
    // players
    CHECK(m.list_of_players[0].list_of_pawns[0].y == -50);

    CHECK(m.check_possible_moves(m.list_of_players[m.turn_num], 1) );

    m.start_pawn_player(6);
    //checking that start_pawn_player worked as expected
    CHECK(m.spin_num == 0);
    CHECK(m.turn_num == 0);

    CHECK(m.player_num_spin == 0);
    CHECK(m.list_of_players[0].list_of_pawns[0].y == -50);

    m.start_pawn_player(1);

    CHECK(m.list_of_players[0].start_pawn_num == 3);
    CHECK(m.list_of_players[1].start_pawn_num == 4);


    CHECK(m.player_num_spin == 1);
    CHECK(m.turn_num == 1);

    CHECK(m.list_of_players[0].list_of_pawns[0].y == 4);

    m.turn_num = 0;

    CHECK(m.check_possible_moves(m.list_of_players[0], 5) );
    m.really_make_move({3, 3}, 5);
    CHECK(m.player_num_spin == 1);
    CHECK(m.turn_num == 0);



    m.really_make_move({0, 4}, 4 );

    CHECK(m.list_of_players[0].list_of_pawns[0].y == 8);
    CHECK(m.list_of_players[0].list_of_pawns[0].x == 0);
    CHECK(m.player_num_spin == 0);
    CHECK(m.turn_num == 1);

    m.turn_num = 0;


    m.start_pawn_player(2);
    CHECK(m.list_of_players[0].list_of_pawns[1].y == 5);
    CHECK(m.list_of_players[0].list_of_pawns[1].x == 0);




    m.list_of_players[0].list_of_pawns[1].y = 7;
    m.list_of_players[0].list_of_pawns[1].x = 1;

    m.turn_num = 1;
    m.start_pawn_player(1);

    m.turn_num = 1;

    //checking if a player can be knocked away from their position



    CHECK(m.check_possible_moves(m.list_of_players[1], 3));
    CHECK(m.list_of_players[0].start_pawn_num == 2);
    m.really_make_move({1, 4}, 3);
    CHECK(m.turn_num == 2);
    CHECK(m.player_num_spin == 1);

    CHECK(m.list_of_players[1].list_of_pawns[0].y == 7);
    CHECK(m.list_of_players[1].list_of_pawns[0].x == 1);
    CHECK(m.list_of_players[0].list_of_pawns[1].y == -50);
    CHECK(m.list_of_players[0].list_of_pawns[1].x == 0);

    CHECK(m.list_of_players[0].start_pawn_num == 3);










}



TEST_CASE("CHECKING FOR GOING TO HOME_ROW, EDGE CASES"){

    Model m = Model();

    m.spin();

    //checking if spin works

    CHECK((m.spin_num > 0) );
    CHECK((m.spin_num <  7) );

    m.list_of_players[0].list_of_pawns[0].x = 3;
    m.list_of_players[0].list_of_pawns[0].y = 14;
    CHECK(m.check_possible_moves(m.list_of_players[0], 3));


    m.really_make_move({3, 14},6 );

    CHECK(m.list_of_players[0].list_of_pawns[0].x == 0);
    CHECK(m.list_of_players[0].list_of_pawns[0].y == 17);


    m.list_of_players[0].list_of_pawns[1].x = 0;
    m.list_of_players[0].list_of_pawns[1].y = 0;

    m.turn_num = 0;

    m.really_make_move({0, 0},6 );

    CHECK(m.list_of_players[0].list_of_pawns[1].x == 0);
    CHECK(m.list_of_players[0].list_of_pawns[1].y == 18);


    m.list_of_players[1].list_of_pawns[0].x = 1;
    m.list_of_players[1].list_of_pawns[0].y = 0;

    m.really_make_move({1, 0},4 );


    //checking that usual paws can transition to home row
    CHECK(m.list_of_players[1].list_of_pawns[0].x == 1);
    CHECK(m.list_of_players[1].list_of_pawns[0].y == 16);



    //checking for a winner

    m.list_of_players[0].list_of_pawns[0].x = 0;
    m.list_of_players[0].list_of_pawns[0].y = 20;

    m.update();

    CHECK(m.list_of_players[0].list_of_pawns[0].x == 0);
    CHECK(m.list_of_players[0].list_of_pawns[0].y == 100);

    m.list_of_players[0].list_of_pawns[1].x = 0;
    m.list_of_players[0].list_of_pawns[1].y = 20;

    m.update();


    m.list_of_players[0].list_of_pawns[2].x = 0;
    m.list_of_players[0].list_of_pawns[2].y = 20;

    m.update();

    m.list_of_players[0].list_of_pawns[3].x = 0;
    m.list_of_players[0].list_of_pawns[3].y = 20;

    m.update();

    CHECK(m.check_win());

    CHECK(m.list_of_players[0].win);

    CHECK(m.declare_winner().start_position == m.list_of_players[0].start_position  );



    //CHECKING IF MOVES CAN BE MADE IN THE HOME ROW but shouldn't go about
    // the home position

    m.list_of_players[2].list_of_pawns[0].x = 2;
    m.list_of_players[2].list_of_pawns[0].y = 15;

    m.turn_num = 2;

    CHECK(m.check_possible_moves(m.list_of_players[2], 3));
    CHECK_FALSE(m.check_possible_moves(m.list_of_players[2], 6));



    m.list_of_players[3].list_of_pawns[0].x = 2;
    m.list_of_players[3].list_of_pawns[0].y = 15;

    m.list_of_players[3].list_of_pawns[1].x = 0;
    m.list_of_players[3].list_of_pawns[1].y = 15;

    m.list_of_players[3].list_of_pawns[2].x = 1;
    m.list_of_players[3].list_of_pawns[2].y = 15;

    m.list_of_players[3].list_of_pawns[3].x = 1;
    m.list_of_players[3].list_of_pawns[3].y = 4;


    CHECK(m.check_possible_moves(m.list_of_players[3], 3));











}
//
// TODO: Write preliminary model tests.
//
// These tests should demonstrate your functional requirements.
//
