

#ifndef TIMESTAMP_H
#define TIMESTAMP_H



#include <chrono>



namespace zxc_net {
  //  using std::chrono::system_clock;
  //  using namespace std::literals::chrono_literals;
	
	using std::chrono::system_clock;
	using namespace std::literals::chrono_literals;
	
	
	
//				typedef ratio<1, 1000000000> nano;
//				using nanoseconds = duration<long long, nano>;

///				using nanoseconds =  duration<long long, ratio<1, 1000000000> >;
typedef std::chrono::nanoseconds   Nanosecond;    // 当加上一个数字 即就是period = -->就变为了一段时间;
typedef std::chrono::microseconds  Microsecond;
typedef std::chrono::milliseconds  Millisecond;
typedef std::chrono::seconds       Second;
typedef std::chrono::minutes       Minute;
typedef std::chrono::hours         Hour;
	
	
	typedef std::chrono::time_point<system_clock, Nanosecond>   Timestamp;

		//system_clock::time_point;
		//std::chrono::time_point<system_clock>    pp;
	
	
	namespace clock
{

		inline Timestamp now()
		 { return system_clock::now(); }

		inline Timestamp nowAfter(Nanosecond interval)
		 { return now() + interval; }

		inline Timestamp nowBefore(Nanosecond interval)
		 { return now() - interval; }

}
	
	
template <typename T>
struct IntervalTypeCheckImpl
{
    static constexpr bool value =
            std::is_same<T, Nanosecond>::value ||
            std::is_same<T, Microsecond>::value ||
            std::is_same<T, Millisecond>::value ||
            std::is_same<T, Second>::value ||
            std::is_same<T, Minute>::value ||
            std::is_same<T, Hour>::value;
};

#define IntervalTypeCheck(T) \
    static_assert(IntervalTypeCheckImpl<T>::value, "bad interval type")

	
	
	
}


#endif

