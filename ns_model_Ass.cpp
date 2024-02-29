#include <iostream>
#include <vector>
#include <random>

using namespace std;

const int road_length = 100;
const int num_lanes = 2;
const int v_max = 5;
const double p_slowdown = 0.3;


void updateRoad(vector<vector<int>>& road) {
    for (int lane = 0; lane < num_lanes; ++lane) {
        for (int i = 0; i < road_length; ++i) {
            
            if (road[lane][i] < v_max) {
                ++road[lane][i];
            }
            
          
            for (int d = 1; d <= road[lane][i]; ++d) {
                if (road[(lane + 1) % num_lanes][(i + d) % road_length] > 0) {
                    road[lane][i] = min(road[lane][i], d - 1);
                    break;
                }
            }
            
            
            if (static_cast<double>(rand()) / RAND_MAX < p_slowdown && road[lane][i] > 0) {
                --road[lane][i];
            }
            
            
            if (road[lane][i] > 0) {
                road[(lane + 1) % num_lanes][(i + road[lane][i]) % road_length] = road[lane][i];
                road[lane][i] = 0;
            }
        }
    }
}


void displayRoad(const vector<vector<int>>& road) {
    for (int lane = 0; lane < num_lanes; ++lane) {
        cout << "Lane " << lane + 1 << ": ";
        for (int cell : road[lane]) {
            if (cell == 0) {
                cout << ". ";
            } else {
                cout << cell << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    
    vector<vector<int>> road(num_lanes, vector<int>(road_length, 0));
    
    
    const int num_steps = 50;
    for (int step = 0; step < num_steps; ++step) {
        cout << "step " << step + 1 << endl;
        updateRoad(road);
        displayRoad(road);
    }
    
    return 0;
}
