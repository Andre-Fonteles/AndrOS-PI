#ifndef	_P_BASE_H
#define	_P_BASE_H

#if RPI_VERSION == 3
#define PBASE 0x3F000000
#elif RPI_VERSION == 4
#define PBASE 0xFE000000
#else
#define PBASE 0
#endif

#endif  /*_P_BASE_H */