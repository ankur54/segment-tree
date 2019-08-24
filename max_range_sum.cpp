#include <bits/stdc++.h>
using namespace std;

typedef struct node {
    int prefSum, sufSum, totalSum, maxSum;
} Node;

void buildTree(int arr[], int s, int e, Node tree[], int idx) {
    if(s > e) return;
    if(s == e) {
        tree[idx] = {arr[s], arr[s], arr[s], arr[s]};
        return;
    }

    int mid = (s + e) >> 1;
    buildTree(arr, s, mid, tree, 2*idx);
    buildTree(arr, mid + 1, e, tree, 2*idx + 1);
    tree[idx].prefSum = max(tree[2*idx].prefSum, tree[2*idx].totalSum + tree[2*idx + 1].prefSum);
    tree[idx].sufSum = max(tree[2*idx + 1].sufSum, tree[2*idx + 1].totalSum + tree[2*idx].sufSum);
    tree[idx].totalSum = tree[2*idx].totalSum + tree[2*idx + 1].totalSum;
    tree[idx].maxSum = max(tree[idx].totalSum, max(tree[idx].sufSum, tree[idx].prefSum));
}

Node queryTreeUtil(Node tree[], int ss, int se, int qs, int qe, int idx) {
    if(ss > qe || qs > se) return { 0, 0, 0, 0 };
    if(ss >= qs && qe >= se) return tree[idx];

    int mid = (ss + se) >> 1;
    Node leftAns = queryTreeUtil(tree, ss, mid, qs, qe, 2*idx);
    Node rightAns = queryTreeUtil(tree, mid + 1, se, qs, qe, 2*idx + 1);
    int prefSum = max(leftAns.prefSum, leftAns.totalSum + rightAns.prefSum);
    int sufSum = max(rightAns.sufSum, rightAns.totalSum + leftAns.sufSum);
    int totalSum = leftAns.totalSum + rightAns.totalSum;
    int maxSum = max(totalSum, max(sufSum, prefSum));
    return {prefSum, sufSum, totalSum, maxSum};
}

int queryTree(Node tree[], int n, int qs, int qe) {
    return queryTreeUtil(tree, 0, n-1, qs, qe, 1).maxSum;
}

int main(int argc, char const *argv[])
{
    int arr[] = {4, 5, -8, 1, 3};
    int n = 5;
    Node tree[4*n + 1];
    buildTree(arr, 0, n-1, tree, 1);
    // for(int i = 1; i <= 9; i++) cout << tree[i].prefSum << " " << tree[i].sufSum << " " << tree[i].totalSum << " " << tree[i].maxSum << endl;
    // cout << endl; 

    int q;
    cin >> q;
    while(q--) {
        int l, r;
        cin >> l >> r;
        cout << queryTree(tree, n, l, r) << endl;
    }
    return 0;
}
