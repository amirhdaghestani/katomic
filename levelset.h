#ifndef LEVELSET
#define LEVELSET
#include "field.h"
#include <string>

int read_ref_atom_num(std::string level);
int read_field_atom_num(std::string level);
Atom* read_atoms(std::string atom_string, int num_of_atom);
void read_level_atoms(std::string level, Atom** atoms);
void read_level(std::string level, Atom** atoms, FieldBlock* field_block, FieldAtom* field_atom);
int read_target_line_num(std::string level);
std::string* read_target_struct(std::string level, int lines_num);
std::string* read_field_struct(Atom*** field_atom);
int** get_target_pos(std::string* target_struct, int atom_num, int lines_num);

#endif