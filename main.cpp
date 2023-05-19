#include "field.h"
#include "levelset.h"
#include "menu.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
//  	Atom** atoms;
//	FieldAtom* field_atom = new FieldAtom;
//	FieldBlock* field_block = new FieldBlock;
//	Field field(field_atom, field_block);
	string level, prefix, suffix, str, input;
	string *target_struct, *target_struct_name, *field_struct;
	int level_number, ref_atom_num, field_atom_num, target_line_num, temp;
	int level_num = 83, turn = 1;
	char dir;
	prefix = string("levels/level_");
	suffix = string("");
	string dummy;

	int btn_num = 2;
	Menu menu(2);
	int btn_selected = 0;
	menu.add_button("Start", 0, true);
	menu.add_button("Exit");
	while(1) {
		menu.get_menu()[btn_selected][0]->set_is_selected(true);
		menu.show();
		menu.get_menu()[btn_selected][0]->set_is_selected(false);
		std::cin >> input;
		if (input == "e" || input == "E") {
			if (btn_selected == 0)
				break;
			if (btn_selected == 1)
				return 0;
		}
		btn_selected++;
		if(btn_selected > (btn_num-1))
			btn_selected = 0;
	}
	for(level_number = 1; level_number <= level_num; level_number++) {
		Atom** ref_atoms;
		FieldAtom* field_atom = new FieldAtom;
		FieldBlock* field_block = new FieldBlock;
		Field field(field_atom, field_block);
		level = prefix + to_string(level_number) + suffix;
		field.set_level_number(level_number);
		turn = 1;

		ref_atom_num = read_ref_atom_num(level);
		field_atom_num = read_field_atom_num(level);
		target_line_num = read_target_line_num(level);

		ref_atoms = new Atom*[ref_atom_num]; // remember to delete[] this
		read_level_atoms(level, ref_atoms);
		field_atom->set_atom_num(field_atom_num);
		field_atom->init_atom_pos();
		read_level(level, ref_atoms, field_block, field_atom);
		
		target_struct = read_target_struct(level, target_line_num);  // remember to delete[] this
		target_struct_name = name_of_struct(target_struct, ref_atoms, target_line_num);
		field_struct = read_field_struct(field_atom->get_field_atom());
		field.set_target_struct_name(target_struct_name);
		field.set_target_line_num(target_line_num);
		field.set_target_struct(target_struct);
		field.set_field_struct(field_struct);
//		target_pos = get_target_pos(target_struct, ref_atom_num, target_line_num); // remember to delete[] this

		field.show();

		while(1) {
			cout << " Input> ";
			std::cin >> input;
			stringstream(input) >> temp;
			if (in_range(temp, 1, field_atom->get_atom_num())) {
				stringstream(input) >> turn;
				dir = 'n';
			} else {
				dir = input.at(0);
			}
			if (in_range(turn, 1, field_atom->get_atom_num()) && valid_dir(dir)) {
				field.move(turn, dir);
			}
			field.set_turn(turn-1);
			field.show();
			if(field.check_completion(field_struct, target_struct)) {
				cout << "\t\t\tWell Done! Enter anything to move to the next level> ";
				cin >> dummy;
				break;
			}
		}
		delete field_atom;
		delete field_block;
		delete[] ref_atoms;
	}
	return 0;
}
