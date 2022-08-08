#include <vector>
#include <iostream>
using namespace std;

// Do not edit the class below except for
// the insert, contains, and remove methods.
// Feel free to add new properties and methods
// to the class.
class BST {
public:
    int value;
    BST* left;
    BST* right;

    BST(int val) {
        value = val;
        left = nullptr;
        right = nullptr;
    }

    BST& insert(int val) {
        // Write your code here.
        // Do not edit the return statement of this method.
        BST* currentNode = this;
        while (true)
        {
            if (val < currentNode->value)
            {
                if (currentNode->left == nullptr)
                {
                    BST* newnode = new BST(val);
                    currentNode->left = newnode;
                    break;
                }
                else
                {
                    currentNode = currentNode->left;
                }

            }
            else
            {
                if (currentNode->right == nullptr)
                {
                    BST* newnode = new BST(val);
                    currentNode->right = newnode;
                    break;
                }

                else
                {
                    currentNode = currentNode->right;
                }
            }

        }

        return *this;
    }

    bool contains(int val) {
        // Write your code here.
        BST* currentNode = this;
        while (currentNode != nullptr)
        {
            if (val < currentNode->value)
            {

                currentNode = currentNode->left;
            }
            else if (val > currentNode->value)
            {
                currentNode = currentNode->right;
            }
            else
            {
                return true;
            }
        }
        return false;
    }

    BST& remove(int val, BST* parentNode = nullptr) {
        // Write your code here.
        // Do not edit the return statement of this method.
        BST* currentNode = this;
        while (currentNode != nullptr)
        {
            if (val < currentNode->value)
            {
                parentNode = currentNode;
                currentNode = currentNode->left;
            }
            else if (val > currentNode->value)
            {
                parentNode = currentNode;
                currentNode = currentNode->right;
            }
            else
            {
                if (currentNode->left != nullptr && currentNode->right != nullptr)
                {
                    currentNode->value = currentNode->right->getMinValue();
                    currentNode->right->remove(currentNode->value, currentNode);
                }
                else if (parentNode == nullptr)
                {
                    if (currentNode->left != nullptr)
                    {
                        currentNode->value = currentNode->left->value;
                        currentNode->right = currentNode->left->right;
                        currentNode->left = currentNode->left->left;
                    }
                    else if (currentNode->right != nullptr)
                    {
                        currentNode->value = currentNode->right->value;
                        currentNode->left = currentNode->right->left;
                        currentNode->right = currentNode->right->right;
                    }
                    else
                    {

                    }
                }
                else if (parentNode->left == currentNode)
                {
                    parentNode->left = currentNode->left != nullptr ? currentNode->left : currentNode->right;
                }
                else if (parentNode->right == currentNode)
                {
                    parentNode->right = currentNode->left != nullptr ? currentNode->left : currentNode->right;
                }
                break;
            }
        }
        return *this;
    }

    int getMinValue()
    {
        if (left == nullptr)return value;
        else
        {
            return left->getMinValue();
        }
    }
};

struct Trunk
{
    Trunk* prev;
    string str;

    Trunk(Trunk* prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
};

void showTrunks(Trunk* p);
void printTree(BST* root, Trunk* prev, bool isLeft);

int main()
{
    BST* root = new BST(10);
    root->left = new BST(5);
    root->left->left = new BST(2);
    root->left->left->left = new BST(1);
    root->left->right = new BST(5);
    root->right = new BST(15);
    root->right->left = new BST(13);
    root->right->left->right = new BST(14);
    root->right->right = new BST(22);

    root->insert(12);
    printTree(root, nullptr, false);

    root->remove(10);
    printTree(root, nullptr, false);

    cout << boolalpha << root->contains(10) << " ";
    return 0;
}



void showTrunks(Trunk* p)
{
    if (p == nullptr) {
        return;
    }

    showTrunks(p->prev);
    cout << p->str;
}

void printTree(BST* root, Trunk* prev, bool isLeft)
{
    if (root == nullptr) {
        return;
    }

    string prev_str = "    ";
    Trunk* trunk = new Trunk(prev, prev_str);

    printTree(root->right, trunk, true);

    if (!prev) {
        trunk->str = "---";
    }
    else if (isLeft)
    {
        trunk->str = ".---";
        prev_str = "   |";
    }
    else {
        trunk->str = "`---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout << " " << root->value << endl;

    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";

    printTree(root->left, trunk, false);
}