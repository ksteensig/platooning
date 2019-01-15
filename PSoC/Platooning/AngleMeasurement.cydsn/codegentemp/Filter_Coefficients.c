#include "Filter.h"
#include "Filter_PVT.h"


/*******************************************************************************
* ChannelA filter coefficients.
* Filter Type is FIR
*******************************************************************************/

/* Renamed array for backward compatibility.
*  Should not be used in new designs.
*/
#define ChannelAFirCoefficients Filter_ChannelAFirCoefficients

/* Number of FIR filter taps are: 8 */

const uint8 CYCODE Filter_ChannelAFirCoefficients[Filter_FIR_A_SIZE] = 
{
 0x9Fu, 0x16u, 0x01u, 0x00u, /* Tap(0), 0.00850284099578857 */

 0x0Eu, 0xD4u, 0x03u, 0x00u, /* Tap(1), 0.0299088954925537 */

 0x0Au, 0xFEu, 0x07u, 0x00u, /* Tap(2), 0.0624401569366455 */

 0x05u, 0x14u, 0x0Bu, 0x00u, /* Tap(3), 0.0865484476089478 */

 0x05u, 0x14u, 0x0Bu, 0x00u, /* Tap(4), 0.0865484476089478 */

 0x0Au, 0xFEu, 0x07u, 0x00u, /* Tap(5), 0.0624401569366455 */

 0x0Eu, 0xD4u, 0x03u, 0x00u, /* Tap(6), 0.0299088954925537 */

 0x9Fu, 0x16u, 0x01u, 0x00u, /* Tap(7), 0.00850284099578857 */
};


/*******************************************************************************
* ChannelB filter coefficients.
* Filter Type is FIR
*******************************************************************************/

/* Renamed array for backward compatibility.
*  Should not be used in new designs.
*/
#define ChannelBFirCoefficients Filter_ChannelBFirCoefficients

/* Number of FIR filter taps are: 8 */

const uint8 CYCODE Filter_ChannelBFirCoefficients[Filter_FIR_B_SIZE] = 
{
 0x9Fu, 0x16u, 0x01u, 0x00u, /* Tap(0), 0.00850284099578857 */

 0x0Eu, 0xD4u, 0x03u, 0x00u, /* Tap(1), 0.0299088954925537 */

 0x0Au, 0xFEu, 0x07u, 0x00u, /* Tap(2), 0.0624401569366455 */

 0x05u, 0x14u, 0x0Bu, 0x00u, /* Tap(3), 0.0865484476089478 */

 0x05u, 0x14u, 0x0Bu, 0x00u, /* Tap(4), 0.0865484476089478 */

 0x0Au, 0xFEu, 0x07u, 0x00u, /* Tap(5), 0.0624401569366455 */

 0x0Eu, 0xD4u, 0x03u, 0x00u, /* Tap(6), 0.0299088954925537 */

 0x9Fu, 0x16u, 0x01u, 0x00u, /* Tap(7), 0.00850284099578857 */
};

