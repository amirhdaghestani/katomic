#include "menu.h"
#include <iostream>
#include <string>

Button::Button() {
    name = "Ok";
    x = 0;
    y = 0;
    button_type = nButton;
    is_selected = true;
}
Button::Button(std::string name_new) {
    name = name_new;
    x = 0;
    y = 0;
    button_type = nButton;
    is_selected = false;
}
Button::Button(std::string name_new, int x_new, int y_new, bool is_selected_new) {
    name = name_new;
    x = x_new;
    y = y_new;
    button_type = nButton;
    is_selected = is_selected_new;
}
Button::Button(std::string name_new, int x_new, int y_new, bool is_selected_new, ButtonType button_type_new) {
    name = name_new;
    x = x_new;
    y = y_new;
    button_type = nButton;
    is_selected = is_selected_new;
}
std::string Button::get_name() {
    return name;
}
int Button::get_x() {
    return x;
}
int Button::get_y() {
    return y;
}
bool Button::get_is_selected() {
    return is_selected;
}
void Button::set_name(std::string name_new) {
    name = name_new;
}
void Button::set_is_selected(bool is_selected_new) {
    is_selected = is_selected_new;
}

Menu::Menu(int btn_num_row_new) {
    btn_num_row = btn_num_row_new;
    btn_num_col = 1;
    menu = new Button**[btn_num_row_new];
    for( int i = 0; i < btn_num_row_new; i++) {
        menu[i] = new Button*[1];
        menu[i][0] = NULL;
    }
}
Menu::Menu(int btn_num_row_new, int btn_num_col_new) {
    btn_num_row = btn_num_row_new;
    btn_num_col = btn_num_col_new;
    menu = new Button**[btn_num_row_new];
    for( int i = 0; i < btn_num_row_new; i++ ) {
        menu[i] = new Button*[btn_num_col_new];
        for( int j = 0; j < btn_num_col_new; j++ ) {
            menu[i][j] = NULL;
        }
    }
}
Button*** Menu::get_menu() {
    return menu;
}
void Menu::add_button(std::string name) {
    for(int i = 0; i < btn_num_col; i++) {
        for(int j = 0; j < btn_num_row; j++) {
            if(menu[j][i] == NULL)
                menu[j][i] = new Button(name, j, i, false);
        }
    }
}
void Menu::add_button(std::string name, int x, bool is_selected_new) {
    menu[x][0] = new Button(name, x, 0, is_selected_new);
}
void Menu::add_button(std::string name, int x, int y, bool is_selected_new) {
    menu[x][0] = new Button(name, x, y, is_selected_new);
}
void Menu::show() {
    system("clear");
    std::cout << "\n\t\t\t    - KAtomic -" << std::endl;
    for( int i = 0; i < btn_num_row; i++ ) {
    std::cout << "\n\t\t\t";
        for( int j = 0; j < btn_num_col; j++ ) {
            if(menu[i][j]->get_name().size() <= 5)
                std::cout << "       ";
            if(menu[i][j]->get_name().size() >= 7)
                std::cout << "      ";
            if(menu[i][j]->get_is_selected())
                std::cout << "\033[3;46m" << menu[i][j]->get_name() << "\033[0m";
            else 
                std::cout << menu[i][j]->get_name();
        }
        std::cout << std::endl << "\n\n";
    }
}
