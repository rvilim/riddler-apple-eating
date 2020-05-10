#include <iostream>
#include "Apple.h"

int main() {
    std::array<int, 10000> bites;
    for(int i=0; i<10000;i++){
        bites[i]=0;
    }
    const int nDraws = 100000;
    Apple a(10000, 4, 1);
    for (int i = 0; i < nDraws; i++) {
        if(i%1000==0){
            std::cout<<i/(double)nDraws<<std::endl;
        }
        a.GenerateSpherePoints();
        auto b = a.Eat();
        bites[b]++;
    }

    double expected_bites = 0;
    for (int i = 0; i < 10000; i++) {
        std::cout<<i<<", "<<bites[i]<<std::endl;
        expected_bites+=i*bites[i]/(double)nDraws;
    }

    std::cout<<expected_bites<<std::endl;
    return 0;
}
