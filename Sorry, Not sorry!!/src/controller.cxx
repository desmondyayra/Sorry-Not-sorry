#include "controller.hxx"

Controller::Controller()
        : view_(model_,mixer()),
          mouse_pos( ge211::Posn<int>{0,0})
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}


View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string
Controller::initial_window_title() const
{
    return view_.initial_window_title();
}




void
Controller::on_mouse_move(ge211::Posn<int> pos)
{

    mouse_pos  = pos;


}


void
Controller::on_mouse_down(ge211::Mouse_button, ge211::Posn<int> pos)
{
    mouse_pos = pos;

    if((model_.player_num_spin == 0)){

        if(view_.screen_to_spin_box(pos) ){

            model_.spin();
            view_.play_rolling_sound();



        }

    }

    if(model_.player_num_spin == 1){

        if(model_.check_possible_moves(model_.list_of_players[model_
        .turn_num],model_.spin_num)){


            ge211::Posn<int> mouse_active_board = view_.screen_to_home_board
                    (pos);
            bool bool1 = (model_.list_of_players[model_.turn_num].start_pawn_num > 0);
            if(((model_.spin_num ==1) || (model_.spin_num == 2)) && bool1){

                if(view_.screen_to_start_button(pos) == model_.turn_num){


                    model_.start_pawn_player(model_.spin_num);

                }


            }

            ge211::Posn<int> sample = model_.list_of_players[model_.turn_num]
                    .make_active_move(mouse_active_board, model_.spin_num);

            if (sample.x != -50){

                model_.really_make_move(mouse_active_board, model_.spin_num);

                if (model_.sorry_sound ){

                    view_.play_sorry_sound();
                }

            }



        }else{

            model_.move_turn();
            model_.player_num_spin = (model_.player_num_spin + 1) % 2;



        }



    }



}
