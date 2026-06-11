#include "Input_32chanel.h"

Input_32chanel::Input_32chanel(TCA6416A chanel0x20, TCA6416A chanel0x21){
    this->chanel0x20 = chanel0x20;
    this->chanel0x21 = chanel0x21;
    this->intFlag = false;
}

Input_32chanel::~Input_32chanel()
{
}

void Input_32chanel::updateAllInput(){
    uint32_t tempRegister;
    tempRegister = chanel0x20.digitalRead16() | chanel0x21.digitalRead16() << 16;
    for (uint8_t i = 0; i < 32; i++){
        bool value = tempRegister & 0x00000001;
        setInputRegister(i, value);
        tempRegister = tempRegister >> 1;
    }
    
}


void Input_32chanel::setInputRegister(uint8_t index, bool val){
    index = mixerIndex[index];
    if (val){
            this->input32bitRegister |= 1ul << index;
        }
        else{
            this->input32bitRegister &= ~(1ul << index);
    }
}

bool Input_32chanel::getChanelValue(uint8_t chanel){
    return (bool)input32bitRegister & 1ul << chanel;
}


void Input_32chanel::loop(){
    if (this->intFlag){
        if (millis() > this->timeToRead){
            this->updateAllInput();
            this->intFlag = false;
        }
        
    }
    
}

void Input_32chanel::begin(){
    chanel0x20.setPinMode16(0xFFFF);
    chanel0x20.setPolarity16(0xFFFF);
    chanel0x21.setPinMode16(0xFFFF);
    chanel0x21.setPolarity16(0xFFFF);
}

