#include <sgl.h>

const Uint32 SystemWork = 0x060FFC00;
const Uint32 SystemSize	= ( 0x06100000 - 0x060FFC00 );

extern Uint32 _bstart, _bend;

int main( void )
{
	Uint8 *pDest;
	Uint32 i;

	/* Zero the .bss section */
	for( pDest = ( Uint8 * )&_bstart; pDest < ( Uint8 * )&_bend; ++pDest )
	{
		( *pDest ) = 0;
	}

	for( pDest = ( Uint8 * )SystemWork, i = 0; i < SystemSize; ++i )
	{
		( *pDest ) = 0;
	}

	slInitSystem( TV_320x224, NULL, 1 );
	slPrint( "Red Ring Rico's", slLocate( 1, 2 ) );
	slPrint( "Mini Ludum Dare #52 Entry", slLocate( 1, 3 ) );

	while( -1 )
	{
		slSynch( );
	}

	return 0;
}

