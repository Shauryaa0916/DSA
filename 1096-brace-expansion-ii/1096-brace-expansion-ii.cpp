class Solution {
public:
    set<string> parse(string &s, int &i) {
        set<string> result;
        set<string> current = {""};

        while (i < s.size() && s[i] != '}') {
            
            if (s[i] == '{') {
                i++; // skip '{'

                set<string> inside;

                while (true) {
                    set<string> part = parse(s, i);

                    inside.insert(part.begin(), part.end());

                    if (s[i] == ',') {
                        i++; // skip ','
                    } else {
                        break;
                    }
                }

                i++; // skip '}'

                // Concatenate current with inside
                set<string> temp;

                for (string a : current) {
                    for (string b : inside) {
                        temp.insert(a + b);
                    }
                }

                current = temp;
            }
            
            else if (s[i] == ',') {
                break;
            }
            
            else {
                // Single lowercase letter
                set<string> temp;

                for (string a : current) {
                    temp.insert(a + s[i]);
                }

                current = temp;
                i++;
            }
        }

        return current;
    }

    vector<string> braceExpansionII(string expression) {
        int i = 0;

        set<string> ans = parse(expression, i);

        return vector<string>(ans.begin(), ans.end());
    }
};