class Solution {
public:
    struct Node {
        int prod;
        long long cnt[5];

        Node() {
            prod = 1;
            for (int i = 0; i < 5; i++)
                cnt[i] = 0;
        }
    };

    int k;

    Node merge(Node &a, Node &b) {
        Node res;

        res.prod = (a.prod * b.prod) % k;

        // Prefixes completely inside left part
        for (int r = 0; r < k; r++)
            res.cnt[r] += a.cnt[r];

        // Left part + prefix of right part
        for (int r = 0; r < k; r++) {
            int newRem = (a.prod * r) % k;
            res.cnt[newRem] += b.cnt[r];
        }

        return res;
    }

    vector<int> resultArray(vector<int>& nums, int K,
                            vector<vector<int>>& queries) {

        k = K;
        int n = nums.size();

        int size = 1;
        while (size < n)
            size *= 2;

        vector<Node> tree(2 * size);

        // Build leaves
        for (int i = 0; i < n; i++) {
            int x = nums[i] % k;

            tree[size + i].prod = x;
            tree[size + i].cnt[x] = 1;
        }

        // Build tree
        for (int i = size - 1; i >= 1; i--)
            tree[i] = merge(tree[i * 2], tree[i * 2 + 1]);

        vector<int> ans;

        for (auto &q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Point update
            int pos = size + index;

            tree[pos] = Node();

            int val = value % k;
            tree[pos].prod = val;
            tree[pos].cnt[val] = 1;

            pos /= 2;

            while (pos >= 1) {
                tree[pos] = merge(tree[pos * 2], tree[pos * 2 + 1]);
                pos /= 2;
            }

            // Query [start, n)
            int l = size + start;
            int r = size + n;

            Node leftResult;
            Node rightResult;

            while (l < r) {
                if (l & 1) {
                    leftResult = merge(leftResult, tree[l]);
                    l++;
                }

                if (r & 1) {
                    --r;
                    rightResult = merge(tree[r], rightResult);
                }

                l /= 2;
                r /= 2;
            }

            Node result = merge(leftResult, rightResult);

            ans.push_back(result.cnt[x]);
        }

        return ans;
    }
};