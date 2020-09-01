# MAST
The exercise is to implement an algorithm that reads a set of n rooted trees in the NEWICK format, and then for each of n(n-1)/2 pairs of trees will calculate the minimum number of leaves whose removal from both trees will make them isomorphic. The problem is known in IT as Maximum agreement subtree problem .


The trees should be saved in the computer's memory in the form of general trees, using one pointer per son, one per brother and one per parent. Such trees are described in lecture 5. Search trees.. The figure below shows such a general representation of both trees. 
The pointers (arrows) down are the relation son and to the right is the relation brother. Pointers directed up (the relation parent) are not drawn in the first figure for the sake of clarity. You can see them in the second drawing. Remembered that every node - except root - has such pointer.

n2 solution (100%)
We are creating internal vertices identifiers for the trees visible above (they do not have to be letter-number combinations as in the example, they can simply be consecutive numbers larger than those assigned to leaves). Remember that these trees are represented all the time using general tree notation - the figure below uses "normal trees" just to improve readability.  
We create a square array where, each dimension contains a representation of all vertices (outer - leaves and inner) of one tree. We first fill in this array by inserting ones for all the leaves of one and then the other tree. Only one label is associated with a given leaf. If the leaf or the inner vertex of the other tree has a leaf with a corresponding label, then type 1 otherwise 0. The most important part of the algorithm begins when comparing the inner vertices of one tree with another. First of all, it should be done in the right order: reverse Breadth-first_search or Post-order. Three cases should be considered for each pair and the one with the highest score should be selected. We assume that we compare two internal vertices of AX with Bx:
one of the sons of the AX node can be identified with the BX node
AX node can be identified as one of the sons of the BX node
identify the sons of the AX node with the sons of the BX node (not necessarily all) so that the sum of identical nodes is as large as possible
Subpoint 3 can be implemented with a brute force algorithm, browsing the full space of possible solutions and selecting the best result. When completing the comparison of the two roots we should get the final result, which is our |l|, please note that as the result we send the value: n-|l|.

You cannot use stl, algorithm and similar libraries in the program. Generally, please use only iostream or stdio and possibly string.

Input
The value of n denotes the size of the set of n rooted trees.
n rooted trees in NEWICK format.
Output
n(n-1)/2 comparisons of input trees (each with each). The order of comparison: 1-2, 1-3, ..., 1-n, 2-3, 2-4, ..., 2-n, ..., (n-1) -n.
Example
Input
4
(1,5,(10,6,3),(2,(8,7)),(9,4));
((7,(3,(4,9,(1,2)))),8,(5,(10,6)));
(7,((6,(9,5),(8,3)),(1,(2,10,4))));
(7,(8,3,4,6,1),(9,5,10),2);

Output
5
7
6
6
6
6
