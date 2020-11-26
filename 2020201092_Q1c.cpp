//longest substring palindrome

#include<iostream>
#include<bits/stdc++.h>
#include<string>

struct suffix
{
    int index;
    int s[2];
};

int cmp(struct suffix a,struct suffix b) 
{ int temp=0;
if (a.s[0]==b.s[0])
{
temp=(a.s[1]<b.s[1]?1:0);
}
else temp=(a.s[0]<b.s[0] ?1: 0);
return temp; 
} 

int * buildSuffixArray(std::string text, int n) 
{ 
    struct suffix suffixes[n]; 
  
    for (int i=0;i<n;++i) 
    { 
        suffixes[i].index = i; 
        suffixes[i].s[0] = text[i] - 'a'; 
        suffixes[i].s[1] = ((i+1) < n)? (text[i + 1] - 'a'): -1; 
    }   
    std::sort(suffixes, suffixes+n, cmp); 
    int ind[n]; 
    for(int k=4;k<2*n;k*=2) 
    {   int i=0;
        int rank = 0; 
        int prev_rank = suffixes[0].s[0]; 
        suffixes[0].s[0] = rank; 
        ind[suffixes[0].index] = 0; 
  
        for (i=1;i<n;++i) 
        { 
            if (suffixes[i].s[0]==prev_rank && suffixes[i].s[1] == suffixes[i-1].s[1]) 
            { 
                prev_rank = suffixes[i].s[0]; 
                suffixes[i].s[0] = rank; 
            } 
            else
            { 
                prev_rank=suffixes[i].s[0];
                ++rank; 
                suffixes[i].s[0]=rank; 
            } 

            ind[suffixes[i].index] = i; 
        } 
        for (i=0;i<n;++i) 
        { 
            int nextindex=suffixes[i].index + k/2; 
            suffixes[i].s[1] = (nextindex<n) ? suffixes[ind[nextindex]].s[0]: -1; 
        } 
        std::sort(suffixes, suffixes+n, cmp); 
    }   
    int *suffixArr = new int[n]; 
    for (int i = 0; i < n; i++) 
        suffixArr[i] = suffixes[i].index; 
    return  suffixArr; 
}

int * lcp_funct(std::string txt, int * suffixArr, int n) 
{ 
    int *lcp= new int[n]; 
    int *invSuffixArr = new int[n]; 
    for(int i=0;i<n;++i) 
        invSuffixArr[suffixArr[i]] = i; 
  
    int k = 0; 
    
    for(int i=0;i<n;++i) 
    { 
        if (invSuffixArr[i]==n-1) 
        { 
            k = 0; 
            continue; 
        } 
        int j = suffixArr[invSuffixArr[i]+1]; 
        while ((j+k<n && i+k<n) && txt[i+k]==txt[j+k]) 
            ++k; 
  
        lcp[invSuffixArr[i]]=k;
        if (k>0) 
            --k; 
        } 
return lcp; 
} 
int main()
{
    std::string s;
    std::cin>>s;
    //="banana";
    int initial_length=s.length();
    std::string rev_string = std::string(s.rbegin(),s.rend());
    std::string st= s+ '$' + rev_string;

    std::cout<<st<<std::endl;
    int n=st.length();
    std::cout<<"n="<<n<<std::endl;
    
    int *suffixArr = buildSuffixArray(st,n);
    int *lcp=lcp_funct(st,suffixArr,n);
    
for(int i=0;i<n;i++)
std::cout<<lcp[i]<<" ";
std::cout<<std::endl;

  std::string ans;
  int longestLength=0, pos=0;

  for(int i=1;i<n;++i)
  {
      if(lcp[i]>longestLength)
      {
          if((suffixArr[i-1]<initial_length) && (suffixArr[i]>initial_length) 
       ||((suffixArr[i]<initial_length) && (suffixArr[i-1]>initial_length)))
            { 
                longestLength=lcp[i]; 
                pos=suffixArr[i]; 
            } 
      
      }

  }
  
  std::cout<<"Longest length="<<longestLength<<std::endl;
    for(int i=pos;i<pos+longestLength;++i)
    std::cout<<st[i];
    std::cout<<std::endl;  
    return 0;
}