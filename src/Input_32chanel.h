#ifndef B7BFD2CB_629A_4A0F_AC94_C2D372ECC938
#define B7BFD2CB_629A_4A0F_AC94_C2D372ECC938

#include <Arduino.h>
#include <TCA6416A.h>

class Input_32chanel
{
private:
    TCA6416A chanel0x20, chanel0x21;
    void setInputRegister(uint8_t index, bool value);
//                                    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
    const uint8_t mixerIndex[32] = {  16, 17, 18, 19, 20, 21, 22, 23, 7,  6,  5,  4,  3,  2,  1,  0,  24, 25, 26, 27, 28, 29, 30, 31, 15, 14, 13, 12, 11, 10, 9,  8};
public:
    Input_32chanel(TCA6416A, TCA6416A);
    ~Input_32chanel();

    uint32_t input32bitRegister;
    void updateAllInput();
};



#endif /* B7BFD2CB_629A_4A0F_AC94_C2D372ECC938 */
