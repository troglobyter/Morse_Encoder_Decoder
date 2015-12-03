#ifndef MORSE_TRANSLATOR_H_
#define MORSE_TRANSLATOR_H_

#include "Binary_Tree.h"
#include "Hash_Table_Open.h"
#include "Morse_Data.h"
#include <fstream>


class Morse_Translator{
public:
	void make_BST_BT(std::ifstream& inFstream);
	std::string letter_to_Morse(const char the_letter) const;
	char Morse_to_letter(const std::string& the_morse_code) const;

private:
	KW::hash_map<char, std::string> letter_to_morse_code_hash_table;
	Binary_Tree<Morse_Data> morse_code_to_letter_tree;

	void selection_sort(Morse_Data arr[], const size_t mc_elements) const;
};
#endif