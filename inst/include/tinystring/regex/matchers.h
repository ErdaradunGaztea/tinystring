#pragma once

#include <vector>

#include "State.h"
#include "Rule.h"
#include "Graph.h"
#include "epsilon.h"


inline Graph match_letter(const std::byte& letter) {
    const auto start = std::make_shared<State>();
    const auto end = std::make_shared<State>();
    const Rule predicate(start, end, [letter](const std::byte& l) -> bool {
        return l == letter;
    });
    const std::vector<Rule> rules{predicate};
    return Graph{start, end, rules};
}

inline Graph match_any() {
    const auto start = std::make_shared<State>();
    const auto end = std::make_shared<State>();
    const Rule predicate(start, end, [](const std::byte& l) -> bool {
        return true;
    });
    const std::vector<Rule> rules{predicate};
    return Graph{start, end, rules};
}

inline Graph zero_or_more(const Graph& subject) {
    const auto start = std::make_shared<State>();
    const auto end = std::make_shared<State>();

    const Rule predicate_skip(start, end, EPSILON, true);
    const Rule predicate_init(start, subject.start(), EPSILON, true);
    const Rule predicate_finalize(subject.end(), end, EPSILON, true);
    const Rule predicate_loop(subject.end(), subject.start(), EPSILON, true);

    std::vector<Rule> rules{predicate_skip, predicate_init, predicate_finalize, predicate_loop};
    rules.reserve(rules.size() + subject.rules().size());
    rules.insert(rules.cend(), subject.rules().cbegin(), subject.rules().cend());

    return Graph{start, end, rules};
}

inline Graph one_or_more(const Graph& subject) {
    const auto start = std::make_shared<State>();
    const auto end = std::make_shared<State>();

    const Rule predicate_init(start, subject.start(), EPSILON, true);
    const Rule predicate_finalize(subject.end(), end, EPSILON, true);
    const Rule predicate_loop(subject.end(), subject.start(), EPSILON, true);

    std::vector<Rule> rules{predicate_init, predicate_finalize, predicate_loop};
    rules.reserve(rules.size() + subject.rules().size());
    rules.insert(rules.cend(), subject.rules().cbegin(), subject.rules().cend());

    return Graph{start, end, rules};
}

inline Graph concat(const Graph& left, const Graph& right) {
    const Rule predicate_line(left.end(), right.start(), EPSILON, true);

    std::vector<Rule> rules{predicate_line};
    rules.reserve(rules.size() + left.rules().size() + right.rules().size());
    rules.insert(rules.cend(), left.rules().cbegin(), left.rules().cend());
    rules.insert(rules.cend(), right.rules().cbegin(), right.rules().cend());

    return Graph{left.start(), right.end(), rules};
}
