#include "kdTree.hpp"

int main(){
    kdTree tree;
    std::vector<double> point1 = {4, 2};
    std::vector<double> point2 = {2, 5};
    std::vector<double> point3 = {3, 1};
    std::vector<double> point4 = {4, 3};
    std::vector<double> point5 = {2, 4};
    std::vector<double> point6 = {6,6};
    
    tree.build({ point3, point4, point5, point6});
    tree.print();
    tree.rangeSearch(point1, point2);
    return 0;
}