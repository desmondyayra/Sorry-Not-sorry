#include "player.hxx"




Player::Player(
        const char *color,
        ge211::Posn<int> start_position,
        ge211::Posn<int> end_possiton)



        :color(color),
        start_position(start_position),
        end_position(end_possiton),
        start_pawn_num(4),
        end_pawn_num(0),
        list_of_pawns( std::vector<ge211::Posn<int> >(4, {start_position.x,
                                                          -50})),
        win(false)

{





}

int Player::vec_to_num(ge211::Posn<int> vec)
{
    //this function converts a vector/pair on the active board position to a
    // number

    return (vec.x * 15) + (vec.y);




}


ge211::Posn<int> Player::num_to_vec(int num){

    //opposite of vec_to_num

    return{int(floor(num/15)), num % 15 };

}

ge211::Posn<int> Player::make_active_move(ge211::Posn<int> pos, int num)
{

    for(ge211::Posn<int>& posn : list_of_pawns ){




        if( posn == pos){
            int tracking_start = vec_to_num(start_position);
            int tracking_end = vec_to_num(end_position);
            int tracking_current = vec_to_num(posn);

            if(posn.y > 14 ){


                if((pos.y + num) <= 20  ){

                    return ge211::Posn<int>{start_position.x, pos.y + num};

                }



            }


            if((start_position.x == 0) && ((tracking_current + num ) > 62)){

                return ge211::Posn<int>{start_position.x, ((tracking_current
                + num )  + 14 - 62) };

            }

            bool bool1 = (tracking_current < tracking_start);
            bool bool2 = ((tracking_current + num) > tracking_end );
            bool bool3 = (pos.y) <= 14;

            if ( bool1 && bool2 && bool3){

                return ge211::Posn<int>{start_position.x, ((tracking_current
                                                            + num  + 14) -
                                                            tracking_end) };

            }

            if(bool3 ) {
                int new_tracker = (tracking_current + num) % 60;

                return num_to_vec(new_tracker);
            }

        }


    }


    return ge211::Posn<int> {-50, -50};
}


void Player::reset_pawn(ge211::Posn<int> pos)
{

    for(ge211::Posn<int>& posn : list_of_pawns ){

        if(posn == pos){

            posn.x = start_position.x;
            posn.y = -50;

            start_pawn_num += 1;

        }

    }


}

void Player::start_pawn(int i){

    for(ge211::Posn<int>& posn : list_of_pawns){

        if (posn.y == -50){

            if(i == 1){

                posn = start_position;
                start_pawn_num -= 1;

            }else if(i == 2){

                posn = ge211::Posn<int>{start_position.x, (start_position.y +
                                        1)};
                start_pawn_num -= 1;
            }

            break;

        }



    }

}

void Player::check_win(){
    ge211::Posn<int> checker = ge211::Posn<int>{start_position.x, 20};
    ge211::Posn<int> checker1 = ge211::Posn<int>{start_position.x, 100};
    end_pawn_num = 0;
    for(ge211::Posn<int>& posn : list_of_pawns){
        if ((posn == checker) || (posn == checker1)){
            posn = {start_position.x, 100};
            end_pawn_num += 1;

        }


    }

    if (end_pawn_num > 3){
        win = true;
    }


}




