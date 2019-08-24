#include <bits/stdc++.h>
using namespace std;

void buildTree(int arr[], int s, int e, int tree[], int index) {
    if(s > e) return;
    if(s == e) {
        tree[index] = arr[s];
        return;
    }

    int mid = (s+e)>>1;
    buildTree(arr, s, mid, tree, 2*index);
    buildTree(arr, mid+1, e, tree, 2*index + 1);

    tree[index] = max(tree[2*index], tree[2*index + 1]);
}

int queryTree(int tree[], int ss, int se, int qs, int qe, int idx) {
    if(ss > qe || se < qs) return INT_MIN;
    if(ss >= qs && se <= qe) return tree[idx];

    int mid = (ss + se) >> 1;
    return max(queryTree(tree, ss, mid, qs, qe, 2*idx), queryTree(tree, mid + 1, se, qs, qe, 2*idx + 1));
}

void updateTree(int tree[], int ss, int se, int l, int r, int inc, int idx) {
    if(ss > r || se < l) return;
    if(ss == se) {
        tree[idx] += inc;
        return;
    }

    int mid = (ss + se)/2;
    updateTree(tree, ss, mid, l, r, inc, 2*idx);
    updateTree(tree, mid + 1, se, l, r, inc, 2*idx + 1);
    tree[idx] = max(tree[idx*2], tree[2*idx + 1]);
}

int queryTreeLazy(int tree[], int ss, int se, int qs, int qe, int idx, int lazy[]) {
    if(lazy[idx] > 0) {
        tree[idx] += lazy[idx];
        if(ss != se) {
            lazy[2*idx + 1] = lazy[2*idx] += lazy[idx];
            lazy[idx] = 0;
        }
    }

    if(ss > qe || se < qs) return INT_MIN;
    if(ss >= qs && se <= qe) return tree[idx];

    int mid = (ss + se) >> 1;
    return max(queryTreeLazy(tree, ss, mid, qs, qe, 2*idx, lazy), queryTreeLazy(tree, mid + 1, se, qs, qe, 2*idx + 1, lazy));
}

void updateTreeLazy(int tree[], int ss, int se, int l, int r, int inc, int lazy[], int idx) {
    if(lazy[idx] > 0) {
        tree[idx] += lazy[idx];
        if(ss != se) {
            lazy[2*idx + 1] = lazy[2*idx] += lazy[idx];
            lazy[idx] = 0;
        }
    }

    if(ss > r || se < l) return;
    if(ss >= l && se <= r) {
        tree[idx] += inc;
        if(ss != se) lazy[2*idx + 1] = lazy[2*idx] += lazy[idx];
        return;
    }

    int mid = (ss + se)/2;
    updateTreeLazy(tree, ss, mid, l, r, inc, lazy, 2*idx);
    updateTreeLazy(tree, mid + 1, se, l, r, inc, lazy, 2*idx + 1);
    tree[idx] = max(tree[idx*2], tree[2*idx + 1]);
}


int main(int argc, char const *argv[])
{
    int arr[] = {4, 5, 2, 6, 7, 10, 25, 1};
    int n = sizeof(arr)/sizeof(int);
    int tree[4*n+1];
    buildTree(arr, 0, n-1, tree, 1);
    updateTree(tree, 0, n-1, 5, 5, 8, 1);

    for(int i = 1; i <= 15; i++) cout << tree[i] << " ";

    int q;
    cin >> q;
    while(q--) {
        int left, right;
        cin >> left >> right;
        cout << queryTree(tree, 0, n-1, left, right, 1) << endl;
    }
    return 0;
}
