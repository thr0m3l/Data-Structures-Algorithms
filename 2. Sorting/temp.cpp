#include <iostream>
#include <random>
using namespace std;
int main()
{
    // std::random_device rd; // obtain a random number from hardware
    // std::mt19937 eng(rd()); // seed the generator
    // std::uniform_int_distribution<> distr(25, 63); // define the range
	int max, min;
    cin>>max>>min;
    for(int n=0; n<40; ++n)
        // std::cout << distr(eng) << ' '; // generate numbers
        cout<< (long)(((double) rand() / (RAND_MAX+1)) * (max-min+1) + min)<<endl;
}