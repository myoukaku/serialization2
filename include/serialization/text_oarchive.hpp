/**
 *	@file	text_oarchive.hpp
 *
 *	@brief	text_oarchive の定義
 *
 *	@author	myoukaku
 */

#ifndef SERIALIZATION_TEXT_OARCHIVE_HPP
#define SERIALIZATION_TEXT_OARCHIVE_HPP

#include <serialization/oarchive.hpp>
#include <cstdint>
#include <memory>

namespace serialization
{

class text_oarchive_impl_base
{
public:
	virtual ~text_oarchive_impl_base() {}

	virtual void save(std::intmax_t) = 0;
	virtual void save(std::uintmax_t) = 0;
};

template <typename OStream>
class text_oarchive_impl
	: public text_oarchive_impl_base
{
public:
	explicit text_oarchive_impl(OStream& os)
		: m_os(os)
	{}

	void save(std::intmax_t t) override
	{
		m_os << t << " ";
	}

	void save(std::uintmax_t t) override
	{
		m_os << t << " ";
	}

private:
	text_oarchive_impl& operator=(text_oarchive_impl const&) = delete;

	OStream&	m_os;
};

class text_oarchive : public oarchive
{
public:
	template <typename OStream>
	explicit text_oarchive(OStream& os)
		: m_impl(new text_oarchive_impl<OStream>(os))
	{
	}

	//template <typename T>
	//text_oarchive& operator<<(T const& t)
	//{
	//	//serialization::detail::save_dispatch::invoke(*this, t);
	//	return *this;
	//}

	//template <typename T>
	//text_oarchive& operator&(T const& t)
	//{
	//	return *this << t;
	//}

private:
	std::unique_ptr<text_oarchive_impl_base>	m_impl;

private:
	void save_primitive(int t) override
	{
		m_impl->save(static_cast<std::intmax_t>(t));
	}

	void save_primitive(unsigned int t) override
	{
		m_impl->save(static_cast<std::uintmax_t>(t));
	}

//private:
//	template <typename T>
//	friend void save_arithmetic(text_oarchive& oa, T const& t)
//	{
//		if constexpr (std::is_floating_point_v<T>)
//		{
//			oa.m_impl->save(t);
//		}
//		else if constexpr (std::is_unsigned_v<T>)
//		{
//			oa.m_impl->save(static_cast<std::uintmax_t>(t));
//		}
//		else
//		{
//			oa.m_impl->save(static_cast<std::intmax_t>(t));
//		}
//	}
//
//	template <typename CharT>
//	friend void save_string(text_oarchive& oa, std::basic_string<CharT> const& t)
//	{
//		oa.m_impl->save(t);
//	}
};

}	// namespace serialization

#endif // SERIALIZATION_TEXT_OARCHIVE_HPP
