#include <iostream>
#include<map>
#include<vector>
#include<iterator>
#include<string>
#include<iomanip>
using namespace std;

class Adjancency_List{
private:
    // class maps
    map<string, vector<pair<string,float>>> website_list_out; // stores the vertex and maps it to the vertices that point to it along with the outdegree
    map<string, vector<string>> website_list_visual; // stores the vertex and connects it to the proper vertices.
public:
    int outdegree_calculator(string from){
        return website_list_visual[from].size(); // grabs the size of the vector, which represents the outdegree of a node.
    }

    void print_websitesWRanks(map<string, float> website_rank){
        for (auto &website_rankLIST : website_rank){
            cout << website_rankLIST.first << " " << fixed << setprecision(2) << website_rankLIST.second << endl; // prints out the website in alphabetical order and the corresponding rank
        }
    }

    void outdegree_updater(){ // calculates the 1 divided the outdegree for each vertex
        for (auto &website : website_list_out){ // Iterates through each vertex
            for (auto &pairs: website.second) { // Iterates through all the vertices stored in each vertex
                string from = pairs.first;
                float out_degree = 1.00/outdegree_calculator(from); // calculates and updates the 1 divided by the outdegree.
                pairs.second = out_degree;
            }
        }
    }

    void Insert(string from, string to){
        website_list_visual[from].push_back(to); // adds to vertex to the map
        if (website_list_visual.find(to)==website_list_visual.end()){
            website_list_visual[to] = {}; // creates the vertex if it doesn't exist
        }
        float out_degree = 1.00/outdegree_calculator(from);
        website_list_out[to].push_back(make_pair(from,out_degree)); // adds the vertex and outdegree to the adjacency list that represent the matrix
        if (website_list_out.find(from)==website_list_out.end()){
            website_list_out[from] = {}; // creates the vertex if it doesn't exist
        }
        outdegree_updater(); // updates the outdegree of each vertex after each insertion
    }

    void ranks_creator(map<string, float> &website_rank){ // takes in an empty map and adds the starting rank to all the vertexes
        for (auto &website : website_list_visual){
            float starting_rank = (1.00/website_list_visual.size());
            website_rank[website.first] = starting_rank;
        }
    }

    void PageRank(int poweriterations){ // goes through the matrices math
        map<string, float> website_rank; // creates a map with the starting rank based off of the amount of vertexes
        ranks_creator(website_rank);
        if(poweriterations - 1 > 0){
            for(int i = 0; i < poweriterations - 1; i++) {
                map<string, float> website_rank_temp = website_rank; // create a temporary map with all the ranks that will be used in the matrices math
                for (auto &website : website_list_out){ // loop through the vectors that each vertex holds
                    float temp_rank = 0.00;
                    for (int j = 0; j < website.second.size(); j++){
                        temp_rank += website.second.at(j).second * website_rank_temp[website.second.at(j).first]; // multiply by each correlating vertex
                    }
                    website_rank[website.first] = temp_rank; // set the rank to what was just calculated
                }
            }
        }
        print_websitesWRanks(website_rank); // calls the print function to print
    }
};

int main() {
    Adjancency_List T;
    int num_lines; // grabs input
    cin>>num_lines;
    int power_iterations;
    cin>>power_iterations;
    for(int i = 0; i < num_lines; i++){
        string from;
        cin>>from;
        string to;
        cin>>to;
        T.Insert(from,to); // calls the insert function to add all the vertices and edges
    }
    T.PageRank(power_iterations); // calls the PageRank function to conduct matrix math p - 1 amount of times and print out the websites and corresponding rank
    return 0;
}
