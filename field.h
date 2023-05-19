#ifndef FIELDH
#define FIELDH
#include <iostream>

enum Type{H,O,C,N,S,F,Cl,Br,P,J,o};
enum Bond{T,TR,R,BR,B,BL,L,TL,dT,dTR,dR,dBR,dB,dBL,dL,dTL,uT,uTR,uR,uBR,uB,uBL,uL,uTL};

char type_to_name(Type type);
int bond_array_num(char ch);
int char_to_int (char ch);
bool in_range(int input, int minimum, int maximum);
bool valid_dir(char dir);

class Block {
 private:
	
 public:
  Block(){}
};

class Atom {
 private:
  Type type;
  int bond_num;
  Bond *bond;
  int num_of_atom;

 public:
  Atom(){}
  Atom(Type type_new, Bond *bond_new, int bond_num_new, int num_of_atom_new);
  ~Atom();
  Type get_type();
  Bond* get_bond();
  int get_bond_num();
  int get_num_of_atom();
  char get_name();
};

class FieldAtom {
 private:
  Atom*** field_atom;
  int** atom_pos;
  int atom_num;
 public:
  FieldAtom();
  ~FieldAtom();
  Atom*** get_field_atom();
  void add(int row, int column, Atom* atom, int count);
  void init_atom_pos();
  int** get_atom_pos();
  void set_atom_num(int atom_num_new);
  int get_atom_num();
};

class FieldBlock {
 private:
  Block*** field_block;
 public:
  FieldBlock();
  ~FieldBlock();
  Block*** get_field_block();
  void add(int row, int column);
};

class Field {
 private:
  FieldAtom* field_atom;
  FieldBlock* field_block;
  std::string* target_struct, *field_struct, *target_struct_name;
  int level_number, turn, target_line_num;;
  int search_bond(int i, int j, Bond bond_new);
  int search_turn(int x, int y);
  void print_symbol(int i, int j, int line_break);

 public:
  Field(FieldAtom* field_atom_new, FieldBlock* field_block_new);
  ~Field();
  void set_turn(int turn_new);
  int get_turn();
  void set_target_struct(std::string* target_struct_new);
  void set_target_struct_name(std::string* target_struct_name_new);
  void set_field_struct(std::string* field_struct_new);
  void set_target_line_num(int target_line_num_new);
  int get_target_line_num();
  void set_level_number(int level_number_new);
  void move(int num, char dir);
  void show();
  bool check_completion(std::string* field_struct, std::string* target_struct);
};


std::string* name_of_struct(std::string* target_struct, Atom** atoms, int lines_num);

#endif