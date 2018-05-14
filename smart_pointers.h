#ifndef SMART_POINTERS_H
#define SMART_POINTERS_H
/***********************************************************************
 * Your assignment, should you choose to accept it, is to implement
 * the shared_ptr and unique_ptr classes
 * 
 * The implementations to NOT have to be thread safe for the purposes
 * of this assignment....and you would be silly to start with making them
 * so...however if your result is thread-safe, you can take TWO extra
 * cans of La Croix from the fridge.
 ***********************************************************************/

/***********************************************************************
 * the "dout" object is available for debug output...you are encouraged
 * to use it
 ***********************************************************************/
#include "debug.h"

/*
 * My Super Cool Shared Ptr Class
 */
template <typename T>
class shared_ptr {
};

/*
 * Create a shared pointer
 */
template<class T, class ... Args>
static shared_ptr<T> make_shared(Args && ... args) {
	dout << "Hey, some fool just made one of my shared objects...." << std::endl;
	return shared_ptr<T>(std::forward<Args>(args)...);
}

/*
 * My Super Cool Unique Ptr Class
 */
template <typename T>
class unique_ptr {
};

/*
 * Create a unique pointer
 */
template<class T, class ... Args>
static unique_ptr<T> make_unique(Args && ... args) {
	dout << "Hey, some fool just made one of my unique objects...." << std::endl;
	return shared_ptr<T>(std::forward<Args>(args)...);
}

#endif /* SMART_POINTERS_H */
