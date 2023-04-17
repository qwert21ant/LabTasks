#pragma once

#include <iostream>
#include <iomanip>

using namespace std;

struct Node;

int input();

int* fill_arr(int size);

void create_root(Node*& root, int val);

void add_value(Node* root, int val);

Node* create_tree(int* data, int size);

int count_depth(Node* node);

void out_gap(int depth, int total_depth);

void out_off(int depth, int total_depth);

void print_tree(Node* root);

int count_branches(Node* node, int depth);

void solve(Node* root);