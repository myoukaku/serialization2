/**
 *	@file	binary_oarchive.hpp
 *
 *	@brief	binary_oarchive の定義
 *
 *	@author	myoukaku
 */

#ifndef SERIALIZATION_binary_oarchive_HPP
#define SERIALIZATION_binary_oarchive_HPP

#include <serialization/oarchive.hpp>
#include <cstddef>
#include <memory>

namespace serialization
{

class binary_oarchive_impl_base
{
public:
	virtual ~binary_oarchive_impl_base() {}

	virtual void save(void const* src, std::size_t size) = 0;
};

template <typename OStream>
class binary_oarchive_impl
	: public binary_oarchive_impl_base
{
public:
	explicit binary_oarchive_impl(OStream& os)
		: m_os(os)
	{}

	void save(void const* src, std::size_t size) override
	{
		using char_type = typename OStream::char_type;
		m_os.write(static_cast<char_type const*>(src), size);
	}

private:
	binary_oarchive_impl& operator=(binary_oarchive_impl const&) = delete;

	OStream&	m_os;
};

class binary_oarchive : public oarchive
{
public:
	template <typename OStream>
	explicit binary_oarchive(OStream& os)
		: m_impl(new binary_oarchive_impl<OStream>(os))
	{
	}

	//template <typename T>
	//binary_oarchive& operator<<(T const& t)
	//{
	//	serialization::detail::save_dispatch::invoke(*this, t);
	//	return *this;
	//}

	//template <typename T>
	//binary_oarchive& operator&(T const& t)
	//{
	//	return *this << t;
	//}

private:
	std::unique_ptr<binary_oarchive_impl_base>	m_impl;

private:
	void save_primitive(int t) override
	{
		m_impl->save(&t, sizeof(int));
	}
	void save_primitive(unsigned int t) override
	{
		m_impl->save(&t, sizeof(unsigned int));
	}

//	template <typename T>
//	friend void save_arithmetic(binary_oarchive& oa, T const& t)
//	{
//		oa.m_impl->save(&t, sizeof(T));
//	}
//
//	template <typename CharT>
//	friend void save_string(binary_oarchive& oa, std::basic_string<CharT> const& t)
//	{
//		std::size_t const len = t.length();
//		oa.m_impl->save(&len, sizeof(len));
//		oa.m_impl->save(t.data(), len * sizeof(CharT));
//	}
};

}	// namespace serialization

#endif // SERIALIZATION_binary_oarchive_HPP
