#include <iostream>
#include <vector>

int main()
{
    int n{0};
    std::cin >> n;
    std::vector<int>FUCK (n , 6);
    for (const auto &i : FUCK)
    {
        std::cout << i << '\t';
    }
    return 0;
}