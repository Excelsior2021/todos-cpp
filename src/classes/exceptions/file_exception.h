#ifndef _FILE_EXCEPTION_
#define _FILE_EXCEPTION_
#include <exception>

class FileException: public std::exception {
	const char* msg;
	public:
		FileException(const char* msg) noexcept :msg{msg} {};
		FileException() noexcept : msg{ "Cannot load file."} {};
		~FileException() noexcept = default;
		virtual const char* what() const noexcept override {
			return msg;
		}
};

#endif