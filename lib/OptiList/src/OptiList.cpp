//
// Created by Max on 17.02.2023.
//

#include <Arduino.h>
#include "OptiList.h"

OptiList::OptiList() {
    Count=0;
    firstElement= nullptr;
}

void OptiList::push(MPUGyro * gyroInfo) {
    if (firstElement == nullptr){
        firstElement = (OptiList::data*) malloc(sizeof(OptiList::data));
        OptiList::data buf{
                gyroInfo,
                nullptr
        };
        *firstElement = buf;
    } else {
        OptiList::data *ptr = firstElement;
        for (;ptr->next != nullptr; ptr = ptr->next){}
        ptr->next = (OptiList::data*) malloc(sizeof(OptiList::data));
        OptiList::data buf{};
        buf.gyroInfo = gyroInfo;
        buf.next = nullptr;
        *(ptr->next) = buf;
    }
    Count++;
}
MPUGyro * OptiList::getById(int id) {
    if (firstElement== nullptr){
        return nullptr;
    } else {
        OptiList::data *ptr = firstElement;
        int i=0;
        for (;ptr->next != nullptr && i<id; ptr = ptr->next, i++){}
        return i==id?ptr->gyroInfo: nullptr;
    }
}
