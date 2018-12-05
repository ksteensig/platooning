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

/* Number of FIR filter taps are: 32 */

const uint8 CYCODE Filter_ChannelAFirCoefficients[Filter_FIR_A_SIZE] = 
{
 0xBEu, 0xCDu, 0xFFu, 0x00u, /* Tap(0), -0.00153374671936035 */

 0x26u, 0xC7u, 0xFFu, 0x00u, /* Tap(1), -0.00173497200012207 */

 0x9Bu, 0xC0u, 0xFFu, 0x00u, /* Tap(2), -0.00193464756011963 */

 0x0Au, 0xC6u, 0xFFu, 0x00u, /* Tap(3), -0.00176882743835449 */

 0x91u, 0xE7u, 0xFFu, 0x00u, /* Tap(4), -0.000745654106140137 */

 0xC7u, 0x36u, 0x00u, 0x00u, /* Tap(5), 0.00167167186737061 */

 0x50u, 0xC3u, 0x00u, 0x00u, /* Tap(6), 0.00596046447753906 */

 0x3Du, 0x97u, 0x01u, 0x00u, /* Tap(7), 0.0124279260635376 */

 0x08u, 0xB4u, 0x02u, 0x00u, /* Tap(8), 0.0211191177368164 */

 0xB0u, 0x10u, 0x04u, 0x00u, /* Tap(9), 0.0317592620849609 */

 0x7Bu, 0x99u, 0x05u, 0x00u, /* Tap(10), 0.0437463521957397 */

 0x7Cu, 0x31u, 0x07u, 0x00u, /* Tap(11), 0.0561976432800293 */

 0xCBu, 0xB5u, 0x08u, 0x00u, /* Tap(12), 0.0680478811264038 */

 0xE6u, 0x01u, 0x0Au, 0x00u, /* Tap(13), 0.0781829357147217 */

 0x9Fu, 0xF4u, 0x0Au, 0x00u, /* Tap(14), 0.0855902433395386 */

 0xC6u, 0x74u, 0x0Bu, 0x00u, /* Tap(15), 0.0895011425018311 */

 0xC6u, 0x74u, 0x0Bu, 0x00u, /* Tap(16), 0.0895011425018311 */

 0x9Fu, 0xF4u, 0x0Au, 0x00u, /* Tap(17), 0.0855902433395386 */

 0xE6u, 0x01u, 0x0Au, 0x00u, /* Tap(18), 0.0781829357147217 */

 0xCBu, 0xB5u, 0x08u, 0x00u, /* Tap(19), 0.0680478811264038 */

 0x7Cu, 0x31u, 0x07u, 0x00u, /* Tap(20), 0.0561976432800293 */

 0x7Bu, 0x99u, 0x05u, 0x00u, /* Tap(21), 0.0437463521957397 */

 0xB0u, 0x10u, 0x04u, 0x00u, /* Tap(22), 0.0317592620849609 */

 0x08u, 0xB4u, 0x02u, 0x00u, /* Tap(23), 0.0211191177368164 */

 0x3Du, 0x97u, 0x01u, 0x00u, /* Tap(24), 0.0124279260635376 */

 0x50u, 0xC3u, 0x00u, 0x00u, /* Tap(25), 0.00596046447753906 */

 0xC7u, 0x36u, 0x00u, 0x00u, /* Tap(26), 0.00167167186737061 */

 0x91u, 0xE7u, 0xFFu, 0x00u, /* Tap(27), -0.000745654106140137 */

 0x0Au, 0xC6u, 0xFFu, 0x00u, /* Tap(28), -0.00176882743835449 */

 0x9Bu, 0xC0u, 0xFFu, 0x00u, /* Tap(29), -0.00193464756011963 */

 0x26u, 0xC7u, 0xFFu, 0x00u, /* Tap(30), -0.00173497200012207 */

 0xBEu, 0xCDu, 0xFFu, 0x00u, /* Tap(31), -0.00153374671936035 */
};


/*******************************************************************************
* ChannelB filter coefficients.
* Filter Type is FIR
*******************************************************************************/

/* Renamed array for backward compatibility.
*  Should not be used in new designs.
*/
#define ChannelBFirCoefficients Filter_ChannelBFirCoefficients

/* Number of FIR filter taps are: 32 */

const uint8 CYCODE Filter_ChannelBFirCoefficients[Filter_FIR_B_SIZE] = 
{
 0xBEu, 0xCDu, 0xFFu, 0x00u, /* Tap(0), -0.00153374671936035 */

 0x26u, 0xC7u, 0xFFu, 0x00u, /* Tap(1), -0.00173497200012207 */

 0x9Bu, 0xC0u, 0xFFu, 0x00u, /* Tap(2), -0.00193464756011963 */

 0x0Au, 0xC6u, 0xFFu, 0x00u, /* Tap(3), -0.00176882743835449 */

 0x91u, 0xE7u, 0xFFu, 0x00u, /* Tap(4), -0.000745654106140137 */

 0xC7u, 0x36u, 0x00u, 0x00u, /* Tap(5), 0.00167167186737061 */

 0x50u, 0xC3u, 0x00u, 0x00u, /* Tap(6), 0.00596046447753906 */

 0x3Du, 0x97u, 0x01u, 0x00u, /* Tap(7), 0.0124279260635376 */

 0x08u, 0xB4u, 0x02u, 0x00u, /* Tap(8), 0.0211191177368164 */

 0xB0u, 0x10u, 0x04u, 0x00u, /* Tap(9), 0.0317592620849609 */

 0x7Bu, 0x99u, 0x05u, 0x00u, /* Tap(10), 0.0437463521957397 */

 0x7Cu, 0x31u, 0x07u, 0x00u, /* Tap(11), 0.0561976432800293 */

 0xCBu, 0xB5u, 0x08u, 0x00u, /* Tap(12), 0.0680478811264038 */

 0xE6u, 0x01u, 0x0Au, 0x00u, /* Tap(13), 0.0781829357147217 */

 0x9Fu, 0xF4u, 0x0Au, 0x00u, /* Tap(14), 0.0855902433395386 */

 0xC6u, 0x74u, 0x0Bu, 0x00u, /* Tap(15), 0.0895011425018311 */

 0xC6u, 0x74u, 0x0Bu, 0x00u, /* Tap(16), 0.0895011425018311 */

 0x9Fu, 0xF4u, 0x0Au, 0x00u, /* Tap(17), 0.0855902433395386 */

 0xE6u, 0x01u, 0x0Au, 0x00u, /* Tap(18), 0.0781829357147217 */

 0xCBu, 0xB5u, 0x08u, 0x00u, /* Tap(19), 0.0680478811264038 */

 0x7Cu, 0x31u, 0x07u, 0x00u, /* Tap(20), 0.0561976432800293 */

 0x7Bu, 0x99u, 0x05u, 0x00u, /* Tap(21), 0.0437463521957397 */

 0xB0u, 0x10u, 0x04u, 0x00u, /* Tap(22), 0.0317592620849609 */

 0x08u, 0xB4u, 0x02u, 0x00u, /* Tap(23), 0.0211191177368164 */

 0x3Du, 0x97u, 0x01u, 0x00u, /* Tap(24), 0.0124279260635376 */

 0x50u, 0xC3u, 0x00u, 0x00u, /* Tap(25), 0.00596046447753906 */

 0xC7u, 0x36u, 0x00u, 0x00u, /* Tap(26), 0.00167167186737061 */

 0x91u, 0xE7u, 0xFFu, 0x00u, /* Tap(27), -0.000745654106140137 */

 0x0Au, 0xC6u, 0xFFu, 0x00u, /* Tap(28), -0.00176882743835449 */

 0x9Bu, 0xC0u, 0xFFu, 0x00u, /* Tap(29), -0.00193464756011963 */

 0x26u, 0xC7u, 0xFFu, 0x00u, /* Tap(30), -0.00173497200012207 */

 0xBEu, 0xCDu, 0xFFu, 0x00u, /* Tap(31), -0.00153374671936035 */
};

