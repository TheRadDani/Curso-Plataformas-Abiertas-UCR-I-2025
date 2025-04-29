#include <iostream>
#include <cstring>
#include <memory>

using namespace std;

float sum(float a, float b) {
    return (float)(a + b);
}

int main() {
    float result = sum(7.1f, 1.2f);
    cout << result <<endl;
    return 0;
}