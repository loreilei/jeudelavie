/* 
 * File:   Subject.cpp
 * Author: Alexandre
 * 
 * Created on 24 janvier 2014, 00:33
 */

#include "Subject.hpp"

void Subject::addObserver(Observer* o) {
    this->observers.push_back(o);
}

void Subject::removeObserver(Observer* o) {
    bool found = false;
    for(vector<Observer *>::iterator it = this->observers.begin(); (it != this->observers.end() && !found); it++ ) {
        if(*it == o) {
                this->observers.erase(it);
                found = true;
        }
    }
}