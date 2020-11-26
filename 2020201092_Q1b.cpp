//longest substring appearing atleast k times

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
    { 
        int rank = 0; 
        int prev_rank = suffixes[0].s[0]; 
        suffixes[0].s[0] = rank; 
        ind[suffixes[0].index] = 0; 
  
        for (int i=1;i<n;++i) 
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
  
        for (int i=0;i<n;++i) 
        { 
            int nextindex=suffixes[i].index + k/2; 
            suffixes[i].s[1] = (nextindex<n) ? suffixes[ind[nextindex]].s[0]: -1; 
        } 
  
        std::sort(suffixes, suffixes+n, cmp); 
    } 
  
    int *suffixArr = new int[n]; 
    for (int i = 0; i < n; i++) 
        suffixArr[i] = suffixes[i].index; 
  
    // Return the suffix array 
    return  suffixArr; 
}

int main()
{
    std::string s;
    std::cin>>s;
    int k;
    std::cin>>k;
    int n=s.length();
    
    int *suffixArr = buildSuffixArray(s,n);
    
    std::string ans="";
	
    for(int i=0;i<1+n-k;i++)
    {
		std::string st="";
		int j=suffixArr[i];
		int l=suffixArr[i+k-1];
		while(s[j]==s[l] && j<n && l<n)
        {
			st=st + s[j];
			l=l+1;
            j=j+1;
		}
		if(ans.size()<st.size())
            ans=st;
	}
	
	if(ans!="")
	    std::cout<<ans.length()<<std::endl;
	else std::cout<<-1<<std::endl;
    return 0;
}