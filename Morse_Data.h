#ifndef MORSE_DATA_H_
#define MORSE_DATA_H_
#include <string>
#include <array>
#include <algorithm>


/** Morse Code Object with letter and associated string of .'s and -'s. Maximum length of string is 4.**/
struct Morse_Data{
	//Data fields.
	char letter;
	std::string morse_code;
	size_t length_morse_code;
	size_t order;
	static const std::string MORSE_CODE_STRINGS[30];
	// Constructor
	Morse_Data(const char alpha = ' ', const std::string& dots_dashes = "") : letter(alpha), morse_code(dots_dashes), length_morse_code(morse_code.length()), order(get_order()){}
	size_t get_order() const;
}; //* End Morse_Data

const std::string Morse_Data::MORSE_CODE_STRINGS[30] = { ".", "-", "..", ".-", "-.", "--", "...", "..-", ".-.", ".--", "-..", "-.-", "--.", "---", "....", "...-", "..-.", "..--", ".-..", ".-.-", ".--.", ".---", "-...", "-..-",
										"-.-.", "-.--", "--..", "--.-", "---.", "----" };

size_t Morse_Data::get_order() const{
	for (int i = 0; i < 30; i++){
		auto it = find(MORSE_CODE_STRINGS, MORSE_CODE_STRINGS + 29, morse_code);
		if (it > MORSE_CODE_STRINGS +29)
			return 31;
		return it-MORSE_CODE_STRINGS;
	}
}
#endif