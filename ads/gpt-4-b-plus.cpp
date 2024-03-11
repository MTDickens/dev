#include <iostream>
#include <vector>
#include <algorithm>
#include <initializer_list>
#include <queue>

#define DEGREE 3

class BPlusTreeNode
{
public:
    bool isLeaf;
    std::vector<int> keys;
    std::vector<BPlusTreeNode *> childPtrs;
    BPlusTreeNode *parent;
    BPlusTreeNode *next;
    BPlusTreeNode *prev;

    BPlusTreeNode(bool isLeaf = false) : isLeaf(isLeaf), parent(nullptr), next(nullptr), prev(nullptr) {}
};

template <typename T, int degree>
class BPlusTree
{
private:
    BPlusTreeNode *root;

    BPlusTreeNode *findLeafNode(T key)
    {
        BPlusTreeNode *node = root;
        while (!node->isLeaf)
        {
            for (int i = 0; i < node->keys.size(); i++)
            {
                if (key < node->keys[i])
                {
                    node = node->childPtrs[i];
                    break;
                }
                if (i == node->keys.size() - 1) // the key is bigger than the biggest key of the node
                {
                    node = node->childPtrs[i + 1];
                    break;
                }
            }
        }
        return node;
    }

    void splitLeafNode(BPlusTreeNode *node)
    {
        /**
         * If degree == 4,
         * [1 2 3 4 5] -> [1 2] [3 4 5]
         */
        int mid = (degree + 1) / 2;
        BPlusTreeNode *rightNode = new BPlusTreeNode(true);
        rightNode->keys.assign(node->keys.begin() + mid, node->keys.end());
        node->keys.erase(node->keys.begin() + mid, node->keys.end());

        /**
         * If this node has no parent, it means that it's the root itself
         * So you have to make a new root
         */
        if (!node->parent)
        {
            BPlusTreeNode *newRoot = new BPlusTreeNode();
            newRoot->keys.push_back(rightNode->keys[0]);
            newRoot->childPtrs.push_back(node);
            newRoot->childPtrs.push_back(rightNode);
            node->parent = rightNode->parent = newRoot;
            root = newRoot;
            return;
        }

        /**
         * Otherwise, you have to deal with its parent, i.e. add the rightNode->keys[0] to its parent
         */
        BPlusTreeNode *parent = node->parent;
        int index = std::upper_bound(parent->keys.begin(), parent->keys.end(), rightNode->keys[0]) - parent->keys.begin();
        parent->keys.insert(parent->keys.begin() + index, rightNode->keys[0]);
        parent->childPtrs.insert(parent->childPtrs.begin() + index + 1, rightNode);
        rightNode->parent = parent;

        /**
         * If its parent has more than `degree - 1` keys, i.e. more than `degree` pointers
         * you have to split the parent
         */
        if (parent->keys.size() > degree - 1)
        {
            splitInternalNode(parent);
        }
    }

    void splitInternalNode(BPlusTreeNode *node)
    {
        /**
         * Assigns half of childPtrs to the left
         */
        int mid = (degree - 1) / 2;
        int mid_val = node->keys[mid];
        BPlusTreeNode *rightNode = new BPlusTreeNode();
        rightNode->keys.assign(node->keys.begin() + mid + 1, node->keys.end());
        rightNode->childPtrs.assign(node->childPtrs.begin() + mid + 1, node->childPtrs.end());
        node->keys.erase(node->keys.begin() + mid, node->keys.end());
        node->childPtrs.erase(node->childPtrs.begin() + mid + 1, node->childPtrs.end());

        /**
         * Change the parent of all right node's children to right node
         */
        for (auto &child : rightNode->childPtrs)
        {
            child->parent = rightNode;
        }

        /**
         * If this node has no parent, it means that it's the root itself
         * So you have to make a new root
         */
        if (!node->parent)
        {
            BPlusTreeNode *newRoot = new BPlusTreeNode();
            newRoot->keys.push_back(mid_val);
            newRoot->childPtrs.push_back(node);
            newRoot->childPtrs.push_back(rightNode);
            node->parent = rightNode->parent = newRoot;
            root = newRoot;
            return;
        }

        /**
         * Otherwise, you have to deal with its parent, i.e. add the mid_val to its parent
         *
         * i.e. (degree == 4, mid = (4 - 1) / 2 = 1): [1 2 3 4] -> [... 2 ...]
         *                                                         [1] [3 4]
         */
        BPlusTreeNode *parent = node->parent;
        int index = std::upper_bound(parent->keys.begin(), parent->keys.end(), mid_val) - parent->keys.begin();
        parent->keys.insert(parent->keys.begin() + index, mid_val);
        parent->childPtrs.insert(parent->childPtrs.begin() + index + 1, rightNode);
        rightNode->parent = parent;

        /**
         * If its parent has more than `degree - 1` keys, i.e. more than `degree` pointers
         * you have to split the parent
         */
        if (parent->keys.size() > degree - 1)
        {
            splitInternalNode(parent);
        }
    }

public:
    BPlusTree() : root(new BPlusTreeNode(true)) {}

    void insert(T key)
    {
        BPlusTreeNode *leafNode = findLeafNode(key);
        int index = std::upper_bound(leafNode->keys.begin(), leafNode->keys.end(), key) - leafNode->keys.begin();
        if (index > 0 && leafNode->keys[index - 1] == key)
        {
            std::cout << "Key " << key << " is duplicated\n";
            return;
        }
        leafNode->keys.insert(leafNode->keys.begin() + index, key);

        if (leafNode->keys.size() > degree)
        {
            splitLeafNode(leafNode);
        }
    }

    void insert(std::initializer_list<int> list)
    {
        for (auto i : list)
            this->insert(i);
    }

    void draw_tree()
    {
        std::queue<BPlusTreeNode *> nodesQueue;
        int nodesInCurrentLevel = 1;
        int nodesInNextLevel = 0;
        nodesQueue.push(root);
        while (!nodesQueue.empty())
        {
            BPlusTreeNode *currentNode = nodesQueue.front();
            nodesQueue.pop();
            nodesInCurrentLevel--;
            if (currentNode)
            {
                std::cout << "[";
                for (int i = 0; i < currentNode->keys.size(); i++)
                {
                    std::cout << currentNode->keys[i];
                    if (i < currentNode->keys.size() - 1)
                    {
                        std::cout << ",";
                    }
                }
                std::cout << "]";
                if (!currentNode->isLeaf)
                {
                    for (int i = 0; i < currentNode->childPtrs.size(); i++)
                    {
                        nodesQueue.push(currentNode->childPtrs[i]);
                        nodesInNextLevel++;
                    }
                }
            }
            if (nodesInCurrentLevel == 0)
            {
                std::cout << std::endl;
                nodesInCurrentLevel = nodesInNextLevel;
                nodesInNextLevel = 0;
            }
        }
    }
};

int main()
{
    BPlusTree<int, DEGREE> bpt;

    // I/O
    int n;
    std::cin >> n;
    for (int i = 0; i != n; ++i)
    {
        int temp;
        std::cin >> temp;
        bpt.insert(temp);
    }
    bpt.draw_tree();
    return 0;
}