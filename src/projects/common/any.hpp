#ifndef DATA_H
#define DATA_H

#include <typeindex>
#include <memory>

struct Any
{
	Any(void) : typeIndex(std::type_index(typeid(void)))
	{

	}
	Any(const Any& that)
		: basePtr(that.Clone()), typeIndex(that.typeIndex)
	{

	}

	Any(Any&& that)
		: basePtr(std::move(that.basePtr)), typeIndex(that.typeIndex)
	{

	}

	template<typename U,
		class = typename std::enable_if<!std::is_same<typename std::decay<U>::type, Any>::value, U>::type>
		Any(U&& value)
		: basePtr(new Derived < typename std::decay<U>::type>(forward<U>(value))),
		typeIndex(type_index(typeid(typename std::decay<U>::type)))
	{

	}

	bool IsNull() const
	{
		return !bool(basePtr);
	}

	template<class U> bool Is() const
	{
		return typeIndex == type_index(typeid(U));
	}

	//将Any转换为实际的类型
	template<class U>
	U& AnyCast()
	{
		if (!Is<U>())
		{
			throw bad_cast();
		}

		auto derived = dynamic_cast<Derived<U>*> (basePtr.get());
		return derived->value;
	}

	Any& operator=(const Any& a)
	{
		if (basePtr == a.basePtr)
			return *this;

		basePtr = a.Clone();
		typeIndex = a.typeIndex;
		return *this;
	}

private:
	struct Base;
	typedef std::unique_ptr<Base> BasePtr;

	struct Base
	{
		virtual ~Base() {}
		virtual BasePtr Clone() const = 0;
	};

	template<typename T>
	struct Derived : Base
	{
		template<typename U>
		Derived(U&& value) : value(std::forward<U>(value)) { }

		BasePtr Clone() const
		{
			return BasePtr(new Derived<T>(this->value));
		}

		T value;
	};

	BasePtr Clone() const
	{
		if (basePtr != nullptr)
			return basePtr->Clone();

		return nullptr;
	}

	BasePtr basePtr;
	std::type_index typeIndex;
};


#endif // !DATA_H