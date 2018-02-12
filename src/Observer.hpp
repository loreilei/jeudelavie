/* 
 * File:   Observer.hpp
 * Author: Alexandre
 *
 * Created on 24 janvier 2014, 00:38
 */

#ifndef OBSERVER_HPP
#define	OBSERVER_HPP

class Observer {
public:
    virtual void notify(void* data) = 0;
private:

};

#endif	/* OBSERVER_HPP */

