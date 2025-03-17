#pragma once
#include<iostream>
#include<stdio.h>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<vector>
#include<string>

using namespace std;

const int nb = 4; // number of columns (32-bit words) comprising the state
int _nk, _nr;
// nk = 4, 6, 8
// nr = 10, 12, 14

void set_nr() {
    _nr = _nk + 6;
}

void set_nk(string key) {
    _nk = key.length() / 8;
    set_nr();
}

void set_nk(int nk) {
    _nk = nk;
    set_nr();
}

void insert_v1_into_v2();

// S-box
const int S[] = {
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

// Inverse S-box
const int IS[] = {
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
    0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
    0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
    0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
    0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};


//--------------------------------component--------------------------------
void showMatrix(unsigned int *m) {
    unsigned int *rs = new unsigned int[4];
    rs[0] = ((m[0] << 0) & 0xff000000) | ((m[1] >> 8) & 0xff0000) | ((m[2] >> 16) & 0xff00) | ((m[3] >> 24) & 0xff);
    rs[1] = ((m[0] << 8) & 0xff000000) | ((m[1] >> 0) & 0xff0000) | ((m[2] >> 8) & 0xff00) | ((m[3] >> 16) & 0xff);
    rs[2] = ((m[0] << 16) & 0xff000000) | ((m[1] << 8) & 0xff0000) | ((m[2] >> 0) & 0xff00) | ((m[3] >> 8) & 0xff);
    rs[3] = ((m[0] << 24) & 0xff000000) | ((m[1] << 16) & 0xff0000) | ((m[2] << 8) & 0xff00) | ((m[3] >> 0) & 0xff);

    for (int i = 0; i < 4; i++) {
        // printf("\t%08x\n", m[i]);// word
        printf("\t%08x\n", rs[i]);
    }
}

unsigned int *XOR(unsigned int *m1, unsigned int *m2) {
    unsigned int *rs = new unsigned int[4];
    rs[0] = m1[0] ^ m2[0];
    rs[1] = m1[1] ^ m2[1];
    rs[2] = m1[2] ^ m2[2];
    rs[3] = m1[3] ^ m2[3];
 
    return rs;
}

unsigned int nhan2(unsigned int w) {
    /*
    Kiểm tra bit cao nhất (rs & 0x80):
    0x80 là hằng số nhị phân 10000000. Phép toán rs & 0x80 kiểm tra 
    xem bit cao nhất (bit thứ 7) của rs có bằng 1 hay không. 
    Nếu bit cao nhất bằng 1, điều đó có nghĩa là phép dịch trái đã làm 
    tràn bit ra ngoài byte 8-bit.
    
    Phép XOR với 0x1b (rs ^= 0x1b):
    0x1b là hằng số nhị phân 00011011. Trong trường hợp 
    bit cao nhất của rs bằng 1, chúng ta cần thực hiện phép XOR với 0x1b 
    để thực hiện phép nhân modulo với đa thức không thể chia x^8 + x^4 + x^3 + x + 1 
    (được biểu diễn bởi 0x1b trong nhị phân). Điều này đảm bảo rằng 
    kết quả của phép nhân vẫn nằm trong trường Galois GF(2^8).
    */
    unsigned int rs = w << 1;
    if ((rs & 0x80) != 0) {
        rs ^= 0x1b;
    }

    return rs & 0xff;
}

unsigned int nhan3(unsigned int w) {
    return nhan2(w) ^ w;
}

unsigned int nhan9(unsigned int w) {
    return (nhan2(nhan2(nhan2(w))) ^ w);
}

unsigned int nhanB(unsigned int w) {
    return (nhan2(nhan2(nhan2(w))) ^ nhan2(w) ^ w);
}

unsigned int nhanD(unsigned int w) {
    return (nhan2(nhan2(nhan2(w))) ^ nhan2(nhan2(w)) ^ w);
}

unsigned int nhanE(unsigned int w) {
    return (nhan2(nhan2(nhan2(w))) ^ nhan2(nhan2(w)) ^ nhan2(w));
}

unsigned int nhanCot_encrypt(unsigned int w) {
    unsigned int *rs = new unsigned int[4];
    unsigned int byte1 = (w >> 24) & 0xff;
    unsigned int byte2 = (w >> 16) & 0xff;
    unsigned int byte3 = (w >> 8) & 0xff;
    unsigned int byte4 = w & 0xff;
    rs[0] = nhan2(byte1) ^ nhan3(byte2) ^ byte3 ^ byte4;
    rs[1] = byte1 ^ nhan2(byte2) ^ nhan3(byte3) ^ byte4;
    rs[2] = byte1 ^ byte2 ^ nhan2(byte3) ^ nhan3(byte4);
    rs[3] = nhan3(byte1) ^ byte2 ^ byte3 ^ nhan2(byte4);
    return (rs[0] << 24) | (rs[1] << 16) | (rs[2] << 8) | rs[3];
}

unsigned int nhanCot_decrypt(unsigned int w) {
    unsigned int *rs = new unsigned int[4];
    unsigned int byte1 = (w >> 24) & 0xff;
    unsigned int byte2 = (w >> 16) & 0xff;
    unsigned int byte3 = (w >> 8) & 0xff;
    unsigned int byte4 = w & 0xff;
    rs[0] = nhanE(byte1) ^ nhanB(byte2) ^ nhanD(byte3) ^ nhan9(byte4);
    rs[1] = nhan9(byte1) ^ nhanE(byte2) ^ nhanB(byte3) ^ nhanD(byte4);
    rs[2] = nhanD(byte1) ^ nhan9(byte2) ^ nhanE(byte3) ^ nhanB(byte4);
    rs[3] = nhanB(byte1) ^ nhanD(byte2) ^ nhan9(byte3) ^ nhanE(byte4);
    return (rs[0] << 24) | (rs[1] << 16) | (rs[2] << 8) | rs[3];
}

unsigned int *randomKey(int nk) {
    srand(time(NULL));
    set_nk(nk);
    unsigned int *key = new unsigned int[nk];
    for (int i = 0; i < nk; i++) {
        key[i] = rand() % 0xffffffff;
    }

    return key;
}

string randomKeyString(int nk) {
    // tuy chinh do phuc tap cua key: bits = 4, 8, 16, 32 || hexans = 1, 2, 4, 8
    // loops = nk * 32 / bits
    srand(time(NULL));
    set_nk(nk);
    string key = "";
    // 32 bit = 8 hexa, nk loop
    // 16 bit = 4 hexa, 2nk loop
    // 8 bit = 2 hexa, 4nk loop
    // 4 bit = 1 hexa, 8nk loop
    for (int i = 0; i < nk; i++) {
        // buffer[9 || 5 || 3 || 2]
        char buffer[9]; // 8 bit + 1 bit null
        sprintf(buffer, "%08x", rand() % int(pow(2, 8 * nk) - 1));
        key += buffer;
    }

    return key;
}


//-----------------------------key expansion----------------------------
//Rotword
unsigned int rotWord(unsigned int w) {
    return (w << 8) | (w >> 24);
}

//Subword
unsigned int subWord(unsigned int w) {
    unsigned int rs = 0x00;
    for (int i = 1; i <= 4; i++) {
        rs <<= 8;
        rs |= S[(w >> (32 - i * 8)) & 0xff];
    }

    return rs;
}

//Rcon
unsigned int Rcon[] = {
    0x00000000,
    0x01000000, 0x02000000, 0x04000000, 0x08000000, 0x10000000, 
    0x20000000, 0x40000000, 0x80000000, 0x1b000000, 0x36000000
};

//KeyExpansion
unsigned int *keyExpansion(unsigned int *key, int nk, int nr) {
    unsigned int *expansion = new unsigned int[nb * (nr + 1)];
    for (int i = 0; i < nk; i++) {
        expansion[i] = key[i];
    }

    for (int i = nk; i < nb * (nr + 1); i++) {
        unsigned int temp = expansion[i - 1];
        if (i % nk == 0) {
            temp = subWord(rotWord(temp)) ^ Rcon[i / nk];
        } else if (nk == 8 and (i % nk) == 4) {
            temp = subWord(temp);
        }
        expansion[i] = expansion[i - nk] ^ temp;
    }

    return expansion;
}


//--------------------------------encrypt--------------------------------
//SubBytes
unsigned int *subBytes(unsigned int *w) {
    unsigned int *rs = new unsigned int[4];
    for (int i = 0; i < 4; i++) {
        rs[i] = subWord(w[i]);
    }

    return rs;
}

//ShiftRows
unsigned int *shiftRows(unsigned int *w) {
    unsigned int *rs = new unsigned int[4];
    rs[0] = (w[0] & 0xff000000) | (w[1] & 0xff0000) | (w[2] & 0xff00) | (w[3] & 0xff);
    rs[1] = (w[1] & 0xff000000) | (w[2] & 0xff0000) | (w[3] & 0xff00) | (w[0] & 0xff);
    rs[2] = (w[2] & 0xff000000) | (w[3] & 0xff0000) | (w[0] & 0xff00) | (w[1] & 0xff);
    rs[3] = (w[3] & 0xff000000) | (w[0] & 0xff0000) | (w[1] & 0xff00) | (w[2] & 0xff);

    return rs;
}

//MixColumns
unsigned int *mixColumns(unsigned int *w) {
    unsigned int *rs = new unsigned int[4];
    for (int i = 0; i < 4; i++) {
        rs[i] = nhanCot_encrypt(w[i]);
    }

    return rs;
}

//AddRoundKey
unsigned int *addRoundKey(unsigned int *w, unsigned int *roundKey) {
    unsigned int *rs = new unsigned int[4];
    for (int i = 0; i < 4; i++) {
        rs[i] = w[i] ^ roundKey[i];
    }

    return rs;
}

//Encrypt
unsigned int *encrypt(unsigned int *w, unsigned int *roundKey, int nk, int nr) {
    unsigned int *rs = new unsigned int[4];

    rs = addRoundKey(w, roundKey);

    for (int i = 1; i < nr; i++) {
        rs = subBytes(rs);
        rs = shiftRows(rs);
        rs = mixColumns(rs);
        rs = addRoundKey(rs, roundKey + i * nb);
    }

    rs = subBytes(rs);
    rs = shiftRows(rs);
    rs = addRoundKey(rs, roundKey + nr * nb);
    
    return rs;
}


//--------------------------------decrypt--------------------------------
//InvShiftRows
unsigned int *invShiftRows(unsigned int *w) {
    unsigned int *rs = new unsigned int[4];
    rs[0] = (w[0] & 0xff000000) | (w[3] & 0xff0000) | (w[2] & 0xff00) | (w[1] & 0xff);
    rs[1] = (w[1] & 0xff000000) | (w[0] & 0xff0000) | (w[3] & 0xff00) | (w[2] & 0xff);
    rs[2] = (w[2] & 0xff000000) | (w[1] & 0xff0000) | (w[0] & 0xff00) | (w[3] & 0xff);
    rs[3] = (w[3] & 0xff000000) | (w[2] & 0xff0000) | (w[1] & 0xff00) | (w[0] & 0xff);

    return rs;
}

//InvSubBytes
unsigned int *invSubBytes(unsigned int *w) {
    unsigned int *rs = new unsigned int[4];
    for (int i = 0; i < 4; i++) {
        rs[i] = 0x00;
        for (int j = 1; j <= 4; j++) {
            rs[i] <<= 8;
            rs[i] |= IS[(w[i] >> (32 - j * 8)) & 0xff];
        }
    }

    return rs;
}

//InvMixColumns
unsigned int *invMixColumns(unsigned int *w) {
    unsigned int *rs = new unsigned int[4];
    for (int i = 0; i < 4; i++) {
        rs[i] = nhanCot_decrypt(w[i]);
    }

    return rs;
}

//Decrypt
unsigned int *decrypt(unsigned int *w, unsigned int *roundKey, int nk, int nr) {
    unsigned int *rs = new unsigned int[4];
    
    rs = addRoundKey(w, roundKey + nr * nb);
    
    for (int i = nr - 1; i > 0; i--) {
        rs = invShiftRows(rs);
        rs = invSubBytes(rs);
        rs = addRoundKey(rs, roundKey + i * nb);
        rs = invMixColumns(rs);
    }

    rs = invShiftRows(rs);
    rs = invSubBytes(rs);
    rs = addRoundKey(rs, roundKey);

    return rs;
}


//--------------------------------converter--------------------------------
// dung cho copy key
unsigned int *hexString_to_block(string s) {
    int keyLength = s.size();
    unsigned int *rs = new unsigned int[keyLength / 8];
    for (int i = 0; i < keyLength / 8; i++) {
        rs[i] = static_cast<unsigned int>(stoul(s.substr(i * 8, 8), nullptr, 16));  
    }

    return rs;
}

// chuyen doi tu vector sang chuoi hex
string vectorHex_to_hexString(vector<unsigned char> v) {
    string rs = "";
    for (unsigned char c : v) {
        char buffer[3];
        sprintf(buffer, "%02x", c);
        rs += buffer;
    }

    return rs;
}

vector<unsigned char> hexString_to_vectorHex(string s) {
    vector<unsigned char> rs;
    for (int i = 0; i < s.length() / 2; i++) {
        rs.push_back(static_cast<unsigned char>(stoul(s.substr(i * 2, 2), nullptr, 16)));
    }

    return rs;
}

// chuyen doi tu chuoi ky tu sang vector
vector<unsigned char> string_to_vectorHex(string s) {
    vector<unsigned char> rs;
    for (char c : s) {
        rs.push_back(static_cast<unsigned char>(c));
    }

    // add padding
    int padding = 16 - rs.size() % 16;
    if (padding < 16) {
        for (int i = 0; i < padding; i++) {
            rs.push_back(static_cast<unsigned char>(padding));
        }
    }

    return rs;
}

// chuyen doi tu vector sang chuoi ky tu
string vectorHex_to_string(vector<unsigned char> v) {
    // remove padding
    bool isPadding = true;
    unsigned char padding = v[v.size() - 1];
    for (int i = 2; i <= padding; i++) {
        if (v[v.size() - i] != padding) {
            isPadding = false;
            break;
        }
    }
    if (isPadding) {
        v.erase(v.end() - padding, v.end());
    }

    string rs = "";
    for (unsigned char c : v) {
        rs += c;
    }

    return rs;
}

// chuyen doi tu vector sang matrix cho de tinh toan
unsigned int *vectorHex_to_block(vector<unsigned char> v) {
    // phai luon di voi for loop vi khong the hardcode duoc so luong phan tu
    unsigned int *rs = new unsigned int[4];
    for (int i = 0; i < 4; i++) {
        rs[i] = 0;
        for (int j = 0; j < 4; j++) {
            rs[i] <<= 8;
            rs[i] |= v[i * 4 + j];
        }
    }

    return rs;
}

// chuyen doi tu matrix sang vector
vector<unsigned char> block_to_vectorHex(unsigned int *m, int block_size = 4) {
    vector<unsigned char> rs;
    for (int i = 0; i < block_size; i++) {
        for (int j = 0; j < 4; j++) {
            rs.push_back(static_cast<unsigned char>((m[i] >> (24 - j * 8)) & 0xff));
        }
    }

    return rs;
}

// chuyen doi tu matrix sang chuoi hex
string block_to_hexString(unsigned int *m) {
    string rs = "";
    for (int i = 0; i < 4; i++) {
        char buffer[9];
        sprintf(buffer, "%08x", m[i]);
        rs += buffer;
    }

    return rs;
}

void print_vectorHex(vector<unsigned char> v) {
    for (unsigned char c : v) {
        printf("%02x ", c);
    }
    cout << endl;
}


//--------------------------------mode--------------------------------
void encrypt_AES_ECB(string plaintext, unsigned int *roundKey) {
    vector<unsigned char> pv = string_to_vectorHex(plaintext);
    vector<unsigned char> cv;
    
    for (int i = 0; i < pv.size() / 16; i++) {
        unsigned int *w = vectorHex_to_block(vector<unsigned char>
            (pv.begin() + i * 16, pv.begin() + (i + 1) * 16));
        vector<unsigned char> ev = block_to_vectorHex(encrypt(w, roundKey, _nk, _nr));
        cv.insert(cv.end(), ev.begin(), ev.end());
    }

    // return cv;
    // return vectorHex_to_string(cv);
    // return vectorHex_to_hexString(cv);
}

void decrypt_AES_ECB(string ciphertext, unsigned int *roundKey) {
    vector<unsigned char> cv = string_to_vectorHex(ciphertext);
    vector<unsigned char> pv;

    for (int i = 0; i < cv.size() / 16; i++) {
        unsigned int *w = vectorHex_to_block(vector<unsigned char>
            (cv.begin() + i * 16, cv.begin() + (i + 1) * 16));
        vector<unsigned char> dv = block_to_vectorHex(decrypt(w, roundKey, _nk, _nr));
        pv.insert(pv.end(), dv.begin(), dv.end());
    }
    
    // return pv;
    // return vectorHex_to_string(pv);
    // return vectorHex_to_hexString(pv);
}

void encrypt_AES_CBC(string plaintext, unsigned int *roundKey, unsigned int *IV) {
    vector<unsigned char> pv = string_to_vectorHex(plaintext);
    vector<unsigned char> cv;
    unsigned int *previous_block = IV;

    for (int i = 0; i < pv.size() / 16; i++) {
        unsigned int *w = vectorHex_to_block(vector<unsigned char>
            (pv.begin() + i * 16, pv.begin() + (i + 1) * 16));
        unsigned int *xored_block = XOR(w, previous_block);
        // previous = encrypted
        previous_block = encrypt(xored_block, roundKey, _nk, _nr);
        vector<unsigned char> ev = block_to_vectorHex(previous_block);
        cv.insert(cv.end(), ev.begin(), ev.end());
    }

    // return cv;
    // return vectorHex_to_string(cv);
    // return vectorHex_to_hexString(cv);
}

void decrypt_AES_CBC(string ciphertext, unsigned int *roundKey, unsigned int *IV) {
    vector<unsigned char> cv = string_to_vectorHex(ciphertext);
    vector<unsigned char> pv;
    unsigned int *previous_block = IV;
    
    for (int i = 0; i < cv.size() / 16; i++) {
        unsigned int *w = vectorHex_to_block(vector<unsigned char>
            (cv.begin() + i * 16, cv.begin() + (i + 1) * 16));
        unsigned int *original_block = 
            XOR(decrypt(w, roundKey, _nk, _nr), previous_block);
        vector<unsigned char> dv = block_to_vectorHex(original_block);
        pv.insert(pv.end(), dv.begin(), dv.end());
        previous_block = w;
    }

    // return pv;
    // return vectorHex_to_string(pv);
    // return vectorHex_to_hexString(pv);
}

void encrypt_AES_CFB(string plaintext, unsigned int *roundKey, unsigned int *IV) {
    vector<unsigned char> pv = string_to_vectorHex(plaintext);
    vector<unsigned char> cv;
    unsigned int *previous_block = IV;
    
    for (int i = 0; i < pv.size() / 16; i++) {
        unsigned int *w = vectorHex_to_block(vector<unsigned char>
            (pv.begin() + i * 16, pv.begin() + (i + 1) * 16));
        unsigned int *cipher_block = 
            XOR(w, encrypt(previous_block, roundKey, _nk, _nr));
        vector<unsigned char> ev = block_to_vectorHex(cipher_block);
        cv.insert(cv.end(), ev.begin(), ev.end());
        previous_block = cipher_block;
    }
    
    // return cv;
    // return vectorHex_to_string(cv);
    // return vectorHex_to_hexString(cv);    
}

void decrypt_AES_CFB(string ciphertext, unsigned int *roundKey, unsigned int *IV) {
    vector<unsigned char> cv = string_to_vectorHex(ciphertext);
    vector<unsigned char> pv;
    unsigned int *previous_block = IV;
    
    for (int i = 0; i < pv.size(); i++) {
        unsigned int *w = vectorHex_to_block(vector<unsigned char>
            (cv.begin() + i * 16, cv.begin() + (i + 1) * 16));
        unsigned int *original_block = 
            XOR(w, encrypt(previous_block, roundKey, _nk, _nr));
        vector<unsigned char> dv = block_to_vectorHex(original_block);
        pv.insert(pv.end(), dv.begin(), dv.end());
        previous_block = w;
    }

    // return pv;
    // return vectorHex_to_string(pv);
    // return vectorHex_to_hexString(pv);
}

void encrypt_AES_OFB(string plaintext, unsigned int *roundKey, unsigned int *IV) {
    vector<unsigned char> pv = string_to_vectorHex(plaintext);
    vector<unsigned char> cv;
    unsigned int *previous_block = IV;

    for (int i = 0; i < pv.size(); i++) {
        unsigned int *w = vectorHex_to_block(vector<unsigned char>
            (pv.begin() + i * 16, pv.begin() + (i + 1) * 16));
        // keystream
        previous_block = encrypt(previous_block, roundKey, _nk, _nr);
        unsigned int *cipher_block = XOR(w, previous_block);
        vector<unsigned char> ev = block_to_vectorHex(cipher_block);
        cv.insert(cv.end(), ev.begin(), ev.end());
    }
    
    // return cv;
    // return vectorHex_to_string(cv);
    // return vectorHex_to_hexString(cv);    
}

void decrypt_AES_OFB(string ciphertext, unsigned int *roundKey, unsigned int *IV) {
    // return
    encrypt_AES_OFB(ciphertext, roundKey, IV);
}

// void encrypt_AES_CTR(string plaintext, unsigned int *roundKey, nonce);

// void decrypt_AES_CTR(string ciphertext, unsigned int *roundKey, nonce);

// void encrypt_AES_GCM(string plaintext, unsigned int *roundKey, nonce, additional_data);

// void decrypt_AES_GCM(string ciphertext, unsigned int *roundKey, additional_data, received_tag);





