#define BOOST_TEST_MODULE CombinerTest
#include <boost/test/unit_test.hpp>

#include <Sx/Signals/Signal.hpp>

struct Fixture : public Sx::Signals::Observer
{
    int minValue() const
    {
        return -1;
    }
    int middleValue() const
    {
        return 0;
    }
    int maxValue() const
    {
        return 1;
    }
};

BOOST_AUTO_TEST_CASE(LastCombiner)
{
    Sx::Signals::Signal<int(), Sx::Signals::LastValue> signal;
    Fixture                                            f;

    signal.connect<&Fixture::minValue>(f);
    signal.connect<&Fixture::middleValue>(f);
    signal.connect<&Fixture::maxValue>(f);

    int ret = signal();
    BOOST_TEST(ret == 1);
}

BOOST_AUTO_TEST_CASE(MinCombiner)
{
    Sx::Signals::Signal<int(), Sx::Signals::MinValue> signal;
    Fixture                                           f;

    signal.connect<&Fixture::minValue>(f);
    signal.connect<&Fixture::middleValue>(f);
    signal.connect<&Fixture::maxValue>(f);

    int ret = signal();
    BOOST_TEST(ret == -1);
}

BOOST_AUTO_TEST_CASE(MaxCombiner)
{
    Sx::Signals::Signal<int(), Sx::Signals::MaxValue> signal;
    Fixture                                           f;

    signal.connect<&Fixture::minValue>(f);
    signal.connect<&Fixture::middleValue>(f);
    signal.connect<&Fixture::maxValue>(f);

    int ret = signal();
    BOOST_TEST(ret == 1);
}

BOOST_AUTO_TEST_CASE(AllCombiner)
{
    Sx::Signals::Signal<int(), Sx::Signals::AllValues> signal;
    std::vector<int>                                   expected {-1, 0, 1};
    Fixture                                            f;

    signal.connect<&Fixture::minValue>(f);
    signal.connect<&Fixture::middleValue>(f);
    signal.connect<&Fixture::maxValue>(f);

    auto ret = signal();
    BOOST_TEST(ret == expected);
}
