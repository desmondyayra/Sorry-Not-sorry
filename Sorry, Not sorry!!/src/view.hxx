#pragma once

#include "model.hxx"



class View
{
public:
    /// View dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// View positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// View rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;


    explicit View(Model const& model, ge211::Mixer& mixer);

    void draw(ge211::Sprite_set& set);


    Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;


    View :: Position
    board_to_screen ( ge211::Posn<int>  pos)const ;


    View :: Position
    home_board_to_screen ( ge211::Posn<int>  pos)const ;

    ge211::Posn<int>
    screen_to_board(View::Position physical) const;

    ge211::Posn<int>
    screen_to_home_board(View::Position physical) const;

    int
    screen_to_start_button(View::Position physical) const;
    bool
    screen_to_spin_box(View::Position physical) const;

    void play_rolling_sound() const;

    void play_sorry_sound() const;





private:
    Model const& model_;

    std::vector <ge211::Color > colors;

    std::vector <ge211::Circle_sprite> circles;


    ge211::Rectangle_sprite box;

    ge211::Font font_;

    ge211::Text_sprite indicator_text;

    ge211::Text_sprite spin_text;

    std::vector <ge211::Rectangle_sprite> indicator_boxes;

    ge211::Text_sprite start_text0;
    ge211::Text_sprite start_text1;
    ge211::Text_sprite start_text2;
    ge211::Text_sprite start_text3;

    ge211::Text_sprite winner_text;


    ge211::Mixer& mixer;
    ge211::Sound_effect rolling_sound;

    ge211::Sound_effect sorry_sound;

    void load_audio_();




};
