#include "field.h"
#include <iostream>

using namespace std;

string* name_of_struct(string* target_struct, Atom** atoms, int lines_num) {
    int str_length = target_struct[0].size();
    string temp;
    string* nstr = new string[str_length];
    for( int i = 0 ; i < lines_num; i++ ) {
        temp = target_struct[i];
        for(int j = 0; j < str_length; j++)
        {
            if (target_struct[i].at(j) != '.') 
                temp.at(j) = atoms[char_to_int(target_struct[i].at(j))-1]->get_name();
            else
                temp.at(j) = '.';
        }
        nstr[i] = temp;
    }
    return nstr;
}
bool in_range(int input, int minimum, int maximum) {
	if(minimum <= input && input <= maximum)
		return true;
	return false;
}
bool valid_dir(char dir) {
	if ( dir == 'w' || dir == 's' || dir == 'a' || dir == 'd' )
		return true;
	return false;
}
char type_to_name(Type type) {
    switch(type) {
	    case H:
		    return 'H';
		    break;
	    case C:
		    return 'C';
		    break;
	    case O:
		    return 'O';
		    break;
	    case N:
		    return 'N';
		    break;
	    case S:
		    return 'S';
		    break;
	    case F:
		    return 'F';
		    break;
	    case Cl:
		    return 'X';
		    break;
	    case Br:
		    return 'B';
		    break;
        case P:
		    return 'P';
		    break;
        case J:
		    return 'J';
		    break;
        case o:
		    return 'o';
		    break;
	    default:
		    break;
    }
    return ' ';
}

int bond_array_num(char ch) {
    switch (ch)
        {
        case 'a':
            return 0;
            break;
        case 'b':
            return 1;
            break;
        case 'c':
            return 2;
            break;
        case 'd':
            return 3;
            break;
        case 'e':
            return 4;
            break;
        case 'f':
            return 5;
            break;
        case 'g':
            return 6;
            break;
        case 'h':
            return 7;
            break;
        case 'A':
            return 8;
            break;
        case 'B':
            return 9;
            break;
        case 'C':
            return 10;
            break;
        case 'D':
            return 11;
            break;
        case 'E':
            return 12;
            break;
        case 'F':
            return 13;
            break;
        case 'G':
            return 14;
            break;
        case 'H':
            return 15;
            break;
        default:
            return 0;
            break;
    }
}

int char_to_int (char ch) {
    switch (ch)
        {
        case 'a':
            return 10;
            break;
        case 'b':
            return 11;
            break;
        case 'c':
            return 12;
            break;
        case 'd':
            return 13;
            break;
        case 'e':
            return 14;
            break;
        case 'f':
            return 15;
            break;
        case 'g':
            return 16;
            break;
        case 'h':
            return 17;
            break;
        case 'i':
            return 18;
            break;
        case 'j':
            return 19;
            break;
        case 'k':
            return 20;
            break;
        case 'l':
            return 21;
            break;
        case 'm':
            return 22;
            break;
        case 'n':
            return 23;
            break;
        case 'o':
            return 24;
            break;
        case 'p':
            return 25;
            break;
        case 'q':
            return 26;
            break;
        case 'r':
            return 27;
            break;
        case 's':
            return 28;
            break;
    default:
        return ((int)ch - (int)'0');
        break;
    }
}

Atom::Atom(Type type_new, Bond *bond_new, int bond_num_new, int num_of_atom_new) {
    type = type_new;
    bond_num = bond_num_new;
    bond = new Bond[bond_num];
    bond = bond_new;
    num_of_atom = num_of_atom_new;
}
Atom::~Atom() {
    delete[] bond;
}
Type Atom::get_type() {
    return type;
}
Bond* Atom::get_bond() {
    return bond;
}
int Atom::get_bond_num() {
    return bond_num;
}
char Atom::get_name() {
    return type_to_name(type);
}
int Atom::get_num_of_atom() {
    return num_of_atom;
}


FieldAtom::FieldAtom() {
    atom_num = 0;
    field_atom = new Atom**[15];
    for ( int i=0; i<15; i++ ) {
        field_atom[i] = new Atom*[15];
        for ( int j=0; j<15; j++ )
            field_atom[i][j] = NULL;
    }
}
FieldAtom::~FieldAtom() {
    for (int i = 0; i < 15; i++)
        delete[] field_atom[i];
    delete[] field_atom;
}
Atom*** FieldAtom::get_field_atom() {
    return field_atom;
}
void FieldAtom::add( int row, int column, Atom* atom, int count ) {
    field_atom[row][column] = atom;
    atom_pos[count][0] = row;
    atom_pos[count][1] = column;
}
void FieldAtom::init_atom_pos() {
    atom_pos = new int*[atom_num];
    for(int i = 0; i < atom_num; i++) {
        atom_pos[i] = new int[2];
    }
}
void FieldAtom::set_atom_num(int atom_num_new) {
    atom_num = atom_num_new;
}
int FieldAtom::get_atom_num() {
    return atom_num;
}
int** FieldAtom::get_atom_pos() {
    return atom_pos;
}

FieldBlock::FieldBlock()
{
    field_block = new Block**[15];
    for ( int i = 0; i < 15; i++ ) {
        field_block[i] = new Block*[15];
        for ( int j=0; j<15; j++ ) {
            field_block[i][j] = NULL;
        }
    }
}
FieldBlock::~FieldBlock() {
    for( int i = 0; i < 15; i++ )
        delete[] field_block[i];
    delete[] field_block;
}
Block*** FieldBlock::get_field_block() {
    return field_block;
}
void FieldBlock::add(int row, int column) {
    field_block[row][column] = new Block();
}


Field::Field(FieldAtom* field_atom_new, FieldBlock* field_block_new) {
    turn = 0;
    level_number = 1;
    field_atom = field_atom_new;
    field_block = field_block_new;
}
Field::~Field() {}
void Field::set_level_number(int level_number_new) {
    level_number = level_number_new;
}
void Field::set_turn(int turn_new) {
    turn = turn_new;
}
int Field::get_turn() {
    return turn;
}
void Field::set_target_struct(string* target_struct_new) {
    target_struct = target_struct_new;
}
void Field::set_target_struct_name(string* target_struct_name_new) {
    target_struct_name = target_struct_name_new;
}
void Field::set_field_struct(string* field_struct_new) {
    field_struct = field_struct_new;
}
void Field::set_target_line_num(int target_line_num_new) {
    target_line_num = target_line_num_new;
}
int Field::get_target_line_num() {
    return target_line_num;
}
void Field::move(int num, char dir) {
    int i = 0, j = 0, x, y, x_old, y_old;
    num--;
    switch (dir)
    {
        case 'd':
            j = 1;
            break;
        case 'w':
            i = -1;
            break;
        case 's':
            i = 1;
            break;
        case 'a':
            j = -1;
            break;
        default:
            break;
    }
    x = field_atom->get_atom_pos()[num][0];
    y = field_atom->get_atom_pos()[num][1];
    x_old = x;
    y_old = y;
    if (field_atom->get_field_atom()[x+i][y+j] == NULL && field_block->get_field_block()[x+i][y+j] == NULL) {
        x += i;
        y += j;
        while( in_range(x, 0, 14) && in_range(y, 0, 14) ) {
            if (field_atom->get_field_atom()[x][y] != NULL || field_block->get_field_block()[x][y] != NULL)
                break;
            x += i;
            y += j;
        }
        field_atom->get_atom_pos()[num][0] = x-i;
        field_atom->get_atom_pos()[num][1] = y-j;
        field_atom->get_field_atom()[x-i][y-j] = field_atom->get_field_atom()[x_old][y_old];
        field_atom->get_field_atom()[x_old][y_old] = NULL;
        field_struct[x-i].at(y-j) = field_struct[x_old].at(y_old);
        field_struct[x_old].at(y_old) = '.';
    }
}
int Field::search_bond( int i, int j, Bond bond_new) {
    for( int k = 0; k < field_atom->get_field_atom()[i][j]->get_bond_num(); k++) {
        if (field_atom->get_field_atom()[i][j]->get_bond()[k] == bond_new)
            return true;
    }
    return false;
}
int Field::search_turn(int x, int y) {
    int temp, atom_num;
    int** atom_pos = field_atom->get_atom_pos();
    atom_num = field_atom->get_atom_num();
    for (int i = 0; i < atom_num; i++)
        if (atom_pos[i][0] == x) {
            if (atom_pos[i][1] == y)
                temp = i+1;
        }
    return temp;
}
void Field::print_symbol( int i, int j, int line_break) {
    Bond bond_all[] = {TL, T, TR, L, R, BL, B, BR, dTL, dT, dTR, dL, dR, dBL, dB, dBR, uTL, uT, uTR, uL, uR, uBL, uB, uBR};
    char ch[] = {'\\', '|', '/', '-', '-','/','|','\\', ' ', 'd', ' ', '=', '=', ' ', 'd', ' ', ' ', 't', ' ', 'p', 'p', ' ', 't', ' '};
    int counter = 0, chki, chkii, trn;
    if (line_break == 1)
        counter = 3;
    else if (line_break == 2)
        counter = 5;

    for( int x = 0; x < 3; x++) {
        if (x == 0)
            cout << "  ";
        chki = search_bond(i, j, bond_all[counter+8]);
        chkii = search_bond(i, j, bond_all[counter+16]);
        if (chki)
            counter += 8;
        if (chkii)
            counter += 16;

        if (line_break != 1 && search_bond(i, j, bond_all[counter])) {
            if (ch[counter] == 'd')
                cout << "\u01C1";
            else if( ch[counter] == 't')
                cout << "\u2980";
            else
                cout << ch[counter];
        }
        else if(line_break != 1)
            cout << " ";
        else if (x != 1 && search_bond(i, j, bond_all[counter]) )
            if( ch[counter] == 'p')
                cout << "\u2261";
            else
                cout << ch[counter];
        else if (x != 1)
            cout << " ";
        else
        {
            if (field_atom->get_atom_pos()[turn][0] == i && field_atom->get_atom_pos()[turn][1] == j)
                cout << "\033[6;45m" << field_atom->get_field_atom()[i][j]->get_name() << "\033[0m";
            else
                cout << "\033[1;45m" << field_atom->get_field_atom()[i][j]->get_name() << "\033[0m";
            counter--;
        }
        if (x == 2 && line_break != 1)
            cout << "  ";
        else if (x == 2) {
            trn = search_turn(i, j);
            if (trn <= 9)
                cout << trn << " ";
            else 
                cout << trn;
        }
        counter++;
        if (chki)
            counter -= 8;
    }
}
void Field::show() {
    system("clear");
    cout << "\n\t\t\t\t\t    KAtomic  - Level "<< level_number << endl;
    cout << " [Target Structure]" << endl;
    for(int i = 0; i < target_line_num; i++)
        if(target_struct_name[i] != "")
            cout << " "<< target_struct_name[i] << endl;
    for ( int i=0; i<15; i++ ) {
        for ( int k = 0; k < 3; k++) {
            for ( int j=0; j<15; j++ ) {
                if (field_atom->get_field_atom()[i][j] == NULL && field_block->get_field_block()[i][j] == NULL)
                    cout << "       ";
                else if (field_atom->get_field_atom()[i][j] != NULL) {
                    print_symbol(i, j, k);
                }
                else if (k == 1)
                    cout << "   \033[1;40m#\033[0m   "; 
                else
                    cout << "       ";
            }
            cout << endl;
        }
    }
}
bool Field::check_completion(string* field_struct, string* target_struct) {
	int counter = 0, loc_first_line_atom = 0, column_size = 0;
    string str;
    column_size = target_struct[0].size();
	for(int i = 0; i < 15; i++) {
		if (field_struct[i].find(target_struct[0]) != string::npos) {
            loc_first_line_atom = field_struct[i].find(target_struct[0]);
            for(int j = 0; j < target_line_num; j++) {
                str = field_struct[i+j].substr(loc_first_line_atom, column_size);
                if (str == target_struct[j]) 
                    counter++;
                else
                    break;
            }
            break;
        }
	}
	if (counter == target_line_num)
		return true;
    return false;
}