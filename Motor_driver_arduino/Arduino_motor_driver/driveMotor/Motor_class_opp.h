const uint8_t L1E1= 3, L1E2= 5, L2E1= 6, L2E2= 8, LATCHPIN= 9, CLOCKPIN= 12, DATAPIN= 11;

class motorDriver{
  private:
    uint8_t _latch;
    uint8_t _clock;
    uint8_t _data;
    uint8_t _l1e1, _l1e2, _l2e1, _l2e2;

    void _pushData(byte datas){//helps push out data to the register
      digitalWrite(_latch, LOW);
      shiftOut(_data, _clock, LSBFIRST, datas);
      digitalWrite(_latch, HIGH);
    }

    String _setBin(const String& command){
      if (command == "forward")  return "10";
      else if (command == "backward") return "01";
      else if (command == "off")      return "00";
      else {
        Serial.println("Error input....please enter valid input!!!!!!");
      }
    }
    byte _stringToByte(const String& strValue) {
      byte value = 0;
      for (uint8_t i = 0; i < 8; i++) {
        value <<= 1;
        if (strValue[i] == '1') value |= 1;
      }
      return value;
}

  public:
    motorDriver(const uint8_t latchPin, const uint8_t clockPin, const uint8_t dataPin, const uint8_t l1e1Pin, const uint8_t l1e2Pin, const uint8_t l2e1Pin, const uint8_t l2e2Pin){
      _latch=latchPin;
      _clock=clockPin;
      _data=dataPin;
      _l1e1=l1e1Pin;
      _l1e2=l1e2Pin;
      _l2e1=l2e1Pin;
      _l2e2=l2e2Pin;
    }
    
    void init(){//helps innitializes shift registers pin for their respective mode
      pinMode(_latch, OUTPUT);
      pinMode(_data, OUTPUT);
      pinMode(_clock, OUTPUT);
      //below lines helps to initialize motor speed
      analogWrite(_l1e1, 140);
      analogWrite(_l1e2, 190);
      analogWrite(_l2e1, 250);
      analogWrite(_l2e2, 0);
    }

    
    void setSpeed(const uint8_t speed1, const uint8_t speed2, const uint8_t speed3, const uint8_t speed4){//helps set individua motor speed i.e 'M1' for motor 1 or 'M2' for motor 2"
        analogWrite(_l1e1, speed1);
        analogWrite(_l1e2, speed2);
        analogWrite(_l2e1, speed3);
        analogWrite(_l2e2, speed4);
    }

    void setDirection(const String& motor1State, const String& motor2State, const String& motor3State, const String& motor4State){//motor state can wither be 'forward', 'backward', 'off'
       String strByte = _setBin(motor1State)+_setBin(motor2State)+_setBin(motor3State)+_setBin(motor4State);
       byte data=  _stringToByte(strByte);
       Serial.println(data, BIN);
       _pushData(data);
    }

};
