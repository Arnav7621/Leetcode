
class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int n = servers.size();
        int m = tasks.size();

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> freeServers;

        priority_queue<tuple<long long,int,int>,
                       vector<tuple<long long,int,int>>,
                       greater<tuple<long long,int,int>>> busyServers;

        for(int i = 0; i < n; i++) {
            freeServers.push({servers[i], i});
        }

        vector<int> ans(m);
        long long currentTime = 0;

        for(int j = 0; j < m; j++) {
            currentTime = max(currentTime, (long long)j);

            while(!busyServers.empty() && get<0>(busyServers.top()) <= currentTime) {
                auto [finish, weight, id] = busyServers.top();
                busyServers.pop();

                freeServers.push({weight, id});
            }

            if(freeServers.empty()) {
                currentTime = get<0>(busyServers.top());

                while(!busyServers.empty() && get<0>(busyServers.top()) <= currentTime) {
                    auto [finish, weight, id] = busyServers.top();
                    busyServers.pop();

                    freeServers.push({weight, id});
                }
            }

            auto [weight, id] = freeServers.top();
            freeServers.pop();

            ans[j] = id;

            busyServers.push({currentTime + tasks[j], weight, id});
        }

        return ans;
    }
};
