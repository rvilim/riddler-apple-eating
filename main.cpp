#include <iostream>
#include "Apple.h"

int main() {
    const int NPoints=10000;
    const int nDraws = 1000;
    const int AppleRadius = 4;
    const int BiteRadius= 1;

    std::array<int, 10000> bites;
    for(int i=0; i<10000;i++){
        bites[i]=0;
    }

    Apple a(NPoints, AppleRadius, BiteRadius);
    for (int i = 0; i < nDraws; i++) {
        a.GenerateSpherePoints();
        auto b = a.Eat();

        if(b<9999){
            bites[b]++;
        }

    }

    double expected_bites = 0;
    for (int i = 0; i < 10000; i++) {
        std::cout<<i<<", "<<bites[i]<<std::endl;
        expected_bites+=i*bites[i]/(double)nDraws;
    }

    std::cout<<expected_bites<<std::endl;
    return 0;
}
