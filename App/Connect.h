//
// Created by user on 05.03.23.
//

#ifndef MANIPULATOR_CONNECT_H
#define MANIPULATOR_CONNECT_H


#include <atomic>
#include <chrono>
#include <cstring>
#include <fcntl.h>
#include <functional>
#include <iostream>
#include <map>
#include <mutex>
#include "ncurses.h"
#include <string>
#include <termios.h>
#include <unistd.h>
#include "../Arduino/Config.h"
#include "Exception.h"
#include "Gservo.h"
#include "str.h"
#include "Vision.h"


inline std::mutex connect_mutex;

inline struct termios SerialPortSettings;


class Connect {
private:
    inline static int Arduino = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NONBLOCK);
    inline static uint8_t command[COMMAND_SIZE];
    inline static uint8_t message[MESSAGE_SIZE];
    inline static std::map<std::string, std::function<void(void)>> command_map;

public:
    inline static str key_cmd;

public:
    static void exchange();
    static void resetCommand();

private:
    static bool openArduino();

public:
    static bool setConnection();
    static void disconnectArduino();

private:
    static uint8_t crc8(const uint8_t pocket[], uint64_t size);
    static void calcCommandCheckSum();
    static uint8_t calcMessageCheckSum(uint8_t buffer[]);

public:
    static void sendCommand();

private:
    static void setTask(uint8_t task);
    static void setValue(uint16_t value);
    static void encodeCommand(uint64_t cmd);

    static void decodeMessage();
    static Gservo* findGservo(uint8_t id);

public:
    static bool receiveMessage();

private:
    static uint64_t checkNumberCommand(std::string s);

public:
    static void stop();
    static void moveForward();
    static void moveBackward();
    static void turnRight();
    static void turnLeft();
    static void push();
    static void pop();
    static void rise();
    static void drop();
    static void beep();
    static void rotate(uint8_t angle);
    static void shake();
    static void visionBlink(int pin);
    static void blink();

    static void decodeKeyInput();

private:
    static void initCommandMap();
};


#endif //MANIPULATOR_CONNECT_H
