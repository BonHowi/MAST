#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
using namespace std;
class Node {
private:
        Node * father;
        Node * nextbrother;
        Node * son;
        int v;
public:
        Node() {
                v = 0;
                son = father = nextbrother = NULL;
        }
        Node * getFather() {
                return father;
        }
        Node * getBrother() {
                return nextbrother;
        }
        Node * getSon(){
                return son;
        }
        int getValue() {
                return v;
        }
        void setFather(Node * father) {
                this->father = father;
                return;
        }
        void setBrother(Node * brother) {
                this->nextbrother = brother;
                return;
        }
        void setSon(Node * son) {
                this->son = son;
                return;
        }
        void setValue(int v) {
                this->v = v;
        }


};

class Tree {
private:
        Node * root;

public:
        int size;
        int leaves_number;
        Node * getRoot() {
                return root;
        }
        void setRoot(Node * root) {
                this->root = root;      
        }
        Node * _findNode(Node * akt,int i) { // DFS
                if (akt->getValue() == i) {
                        return akt;
                }
                Node * s = akt->getSon();
                while (s != NULL) {
                        Node * returned = _findNode(s, i);
                        if (returned != NULL)return returned;
                        s = s->getBrother();
                }
                return NULL;
        }
        Node * findNode(int i) {
                return _findNode(this->root, i);
        }
        void _fillValues(Node * akt, int * v) {
                if (akt->getValue() == 0) {
                        akt->setValue(*v);
                        (*v)++;
                }
                Node * s = akt->getSon();
                while (s != NULL) {
                        _fillValues(s, v);
                        s = s->getBrother();
                }
        }
        void fillValues() {
                int tmp = leaves_number + 1;
                _fillValues(this->root, &tmp);
        }

};

class CombinationsGenerator {
public:
        int n;
        int k;
        int *generated_values;
        bool * used;
        int place;
        int curr_size = 0;
        int ** all;
        int size = 0;
        bool first = true;
        int curr_taken = 0;
        CombinationsGenerator(int k, int n) {
                this->k = k;
                this->n = n;
                this->generated_values = new int[k];
                this->used = new bool[n];

                this->curr_size = 0;
                this->size = s(n) / s(n - k) / s(k);
                this->all = new int*[this->size];
                for (int i = 0; i < this->size; i++) {
                        this->all[i] = new int[k];
                }
                this->init();
                this->gen(0);
                this->reset();
        }

        void gen(int d) {
                if (d == k) {
                        for (int i = 0; i < k; i++) {
                                all[curr_size][i] = generated_values[i];
                        }
                        curr_size++;
                        return;
                }
                int last;
                if (d == 0) {
                        last = 0;
                }
                else last = generated_values[d - 1]+1;
                for (int i = last; i < n; i++) {
                        if (used[i] == 0) {

                                used[i] = 1;
                                generated_values[d] = i;
                                gen(d + 1);
                                used[i] = 0;
                        }
                }
        } 
        void init() {

                for (int i = 0; i < n; i++) {
                        used[i] = 0;
                }
                for (int i = 0; i < k; i++) {
                        generated_values[i] = 0;
                }
                first = true;
        }

        int s(int n) {
                if (n <= 1)return 1;
                return n * s(n - 1);
        }
        int * next() {
                if (curr_taken >= size)return NULL;
                return all[this->curr_taken++];
        }
        void reset() {
                curr_taken = 0;
        }
        ~CombinationsGenerator() {
                delete[] generated_values;
                delete[] used;
                for (int i = 0; i < this->size; i++) {
                        delete[] all[i];
                }
                delete[] all;
        }


};

class VariationsGenerator {
public:
        int n;
        int k;
        int *generated_values;
        bool * used;
        int size;
        int ** all;
        int curr_size = 0;
        int curr_taken = 0;

        VariationsGenerator(int k, int n) {
                this->k = k;
                this->n = n;
                this->generated_values = new int[k];
                this->used = new bool[n];
                this->size = s(n) / s(n - k);
                this->all = new int*[size];
                this->curr_size = 0;
                for (int i = 0; i < this->size; i++) {
                        this->all[i] = new int[k];
                }
                this->init();
                gen(0);
        }
        void gen(int d) {
                if (d == k) {
                        for (int i = 0; i < k; i++) {
                                all[curr_size][i] = generated_values[i];
                        }
                        curr_size++;
                        return;
                }
                for (int i = 0; i < n; i++) {
                        if (used[i] == 0) {

                                used[i] = 1;
                                generated_values[d] = i;
                                gen(d + 1);
                                used[i] = 0;
                        }
                }
        }
        int s(int n) {
                if (n <= 1)return 1;
                return n * s(n - 1);
        }
        void init() {
                for (int i = 0; i < n; i++) {
                        used[i] = 0;
                }
                for (int i = 0; i < k; i++) {
                        generated_values[i] = i;
                }
        }
        void reset() {
                curr_taken = 0;
        }
        int * next() {
                if (curr_taken >= size)return NULL;
                return all[curr_taken++];
        }
        ~VariationsGenerator() {
                delete[] generated_values;
                delete[] used;
                for (int i = 0; i < this->size; i++) {
                        delete[] all[i];
                }
                delete[] all;
        }


};


int main() {

        int tree_num;
        scanf("%d", &tree_num);
        Tree * trees = new Tree[tree_num];
        for (int i = 0; i < tree_num; i++) {
                char sign = ' ';
                trees[i].setRoot(new Node());
                Node * akt = trees[i].getRoot();
                int leaves = 0;
                int vertex = 1;
                while (sign != ';') {
                        int tmp;
                        if (scanf("%d", &tmp) == 1) {
                                akt->setValue(tmp);
                                leaves++;
                                continue;
                        }
                        scanf("%c", &sign);
                        switch (sign) {
                        case '(':
                                akt->setSon(new Node());
                                akt->getSon()->setFather(akt);
                                akt = akt->getSon();
                                vertex++;
                                break;
                        case ',':
                                akt->setBrother(new Node());
                                akt->getBrother()->setFather(akt->getFather());
                                akt = akt->getBrother();
                                vertex++;
                                break;
                        case ')':
                                akt = akt->getFather();
                                break;
                        }

                }
                trees[i].leaves_number = leaves;
                trees[i].size = vertex;
                trees[i].fillValues();
        }
        for(int c1 = 0;c1<tree_num;c1++){
                for(int c2 = c1+1;c2<tree_num;c2++){

        Tree tree_1 = trees[c1];
        Tree tree_2 = trees[c2];

        int ** arr = new int*[tree_1.size + 1];
        for (int i = 0; i <= tree_1.size; i++) {
                arr[i] = new int[tree_2.size + 1];
                for (int j = 0; j <= tree_2.size; j++) {
                        arr[i][j] = 0;
                }
        }
        for (int i = 1; i <= tree_1.leaves_number; i++) {
                arr[i][i] = 1;
        }
        for (int i = tree_1.size; i > tree_1.leaves_number; i--) {
                Node * akt = tree_1.findNode(i);
                akt = akt->getSon();
                while (akt != NULL) {
                        for (int j = 1; j <= tree_1.leaves_number; j++) {
                                if (arr[akt->getValue()][j] == 1) {
                                        arr[i][j] = 1;
                                }
                        }
                        akt = akt->getBrother();
                }
        }
        for (int i = tree_2.size; i > tree_2.leaves_number; i--) {
                Node * akt = tree_2.findNode(i);
                akt = akt->getSon();
                while (akt != NULL) {
                        for (int j = 1; j <= tree_2.leaves_number; j++) {
                                if (arr[j][akt->getValue()] == 1) {
                                        arr[j][i] = 1;
                                }
                        }
                        akt = akt->getBrother();
                }
        }

        for (int i = tree_1.size; i > tree_1.leaves_number; i--) {
                for (int j = tree_2.size; j > tree_2.leaves_number; j--) {
                        int ** sons_matching = new int*[tree_1.leaves_number];
                        for (int k = 0; k < tree_1.leaves_number; k++) {
                                sons_matching[k] = new int[tree_2.leaves_number];
                        }
                        int si, sj;
                        si = 0;
                        Node * akt1 = tree_1.findNode(i);
                        Node * akt2 = tree_2.findNode(j);

                        for (Node * son1 = akt1->getSon(); son1 != NULL; son1 = son1->getBrother()) {
                                sj = 0;
                                for (Node * son2 = akt2->getSon(); son2 != NULL; son2 = son2->getBrother()) {

                                        sons_matching[si][sj] = arr[son1->getValue()][son2->getValue()];
                                        //cout << sons_matching[si][sj] << " ";
                                        sj++;
                                }
                                //cout << endl;
                                si++;
                        }
                        int lesser = si < sj ? si : sj;
                        CombinationsGenerator comb_gen(lesser, si);
                        VariationsGenerator var_gen(lesser, sj);
                        int * comb;
                        int * var;
                        comb_gen.reset();
                        comb = comb_gen.next();
                        int mx = 0;
                        for (; comb != NULL;) {
                                var_gen.reset();
                                var = var_gen.next();
                                for (; var != NULL;) {
                                        int s = 0;
                                        for (int h = 0; h < lesser; h++) {
                                                s += sons_matching[comb[h]][var[h]];
                                        }
                                        //cout << s << endl;
                                        if (s > mx)mx = s;
                                        var = var_gen.next();
                                }

                                comb = comb_gen.next();
                        }
                        for (Node * son1 = akt1->getSon(); son1 != NULL; son1 = son1->getBrother()) {
                                if (mx < arr[son1->getValue()][j]) {
                                        mx = arr[son1->getValue()][j];
                                }
                        }
                        for (Node * son2 = akt2->getSon(); son2 != NULL; son2 = son2->getBrother()) {
                                if (mx < arr[i][son2->getValue()]) {
                                        mx = arr[i][son2->getValue()];
                                }
                        }
                        arr[i][j] = mx;
                        for (int k = 0; k < tree_1.leaves_number; k++) {
                                delete[] sons_matching[k];
                        }
                        delete[] sons_matching;
                        
                }
        }
        cout << tree_1.leaves_number - arr[tree_1.leaves_number + 1][tree_2.leaves_number + 1] << endl;
        for (int k = 0; k < tree_1.size; k++) {
                delete[] arr[k];
        }
        delete[] arr;

        /*for (int i = 1; i <= tree_1.size - 1; i++) {
                for (int j = 1; j <= tree_2.size - 1; j++) {
                        cout << arr[i][j];
                }
                cout << endl;
        }*/

}}

        return 0;
}
