#include<iostream>
#include<vector>
#include<string>
#include "aes.h"

using namespace std;

int main() {
    // string str_128 = "2b7e151628aed2a6abf7158809cf4f3c";
    // string str_192 = "8e73b0f7da0e6452c810f32b809079e562f8ead2522c6b7b";
    // string str_256 = "603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4";
    // string str_key = str_128; // randomKeyString(nk = 4, 6, 8);
    // unsigned int *key = hexString_to_block(str_key); // randomKey(nk = 4, 6, 8);
    // int nk = str_key.length() / 8;
    // int nr = nk + 6;
    // unsigned int *roundKey = keyExpansion(key, nk, nr);

    // string plaintext = vectorHex_to_string(hexString_to_vectorHex(str_128));
    // vector<unsigned char> v = string_to_vectorHex(plaintext);
    
    // vector<unsigned char> cipher;
    // for (int i = 0; i < v.size() / 16; i++) {
    //     unsigned int *m = vectorHex_to_block(vector<unsigned char>(v.begin() + i * 16, v.begin() + (i + 1) * 16));
    //     vector<unsigned char> temp = block_to_vectorHex(encrypt(m, roundKey, nk, nr));
    //     cipher.insert(cipher.end(), temp.begin(), temp.end());
    // }
    
    // vector<unsigned char> decipher;
    // for (int i = 0; i < cipher.size() / 16; i++) {
    //     unsigned int *m = vectorHex_to_block(vector<unsigned char>(cipher.begin() + i * 16, cipher.begin() + (i + 1) * 16));
    //     vector<unsigned char> temp = block_to_vectorHex(decrypt(m, roundKey, nk, nr));
    //     decipher.insert(decipher.end(), temp.begin(), temp.end());
    // }

    // showMatrix(vectorHex_to_block(cipher));

    // print_vectorHex(v); cout << endl;
    // print_vectorHex(cipher); cout << endl;
    // print_vectorHex(decipher); cout << endl;

    // cout << "\nKey hex: " << str_key << endl;
    // cout << "\nPlain hex: " << vectorHex_to_hexString(v) << endl;
    // cout << "\nCipher hex: " << vectorHex_to_hexString(cipher) << endl;
    // cout << "\nDecipher hex: " << vectorHex_to_hexString(decipher) << endl;

    // cout << "\nPlaintext: " << plaintext << endl;
    // string ciphertext = vectorHex_to_string(cipher);
    // cout << "\nCiphertext: " << ciphertext << endl;
    // string deciphertext = vectorHex_to_string(decipher);
    // cout << "\nDeciphertext: " << deciphertext << endl;

    // print_vectorHex(hexString_to_vectorHex(str_128));
    // print_vectorHex(hexString_to_vectorHex(str_192));
    // print_vectorHex(hexString_to_vectorHex(str_256));

    // delete[] key, roundKey;

    vector<unsigned char> v = string_to_vectorHex("hello world");
    print_vectorHex(v);
    return 0;
}

/*
1. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Proin in leo in justo efficitur tristique.
2. Phasellus justo odio, gravida at arcu ut, consequat condimentum ante. Sed quis purus ipsum. Nullam sed metus nec lacus tincidunt consectetur.
3. Fusce at sem non nisi accumsan scelerisque. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas.
4. Curabitur sit amet mauris eget lectus pharetra porttitor. Sed sagittis justo at lacus ultricies, vel cursus erat suscipit.
5. Nunc sit amet justo sed tortor efficitur consequat eget non quam. Phasellus eu dolor sit amet mauris ullamcorper varius.
*/