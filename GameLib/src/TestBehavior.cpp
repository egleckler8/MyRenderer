/**
 * @file TestBehavior.cpp
 * @author Elijah Gleckler
 */
#include <iostream>
#include "TestBehavior.h"

#include "GameObject.h"

const double r = 3;
const double omega = 0.8;


/**
 * Simple thing that just makes it move
 * @param dt
 */
void TestBehavior::Update(double t)
{
    std::cout << "dt: " << t << std::endl;
    auto object = GetExhibitor();

    double x = r * sin(omega * t);
    double y = 4;
    double z = r * cos(omega * t);

    glm::vec3 p(x, y, z);

    object->SetPosition(p);


}
