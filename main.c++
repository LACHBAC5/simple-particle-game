#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

#define scrwidth 450
#define scrheight 450

#define boxoffsetx 30
#define boxoffsety 30

#define windowupdate 30
#define calcupdate 0.5
#define circlespd 10

#define ccd true
#define wcd true

#define pi 3.14159265

class circle{
    public:
    Color rgb;
    float x, y;
    float angle;
    int r;

    bool collided = false;
    float collangle = 0;
    int times = 0;

    bool targeted = false;

    circle(float X, float Y, float ANGLE, int R, Color RGB){
        x = X, y = Y, angle = ANGLE, r = R, rgb = RGB; 
    }
};

RenderWindow window(sf::VideoMode(scrwidth, scrheight), "test!");
vector<circle> vec;
bool pause = false;

float p1x, p1y, p2x, p2y;

void timer(){
    int times = 0;

    time_t start = clock();
    while(true){
        if(!window.isOpen()){
            return;
        }
        if(float(clock()-start)/1000000 > calcupdate && !pause){
            float time = 0;
            float AC, BC;
            while(calcupdate-time > 0){
                float timeaddr = calcupdate-time;

                for(int i = 0; i < vec.size(); i++){
                    if(ccd){
                        for(int o = i+1; o < vec.size(); o++){
                            float AB1 = vec[i].r+vec[o].r;

                            float a = pow(cos(vec[i].angle*pi/180)*circlespd-cos(vec[o].angle*pi/180)*circlespd, 2) + pow(sin(vec[o].angle*pi/180)*circlespd-sin(vec[i].angle*pi/180)*circlespd, 2);
                            float b = (2 * (vec[i].x-vec[o].x) * (cos(vec[i].angle*pi/180)*circlespd-cos(vec[o].angle*pi/180)*circlespd)) + (2 * (vec[i].y-vec[o].y) * (sin(vec[o].angle*pi/180)*circlespd-sin(vec[i].angle*pi/180)*circlespd));
                            float c = pow(vec[i].x, 2) + pow(vec[o].x, 2) - 2 * vec[i].x*vec[o].x + pow(vec[i].y, 2) + pow(vec[o].y, 2) - 2 * vec[i].y*vec[o].y - pow(AB1, 2);

                            float D = pow(b, 2) - 4 * a * c;

                            float t1 = (- b - sqrt(D)) / (2 * a);
                            //float t2 = (- b + sqrt(D)) / (2 * a);
                            
                            if(t1 > 0){
                                if(t1 < timeaddr){
                                    for(int p = 0; p < vec.size(); p++){
                                        vec[p].collided = false;
                                        vec[p].collangle = 0;
                                        vec[p].times = 0;
                                    }
                                    timeaddr = t1;
                                }
                                if(t1 == timeaddr){
                                    float addangl = atan2((vec[o].y-vec[i].y), (vec[i].x-vec[o].x))/pi*180;
                                    vec[i].collided = true;
                                    vec[i].collangle += addangl;
                                    vec[i].times ++;

                                    addangl = atan2((vec[i].y-vec[o].y), (vec[o].x-vec[i].x))/pi*180;
                                    vec[o].collided = true;
                                    vec[o].collangle += addangl;
                                    vec[o].times ++;
                                }
                            }
                        }
                    }
                    if(wcd){
                        float top = fabs((vec[i].y-p1y)/sin(vec[i].angle*pi/180)/circlespd);
                        bool pot = false;
                        if(sin(vec[i].angle*pi/180)/circlespd > 0){
                            pot = true;
                        }
                        float bot = fabs((p2y-vec[i].y)/sin(vec[i].angle*pi/180)/circlespd);
                        bool tob = false;
                        if(sin(vec[i].angle*pi/180)/circlespd < 0){
                            tob = true;
                        }
                        float right = fabs((p2x-vec[i].x)/cos(vec[i].angle*pi/180)/circlespd);
                        bool thgir = false;
                        if(cos(vec[i].angle*pi/180)/circlespd > 0){
                            thgir = true;
                        }
                        float left = fabs((vec[i].x-p1x)/cos(vec[i].angle*pi/180)/circlespd);
                        bool tfel = false;
                        if(cos(vec[i].angle*pi/180)/circlespd < 0){
                            tfel = true;
                        }
                        float sides[4] = {top, bot, right, left};
                        bool check[4] = {pot, tob, thgir, tfel};
                        for(int o = 0 ; o < 4; o++){
                            if(sides[o] < timeaddr && check[o]){
                                timeaddr = sides[o];
                                for(int p = 0; p < vec.size(); p++){
                                    vec[p].collided = false;
                                    vec[p].collangle = 0;
                                    vec[p].times = 0;
                                }
                            }
                        }
                        if(timeaddr == top && pot){
                            vec[i].collided = true;
                            vec[i].collangle += 270;
                            vec[i].times ++;
                        }
                        else if(timeaddr == left && tfel){
                            vec[i].collided = true;
                            vec[i].collangle += 0;
                            vec[i].times ++;
                        }
                        else if(timeaddr == bot && tob){
                            vec[i].collided = true;
                            vec[i].collangle += 90;
                            vec[i].times ++;
                        }
                        else if(timeaddr == right && thgir){
                            vec[i].collided = true;
                            vec[i].collangle += 180;
                            vec[i].times ++;
                        }
                    }
                }

                for(int i = 0; i < vec.size(); i++){
                    vec[i].x += cos(vec[i].angle*pi/180)*timeaddr*circlespd;
                    vec[i].y -= sin(vec[i].angle*pi/180)*timeaddr*circlespd;

                    if(vec[i].collided){
                        float angle = vec[i].collangle/vec[i].times;
                        float size = fabs(2 * sin(fabs(fabs(angle-vec[i].angle)-90)*pi/180));

                        float Cx = vec[i].x + cos(vec[i].angle*pi/180) + cos(angle*pi/180) * size;
                        float Cy = vec[i].y - sin(vec[i].angle*pi/180) - sin(angle*pi/180) * size;
                        //cout << i << ' ' << vec[i].angle << ' ' << vec[i].collangle << ' ' << vec[i].times << ' ';
                        vec[i].angle = atan2((vec[i].y-Cy), (Cx-vec[i].x))/pi*180;
                        if(vec[i].angle > 360){
                            vec[i].angle -= 360;
                        }
                        else if(vec[i].angle < 0){
                            vec[i].angle += 360;
                        }
                        //cout << vec[i].angle << '\n';

                        vec[i].collided = false;
                        vec[i].collangle = 0;
                        vec[i].times = 0;
                    }
                }
                time += timeaddr;
            }
            start = clock();
        }
    }
}

int main(){
    p1x = boxoffsetx, p1y = boxoffsety;
    p2x = scrwidth - boxoffsetx, p2y = scrheight - boxoffsety;
    Thread core1(&timer);
    core1.launch();
    /*
    for(int i = 0; i <= 355; i+=10){
        vec.push_back(circle(scrwidth/2, scrheight/2, i, 5, Color::White));
    }
    */
    /*
    vec.push_back(circle(scrwidth/2-50, scrheight/2-11, 0, 10, Color::Red));
    vec.push_back(circle(scrwidth/2-50, scrheight/2+11, 0, 10, Color::Red));
    vec.push_back(circle(scrwidth/2+50, scrheight/2, 180, 10, Color::Blue));
    */
    vec.push_back(circle(scrwidth/2-50, scrheight/2-50, 315, 10, Color::Red));
    vec.push_back(circle(scrwidth/2-50, scrheight/2+50, 45, 10, Color::Red));
    vec.push_back(circle(scrwidth/2+50, scrheight/2-50, 225, 10, Color::Red));
    vec.push_back(circle(scrwidth/2+50, scrheight/2+50, 135, 10, Color::Red));
    

    float spawnangl = 0;
    window.setFramerateLimit(windowupdate);
    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
                core1.wait();
                core1.terminate();
            }
            else if(event.type == Event::KeyPressed){
                if(event.key.code == Keyboard::C){
                    cout << "cleard...\n";
                    vec.clear();
                }
                else if(event.key.code == Keyboard::P){
                    if(pause){
                        cout << "pause... false\n";
                        pause = false;
                    }
                    else
                    {
                        cout << "pause... true\n";
                        pause = true;
                    }
                }
                else if(event.key.code == Keyboard::Enter){
                    cout << "number of circles... " << vec.size() << '\n'; 
                }
            }
            else if(event.type == Event::MouseButtonPressed){
                if(event.mouseButton.button == Mouse::Left){
                    int x = Mouse::getPosition(window).x, y = Mouse::getPosition(window).y;
                    for(int i = 0; i < vec.size(); i++){
                        if(fabs(vec[i].x - x) < vec[i].r && fabs(vec[i].y - y) < vec[i].r){
                            vec[i].targeted = true;
                            break;
                        }
                    }
                }
                else if(event.mouseButton.button == Mouse::Right){
                    int x = Mouse::getPosition(window).x, y = Mouse::getPosition(window).y;
                    vec.push_back(circle(x, y, spawnangl, 5, Color::White));
                }
            }
            else if(event.type == Event::MouseButtonReleased){
                if(event.mouseButton.button == Mouse::Left){
                    for(int i = 0; i < vec.size(); i++){
                        vec[i].targeted = false;
                    }
                }
            }
            else if(event.type == sf::Event::MouseWheelMoved){
                int x = Mouse::getPosition(window).x, y = Mouse::getPosition(window).y;
                bool missed = true;
                for(int i = 0; i < vec.size(); i++){
                    if(fabs(vec[i].x - x) < vec[i].r && fabs(vec[i].y - y) < vec[i].r){
                        vec[i].angle += event.mouseWheel.delta*5;
                        missed = false;
                        break;
                    }
                }
                if(missed){
                    spawnangl += event.mouseWheel.delta*5;
                }
            }
            for(int i = 0; i < vec.size(); i++){
                if(vec[i].targeted == true){
                    vec[i].x = Mouse::getPosition(window).x;
                    vec[i].y = Mouse::getPosition(window).y;
                }
            }
        }
        window.clear(Color::Black);
        CircleShape circle1;
        for(int i = 0; i < vec.size(); i++){
            circle1.setFillColor(vec[i].rgb);
            circle1.setRadius(vec[i].r);
            circle1.setPosition(Vector2f(int(vec[i].x-vec[i].r), int(vec[i].y-vec[i].r)));
            window.draw(circle1);
        }
        Vertex line[] = {Vertex(Vector2f(p1x, p1y)),Vertex(Vector2f(p2x, p1y))};
        window.draw(line, 2, sf::Lines);
        line[0] = Vertex(Vector2f(p1x, p1y)), line[1] = Vertex(Vector2f(p1x, p2y));
        window.draw(line, 2, sf::Lines);
        line[0] = Vertex(Vector2f(p2x, p2y)), line[1] = Vertex(Vector2f(p1x, p2y));
        window.draw(line, 2, sf::Lines);
        line[0] = Vertex(Vector2f(p2x, p2y)), line[1] = Vertex(Vector2f(p2x, p1y));
        window.draw(line, 2, sf::Lines);

        window.display();
    }
}
