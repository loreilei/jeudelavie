/* 
 * File:   main.cpp
 * Author: Alexandre
 *
 * Created on 23 janvier 2014, 16:27
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Grid.hpp"
#include "GridRenderer.hpp"

using namespace std;
using namespace sf;

int nbVoisinVivant(Grid g, int i, int j) {
    int nb = 0;
    int bminlimit = j-1;
    int bmaxlimit = j+1;
    int aminlimit = i-1;
    int amaxlimit = i+1;
    
    if(i == 0) {
        aminlimit = 0;
    }
    else if (i == g.width()-1) {
        amaxlimit = i;
    }
    
    if(j == 0) {
        bminlimit = 0;
    }
    else if(j == g.height()-1) {
        bmaxlimit = j;
    }

    for(int b = bminlimit; b <= bmaxlimit; b++) {
        for(int a = aminlimit; a <= amaxlimit; a++) {
            if(g.get(a,b) && (a != i || b != j)) {
                nb++;
            }
        }
    }
    
    //cout << "Found " << nb << " neighbors alive for (" << i << "," << j << ")" << endl;
    return nb;
}

void setVoisins(Grid &g, int i, int j) {
    g.reset();
    int bminlimit = j-1;
    int bmaxlimit = j+1;
    int aminlimit = i-1;
    int amaxlimit = i+1;
    
    if(i == 0) {
        aminlimit = 0;
    }
    else if (i == g.width()-1) {
        amaxlimit = i;
    }
    
    if(j == 0) {
        bminlimit = 0;
    }
    else if(j == g.height()-1) {
        bmaxlimit = j;
    }

    for(int b = bminlimit; b <= bmaxlimit; b++) {
        for(int a = aminlimit; a <= amaxlimit; a++) {
            if((a != i || b != j)) {
                g.set(true, a, b);
            }
        }
    }
}

void generate(Grid& g) {
    for(int j = 0; j < g.height(); j++) {
        for(int i = 0; i < g.width(); i++) {
            bool value = true;
            float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            if(r < 0.5f)
                value = false;
            g.set(value, i, j);
        }
    }
}

void step(Grid& g) {
    Grid tmp(g.width(), g.height());

    for(int j = 0; j < g.height(); j++) {
        for(int i = 0; i < g.width(); i++) {
            int nb = nbVoisinVivant(g, i, j);
            if(g.get(i,j) && (nb == 2 || nb == 3)) {
                tmp.set(true, i, j);
            }
            else if(!(g.get(i,j)) &&  nb == 3) {
                tmp.set(true, i, j);
            }
            else {
                tmp.set(false, i, j);
            }
        }
    }

    for(int j = 0; j < g.height(); j++) {
        for(int i = 0; i < g.width(); i++) {
                g.set(tmp.get(i, j),i,j);
        }
    }
    

}

bool Collision(Vector2i position,FloatRect box) {
    if (position.x >= box.left 
    && position.x < box.left + box.width
    && position.y >= box.top 
    && position.y < box.top + box.width)
       return true;
   else
       return false;
}

void renderHelp(RenderWindow& window) {
    Sprite spr;
    
    RenderTexture rt;
    rt.create(400, 400);
    rt.clear(Color::White);
    spr.setTexture(rt.getTexture());
    spr.setOrigin(spr.getLocalBounds().width/2,spr.getLocalBounds().height/2 );
    spr.setPosition(300, 300);
    
    window.draw(spr);
    
    RectangleShape rect(Vector2f(395, 395));
    rect.setFillColor(Color::Transparent);
    rect.setOutlineColor(Color(192,192,192));
    rect.setOutlineThickness(5.0);
    rect.setOrigin(rect.getLocalBounds().width/2,rect.getLocalBounds().height/2 );
    rect.setPosition(305, 305);
    window.draw(rect);
    
    sf::Font font;
    font.loadFromFile("res/DejaVuSans.ttf");
    float offset = 20.0f;
    sf::Text text;
    text.setFont(font);
    text.setString("- Jeu de la vie -");
    text.setCharacterSize(30);
    text.setColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2);
    text.setPosition(300, 110+offset);
    window.draw(text);
    
    text.setStyle(sf::Text::Regular);
    text.setCharacterSize(20);
    
    text.setString("Clic sur une cellule :\nTuer/Donner vie a la cellule");
    text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2);
    text.setPosition(300, 160+offset);
    window.draw(text);
    
    text.setString("+/- : Accelerer/Ralentir la simulation");
    text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2);
    text.setPosition(300, 160+25+20+offset);
    window.draw(text);
    
    text.setString("G : Generer une grille aleatoirement");
    text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2);
    text.setPosition(300, 160+2*(25+20)+offset);
    window.draw(text);
    
    text.setString("R : Reset de la grille");
    text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2);
    text.setPosition(300, 160+3*(25+20)+offset);
    window.draw(text);
    
    text.setString("E : Prochaine etape de simulation");
    text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2);
    text.setPosition(300, 160+4*(25+20)+offset);
    window.draw(text);
    
    text.setString("S : Activer/desactiver la\n simulation automatique");
    text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2);
    text.setPosition(300, 160+5*(25+20)+offset);
    window.draw(text);
    
    text.setString("F5 : Activer/desactiver cette aide");
    text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2);
    text.setPosition(300, 160+6*(25+20)+offset);
    window.draw(text);
}

int main()
{
    srand (time(NULL));
    
    Grid g(20, 20);
    
    string title = "Jeu de la vie";
        
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window(VideoMode(600, 600), title, Style::Default, settings);
    
    
    GridRenderer gr(&window, g);
    g.addObserver(&gr);
    
    Clock clk;
    
            
    float space = 0.25f;
    float width = window.getSize().x;
    float height = window.getSize().y;
    int nbLine = g.height();
    int nbCol = g.width();
    float elemWidth = width / (static_cast<float>(nbCol) + space * static_cast<float>(nbCol) + space);
    float elemHeight = height / (static_cast<float>(nbLine) + space * static_cast<float>(nbCol) + space);
    float horizontalSpaceBetweenElement = space*elemWidth;
    float verticalSpaceBetweenElement = space*elemWidth;
    
    bool paused = true;
    float timeBetweenSteps = 0.0f;
    float timeLimit = 1.0f;
    float displaying = true;
    
    
    while (window.isOpen())
    {
        stringstream strs;
        strs << title << " - (" << width << "x" << height << ")";
        if(paused) {
            strs << endl;
        }
        else
        {
           strs << "- Speed : " << 1.0f/timeLimit << endl; //<< " (" << timeLimit << ")" << endl;" 
        }
        window.setTitle(strs.str());
    
        Time elapsed = clk.restart();
        Event event;

        
        
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                    window.close();
            if(!displaying) {
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::G)
                    generate(g);
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::E)
                    step(g);
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::S)
                    paused = !paused;
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::R)
                    g.reset();
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Add) {
                    if(timeLimit- 0.01f > 0.0f) {
                     timeLimit-=0.01f;
                    }
                    else {
                        timeLimit =0.01f;
                    }
                }
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Subtract)
                    timeLimit+=0.01f;

                if((event.type == Event::MouseButtonPressed) && (event.mouseButton.button == Mouse::Left)) {

                    /*
                    bool inElement = false;
                    int xElement = 0;
                    int yElement = 0;

                    for(int j = 0; (j < nbLine && !inElement) ; j++) {
                        for(int i = 0; (i < nbCol && !inElement); i++) {
                            if((event.mouseButton.x <= ((i+1)*horizontalSpaceBetweenElement+(i*elemWidth)+elemWidth))
                                    && (event.mouseButton.x > ((i+1)*horizontalSpaceBetweenElement+(i*elemWidth)))
                                    && (event.mouseButton.y <= ((j+1)*verticalSpaceBetweenElement+(j*elemHeight)+elemHeight))
                                    && (event.mouseButton.y >= ((j+1)*verticalSpaceBetweenElement+(j*elemHeight)))) {
                                inElement = true;
                                bool value = g.get(i, j);
                                g.set(i,j, !(g.get(i, j)));

                            }
                        }
                    }//*/
                    bool cont = true;
                    for(int j = 0; (j < nbLine && cont) ; j++) {
                        for(int i = 0; (i < nbCol && cont); i++) {
                            FloatRect rect((i+1)*horizontalSpaceBetweenElement+(i*elemWidth), (j+1)*verticalSpaceBetweenElement+(j*elemHeight), elemWidth, elemHeight);
                            if(Collision(Mouse::getPosition(window), rect)) {
                                //cout << "In (" << i << "," << j << ")" << endl;
                                cont = false;

                                g.set(!(g.get(i, j)), i,j);

                            }
                        }
                    }//*/
                }
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::F5) {
                displaying = !displaying;
                //paused = !paused;
            }
                    
        }
        
        /*
        bool cont = true;
        for(int j = 0; (j < nbLine && cont) ; j++) {
            for(int i = 0; (i < nbCol && cont); i++) {
                FloatRect rect((i+1)*horizontalSpaceBetweenElement+(i*elemWidth), (j+1)*verticalSpaceBetweenElement+(j*elemHeight), elemWidth, elemHeight);
                if(Collision(Mouse::getPosition(window), rect)) {
                    //g.set(i,j, !(g.get(i, j)));
                    //window.clear(Color::Green);
                    //cout << "In (" << i << "," << j << ")" << endl;
                    setVoisins(g, i, j);
                    cont = false;
                }
            }
        }//*/
        window.clear();
        if(!paused) {
            if(timeBetweenSteps > timeLimit) {
                step(g);
                timeBetweenSteps = 0.0f;
            }
            else {
                timeBetweenSteps += elapsed.asSeconds();
            }
        }
        else{
            timeBetweenSteps += elapsed.asSeconds();
        }
        
        gr.render();
        
        if(displaying) {
                renderHelp(window);
        }
        
        window.display();
    }

    return 0;
}
