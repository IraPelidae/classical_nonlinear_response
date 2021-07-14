#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "random_wrapper.h"

#define N 5
void init_velocities();
void init_positions();
std::vector<double> x(N); // Store the left extrema of all rods. It should remain sorted at all times
std::vector<double> v(N); // Store the velocity of all the rods (stored in the same order as x).
double sys_time;

const double T = 1; //temperature
const double L = 100; //length of the system
const double rod_length = 0.1;


random_wrapper rand_num_gen;

void init_velocities();
void init_positions();
std::pair<double, int> min_collision_time(std::vector<double> x, std::vector<double> v);
void next_collision(int no_collisions);


int main(int argc, char** argv) {

    init_positions();
    init_velocities();

      
    next_collision(5);


}

void init_velocities() {

    std::cout << "\nDisplaying velocities: ";
    
    for (int i = 0; i < N; i++) {
        v[i] = rand_num_gen.gaussian(T);
        std::cout << v[i] << " "; 
    }
    std::cout << "\n_________________________________";
}

void init_positions() {
    
    for (int i = 0; i < N; i++) {
        x[i] = rand_num_gen.uniform(0, L - N * rod_length); // need to improve this - rods are less likely to populate near the RH wall?
        
    }

    std::sort(x.begin(), x.end());

    
    std::cout << "\n\nDisplaying positions: ";
    for (int i = 0; i < N; i++) {
        x[i] += rod_length * i; // Make sure that none of the rods are overlapping
        std::cout << x[i] << " "; 
    }
    
}

std::pair<double,int> min_collision_time(std::vector<double> x, std::vector<double> v) {

    std::vector<double> times = {};
    std::vector<double> indices = {};
    
    for (int i = 0; i < N; i++) {
        if (i == 0 && v[0] < 0) {
            //does rod[0] collide with LH wall or rod[1]
            times.push_back(-1 * x[0] / v[0]);
            indices.push_back(-1); // index -1 means that rod[0] collides with wall
            if (v[0] > v[1]) {
                times.push_back((x[i + 1] - (x[i] + rod_length)) / (v[i] - v[i + 1]));
                indices.push_back(i);
            }
        }
        else if (i < N - 1 && v[i] > v[i + 1]) {
            //Check if collision occurs between x[i] and rod i+1 for 0 < i < N-1
            times.push_back((x[i + 1] - (x[i] + rod_length)) / (v[i] - v[i + 1]));
            indices.push_back(i);
        }

        else if (i == N - 1 && v[N - 1] > 0) {
            //does rod[N-1] collide with RH wall
            times.push_back((L - (x[N - 1] + rod_length)) / v[N - 1]);
            indices.push_back(i);
        }
    }
        double min_time = *std::min_element(times.begin(), times.end());

    int min_time_index = indices[std::distance(times.begin(), std::min_element(times.begin(), times.end()))];

    

    std::cout << "\n\nDisplaying coll_index: ";

    for (int i = 0; i < indices.size(); i++) {
            std::cout << indices[i] << " ";
    }
    std::cout << "\nDisplaying coll_times: ";

    for (int i = 0; i < times.size(); i++) {
        std::cout << times[i] << " ";
    }

    std::cout << "\n\nDisplaying min_time: " << min_time;
    std::cout << "\nDisplaying min_time_index: " << min_time_index;
    
    return std::make_pair(min_time, min_time_index);   

    }

    
void next_collision(int no_collisions) {
    for (int i = 0; i < no_collisions; i++) {

        

        auto mct = min_collision_time(x, v);
        double min_time = mct.first;
        int min_time_index = mct.second;

        sys_time += min_time;

        for (int j = 0; j < N; j++) {
            x[j] += v[j] * min_time; //Update positions
        }

        //Updating velocities
        if (min_time_index == -1) {
            v[0] = -1 * v[0];
        }
        else if (min_time_index == N-1) {
            v[N - 1] = -1 * v[N - 1];


        }
        else if (min_time_index < N-1) {

            // if a rod collies with a rod

            std::iter_swap(v.begin() + min_time_index, v.begin() + min_time_index+1); //swap v[j] and v[j+1]

        }
        
        std::cout << "\n\nAfter collision " << i+1;
        std::cout << "\nTime Elapsed: " << sys_time;
        std::cout << "\n\nDisplaying positions: ";
        for (int i = 0; i < N; i++) {
            std::cout << x[i] << " ";
        }
        std::cout << "\nDisplaying velocities: ";

        for (int i = 0; i < N; i++) {
            std::cout << v[i] << " ";
        }
        std::cout << "\n_________________________________";
        
    }

    
}