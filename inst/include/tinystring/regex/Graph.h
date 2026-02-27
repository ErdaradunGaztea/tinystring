#pragma once

#include <vector>
#include <unordered_set>

#include "State.h"
#include "Rule.h"


class Graph {
    std::shared_ptr<State> start_;
    std::shared_ptr<State> end_;
    std::vector<Rule> rules_;

public:
    Graph(const std::shared_ptr<State>& start, const std::shared_ptr<State>& end);
    Graph(const std::shared_ptr<State>& start, const std::shared_ptr<State>& end, const std::vector<Rule>& rules);

    bool match(const TinyString& string) const;

    [[nodiscard]] std::shared_ptr<State> start() const;
    [[nodiscard]] std::shared_ptr<State> end() const;
    [[nodiscard]] std::vector<Rule> rules() const;

private:
    std::unordered_set<std::shared_ptr<State>> follow_epsilons(const std::shared_ptr<State>& state) const;
};

inline Graph::Graph(const std::shared_ptr<State> &start, const std::shared_ptr<State> &end)
    : Graph(start, end, std::vector<Rule>()) {}

inline Graph::Graph(const std::shared_ptr<State> &start, const std::shared_ptr<State> &end, const std::vector<Rule>& rules)
    : start_(start), end_(end), rules_(rules) {}

inline bool Graph::match(const TinyString& string) const {
    std::unordered_set<std::shared_ptr<State>> states = follow_epsilons(start_);
    for (const auto& letter : string) {
        std::unordered_set<std::shared_ptr<State>> new_states{};
        for (const auto& rule : rules_) {
            if (states.find(rule.start()) != states.end() and rule.match(letter)) {
                std::unordered_set<std::shared_ptr<State>> to_add = follow_epsilons(rule.end());
                new_states.insert(to_add.begin(), to_add.end());
            }
        }
        states = new_states;
    }
    return states.find(end_) != states.end();
}

inline std::shared_ptr<State> Graph::start() const {
    return start_;
}

inline std::shared_ptr<State> Graph::end() const {
    return end_;
}

inline std::vector<Rule> Graph::rules() const {
    return rules_;
}

inline std::unordered_set<std::shared_ptr<State>> Graph::follow_epsilons(const std::shared_ptr<State>& state) const {
    std::unordered_set<std::shared_ptr<State>> resolved{state};
    for (const auto& rule : rules_) {
        if (rule.is_epsilon() and rule.start() == state) {
            const std::unordered_set<std::shared_ptr<State>> to_add = follow_epsilons(rule.end());
            resolved.insert(to_add.begin(), to_add.end());
        }
    }
    return resolved;
}
