/***********************************************************************
 * Smart Pointer Exercise - Ocient LLC
 ***********************************************************************
 * Test implementations of shared_ptr and unique_ptr
 *
 * If this code is compiled with USE_STD defined, it will be built with 
 * std::shared_ptr and std::unique_ptr, othewwise it assumes 
 * the existence of a smart_pointers.h header file that provides those.
 *
 * If this code is compiled with DEBUG defined it will print extra
 * output.
 ***********************************************************************/
#include <list>
#include <vector>
#include <random>
#include <iostream>

#include "debug.h"

/***********************************************************************
 * If USE_STD is NOT defined, include smart_ptrs.h.  That header
 * file should implement shared_ptr and unique_ptr classes, and 
 * make_shared and make_unique functions
 ***********************************************************************/
#ifndef USE_STD
#include "smart_pointers.h"

/***********************************************************************
 * USE_STD NOT defined, use the std:: implementations
 ***********************************************************************/
#else
#include <memory>
template <typename T>
using shared_ptr = std::shared_ptr<T>;

#define make_shared std::make_shared

template <typename T>
using unique_ptr = std::unique_ptr<T>;

#define make_unique std::make_unique
#endif
/***********************************************************************/

/***********************************************************************
 * The Thing class.  One of the most useless classes ever
 ***********************************************************************/
class Thing {
public:
	/* Construct taking a value */
	Thing(int value) : m_value(value) {
		dout << "Constructing Thing " << m_value << std::endl;
	}

	/* Destruct thing */
	~Thing() {
		dout << "Destructing Thing " << m_value << std::endl;
	}

	/* Deliberately PREVENT copying.  Note that this will also
	 * prevent constructing and move assigning.
	 */
	Thing(const Thing &other) = delete;
	Thing &operator=(const Thing &other) = delete;

	/* Get our value */
	int value() const { return m_value; }
	
private:
	int m_value;
};

/***********************************************************************
 * A function that does something very clever with a Thing.  Note that 
 * because this takes a unique_ptr as input, it is obvious that this 
 * function TAKES OWNERSHIP of the object
 ***********************************************************************/
static void DoSomethingClever(unique_ptr<Thing> thing) {
	std::cout << "Clever with thing " << thing->value() << std::endl;
};

/***********************************************************************
 * Genesis....
 ***********************************************************************/
int main(int argc, char **argv) {

	std::vector< unique_ptr< Thing > > single_things;

	std::list< shared_ptr < Thing > > shared_things;
	std::list< shared_ptr < Thing > > even_things;
	std::list< shared_ptr < Thing > > odd_things;

	/*******************************************************************
	 * NOTE!!!!: If this code is built correctly with address sanitizer,
	 * this SHOULD display an error about lost memory at run time. 
	 * Feel free to delete this line once you have verified that 
	 * the address sanitizer works
	 *******************************************************************/
	new Thing(99);

	// Make some unqiue things
	for (auto i=0; i<3; i++) {
		single_things.push_back( make_unique<Thing>(i) );
	}

	// Make some shared things
	for (auto i=10; i<16; i++) {
		shared_things.emplace_back( make_shared<Thing>(i) );

		if (i % 2)
			odd_things.emplace_back( shared_things.back() );
		else
			even_things.emplace_back( shared_things.back() );
	}

	// Do something clever with all the unique things
	for (auto &thing: single_things) {
		DoSomethingClever( std::move(thing) );

		// After calling DoSomethingClever, we should no longer own
		// the thing.
		if (thing) 
			std::cerr << "Something went horribly wrong...." << std::endl;
	}

	// At this point, single_things is a container of empty unique_ptrs.
	// Clean them up.
	single_things.clear();

	return 0;
}
