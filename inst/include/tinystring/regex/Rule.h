#pragma once

#include <cstddef>
#include <functional>

#include "State.h"


class Rule {
    std::shared_ptr<State> start_;
    std::shared_ptr<State> end_;
    std::function<bool(const std::byte&)> predicate_;
    bool is_epsilon_;

public:
    Rule(const std::shared_ptr<State>& start,
        const std::shared_ptr<State>& end,
        const std::function<bool(const std::byte &)> &predicate);
    Rule(const std::shared_ptr<State>& start,
        const std::shared_ptr<State>& end,
        const std::function<bool(const std::byte &)> &predicate,
        bool is_epsilon);

    [[nodiscard]] bool match(const std::byte& letter) const;
    [[nodiscard]] bool is_epsilon() const;

    [[nodiscard]] std::shared_ptr<State> start() const;
    [[nodiscard]] std::shared_ptr<State> end() const;
    [[nodiscard]] const char* label() const;
};

inline Rule::Rule(const std::shared_ptr<State>& start, const std::shared_ptr<State>& end, const std::function<bool(const std::byte &)> &predicate)
    : Rule(start, end, predicate, false) {}

inline Rule::Rule(const std::shared_ptr<State>& start, const std::shared_ptr<State>& end, const std::function<bool(const std::byte &)> &predicate, bool is_epsilon)
    : start_(start), end_(end), predicate_(predicate), is_epsilon_(is_epsilon) {}

inline bool Rule::match(const std::byte& letter) const {
    return predicate_(letter);
}

inline bool Rule::is_epsilon() const {
    return is_epsilon_;
}

inline std::shared_ptr<State> Rule::start() const {
    return start_;
}

inline std::shared_ptr<State> Rule::end() const {
    return end_;
}
