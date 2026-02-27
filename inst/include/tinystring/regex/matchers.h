#pragma once

#include "State.h"
#include "Rule.h"
#include "Graph.h"
#include "epsilon.h"


inline Graph match_letter(const std::byte& letter) {
    const std::shared_ptr<State> start{};
    const std::shared_ptr<State> end{};
    const Rule predicate(start, end, [letter](const std::byte& l) -> bool {
        return l == letter;
    });
    const std::vector<Rule> rules{predicate};
    return Graph{start, end, rules};
}

inline Graph match_any() {
    const std::shared_ptr<State> start{};
    const std::shared_ptr<State> end{};
    const Rule predicate(start, end, [](const std::byte& l) -> bool {
        return true;
    });
    const std::vector<Rule> rules{predicate};
    return Graph{start, end, rules};
}

inline Graph zero_or_more(const Graph& subject) {
    const std::shared_ptr<State> start{};
    const std::shared_ptr<State> end{};

    const Rule predicate_skip(start, end, EPSILON);
    const Rule predicate_init(start, subject.start(), EPSILON);
    const Rule predicate_finalize(subject.end(), end, EPSILON);
    const Rule predicate_loop(subject.end(), subject.start(), EPSILON);

    std::vector<Rule> rules{predicate_skip, predicate_init, predicate_finalize, predicate_loop};
    rules.reserve(rules.size() + subject.rules().size());
    rules.insert(rules.end(), subject.rules().begin(), subject.rules().end());

    return Graph{start, end, rules};
}

inline Graph one_or_more(const Graph& subject) {
    const std::shared_ptr<State> start{};
    const std::shared_ptr<State> end{};

    const Rule predicate_init(start, subject.start(), EPSILON);
    const Rule predicate_finalize(subject.end(), end, EPSILON);
    const Rule predicate_loop(subject.end(), subject.start(), EPSILON);

    std::vector<Rule> rules{predicate_init, predicate_finalize, predicate_loop};
    rules.reserve(rules.size() + subject.rules().size());
    rules.insert(rules.end(), subject.rules().begin(), subject.rules().end());

    return Graph{start, end, rules};
}

inline Graph concat(const Graph& left, const Graph& right) {
    const Rule predicate_line(left.end(), right.start(), EPSILON);

    std::vector<Rule> rules{predicate_line};
    rules.reserve(rules.size() + left.rules().size() + right.rules().size());
    rules.insert(rules.end(), left.rules().begin(), left.rules().end());
    rules.insert(rules.end(), right.rules().begin(), right.rules().begin());

    return Graph{left.start(), right.end(), rules};
}
