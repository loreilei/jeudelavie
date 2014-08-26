/* 
 * File:   GridRenderer.hpp
 * Author: Alexandre
 *
 * Created on 24 janvier 2014, 00:47
 */

#ifndef GRIDRENDERER_HPP
#define	GRIDRENDERER_HPP

#include <iostream>
#include "SFML/Graphics.hpp"
#include "Observer.hpp"
#include "Grid.hpp"

using namespace std;
using namespace sf;

class GridRenderer : public Observer {
public:
    GridRenderer(RenderWindow* rw, Grid grid);
    GridRenderer(const GridRenderer& orig);
    virtual ~GridRenderer();
    
    void notify(void* data);
    void render();
private:
    RenderWindow* rw;
    Grid grid;
};

#endif	/* GRIDRENDERER_HPP */

