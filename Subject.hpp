/* 
 * File:   Subject.hpp
 * Author: Alexandre
 *
 * Created on 24 janvier 2014, 00:31
 */

#ifndef SUBJECT_HPP
#define	SUBJECT_HPP

#include <vector>
#include "Observer.hpp"

using namespace std;

class Subject {
public:    
    virtual void addObserver(Observer* o);
    virtual void removeObserver(Observer* o);
    virtual void notifyObservers() = 0;
protected:
    vector<Observer *> observers;
};

#endif	/* SUBJECT_HPP */

