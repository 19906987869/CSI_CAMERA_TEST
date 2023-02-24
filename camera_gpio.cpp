#include "camera_gpio.h"
#include <chrono>
#include <thread>
#include <signal.h>
#include <JetsonGPIO.h>
#include "mainwindow.h"

using namespace std;
//static bool end_this_program = false;
static bool flag = false;
camera_gpio::camera_gpio()
{

}

void camera_gpio::gpio_start(){
    int output_pin = 7;
    int input_pin = 18;
    int oldgpio = 1;
    GPIO::setmode(GPIO::BOARD);
    GPIO::setup(output_pin,GPIO::OUT, GPIO::LOW);
    GPIO::setup(input_pin,GPIO::IN);
    while (1) {
        int in_curr = GPIO::input(input_pin);
        qDebug() << "inputting" << in_curr << "to pin";
        delay(1);
        if(in_curr == 1 && oldgpio == 0){
            MainWindow* mw = new MainWindow();
            mw->BinarzationStack();
        }
        oldgpio = in_curr;

    }
    cleanup();
}

void camera_gpio::delay(int s){
    this_thread::sleep_for(chrono::seconds(s));
}

void camera_gpio::cleanup(){
    GPIO::cleanup();
}
