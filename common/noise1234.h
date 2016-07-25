// Noise1234
// Author: Stefan Gustavson (stegu@itn.liu.se)
//
// This library is public domain software, released by the author
// into the public domain in February 2011. You may do anything
// you like with it. You may even remove all attributions,
// but of course I'd appreciate it if you kept my name somewhere.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.

/** \file
		\brief Declares the Noise1234 class for producing Perlin noise.
		\author Stefan Gustavson (stegu@itn.liu.se)
*/

/*
 * This is a clean, fast, modern and free Perlin noise class in C++.
 * Being a stand-alone class with no external dependencies, it is
 * highly reusable without source code modifications.
 *
 * Note:
 * Replacing the "float" type with "double" can actually make this run faster
 * on some platforms. A templatized version of Noise1234 could be useful.
 */


/** 1D, 2D, 3D and 4D float Perlin noise, SL "noise()"
 */
    static float noise1( float x );
    static float noise2( float x, float y );
    static float noise3( float x, float y, float z );
    static float noise4( float x, float y, float z, float w );

/** 1D, 2D, 3D and 4D float Perlin periodic noise, SL "pnoise()"
 */
    static float pnoise1( float x, int px );
    static float pnoise2( float x, float y, int px, int py );
    static float pnoise3( float x, float y, float z, int px, int py, int pz );
    static float pnoise4( float x, float y, float z, float w,
                              int px, int py, int pz, int pw );

    // static unsigned char perm[];
    static float  grad1( int hash, float x );
    static float  grad2( int hash, float x, float y );
    static float  grad3( int hash, float x, float y , float z );
    static float  grad4( int hash, float x, float y, float z, float t );

