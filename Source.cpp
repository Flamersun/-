#include<iostream>
using namespace std;

class self_synchronizing_scrambler
{
    unsigned char key;
    unsigned char shift_register;

    bool pickbit(const unsigned char val, const short index)
    {
        return ((val >> index) % 2);
    }

public:
    self_synchronizing_scrambler() {}

    self_synchronizing_scrambler(unsigned char key, unsigned char shift_register)
    {
        this->key = key;
        this->shift_register = shift_register;
    }

    void assign_key(unsigned char key) { this->key = key; }
    void assign_register(unsigned char shift_register) { this->shift_register = shift_register; }

    unsigned char key_value() { return key; }
    unsigned char register_value() { return shift_register; }

    void scramble(unsigned char& letter)
    {
        unsigned char output = 0;
        for (unsigned char i = 0; i < 8; ++i)
        {
            bool newbit = pickbit(letter, 7 - i);
            for (unsigned char j = 0; j < 8; ++j)
            {
                newbit ^= pickbit(this->key, 7 - j) & pickbit(this->shift_register, 7 - j);
            }
            output ^= (newbit << (7 - i));

            key = (key >> 1) + (newbit << 7);
        }
        letter = output;
    }

    void descramble(unsigned char& letter)
    {
        unsigned char output = 0;
        for (unsigned char i = 0; i < 8; ++i)
        {
            bool oldbit = pickbit(letter, 7 - i), scrambit = 0;
            for (unsigned char j = 0; j < 8; ++j)
            {
                scrambit ^= pickbit(this->key, 7 - j) & pickbit(this->shift_register, 7 - j);
            }
            output ^= ((scrambit ^ oldbit) << (7 - i));

            key = (key >> 1) + (oldbit << 7);
        }
        letter = output;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    self_synchronizing_scrambler A(5, 17);
    unsigned char input;
    //unsigned char output;
    cout << "Введите слово для шифрования."<<endl;
    while (scanf_s("%c", &input))
    {
        if (input == '\n') break;
        A.scramble(input);

        printf("%x ", input);
        //output = input;
        //A.descramble(output);
        //printf("%x \n", output);
    }
    cout << "Шифрование завершено."<<endl;
    cout << "Введите для расшифровки."<<endl;

    self_synchronizing_scrambler B(5,17);
    unsigned short scrambled;
    unsigned char output;
 
    while (cin >> hex >> scrambled)
    {
        if (scrambled == 'stop') break;
       output = scrambled;
        B.descramble(output);
        cout << output;
    }
    cout << "Рашифровка завершена."<<endl;
    return 0;
}