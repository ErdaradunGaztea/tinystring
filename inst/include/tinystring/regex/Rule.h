#pragma once

#include <cstddef>
#include <functional>

#include "State.h"
#include "epsilon.h"


class Rule {
    std::shared_ptr<State> start_;
    std::shared_ptr<State> end_;
    std::function<bool(const std::byte&)> predicate_;

public:
    Rule(const std::shared_ptr<State>& start, const std::shared_ptr<State>& end, const std::function<bool(const std::byte &)> &predicate);

    [[nodiscard]] bool match(const std::byte& letter) const;
    [[nodiscard]] bool is_epsilon() const;

    [[nodiscard]] std::shared_ptr<State> start() const;
    [[nodiscard]] std::shared_ptr<State> end() const;
};

inline Rule::Rule(const std::shared_ptr<State>& start, const std::shared_ptr<State>& end, const std::function<bool(const std::byte&)> &predicate)
    : start_(start), end_(end), predicate_(predicate) {}

inline bool Rule::match(const std::byte& letter) const {
    return predicate_(letter);
}

inline bool Rule::is_epsilon() const {
    // Comparing references instead of functions themselves, as it's all we really need
    return &predicate_ == &EPSILON;
}

inline std::shared_ptr<State> Rule::start() const {
    return start_;
}

inline std::shared_ptr<State> Rule::end() const {
    return end_;
}
