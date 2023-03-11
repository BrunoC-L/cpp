#pragma once

#include <coroutine>
#include <exception>

template <typename T, typename O>
struct Generator {
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;
    using value_type = T;
    
    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;
    Generator(Generator&& other) {
        *this = std::move(other);
    }
    Generator& operator=(Generator&& other) {
        h_ = other.h_;
        other.h_ = {};
        full_ = other.full_;
        other.full_ = false;
        return *this;
    }

    struct promise_type // required
    {
        T value_{};
        std::exception_ptr exception_{};

        Generator get_return_object() {
            return Generator(handle_type::from_promise(*this));
        }
        std::suspend_always initial_suspend() {
            return {};
        }
        std::suspend_always final_suspend() noexcept {
            return {};
        }
        void unhandled_exception() {
            exception_ = std::current_exception();
        }

        template <std::convertible_to<T> From>
        std::suspend_always yield_value(From&& from) {
            value_ = std::forward<From>(from);
            return {};
        }
        void return_void() { }
    };

    handle_type h_;

    Generator(handle_type h) : h_(h) { }

    ~Generator() {
        if (h_.address()) {// will be nullptr after move
            h_.destroy();
            h_ = {};
        }
    }
    explicit operator bool() {
        fill();
        return !h_.done();
    }
    T operator()() {
        fill();
        full_ = false;
        return std::move(h_.promise().value_);
    }

private:
    bool full_ = false;

    void fill() {
        if (!full_) {
            h_();
            if (h_.promise().exception_)
                std::rethrow_exception(h_.promise().exception_);
            full_ = true;
        }
    }
};
