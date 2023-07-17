/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
    private:
        queue<TreeNode*> q;
        string serializeNumber(TreeNode *node){
            if(node == nullptr){
                return "null";
            }
            
            int n = node->val;

            string number = "";
            if(node->val < 0) {
                number += '-';
            }
            if(node->val == 0)
                return "0";
            
            while(abs(node->val)){
                number += abs(node->val) % 10 + 48;
                node->val /= 10;
            }
            //cout << number << endl;
            if(n < 0)
                reverse(number.begin() + 1, number.end());
            else
                reverse(number.begin(), number.end());
            
            cout << number << endl;
            return number;
        }
    
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string serialized = "";
        if(root == nullptr){
            return "null";
        }
        q.push(root);
   
        while(!q.empty()){
            if(q.front() != nullptr){
                if(q.front()->left != nullptr){
                    q.push(q.front()->left);
                }
                else{
                    q.push(nullptr);
                }
                if(q.front()->right != nullptr){
                    q.push(q.front()->right);
                }
                else{
                    q.push(nullptr);
                }
            }
            serialized += serializeNumber(q.front());
            serialized += ",";
            q.pop();
        }
        
        //cout << serialized << endl;
        int index;
        for(int i = 0 ; i < serialized.size(); i++){
            if(serialized[i] >= '0' && serialized[i] <= '9'){
                index = i;
            }
        }
        
        serialized.erase(index + 1, serialized.size() - 1 - index + 1);
        
        //cout << serialized;
        
        return serialized;
    }
    
    int deserializeNumber(string str){
        //cout << str << endl;
        bool negative = false;
        if(str[0] == '-'){
            negative = true;
        }
        int number = 0;
        int i = 0;
        if(negative){
            i += 1;
        }
        for(i ; i < str.size(); i++){
            number *= 10;
            number += str[i] - 48;
        }
        if(negative == true){
            number *= -1; 
        }
        //cout << number << endl;
        return number;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
      // cout << data << endl;
        if(data == "null"){
            return nullptr;
        }
        queue<TreeNode*> q;
        vector<int>v;
        //q.push(new TreeNode())
        int start = 0;
        int end = 0;
        for(int i = 0 ; i < data.size(); i++){
            if(data[i] == 'n'){
                start = i + 4;
                i += 3;
                v.push_back(5000);
            }
            if(data[i] == ','){
                end = i - 1;
                if(start != i){
                    //cout << data.substr(start, i - start) << endl;
                    v.push_back(deserializeNumber(data.substr(start, i - start)));
                }
                start = i + 1;

            }

        }
        
        v.push_back(deserializeNumber(data.substr(start, data.size() - start)));

        
        /*for(int j = 0 ; j < v.size(); j++){
            cout << v[j] << endl;
        }*/
        TreeNode *root = new TreeNode(v[0]);
        q.push(root);
        int k = 1;
        
        while(!q.empty() && k < v.size()){
            TreeNode *node = q.front();
            q.pop();
            if(node != nullptr){
                if(v[k] == 5000)
                    node->left = nullptr;
                else{
                    node->left = new TreeNode(v[k]);
                    q.push(node->left);
                }
                    k += 1;

                if(k < v.size()){
                    if(v[k] == 5000)
                        node->right = nullptr;
                    else{
                        node->right = new TreeNode(v[k]);
                        q.push(node->right);
                    }

                    k += 1;
                }
            }
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
