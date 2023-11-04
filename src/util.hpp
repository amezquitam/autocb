#pragma once
#include <stack>

template <typename T>
void clean(std::stack<T> &stack) {
    while (!stack.empty())
        stack.pop();
}