//
// Created by Ryan Vilim on 5/10/20.
//


#include "Apple.h"

using namespace std;

void Apple::FilterPoint(double lam, double phi){
    /*
     * This is function is a bit confusing. It takes in a lambda and phi then overwrites points_idx
     * with a new points_idx where with all points within r (bite radius) removed.
     *
     * It does this using a very optimized version of the Haversine formula
     * (https://en.wikipedia.org/wiki/Haversine_formula) where we have used the angle-sum trig
     * identities to break the trig functions apart. We can then precompute the trig values of
     * all the monte-carlo points and also precompute the trig functions of the actual points,
     * so that looping over the remaining monte carlo points becomes a question of powers and
     * addition.
     *
     * Also, we can pull the last inverse sine in the haversine formula into the ratio r/2R.
     */
    std::vector<int> new_points_idx;
    new_points_idx.reserve(points_idx.size());
    double phi_2_sin = sin(phi/2.0);
    double phi_2_cos = cos(phi/2.0);

    double lam_2_sin = sin(lam/2.0);
    double lam_2_cos = cos(lam/2.0);

    double phi_cos = cos(phi);

    for(int i=0; i<points_idx.size(); i++){
        int idx=points_idx[i];
        const double a = pow(phi_2_sin*points_phi_2_cos[idx] - phi_2_cos*points_phi_2_sin[idx], 2);
        const double b = points_phi_cos[idx] * phi_cos *pow(lam_2_sin*points_lam_2_cos[idx]- lam_2_cos*points_lam_2_sin[idx], 2);
        if (a+b>rFrac){
            new_points_idx.push_back(idx);
        }
    }
    points_idx=new_points_idx;
}

std::array<double, 2> Apple::GenerateSpherePoint(){

    double r_lam = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX));
    double r_phi = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX));

    std::array<double, 2> pt = {M_PI * (2*r_lam-1), asin(r_phi*2-1)};

    return pt;
}

int Apple::Eat(){
    int bites=0;
    while (!points_idx.empty()){
        auto bite_point = GenerateSpherePoint();
        Apple::FilterPoint(bite_point[0], bite_point[1]);
        bites++;
    }

    return bites;
}
void Apple::GenerateSpherePoints(){
    points_lam_2_sin.clear();
    points_phi_2_sin.clear();

    points_lam_2_cos.clear();
    points_phi_2_cos.clear();

    points_phi_cos.clear();
    points_idx.clear();

    for (int i=0; i<N; i++){
        auto pt = GenerateSpherePoint();

        points_lam_2_sin.push_back(sin(pt[0]/2));
        points_phi_2_sin.push_back(sin(pt[1]/2));

        points_lam_2_cos.push_back(cos(pt[0]/2));
        points_phi_2_cos.push_back(cos(pt[1]/2));

        points_phi_cos.push_back(cos(pt[1]));

        points_idx.push_back(i);
    }
}

Apple::Apple( int n_points,  double apple_radius,  double bite_radius) {
    srand((unsigned) time(0));
    N = n_points;
    R = apple_radius;
    r = bite_radius;

    rFrac = pow(sin(r/(2.0*R)),2.0);
}
