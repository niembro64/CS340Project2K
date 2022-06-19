// CS340 Program2
// Eric Niemeyer
// Dr. Matta
// Fall 2018

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <assert.h>
//#include <time.h>
#include <chrono>
#include <sys/timeb.h>
#include <cstdlib>

using namespace std;

std::chrono::steady_clock::time_point start;

long double clock(std::chrono::steady_clock::time_point start) {
	std::chrono::steady_clock::time_point end = chrono::high_resolution_clock::now();
	long double time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

	return time;
}


char choice;

struct bst_node;
struct rbt_node;

#define str_ptr string*
#define bst_node_ptr bst_node*
#define rbt_node_ptr rbt_node*


string tree_type;
string multiples_of_fifteen[10] = { "15","30","45","60","75","90","105","120","135","150"};


string filename_in = "sorted15K.txt";
string path = "C:/Users/secpc/Desktop/wordlists/";

string filename_out = "AAA_out.txt";

bool print_stuff = false;
int printResolution = 2;

typedef string key_type;
typedef char color_type;



bst_node* bst_searchPrintTree(bst_node* p, key_type a, bool printstuff);
rbt_node* rbt_searchPrintTree(rbt_node* p, key_type a, bool printstuff);


//long int shortPauseTime = 100000000;
long int longPauseTime = 100000000;



//////////////////////////////////////////////////////
///////////// NODE STRUCTS 
//////////////////////////////////////////////////////


key_type DEFAULT_VALUE = "DEFAULT*******";
color_type DEFAULT_COLOR = 'x';

struct bst_node {
	key_type key = DEFAULT_VALUE;
	bst_node* parent = nullptr;
	bst_node* left = nullptr;
	bst_node* right = nullptr;
};

struct rbt_node {
	key_type key = DEFAULT_VALUE;
	color_type color = DEFAULT_COLOR;
	rbt_node* parent = nullptr;
	rbt_node* left = nullptr;
	rbt_node* right = nullptr;
};

//////////////////////////////////////////////////////
///////////// SIMPLE FUNCTIONS 
//////////////////////////////////////////////////////
/*
void niemShortPause() {
for (int i = 0; i < shortPauseTime; i++);
}
*/
void niemLongPause() {
	int i = 0;
	while (i < longPauseTime) {
		i++;
	}
}
bool alphabetical(string a, string b) {
	bool truth;

	// AAA.compare(BBB) = -1
	// AAA.compare(AAA) = 0
	// BBB.compare(AAA) = 1
	
	if (a.compare(b) >= 0) {
		truth = false;
	}
	else {
		truth = true;
	}
	return truth;
}
bool isWord(string a) {
	//return (alphabetical(a, "AAAAAAAAAAAAAAA") || alphabetical("ZZZZZZZZZZZ", a));
	return (alphabetical("A", a) && alphabetical(a, "ZZZZZZZZZZZZZZZZZZZ"));
}
void line() {
	cout << "----------------------------------------" << endl;
}
void line(bool printStuff) {
	if (printStuff)
	cout << "----------------------------------------" << endl;
}
int printTimesScreen(string tree_type, string f, int searches, long double duration_construct, long double duration_insert_key_AVERAGE, long double duration_insert_key_WORST, long double duration_search_AVERAGE, long double duration_search_WORST, long double duration_time_extra) {

	cout << "File Used: " << f << endl;
	cout << "Tree Type: " << tree_type << endl;
	cout << "             CONSTRUCT: ";
	cout.width(15);
	cout << right << fixed << setprecision(printResolution) << duration_construct << " ns" << endl;
	cout << "        AVERAGE INSERT: ";
	cout.width(15);
	cout << right << fixed << setprecision(printResolution) << duration_insert_key_AVERAGE << " ns" << endl;
	cout << "          WORST INSERT: ";
	cout.width(15);
	cout << right << fixed << setprecision(printResolution) << duration_insert_key_WORST << " ns" << endl;
	cout << " AVERAGE SEARCH (of " << searches << "): ";
	cout.width(15);
	cout << right << fixed << setprecision(printResolution) << duration_search_AVERAGE << " ns" << endl;
	cout << "   WORST SEARCH (of " << searches << "): ";
	cout.width(15);
	cout << right << fixed << setprecision(printResolution) << duration_search_WORST << " ns" << endl;
	cout << "          RANDO SEARCH: ";
	cout.width(15);
	cout << right << fixed << setprecision(printResolution) << duration_time_extra << " ns" << endl;

	return 0;
}
int printTimesFile(ofstream &fout, string tree_type, string f_out, string f_in, int searches, long double duration_construct, long double duration_insert_key_AVERAGE, long double duration_insert_key_WORST, long double duration_search_AVERAGE, long double duration_search_WORST, long double duration_time_extra) {


	fout << "File Used: " << f_in << endl;
	fout << "Tree Type: " << tree_type << endl;

	fout << "             CONSTRUCT: ";
	fout.width(15);
	fout << right << fixed << setprecision(printResolution) << duration_construct << " ns" << endl;
	fout << "        AVERAGE INSERT: ";
	fout.width(15);
	fout << right << fixed << setprecision(printResolution) << duration_insert_key_AVERAGE << " ns" << endl;
	fout << "          WORST INSERT: ";
	fout.width(15);
	fout << right << fixed << setprecision(printResolution) << duration_insert_key_WORST << " ns" << endl;
	//fout << "AVERAGE SEARCH (of " << searches << "): ";
	//fout.width(15);
	//fout << right << fixed << setprecision(printResolution) << duration_search_AVERAGE << " ns" << endl;
	fout << "  WORST SEARCH (of " << searches << "): ";
	fout.width(15);
	fout << right << fixed << setprecision(printResolution) << duration_search_WORST << " ns" << endl;
	fout << "  RANDO SEARCH     " << searches << "): ";
	fout.width(15);
	fout << right << fixed << setprecision(printResolution) << duration_time_extra << " ns" << endl;
	fout << "---------------------------------------------" << endl;


	return 0;
}

//////////////////////////////////////////////////////

///////////// CLASS

//////////////////////////////////////////////////////


class Tree {
private:
public:
	void line() {
		cout << "----------------------------------------" << endl;
	}
	void line(bool printStuff) {
		if (printStuff)
			cout << "----------------------------------------" << endl;
	}
	int printTimesScreen(string tree_type, string f, int searches, long double duration_construct, long double duration_insert_key_AVERAGE, long double duration_insert_key_WORST, long double duration_search_AVERAGE, long double duration_search_WORST, long double duration_time_extra) {

		cout << "File Used: " << f << endl;
		cout << "Tree Type: " << tree_type << endl;
		cout << "             CONSTRUCT: ";
		cout.width(15);
		cout << right << fixed << setprecision(printResolution) << duration_construct << " ns" << endl;
		cout << "        AVERAGE INSERT: ";
		cout.width(15);
		cout << right << fixed << setprecision(printResolution) << duration_insert_key_AVERAGE << " ns" << endl;
		cout << "          WORST INSERT: ";
		cout.width(15);
		cout << right << fixed << setprecision(printResolution) << duration_insert_key_WORST << " ns" << endl;
		cout << " AVERAGE SEARCH (of " << searches << "): ";
		cout.width(15);
		cout << right << fixed << setprecision(printResolution) << duration_search_AVERAGE << " ns" << endl;
		cout << "   WORST SEARCH (of " << searches << "): ";
		cout.width(15);
		cout << right << fixed << setprecision(printResolution) << duration_search_WORST << " ns" << endl;
		cout << "          RANDO SEARCH: ";
		cout.width(15);
		cout << right << fixed << setprecision(printResolution) << duration_time_extra << " ns" << endl;

		return 0;
	}
	int printTimesFile(ofstream &fout, string tree_type, string f_out, string f_in, int searches, long double duration_construct, long double duration_insert_key_AVERAGE, long double duration_insert_key_WORST, long double duration_search_AVERAGE, long double duration_search_WORST, long double duration_time_extra) {


		fout << "File Used: " << f_in << endl;
		fout << "Tree Type: " << tree_type << endl;

		fout << "             CONSTRUCT: ";
		fout.width(15);
		fout << right << fixed << setprecision(printResolution) << duration_construct << " ns" << endl;
		fout << "        AVERAGE INSERT: ";
		fout.width(15);
		fout << right << fixed << setprecision(printResolution) << duration_insert_key_AVERAGE << " ns" << endl;
		fout << "          WORST INSERT: ";
		fout.width(15);
		fout << right << fixed << setprecision(printResolution) << duration_insert_key_WORST << " ns" << endl;
		//fout << "AVERAGE SEARCH (of " << searches << "): ";
		//fout.width(15);
		//fout << right << fixed << setprecision(printResolution) << duration_search_AVERAGE << " ns" << endl;
		fout << "  WORST SEARCH (of " << searches << "): ";
		fout.width(15);
		fout << right << fixed << setprecision(printResolution) << duration_search_WORST << " ns" << endl;
		fout << "  RANDO SEARCH     " << searches << "): ";
		fout.width(15);
		fout << right << fixed << setprecision(printResolution) << duration_time_extra << " ns" << endl;
		fout << "---------------------------------------------" << endl;


		return 0;
	}

};

class BST : public Tree {
private:
	bst_node root;
public:
	bst_node* bst_printSearchPath(
		bst_node* p,
		key_type a,
		long double* start_time_search_WORST,
		long double* end_time_search_WORST,
		long double* duration_search_WORST,
		long double* start_time_search_AVERAGE,
		long double* end_time_search_AVERAGE,
		long double* duration_search_AVERAGE,
		long double* start_time_extra,
		long double* end_time_extra,
		long double* duration_time_extra,
		bool printstuff) {
		if (printstuff) {
			cout << a << " SEARCH PATH: " << endl;
		}
		bst_node* p2;
		*start_time_extra = *start_time_search_AVERAGE = *start_time_search_WORST = clock(start);
		p2 = bst_searchPrintTree(p, a, printstuff);
		*end_time_extra = *end_time_search_AVERAGE = *end_time_search_WORST = clock(start);
		*duration_search_AVERAGE += (*end_time_search_AVERAGE - *start_time_search_AVERAGE);
		if (*duration_search_WORST <
			(*end_time_search_WORST - *start_time_search_WORST)) {
			*duration_search_WORST =
				(*end_time_search_WORST - *start_time_search_WORST);
		}
		*duration_time_extra = (*end_time_extra - *start_time_extra);
		return p2;
	}
	int bst_printFound(string a, bst_node* p) {
		cout << a << " Found?: " << " "
			<< ((p == nullptr) ? "nullptr" : p->key) << endl;
		return 0;
	}
	bst_node* bst_insert(bst_node* root, key_type a) {

		if (root == nullptr) {
			bst_node* p = new bst_node;
			p->key = a;
			p->left = nullptr;
			p->right = nullptr;
			return p;
		}

		if (alphabetical(root->key, a)) {
			root->right = bst_insert(root->right, a);
		}
		else {
			root->left = bst_insert(root->left, a);
		}

		return root;
	}
	int bst_printInOrder(bst_node* p, bool printstuff) {
		if (p == nullptr) {
			return 0;
		}
		bst_printInOrder(p->left, printstuff);
		if (printstuff) {
			cout << "                 ";
			cout << p->key << endl;
		}
		bst_printInOrder(p->right, printstuff);

		return 0;
	}
	bst_node* bst_searchPrintTree(bst_node* p, key_type a, bool printstuff) {
		if (printstuff) {
			cout << "                 ";
			cout << ((p == nullptr) ? "nullptr" : p->key) << endl;
		}
		bst_node* p2 = nullptr;

		// base case not found and leaf
		if (p == nullptr) return nullptr;
		// base case found
		if (p->key == a) return p;

		// general case not found
		if (alphabetical(p->key, a)) p2 = bst_searchPrintTree(p->right, a, printstuff);
		if (alphabetical(a, p->key)) p2 = bst_searchPrintTree(p->left, a, printstuff);

		return p2;
	}
	bst_node* bst_searchTree(bst_node* p, key_type a) {

		bst_node* p2 = nullptr;

		// base case not found and leaf
		if (p == nullptr) return nullptr;
		// base case found
		if (p->key == a) return p;

		// general case not found
		if (alphabetical(p->key, a)) p2 = bst_searchTree(p->right, a);
		if (alphabetical(a, p->key)) p2 = bst_searchTree(p->left, a);

		return p2;
	}
	int bst_makeTree(
		string filename_and_path_in,
		bst_node* p,
		long double* start_time_construct,
		long double* end_time_construct,
		long double* duration_construct,
		long double* start_time_insert_key_WORST,
		long double* end_time_insert_key_WORST,
		long double* duration_insert_key_WORST,
		long double* start_time_insert_key_AVERAGE,
		long double* end_time_insert_key_AVERAGE,
		long double* duration_insert_key_AVERAGE,
		bool printstuff) {

		key_type temp_string;
		ifstream infile;

		*start_time_construct = clock(start);
		infile.open(filename_and_path_in);
		if (infile.fail()) {
			cout << "***** BAD FILENAME *****\n\n";
			system("pause");
		}

		line();

		if (print_stuff) { cout << "Print while inserting: " << endl; }
		else { //cout << "Don't print while inserting: " << endl; 
		}

		// get root
		getline(infile, temp_string);
		p->key = temp_string;
		if (print_stuff) {
			cout << "                 ";
			cout << temp_string << endl;
		}

		int num_of_nodes = 1;
		while (!infile.eof()) {
			num_of_nodes++;
			getline(infile, temp_string);
			// don't add if not word, i.e. " "
			if (!isWord(temp_string)) {
				num_of_nodes--;
				//cout << "space" << endl;
			}
			else {
				if (print_stuff) {
					cout << "                 ";
					cout << temp_string << endl;
				}
				*start_time_insert_key_WORST = clock(start);
				*start_time_insert_key_AVERAGE = clock(start);
				bst_insert(p, temp_string);
				*end_time_insert_key_WORST = clock(start);
				*end_time_insert_key_AVERAGE = clock(start);
				*duration_insert_key_AVERAGE += ((*end_time_insert_key_AVERAGE) - (*start_time_insert_key_AVERAGE));
				if (*duration_insert_key_WORST <
					(*end_time_insert_key_WORST - *start_time_insert_key_WORST)) {
					*duration_insert_key_WORST = ((*end_time_insert_key_WORST) - (*start_time_insert_key_WORST));
				}
			}
		}
		(*duration_insert_key_AVERAGE) = ((*duration_insert_key_AVERAGE) / num_of_nodes);
		infile.close();
		*end_time_construct = clock(start);
		*duration_construct = *end_time_construct - *start_time_construct;

		return 0;
	}


};

class RBT : public Tree {
private:
	rbt_node root;
public:
	void leftrotate(rbt_node *p, rbt_node* root)
	{
		if (p->right == nullptr)
			return;
		else
		{
			rbt_node *y = p->right;
			if (y->left != nullptr)
			{
				p->right = y->left;
				y->left->parent = p;
			}
			else
				p->right = nullptr;
			if (p->parent != nullptr)
				y->parent = p->parent;
			if (p->parent == nullptr)
				root = y;
			else
			{
				if (p == p->parent->left)
					p->parent->left = y;
				else
					p->parent->right = y;
			}
			y->left = p;
			p->parent = y;
		}
	}
	void rightrotate(rbt_node *p, rbt_node* root)
	{
		if (p->left == nullptr)
			return;
		else
		{
			rbt_node *y = p->left;
			if (y->right != nullptr)
			{
				p->left = y->right;
				y->right->parent = p;
			}
			else
				p->left = nullptr;
			if (p->parent != nullptr)
				y->parent = p->parent;
			if (p->parent == nullptr)
				root = y;
			else
			{
				if (p == p->parent->left)
					p->parent->left = y;
				else
					p->parent->right = y;
			}
			y->right = p;
			p->parent = y;
		}
	}
	rbt_node* insertfix_1(rbt_node *t, rbt_node* root)
	{
		rbt_node *u;
		if (root == t)
		{
			t->color = 'b';
			return root;
		}
		while (t->parent != nullptr && t->parent->color == 'r')
		{
			rbt_node *g = t->parent->parent;
			if (g->left == t->parent)
			{
				if (g->right != nullptr)
				{
					u = g->right;
					if (u->color == 'r')
					{
						t->parent->color = 'b';
						u->color = 'b';
						g->color = 'r';
						t = g;
					}
				}
				else
				{
					if (t->parent->right == t)
					{
						t = t->parent;
						leftrotate(t, root);
					}
					t->parent->color = 'b';
					g->color = 'r';
					rightrotate(g, root);
				}
			}
			else
			{
				if (g->left != nullptr)
				{
					u = g->left;
					if (u->color == 'r')
					{
						t->parent->color = 'b';
						u->color = 'b';
						g->color = 'r';
						t = g;
					}
				}
				else
				{
					if (t->parent->left == t)
					{
						t = t->parent;
						rightrotate(t, root);
					}
					t->parent->color = 'b';
					g->color = 'r';
					leftrotate(g, root);
				}
			}
			root->color = 'b';
		}
		// finding root
		while (root->parent != nullptr) {
			root = root->parent;
		}

		return root;
	}
	rbt_node* insertfix(rbt_node* z, rbt_node* root)
	{
		if (z->parent != NULL && z->parent->parent != NULL)
		{
			while (z != NULL && z->parent != NULL &&
				z->parent->parent != NULL && !z->parent->color == 'b')
				// ass long as color is not black, thus red
			{
				if (z->parent == z->parent->parent->left)
				{
					rbt_node *y = z->parent->parent->right;
					if (y != NULL && y->color == 'r')
					{
						z->parent->color = 'b';
						y->color = 'b';
						z->parent->parent->color = 'r';
						z = z->parent->parent;
					}
					else if (z == z->parent->right)
					{
						z = z->parent;
						leftrotate(z, root);
					}
					z->parent->color = 'b';
					z->parent->parent->color = 'r';
					rightrotate(z->parent->parent, root);

				}
				else
				{

					rbt_node *y = z->parent->parent->left; // left instead of right
					if (y != NULL && y->color == 'r') // is red?
					{
						z->parent->color = 'b'; // color = black
						y->color = 'b'; // color = black
						z->parent->parent->color = 'r'; // color = red
						z = z->parent->parent;
					}
					else
					{
						if (z == z->parent->left) // left instead of right
						{
							z = z->parent;
							rightrotate(z, root);
						}
						z->parent->color = 'b'; // color is black
						z->parent->parent->color = 'r'; // color is red
						leftrotate(z->parent->parent, root);
					}
				}
			}
		}

		// return actual root
		while (root->parent != nullptr) {
			root = root->parent;
		}
		return root;
	}
	rbt_node* rbt_insert(rbt_node* root, key_type z)
	{

		int i = 0;
		rbt_node *p, *q;
		rbt_node *t = new rbt_node;
		t->key = z;
		t->left = nullptr;
		t->right = nullptr;
		t->color = 'r';
		p = root;
		q = nullptr;
		if (root == nullptr)
		{
			root = t;
			t->parent = nullptr;
		}
		else
		{
			while (p != nullptr)
			{
				q = p;
				//if (p->key<t->key)
				if (alphabetical(p->key, t->key))
					p = p->right;
				else
					p = p->left;
			}
			t->parent = q;
			//if (q->key<t->key)
			if (alphabetical(q->key, t->key))
				q->right = t;
			else
				q->left = t;
		}
		insertfix(t, root);

		// find correct root
		while (root->parent != nullptr) {
			root = root->parent;
		}


		return root;
	}
	void display(rbt_node *p, rbt_node* root)
	{
		if (root == nullptr)
		{
			cout << "\nEmpty Tree.";
			return;
		}
		if (p != nullptr)
		{
			cout << "\n\t NODE: ";
			cout << "\n Key: " << p->key;
			cout << "\n Colour: ";
			if (p->color == 'b')
				cout << "Black";
			else
				cout << "Red";
			if (p->parent != nullptr)
				cout << "\n Parent: " << p->parent->key;
			else
				cout << "\n There is no parent of the node.  ";
			if (p->right != nullptr)
				cout << "\n Right Child: " << p->right->key;
			else
				cout << "\n There is no right child of the node.  ";
			if (p->left != nullptr)
				cout << "\n Left Child: " << p->left->key;
			else
				cout << "\n There is no left child of the node.  ";
			cout << endl;
			if (p->left)
			{
				cout << "\n\nLeft:\n";
				display(p->left, root);
			}

			if (p->right)
			{
				cout << "\n\nRight:\n";
				display(p->right, root);
			}

		}
	}
	void disp(rbt_node* root)
	{
		display(root, root);
	}
	rbt_node* rbt_makeTree(
		string filename_and_path_in,
		rbt_node* root,
		long double* start_time_construct,
		long double* end_time_construct,
		long double* duration_construct,
		long double* start_time_insert_key_WORST,
		long double* end_time_insert_key_WORST,
		long double* duration_insert_key_WORST,
		long double* start_time_insert_key_AVERAGE,
		long double* end_time_insert_key_AVERAGE,
		long double* duration_insert_key_AVERAGE,
		bool printstuff) {

		key_type temp_string;
		ifstream infile;

		*start_time_construct = clock(start);
		infile.open(filename_and_path_in);
		if (infile.fail()) {
			cout << "***** BAD FILENAME *****\n\n";
			//system("pause");
		}

		line();

		if (print_stuff) { cout << "Print while inserting: " << endl; }
		else { //cout << "Don't print while inserting: " << endl; 
		}

		// get root
		getline(infile, temp_string);
		root->key = temp_string;
		if (print_stuff) {
			cout << "                 ";
			cout << temp_string << endl;
		}

		int num_of_nodes = 1;
		while (!infile.eof()) {
			num_of_nodes++;
			getline(infile, temp_string);
			// don't add if not word, i.e. " "
			if (!isWord(temp_string)) { // emn
				num_of_nodes--;
				//cout << "space" << endl;
			}
			else {
				if (print_stuff) {
					cout << "                 ";
					cout << temp_string << endl;
				}
				*start_time_insert_key_WORST = clock(start);
				*start_time_insert_key_AVERAGE = clock(start);
				root = rbt_insert(root, temp_string);
				*end_time_insert_key_WORST = clock(start);
				*end_time_insert_key_AVERAGE = clock(start);
				*duration_insert_key_AVERAGE += ((*end_time_insert_key_AVERAGE) - (*start_time_insert_key_AVERAGE));
				if (*duration_insert_key_WORST <
					(*end_time_insert_key_WORST - *start_time_insert_key_WORST)) {
					*duration_insert_key_WORST = ((*end_time_insert_key_WORST) - (*start_time_insert_key_WORST));
				}
			}
		}
		(*duration_insert_key_AVERAGE) = ((*duration_insert_key_AVERAGE) / num_of_nodes);
		infile.close();
		*end_time_construct = clock(start);
		*duration_construct = *end_time_construct - *start_time_construct;

		return root;
	}
	rbt_node* rbt_printSearchPath(
		rbt_node* p,
		key_type a,
		long double* start_time_search_WORST,
		long double* end_time_search_WORST,
		long double* duration_search_WORST,
		long double* start_time_search_AVERAGE,
		long double* end_time_search_AVERAGE,
		long double* duration_search_AVERAGE,
		long double* start_time_extra,
		long double* end_time_extra,
		long double* duration_time_extra,
		bool printstuff) {
		if (printstuff) {
			cout << a << " SEARCH PATH: " << endl;
		}
		rbt_node* p2;
		*start_time_extra = *start_time_search_AVERAGE = *start_time_search_WORST = clock(start);
		p2 = rbt_searchPrintTree(p, a, printstuff);
		*end_time_extra = *end_time_search_AVERAGE = *end_time_search_WORST = clock(start);
		*duration_search_AVERAGE += (*end_time_search_AVERAGE - *start_time_search_AVERAGE);
		if (*duration_search_WORST <
			(*end_time_search_WORST - *start_time_search_WORST)) {
			*duration_search_WORST =
				(*end_time_search_WORST - *start_time_search_WORST);
		}
		*duration_time_extra = (*end_time_extra - *start_time_extra);

		return p2;
	}
	int rbt_printFound(string a, rbt_node* p) {
		cout << a << " Found?: " << " "
			<< ((p == nullptr) ? "nullptr" : p->key) << endl;
		return 0;
	}
	int rbt_printInOrder(rbt_node* p, bool printstuff) {
		//if (p != nullptr)
		//cout << p->key << endl;

		if (p == nullptr) {
			return 0;
		}
		rbt_printInOrder(p->left, printstuff);
		if (printstuff) {
			cout << "                 ";
			cout << p->key << endl;
		}
		rbt_printInOrder(p->right, printstuff);

		return 0;
	}
	rbt_node* rbt_searchPrintTree(rbt_node* p, key_type a, bool printstuff) {
		if (printstuff) {
			cout << "                 ";
			cout << ((p == nullptr) ? "nullptr" : p->key) << endl;
		}
		rbt_node* p2 = nullptr;

		// base case not found and leaf
		if (p == nullptr) return nullptr;
		// base case found
		if (p->key == a) return p;

		// general case not found
		if (alphabetical(p->key, a)) p2 = rbt_searchPrintTree(p->right, a, printstuff);
		if (alphabetical(a, p->key)) p2 = rbt_searchPrintTree(p->left, a, printstuff);

		return p2;
	}
	rbt_node* rbt_searchTree(rbt_node* p, key_type a) {

		rbt_node* p2 = nullptr;

		// base case not found and leaf
		if (p == nullptr) return nullptr;
		// base case found
		if (p->key == a) return p;

		// general case not found
		if (alphabetical(p->key, a)) p2 = rbt_searchTree(p->right, a);
		if (alphabetical(a, p->key)) p2 = rbt_searchTree(p->left, a);

		return p2;
	}

};


//////////////////////////////////////////////////////
///////////// COMPLEX FUNCTIONS 
//////////////////////////////////////////////////////



/*



///// RBT /////
int rbt_printFound(string a, rbt_node* p) {
	cout << a << " Found?: " << " "
		<< ((p == nullptr) ? "nullptr" : p->key) << endl;
	return 0;
}
void leftrotate(rbt_node *p, rbt_node* root)
{
	if (p->right == nullptr)
		return;
	else
	{
		rbt_node *y = p->right;
		if (y->left != nullptr)
		{
			p->right = y->left;
			y->left->parent = p;
		}
		else
			p->right = nullptr;
		if (p->parent != nullptr)
			y->parent = p->parent;
		if (p->parent == nullptr)
			root = y;
		else
		{
			if (p == p->parent->left)
				p->parent->left = y;
			else
				p->parent->right = y;
		}
		y->left = p;
		p->parent = y;
	}
}
void rightrotate(rbt_node *p, rbt_node* root)
{
	if (p->left == nullptr)
		return;
	else
	{
		rbt_node *y = p->left;
		if (y->right != nullptr)
		{
			p->left = y->right;
			y->right->parent = p;
		}
		else
			p->left = nullptr;
		if (p->parent != nullptr)
			y->parent = p->parent;
		if (p->parent == nullptr)
			root = y;
		else
		{
			if (p == p->parent->left)
				p->parent->left = y;
			else
				p->parent->right = y;
		}
		y->right = p;
		p->parent = y;
	}
}
rbt_node* insertfix_1(rbt_node *t, rbt_node* root)
{
	rbt_node *u;
	if (root == t)
	{
		t->color = 'b';
		return root;
	}
	while (t->parent != nullptr && t->parent->color == 'r')
	{
		rbt_node *g = t->parent->parent;
		if (g->left == t->parent)
		{
			if (g->right != nullptr)
			{
				u = g->right;
				if (u->color == 'r')
				{
					t->parent->color = 'b';
					u->color = 'b';
					g->color = 'r';
					t = g;
				}
			}
			else
			{
				if (t->parent->right == t)
				{
					t = t->parent;
					leftrotate(t, root);
				}
				t->parent->color = 'b';
				g->color = 'r';
				rightrotate(g, root);
			}
		}
		else
		{
			if (g->left != nullptr)
			{
				u = g->left;
				if (u->color == 'r')
				{
					t->parent->color = 'b';
					u->color = 'b';
					g->color = 'r';
					t = g;
				}
			}
			else
			{
				if (t->parent->left == t)
				{
					t = t->parent;
					rightrotate(t, root);
				}
				t->parent->color = 'b';
				g->color = 'r';
				leftrotate(g, root);
			}
		}
		root->color = 'b';
	}
	// finding root
	while (root->parent != nullptr) {
		root = root->parent;
	}

	return root;
}
rbt_node* insertfix(rbt_node* z, rbt_node* root)
{
	if (z->parent != NULL && z->parent->parent != NULL)
	{
		while (z != NULL && z->parent != NULL &&
			z->parent->parent != NULL && !z->parent->color == 'b')
			// ass long as color is not black, thus red
		{
			if (z->parent == z->parent->parent->left)
			{
				rbt_node *y = z->parent->parent->right;
				if (y != NULL && y->color == 'r')
				{
					z->parent->color = 'b';
					y->color = 'b';
					z->parent->parent->color = 'r';
					z = z->parent->parent;
				}
				else if (z == z->parent->right)
				{
					z = z->parent;
					leftrotate(z, root);
				}
				z->parent->color = 'b';
				z->parent->parent->color = 'r';
				rightrotate(z->parent->parent, root);

			}
			else
			{

				rbt_node *y = z->parent->parent->left; // left instead of right
				if (y != NULL && y->color == 'r') // is red?
				{
					z->parent->color = 'b'; // color = black
					y->color = 'b'; // color = black
					z->parent->parent->color = 'r'; // color = red
					z = z->parent->parent;
				}
				else
				{
					if (z == z->parent->left) // left instead of right
					{
						z = z->parent;
						rightrotate(z, root);
					}
					z->parent->color = 'b'; // color is black
					z->parent->parent->color = 'r'; // color is red
					leftrotate(z->parent->parent, root);
				}
			}
		}
	}

	// return actual root
	while (root->parent != nullptr) {
		root = root->parent;
	}
	return root;
}
rbt_node* rbt_insert(rbt_node* root, key_type z)
{

	int i = 0;
	rbt_node *p, *q;
	rbt_node *t = new rbt_node;
	t->key = z;
	t->left = nullptr;
	t->right = nullptr;
	t->color = 'r';
	p = root;
	q = nullptr;
	if (root == nullptr)
	{
		root = t;
		t->parent = nullptr;
	}
	else
	{
		while (p != nullptr)
		{
			q = p;
			//if (p->key<t->key)
			if (alphabetical(p->key,t->key))
				p = p->right;
			else
				p = p->left;
		}
		t->parent = q;
		//if (q->key<t->key)
		if (alphabetical(q->key,t->key))
			q->right = t;
		else
			q->left = t;
	}
	insertfix(t, root);

	// find correct root
	while (root->parent != nullptr) {
		root = root->parent;
	}


	return root;
}
void display(rbt_node *p, rbt_node* root)
{
	if (root == nullptr)
	{
		cout << "\nEmpty Tree.";
		return;
	}
	if (p != nullptr)
	{
		cout << "\n\t NODE: ";
		cout << "\n Key: " << p->key;
		cout << "\n Colour: ";
		if (p->color == 'b')
			cout << "Black";
		else
			cout << "Red";
		if (p->parent != nullptr)
			cout << "\n Parent: " << p->parent->key;
		else
			cout << "\n There is no parent of the node.  ";
		if (p->right != nullptr)
			cout << "\n Right Child: " << p->right->key;
		else
			cout << "\n There is no right child of the node.  ";
		if (p->left != nullptr)
			cout << "\n Left Child: " << p->left->key;
		else
			cout << "\n There is no left child of the node.  ";
		cout << endl;
		if (p->left)
		{
			cout << "\n\nLeft:\n";
			display(p->left, root);
		}

		if (p->right)
		{
			cout << "\n\nRight:\n";
			display(p->right, root);
		}


	}
}
void disp(rbt_node* root)
{
	display(root, root);
}
rbt_node* rbt_makeTree(
	string filename_and_path_in,
	rbt_node* root,
	long double* start_time_construct,
	long double* end_time_construct,
	long double* duration_construct,
	long double* start_time_insert_key_WORST,
	long double* end_time_insert_key_WORST,
	long double* duration_insert_key_WORST,
	long double* start_time_insert_key_AVERAGE,
	long double* end_time_insert_key_AVERAGE,
	long double* duration_insert_key_AVERAGE,
	bool printstuff) {

	key_type temp_string;
	ifstream infile;

	*start_time_construct = clock(start);
	infile.open(filename_and_path_in);
	if (infile.fail()) {
		cout << "***** BAD FILENAME *****\n\n";
		//system("pause");
	}

	line();

	if (print_stuff) { cout << "Print while inserting: " << endl; }
	else { //cout << "Don't print while inserting: " << endl; 
	}

	// get root
	getline(infile, temp_string);
	root->key = temp_string;
	if (print_stuff) {
		cout << "                 ";
		cout << temp_string << endl;
	}

	int num_of_nodes = 1;
	while (!infile.eof()) {
		num_of_nodes++;
		getline(infile, temp_string);
		// don't add if not word, i.e. " "
		if (!isWord(temp_string)) { // emn
			num_of_nodes--;
			//cout << "space" << endl;
		}
		else {
			if (print_stuff) {
				cout << "                 ";
				cout << temp_string << endl;
			}
			*start_time_insert_key_WORST = clock(start);
			*start_time_insert_key_AVERAGE = clock(start);
			root = rbt_insert(root, temp_string);
			*end_time_insert_key_WORST = clock(start);
			*end_time_insert_key_AVERAGE = clock(start);
			*duration_insert_key_AVERAGE += ((*end_time_insert_key_AVERAGE) - (*start_time_insert_key_AVERAGE));
			if (*duration_insert_key_WORST <
				(*end_time_insert_key_WORST - *start_time_insert_key_WORST)) {
				*duration_insert_key_WORST = ((*end_time_insert_key_WORST) - (*start_time_insert_key_WORST));
			}
		}
	}
	(*duration_insert_key_AVERAGE) = ((*duration_insert_key_AVERAGE) / num_of_nodes);
	infile.close();
	*end_time_construct = clock(start);
	*duration_construct = *end_time_construct - *start_time_construct;

	return root;
}
rbt_node* rbt_printSearchPath(
	rbt_node* p,
	key_type a,
	long double* start_time_search_WORST,
	long double* end_time_search_WORST,
	long double* duration_search_WORST,
	long double* start_time_search_AVERAGE,
	long double* end_time_search_AVERAGE,
	long double* duration_search_AVERAGE,
	long double* start_time_extra,
	long double* end_time_extra,
	long double* duration_time_extra,
	bool printstuff) {
	if (printstuff) {
		cout << a << " SEARCH PATH: " << endl;
	}
	rbt_node* p2;
	*start_time_extra = *start_time_search_AVERAGE = *start_time_search_WORST = clock(start);
	p2 = rbt_searchPrintTree(p, a, printstuff);
	*end_time_extra = *end_time_search_AVERAGE = *end_time_search_WORST = clock(start);
	*duration_search_AVERAGE += (*end_time_search_AVERAGE - *start_time_search_AVERAGE);
	if (*duration_search_WORST <
		(*end_time_search_WORST - *start_time_search_WORST)) {
		*duration_search_WORST =
			(*end_time_search_WORST - *start_time_search_WORST);
	}
	*duration_time_extra = (*end_time_extra - *start_time_extra);

	return p2;
}
int rbt_printInOrder(rbt_node* p, bool printstuff) {
	//if (p != nullptr)
		//cout << p->key << endl;

	if (p == nullptr) {
		return 0;
	}
	rbt_printInOrder(p->left, printstuff);
	if (printstuff) {
		cout << "                 ";
		cout << p->key << endl;
	}
	rbt_printInOrder(p->right, printstuff);

	return 0;
}
rbt_node* rbt_searchPrintTree(rbt_node* p, key_type a, bool printstuff) {
	if (printstuff) {
		cout << "                 ";
		cout << ((p == nullptr) ? "nullptr" : p->key) << endl;
	}
	rbt_node* p2 = nullptr;

	// base case not found and leaf
	if (p == nullptr) return nullptr;
	// base case found
	if (p->key == a) return p;

	// general case not found
	if (alphabetical(p->key, a)) p2 = rbt_searchPrintTree(p->right, a, printstuff);
	if (alphabetical(a, p->key)) p2 = rbt_searchPrintTree(p->left, a, printstuff);

	return p2;
}
rbt_node* rbt_searchTree(rbt_node* p, key_type a) {

	rbt_node* p2 = nullptr;

	// base case not found and leaf
	if (p == nullptr) return nullptr;
	// base case found
	if (p->key == a) return p;

	// general case not found
	if (alphabetical(p->key, a)) p2 = rbt_searchTree(p->right, a);
	if (alphabetical(a, p->key)) p2 = rbt_searchTree(p->left, a);

	return p2;
}

///// BST /////
bst_node* bst_printSearchPath(
	bst_node* p,
	key_type a,
	long double* start_time_search_WORST,
	long double* end_time_search_WORST,
	long double* duration_search_WORST,
	long double* start_time_search_AVERAGE,
	long double* end_time_search_AVERAGE,
	long double* duration_search_AVERAGE,
	long double* start_time_extra,
	long double* end_time_extra,
	long double* duration_time_extra,
	bool printstuff) {
	if (printstuff) {
		cout << a << " SEARCH PATH: " << endl;
	}
	bst_node* p2;
	*start_time_extra = *start_time_search_AVERAGE = *start_time_search_WORST = clock(start);
	p2 = bst_searchPrintTree(p, a, printstuff);
	*end_time_extra = *end_time_search_AVERAGE = *end_time_search_WORST = clock(start);
	*duration_search_AVERAGE += (*end_time_search_AVERAGE - *start_time_search_AVERAGE);
	if (*duration_search_WORST <
		(*end_time_search_WORST - *start_time_search_WORST)) {
		*duration_search_WORST =
			(*end_time_search_WORST - *start_time_search_WORST);
	}
	*duration_time_extra = (*end_time_extra - *start_time_extra);
	return p2;
}
int bst_printFound(string a, bst_node* p) {
	cout << a << " Found?: " << " "
		<< ((p == nullptr) ? "nullptr" : p->key) << endl;
	return 0;
}
bst_node* bst_insert(bst_node* root, key_type a) {

	if (root == nullptr) {
		bst_node* p = new bst_node;
		p->key = a;
		p->left = nullptr;
		p->right = nullptr;
		return p;
	}

	if (alphabetical(root->key, a)) {
		root->right = bst_insert(root->right, a);
	}
	else {
		root->left = bst_insert(root->left, a);
	}

	return root;
}
int bst_printInOrder(bst_node* p, bool printstuff) {
	if (p == nullptr) {
		return 0;
	}
	bst_printInOrder(p->left, printstuff);
	if (printstuff) {
		cout << "                 ";
		cout << p->key << endl;
	}
	bst_printInOrder(p->right, printstuff);

	return 0;
}
bst_node* bst_searchPrintTree(bst_node* p, key_type a, bool printstuff) {
	if (printstuff) {
		cout << "                 ";
		cout << ((p == nullptr) ? "nullptr" : p->key) << endl;
	}
	bst_node* p2 = nullptr;

	// base case not found and leaf
	if (p == nullptr) return nullptr;
	// base case found
	if (p->key == a) return p;

	// general case not found
	if (alphabetical(p->key, a)) p2 = bst_searchPrintTree(p->right, a, printstuff);
	if (alphabetical(a, p->key)) p2 = bst_searchPrintTree(p->left, a, printstuff);

	return p2;
}
bst_node* bst_searchTree(bst_node* p, key_type a) {

	bst_node* p2 = nullptr;

	// base case not found and leaf
	if (p == nullptr) return nullptr;
	// base case found
	if (p->key == a) return p;

	// general case not found
	if (alphabetical(p->key, a)) p2 = bst_searchTree(p->right, a);
	if (alphabetical(a, p->key)) p2 = bst_searchTree(p->left, a);

	return p2;
}
int bst_makeTree(
	string filename_and_path_in,
	bst_node* p,
	long double* start_time_construct,
	long double* end_time_construct, 
	long double* duration_construct,
	long double* start_time_insert_key_WORST,
	long double* end_time_insert_key_WORST,
	long double* duration_insert_key_WORST,
	long double* start_time_insert_key_AVERAGE,
	long double* end_time_insert_key_AVERAGE,
	long double* duration_insert_key_AVERAGE,
	bool printstuff){

key_type temp_string;
ifstream infile;

*start_time_construct = clock(start);
infile.open(filename_and_path_in);
if (infile.fail()) {
	cout << "***** BAD FILENAME *****\n\n";
	system("pause");
}

line();

if (print_stuff) { cout << "Print while inserting: " << endl; }
else { //cout << "Don't print while inserting: " << endl; 
}

// get root
getline(infile, temp_string);
p->key = temp_string;
if (print_stuff) {
	cout << "                 ";
	cout << temp_string << endl;
}

int num_of_nodes = 1;
while (!infile.eof()) {
	num_of_nodes++;
	getline(infile, temp_string);
	// don't add if not word, i.e. " "
	if (!isWord(temp_string)) {
		num_of_nodes--;
		//cout << "space" << endl;
	}
	else {
		if (print_stuff) {
			cout << "                 ";
			cout << temp_string << endl;
		}
		*start_time_insert_key_WORST = clock(start);
		*start_time_insert_key_AVERAGE = clock(start);
		bst_insert(p, temp_string);
		*end_time_insert_key_WORST = clock(start);
		*end_time_insert_key_AVERAGE = clock(start);
		*duration_insert_key_AVERAGE += ((*end_time_insert_key_AVERAGE) - (*start_time_insert_key_AVERAGE));
		if (*duration_insert_key_WORST <
			(*end_time_insert_key_WORST - *start_time_insert_key_WORST)) {
			*duration_insert_key_WORST = ((*end_time_insert_key_WORST) - (*start_time_insert_key_WORST));
		}
	}
}
(*duration_insert_key_AVERAGE) = ((*duration_insert_key_AVERAGE) / num_of_nodes);
infile.close();
*end_time_construct = clock(start);
*duration_construct = *end_time_construct - *start_time_construct;

return 0;
}



*/



//////////////////////////////////////////////////////
///////////// INTERFACE FUNCTIONS 
//////////////////////////////////////////////////////




char splash(){
	char c;
	cout << "    Eric Niemeyer" << endl;
	cout << "    CS 340 Project 2" << endl;
	cout << endl;
	cout << "What do you want to do?" << endl;
	cout << endl;
	cout << " GRADER INTERACT : 'i'" << endl;
	cout << "      RUN A TEST : 't'" << endl;
	cout << "   RUN ALL TESTS : 'a'" << endl;
	cout << "   RUN ALL T + 1 : 'o'" << endl;
	cout << "       or   QUIT : 'q'" << endl;
	cout << endl;
	cout << "     YOUR CHOICE :  ";
	cin >> c;
	
	while (!(c == 't' || c == 'i' || c == 'q' || c == 'a' || c == 'o')) {
		cout << endl;
		cout << "*************************" << endl;
		cout << "*** INVALID SELECTION ***" << endl;
		cout << "*************************" << endl;
		cout << "What do you want to do?" << endl;
		cout << endl;
		cout << " GRADER INTERACT : 'i'" << endl;
		cout << "      RUN A TEST : 't'" << endl;
		cout << "   RUN ALL TESTS : 'a'" << endl;
		cout << "   RUN ALL T + 1 : 'o'" << endl;
		cout << "       or   QUIT : 'q'" << endl;
		cout << endl;
		cout << "     YOUR CHOICE :  ";
		cin >> c;
	}
	cout << endl << endl;
	return c;
}

struct graderChoice {
	string grader_word = "XXX";
	string grader_file = "XXX";
	string grader_tree = "XXX";
};

graderChoice* graderSplash() {

	string g_w, g_f, g_t;
	graderChoice* a = new graderChoice;

	cout << "Search for what word?(ALL UPPERCASE PLEASE): ";
	cin >> g_w;
	while (!isWord(g_w)) {
		cout << endl;
		cout << "*************************" << endl;
		cout << "***   INVALID WORD    ***" << endl;
		cout << "*************************" << endl;
		cout << endl;
		cout << "Search for what word?(ALL UPPERCASE PLEASE): ";
		cin >> g_w;
	}
	cout << "Search in what file?(FULL PATH & FILENAME): ";
	cin >> g_f;
	while (!(alphabetical(g_f,"C;") && alphabetical("C9",g_f)) ){
		cout << endl;
		cout << "*************************" << endl;
		cout << "***   INVALID PATH    ***" << endl;
		cout << "*************************" << endl;
		cout << endl;
		cout << "Example: C:/Users/secpc/Desktop/wordlists/perm15K.txt" << endl;
		cout << endl;
		cout << "Search in what file?(FULL PATH & FILENAME): ";
		cin >> g_f;
	}

	cout << "Binary Search 'bst' or Red-Black 'rbt'?: ";
	cin >> g_t;
	while (!(g_t == "bst" || g_t == "rbt"|| g_t == "BST" || g_t == "RBT")) {
		cout << endl;
		cout << "*************************" << endl;
		cout << "*** INVALID SELECTION ***" << endl;
		cout << "*************************" << endl;
		cout << endl;
		cout << "Binary Search 'bst' or Red-Black 'rbt'?: ";
		cin >> g_t;
	}
	if (g_t == "bst") {
		g_t = "BST";
	}
	if (g_t == "rbt") {
		g_t = "RBT";
	}

	a->grader_file = g_f;
	a->grader_word = g_w;
	a->grader_tree = g_t;

	return a;

}

int initializeTimers(
	long double* start_time_construct,
long double* start_time_insert_key_AVERAGE,
long double* start_time_insert_key_WORST,
long double* start_time_search_AVERAGE,
long double* start_time_search_WORST,
long double* end_time_construct,
long double* end_time_insert_key_AVERAGE,
long double* end_time_insert_key_WORST,
long double* end_time_search_AVERAGE,
long double* end_time_search_WORST,
long double* duration_construct,
long double* duration_insert_key_AVERAGE,
long double* duration_insert_key_WORST,
long double* duration_search_AVERAGE,
long double* duration_search_WORST,
long double* start_time_extra,
long double* end_time_extra,
long double* duration_time_extra
) {

	*start_time_construct = 0;
	*start_time_insert_key_AVERAGE = 0;
	*start_time_insert_key_WORST = 0;
	*start_time_search_AVERAGE = 0;
	*start_time_search_WORST = 0;

	*end_time_construct = 0;
	*end_time_insert_key_AVERAGE = 0;
	*end_time_insert_key_WORST = 0;
	*end_time_search_AVERAGE = 0;
	*end_time_search_WORST = 0;

	*duration_construct = 0;
	*duration_insert_key_AVERAGE = 0;
	*duration_insert_key_WORST = 0;
	*duration_search_AVERAGE = 0;
	*duration_search_WORST = 0;

	*start_time_extra = 0;
	*end_time_extra = 0;
	*duration_time_extra = 0;


	return 0;
}


//////////////////////////////////////////////////////

///////////// MAIN 

//////////////////////////////////////////////////////
int main() {

	start = chrono::high_resolution_clock::now();

	RBT * myRBT = new RBT;
	BST* myBST = new BST;

	myRBT->line();
	choice = splash();

	graderChoice* myGraderChoice;

	int filecounts[10];
	for (int i = 0; i < 10; i++) {
		filecounts[i] = 15 + i * 15;
	}


	// stuff to insert
	int base = 65;
	int numberOfSearches = 26;


	str_ptr* n = new str_ptr[numberOfSearches];
	//strptr n[26];

	for (int i = 0; i < numberOfSearches; i++) {
		n[i] = new string;
		*(n[i]) = "";
		for (int j = 0; j < 5; j++) {
			(*(n[i])).push_back(65 + i);
		}
	}
	/*
	n[0] = new string;
	n[1] = new string;
	n[2] = new string;
	*(n[0]) = "AAA";
	*(n[1]) = "BBB";
	*(n[2]) = "CCC";
	*/

	long double* start_time_construct = new long double;
	long double* start_time_insert_key_AVERAGE = new long double;
	long double* start_time_insert_key_WORST = new long double;
	long double* start_time_search_AVERAGE = new long double;
	long double* start_time_search_WORST = new long double;

	long double* end_time_construct = new long double;
	long double* end_time_insert_key_AVERAGE = new long double;
	long double* end_time_insert_key_WORST = new long double;
	long double* end_time_search_AVERAGE = new long double;
	long double* end_time_search_WORST = new long double;

	long double* duration_construct = new long double;
	long double* duration_insert_key_AVERAGE = new long double;
	long double* duration_insert_key_WORST = new long double;
	long double* duration_search_AVERAGE = new long double;
	long double* duration_search_WORST = new long double;

	long double* start_time_extra = new long double;
	long double* end_time_extra = new long double;
	long double* duration_time_extra = new long double;

	string* rando = new string;

	/*
	*start_time_construct = 0;
	*start_time_insert_key_AVERAGE = 0;
	*start_time_insert_key_WORST = 0;
	*start_time_search_AVERAGE = 0;
	*start_time_search_WORST = 0;

	*end_time_construct = 0;
	*end_time_insert_key_AVERAGE = 0;
	*end_time_insert_key_WORST = 0;
	*end_time_search_AVERAGE = 0;
	*end_time_search_WORST = 0;

	*duration_construct = 0;
	*duration_insert_key_AVERAGE = 0;
	*duration_insert_key_WORST = 0;
	*duration_search_AVERAGE = 0;
	*duration_search_WORST = 0;

	*start_time_extra = 0;
	*end_time_extra = 0;
	*duration_time_extra = 0;
	*/


		// all tests
		if (choice == 'a') {
			ofstream fout;
			string out_filenameandpath = path + filename_out;
			fout.open(out_filenameandpath);

			// each mult of 15
			for (int e = 0; e < 10; e++) {

				// perm and sorted
				for (int o = 0; o < 2; o++) {



					string filename_and_path_in = path
						+ ((o == 1) ? "perm" : "sorted")
						+ multiples_of_fifteen[e]
						+ "K.txt";
					string filename_and_path_out = path + filename_out;

					//cout << filename_in << endl;

					int numberOfInsertions = 0;
					bst_node_ptr* bst_test_nodes;
					rbt_node_ptr* rbt_test_nodes;

					/////////////////// RED BLACK ///////////////////
					/////////////////// RED BLACK ///////////////////
					/////////////////// RED BLACK ///////////////////

					cout << "/////////////////// RED BLACK ///////////////////" << endl;
					tree_type = "RBT";

					rbt_node* rbt_root_ptr = new rbt_node;
					rbt_root_ptr->color = 'b';

					
					initializeTimers(
						start_time_construct,
						start_time_insert_key_AVERAGE,
						start_time_insert_key_WORST,
						start_time_search_AVERAGE,
						start_time_search_WORST,
						end_time_construct,
						end_time_insert_key_AVERAGE,
						end_time_insert_key_WORST,
						end_time_search_AVERAGE,
						end_time_search_WORST,
						duration_construct,
						duration_insert_key_AVERAGE,
						duration_insert_key_WORST,
						duration_search_AVERAGE,
						duration_search_WORST,
						start_time_extra,
						end_time_extra,
						duration_time_extra
					);
					

					rbt_root_ptr = myRBT->rbt_makeTree
					(
						filename_and_path_in,
						rbt_root_ptr,
						start_time_construct,
						end_time_construct,
						duration_construct,
						start_time_insert_key_WORST,
						end_time_insert_key_WORST,
						duration_insert_key_WORST,
						start_time_insert_key_AVERAGE,
						end_time_insert_key_AVERAGE,
						duration_insert_key_AVERAGE,
						print_stuff);

					int test_int_rbt = 0;
					numberOfInsertions = 0;

					for (int i = 0; i < (numberOfSearches - 1); i++) {
						if (i % 2 == 0) {

							myRBT->rbt_insert(rbt_root_ptr, *n[i]);
							numberOfInsertions++;

						}

					}

					rbt_root_ptr = myRBT->rbt_insert(rbt_root_ptr, *n[numberOfSearches - 1]);
					numberOfInsertions++;



					myRBT->line(print_stuff);
					if (print_stuff) {
						cout << "Print in order:" << endl;
					}
					else {
						//cout << "Don't print in order:" << endl;
					}

					if (print_stuff) {
						myRBT->rbt_printInOrder(rbt_root_ptr, print_stuff);
					}


					myRBT->line(print_stuff);
					//*start_time_search_AVERAGE = clock();

					rbt_test_nodes = new rbt_node_ptr[numberOfSearches]; // emn

					for (int i = 0; i < numberOfSearches; i++) {
						rbt_test_nodes[i] = new rbt_node;
					}



					for (int i = 0; i < numberOfSearches; i++) {
						rbt_test_nodes[i] = myRBT->rbt_printSearchPath(
							rbt_root_ptr,
							*n[i],
							start_time_search_WORST,
							end_time_search_WORST,
							duration_search_WORST,
							start_time_search_AVERAGE,
							end_time_search_AVERAGE,
							duration_search_AVERAGE,
							start_time_extra,
							end_time_extra,
							duration_time_extra,
							print_stuff);
						myRBT->line(print_stuff);
					}

					*duration_search_AVERAGE = *duration_search_AVERAGE / numberOfSearches;
					for (int i = 0; i < numberOfSearches; i++) {
						if (print_stuff) {
							myRBT->rbt_printFound(*n[i], rbt_test_nodes[i]);
						}
					}


					line(print_stuff);
					myRBT->printTimesScreen(tree_type, filename_and_path_in, numberOfSearches, *duration_construct, *duration_insert_key_AVERAGE, *duration_insert_key_WORST, *duration_search_AVERAGE, *duration_search_WORST, *duration_time_extra);
					myRBT->printTimesFile(fout, tree_type, filename_and_path_out, filename_and_path_in, numberOfSearches, *duration_construct, *duration_insert_key_AVERAGE, *duration_insert_key_WORST, *duration_search_AVERAGE, *duration_search_WORST, *duration_time_extra);

					myRBT->line(print_stuff);
					/*
					cout << "START" << endl;
					rbt_searchPrintTree(rbt_root_ptr, "AAAAA", true);
					cout << "MID" << endl;
					cout << rbt_searchTree(rbt_root_ptr, "AAAAA")->key << endl;
					cout << "END" << endl;
					*/
					delete[] rbt_test_nodes;
					myRBT->line(print_stuff);


					//system("pause");

					/////////////////// BINARY SEARCH ///////////////////
					/////////////////// BINARY SEARCH ///////////////////
					/////////////////// BINARY SEARCH ///////////////////

					cout << "/////////////////// BINARY SEARCH ///////////////////" << endl;
					tree_type = "BST";

					bst_node* bst_root = new bst_node;

					initializeTimers(
						start_time_construct,
						start_time_insert_key_AVERAGE,
						start_time_insert_key_WORST,
						start_time_search_AVERAGE,
						start_time_search_WORST,
						end_time_construct,
						end_time_insert_key_AVERAGE,
						end_time_insert_key_WORST,
						end_time_search_AVERAGE,
						end_time_search_WORST,
						duration_construct,
						duration_insert_key_AVERAGE,
						duration_insert_key_WORST,
						duration_search_AVERAGE,
						duration_search_WORST,
						start_time_extra,
						end_time_extra,
						duration_time_extra
					);


					myBST->bst_makeTree(
						filename_and_path_in,
						bst_root,
						start_time_construct,
						end_time_construct,
						duration_construct,
						start_time_insert_key_WORST,
						end_time_insert_key_WORST,
						duration_insert_key_WORST,
						start_time_insert_key_AVERAGE,
						end_time_insert_key_AVERAGE,
						duration_insert_key_AVERAGE,
						print_stuff);

					int test_int_bst = 0;
					numberOfInsertions = 0;
					for (int i = 0; i < (numberOfSearches - 1); i++) {
						if (i % 2 == 0) {
							myBST->bst_insert(bst_root, *n[i]);
							numberOfInsertions++;
						}
					}
					myBST->bst_insert(bst_root, *n[numberOfSearches - 1]);
					numberOfInsertions++;

					myBST->line(print_stuff);
					if (print_stuff) {
						cout << "Print in order:" << endl;
					}
					else {
						//cout << "Don't print in order:" << endl;
					}

					if (print_stuff) {
						myBST->bst_printInOrder(bst_root, print_stuff);
					}

					myBST->line(print_stuff);
					//*start_time_search_AVERAGE = clock();

					bst_test_nodes = new bst_node_ptr[numberOfSearches]; // emn

					for (int i = 0; i < numberOfSearches; i++) {
						bst_test_nodes[i] = new bst_node;
					}

					for (int i = 0; i < numberOfSearches; i++) {
						bst_test_nodes[i] = myBST->bst_printSearchPath(
							bst_root,
							*n[i],
							start_time_search_WORST,
							end_time_search_WORST,
							duration_search_WORST,
							start_time_search_AVERAGE,
							end_time_search_AVERAGE,
							duration_search_AVERAGE,
							start_time_extra,
							end_time_extra,
							duration_time_extra,
							print_stuff);
						line(print_stuff);
					}

					*duration_search_AVERAGE = *duration_search_AVERAGE / numberOfSearches;
					for (int i = 0; i < numberOfSearches; i++) {
						if (print_stuff) {
							myBST->bst_printFound(*n[i], bst_test_nodes[i]);
						}
					}

					myBST->line(print_stuff);
					myBST->printTimesScreen(tree_type, filename_and_path_in, numberOfSearches, *duration_construct, *duration_insert_key_AVERAGE, *duration_insert_key_WORST, *duration_search_AVERAGE, *duration_search_WORST, *duration_time_extra);
					myBST->printTimesFile(fout, tree_type, filename_and_path_out, filename_and_path_in, numberOfSearches, *duration_construct, *duration_insert_key_AVERAGE, *duration_insert_key_WORST, *duration_search_AVERAGE, *duration_search_WORST, *duration_time_extra);

					myBST->line(print_stuff);
					/*
					cout << "START" << endl;
					bst_searchPrintTree(bst_root, "AAAAA", true);
					cout << "MID" << endl;
					cout << bst_searchTree(bst_root, "AAAAA")->key << endl;
					cout << "END" << endl;
					*/
					delete[] bst_test_nodes;
					myBST->line(print_stuff);

				}
			}
			fout.close();
		}
		// all tests plus one
		if (choice == 'o') {
			ofstream fout;
			string out_filenameandpath = path + filename_out;
			fout.open(out_filenameandpath);

			// each mult of 15
			for (int e = 0; e < 10; e++) {
			//for (int e = 9; e >= 0; e--) { // emn

				// perm and sorted
				for (int o = 0; o < 2; o++) {



					string filename_and_path_in = path
						+ ((o == 1) ? "perm" : "sorted")
						+ multiples_of_fifteen[e]
						+ "K.txt";
					string filename_and_path_out = path + filename_out;

					//cout << filename_in << endl;

					int numberOfInsertions = 0;
					bst_node_ptr* bst_test_nodes;
					rbt_node_ptr* rbt_test_nodes;

					/////////////////// RED BLACK ///////////////////
					/////////////////// RED BLACK ///////////////////
					/////////////////// RED BLACK ///////////////////

					cout << "/////////////////// RED BLACK ///////////////////" << endl;
					tree_type = "RBT";

					rbt_node* rbt_root_ptr = new rbt_node;
					rbt_root_ptr->color = 'b';

					initializeTimers(
						start_time_construct,
						start_time_insert_key_AVERAGE,
						start_time_insert_key_WORST,
						start_time_search_AVERAGE,
						start_time_search_WORST,
						end_time_construct,
						end_time_insert_key_AVERAGE,
						end_time_insert_key_WORST,
						end_time_search_AVERAGE,
						end_time_search_WORST,
						duration_construct,
						duration_insert_key_AVERAGE,
						duration_insert_key_WORST,
						duration_search_AVERAGE,
						duration_search_WORST,
						start_time_extra,
						end_time_extra,
						duration_time_extra
					);

					rbt_root_ptr = myRBT->rbt_makeTree(
						filename_and_path_in,
						rbt_root_ptr,
						start_time_construct,
						end_time_construct,
						duration_construct,
						start_time_insert_key_WORST,
						end_time_insert_key_WORST,
						duration_insert_key_WORST,
						start_time_insert_key_AVERAGE,
						end_time_insert_key_AVERAGE,
						duration_insert_key_AVERAGE,
						print_stuff);

					int test_int_rbt = 0;
					numberOfInsertions = 0;

					for (int i = 0; i < (numberOfSearches - 1); i++) {
						if (i % 2 == 0) {

							myRBT->rbt_insert(rbt_root_ptr, *n[i]);
							numberOfInsertions++;

						}

					}

					rbt_root_ptr = myRBT->rbt_insert(rbt_root_ptr, *n[numberOfSearches - 1]);
					numberOfInsertions++;



					line(print_stuff);
					if (print_stuff) {
						cout << "Print in order:" << endl;
					}
					else {
						//cout << "Don't print in order:" << endl;
					}

					if (print_stuff) {
						myRBT->rbt_printInOrder(rbt_root_ptr, print_stuff);
					}


					line(print_stuff);
					//*start_time_search_AVERAGE = clock();

					rbt_test_nodes = new rbt_node_ptr[numberOfSearches]; // emn

					for (int i = 0; i < numberOfSearches; i++) {
						rbt_test_nodes[i] = new rbt_node;
					}



					for (int i = 0; i < numberOfSearches; i++) {
						rbt_test_nodes[i] = myRBT->rbt_printSearchPath(
							rbt_root_ptr,
							*n[i],
							start_time_search_WORST,
							end_time_search_WORST,
							duration_search_WORST,
							start_time_search_AVERAGE,
							end_time_search_AVERAGE,
							duration_search_AVERAGE,
							start_time_extra,
							end_time_extra,
							duration_time_extra,
							print_stuff);
						line(print_stuff);
					}

					*duration_search_AVERAGE = *duration_search_AVERAGE / numberOfSearches;
					for (int i = 0; i < numberOfSearches; i++) {
						if (print_stuff) {
							myRBT->rbt_printFound(*n[i], rbt_test_nodes[i]);
						}
					}


					myRBT->line(print_stuff);
					myRBT->printTimesScreen(tree_type, filename_and_path_in, numberOfSearches, *duration_construct, *duration_insert_key_AVERAGE, *duration_insert_key_WORST, *duration_search_AVERAGE, *duration_search_WORST, *duration_time_extra);
					myRBT->printTimesFile(fout, tree_type, filename_and_path_out, filename_and_path_in, numberOfSearches, *duration_construct, *duration_insert_key_AVERAGE, *duration_insert_key_WORST, *duration_search_AVERAGE, *duration_search_WORST, *duration_time_extra);

					line(print_stuff);
					/*
					cout << "START" << endl;
					rbt_searchPrintTree(rbt_root_ptr, "AAAAA", true);
					cout << "MID" << endl;
					cout << rbt_searchTree(rbt_root_ptr, "AAAAA")->key << endl;
					cout << "END" << endl;
					*/

					/*
								// random insert that's checked
								*start_time_extra = clock();
								*rando = (rbt_searchTree(rbt_root_ptr, "DDDDD"))->key;
								*end_time_extra = clock();
								*duration_time_extra = (*end_time_extra - *start_time_extra);
								cout << ((rando==nullptr)?"rando nullptr":*rando) << endl;
								//cout << "     " << rbt_test_nodes[3]->key << " INSERT & SEARCHED: " << ((rando == nullptr) ? "nullptr" : *rando) << " , Duration: " << *duration_time_extra << endl;
						*/
					delete[] rbt_test_nodes;
					line(print_stuff);


					//system("pause");

					/////////////////// BINARY SEARCH ///////////////////
					/////////////////// BINARY SEARCH ///////////////////
					/////////////////// BINARY SEARCH ///////////////////

					cout << "/////////////////// BINARY SEARCH ///////////////////" << endl;
					tree_type = "BST";

					bst_node* bst_root_ptr = new bst_node;

					initializeTimers(
						start_time_construct,
						start_time_insert_key_AVERAGE,
						start_time_insert_key_WORST,
						start_time_search_AVERAGE,
						start_time_search_WORST,
						end_time_construct,
						end_time_insert_key_AVERAGE,
						end_time_insert_key_WORST,
						end_time_search_AVERAGE,
						end_time_search_WORST,
						duration_construct,
						duration_insert_key_AVERAGE,
						duration_insert_key_WORST,
						duration_search_AVERAGE,
						duration_search_WORST,
						start_time_extra,
						end_time_extra,
						duration_time_extra
					);

					myBST->bst_makeTree(
						filename_and_path_in,
						bst_root_ptr,
						start_time_construct,
						end_time_construct,
						duration_construct,
						start_time_insert_key_WORST,
						end_time_insert_key_WORST,
						duration_insert_key_WORST,
						start_time_insert_key_AVERAGE,
						end_time_insert_key_AVERAGE,
						duration_insert_key_AVERAGE,
						print_stuff);

					int test_int_bst = 0;
					numberOfInsertions = 0;
					for (int i = 0; i < (numberOfSearches - 1); i++) {
						if (i % 2 == 0) {
							myBST->bst_insert(bst_root_ptr, *n[i]);
							numberOfInsertions++;
						}
					}
					myBST->bst_insert(bst_root_ptr, *n[numberOfSearches - 1]);
					numberOfInsertions++;

					line(print_stuff);
					if (print_stuff) {
						cout << "Print in order:" << endl;
					}
					else {
						//cout << "Don't print in order:" << endl;
					}

					if (print_stuff) {
						myBST->bst_printInOrder(bst_root_ptr, print_stuff);
					}

					line(print_stuff);
					//*start_time_search_AVERAGE = clock();

					bst_test_nodes = new bst_node_ptr[numberOfSearches]; // emn

					for (int i = 0; i < numberOfSearches; i++) {
						bst_test_nodes[i] = new bst_node;
					}

					for (int i = 0; i < numberOfSearches; i++) {
						bst_test_nodes[i] = myBST->bst_printSearchPath(
							bst_root_ptr,
							*n[i],
							start_time_search_WORST,
							end_time_search_WORST,
							duration_search_WORST,
							start_time_search_AVERAGE,
							end_time_search_AVERAGE,
							duration_search_AVERAGE,
							start_time_extra,
							end_time_extra,
							duration_time_extra,
							print_stuff);
						myBST->line(print_stuff);
					}

					*duration_search_AVERAGE = *duration_search_AVERAGE / numberOfSearches;
					for (int i = 0; i < numberOfSearches; i++) {
						if (print_stuff) {
							myBST->bst_printFound(*n[i], bst_test_nodes[i]);
						}
					}

					myBST->line(print_stuff);
					myBST->printTimesScreen(tree_type, filename_and_path_in, numberOfSearches, *duration_construct, *duration_insert_key_AVERAGE, *duration_insert_key_WORST, *duration_search_AVERAGE, *duration_search_WORST, *duration_time_extra);
					myBST->printTimesFile(fout, tree_type, filename_and_path_out, filename_and_path_in, numberOfSearches, *duration_construct, *duration_insert_key_AVERAGE, *duration_insert_key_WORST, *duration_search_AVERAGE, *duration_search_WORST, *duration_time_extra);

					myBST->line(print_stuff);
					/*
					cout << "START" << endl;
					bst_searchPrintTree(bst_root, "AAAAA", true);
					cout << "MID" << endl;
					cout << bst_searchTree(bst_root, "AAAAA")->key << endl;
					cout << "END" << endl;
					*/

					/*
						// random insert that's checked
						*start_time_extra = clock();
						*rando = (bst_searchTree(bst_root_ptr, "CCCCC")->key);
						*end_time_extra = clock();
						*duration_time_extra = (*end_time_extra - *start_time_extra);
						cout << "     " << bst_test_nodes[3]->key << " INSERT & SEARCHED: " << ((rando==nullptr)?"nullptr":*rando)
							<< " , Duration: " << *duration_time_extra << endl;
						*/
					delete[] bst_test_nodes;
					myBST->line(print_stuff);

				}
			}
			fout.close();
		}
		// one test
		else if (choice == 't') {
			ofstream fout;
			string out_filenameandpath = path + filename_out;
			fout.open(out_filenameandpath);



			string filename_and_path_in = path + filename_in;
			string filename_and_path_out = path + filename_out;

			//cout << filename_in << endl;

			int numberOfInsertions = 0;
			bst_node_ptr* bst_test_nodes;
			rbt_node_ptr* rbt_test_nodes;

			/////////////////// RED BLACK ///////////////////
			/////////////////// RED BLACK ///////////////////
			/////////////////// RED BLACK ///////////////////

			cout << "/////////////////// RED BLACK ///////////////////" << endl;
			tree_type = "RBT";

			rbt_node* rbt_root_ptr = new rbt_node;
			rbt_root_ptr->color = 'b';

			initializeTimers(
				start_time_construct,
				start_time_insert_key_AVERAGE,
				start_time_insert_key_WORST,
				start_time_search_AVERAGE,
				start_time_search_WORST,
				end_time_construct,
				end_time_insert_key_AVERAGE,
				end_time_insert_key_WORST,
				end_time_search_AVERAGE,
				end_time_search_WORST,
				duration_construct,
				duration_insert_key_AVERAGE,
				duration_insert_key_WORST,
				duration_search_AVERAGE,
				duration_search_WORST,
				start_time_extra,
				end_time_extra,
				duration_time_extra
			);

			rbt_root_ptr = myRBT->rbt_makeTree(
				filename_and_path_in,
				rbt_root_ptr,
				start_time_construct,
				end_time_construct,
				duration_construct,
				start_time_insert_key_WORST,
				end_time_insert_key_WORST,
				duration_insert_key_WORST,
				start_time_insert_key_AVERAGE,
				end_time_insert_key_AVERAGE,
				duration_insert_key_AVERAGE,
				print_stuff);

			int test_int_rbt = 0;
			numberOfInsertions = 0;

			for (int i = 0; i < (numberOfSearches - 1); i++) {
				if (i % 2 == 0) {

					myRBT->rbt_insert(rbt_root_ptr, *n[i]);
					numberOfInsertions++;

				}

			}

			rbt_root_ptr = myRBT->rbt_insert(rbt_root_ptr, *n[numberOfSearches - 1]);
			numberOfInsertions++;



			line(print_stuff);
			if (print_stuff) {
				cout << "Print in order:" << endl;
			}
			else {
				//cout << "Don't print in order:" << endl;
			}

			if (print_stuff) {
				myRBT->rbt_printInOrder(rbt_root_ptr, print_stuff);
			}


			line(print_stuff);
			//*start_time_search_AVERAGE = clock();

			rbt_test_nodes = new rbt_node_ptr[numberOfSearches]; // emn

			for (int i = 0; i < numberOfSearches; i++) {
				rbt_test_nodes[i] = new rbt_node;
			}



			for (int i = 0; i < numberOfSearches; i++) {
				rbt_test_nodes[i] = myRBT->rbt_printSearchPath(
					rbt_root_ptr,
					*n[i],
					start_time_search_WORST,
					end_time_search_WORST,
					duration_search_WORST,
					start_time_search_AVERAGE,
					end_time_search_AVERAGE,
					duration_search_AVERAGE,
					start_time_extra,
					end_time_extra,
					duration_time_extra,
					print_stuff);
				myRBT->line(print_stuff);
			}

			*duration_search_AVERAGE = *duration_search_AVERAGE / numberOfSearches;
			for (int i = 0; i < numberOfSearches; i++) {
				if (print_stuff) {
					myRBT->rbt_printFound(*n[i], rbt_test_nodes[i]);
				}
			}


			myRBT->line(print_stuff);
			myRBT->printTimesScreen(tree_type, filename_and_path_in, numberOfSearches, *duration_construct, *duration_insert_key_AVERAGE, *duration_insert_key_WORST, *duration_search_AVERAGE, *duration_search_WORST, *duration_time_extra);
			myRBT->printTimesFile(fout, tree_type, filename_and_path_out, filename_and_path_in, numberOfSearches, *duration_construct, *duration_insert_key_AVERAGE, *duration_insert_key_WORST, *duration_search_AVERAGE, *duration_search_WORST, *duration_time_extra);

			myRBT->line(print_stuff);
			/*
			cout << "START" << endl;
			rbt_searchPrintTree(rbt_root_ptr, "AAAAA", true);
			cout << "MID" << endl;
			cout << rbt_searchTree(rbt_root_ptr, "AAAAA")->key << endl;
			cout << "END" << endl;
			*/
			delete[] rbt_test_nodes;
			myRBT->line(print_stuff);


			//system("pause");

			/////////////////// BINARY SEARCH ///////////////////
			/////////////////// BINARY SEARCH ///////////////////
			/////////////////// BINARY SEARCH ///////////////////

			cout << "/////////////////// BINARY SEARCH ///////////////////" << endl;
			tree_type = "BST";

			bst_node* bst_root = new bst_node;

			initializeTimers(
				start_time_construct,
				start_time_insert_key_AVERAGE,
				start_time_insert_key_WORST,
				start_time_search_AVERAGE,
				start_time_search_WORST,
				end_time_construct,
				end_time_insert_key_AVERAGE,
				end_time_insert_key_WORST,
				end_time_search_AVERAGE,
				end_time_search_WORST,
				duration_construct,
				duration_insert_key_AVERAGE,
				duration_insert_key_WORST,
				duration_search_AVERAGE,
				duration_search_WORST,
				start_time_extra,
				end_time_extra,
				duration_time_extra
			);

			myBST->bst_makeTree(
				filename_and_path_in,
				bst_root,
				start_time_construct,
				end_time_construct,
				duration_construct,
				start_time_insert_key_WORST,
				end_time_insert_key_WORST,
				duration_insert_key_WORST,
				start_time_insert_key_AVERAGE,
				end_time_insert_key_AVERAGE,
				duration_insert_key_AVERAGE,
				print_stuff);

			int test_int_bst = 0;
			numberOfInsertions = 0;
			for (int i = 0; i < (numberOfSearches - 1); i++) {
				if (i % 2 == 0) {
					myBST->bst_insert(bst_root, *n[i]);
					numberOfInsertions++;
				}
			}
			myBST->bst_insert(bst_root, *n[numberOfSearches - 1]);
			numberOfInsertions++;

			myBST->line(print_stuff);
			if (print_stuff) {
				cout << "Print in order:" << endl;
			}
			else {
				//cout << "Don't print in order:" << endl;
			}

			if (print_stuff) {
				myBST->bst_printInOrder(bst_root, print_stuff);
			}

			myBST->line(print_stuff);
			//*start_time_search_AVERAGE = clock();

			bst_test_nodes = new bst_node_ptr[numberOfSearches]; // emn

			for (int i = 0; i < numberOfSearches; i++) {
				bst_test_nodes[i] = new bst_node;
			}

			for (int i = 0; i < numberOfSearches; i++) {
				bst_test_nodes[i] = myBST->bst_printSearchPath(
					bst_root,
					*n[i],
					start_time_search_WORST,
					end_time_search_WORST,
					duration_search_WORST,
					start_time_search_AVERAGE,
					end_time_search_AVERAGE,
					duration_search_AVERAGE,
					start_time_extra,
					end_time_extra,
					duration_time_extra,
					print_stuff);
				myBST->line(print_stuff);
			}

			*duration_search_AVERAGE = *duration_search_AVERAGE / numberOfSearches;
			for (int i = 0; i < numberOfSearches; i++) {
				if (print_stuff) {
					myBST->bst_printFound(*n[i], bst_test_nodes[i]);
				}
			}

			myBST->line(print_stuff);
			myBST->printTimesScreen(tree_type, filename_and_path_in, numberOfSearches, *duration_construct, *duration_insert_key_AVERAGE, *duration_insert_key_WORST, *duration_search_AVERAGE, *duration_search_WORST, *duration_time_extra);
			myBST->printTimesFile(fout, tree_type, filename_and_path_out, filename_and_path_in, numberOfSearches, *duration_construct, *duration_insert_key_AVERAGE, *duration_insert_key_WORST, *duration_search_AVERAGE, *duration_search_WORST, *duration_time_extra);

			myBST->line(print_stuff);
			/*
			cout << "START" << endl;
			bst_searchPrintTree(bst_root, "AAAAA", true);
			cout << "MID" << endl;
			cout << bst_searchTree(bst_root, "AAAAA")->key << endl;
			cout << "END" << endl;
			*/
			delete[] bst_test_nodes;
			myBST->line(print_stuff);


			fout.close();
		}
		// grader interact grade
		else if (choice == 'i') {
			// never leave grader interact
			while (1) {

				myGraderChoice = graderSplash();

				line();
				cout << "Searching for: '";
				cout << myGraderChoice->grader_word << "' " << endl;
				cout << "  In the file: ";
				cout << myGraderChoice->grader_file << endl;
				cout << "    Tree type: ";
				cout << myGraderChoice->grader_tree << endl;



				string* filename_and_path_in = new string;
				*filename_and_path_in = myGraderChoice->grader_file;


				filename_out = "AAA_out.txt";

				if (myGraderChoice->grader_tree == "RBT") {
					rbt_node* rbt_root = new rbt_node;
					rbt_root->color = 'b';

					rbt_node* rbt_search_end;

					initializeTimers(
						start_time_construct,
						start_time_insert_key_AVERAGE,
						start_time_insert_key_WORST,
						start_time_search_AVERAGE,
						start_time_search_WORST,
						end_time_construct,
						end_time_insert_key_AVERAGE,
						end_time_insert_key_WORST,
						end_time_search_AVERAGE,
						end_time_search_WORST,
						duration_construct,
						duration_insert_key_AVERAGE,
						duration_insert_key_WORST,
						duration_search_AVERAGE,
						duration_search_WORST,
						start_time_extra,
						end_time_extra,
						duration_time_extra
					);

					myRBT->rbt_makeTree(
						*filename_and_path_in,
						rbt_root,
						start_time_construct,
						end_time_construct,
						duration_construct,
						start_time_insert_key_WORST,
						end_time_insert_key_WORST,
						duration_insert_key_WORST,
						start_time_insert_key_AVERAGE,
						end_time_insert_key_AVERAGE,
						duration_insert_key_AVERAGE,
						print_stuff);


					rbt_search_end = myRBT->rbt_printSearchPath(
						rbt_root,
						myGraderChoice->grader_word,
						start_time_search_WORST,
						end_time_search_WORST,
						duration_search_WORST,
						start_time_search_AVERAGE,
						end_time_search_AVERAGE,
						duration_search_AVERAGE,
						start_time_extra,
						end_time_extra,
						duration_time_extra,
						print_stuff);


					printTimesScreen(
						myGraderChoice->grader_tree,
						*filename_and_path_in,
						1,
						*duration_construct,
						*duration_insert_key_AVERAGE,
						*duration_insert_key_WORST,
						*duration_search_AVERAGE,
						*duration_search_WORST,
						*duration_time_extra
					);

					cout << endl;
					if (rbt_search_end == nullptr) {
						cout << "The word '" << myGraderChoice->grader_word << "' was NOT FOUND." << endl;
						cout << "End value was nullptr." << endl;
					}
					else {
						if (rbt_search_end->key == myGraderChoice->grader_word) {
							cout << "The word '" << rbt_search_end->key << "' was found in the tree." << endl;
						}
						else {
							cout << "The word '" << myGraderChoice->grader_word << "' was NOT FOUND." << endl;
							cout << "End value was not equal." << endl;
						}
					}
					cout << endl;

					delete rbt_search_end;
					delete rbt_root;

				}
				else if (myGraderChoice->grader_tree == "BST") {
					bst_node* bst_root = new bst_node;
					
					bst_node* bst_search_end;

					initializeTimers(
						start_time_construct,
						start_time_insert_key_AVERAGE,
						start_time_insert_key_WORST,
						start_time_search_AVERAGE,
						start_time_search_WORST,
						end_time_construct,
						end_time_insert_key_AVERAGE,
						end_time_insert_key_WORST,
						end_time_search_AVERAGE,
						end_time_search_WORST,
						duration_construct,
						duration_insert_key_AVERAGE,
						duration_insert_key_WORST,
						duration_search_AVERAGE,
						duration_search_WORST,
						start_time_extra,
						end_time_extra,
						duration_time_extra
					);

					myBST->bst_makeTree(
						*filename_and_path_in,
						bst_root,
						start_time_construct,
						end_time_construct,
						duration_construct,
						start_time_insert_key_WORST,
						end_time_insert_key_WORST,
						duration_insert_key_WORST,
						start_time_insert_key_AVERAGE,
						end_time_insert_key_AVERAGE,
						duration_insert_key_AVERAGE,
						print_stuff
					);

					


					bst_search_end = myBST->bst_printSearchPath(
						bst_root, 
						myGraderChoice->grader_word, 
						start_time_search_WORST, 
						end_time_search_WORST, 
						duration_search_WORST, 
						start_time_search_AVERAGE, 
						end_time_search_AVERAGE, 
						duration_search_AVERAGE, 
						start_time_extra, 
						end_time_extra, 
						duration_time_extra, 
						print_stuff);


					printTimesScreen(
						myGraderChoice->grader_tree,
						*filename_and_path_in,
						1, 
						*duration_construct, 
						*duration_insert_key_AVERAGE, 
						*duration_insert_key_WORST, 
						*duration_search_AVERAGE, 
						*duration_search_WORST, 
						*duration_time_extra
					);

					cout << endl;
					if (bst_search_end == nullptr) {
						cout << "The word '" << myGraderChoice->grader_word << "' was NOT FOUND." << endl;
						cout << "End value was nullptr." << endl;
					}
					else {
						if (bst_search_end->key == myGraderChoice->grader_word) {
							cout << "The word '" << bst_search_end->key << "' was found in the tree." << endl;
						}
						else {
							cout << "The word '" << myGraderChoice->grader_word << "' was NOT FOUND." << endl;
							cout << "End value was not equal." << endl;
						}
					}
					cout << endl;
					delete bst_search_end;
					delete bst_root;
				}
				else {
					assert(false);
				}
				
				delete filename_and_path_in;
				delete myGraderChoice;
				myBST->line();
				system("pause");
				cout << endl;

				cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||" << endl;

				cout << endl;
			}
			// never leave grader interact
		}
		// end grader interact grade

		system("pause");
	

	return 0;
}
// C:/Users/secpc/Desktop/wordlists/sorted15K.txt