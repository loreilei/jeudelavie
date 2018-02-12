/* 
 * File:   Grid.hpp
 * Author: Alexandre
 *
 * Created on 23 janvier 2014, 16:36
 */

#ifndef GRID_HPP
#define	GRID_HPP

#include <vector>
#include <exception>
#include <iostream>
#include "Subject.hpp"

using namespace std;


class Grid : public Subject{
public:
    Grid();
    Grid(int w, int h);
    Grid(int w, int h, bool value);
    Grid(const Grid& orig);
    virtual ~Grid();
    
    bool get(int i, int j) throw(exception);
    void set(bool value, int i, int j) throw(exception);
    void reset();
    
    int width();
    int height();
    
    void notifyObservers();
private:
    void init(int w, int h, bool value);
    vector<vector< bool > > grid;
};

#endif	/* GRID_HPP */

