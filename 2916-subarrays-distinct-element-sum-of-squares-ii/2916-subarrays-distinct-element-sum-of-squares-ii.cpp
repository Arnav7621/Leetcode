
class Solution {
public:
    static const int MOD = 1e9 + 7;

    struct Node {
        long long sum = 0, sq = 0, lazy = 0;
    };

    vector<Node> tree;
    int n;

    void apply(int p, int l, int r, long long v) {
        long long len = r - l + 1;
        tree[p].sq = (tree[p].sq + 2 * v * tree[p].sum + v * v % MOD * len) % MOD;
        tree[p].sum = (tree[p].sum + v * len) % MOD;
        tree[p].lazy = (tree[p].lazy + v) % MOD;
    }

    void push(int p, int l, int r) {
        if (!tree[p].lazy || l == r) return;
        int m = (l + r) / 2;
        apply(p * 2, l, m, tree[p].lazy);
        apply(p * 2 + 1, m + 1, r, tree[p].lazy);
        tree[p].lazy = 0;
    }

    void update(int p, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            apply(p, l, r, 1);
            return;
        }
        push(p, l, r);
        int m = (l + r) / 2;
        update(p * 2, l, m, ql, qr);
        update(p * 2 + 1, m + 1, r, ql, qr);
        tree[p].sum = (tree[p * 2].sum + tree[p * 2 + 1].sum) % MOD;
        tree[p].sq = (tree[p * 2].sq + tree[p * 2 + 1].sq) % MOD;
    }

    int sumCounts(vector<int>& nums) {
        n = nums.size();
        tree.assign(4 * n, Node());
        vector<int> last(100001, -1);
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            update(1, 0, n - 1, last[nums[i]] + 1, i);
            ans = (ans + tree[1].sq) % MOD;
            last[nums[i]] = i;
        }
        return ans;
    }
};
