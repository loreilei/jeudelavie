/* 
 * File:   Grid.cpp
 * Author: Alexandre
 * 
 * Created on 23 janvier 2014, 16:36
 */

#include "Grid.hpp"

Grid::Grid() {
    this->init(10, 10, false);
}

Grid::Grid(int w, int h) {
    this->init(w, h, false);
}

Grid::Grid(int w, int h, bool value) {
    this->init(w, h, value);
}

Grid::Grid(const Grid& orig) {
    for(int j = 0; j < orig.grid.size(); j++) {
        vector<bool> temp;
        for(int i = 0; i < orig.grid.at(j).size(); i++) {
            temp.push_back(orig.grid.at(j).at(i));
        }
        this->grid.push_back(temp);
    }
}

Grid::~Grid() {
}

bool Grid::get(int i, int j) throw(exception) {
    return this->grid.at(j).at(i);
}

void Grid::set(bool value, int i, int j) throw(exception) {
    
    //cout << "Setting (" << i << "," << j << ") from " << this->grid.at(j).at(i) << " to " << value << endl;
    this->grid.at(j).at(i) = value;
                
    this->notifyObservers();
}

void Grid::reset() {
    int w = this->width();
    int h = this->height();
    this->grid.clear();
    this->init(w, h, false);
}

int Grid::width() {
    return this->grid.at(0).size();
}

int Grid::height() {
    return this->grid.size();
}

void Grid::init(int w, int h, bool value) {
    for(int j = 0; j < h; j++) {
        vector<bool> temp;
        for(int i = 0; i < w; i++) {
            temp.push_back(value);
        }
        this->grid.push_back(temp);
    }
    this->notifyObservers();
}

void Grid::notifyObservers() {
    for(vector<Observer *>::iterator it = this->observers.begin(); it != this->observers.end(); it++ ) {
        (*it)->notify(this);
    }
}
