#include <iostream>
#include <type_traits>
#include <string>

#include <UTemplate/List/TemplateList.h>
#include <UTemplate/Name.h>

using namespace std;
using namespace Ubpa;

template<typename = void>
struct A {
	template<typename = void>
	struct Double {
		string name = "AA";
	};
	string name = "A";
};

template<typename = void>
struct B {
	template<typename = void>
	struct Double {
		string name = "BB";
	};
	string name = "B";
};

template<typename = void>
struct C {
	template<typename = void>
	struct Double {
		string name = "CC";
	};
	string name = "C";
};

template<typename = void>
struct D {
	template<typename = void>
	struct Double {
		string name = "DD";
	};
	string name = "D";
};

template<>
struct Name<TemplateList<>> {
	friend std::ostream& operator<<(std::ostream& os, Name<TemplateList<>>) {
		return os;
	}
};

template<template<typename...> class T>
struct Name<TemplateList<T>> {
	friend std::ostream& operator<<(std::ostream& os, Name<TemplateList<T>>) {
		os << T<void>().name;
		return os;
	}
};
template<template<typename...>class... Ts>
struct Name<TemplateList<Ts...>> {
	friend std::ostream& operator<<(std::ostream& os, Name<TemplateList<Ts...>>) {
		os << TFront<TemplateList<Ts...>>::template Ttype<void>().name << ", "
			<< Name<TPopFront_t<TemplateList<Ts...>>>();
		return os;
	}
};

template<typename I, typename List, size_t Index>
using ToI = TPushFront<I, TAt<List, Index>::template Ttype>;

template<template<typename...>class T>
struct Double {
	template<typename... Ts>
	using Ttype = typename T<void>::template Double<Ts...>;
};

struct Rst : is_instance_of<A<void>, TFront<TemplateList<A>>::Ttype> {};
template<typename T>
using BAlias = B<T>;

template<typename T0, typename T1>
struct T2 {};

int main() {
	using list0 = TemplateList<A, B, C>;

	cout << "list0" << endl
		<< "\t" << Name<list0>() << endl;
	cout << "TPushFront_t<list0, D>" << endl
		<< "\t" << Name<TPushFront_t<list0, D>>() << endl;
	cout << "TPopFront_t<list0>" << endl
		<< "\t" << Name<TPopFront_t<list0>>() << endl;
	cout << "TAt<list0, 1>" << endl
		<< "\t" << TAt<list0, 1>::Ttype<>().name << endl;
	cout << "TReverse_t<list0>" << endl
		<< "\t" << Name<TReverse_t<list0>>() << endl;
	cout << "TPushBack_t<list0, D>" << endl
		<< "\t" << Name<TPushBack_t<list0, D>>() << endl;
	cout << "TConcat_t<list0, TemplateList<A,D>>" << endl
		<< "\t" << Name<TConcat_t<list0, TemplateList<A,D>>>() << endl;
	cout << "TAccumulateIS_t<list0, ToI, TemplateList<D>, 0, 2>" << endl
		<< "\t" << Name<TAccumulateIS_t<list0, ToI, TemplateList<D>, 0, 2>>() << endl;
	cout << "TSelect_t<list0, 0, 2>" << endl
		<< "\t" << Name<TSelect_t<list0, 0, 2>>() << endl;
	cout << "TSelect_t<list0, 0, 2>" << endl
		<< "\t" << Name<TTransform_t<list0, Double>>() << endl;
	cout << "TInstantiable<list0, B>" << endl
		<< "\t" << TInstantiable_v<list0, B<>> << endl;
	cout << "TInstantiable<list0, D>" << endl
		<< "\t" << TInstantiable_v<list0, D<>> << endl;
	cout << "TInstantiableList_v<list0, TemplateList<TypeList<void>, A, B>>" << endl
		<< "\t" << TInstantiableList_v<list0, TInstanceList_t<TemplateList<A, B>, TypeList<void>>> << endl;
	cout << "TInstantiableList_v<list0, TemplateList<TypeList<void>, D, B>>" << endl
		<< "\t" << TInstantiableList_v<list0, TInstanceList_t<TemplateList<D, B>, TypeList<void>>> << endl;
	return 0;
}