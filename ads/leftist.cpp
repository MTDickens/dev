// Online C++ compiler to run C++ program online
#include <iostream>
#include <algorithm>

using namespace std;

struct LeftistNode;
using NodePtr = LeftistNode*;
struct LeftistNode {
    LeftistNode() = delete;
    LeftistNode(int val) : Left(nullptr), Right(nullptr), Element(val), Npl(0) {}
    NodePtr Left;
    NodePtr Right;
    int Element;
    int Npl;
};

struct PriorityQueue {
    PriorityQueue() : root(nullptr) {}
    NodePtr root;
};

NodePtr merge (NodePtr A, NodePtr B)
{
    if (A == nullptr) return B;
    if (B == nullptr) return A;
    
    if (A->Element > B->Element)
        swap(A, B);
        
    if (A->Left == nullptr) A->Left = B;
    else
    {
        A->Right = merge(A->Right, B);
        if (A->Right->Npl > A->Left->Npl)
            swap(A->Right, A->Left);
        A->Npl = A->Right->Npl + 1;
    }
    
    return A;
}

NodePtr insert (NodePtr node, int v)
{
    NodePtr new_node = new LeftistNode(v);
    return merge(node, new_node);
}

int smallest(PriorityQueue &queue)
{
    return queue.root->Element;
}

int main() {
    PriorityQueue queue;
    
    queue.root = insert(queue.root, 1);
    queue.root = insert(queue.root, 3);
    queue.root = insert(queue.root, 2);
    queue.root = insert(queue.root, 0);
    
    cout << smallest(queue) << '\n';
    return 0;
}