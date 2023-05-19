#ifndef MENU
#define MENU
#include <iostream>
#include <string>

enum ButtonType{nButton, Submit};

class Button {
 private:
   int x,y;
   ButtonType button_type;
   std::string name;
   bool is_selected;
 public:
    Button();
    Button(std::string name_new);
    Button(std::string name_new, int x_new, int y_new, bool is_selected_new);
    Button(std::string name_new, int x_new, int y_new, bool is_selected_new, ButtonType button_type_new);
    std::string get_name();
    int get_x();
    int get_y();
    bool get_is_selected();
    void set_name(std::string name_new);
    void set_is_selected(bool is_selected_new);
};

class Menu {
 private:
   int btn_num_row;
   int btn_num_col;
   Button*** menu;
 public:
    Menu(int btn_num_row_new);
    Menu(int btn_num_row_new, int btn_num_col_new);
    Button*** get_menu();
    void add_button(std::string name);
    void add_button(std::string name, int x, bool is_selected_new);
    void add_button(std::string name, int x, int y, bool is_selected_new);
    void change_selected_button(int btn_selected);
    void show();
};
#endif