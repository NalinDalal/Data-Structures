#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Node {
  int x, y, sz;
  Node *left, *right;
  Node(int x) : x(x), y(rng()), sz(1), left(nullptr), right(nullptr) {}
};

int sz(Node *t) { return t ? t->sz : 0; }

void upd(Node *t) {
  if (t)
    t->sz = 1 + sz(t->left) + sz(t->right);
}

// Split by key: left has keys < x, right has keys >= x
pair<Node *, Node *> split(Node *t, int x) {
  if (!t)
    return {nullptr, nullptr};
  if (t->x < x) {
    auto [l, r] = split(t->right, x);
    t->right = l;
    upd(t);
    return {t, r};
  } else {
    auto [l, r] = split(t->left, x);
    t->left = r;
    upd(t);
    return {l, t};
  }
}

// Merge: all keys in l < all keys in r
Node *merge(Node *l, Node *r) {
  if (!l)
    return r;
  if (!r)
    return l;
  if (l->y > r->y) {
    l->right = merge(l->right, r);
    upd(l);
    return l;
  } else {
    r->left = merge(l, r->left);
    upd(r);
    return r;
  }
}

// Insert key x
Node *insert(Node *t, int x) {
  auto [l, r] = split(t, x);
  Node *nd = new Node(x);
  return merge(merge(l, nd), r);
}

// Delete key x
Node *erase(Node *t, int x) {
  auto [l, tmp] = split(t, x);
  auto [m, r] = split(tmp, x + 1);
  delete m;
  return merge(l, r);
}

// Get k-th element (1-indexed)
int get(Node *t, int k) {
  int leftSz = sz(t->left);
  if (k == leftSz + 1)
    return t->x;
  if (k <= leftSz)
    return get(t->left, k);
  return get(t->right, k - leftSz - 1);
}
