#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>


class Trie {
public:
    Trie() = default;
    explicit Trie(const std::vector<std::string> &words);
    void Go(char c);
    std::vector<int> GetTerminates();

private:
    int cur_node = 0;
    std::unordered_set<char> alphabet;
    std::vector<std::unordered_map<char, int>> go = {{}};
    std::vector<std::vector<int>> terminates = {{}};
    std::vector<int> terminate_link = {0};
};

Trie::Trie(const std::vector<std::string> &words) {
    int nodes = 1;

    for (int i = 0; i < words.size(); ++i) {
        int cur = 0;
        for (auto c : words[i]) {
            alphabet.insert(c);
            if (go[cur][c] == 0) {
                go[cur][c] = nodes; // new node
                go.emplace_back();
                terminates.emplace_back();
                ++nodes;
            }
            cur = go[cur][c];
        }

        terminates[cur].push_back(i);
    }

    std::vector<int> suf_link(nodes, 0);
    terminate_link.resize(nodes, 0);

    std::queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        terminate_link[cur] = cur ? (terminates[suf_link[cur]].empty() ? terminate_link[suf_link[cur]] : suf_link[cur]) : 0;
        for (auto i : alphabet) {
            if (go[cur][i]) {
                suf_link[go[cur][i]] = cur ? go[suf_link[cur]][i] : 0;
                q.push(go[cur][i]);
            } else {
                go[cur][i] = cur ? go[suf_link[cur]][i] : 0;
            }
        }
    }
}

void Trie::Go(char c) {
    cur_node = alphabet.count(c) ? go[cur_node][c] : 0;
}

std::vector<int> Trie::GetTerminates() {
    std::vector<int> res = terminates[0];
    int cur = cur_node;
    while (cur) {
        for (auto t : terminates[cur]) {
            res.push_back(t);
        }
        cur = terminate_link[cur];
    }
    return res;
}

int main() {
    Trie pt({"abcd", "abab", "cdab", "abc", "ab"});
    std::string str = "ababxcdabcd";
    for (int i = 0; i < str.size(); ++i) {
        pt.Go(str[i]);
        std::cout << i << ": ";
        for (auto t : pt.GetTerminates()) {
            std::cout << t << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}
