//
// Created by liels on 03/08/2024.
//
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include <stdexcept>

#define DYNAMIC_ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            throw std::runtime_error(message); \
        } \
    } while (false)


using namespace std;

void encrypt(string str, char *encrypted_str)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    int length = strlen(str.c_str());
    char buffer[((signed int)(((unsigned int)(6*length+3))/(unsigned int)4))*4-4];
    int var_C = 0, var_1C = 0;
    for(int i=0; i < length; i++)
    {
        int char_ASCII_value = str[i];
        int var_16 = (char_ASCII_value >> 4) & 0x0f;
        int var_17 = char_ASCII_value & 0x0f;
        if(var_16 >= 2 && var_16 <= 9)
        {
            buffer[var_C++] = var_16 + 48;
        }
        if((unsigned int)var_16 > 12 )
        {
            int random = rand();
            int64_t extendedrandom = static_cast<int64_t>(random);
            int32_t Divisor = static_cast<int32_t>(18-var_16);
            var_1C = var_16 - 9 + (extendedrandom % Divisor);
            buffer[var_C++] = var_1C + 48;
            buffer[var_C++] = 43;
            buffer[var_C++] = var_16-var_1C+48;
        }
        if(var_16 ==0)
        {
            int random = rand();
            int random2 = random >> 31;
            random2 = (unsigned int)(random2) >> 29;
            random += random2;
            random = random & 7 - random2;
            random2 = random + 2;
            var_1C = random2;
            buffer[var_C++] = var_1C+48;
            buffer[var_C++] = 45;
            buffer[var_C++] = var_1C+48;
        }
        if(var_16 ==1)
        {
            buffer[var_C++] = 65;
        }
        if(var_16 ==10)
        {
            buffer[var_C++] = 74;
        }
        if(var_16 ==11)
        {
            buffer[var_C++] = 81;
        }
        if(var_16 ==12)
        {
            buffer[var_C++] = 75;
        }



        if(var_17 >= 2 && var_17 <= 9)
        {
            buffer[var_C++] = var_17 + 48;
        }
        if((unsigned int)var_17 > 12 )
        {
            int random = rand();
            int64_t extendedrandom = static_cast<int64_t>(random);
            int32_t Divisor = static_cast<int32_t>(18-var_17);
            var_1C = var_17 - 9 + (extendedrandom % Divisor);
            buffer[var_C++] = var_1C + 48;
            buffer[var_C++] = 43;
            buffer[var_C++] = var_17-var_1C+48;
        }
        if(var_17 ==0)
        {
            int random = rand();
            int random2 = random >> 31;
            random2 = (unsigned int)(random2) >> 29;
            random += random2;
            random = random & 7 - random2;
            random2 = random + 2;
            var_1C = random2;
            buffer[var_C++] = var_1C+48;
            buffer[var_C++] = 45;
            buffer[var_C++] = var_1C+48;
        }
        if(var_17 ==1)
        {
            buffer[var_C++] = 65;
        }
        if(var_17 ==10)
        {
            buffer[var_C++] = 74;
        }
        if(var_17 ==11)
        {
            buffer[var_C++] = 81;
        }
        if(var_17 ==12)
        {
            buffer[var_C++] = 75;
        }
    }

    buffer[var_C++] = 0;
    strcpy(encrypted_str, buffer);
}

//get a buffer with encrypted message and puts inside it the decrypted message
void decrypt(char* encrypted_str)
{
    int i = 0;      // Position in the encrypted string
    int j = 0;      // Position in the decrypted string
    int length = strlen(encrypted_str);
    char decrypted_str[length];
    while(i < length)
    {
        int higher_nibble = 0;
        int lower_nibble = 0;
        if(encrypted_str[i] == 10  || encrypted_str[i] == 13)
        {
            decrypted_str[j] = encrypted_str[i];
            j++;
            i++;
            continue;
        }

        if (i + 1 < length - 1 && encrypted_str[i + 1] == 43) {
            int var_1C = encrypted_str[i++] - 48;
            i++;
            higher_nibble = encrypted_str[i++] + var_1C - 48; //not accurate
        } else if (i + 1 < length - 1 && encrypted_str[i + 1] == 45) {
            higher_nibble = 0;
            i += 3;
        } else if (encrypted_str[i] == 65) {
            higher_nibble = 1;
            i++;
        } else if (encrypted_str[i] == 74) {
            higher_nibble = 10;
            i++;
        } else if (encrypted_str[i] == 81) {
            higher_nibble = 11;
            i++;
        } else if (encrypted_str[i] == 75) {
            higher_nibble = 12;
            i++;
        } else {
            higher_nibble = encrypted_str[i] - 48;
            DYNAMIC_ASSERT(higher_nibble <= 9, "higher_nibble is not <= 9");
            DYNAMIC_ASSERT(higher_nibble >= 2, "higher_nibble is not >= 2");
            i++;
        }


        if (i + 1 < length - 1 && encrypted_str[i + 1] == 43) {
            int var_1C = encrypted_str[i++] - 48;
            i++;
            lower_nibble = encrypted_str[i++] + var_1C - 48; //not accurate
        } else if (i + 1 < length - 1 && encrypted_str[i + 1] == 45) {
            lower_nibble = 0;
            i += 3;
        } else if (encrypted_str[i] == 65) {
            lower_nibble = 1;
            i++;
        } else if (encrypted_str[i] == 74) {
            lower_nibble = 10;
            i++;
        } else if (encrypted_str[i] == 81) {
            lower_nibble = 11;
            i++;
        } else if (encrypted_str[i] == 75) {
            lower_nibble = 12;
            i++;
        } else {
            lower_nibble = encrypted_str[i] - 48;
            DYNAMIC_ASSERT(lower_nibble <= 9, "lower_nibble is not <= 9");
            DYNAMIC_ASSERT(lower_nibble >= 2, "lower_nibble is not >= 2");
            i++;
        }

        decrypted_str[j] = (higher_nibble << 4) + lower_nibble;
        j++;
    }
    for(int k=0; k < j; k++)
    {
        encrypted_str[k] = decrypted_str[k];
    }
    encrypted_str[j] = '\0';
}








int main()
{
    return 0;
}