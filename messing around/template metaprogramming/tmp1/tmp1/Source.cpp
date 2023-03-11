#include "types.h"

using namespace int_ns::named_values;
using int_ns::Int;
using pair::Pair;
using types::Types;

using equality_ns::equality;

int main() {
	{
		using Empty = Types<>;
		using L = Types<int, int, float, Empty>;

		equality<L::Get<Zero>						, int>;
		equality<L::Contains<float>					, std::true_type>;
		equality<L::IndexOf<float>					, Two>;
		equality<L::Size							, Four>;
		equality<L::Reverse							, Types<Empty, float, int, int>>;
		equality<L::Head							, int>;
		equality<L::Tail							, Empty>;
		equality<L::Index							, Types<Pair<Zero, int>, Pair<One, int>, Pair<Two, float>, Pair<Three, Empty>>>;
		equality<L::Index::Get<Zero>				, Pair<Zero, int>>;
		equality<L::Index::Get<Zero>::Get<One>	, int>;

		equality<L::SplitAtIndex<Zero> , Types<Empty  , Types<int, int, float, Empty>>>;
		equality<L::SplitAtIndex<One>  , Types<Types<int>, Types<int, float, Empty>>>;
		equality<L::SplitAtIndex<Two>  , Types<Types<int, int>, Types<float, Empty>>>;
		equality<L::SplitAtIndex<Three>, Types<Types<int, int, float>, Types<Empty>>>;
		equality<L::SplitAtIndex<Four> , Types<Types<int, int, float, Empty>, Empty  >>;
	}

	{
		using P = Pair<Types<float>, Types<Int<1>>>;

		equality<P::Contains<Types<float>>			, std::true_type>;
		equality<P::IndexOf<Types<float>>           , Zero>;
		equality<P::IndexOf<Types<Int<1>>>          , One>;
	}

}
