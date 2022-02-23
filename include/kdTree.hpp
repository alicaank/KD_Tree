

#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <stdlib.h>


struct node {
            std::vector<double> point;
            std::shared_ptr<node> left;
            std::shared_ptr<node> right;
            node(std::vector<double> point) : point(point), left(nullptr), right(nullptr) {}
        };


class kdTree {

    private:
        
        std::shared_ptr<node> root;

    public:
        kdTree() : root(nullptr) {}


        void build(std::vector<std::vector<double>> points) {
           
            root = buildTree(points, 0);
        }

        std::shared_ptr<node> buildTree(std::vector<std::vector<double>> points, int depth) {
            if (points.size() == 0) {
                return nullptr;
            }
            int median = 0;
            std::shared_ptr<node> n = std::make_shared<node>(points[median]);
            std::vector<std::vector<double>> leftPoints;
            std::vector<std::vector<double>> rightPoints;
            for (int i = 1; i < points.size(); i++) {
                if (i != median) {
              
                    if (points[i][depth % points[i].size()] < points[median][depth % points[median].size()]) {
                        leftPoints.push_back(points[i]);
                    } else {
                        rightPoints.push_back(points[i]);
                    }
                }
            }
            n->left = buildTree(leftPoints, depth + 1);
            n->right = buildTree(rightPoints, depth + 1);
            return n;
        }

        void insert(std::vector<double> point) {
           if(root == nullptr) {
               root = std::make_shared<node>(point);
           } else {
               insert(root, point, 0);
           }
        }

        void insert(std::shared_ptr<node> n, std::vector<double> point, int depth) {
            if(n->point == point) {
                return;
            }

            int cd = depth % point.size();

            if(point[cd] < n->point[cd]) {
                if(n->left == nullptr) {
                    n->left = std::make_shared<node>(point);
                } else {
                    insert(n->left, point, depth + 1);
                }
            } else {
                if(n->right == nullptr) {
                    n->right = std::make_shared<node>(point);
                } else {
                    insert(n->right, point, depth + 1);
                }
            }
        }
        void print() {
            print(root, 0);
        }
        void print(std::shared_ptr<node> n, int depth) {
            if(n == nullptr) {
                return;
            }
           
            print(n->right, depth + 1);
            for(int i = 0; i < depth; i++) {
                std::cout << "  ";
            }
          //  std::cout << "Dept: " << depth << " ";
            std::cout << n->point[depth % n->point.size()] << std::endl;
            print(n->left, depth + 1);
        }
        void search(std::vector<double> point) {
            search(root, point, 0);
        }
        void search(std::shared_ptr<node> n, std::vector<double> point, int depth) {
            if(n == nullptr) {
                std::cout << "Not found" << std::endl;
                return;
            }
            else{
                if(n->point==point){
                    std::cout<<"found at"<<std::endl;
                }
                else{
                    int cd = depth % point.size();
                    if(point[cd] < n->point[cd]) {
                        search(n->left, point, depth + 1);
                    } else {
                        search(n->right, point, depth + 1);
                    }
                }

            }
            
        }
        void deleteNode(std::vector<double> point) {
            deleteNode(root, point, 0);
        }
        void deleteNode(std::shared_ptr<node> n, std::vector<double> point, int depth) {
            if(n == nullptr) {
                return;
            }
            else{
                if(n->point==point){
                    if(n->left==nullptr && n->right==nullptr){
                        n=nullptr;
                    }
                    else if(n->left==nullptr){
                        n=n->right;
                    }
                    else if(n->right==nullptr){
                        n=n->left;
                    }
                    else{
                        std::shared_ptr<node> temp=n->right;
                        while(temp->left!=nullptr){
                            temp=temp->left;
                        }
                        n->point=temp->point;
                        deleteNode(n->right,temp->point,depth+1);
                    }
                }
                else{
                    int cd = depth % point.size();
                    if(point[cd] < n->point[cd]) {
                        deleteNode(n->left, point, depth + 1);
                    } else {
                        deleteNode(n->right, point, depth + 1);
                    }
                }
            }
        }
        
        
        //TODO
        // Implement the k-nearest-neighbors search
        // Implement the range search
        // Implement the radius search

       
};