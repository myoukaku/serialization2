/**
 *	@file	oarchive.hpp
 *
 *	@brief	oarchive の定義
 */

#ifndef SERIALIZATION_OARCHIVE_HPP
#define SERIALIZATION_OARCHIVE_HPP

#include <serialization/archive.hpp>
#include <serialization/detail/save_dispatch.hpp>

namespace serialization
{

class oarchive : public archive
{
public:
	template <typename T>
	oarchive& operator<<(T const& t)
	{
		serialization::detail::save_dispatch::invoke(*this, t);
		return *this;
	}

private:
	bool is_loading(void) const override
	{
		return false;
	}

	//virtual void save_primitive(bool t) = 0;
	//virtual void save_primitive(char t) = 0;
	//virtual void save_primitive(wchar_t t) = 0;
	//virtual void save_primitive(signed   char t) = 0;
	//virtual void save_primitive(unsigned char t) = 0;
	//virtual void save_primitive(signed   short t) = 0;
	//virtual void save_primitive(unsigned short t) = 0;
	virtual void save_primitive(signed   int t) = 0;
	virtual void save_primitive(unsigned int t) = 0;
	//virtual void save_primitive(signed   long t) = 0;
	//virtual void save_primitive(unsigned long t) = 0;
	//virtual void save_primitive(signed   long long t) = 0;
	//virtual void save_primitive(unsigned long long t) = 0;

	friend class detail::save_dispatch;
};

}	// namespace serialization

#endif // SERIALIZATION_OARCHIVE_HPP
