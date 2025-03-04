#include<iostream>
#include<stdio.h>
#include<chrono>

using namespace std;
using namespace std::chrono; // for high_resolution_clock

const int nb = 4; // number of columns (32-bit words) comprising the state

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

//--------------------------------encode--------------------------------
unsigned int *subBytes(unsigned int *w);
unsigned int *shiftRows(unsigned int *w);
unsigned int *mixColumns(unsigned int *w);
unsigned int *addRoundKey(unsigned int *w, unsigned int *roundKey);
unsigned int *encode(unsigned int *w, unsigned int *roundKey, int nk, int nr);

//-----------------------------key expansion----------------------------
unsigned int rotWord(unsigned int w);
unsigned int subWord(unsigned int w);
unsigned int *keyExpansion(unsigned int *key, int nk, int nr);

//--------------------------------decode--------------------------------
unsigned int *invSubBytes(unsigned int *w);
unsigned int *invShiftRows(unsigned int *w);
unsigned int *invMixColumns(unsigned int *w);
unsigned int *decode(unsigned int *w, unsigned int *roundKey, int nk, int nr);

//--------------------------------component--------------------------------
unsigned int *cong(unsigned int *m1, unsigned int *m2);
unsigned int nhan2(unsigned int w);
unsigned int nhan3(unsigned int w);
unsigned int nhan9(unsigned int w);
unsigned int nhanB(unsigned int w);
unsigned int nhanD(unsigned int w);
unsigned int nhanE(unsigned int w);
unsigned int nhanCot_encode(unsigned int w);
unsigned int nhanCot_decode(unsigned int w);

void showMatrix(unsigned int *m);

int main() {
    int nk = 4, nr = 10;
    // input = 0x3243f6a8885a308d313198a2e0370734;
    unsigned int *w = new unsigned int[4];
    w[0] = 0x3243f6a8; w[1] = 0x885a308d; w[2] = 0x313198a2; w[3] = 0xe0370734;

    // key = 0x2b7e151628aed2a6abf7158809cf4f3c;
    unsigned int *key128 = new unsigned int[4];
    key128[0] = 0x2b7e1516; key128[1] = 0x28aed2a6; key128[2] = 0xabf71588; key128[3] = 0x09cf4f3c;

    // key = 0x8e73b0f7da0e6452c810f32b809079e562f8ead2522c6b7b;
    unsigned int *key192 = new unsigned int[6];
    key192[0] = 0x8e73b0f7; key192[1] = 0xda0e6452; key192[2] = 0xc810f32b;
    key192[3] = 0x809079e5; key192[4] = 0x62f8ead2; key192[5] = 0x522c6b7b;

    // key = 0x603deb1015ca71be2b73aef0857d77811f352c073b6108d72d9810a30914dff4;
    unsigned int *key256 = new unsigned int[8];
    key256[0] = 0x603deb10; key256[1] = 0x15ca71be; key256[2] = 0x2b73aef0; key256[3] = 0x857d7781;
    key256[4] = 0x1f352c07; key256[5] = 0x3b6108d7; key256[6] = 0x2d9810a3; key256[7] = 0x0914dff4;
    
    unsigned int *roundKey, *cipher, *decipher;

    cout << "128:\n";
    roundKey = keyExpansion(key128, 4, 10);
    cipher = encode(w, roundKey, 4, 10);
    decipher = decode(cipher, roundKey, 4, 10);
    
    // cout << "192:\n";
    // roundKey = keyExpansion(key192, 6, 12);
    // cipher = encode(w, roundKey, 6, 12);
    // decipher = decode(cipher, roundKey, 6, 12);
    
    // cout << "256:\n";
    // roundKey = keyExpansion(key256, 8, 14);
    // cipher = encode(w, roundKey, 8, 14);
    // decipher = decode(cipher, roundKey, 8, 14);

    cout << "Plaintext:\n";
    showMatrix(w);
    cout << "Ciphertext:\n";
    showMatrix(cipher);
    cout << "Deciphertext:\n";
    showMatrix(decipher);

    delete[] w, key128, key192, key256, roundKey, cipher, decipher;
    return 0;
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

    // for (int i = 0; i < nb * (nr + 1); i++) {
    //     printf("\t[%02d]: %08x\n", i, expansion[i]);
    //     if ((i + 1) % nb == 0) {
    //         cout << endl;
    //     }
    // }

    // for (int i = 0; i < nr + 1; i++) {
    //     showMatrix(expansion + i * nb);
    //     cout << endl;
    // }

    return expansion;
}

//--------------------------------encode--------------------------------
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
        rs[i] = nhanCot_encode(w[i]);
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

//Encode
unsigned int *encode(unsigned int *w, unsigned int *roundKey, int nk, int nr) {
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

//--------------------------------decode--------------------------------
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
        rs[i] = nhanCot_decode(w[i]);
    }

    return rs;
}

//Decode
unsigned int *decode(unsigned int *w, unsigned int *roundKey, int nk, int nr) {
    unsigned int *rs = new unsigned int[4];
    
    rs = addRoundKey(w, roundKey + nr * nb);
    
    for (int i = nr - 1; i > 0; i--) {
        rs = invShiftRows(rs);
        rs = invSubBytes(rs);
        rs = addRoundKey(rs, roundKey + (nb * i));
        rs = invMixColumns(rs);
    }

    rs = invShiftRows(rs);
    rs = invSubBytes(rs);
    rs = addRoundKey(rs, roundKey);

    return rs;
}

//Second way to decode


//--------------------------------component--------------------------------
void showMatrix(unsigned int *m) {
    unsigned int *rs = new unsigned int[4];

    // auto start1 = high_resolution_clock::now();
    // tranpose
    rs[0] = ((m[0] << 0) & 0xff000000) | ((m[1] >> 8) & 0xff0000) | ((m[2] >> 16) & 0xff00) | ((m[3] >> 24) & 0xff);
    rs[1] = ((m[0] << 8) & 0xff000000) | ((m[1] >> 0) & 0xff0000) | ((m[2] >> 8) & 0xff00) | ((m[3] >> 16) & 0xff);
    rs[2] = ((m[0] << 16) & 0xff000000) | ((m[1] << 8) & 0xff0000) | ((m[2] >> 0) & 0xff00) | ((m[3] >> 8) & 0xff);
    rs[3] = ((m[0] << 24) & 0xff000000) | ((m[1] << 16) & 0xff0000) | ((m[2] << 8) & 0xff00) | ((m[3] >> 0) & 0xff);
    // auto stop1 = high_resolution_clock::now();
    
    // auto start2 = high_resolution_clock::now();
    // for (int i = 0; i < 4; i++) {
    //     rs[i] = 0x00;
    //     for (int j = 0; j < 4; j++) {
    //         rs[i] <<= 8;
    //         rs[i] |= (m[j] >> (32 - (i + 1) * 8) & 0xff);
    //     }
    // }
    // auto stop2 = high_resolution_clock::now();
    // auto duration1 = duration_cast<microseconds>(stop1 - start1);
    // auto duration2 = duration_cast<microseconds>(stop2 - start2);
    // cout << duration1.count() << " mcs" << endl;
    // cout << duration2.count() << " mcs" << endl;

    for (int i = 0; i < 4; i++) {
        // printf("\t%08x\n", m[i]);
        printf("\t%08x\n", rs[i]);
    }
}

unsigned int *cong(unsigned int *m1, unsigned int *m2) {
    unsigned int *rs = new unsigned int[4];
    rs[0] = m1[0] ^ m2[0];
    rs[1] = m1[1] ^ m2[1];
    rs[2] = m1[2] ^ m2[2];
    rs[3] = m1[3] ^ m2[3];
 
    return rs;
}

unsigned int nhan2(unsigned int w) {
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

unsigned int nhanCot_encode(unsigned int w) {
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

unsigned int nhanCot_decode(unsigned int w) {
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


