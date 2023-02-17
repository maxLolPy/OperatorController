//
// Created by Max on 17.02.2023.
//
#include <Arduino.h>
#include "GyroSender.h"
#include "settings.h"

GyroSender::GyroSender() {
    radio = (RF24(CE, CSN));
    byte buf[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"};
    memcpy(address, buf, sizeof(buf));
    radio.begin();                      // активировать модуль
    radio.setAutoAck(true);                // режим подтверждения приёма, 1 вкл 0 выкл
    radio.setRetries(0, 15);            // (время между попыткой достучаться, число попыток)
    radio.enableAckPayload();           // разрешить отсылку данных в ответ на входящий сигнал
    radio.setPayloadSize(16);           // размер пакета, в байтах
    radio.openWritingPipe(address[0]);  // мы - труба 0, открываем канал для передачи данных
    radio.setChannel(CHANNEL);             // выбираем канал (в котором нет шумов!)
    radio.setPALevel(POWER_LEVEL);      // уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
    radio.setDataRate(SEND_SPEED);      // скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
    // должна быть одинакова на приёмнике и передатчике!
    // при самой низкой скорости имеем самую высокую чувствительность и дальность!!
    // ВНИМАНИЕ!!! enableAckPayload НЕ РАБОТАЕТ НА СКОРОСТИ 250 kbps!
    radio.powerUp();        // начать работу
    radio.stopListening();  // не слушаем радиоэфир, мы передатчик
}
void GyroSender::tick(){
    if (millis() - send_data_tmr > 300) {      //отправляем данные получателю каждые 300мс
        int val[9];
        createPkg(val);
        radio.write(val, 9);
        send_data_tmr = millis();
    }
}

void GyroSender::createPkg(int * val) {
//TODO
}