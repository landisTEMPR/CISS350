#ifndef INTMAXHEAP_H
#define INTMAXHEAP_H

#include <iostream>
#include <vector>

std::ostream & operator<<(std::ostream &, const std::vector< int > &);

void maxheap_insert(std::vector< int > & h, int x);
int  maxheap_delete(std::vector< int > & h);
int  maxheap_max(const std::vector< int > & h);
void maxheap_heapify_down(std::vector< int > & h, int i);
void maxheap_heapify_up(std::vector< int > & h, int i);
void maxheap_build(std::vector< int > & h);
void maxheap_heapsort(std::vector< int > & h);

#endif
