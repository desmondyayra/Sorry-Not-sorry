#include "view.hxx"

ge211::Image_sprite board_spirite = ge211::Image_sprite("board_image"
                                                        ".jpg");
static std::string const rolling_sound_filename  {"rolling.ogg"};

static std::string const sorry_sound_filename  {"sorry.ogg"};


View::View(Model const& model, ge211::Mixer& mixer)
        : model_(model),
        box(ge211::Rectangle_sprite({159, 159}, ge211::Color(240,240, 240))),
        font_("sans.ttf", 25),
        indicator_text(),
        spin_text(),
        start_text0(),
        start_text1(),
        start_text2(),
        start_text3(),
        winner_text(),
        mixer(mixer)

{

    colors.push_back(ge211::Color(240,10, 10));
    colors.push_back(ge211::Color(10,10, 240));
    colors.push_back(ge211::Color(240,240, 10));
    colors.push_back(ge211::Color(10,240, 10));

    circles.push_back(ge211::Circle_sprite(26, colors[0]));
    circles.push_back(ge211::Circle_sprite(26, colors[1]));
    circles.push_back(ge211::Circle_sprite(26, colors[2]));
    circles.push_back(ge211::Circle_sprite(26, colors[3]));

    indicator_boxes.push_back(ge211::Rectangle_sprite({159, 159},colors[0]));
    indicator_boxes.push_back(ge211::Rectangle_sprite({159, 159},colors[1]));
    indicator_boxes.push_back(ge211::Rectangle_sprite({159, 159},colors[2]));
    indicator_boxes.push_back(ge211::Rectangle_sprite({159, 159},colors[3]));



    if(mixer.is_enabled()){

        load_audio_();
    }



}

void
View::draw(ge211::Sprite_set& set)
{

    set.add_sprite(board_spirite, {0, 0}, 0);

    for (int i = 0; i < 4; ++i) {


        for (Position pos : model_.list_of_players[i].list_of_pawns) {

            if ((pos.y != 100) && (pos.y != -50)) {

                if(pos.y > 14 ){

                    set.add_sprite(circles[i], home_board_to_screen(pos), 1 );

                }
                if(pos.y <= 14 ){

                    set.add_sprite(circles[i], board_to_screen(pos), 1 );

                }

            }

        }
    }




    for(Player player : model_.list_of_players){


        int start_num = player.start_pawn_num;
        ge211::Text_sprite::Builder player_start(font_);
        player_start.color(ge211::Color(10, 10, 10));
        player_start << start_num;


        if (player.start_position.x == 0){

            start_text0.reconfigure(player_start);
            set.add_sprite(start_text0, {224, 80}, 1);
        }
        if (player.start_position.x == 1){
            start_text1.reconfigure(player_start);
            set.add_sprite(start_text1, {672, 224}, 1);
        }
        if (player.start_position.x==2){
            start_text2.reconfigure(player_start);
            set.add_sprite(start_text2, { 560, 672 }, 1);

        }
        if(player.start_position.x==3){
            start_text3.reconfigure(player_start);
            set.add_sprite(start_text3, { 80, 560 }, 1);

        }




    }


    ge211::Text_sprite::Builder text_builder(font_);
    text_builder.color(ge211::Color(10, 10, 10));
    text_builder << "INDICATOR";

    set.add_sprite(box, { 212, 318}, 1);
    set.add_sprite(indicator_text, {477, 290},1);
    indicator_text.reconfigure(text_builder);


    if(model_.player_num_spin == 0) {
        ge211::Text_sprite::Builder spin_text_builder(font_);
        spin_text_builder.color(ge211::Color(10, 10, 10));
        spin_text_builder << "CLICK HERE";
        spin_text.reconfigure(spin_text_builder);
        set.add_sprite(spin_text, {230, 390}, 2);
    }else{
        ge211::Text_sprite::Builder spin_text_builder(font_);
        spin_text_builder.color(ge211::Color(10, 10, 10));
        spin_text_builder << model_.spin_num;
        spin_text.reconfigure(spin_text_builder);
        set.add_sprite(spin_text, {212, 390}, 2);

    }

    set.add_sprite(indicator_boxes[model_.turn_num], { 477, 318}, 2);




    for(Player player : model_.list_of_players){

        if(player.win){
            ge211::Text_sprite::Builder winner_text_builder(font_);
            winner_text_builder.color(ge211::Color(250, 250, 0));
            winner_text_builder <<  "winner is  " << player.color;
            winner_text .reconfigure(winner_text_builder);
            set.add_sprite(winner_text, {212, 530}, 2);



        }

    }




}
View::Dimensions
View::initial_window_dimensions() const
{

    return {848, 848};
}

std::string
View::initial_window_title() const
{
    // You can change this if you want:
    return "Sorry, Not Sorry !!";
}


View::Position
View::board_to_screen(ge211::Posn<int> pos) const{

   // int board_len = 14;
    int board_width = 848;
    int board_height = 848;
    int square_size = board_height/16;

    if(pos.x == 0){

        int x = pos.y * square_size;
        int y = 0;

        return Position{x, y};
    }

    if(pos.x == 1){
        int x = 15 * square_size;
        int y = pos.y * square_size;
        return Position{x, y};
    }

    if(pos.x == 2){
        int x = board_width - ((pos.y + 1)  * square_size);
        int y = 15 * square_size;
        return Position{x, y};

    }

    if(pos.x == 3){
        int x = 0;
        int y = board_height - ((pos.y + 1) * square_size);
        return Position{x, y};


    }


    return Position {-100, -100};

}

View::Position
View::home_board_to_screen(ge211::Posn<int> pos) const
{
    int board_len = 14;
    int board_width = 848;
    int board_height = 848;
    int square_size = board_height/16;

    if(pos.x == 0){

        int x = square_size * 2;
        int y = square_size * ( pos.y - board_len);

        return Position{x, y};
    }

    if(pos.x == 1){
        int x = board_width - (square_size * (1 - board_len + pos.y));
        int y = square_size * 2;
        return Position{x, y};
    }

    if(pos.x == 2){
        int x = board_height - (square_size * 3);
        int y = board_height - (square_size * (1 - board_len + pos.y));
        return Position{x, y};

    }

    if(pos.x == 3){
        int x = (square_size * ( - board_len + pos.y));
        int y = board_height - (3 * square_size);
        return Position{x, y};


    }


    return Position {-60, -60};

}

ge211::Posn<int>
View::screen_to_board(View::Position physical) const
{
    int x =  (floor(physical.x / 53));
    int y = (floor(physical.y / 53));





    return Position { x, y};
}


ge211::Posn<int>
View::screen_to_home_board(View::Position physical) const
{
   ge211::Posn <int> checker = screen_to_board(physical);

   if( (checker.x == 0) && (checker.y == 0)){ return {0, 0};}

   if( (checker.y == 0) && (checker.x != 15)){ return {0, checker.x}; }

   if (( checker.x == 15) && (checker.y != 15)){ return {1, checker.y}; }

   if ((checker.y == 15) && (checker.x != 0)){ return {2, 15-checker.x};}

   if((checker.x == 0) && (checker.y != 0)){return {3, 15-checker.y};}

   if ((checker.x == 2) && (checker.y <= 5)){return {0, checker.y + 14};}

   if((checker.y == 2)&& (checker.x >9)){return {1, 29-checker.x};}

   if ((checker.x == 13) && (checker.y > 9)){return{2,29-checker.y };}

   if((checker.y == 13) && (checker.x <= 5)){return{3, checker.x + 14};}

    return {-100, -100};
}


int
View::screen_to_start_button(View::Position physical) const
{
    ge211::Posn <int> checker = screen_to_board(physical);

    if((3 <= checker.x) && (checker.x <= 5) && (1 <= checker.y)&& (checker.y <=
    3)){
        return 0;

    }

    if((12 <= checker.x) && (checker.x <= 14) && (3 <= checker.y)&& (checker
    .y <= 5)){
        return 1;

    }

    if((10 <= checker.x) && (checker.x <= 12) && (12 <= checker.y)&& (checker
    .y <= 14)){
        return 2;

    }



    if((1 <= checker.x) && (checker.x <= 3) && (10 <= checker.y)&& (checker.y
    <= 12)){
        return 3;

    }


    return -100;



}

bool
View::screen_to_spin_box(View::Position physical) const
{

    ge211::Posn <int> checker = screen_to_board(physical);

    if((4 <= checker.x) &&(checker.x <= 7) && (6 <= checker.y) && (checker.y<= 9)){

        return true;

    }

    return false;


}

void
View::play_rolling_sound() const
{
    mixer.try_play_effect(rolling_sound);


}
void
View::play_sorry_sound() const
{

    mixer.try_play_effect(sorry_sound);

}



void
View::load_audio_()
{
    rolling_sound.try_load(rolling_sound_filename, mixer);
    sorry_sound.try_load(sorry_sound_filename, mixer);



}

