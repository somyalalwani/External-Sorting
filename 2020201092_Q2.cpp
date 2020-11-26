#include<iostream>
#include<bits/stdc++.h> 
using namespace std; 
  
struct TrieNode 
{ 
    TrieNode* child[2]; 
}; 
    
TrieNode* newTrieNode() 
{ 
    TrieNode* temp=new TrieNode; 

    temp->child[0]=NULL; 
    temp->child[1]=NULL;   
return temp; 
} 
  
void insert(TrieNode* root, int x) 
{ 
    TrieNode* temp=root; 

    int i=63;
    while(i--) 
    { 
        int f=(bool)(x & (1<<i)); 
        if (!temp->child[f]) 
            temp->child[f] = newTrieNode(); 
  
        temp=temp->child[f]; 
    }
} 

int max_xor(TrieNode *root,int x) 
{ 
    TrieNode* temp=root; 
    int ans=0,i=31; 

    while(i--)
    { 
        int f=(bool)(x & (1<<i));
        int y=bool(f^1);
        if (temp->child[y] == NULL) 
            temp=temp->child[f]; 
        else
        {
            temp=temp->child[y]; 
            ans+=(1<<i);
        }  
    }   
return ans; 
} 

int main() {

    int n,q;
    std::cin>>n>>q;

    TrieNode* root = newTrieNode();
    for (int i=0;i<n;i++)
    { int x;
        std::cin>>x;
        insert(root,x);
    }
    
    vector<int> ans;    
    while(q--)
    {   
        int x;
        cin>>x;
        ans.push_back(max_xor(root,x));
    }
    for (auto i:ans)
        cout<<i<<endl;
    return 0;
}