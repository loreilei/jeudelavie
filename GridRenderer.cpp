/* 
 * File:   GridRenderer.cpp
 * Author: Alexandre
 * 
 * Created on 24 janvier 2014, 00:47
 */

#include "GridRenderer.hpp"
#include "Grid.hpp"

GridRenderer::GridRenderer(RenderWindow* rw, Grid grid) {
    this->rw = rw;
    this->grid = grid;
}

GridRenderer::GridRenderer(const GridRenderer& orig) {
    this->rw = orig.rw;
    this->grid = orig.grid;
}

GridRenderer::~GridRenderer() {
}

void GridRenderer::notify(void* data) {
    
    this->grid = *((Grid*)data);
    /*
    cout <<  " ############### " << endl;
    for(int j = 0; j < this->grid.height(); j++) {
        for(int i = 0; i < this->grid.width(); i++) {
            cout << this->grid.get(i, j) << " ";
        }
        cout << endl;
    }
    cout <<  " ############### " << endl;//*/
}

void GridRenderer::render() {
    float space = 0.25f;
    float width = this->rw->getSize().x;
    float height = this->rw->getSize().y;
    int nbLine = this->grid.height();
    int nbCol = this->grid.width();
    float elemWidth = width / (static_cast<float>(nbCol) + space * static_cast<float>(nbCol) + space);
    float elemHeight = height / (static_cast<float>(nbLine) + space * static_cast<float>(nbCol) + space);
    float horizontalSpaceBetweenElement = space*elemWidth;
    float verticalSpaceBetweenElement = space*elemWidth;
    
    RectangleShape shape(Vector2f(elemWidth, elemHeight));
    Color activatedColor = Color::White;
    Color desactivatedColor = Color(64,64,64,255);
    for(int j = 0; j < nbLine; j++) {
        for(int i = 0; i < nbCol; i++) {
            shape.setPosition((i+1)*horizontalSpaceBetweenElement+(i*elemWidth), (j+1)*verticalSpaceBetweenElement+(j*elemHeight));
            /*
            int r = static_cast<int>((static_cast<float>(j)/static_cast<float>(nbLine))*255);
            int b = static_cast<int>((static_cast<float>(i)/static_cast<float>(nbCol))*255);
            shape.setFillColor(Color(r, 0, b));//*/
            //*
            if(this->grid.get(i, j))
                shape.setFillColor(activatedColor);
            else
                shape.setFillColor(desactivatedColor);//*/
            this->rw->draw(shape);
        }
    }
}