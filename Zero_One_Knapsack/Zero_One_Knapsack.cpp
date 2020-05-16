#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>   

using namespace std;

void Zero_One_Knapsack(int, int, vector<int>, vector<int>, vector<vector<bool>>&, int&);

int main() {

	/*=====Read Input File=====*/
	ifstream ReadFile("input.txt", ios::in);
	//check if file exists
	if (!ReadFile.is_open()) {
		cerr << "Input File not found.";
		exit(1);
	}

	int n = 0; //#of items
	int max_weight = 0; //maximum weight

	ReadFile >> n; 
	ReadFile >> max_weight;

	vector<int> value; //value of each item
	vector<int> weight; //weight of each item
	for (int i = 0; i < n; i++) { //read items
		int v, w;
		ReadFile >> v >> w;
		value.push_back(v);
		weight.push_back(w);
	}
	
	/*=====0-1Knapsack=====*/
	int total_revenue = 0; //record the maximum total revenue
	vector<vector<bool>> choice(n, vector<bool>(max_weight + 1)); //record items to select during dynamic programming
	Zero_One_Knapsack(n, max_weight, value, weight, choice, total_revenue);
	
	/*=====Write Output File=====*/
	ofstream WriteFile("output.txt", ios::out | ios::trunc);
	//check if file exists
	if (!WriteFile.is_open()) {
		cerr << "Output File not found.";
		exit(1);
	}

	WriteFile << "Total revenue = " << total_revenue << "\n";
	WriteFile << "Selected item: ";
	for (int i = n - 1, j = max_weight; i >= 0; i--) { //at weight j, check if item i is selected
		//p.s. start from j = maximum weight, and check if i = the last item is selected

		if (choice[i][j]) { //at weight j, if item i is selected
			WriteFile << i+1 << " "; //write item i into file(true index is i+1)
			j -= weight[i]; //subtract the weight of item i from j and check for the next item
		}
	}

	return 0;
}

void Zero_One_Knapsack(int n, int max_weight, vector<int> value, vector<int> weight, vector<vector<bool>> &choice, int &total_revenue) {
	
	vector<int> revenue(max_weight + 1, 0); //record the revenue at each possible weight

	for (int i = 0; i < n; i++) {
		for (int j = max_weight; j - weight[i] >= 0; j--) { //starting from the maximum weight
			int new_max_value = revenue[j - weight[i]] + value[i]; //the new revenue if item i is selected
			if (new_max_value > revenue[j]) { //the new revenue is greater than not the revenue without item i
				revenue[j] = new_max_value; //update new revenue
				choice[i][j] = true; //mark item i true at this particular weight
			}
		}
	}
	
	total_revenue = revenue[max_weight]; //the total revenue is the revenue when weight is maximized
}