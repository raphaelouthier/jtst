#include "main.hpp"

/***********
 * Configs *
 ***********/

// Comment to not report the "base" class final
//#define BASE_IS_FINAL

// Comment to enable mangling
#define NO_MANGLING

/************
 * Mangling *
 ************/

#ifdef NO_MANGLING
extern "C" {
#endif

/*******************
 * Opti prevention *
 *******************/

u64 seed = 42;

#define _noinline __attribute__((noinline))

/*********************************
 * Class without virtual members *
 *********************************/


/* base::method pointer. */
typedef u64 (base::*base_mptr)(void);

/*
 * Utilities
 */

/*
 * Get a (random) base pointer.
 */ 
_noinline base *base_get_ptr(void) {
	return new base();
};

/*
 * Get a (random) method pointer.
 */
_noinline base_mptr base_get_mptr(u64 idx) {
	if (seed) return 0;
	switch (idx) {
		case 0:return &base::mtd0;
		case 1:return &base::mtd1;
		case 2:return &base::mtd2;
		case 3:return &base::mtd3;
	}
	return 0;
}

/*
 * From an instance pointer an a method pointer, call the
 * method on the instance.
 */
_noinline u64 base_mptr_call(base *ptr, base_mptr mtd) {
	return (ptr->*mtd)();
}

/*
 * Procedures
 */

/*
 * Fetch (sum) attributes.
 */
__attribute__((optimize("O1")))
u64 base_get_atts() {
	base *ptr = base_get_ptr();
	return ptr->att0 + ptr->att1 + ptr->att2 + ptr->att3;
}

/*
 * Perform an inline method call directly. 
 */
u64 base_inline_call(void) {
	base *ptr = base_get_ptr();
	return ptr->mtd0();
}

/*
 * Perform a non inline method call directly. 
 */
u64 base_direct_call(void) {
	base *ptr = base_get_ptr();
	return ptr->mtd2();
}

/*
 * Perform a method call by pointer. 
 */
u64 base_indirect_call(void) {
	base *ptr = base_get_ptr();
	base_mptr mtd = base_get_mptr(0);
	return base_mptr_call(ptr, mtd);
}

/*
 * Print what a method pointer really is underneath.
 * (saves and restore @seed, don't overthing it).
 */
void base_show_mptr(void) {
	base *ptr;
	base_mptr mtd;
	u64 prv = seed;
	ptr = base_get_ptr();
	seed = 0;
	mtd = base_get_mptr(0);
	printf("base method pointers : \n");
	printf("mtd0 : %lld 0x%llx 0x%llx 0x%llx 0x%llx.\n", ptr, mtd, 0xff, 0, 0, 0);
	mtd = base_get_mptr(1);
	printf("mtd1 : %lld 0x%llx 0x%llx 0x%llx 0x%llx.\n", ptr, mtd, 0xff, 0, 0, 0);
	mtd = base_get_mptr(2);
	printf("mtd2 : %lld 0x%llx 0x%llx 0x%llx 0x%llx.\n", ptr, mtd, 0xff, 0, 0, 0);
	mtd = base_get_mptr(3);
	printf("mtd3 : %lld 0x%llx 0x%llx 0x%llx 0x%llx.\n", ptr, mtd, 0xff, 0, 0, 0);
	mtd = base_get_mptr(4);
	printf("mtd4 : %lld 0x%llx 0x%llx 0x%llx 0x%llx.\n", ptr, mtd, 0xff, 0, 0, 0);
	seed = prv;
}

/******************************
 * Class with virtual members *
 ******************************/


/* vbase::method pointer. */
typedef u64 (vbase::*vbase_mptr)(void);

/*
 * Utilities
 */

/*
 * Get a (random) vbase pointer.
 */ 
_noinline vbase *vbase_get_ptr(void) {
	return new child();
};

/*
 * Get a (random) method pointer.
 */
_noinline vbase_mptr vbase_get_mptr(u64 idx) {
	if (seed) return 0;
	switch (idx) {
		case 0:return &vbase::mtd0;
		case 1:return &vbase::mtd1;
		case 2:return &vbase::mtd2;
		case 3:return &vbase::mtd3;
	}
	return 0;
}

/*
 * From an instance pointer an a method pointer, call the
 * method on the instance.
 */
_noinline u64 vbase_mptr_call(vbase *ptr, vbase_mptr mtd) {
	return (ptr->*mtd)();
}

/*
 * Procedures
 */

/*
 * Fetch (sum) attributes.
 */
__attribute__((optimize("O1")))
u64 vbase_get_atts() {
	vbase *ptr = vbase_get_ptr();
	return ptr->att0 + ptr->att1 + ptr->att2 + ptr->att3;
}

/*
 * Perform a non-virtual method call directly. 
 */
u64 vbase_direct_call(void) {
	vbase *ptr = vbase_get_ptr();
	return ptr->mtd2();
}

/*
 * Perform a virtual method call directly. 
 */
u64 vbase_direct_vcall(void) {
	vbase *ptr = vbase_get_ptr();
	return ptr->mtd0();
}

/*
 * Perform a virtual method call by pointer. 
 */
u64 vbase_indirect_call(void) {
	vbase *ptr = vbase_get_ptr();
	vbase_mptr mtd = vbase_get_mptr(0);
	return vbase_mptr_call(ptr, mtd);
}

/*
 * Print what a method pointer really is underneath.
 * (saves and restore @seed, don't overthing it).
 */
void vbase_show_mptr(void) {
	vbase *ptr;
	vbase_mptr mtd;
	u64 prv = seed;
	ptr = vbase_get_ptr();
	seed = 0;
	mtd = vbase_get_mptr(0);
	printf("vbase method pointers : \n");
	printf("mtd0 : 0x%lld 0x%llx 0x%llx 0x%llx 0x%llx.\n", ptr, mtd, 0xff, 0, 0, 0);
	mtd = vbase_get_mptr(1);
	printf("mtd1 : 0x%lld 0x%llx 0x%llx 0x%llx 0x%llx.\n", ptr, mtd, 0xff, 0, 0, 0);
	mtd = vbase_get_mptr(2);
	printf("mtd2 : 0x%lld 0x%llx 0x%llx 0x%llx 0x%llx.\n", ptr, mtd, 0xff, 0, 0, 0);
	mtd = vbase_get_mptr(3);
	printf("mtd3 : 0x%lld 0x%llx 0x%llx 0x%llx 0x%llx.\n", ptr, mtd, 0xff, 0, 0, 0);
	mtd = vbase_get_mptr(4);
	printf("mtd4 : 0x%lld 0x%llx 0x%llx 0x%llx 0x%llx.\n", ptr, mtd, 0xff, 0, 0, 0);
	seed = prv;
}

_noinline void* trap() {
	void *x = malloc(16);
	return x;
}

/**************
 * Entrypoint *
 **************/

__attribute__((optimize("O0")))
int main(void) {

	// Show various method pointers.
	base_show_mptr();
	vbase_show_mptr();

	// Allocate two instances and break.
	base *base_ptr = base_get_ptr();
	vbase *vbase_ptr = vbase_get_ptr();
	void *res = trap();

}


/************
 * Mangling *
 ************/

#ifdef NO_MANGLING
}
#endif
