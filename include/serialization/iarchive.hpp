/**
 *	@file	iarchive.hpp
 *
 *	@brief	iarchive の定義
 */

#ifndef SERIALIZATION_IARCHIVE_HPP
#define SERIALIZATION_IARCHIVE_HPP

#include <serialization/archive.hpp>
#include <serialization/detail/load_dispatch.hpp>

namespace serialization
{

class iarchive : public archive
{
public:
	template <typename T>
	iarchive& operator>>(T& t)
	{
		serialization::detail::load_dispatch::invoke(*this, t);
		return *this;
	}

private:
	bool is_loading(void) const override
	{
		return true;
	}

	virtual void load_primitive(int& t) = 0;
	virtual void load_primitive(unsigned int& t) = 0;

	friend class detail::load_dispatch;
};

}	// namespace serialization

#endif // SERIALIZATION_IARCHIVE_HPP
