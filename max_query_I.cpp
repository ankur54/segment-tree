#include <bits/stdc++.h>
using namespace std;

void buildTree(int arr[], int s, int e, pair<int, int> tree[], int idx) {
    if(s > e) return;
    if(s == e) {
        tree[idx] = {arr[s], arr[s]};
        return;
    }

    int mid = (s + e) >> 1;
    buildTree(arr, s, mid, tree, 2*idx);
    buildTree(arr, mid + 1, e, tree, 2*idx + 1);
    tree[idx] = {min(tree[2*idx].first, tree[2*idx + 1].first), 
            max(tree[2*idx].second, tree[2*idx + 1].second)};
}

int maxQuery(pair<int, int> tree[], int ss, int se, int qs, int qe, int k, int idx) {
    if(ss > qe || se < qs) return 0;
    if(ss == se) {
        if(tree[idx].first >= k) return 1;
        return 0;
    } 
    if(qs <= ss && qe >= se) {
        if(tree[idx].first >= k) return (se - ss + 1);
        if(tree[idx].second < k) return 0;
    } 

    int mid = (ss + se) >> 1;
    return maxQuery(tree, ss, mid, qs, qe, k, 2*idx) + maxQuery(tree, mid + 1, se, qs, qe, k, 2*idx + 1); 
}

int main(int argc, char const *argv[])
{
    int n, q;
    cin >> n;
    int arr[n];
    pair<int, int> tree[4*n + 1];
    for(int i = 0; i < n; i++) cin >> arr[i];
    buildTree(arr, 0, n-1, tree, 1);
        
    cin >> q;
    while(q--) {
        int l, r, k;
        cin >> l >> r >> k;
        cout << maxQuery(tree, 0, n-1, l - 1, r - 1, k, 1) << endl;
    }
    return 0;
}
