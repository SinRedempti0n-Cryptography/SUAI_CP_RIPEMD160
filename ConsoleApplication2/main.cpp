#include "RIPEMD-160.h"
#include <iostream>
#include <fstream>

typedef unsigned long long uint64;
typedef unsigned long uint32;
typedef unsigned int uint16;
typedef unsigned char uint8;

typedef std::vector<uint64> v64;
typedef std::vector<std::vector<uint64>> vv64;

int main(int argc, char *argv[]){
    char message[] = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised in the 1960s with the release of Letraset sheets containing Lorem Ipsum passages, and more recently with desktop publishing software like Aldus PageMaker including versions of Lorem Ipsum.";
    std::cout << "Message: " << (char *)message << std::endl;
    std::string hash = RIPEMD160((char *)message).getHash();
    std::cout << "Hashcode: " << hash << std::endl;

    std::ofstream file1("data1.txt", std::ios_base::trunc);
    std::ofstream file2("data2.txt", std::ios_base::trunc);

    std::string table = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ,.-";
    std::cout << "8bit" << std::endl;
    uint8 x = uint8(hash[0]);
    vv64 v_Y;
    v64 Y;
    int N = 0;
    srand(time(NULL));
    while (1) {
        N++;
        std::string message_y = "";
        for (int i = 0; i < 8; i++) {
            message_y += table[rand() % table.length()];
        }
        //cout << message_y << endl;
        std::string hash_y = RIPEMD160(&message_y[0]).getHash();
        uint8 y = uint8(hash_y[0]);
        Y.push_back(y);

        if (x == y) {
            break;
        }
    }
    v_Y.push_back(Y);
    std::cout << "Complexity of the second prototype: " << N << std::endl;

    //нахождение коллизии
    int N_c = 0;
    bool count = false;
    for (int i = 0; i < Y.size(); i++) {
        for (int j = 0; j < Y.size(); j++) {

            N_c++;
            if (Y[i] == Y[j] && i != j) {
                count = true;
                break;
            }
        }
        if (count == true) {
            break;
        }
    }
    std::cout << "Complexity of the collision: " << N_c << std::endl;

    // нахождение среднего числа сложности второго прообраза
    int sum = N;

    for (int j = 0; j < 999; j++) {
        v64 tmpY;
        while (1) {
            sum++;
            std::string message_y = "";
            for (int i = 0; i < 8; i++) {
                message_y += table[rand() % table.length()];
            }
            //cout << message_y << endl;
            std::string hash_y = RIPEMD160(&message_y[0]).getHash();
            uint8 y = uint8(hash_y[0]);
            tmpY.push_back(y);

            if (x == y) {
                break;
            }
        }
        v_Y.push_back(tmpY);
    }
    int medium_N = sum / 1000;
    std::cout << "Medium complexity of the second prototype: " << medium_N << std::endl;
    file1 << medium_N << "\n";
    // нахождение среднего числа сложности коллизии
    int sum2 = N_c;

    for (int k = 0; k < v_Y.size(); k++) {

        bool count = false;
        for (int i = 0; i < v_Y[k].size(); i++) {
            for (int j = 0; j < v_Y[k].size(); j++) {

                sum2++;
                if (v_Y[k][i] == v_Y[k][j] && i != j) {
                    count = true;
                    break;
                }
            }
            if (count == true) {
                break;
            }
        }
    }

    int medium_N_c = sum2 / v_Y.size();
    std::cout << "Medium complexity of the collision: " << medium_N_c << std::endl;
    file2 << medium_N_c << "\n";

    /*12bit*/
    std::cout << "12bit" << std::endl;
    uint16 x2 = uint16(hash[0]) << 4 | uint16(hash[1]) >> 4;
    vv64 v_Y2;

    // нахождение среднего числа сложности второго прообраза
    int sum12 = 0;

    for (int j = 0; j < 1000; j++) {
        v64 tmpY;
        while (1) {
            sum12++;
            std::string message_y = "";
            for (int i = 0; i < 8; i++) {
                message_y += table[rand() % table.length()];
            }
            //cout << message_y << endl;
            std::string hash_y = RIPEMD160(&message_y[0]).getHash();
            uint16 y = uint16(hash_y[0]) << 4 | uint16(hash_y[1]) >> 4;
            tmpY.push_back(y);

            if (x2 == y) {
                break;
            }
        }
        v_Y2.push_back(tmpY);
    }
    int medium_N2 = sum12 / 1000;
    file1 << medium_N2 << "\n";

    // нахождение среднего числа сложности коллизии
    int sum22 = 0;

    for (int k = 0; k < v_Y2.size(); k++) {

        bool count = false;
        for (int i = 0; i < v_Y2[k].size(); i++) {
            for (int j = 0; j < v_Y2[k].size(); j++) {

                sum22++;
                if (v_Y2[k][i] == v_Y2[k][j] && i != j) {
                    count = true;
                    break;
                }
            }
            if (count == true) {
                break;
            }
        }
    }

    int medium_N_c2 = sum22 / v_Y2.size();
    file2 << medium_N_c2 << "\n";

    /*16bit*/
    std::cout << "16bit" << std::endl;
    uint16 x3 = uint16(hash[0]) << 8 | uint16(hash[1]);
    vv64 v_Y3;

    // нахождение среднего числа сложности второго прообраза
    int sum13 = 0;

    for (int j = 0; j < 1000; j++) {
        v64 tmpY;
        while (1) {
            sum13++;
            std::string message_y = "";
            for (int i = 0; i < 8; i++) {
                message_y += table[rand() % table.length()];
            }
            //cout << message_y << endl;
            std::string hash_y = RIPEMD160(&message_y[0]).getHash();
            uint16 y = uint16(hash_y[0]) << 8 | uint16(hash_y[1]);
            tmpY.push_back(y);

            if (x3 == y) {
                break;
            }
        }
        v_Y3.push_back(tmpY);
    }
    int medium_N3 = sum13 / 1000;
    file1 << medium_N3 << "\n";

    // нахождение среднего числа сложности коллизии
    int sum23 = 0;

    for (int k = 0; k < v_Y3.size(); k++) {

        bool count = false;
        for (int i = 0; i < v_Y3[k].size(); i++) {
            for (int j = 0; j < v_Y3[k].size(); j++) {

                sum23++;
                if (v_Y3[k][i] == v_Y3[k][j] && i != j) {
                    count = true;
                    break;
                }
            }
            if (count == true) {
                break;
            }
        }
    }

    int medium_N_c3 = sum23 / v_Y3.size();
    file2 << medium_N_c3 << "\n";


    /*20bit*/
    std::cout << "20bit" << std::endl;
    uint32 x4 = uint32(hash[0]) << 12 | uint32(hash[1]) << 4 | uint32(hash[2]) >> 4;
    vv64 v_Y4;

    // нахождение среднего числа сложности второго прообраза
    int sum14 = 0;

    for (int j = 0; j < 1000; j++) {
        v64 tmpY;
        while (1) {
            sum14++;
            std::string message_y = "";
            for (int i = 0; i < 8; i++) {
                message_y += table[rand() % table.length()];
            }
            //cout << message_y << endl;
            std::string hash_y = RIPEMD160(&message_y[0]).getHash();
            uint32 y = uint32(hash_y[0]) << 12 | uint32(hash_y[1]) << 4 | uint32(hash_y[2]) >> 4;
            tmpY.push_back(y);

            if (x4 == y) {
                break;
            }
        }
        v_Y4.push_back(tmpY);
    }
    int medium_N4 = sum14 / 1000;
    file1 << medium_N4 << "\n";

    // нахождение среднего числа сложности коллизии
    int sum24 = 0;

    for (int k = 0; k < v_Y4.size(); k++) {

        bool count = false;
        for (int i = 0; i < v_Y4[k].size(); i++) {
            for (int j = 0; j < v_Y4[k].size(); j++) {

                sum24++;
                if (v_Y4[k][i] == v_Y4[k][j] && i != j) {
                    count = true;
                    break;
                }
            }
            if (count == true) {
                break;
            }
        }
    }

    int medium_N_c4 = sum24 / v_Y4.size();
    file2 << medium_N_c4 << "\n";


    /*24bit*/
    std::cout << "24bit" << std::endl;
    uint32 x5 = uint32(hash[0]) << 12 | uint32(hash[1]) << 8 | uint32(hash[2]);
    vv64 v_Y5;

    // нахождение среднего числа сложности второго прообраза
    int sum15 = 0;

    for (int j = 0; j < 1000; j++) {
        v64 tmpY;
        while (1) {
            sum15++;
            std::string message_y = "";
            for (int i = 0; i < 8; i++) {
                message_y += table[rand() % table.length()];
            }
            //cout << message_y << endl;
            std::string hash_y = RIPEMD160(&message_y[0]).getHash();
            uint32 y = uint32(hash_y[0]) << 12 | uint32(hash_y[1]) << 8 | uint32(hash_y[2]);
            tmpY.push_back(y);

            if (x5 == y) {
                break;
            }
        }
        v_Y5.push_back(tmpY);
    }
    int medium_N5 = sum15 / 1000;
    file1 << medium_N5 << "\n";

    // нахождение среднего числа сложности коллизии
    int sum25 = 0;

    for (int k = 0; k < v_Y5.size(); k++) {

        bool count = false;
        for (int i = 0; i < v_Y5[k].size(); i++) {
            for (int j = 0; j < v_Y5[k].size(); j++) {

                sum25++;
                if (v_Y5[k][i] == v_Y5[k][j] && i != j) {
                    count = true;
                    break;
                }
            }
            if (count == true) {
                break;
            }
        }
    }

    int medium_N_c5 = sum25 / v_Y5.size();
    file2 << medium_N_c5 << "\n";

    file1.close();
    file2.close();
    return 0;
}