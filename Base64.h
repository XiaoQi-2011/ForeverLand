#ifndef BASE64_H
#define BASE64_H

#include <iostream>
#include <string>
#include <functional>
#include <windows.h>
#include <cstdint>

using namespace std;

size_t Base64Key;
// ???????????????? Base64 ?????
inline string generate_base64_table(const size_t seed) {
    // ??? Base64 ?????
    string table =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "0123456789+/";

    random_shuffle(table.begin(), table.end(), [&](int i) {
        return (seed + i) % table.size();
    });

    return table;
}

// ?§Ø?????? Base64 ???
inline bool is_base64(char c, const string& table) {
    return table.find(c) != string::npos;
}

// ===================== ????? Base64 ??????????? =====================
inline string encode(const string& data) {
    const string table = generate_base64_table(Base64Key);
    string ret;
    int i = 0;
    uint8_t buf3[3];
    uint8_t buf4[4];
    size_t len = data.size();
    const uint8_t* bytes = reinterpret_cast<const uint8_t*>(data.c_str());

    for (size_t k = 0; k < len; ++k) {
        buf3[i++] = bytes[k];
        if (i == 3) {
            buf4[0] = (buf3[0] & 0xfc) >> 2;
            buf4[1] = ((buf3[0] & 0x03) << 4) + ((buf3[1] & 0xf0) >> 4);
            buf4[2] = ((buf3[1] & 0x0f) << 2) + ((buf3[2] & 0xc0) >> 6);
            buf4[3] = buf3[2] & 0x3f;

            for (i = 0; i < 4; ++i) ret += table[buf4[i]];
            i = 0;
        }
    }

    if (i > 0) {
        for (int j = i; j < 3; ++j) buf3[j] = 0;
        buf4[0] = (buf3[0] & 0xfc) >> 2;
        buf4[1] = ((buf3[0] & 0x03) << 4) + ((buf3[1] & 0xf0) >> 4);
        buf4[2] = ((buf3[1] & 0x0f) << 2) + ((buf3[2] & 0xc0) >> 6);
        buf4[3] = buf3[2] & 0x3f;

        for (int j = 0; j < i + 1; ++j) ret += table[buf4[j]];
        while (i++ < 3) ret += '=';
    }
    return ret;
}

// ===================== ????? Base64 ??????????? =====================
inline string decode(const string& encoded) {
    const string table = generate_base64_table(Base64Key);
    string ret;
    int i = 0;
    uint8_t buf4[4], buf3[3];
    size_t len = encoded.size();

    for (size_t k = 0; k < len && encoded[k] != '='; ++k) {
        if (!is_base64(encoded[k], table)) continue;
        buf4[i++] = encoded[k];
        if (i == 4) {
            for (i = 0; i < 4; ++i) buf4[i] = table.find(buf4[i]);
            buf3[0] = (buf4[0] << 2) | ((buf4[1] & 0x30) >> 4);
            buf3[1] = ((buf4[1] & 0x0f) << 4) | ((buf4[2] & 0x3c) >> 2);
            buf3[2] = ((buf4[2] & 0x03) << 6) | buf4[3];
            for (i = 0; i < 3; ++i) ret += buf3[i];
            i = 0;
        }
    }

    if (i > 0) {
        for (int j = i; j < 4; ++j) buf4[j] = 0;
        for (int j = 0; j < i; ++j) buf4[j] = table.find(buf4[j]);
        buf3[0] = (buf4[0] << 2) | ((buf4[1] & 0x30) >> 4);
        buf3[1] = ((buf4[1] & 0x0f) << 4) | ((buf4[2] & 0x3c) >> 2);
        if (i > 2) buf3[2] = ((buf4[2] & 0x03) << 6) | buf4[3];
        for (int j = 0; j < i - 1; ++j) ret += buf3[j];
    }
    return ret;
}

const char verificationTable[] {
        'F','O','R','1','7','>','*','=','#','%'
};
string getVerificationCode(const string& str) {
    unsigned long long add = 0;
    string code;
    for (int i = 0; i < str.size(); i++) {
        add += (int) str[i] * (i + 1);
    }
    string addStr = to_string(add);
    for (auto & c : addStr) {
        code += verificationTable[c - '0'];
    }
    return code;
}

const char timeTable[] {
        '#',']','h','=','[','O','*','_','$','S'
};
long long decodeTime(const string& str) {
    long long time = 0;
    for (char i : str) {
        for (int j = 0; j <= 9; j++) {
            if (i == timeTable[j]) {
                time = time * 10 + j;
                break;
            }
        }
    }
    return time;
}
string encodeTime(long long time) {
    string str, str2 = to_string(time);
    for (char i : str2) {
        str += timeTable[i - '0'];
    }
    return str;
}

#endif //BASE64_H
