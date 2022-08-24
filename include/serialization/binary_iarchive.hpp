/**
 *	@file	binary_iarchive.hpp
 *
 *	@brief	binary_iarchive の定義
 *
 *	@author	myoukaku
 */

#ifndef SERIALIZATION_binary_iarchive_HPP
#define SERIALIZATION_binary_iarchive_HPP

#include <serialization/iarchive.hpp>
#include <cstddef>
#include <memory>

namespace serialization
{

class binary_iarchive_impl_base
{
public:
	virtual ~binary_iarchive_impl_base() {}

	virtual void load(void* dst, std::size_t size) = 0;
};

template <typename IStream>
class binary_iarchive_impl
	: public binary_iarchive_impl_base
{
public:
	explicit binary_iarchive_impl(IStream& is)
		: m_is(is)
	{}

	void load(void* dst, std::size_t size) override
	{
		using char_type = typename IStream::char_type;
		m_is.read(static_cast<char_type*>(dst), size);
	}

private:
	binary_iarchive_impl& operator=(binary_iarchive_impl const&) = delete;

	IStream&	m_is;
};

class binary_iarchive : public iarchive
{
public:
	template <typename IStream>
	explicit binary_iarchive(IStream& is)
		: m_impl(new binary_iarchive_impl<IStream>(is))
	{
	}

	//template <typename T>
	//binary_iarchive& operator>>(T& t)
	//{
	//	serialization::detail::load_dispatch::invoke(*this, t);
	//	return *this;
	//}

	//template <typename T>
	//binary_iarchive& operator&(T& t)
	//{
	//	return *this >> t;
	//}

private:
	std::unique_ptr<binary_iarchive_impl_base>	m_impl;

private:
	void load_primitive(int& t) override
	{
		m_impl->load(&t, sizeof(int));
	}
	void load_primitive(unsigned int& t) override
	{
		m_impl->load(&t, sizeof(unsigned int));
	}

//	template <typename T>
//	friend void load_arithmetic(binary_iarchive& ia, T& t)
//	{
//		ia.m_impl->load(&t, sizeof(T));
//	}
//
//	template <typename CharT>
//	friend void load_string(binary_iarchive& ia, std::basic_string<CharT>& t)
//	{
//		std::size_t len;
//		ia.m_impl->load(&len, sizeof(len));
//
//		t.resize(len);
//		ia.m_impl->load(t.data(), len * sizeof(CharT));
//	}
};

}	// namespace serialization

#endif // SERIALIZATION_binary_iarchive_HPP
