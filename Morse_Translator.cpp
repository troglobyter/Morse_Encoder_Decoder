#include "Morse_Translator.h"
#include <iostream> //needed for error msgs

void Morse_Translator::make_HASH_TABLE_BT(std::ifstream& inFstream){
	
	//Open the morse code file
	inFstream.open("morse.txt");

	//Check to see if file opened correctly
	if (!inFstream)
	{
		// Print Error And Exit
		std::cerr << "/n/nMorse code file not found... /n";
		system("pause");
		exit(0);
	}

	
	//**Variables needed for creating hash table and binary tree.
	std::string alpha_dots_dashes, Morse_Code_string;
	Morse_Data Morse_Code_Obj_Array[30];
	char Letter;
	int arr_index = 0;

	//**Read from input file, create Morse_Data objects and store in an array.
	while (inFstream >> alpha_dots_dashes){
		Letter = alpha_dots_dashes[0];
		Morse_Code_string = alpha_dots_dashes.substr(1);
		Morse_Data Morse_Code_Obj(Letter, Morse_Code_string);
		Morse_Code_Obj_Array[arr_index] = Morse_Code_Obj;
		++arr_index;
	}

	//**Sort array of Morse_Data objects.
	selection_sort(Morse_Code_Obj_Array, arr_index + 1);

	//**Begin with empty Morse_Data root node to binary tree.
	Morse_Data Empty_Morse_Data;
	morse_code_to_letter_tree.setRoot(new BTNode<Morse_Data>(Empty_Morse_Data));

	//**Create binary tree nodes one at a time from the Morse_Data sorted array.
	for (int i = 0; i <= arr_index; i++){
		Morse_Data Morse_Code_Obj = Morse_Code_Obj_Array[i];
		BTNode<Morse_Data>* current = morse_code_to_letter_tree.getRoot();

		//**Use Morse_Data morse_code string one character at a time to traverse tree to the appropriate node.
		for (int i = 0; i < Morse_Code_Obj.length_morse_code; ++i){
			if (Morse_Code_Obj.morse_code[i] == '.')
				current = current->left;
			else if (Morse_Code_Obj.morse_code[i] == '-')
				current = current->right;
			else
			// Print Error And Exit!
			std::cerr << "/n/nError creating morse code binary tree... /n";
			system("pause");
			exit(0);
		}
		//**Add the Morse_Data object to the binary tree.
		bool valid_insert = morse_code_to_letter_tree.insert(current, Morse_Code_Obj);
		//**Hash based on the Morse_Data object letter as key and Morse_Data object morse_code string as value.
		letter_to_morse_code_hash_table[Morse_Code_Obj.letter] = Morse_Code_Obj.morse_code;
	}
	return;
}

std::string Morse_Translator::letter_to_Morse(const char the_letter) const{
	try {
		std::string the_morse_code_string = letter_to_morse_code_hash_table[the_letter];
		return the_morse_code_string;
	}
	catch(...){
		//**Exception when item not found.
		return "0000";
	}
}

char Morse_Translator::Morse_to_letter(const std::string& the_morse_code) const{
	
	BTNode<Morse_Data>* current = morse_code_to_letter_tree.getRoot();
	std::string::const_iterator c_itr;

	//**Move the BTNode<Morse_Data> pointer through the tree according to the dots and dashes
	//**in the passed string the_morse_code.
	for (c_itr = the_morse_code.cbegin(); c_itr != the_morse_code.cend(); c_itr++){
		if (*c_itr == '.'){
			BTNode<Morse_Data>* left = current->left;
			current = left;
		}
		else if (*c_itr == '-'){
			BTNode<Morse_Data>* right = current->right;
			current = right;
		}
		else
		// Print Error And Exit!
			std::cerr << "/n/nError in translating morse code to text... /n";
			system("pause");
			exit(0);
	}
	return current->data.letter;
}

//**Standard selection sort sorting based on the Morse_Data object's order variable which is assigned when constructed
//**according to the defined Morse_Data member string array.
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
