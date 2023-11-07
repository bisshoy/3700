#include <iostream>
#include <fstream>
#include "queue.h"
#include "linearlist.h"

using namespace std;

struct word { 
	int parent; 
	string name; 
	LinearList<int> list; 
};

const int SGB_SIZE = 5757;

// Master list of all words from file turned into structs
// Don't need file after this is populated 
word MasterList[SGB_SIZE];

void genLadder   (int, int); 
int  hammingDist (string, string); 
int  searchList  (string);
void populateML	 (void); 
void findNearby	 (int); 

int main() {
	int w1_idx, w2_idx;
	string s1, s2;

	// Populate MasterList so that we don't have 
	// to use sgb-words.txt 
	populateML();
	// From this point on, we can just address 
	// MasterList 

	// For each word in MasterList, populate its "list"
	// variable with 
	for (int i = 0; i < SGB_SIZE; i++) {
		findNearby(i);
	}

	// Input w1 and w2
	cout << "What two words?" << endl;
	cin >> s1 >> s2;

	w1_idx = searchList(s1);
	w2_idx = searchList(s2);

	// Check if words are in list 
	if (w1_idx == -1) {
		cout << "Error: first word not in list" << endl;
		return 0;
	} 

	if (w2_idx == -1) {
		cout << "Error: second word not in list" << endl;
		return 0;
	} 

	cout << endl;
	// Generate Word Ladder 
	genLadder(w1_idx, w2_idx);

	return 0;

}

void genLadder(int w1, int w2) {
	// Contains indicies of words with Hamming Distance of 1 
	// from the input word  
	Queue<int> Q;
	int w;
	int v;

	// Add w2 to a queue Q
	Q.enqueue(w2);

	// while Q is not empty do 
	while (!Q.isEmpty()) {

		// dequeue Q into w
		w = Q.dequeue();

		// for each word v in w.list do
		for (int i = 0; i < MasterList[w].list.size(); i++) {
			v = MasterList[w].list[i];
			// if v.ptr = NULL and v != w2 then 
			if (MasterList[v].parent == -1 && v != w2) {

				// v.ptr = w
				MasterList[v].parent = w;

				// enqueue v in Q
				Q.enqueue(v);


			} // end if 
		} // end for 
	} // end while 

	// if w1.ptr != NULL then 
	if (MasterList[w1].parent != -1) {
		
		cout << "Ladder:" << endl;
		// output w1
		cout << MasterList[w1].name << endl;

		// w = w1.ptr
		w = MasterList[w1].parent;

		// while w != NULL do
		while (w != -1) {

			// output w
			cout << MasterList[w].name << endl;

			// w = w.ptr 
			w = MasterList[w].parent; 

		} // end while 
	
	} else {
		// No ladder exists 
		cout << "No ladder exists." << endl;
	}

} // end procedure 

// Returns Hamming Distance between two words 
int hammingDist(string s1, string s2) {
	int i = 0; 
	int dist = 0; 

	while (s1[i] && s2[i]) {
		if (s1[i] != s2[i]) {
			dist++;
		}

		i++;
	}

	return dist;
}

// Given a key, return the position of that key 
// in the MasterList 
int searchList(string key) {

	for (int i = 0; i < SGB_SIZE; i++) {
		if (MasterList[i].name == key) {
			return i;
		}
	}

	return -1;

}

// Fill MasterList with each word in the sgb-words.txt file 
void populateML(void) {
	ifstream myfile;
	string line;

	// Open sgb-words.txt 
	myfile.open("sgb-words.txt");

	// In case of error opening 
	if (!myfile.is_open()) {
		perror("Error opening!");
		exit(EXIT_FAILURE);
	} 

	// For every word in sgb-words.txt, 
	// fill each index of MasterList with
	// the appropriate data 
	int i = 0;
	while (getline(myfile, line)) {
		MasterList[i].name = line;
		MasterList[i].parent = -1;
		i++;
	}

	myfile.close();

}

// Find all words in the MasterList with a Hamming Distance 
// of 1 from the input word, then add those words' indicies
// to the "list" variable of 
void findNearby(int w) {

	for (int i = w + 1; i < SGB_SIZE; i++) {
		if (hammingDist(MasterList[i].name, MasterList[w].name) == 1) {
			MasterList[w].list.insert(0, i);
			MasterList[i].list.insert(0, w);
		}
	}
}

