#include "field.h"
#include "levelset.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int read_ref_atom_num(string level) {
	ifstream lvl_file(level);
	string str;
	int atom_num = 0;
	while(getline(lvl_file, str)) {
		if(str.find("atom") != string::npos) {
			atom_num++;
		}
		if(str.find("feld") != string::npos) {
			break;
		}
	}
	lvl_file.close();
	return atom_num;
}
int read_field_atom_num(string level) {
	ifstream lvl_file(level);
	string str;
	int temp = 0, i = 0;
	do{
		getline(lvl_file, str);
		if(str.find("feld") != string::npos) {
			for( int j = 0; j < 15; j++) {
				if ( str.at(j+8) != '.' && str.at(j+8) != '#' ) {
					temp++;
				}
			}
			i++;
		}
	}while(i < 15);
	lvl_file.close();
	return temp;
}
Atom* read_atoms(string atom_string, int num_of_atom) {
	Type type[11] = {H,C,O,N,S,F,Cl,Br,P,J,o};
	Bond bond[16] = {T, TR, R, BR, B, BL, L, TL, dT, dR, dB, dL, uT, uR, uB, uL};
	int type_num;
	string atom_type = atom_string.substr(0,atom_string.find("-"));
	string bond_type = atom_string.substr(atom_string.find("-")+1);
    istringstream(atom_type) >> type_num;
	int bond_num = bond_type.size();
	Bond *atom_bond = new Bond[bond_num];
	int temp;
	for ( int i = 0; i < bond_num; i++ ) {
		temp =  bond_array_num(bond_type.at(i));
		atom_bond[i] = bond[temp];
	}
	Atom* atom = new Atom(type[type_num-1], atom_bond, bond_num, num_of_atom);
	return atom;
}
void read_level_atoms(string level, Atom** atoms) {
	ifstream lvl_file(level);
	string str;
	int i = 0;
	while(getline(lvl_file, str)) {
		if(str.find("atom") != string::npos) {
			str = str.substr(str.find("=")+1);
			atoms[i] = read_atoms(str, i);
			i++;
		}
	}
	lvl_file.close();
}
void read_level(string level, Atom** atoms, FieldBlock* field_block, FieldAtom* field_atom) {
	ifstream lvl_file(level);
	string str;
	int temp, count = 0, i = 0;
	do{
		getline(lvl_file, str);
		if(str.find("feld") != string::npos) {
			for( int j = 0; j < 15; j++) {
				if (str.at(j+8) == '#' ) {
					field_block->add(i, j);
				}
				else if ( str.at(j+8) != '.' && str.at(j+8) != '#') {
					temp = char_to_int(str.at(j+8));
					field_atom->add(i, j, atoms[temp-1], count);
					count++;
				}
			}
			i++;
		}
	}while(i < 15);
	lvl_file.close();
}
int read_target_line_num(string level) {
	ifstream lvl_file(level);
	string str;
	int lines_num = 0;
	while(getline(lvl_file, str)) {
		if (str.find("mole") != string::npos)
			lines_num++;
	}
	lvl_file.close();
	return lines_num;
}
string* read_target_struct(string level, int lines_num) {
	string* target_struct = new string[lines_num];
	ifstream lvl_file(level);
	string str;
	int i = 0;
	do {
		getline(lvl_file, str);
		if (str.find("mole") != string::npos) {
			target_struct[i] = str.substr(str.find("=")+1);
			i++;
		}
	}while(i < lines_num);
	lvl_file.close();
	return target_struct;
}
string* read_field_struct(Atom*** field_atom) {
	size_t size = 15;
	string* field_struct = new string[15];
	string blanc(size, ' ');
	for(int i = 0; i < 15; i++) {
		field_struct[i] = blanc;
		for(int j = 0; j < 15; j++) {
			if(field_atom[i][j] != NULL)
				field_struct[i].at(j) = '0' + (char)(field_atom[i][j]->get_num_of_atom()+1);
			else 
				field_struct[i].at(j) = '.';
		}
	}
	return field_struct;
}
int** get_target_pos(string* target_struct, int atom_num, int lines_num) {
    int** target_pos = new int*[atom_num];
    for(int i = 0; i < atom_num; i++) {
        target_pos[i] = new int[2];
    }
    int size_column = target_struct[0].size();
    int number_of_atom;
    for(int i = 0; i < lines_num; i++) {
        for (int j = 0; j < size_column; j++)
        {
            if(target_struct[i].at(j) != '.') {
                number_of_atom = char_to_int(target_struct[i].at(j)) - 1;
                target_pos[number_of_atom][0] = i;
                target_pos[number_of_atom][1] = j;
            }
        }
    }
    for(int i = 1; i < atom_num; i++) {
        for (int j = 0; j < 2; j++)
        {
            target_pos[i][j] -= target_pos[0][j];
        }
    }
    target_pos[0][0] = 0;
    target_pos[0][1] = 0;
    return target_pos;
}