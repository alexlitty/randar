#ifndef __CEF_PATH_HPP
#define __CEF_PATH_HPP

#include <randar/Filesystem/Path.hpp>

namespace randar
{
	class CefPath : public Path
	{
	public:
		/**
		* Default constructor.
		*
		* Set to the current working directory.
		*/
		CefPath();

		/**
		* Constructor, given a UNIX-style string path.
		*/
		CefPath(const std::string& path);

		/**
		* Copy constructor.
		*/
		CefPath(const CefPath& other);

		/**
		* Converts to a platform-appropriate string.
		* Prefixes file:// to path so that CEF plays nice.
		*/
		virtual std::string toString() const override;
	};
}

#endif
