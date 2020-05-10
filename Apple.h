//
// Created by Ryan Vilim on 5/10/20.
//

#ifndef APPLE_APPLE_H
#define APPLE_APPLE_H

#include <iostream>
#include <cstdlib>
#include <math.h>
#include <list>
#include <array>
#include <vector>
#include <random>


class Apple {
public:
    void GenerateSpherePoints();
    void FilterPoint(double lam, double phi);
    int Eat();

    Apple( const int NPoints, double AppleRadius,  double BiteRadius);

private:
    int N;
    double r, R;
    std::array<double, 2> GenerateSpherePoint();

//    std::vector<double> points_lam;
//    std::vector<double> points_phi;

    std::vector<int> points_idx;

    std::vector<double> points_lam_2_sin;
    std::vector<double> points_phi_2_sin;

    std::vector<double> points_lam_2_cos;
    std::vector<double> points_phi_2_cos;

    std::vector<double> points_lam_cos;
    std::vector<double> points_phi_cos;
    double rFrac;
//    std::list < std::array<double, 2>  > points;
};


#endif //APPLE_APPLE_H
