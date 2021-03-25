#include <iostream>
#include <chrono>
#include <functional>

using Time = std::chrono::steady_clock::time_point;

enum class Sound { Beep, Siren, Whistle };

using Duration = std::chrono::steady_clock::duration;

void setAlarm(Time t, Sound s, Duration d) {
    std::cout << "Setting alarm" << std::endl;
}

enum class Volume { Normal, Loud, LoudPlusPlus };

void setAlarm(Time t, Sound s, Duration d, Volume v) {
    std::cout << "Setting alarm with volume" << std::endl;
}

class Widget {};

enum class CompLevel { Low, Normal, High }; // compression
                                            // level

Widget compress(const Widget& w, // make compressed
                CompLevel lev) { // copy of w

    std::cout << "Make compress copy of w with level: " << lev << std::endl;
}

int main() {
    // Lambda sample
    auto setSoundL =
        [](Sound s)
        {
            // make std::chrono components available w/o qualification
            using namespace std::chrono;
            using namespace std::literals; // for C++14 suffixes
            setAlarm(steady_clock::now() + 1h, // alarm to go off
                s, // in an hour for
                30s); // 30 seconds
        };

    // std::bind sample
    using namespace std::chrono; // as above
    using namespace std::literals;
    using namespace std::placeholders; // needed for use of "_1"


/* Error cant choose version of setAlarm
    auto setSoundB1 = // "B" for "bind"
        std::bind(setAlarm,
                  // This will be evaluated right now
                  steady_clock::now() + 1h, // incorrect! see below
                  _1,
                  30s);
    
    auto setSoundB =
        std::bind(
            setAlarm,
            std::bind(std::plus<>(), steady_clock::now(), 1h),
            _1,
            30s);

    auto setSoundBC11 =
        std::bind(
            setAlarm,
            std::bind(std::plus<steady_clock::time_point>(),
                    steady_clock::now(),
                    hours(1)),
            _1,
            seconds(30));
*/
    using SetAlarm3ParamType = void(*)(Time t, Sound s, Duration d);
        auto setSoundB = // now
            std::bind(
                static_cast<SetAlarm3ParamType>(setAlarm), // okay
                std::bind(
                    std::plus<>(),
                    steady_clock::now(),
                    1h),
                _1,
                30s);

    setSoundL(Sound::Siren); // body of setAlarm may
                             // well be inlined here

    setSoundB(Sound::Siren); // body of setAlarm is less
                             // likely to be inlined here


    // Low/High val sample
    int lowVal = 0, highVal = 10;
    auto betweenL =
        [lowVal, highVal]
        (const auto& val) // C++14
            { return lowVal <= val && val <= highVal; };

    // Mother of god
    using namespace std::placeholders; // as above
    auto betweenB =
        std::bind(std::logical_and<>(), // C++14
            std::bind(std::less_equal<>(), lowVal, _1),
            std::bind(std::less_equal<>(), _1, highVal));

    auto betweenBC11 = // C++11 version
        std::bind(std::logical_and<bool>(),
            std::bind(std::less_equal<int>(), lowVal, _1),
            std::bind(std::less_equal<int>(), _1, highVal));


    // Compress sample
    Widget w;
    using namespace std::placeholders;
    // How w is captured?
    auto compressRateB = std::bind(compress, w, _1);

    auto compressRateL = // w is captured by
        [w](CompLevel lev) // value; lev is
            { return compress(w, lev); }; // passed by value

    compressRateL(CompLevel::High); // arg is passed
                                    // by value

    compressRateB(CompLevel::High); // how is arg
                                    // passed?
}