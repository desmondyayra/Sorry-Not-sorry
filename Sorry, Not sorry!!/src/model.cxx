#include "model.hxx"




Model::Model()
    :player_num_spin(0),
    //player_turn(Player("place_holder", {-50, -50}, {-50, -50}))
     turn_num(0),
     spin_num(0),
     sorry_sound(false)





{
    list_of_players.push_back(Player("red", {0,4}, {0,2}));
    list_of_players.push_back(Player("blue", {1,4}, {1,2}));
    list_of_players.push_back(Player("yellow", {2,4}, {2,2}));
    list_of_players.push_back(Player("green", {3,4}, {3,2}));

    for(int i = 0; i < 4; ++i){


        for(int j = 0; j < 21; ++j){

            active_board.push_back(ge211::Posn<int>{i, j});


        }


    }







}


void Model::move_turn()
{

    turn_num = (turn_num + 1) % 4;


}


bool Model::check_possible_moves(Player player, int num){
    //when the num can be used to activate a pawn yet to start


    if ((num == 1) || (num==2)){
        for(ge211::Posn<int>& posn : player.list_of_pawns ){
            if (posn.y == -50 ) {
                return true;
            }
        }
    }

    //checking if there a situation where the prospective move already
    // contains an existing pawn
    // for(ge211::Posn<int>& posn : player.list_of_pawns ) {
    //
    //     if((posn.y != 100) && (posn.y != -50)) {
    //
    //         ge211::Posn<int> checker = player.make_active_move(posn, num);
    //
    //         if(checker.x != -50){
    //
    //             for(ge211::Posn<int>& nposn : player.list_of_pawns ) {
    //                 if (nposn == checker){
    //
    //                     return false;
    //                 }
    //
    //
    //             }
    //         }
    //
    //         //return true;
    //     }
    //
    // }

    for(ge211::Posn<int>& posn : player.list_of_pawns ) {

        if ((posn.y != -50) && (posn.y != 100)) {

            ge211::Posn<int> checker = player.make_active_move(posn, num);

            if(checker.x != -50){

                return true;

            }

        }
    }
     return false;

}



Player Model::check_position(ge211::Posn<int> pos, Player play)
{

    for( Player& sample : list_of_players){
        if (sample.start_position != play.start_position){

            for(ge211::Posn<int>& posn: sample.list_of_pawns){
                if (posn == pos){

                    return sample;
                }

            }

        }

    }




    return Player("placeholder", {-50, -50}, {-50, -50});
}


int Model::find_player(Player player)
{
    for(int i = 0; i < 4; ++i ){

        if(list_of_players[i].start_position.x == player.start_position.x){

            return i;
        }

    }


    return -5;
}

void Model::update()
{
    for(Player& player : list_of_players){

        player.check_win();

    }


}
void Model::really_make_move(ge211::Posn<int> pos, int num)
{
    ge211::Posn<int> checker = list_of_players[turn_num].make_active_move
            (pos, num);



    if(checker.x != -50) {
        for (ge211::Posn<int>& posn : list_of_players[turn_num].list_of_pawns) {

            if (posn == pos) {

                Player play_checker = check_position(checker,
                                                     list_of_players[turn_num]);



                if (play_checker.start_position == ge211::Posn<int>{-50, -50}){

                    posn = checker;
                    move_turn();
                    player_num_spin =  (player_num_spin + 1) % 2;
                    update();
                    break;


                }else {



                    // check_position(checker,
                    //                list_of_players[turn_num]).reset_pawn(checker);


                    int find = find_player(check_position(checker,
                                                          list_of_players[turn_num]));



                    list_of_players[find].reset_pawn(checker);
                    sorry_sound = true;

                    posn = checker;

                    move_turn();
                    player_num_spin = (player_num_spin + 1) % 2;
                    update();
                    break;

                }

            }

        }

    }






}


void Model::spin()
{

    int spin_list[6] = {1, 2, 3, 4, 5, 6};
    int random =  rand() % 6;
    spin_num = spin_list[random];
    sorry_sound = false;

    player_num_spin =  (player_num_spin + 1) % 2;


}

void Model::change_spin()
{

    if (player_num_spin == 1){
        player_num_spin = 0;
    }

    if (player_num_spin == 0){

        player_num_spin = 1;
    }


}

void Model::start_pawn_player(int i)
{
    if ((i == 1) || (i == 2)){

        list_of_players[turn_num].start_pawn(i);
        move_turn();
        player_num_spin =  (player_num_spin + 1) % 2;

    }



}

bool Model::check_win()
{

    for(Player& player : list_of_players){

        if (player.win){
            return true;

        }
    }

    return false;

}


Player Model::declare_winner(){

    for(Player& player : list_of_players){

        if (player.win){
            return player;

        }
    }
    return Player("place_holder", {-50, -50}, {-50, -50});



}