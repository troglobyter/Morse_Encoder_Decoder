#include "Morse_Translator.h"

void Morse_Translator::make_HASH_TABLE_BT(std::ifstream& inFstream){
	std::string alpha_dots_dashes, Morse_Code_string;
	Morse_Data Morse_Code_Obj_Array[30];
	char Letter;
	int arr_index = 0;
	while (inFstream >> alpha_dots_dashes){
		Letter = alpha_dots_dashes[0];
		Morse_Code_string = alpha_dots_dashes.substr(1);
		Morse_Data Morse_Code_Obj(Letter, Morse_Code_string);
		Morse_Code_Obj_Array[arr_index] = Morse_Code_Obj;
		++arr_index;
	}

	selection_sort(Morse_Code_Obj_Array, arr_index + 1);

	Morse_Data Empty_M_Data;
	morse_code_to_letter_tree.setRoot(new BTNode<Morse_Data>(Empty_M_Data));
	for (int i = 0; i <= arr_index; i++){
		Morse_Data Morse_Code_Obj = Morse_Code_Obj_Array[i];
		BTNode<Morse_Data>* current = morse_code_to_letter_tree.getRoot();
		for (int i = 0; i < Morse_Code_Obj.length_morse_code; ++i){
			if (Morse_Code_Obj.morse_code[i] == '.')
				current = current->left;
			else if (Morse_Code_Obj.morse_code[i] == '-')
				current = current->right;
			//else
				//error
		}
		bool valid_insert = morse_code_to_letter_tree.insert(current, Morse_Code_Obj);
		letter_to_morse_code_hash_table[Morse_Code_Obj.letter] = Morse_Code_Obj.morse_code;
	}
	return;
}

void Morse_Translator::selection_sort(Morse_Data arr[], const size_t mc_elements) const {
	for (int fill = 0; fill < (mc_elements - 1); ++fill) {
		int pos_min = fill;
		for (int next = fill + 1; next < mc_elements; ++next) {

			if (arr[next].order < arr[pos_min].order)
				pos_min = next;

		}
		if (fill != pos_min){
			std::swap(arr[pos_min], arr[fill]);
		}
	}
	return;
}