#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

int getMid(int s,int e){
	return (s+(e-s)/2);
}

int max(int a,int b){
	return (a>b)?a:b;
}

int max(int a,int b,int c){
	return max(max(a,b),c);
}

int minVal(int *arr,int a,int b){
	return (arr[a]<arr[b])?a:b;
}

int RMQUtil(int *arr,int *st,int ss,int se,int qs,int qe,int index){
	if(qs<=ss && qe>=se)
		return st[index];
	if(se<qs || ss>qe)
		return -1;
	int m = getMid(ss,se);
	return minVal(arr,RMQUtil(arr,st,ss,m,qs,qe,2*index+1),RMQUtil(arr,st,m+1,se,qs,qe,2*index+2));
}

int RMQ(int *arr,int *st,int n,int qs,int qe){
	if(qs<0 || qe>n-1 || qs>qe)
		return -1;
	return RMQUtil(arr,st,0,n-1,qs,qe,0);
}

int constructSTUtil(int *arr,int *st,int ss,int se,int index){
	if(ss==se){
		st[index] = ss;
		return ss;
	}
	int m = getMid(ss,se);
	st[index] = minVal(arr,constructSTUtil(arr,st,ss,m,2*index+1),constructSTUtil(arr,st,m+1,se,2*index+2));
	return st[index];
}

int *constructST(int *arr,int n){
	int x = (int)(ceil(log2(n))); //Height of segment tree
	int max_size = 2*(int)pow((float)2, x) - 1;
	int *st = new int[max_size];
	constructSTUtil(arr,st,0,n-1,0);
	return st;
}

int getMaxAreaRec(int *arr,int *st,int n,int l,int r){
	if(l>r)
		return -1;
	if(l==r)
		return arr[l];
	int m = RMQ(arr,st,n,l,r);
	return max(getMaxAreaRec(arr,st,n,l,m-1),getMaxAreaRec(arr,st,n,m+1,r),(r-l+1)*arr[m]);
}

int getMaxArea(int *hist, int n){
	int *st = constructST(hist,n);
	return getMaxAreaRec(hist,st,n,0,n-1);
}

int main(){
	int hist[] =  {6, 1, 5, 4, 5, 2, 6};
	int n = sizeof(hist)/sizeof(hist[0]);
	cout << "Maximum area is " << getMaxArea(hist, n);
	return 0;
}