#pragma once

#include <limits>
#include <vector>

namespace Sx::Signals {

template <typename T, typename R = T>
struct CombinerBase {
    using ResultType = R;

    virtual bool operator()(const T&) = 0;
    virtual ResultType result() const  = 0;
};

template<>
struct CombinerBase<void> {
    using ResultType = void;
    void result() const {}
};

template <typename T>
class LastValue : public CombinerBase<T> {
  public:
    bool operator()(const T& value) override {
        _result = value;
        return true;
    }

    T result() const override {
        return _result;
    };

  private:
    T _result {};
};

template <>
struct LastValue<void> : public CombinerBase<void> {
};

template <typename T>
class MaxValue : public CombinerBase<T> {
  public:
    bool operator()(const T& value) override {
        if (value > _result)
            _result = value;
        return true;
    }

    T result() const override {
        return _result;
    };

  private:
    T _result = std::numeric_limits<T>::min();
};

template <typename T>
class MinValue : public CombinerBase<T> {
  public:
    bool operator()(const T& value) override {
        if (value < _result)
            _result = value;
        return true;
    }

    T result() const override {
        return _result;
    };

  private:
    T _result = std::numeric_limits<T>::max();
};

template <typename T>
class AllValues : public CombinerBase<T, std::vector<T>> {
  public:
    using ResultType = std::vector<T>;

    bool operator()(const T& value) override {
        _result.push_back(value);
        return true;
    }

    ResultType result() const override {
        return _result;
    };

  private:
    ResultType _result{};
};

}; // namespace Sx::Signals
