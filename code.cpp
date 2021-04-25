#include<bits/stdc++.h> 
#include<iostream>

using namespace std; 

#define ll long long int

FILE* openFile(char* fileName, string m) 
{ 	const char * mode=&m[0];
	FILE* fp = fopen(fileName, mode); 

	if (fp == NULL) { 
		perror("Error while opening the file.\n"); 
		exit(EXIT_FAILURE); 
	} 
	return fp; 
}

struct MinHeapNode 
{ 
	ll i; 
    ll key;
}; 

void swap(MinHeapNode* a, MinHeapNode* b) 
{ 
	MinHeapNode temp = *a; 
	*a=*b; 
	*b=temp; 
} 

class MinHeap 
{ 
	MinHeapNode* heap_arr; 
	ll heap_size; 

public: 
    
    MinHeapNode getMin() 
        {
            return heap_arr[0];
        } 
    
    void replaceMin(MinHeapNode x) 
	{ 
		heap_arr[0] = x; 
		MinHeapify(0); 
	}

	void MinHeapify(ll i)
    { 
	ll l=2*i+1; 
	ll r=2*i+2; 
	ll smallest=i; 
	if(heap_arr[l].key<heap_arr[i].key && l<heap_size) 
		smallest=l; 
	if(heap_arr[r].key<heap_arr[smallest].key && r<heap_size) 
		smallest=r; 
	if (i!=smallest) 
        { 
		swap(&heap_arr[i], &heap_arr[smallest]); 
		MinHeapify(smallest); 
	    } 
    }

    MinHeap(MinHeapNode a[], ll size)
    { 
	    heap_arr=a;
	    heap_size=size; 

    	ll x=(heap_size-1)/2; 
	    while(x>= 0) 
		    {
		    	MinHeapify(x);
		    	--x;
		    }

    }
}; 


void merge(ll arr[], ll left, ll mid, ll right) 
{ 
    ll LeftArr[mid-left+1];
    ll RightArr[right-mid]; 

	for(ll i=0;i<=mid-left;++i) 
		LeftArr[i]=arr[i+left]; 
	for(ll j=0;j<right-mid;++j) 
		RightArr[j]=arr[mid+1+j]; 
    
    ll i=0, j=0, k=left;
	while (i<=mid-left && j<right-mid)
    { 
		if (LeftArr[i]<=RightArr[j]) 
			{
                arr[k] = LeftArr[i];
                ++i;
            }
		else
            {
                arr[k] = RightArr[j]; 
                ++j;
            }	
            ++k;
	}

	while (j<right-mid)
        {
            arr[k]=RightArr[j];
            ++k;
            ++j; 
        } 

	while (i<=mid-left) 
		{
            arr[k]=LeftArr[i]; 
            ++k;
            ++i;
        }
		
} 

void mergeSort(ll arr[], ll l, ll r) 
{ 
	if (l < r) { 
		ll m = l+(r-l)/2; 
    	mergeSort(arr,l,m); 
		mergeSort(arr,m+1,r); 
		merge(arr,l,m,r); 
	} 
}  

void mergeFiles(char* output_file, ll n, ll k) 
{ 
	FILE* in[k]; 
	ll i=0;
	ll count = 0; 
    MinHeapNode * heap_arr=new MinHeapNode[k];  
    for(i=0;i<k;++i) 
    {
		char fName[2]; 
    	snprintf(fName,sizeof(fName),"%lld",i); 
    	in[i]=openFile(fName,"r"); 
	}

	FILE* out=openFile(output_file,"w"); //final putput file
	
	for(i=0;i<k;++i) 
    { 
		if(fscanf(in[i],"%lld", &heap_arr[i].key)!=1) 
			break; 
        heap_arr[i].i = i; 
	} 

	MinHeap hp(heap_arr, i); 
	   
	while(count != i)
    {
		MinHeapNode root=hp.getMin(); 
		fprintf(out,"%lld, ",root.key); 
		if(fscanf(in[root.i],",%lld",&root.key)!= 1)
        { 
			root.key=INT_MAX; 
			++count; 
		} 
        hp.replaceMin(root);
	} 

	for(ll i=0;i<k;++i) 
		fclose(in[i]); 

	fclose(out); 
} 

void createInitialRuns( char* input_file,ll run_size,ll partition_count) 
{ 
	FILE* in=openFile(input_file,"r"); 
	FILE* out[partition_count];
	ll i=0;
	char fName[2]; 
	ll* arr=(ll*)malloc(run_size*sizeof(ll)); 
	bool flag=true; 
	ll next_output_file=0; 

    for(i=0;i<partition_count;++i)
    	{ 
		snprintf(fName,sizeof(fName),"%lld",i); 
		out[i]=openFile(fName,"w"); 
	} 	
	while(flag)
	    { 
		for(i=0;i<run_size;++i)
	    { 
			if(fscanf(in,"%lld,",&arr[i])!=1)
		    {
				flag=false; 
				break; 
				} 
			} 

		mergeSort(arr,0,i-1); 
    	
		for(ll j=0;j<i;++j) 
			fprintf(out[next_output_file],"%lld,", arr[j]); 
		
		next_output_file++; 
	} 

	for(i=0;i<partition_count;++i) 
		fclose(out[i]); 

	fclose(in); 
} 

int main() 
{ 	
	ll run_size =1000000; 

	char input_file[30]; 
	std::cin>>input_file;

	char output_file[30]; 
	std::cin>>output_file;


		ifstream  fin(input_file);
        char ch;
        ll i, c=0;
        while(fin)
        {
                fin.get(ch);
                i=ch;
                if(i==44)
                	c++;
        }      
	ll partition_count = 1+ (c+10)/1000000; 

	createInitialRuns(input_file,run_size, partition_count); 
	mergeFiles(output_file, run_size, partition_count); 
	return 0; 
} 
