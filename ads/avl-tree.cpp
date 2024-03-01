#include <iostream>

#define LEFT -1
#define RIGHT 1
#define COUNT 10

using namespace std;

// Classes

template <typename T>
class avl_node
{
public:
    avl_node() : father(nullptr) {}
    avl_node(int val, avl_node<T> *father, int fa_dir) : height(1), val(val), left(nullptr), right(nullptr), father(father), fa_dir(fa_dir) {}

    int l_height();
    int r_height();
    int diff_height();
    bool is_satisfy_avl_property();
    void update_height();

    void add_val(T val);
    void zig();
    void zag();

    int height;
    T val;
    avl_node<T> *left, *right, *father; // root's father is senitel, senitel's father is nullptr
    int fa_dir;                         // if it's left child, then LEFT; if it's right child, then RIGHT
};

// Other functions

template <typename T>
avl_node<T> *make_avl_tree()
{
    return new avl_node<T>;
}

template <typename T>
bool is_sentinel(avl_node<T> *node)
{
    return node != nullptr && node->father == nullptr;
}

/**
 * Member functions
 */

// Height functions

template <typename T>
int avl_node<T>::l_height()
{
    if (this->left == nullptr)
        return 0;
    else
        return this->left->height;
}

template <typename T>
int avl_node<T>::r_height()
{
    if (this->right == nullptr)
        return 0;
    else
        return this->right->height;
}

template <typename T>
void avl_node<T>::update_height()
{
    this->height = max(this->l_height(), this->r_height()) + 1;
}

// l_height - r_height
template <typename T>
int avl_node<T>::diff_height()
{
    return this->l_height() - this->r_height();
}

template <typename T>
bool avl_node<T>::is_satisfy_avl_property()
{
    int diff = this->diff_height();
    return diff >= -1 && diff <= 1;
}

// Twist functions

template <typename T>
void avl_node<T>::zig()
{
    auto original_father = this->father;
    auto original_left_right = this->left->right;

    if (this->fa_dir == LEFT)
    {
        this->father->left = this->left;
    }
    else if (this->fa_dir == RIGHT)
    {
        this->father->right = this->left;
    }
    this->father = this->left;

    if (this->left->right != nullptr)
    {
        this->left->right->father = this;
    }
    this->left->right = this;

    this->left->father = original_father;
    this->left = original_left_right;

    // update height
    this->update_height();
    this->father->update_height();

    // update father direction
    this->father->fa_dir = this->fa_dir;
    this->fa_dir = RIGHT;
}

template <typename T>
void avl_node<T>::zag()
{
    auto original_father = this->father;
    auto original_right_left = this->right->left;

    if (this->fa_dir == LEFT)
    {
        this->father->left = this->right;
    }
    else if (this->fa_dir == RIGHT)
    {
        this->father->right = this->right;
    }
    this->father = this->right;

    if (this->right->left != nullptr)
    {
        this->right->left->father = this;
    }
    this->right->left = this;

    this->right->father = original_father;
    this->right = original_right_left;

    // update height
    this->update_height();
    this->father->update_height();

    // update father direction
    this->father->fa_dir = this->fa_dir;
    this->fa_dir = LEFT;
}

// Add function

template <typename T>
void avl_node<T>::add_val(T val)
{
    avl_node<T> *cur_node = this;

    /**
     * Add the node
     */
    while (true)
    {
        // Error check
        if (cur_node == nullptr)
        {
            return;
        }

        // Iteratively compare values
        if (cur_node->val == val) // Same value, thus duplicated, don't add
        {
            return;
        }
        else if (cur_node->val > val)
        {
            if (cur_node->left == nullptr) // Insert here
            {
                cur_node->left = new avl_node<T>(val, cur_node, LEFT);
                break;
            }
            else // continue
            {
                cur_node = cur_node->left;
            }
        }
        else // (cur_node->val < val)
        {
            if (cur_node->right == nullptr) // Insert here
            {
                cur_node->right = new avl_node<T>(val, cur_node, RIGHT);
                break;
            }
            else // Continue
            {
                cur_node = cur_node->right;
            }
        }
    }

    /**
     * Adjust the node
     */
    while (!is_sentinel(cur_node))
    {
        // since we have added a node, we have to update all the height of the nodes on the path
        cur_node->update_height();

        if (cur_node->is_satisfy_avl_property())
        {
            cur_node = cur_node->father;
            continue;
        }

        /**
         * Now that cur_node doesn't satisfy AVL property, we have to make a "twist"
         */
        if (cur_node->diff_height() < 0) // R
        {
            if (cur_node->right->diff_height() <= 0) // RR
            {
                cur_node->zag();
                cur_node = cur_node->father->father;
            }
            else // RL
            {
                cur_node->right->zig();
                cur_node->zag();
                cur_node = cur_node->father->father;
            }
        }
        else // cur_node->diff_height() > 0: L
        {
            if (cur_node->left->diff_height() > 0) // LL
            {
                cur_node->zig();
                cur_node = cur_node->father->father;
            }
            else // LR
            {
                cur_node->left->zag();
                cur_node->zig();
                cur_node = cur_node->father->father;
            }
        }
    }
}

// print tree
template <typename T>
void print2DUtil(avl_node<T> *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    cout << endl;
    for (int i = COUNT; i < space; i++)
        cout << " ";
    cout << root->val << "(" << root->l_height() << "," << root->r_height() << "," << root->height << ")"
         << "\n";

    // Process left child
    print2DUtil(root->left, space);
}

// check tree
// print tree
template <typename T>
void check_tree(avl_node<T> *root)
{
    if (root->left != nullptr)
    {
        if (root->left->father != root)
        {
            cerr << "Error: " << root->val << "-" << root->left->val << " is not father-leftchild, the child's father is " << root->left->father->val << '\n';
        }
        check_tree(root->left);
    }
    if (root->right != nullptr)
    {
        if (root->right->father != root)
        {
            cerr << "Error: " << root->val << "-" << root->right->val << " is not father-rightchild, the child's father is " << root->right->father->val << '\n';
        }
        check_tree(root->right);
    }
}

// Wrapper over print2DUtil()
template <typename T>
void print2D(avl_node<T> *root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

// main function

int main()
{
    avl_node<int> *tree = new avl_node<int>;

    int op_num;
    cin >> op_num;
    for (int i = 0; i != op_num; ++i)
    {
        int val;
        cin >> val;
        if (tree->left == nullptr) // if the tree is empty
        {
            tree->left = new avl_node<int>(val, tree, LEFT); // always add on left
        }
        else
        {
            tree->left->add_val(val);
        }
    }

#ifdef PRINT
    print2D(tree->left);
#endif
#ifdef CHECK
    check_tree(tree->left);
#endif
    cout << tree->left->val;

    return 0;
}