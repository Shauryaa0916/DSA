class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> mp;

        // Store key-value pairs
        for (auto &k : knowledge) {
            mp[k[0]] = k[1];
        }

        string ans = "";

        for (int i = 0; i < s.size(); ) {
            if (s[i] == '(') {
                int j = i + 1;

                // Find closing bracket
                while (s[j] != ')') {
                    j++;
                }

                // Extract key
                string key = s.substr(i + 1, j - i - 1);

                // Replace with value or '?'
                if (mp.find(key) != mp.end()) {
                    ans += mp[key];
                } else {
                    ans += "?";
                }

                // Move after ')'
                i = j + 1;
            } 
            else {
                ans += s[i];
                i++;
            }
        }

        return ans;
    }
};