#include <Sx/Signals/Signal.hpp>
#include <boost/signals2.hpp>
#include <chrono>
#include <iostream>
#include <limits>

struct PerfTest {
  static PerfTest& instance() {
    static PerfTest p;
    return p;
  }

  static void static_slot(size_t val) { instance().slot(val); }

  size_t slot(size_t val) const {
    if ((result > val) && ((val % 2) == 0))
      result -= val;
    else
      result += val;
    return result;
  }

  mutable size_t result = 0;
};

using namespace boost::signals2;
using namespace Sx::Signals;
using namespace std::chrono;

void RunPerfTest(size_t count = 1000000000) {
  signal_type<void(size_t), keywords::mutex_type<dummy_mutex> >::type b_signal;
  b_signal.connect(&PerfTest::static_slot);
  high_resolution_clock::time_point b_start = high_resolution_clock::now();
  for (size_t i = 0; i < count; ++i) b_signal(i);
  high_resolution_clock::time_point b_end = high_resolution_clock::now();
  auto b_time = duration_cast<microseconds>(b_end - b_start).count();

  Signal<void(size_t)> o_signal;
  o_signal.connect<&PerfTest::static_slot>();
  high_resolution_clock::time_point o_start = high_resolution_clock::now();
  for (size_t i = 0; i < count; ++i) o_signal(i);
  high_resolution_clock::time_point o_end = high_resolution_clock::now();
  auto o_time = duration_cast<microseconds>(o_end - o_start).count();

  using Callback = void (*)(size_t);
  Callback p_signal = &PerfTest::static_slot;
  high_resolution_clock::time_point p_start = high_resolution_clock::now();
  for (size_t i = 0; i < count; ++i) p_signal(i);
  high_resolution_clock::time_point p_end = high_resolution_clock::now();
  auto p_time = duration_cast<microseconds>(p_end - p_start).count();

  std::cout << "**> Result (MAX)           : "
            << std::numeric_limits<size_t>::max() << std::endl;
  std::cout << "**> Test calls count       : " << count << std::endl;
  std::cout << "**> Boost signal2 duration : " << b_time << std::endl;
  std::cout << "**> Own signal duration    : " << o_time << std::endl;
  std::cout << "**> Plain callback duration: " << p_time << std::endl;
  std::cout << "**> Boost/Plain            : "
            << double(b_time) / double(p_time) << std::endl;
  std::cout << "**> Own/Plain              : "
            << double(o_time) / double(p_time) << std::endl;
  std::cout << "**> Boost/Own              : "
            << double(b_time) / double(o_time) << std::endl;
  std::cout << "**> Result                 : " << PerfTest::instance().result
            << std::endl;
}

int main() {
  RunPerfTest();
  return 0;
}
