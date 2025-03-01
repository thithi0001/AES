# include <iostream>
# include <vector>
# include <sstream>
#include <algorithm> 
#include <cstdint> 
using namespace std;

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
const uint8_t Key_128[16] = {0x2b, 0x7e, 0x15, 0x16,
                             0x28, 0xae, 0xd2, 0xa6,
                             0xab, 0xf7, 0x15, 0x88,
                             0x09, 0xcf, 0x4f, 0x3c};

const uint8_t Key_192[24] = {0x00 ,0x01 ,0x02 ,0x03
                            ,0x04 ,0x05 ,0x06 ,0x07
                            ,0x08 ,0x09 ,0x0a ,0x0b
                            ,0x0c ,0x0d ,0x0e ,0x0f
                            ,0x10 ,0x11 ,0x12 ,0x13
                            ,0x14 ,0x15 ,0x16 ,0x17
                        };
const uint8_t Key_256[32] = {0x60 ,0x3d ,0xeb ,0x10
                            ,0x15 ,0xca ,0x71 ,0xbe
                            ,0x2b ,0x73 ,0xae ,0xf0
                            ,0x85 ,0x7d ,0x77 ,0x81
                            ,0x1f ,0x35 ,0x2c ,0x07
                            ,0x3b ,0x61 ,0x08 ,0xd7
                            ,0x2d ,0x98 ,0x10 ,0xa3
                            ,0x09 ,0x14 ,0xdf ,0xf4 
                        };
const uint8_t Rcon[11] = {0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0X20, 0X40, 0X80, 0X1b, 0x36};   

vector<vector<uint8_t>> stringToBlockHex(string& text, int blockSize);
vector<vector<uint8_t>> convertorBlockToMatrix(vector<uint8_t> &block);
vector<uint8_t> convertorMatrixToBlock( vector<vector<uint8_t>> &matrix);
string convertorBlocksHexToString(vector<vector<uint8_t>>& blocks, int blockSize);

//-----------------------------key expansion----------------------------
void rotWord(vector<uint8_t>, int);
vector<vector<uint8_t>> keyExpansion( const uint8_t key[], int , int); 
void addRoundKey(vector<vector<uint8_t>> &matrix, vector<uint8_t> roundKeys);

//--------------------------------encode--------------------------------
void subWord(uint8_t &input);
void subByte(vector<vector<uint8_t>> &input);
void shiftRows(vector<vector<uint8_t>> &input);
void mixColumns(vector<vector<uint8_t>> &matrix);
void AES(vector<vector<uint8_t>> &matrix, const vector<vector<uint8_t>> roundKeys, int round);

//--------------------------------decode--------------------------------
void invSubWord(uint8_t &input);
void invSubByte(vector<vector<uint8_t>> &input);
void invShiftRows(vector<vector<uint8_t>> &input);
void invMixColumns(vector<vector<uint8_t>> &matrix);
void invAES(vector<vector<uint8_t>> &matrix, const vector<vector<uint8_t>> roundKeys, int round);

uint8_t nhan2(uint8_t x);
uint8_t nhan3(uint8_t x);
uint8_t nhan9(uint8_t x);
uint8_t nhanB(uint8_t x);
uint8_t nhanD(uint8_t x);
uint8_t nhanE(uint8_t x);

void printMatrix(vector<vector<uint8_t>> &matrix);
void printRoundKeys(const vector<vector<uint8_t>> &roundKeys);

int main() {
    string text = "Hello, AES Block Cipher!";
    int blockSize = 16;
    vector<uint8_t> input = {0x00 ,0x11 ,0x22 ,0x33
                            ,0x44 ,0x55 ,0x66 ,0x77 
                            ,0x88 ,0x99 ,0xaa ,0xbb
                            ,0xcc ,0xdd ,0xee ,0xff};
    vector<vector<uint8_t>> matrix = convertorBlockToMatrix(input);
    vector<vector<uint8_t>> roundKey_24 = keyExpansion(Key_192, 24, 13);
    vector<vector<uint8_t>> roundKey_16 = keyExpansion(Key_128, 16, 11);
    vector<vector<uint8_t>> roundKey_32 = keyExpansion(Key_128, 32, 15);

    
    printMatrix(matrix);
    cout<< "AES_128"<< endl;
    AES(matrix, roundKey_16, 10);
    cout << "after cipher"<<endl;
    printMatrix(matrix);
    invAES(matrix, roundKey_16, 10);
    cout << "after decipher"<<endl;
    printMatrix(matrix);
    cout<<endl;

    
    cout<< "AES_192"<< endl;
    AES(matrix, roundKey_24, 12);
    cout << "after cipher"<<endl;
    printMatrix(matrix);
    invAES(matrix, roundKey_24, 12);
    cout << "after decipher"<<endl;
    printMatrix(matrix);
    cout<<endl;


    cout<< "AES_256"<< endl;
    AES(matrix, roundKey_32, 14);
    cout << "after cipher"<<endl;
    printMatrix(matrix);
    invAES(matrix, roundKey_32, 14);
    cout << "after decipher"<<endl;
    printMatrix(matrix);
    cout<<endl;
    
    return 0;
}



vector<vector<uint8_t>> stringToBlockHex(string& text, int blockSize) {
    vector<vector<uint8_t>> blocks;
    for (size_t i = 0; i < text.length(); i += blockSize) 
    {   
        string x = text.substr(i, blockSize);
        vector<uint8_t> block(x.begin() , x.end());
        if(block.size() < blockSize){ //add padding into block
            int x = blockSize - block.size();
            while (block.size() < blockSize)
            {   
                block.push_back(x);
            }
        }
        blocks.push_back(block); // add block into blocks
    }
    return blocks;
}

vector<vector<uint8_t>> convertorBlockToMatrix(vector<uint8_t> &block) {
    vector<vector<uint8_t>> matrix(4, vector<uint8_t>(4, 0));
    for (int i = 0; i < 16; i++) {
        matrix[i % 4][i / 4] = block[i];  // Chuyển đổi đúng thứ tự AES
    }
    return matrix;
}

vector<uint8_t> convertorMatrixToBlock( vector<vector<uint8_t>> &matrix){
    vector<uint8_t> result;
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j ++){
            result.push_back(matrix[i][j]);
        }
    }
    return result;
}

string convertorBlocksHexToString( vector<vector<uint8_t>>& blocks, int blockSize) {
    vector<uint8_t> data;
    for (const auto &block : blocks) {
        data.insert(data.end(), block.begin(), block.end());
    }
    // Remove PKCS#7 padding from last block
    if (!data.empty()) {
        uint8_t padValue = data.back();
        // Check for valid padding value (between 1 and blockSize)
        if (padValue > 0 && padValue <= blockSize) {
            bool validPadding = true;
            for (size_t i = data.size() - padValue; i < data.size(); i++) {
                if (data[i] != padValue) {
                    validPadding = false;
                    break;
                }
            }
            if (validPadding) {
                data.resize(data.size() - padValue);
            }
        }
    }
    return string(data.begin(), data.end());
}

void rotWord(vector<uint8_t> &col){
    rotate(col.begin(), col.begin() + 1, col.end());
}

void subWord(uint8_t &input){
    int row = (input >>4)& 0x0f;
    int col = input & 0x0f;
    int index = row * 16 + col;
    input = S[index];
}

void subByte(vector<vector<uint8_t>> &input){
    for (int i = 0; i<4 ; i++){
        for (int j = 0; j<4 ; j++){
            subWord(input[i][j]);
        }
    }   
}

void shiftRows(vector<vector<uint8_t>> &input){
    for(int i = 1; i<4; i++){
        for(int j = 0; j<i; j++){
            rotWord(input[i]);
        }
    }
}

vector<vector<uint8_t>> keyExpansion_128 (const uint8_t Key_128[16]){
    vector<vector<uint8_t>> roundKeys(11, vector<uint8_t>(16));
    for (int i = 0; i < 16; i++)
            roundKeys[0][i] = Key_128[i]; //save cipherKey into roundkeys
    //keyExpansion loop        
    for(int round = 1; round < 11 ;round ++){
        vector<uint8_t> lastCol;
        //get 4 last component in roundkey(last col)
        for (int i = 12; i < 16; i++ ) lastCol.push_back(roundKeys[round -1][i]);
        //subwWord lastCol
        for(int i = 0; i < 4; i++)subWord(lastCol[i]);
        // rotate lastCol
        rotWord(lastCol);
        
        vector<uint8_t> roundKey(16);

        for (int i = 0; i < 4; i++)
            roundKeys[round][i] = roundKeys[round - 1][i] ^ lastCol[i] ^ ((i == 0) ? Rcon[round] : 0x00);

        for (int i = 4; i < 16; i++)
            roundKeys[round][i] = roundKeys[round - 1][i] ^ roundKeys[round][i - 4];
    }
    return roundKeys;
}

vector<vector<uint8_t>> keyExpansion_192 ( const uint8_t key_192[24]){
    vector<vector<uint8_t>> roundKeys(13, vector<uint8_t>(16));

    for(int i = 0; i < 24; i++){
        roundKeys[i / 16][i % 16] = key_192[i]; 
    }
    int byteIndex = 24; // Number of bytes existes in roundKeys
    int RconIndex = 1;
    vector<uint8_t> colSubByte(4);//contains 4 byte of col need to subByte

    while (byteIndex < 208){
        if(byteIndex % 24 == 0){
            for (int i = 0; i < 4; i++){
                colSubByte[i] = roundKeys[(byteIndex - 4) /16][(byteIndex -  4 + i )%16];
            }
            rotWord(colSubByte);
            for (int i = 0; i < 4; i++) {
                subWord(colSubByte[i]); // SubWord
            }

            for (int i = 0; i < 4; i++){
                roundKeys[byteIndex/16][byteIndex%16] = roundKeys[(byteIndex - 24)/16][(byteIndex - 24)%16] ^ colSubByte[i] ^ ((i == 0) ? Rcon[RconIndex]: 0x00);
                byteIndex++;
            }

            RconIndex++;
        }
        else{
            roundKeys[byteIndex/16][byteIndex%16] =  roundKeys[(byteIndex - 4)/16][(byteIndex - 4)%16] ^ roundKeys[(byteIndex - 24)/16][(byteIndex - 24)%16];
            byteIndex++;
        }
    }
    return roundKeys; 
}

vector<vector<uint8_t>> keyExpansion ( const uint8_t Key[], int keySize, int nKey){
    vector<vector<uint8_t>> roundKeys(nKey, vector<uint8_t>(16));

    for(int i = 0; i < keySize; i++){
        roundKeys[i / 16][i % 16] = Key[i]; 
    }
    int byteIndex = 24; // Number of bytes existes in roundKeys
    int RconIndex = 1;
    vector<uint8_t> colSubByte(4);//contains 4 byte of col need to subByte

    while (byteIndex < 16*nKey){
        if(byteIndex % keySize == 0){
            for (int i = 0; i < 4; i++){
                colSubByte[i] = roundKeys[(byteIndex - 4) /16][(byteIndex -  4 + i )%16];
            }
            rotWord(colSubByte);
            for (int i = 0; i < 4; i++) {
                subWord(colSubByte[i]); // SubWord
            }

            for (int i = 0; i < 4; i++){
                roundKeys[byteIndex/16][byteIndex%16] = roundKeys[(byteIndex - 24)/16][(byteIndex - 24)%16] ^ colSubByte[i] ^ ((i == 0) ? Rcon[RconIndex]: 0x00);
                byteIndex++;
            }

            RconIndex++;
        }
        else{
            roundKeys[byteIndex/16][byteIndex%16] =  roundKeys[(byteIndex - 4)/16][(byteIndex - 4)%16] ^ roundKeys[(byteIndex - 24)/16][(byteIndex - 24)%16];
            byteIndex++;
        }
    }
    return roundKeys; 
}

void addRoundKey(vector<vector<uint8_t>> &matrix ,const vector<uint8_t> roundKey){
    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            matrix[col][row] ^= roundKey[row*4 + col];
        }
    }
}

void mixColumns(vector<vector<uint8_t>> &matrix) {
    for (int col = 0; col < 4; col++) {
        uint8_t s0 = matrix[0][col], s1 = matrix[1][col], s2 = matrix[2][col], s3 = matrix[3][col];

        matrix[0][col] = nhan2(s0) ^ nhan3(s1) ^ s2 ^ s3;
        matrix[1][col] = s0 ^ nhan2(s1) ^ nhan3(s2) ^ s3;
        matrix[2][col] = s0 ^ s1 ^ nhan2(s2) ^ nhan3(s3);
        matrix[3][col] = nhan3(s0) ^ s1 ^ s2 ^ nhan2(s3);
    }
}

void AES(vector<vector<uint8_t>> &matrix, const vector<vector<uint8_t>> roundKeys, int round){
    addRoundKey(matrix, roundKeys[0]);
    for(int r = 1; r < round; r++){
        subByte(matrix);
        shiftRows(matrix);
        mixColumns(matrix);
        addRoundKey(matrix, roundKeys[r]);
    }
    subByte(matrix);
    shiftRows(matrix);
    addRoundKey(matrix, roundKeys[round]); 
}
void printMatrix(vector<vector<uint8_t>> &matrix) {
    for (const auto &row : matrix) {
        for (uint8_t val : row)
            printf("%02X ", val);
        cout << endl;
    }
}


void printRoundKeys(const vector<vector<uint8_t>> &roundKeys) {
    cout << "Round Keys:\n";
    for (size_t round = 0; round < roundKeys.size(); round++) {
        cout << "Round " << round << ": ";
        for (size_t i = 0; i < roundKeys[round].size(); i++) {
            printf("%02X ", roundKeys[round][i]); // In dạng hex
            if ((i + 1) % 4 == 0) cout << "  "; // Ngăn cách từng cột
        }
        cout << endl;
    }
}

void printRoundKey(vector<uint8_t> roundkey){
    cout << "roundKey " << endl;
    for (size_t i = 0; i < 16; i++) {
        printf("%02X ", roundkey[i]); // In dạng hex
        if ((i + 1) % 4 == 0) cout << "  "; // Ngăn cách từng cột
    }
    cout << endl;
}
void invSubByte(vector<vector<uint8_t>> &input){
    for (int i = 0; i<4 ; i++){
        for (int j = 0; j<4 ; j++){
            input[i][j] = IS[input[i][j]];
        }
    }  
};
void invShiftRows(vector<vector<uint8_t>> &input){
    for(int i = 1; i<4; i++){
        rotate(input[i].begin(), input[i].begin() + (4 - i), input[i].end());
    }
};

void invMixColumns(vector<vector<uint8_t>> &matrix){
    for (int col = 0; col < 4; col++) {
        uint8_t s0 = matrix[0][col], s1 = matrix[1][col], s2 = matrix[2][col], s3 = matrix[3][col];

        matrix[0][col] = nhanE(s0) ^ nhanB(s1) ^ nhanD(s2) ^ nhan9(s3); 
        matrix[1][col] = nhan9(s0) ^ nhanE(s1) ^ nhanB(s2) ^ nhanD(s3);
        matrix[2][col] = nhanD(s0) ^ nhan9(s1) ^ nhanE(s2) ^ nhanB(s3);
        matrix[3][col] = nhanB(s0) ^ nhanD(s1) ^ nhan9(s2) ^ nhanE(s3);
    }
};

void invAES(vector<vector<uint8_t>> &matrix, const vector<vector<uint8_t>> roundKeys, int round){
    addRoundKey(matrix, roundKeys[round]);
    for(int r = round - 1; r >= 1; r--){
        invShiftRows(matrix);
        invSubByte(matrix);
        addRoundKey(matrix, roundKeys[r]);
        invMixColumns(matrix);
        
    }
    invShiftRows(matrix);
    invSubByte(matrix);
    addRoundKey(matrix, roundKeys[0]); 
}

uint8_t nhan2(uint8_t x){
    return (x << 1) ^ ((x & 0x80) ? 0x1B : 0x00);
}
uint8_t nhan3(uint8_t x){
    return x ^ nhan2(x);
}
uint8_t nhan9(uint8_t x){
    return (nhan2(nhan2(nhan2(x))) ^ x);
};
uint8_t nhanB(uint8_t x){
    return (nhan2(nhan2(nhan2(x))) ^ nhan2(x) ^ x);
};
uint8_t nhanD(uint8_t x){
    return (nhan2(nhan2(nhan2(x))) ^ nhan2(nhan2(x))^ x);
};
uint8_t nhanE(uint8_t x){
    return (nhan2(nhan2(nhan2(x))) ^ nhan2(nhan2(x)) ^ nhan2(x));
};

