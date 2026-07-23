# Centroid Decomposition

## Overview
Centroid Decomposition is a tree algorithm that recursively breaks down a tree by finding and removing centroids, creating a decomposition tree of height O(log n).

## Key Idea
- A centroid is a node whose removal splits the tree into components each with size ≤ n/2
- Every tree has at most 2 centroids
- Recursively find centroids to decompose the tree

## Finding Centroid
1. Start from any node, compute subtree sizes
2. Move to the child with size > n/2 if it exists
3. That node is the centroid

## Pseudocode
```cpp
// Find centroid of tree rooted at u
int findCentroid(int u, int parent, int treeSize) {
    for (int v : adj[u]) {
        if (v != parent && !removed[v]) {
            if (subtreeSize[v] > treeSize / 2)
                return findCentroid(v, u, treeSize);
        }
    }
    return u; // u is centroid
}

// Decompose the tree
void decompose(int u, int parentCentroid) {
    computeSubtreeSizes(u, -1);
    int centroid = findCentroid(u, -1, subtreeSize[u]);
    
    removed[centroid] = true;
    decomposeTree[centroid] = parentCentroid; // build decomposition tree
    
    for (int v : adj[centroid]) {
        if (!removed[v])
            decompose(v, centroid);
    }
}
```

## Applications
- Path queries between all pairs
- Distance-based queries
- Tree matching problems
- Solving problems with O(n log n) using divide and conquer on trees

## Complexity
- Decomposition: O(n log n)
- Each level processes O(n) nodes, O(log n) levels total
