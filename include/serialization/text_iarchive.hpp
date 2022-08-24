/**
 *	@file	text_iarchive.hpp
 *
 *	@brief	text_iarchive の定義
 *
 *	@author	myoukaku
 */

#ifndef SERIALIZATION_TEXT_IARCHIVE_HPP
#define SERIALIZATION_TEXT_IARCHIVE_HPP

#include <serialization/iarchive.hpp>
#include <cstdint>
#include <memory>

namespace serialization
{

class text_iarchive_impl_base
{
public:
	virtual ~text_iarchive_impl_base() {}

	virtual void load(std::intmax_t&) = 0;
	virtual void load(std::uintmax_t&) = 0;
};

template <typename IStream>
class text_iarchive_impl
	: public text_iarchive_impl_base
{
public:
	explicit text_iarchive_impl(IStream& is)
		: m_is(is)
	{}

	void load(std::intmax_t& t) override
	{
		m_is >> t;
	}

	void load(std::uintmax_t& t) override
	{
		m_is >> t;
	}

private:
	text_iarchive_impl& operator=(text_iarchive_impl const&) = delete;

	IStream&	m_is;
};

class text_iarchive : public iarchive
{
public:
	template <typename IStream>
	explicit text_iarchive(IStream& is)
		: m_impl(new text_iarchive_impl<IStream>(is))
	{
	}

//	template <typename T>
//	text_iarchive& operator>>(T& t)
//	{
////		serialization::detail::load_dispatch::invoke(*this, t);
//		return *this;
//	}
//
//	template <typename T>
//	text_iarchive& operator&(T& t)
//	{
//		return *this >> t;
//	}
//
private:
	std::unique_ptr<text_iarchive_impl_base>	m_impl;

private:
	void load_primitive(int& t) override
	{
		std::intmax_t i;
		m_impl->load(i);
		t = static_cast<int>(i);
	}

	void load_primitive(unsigned int& t) override
	{
		std::uintmax_t i;
		m_impl->load(i);
		t = static_cast<unsigned int>(i);
	}

//private:
//	template <typename T>
//	friend void load_arithmetic(text_iarchive& ia, T& t)
//	{
//		if constexpr (std::is_floating_point_v<T>)
//		{
//			ia.m_impl->load(t);
//		}
//		else if constexpr (std::is_unsigned_v<T>)
//		{
//			std::uintmax_t i;
//			ia.m_impl->load(i);
//			t = static_cast<T>(i);
//		}
//		else
//		{
//			std::intmax_t i;
//			ia.m_impl->load(i);
//			t = static_cast<T>(i);
//		}
//	}
//
//	template <typename CharT>
//	friend void load_string(text_iarchive& ia, std::basic_string<CharT>& t)
//	{
//		ia.m_impl->load(t);
//	}
};

}	// namespace serialization

#endif // SERIALIZATION_TEXT_IARCHIVE_HPP
