#include"huffman.hpp"
#include<queue>

struct compare{
    bool operator()(const Node* a,const Node* b)const
    {
        return a->freq>b->freq;
    }
};

Node* buildHuffmanTree(const std::unordered_map<char,size_t>& freq_map)
{
    std::priority_queue<Node*,std::vector<Node*>,compare> pq;
    for(auto& x:freq_map)
    {
        pq.push(new Node(x.first,x.second));
    }
    while(pq.size()>1)
    {
        Node* l=pq.top();pq.pop();
        Node* r=pq.top();pq.pop();
        Node* parent=new Node('\0',l->freq+r->freq);
        parent->left=l;
        parent->right=r;
        pq.push(parent);
    }
    return pq.top();
}

void buildCode(Node* node,std::vector<bool>& prefix,std::unordered_map<char,std::vector<bool>>& out)
{
    if(!node->left&&!node->right)//reached leaf..
    {
        out[node->character]=prefix;
        return;
    }
    if(node->left)
    {
        prefix.push_back(false);//pushing zero for left edge
        buildCode(node->left,prefix,out);
        prefix.pop_back();//backtrack..
    }
    if(node->right)
    {
        prefix.push_back(true);//pushing 1 for right edge
        buildCode(node->right,prefix,out);
        prefix.pop_back();
    }
}

std::unordered_map<char,std::vector<bool>> generateCodes(Node* root)
{
    std::unordered_map<char, std::vector<bool>> codes;
    std::vector<bool> prefix;
    buildCode(root,prefix,codes);
    return codes;
}