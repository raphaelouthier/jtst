#include <stdio.h>

#include <stdint.h>

#include <stdlib.h>

typedef uint8_t u8;
typedef uint64_t u64;

/*
 * Define a class with no virtual methods.
 */
class base
#ifdef BASE_IS_FINAL
	final
#endif
{
	public:
	u64 mtd0(void) {return 0;}
	u64 mtd1(void) {return 1;}
	u64 mtd2(void);
	u64 mtd3(void);
	u64 att0 = 0;
	u64 att1 = 1;
	u64 att2 = 2;
	u64 att3 = 3;
};

/*
 * Define a class with virtual methods.
 */
class vbase {
	public:
	virtual u64 mtd0(void) = 0;
	virtual u64 mtd1(void) = 0;
	u64 mtd2(void);
	u64 mtd3(void);
	u64 att0 = 0;
	u64 att1 = 1;
	u64 att2 = 2;
	u64 att3 = 3;
};
class child : public vbase {
	u64 mtd0(void) override;
	u64 mtd1(void) override;
	u8 att4 = 0xff;
	u64 att5 = 5;
	u8 att6 = 6;
};
