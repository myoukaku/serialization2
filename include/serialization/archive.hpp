/**
 *	@file	archive.hpp
 *
 *	@brief	archive の定義
 */

#ifndef SERIALIZATION_ARCHIVE_HPP
#define SERIALIZATION_ARCHIVE_HPP

namespace serialization
{

class iarchive;
class oarchive;

class archive
{
public:
	template <typename T>
	archive& operator&(T& t)
	{
		if (is_loading())
		{
			(iarchive&)(*this) >> t;
		}
		else
		{
			(oarchive&)(*this) << t;
		}
		return *this;
	}

private:
	virtual bool is_loading(void) const = 0;
};

}	// namespace serialization

#endif // SERIALIZATION_ARCHIVE_HPP
