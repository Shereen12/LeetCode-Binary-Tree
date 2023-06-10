/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
    private:
        queue<Node*>q;
public:
    Node* connect(Node* root) {
        if(root == nullptr) {
            return nullptr;
        }
        q.push(root);
        while(!q.empty()) {
            int size = q.size();
            while(size){
                Node *currentNode = q.front();
                q.pop();
                if(size > 1)
                    currentNode->next = q.front();
                else currentNode->next = nullptr;
                if(currentNode->left != nullptr)
                    q.push(currentNode->left);
                if(currentNode->right != nullptr)
                    q.push(currentNode->right);
                --size;
            }
        }
        
        
        return root;
    }
};
