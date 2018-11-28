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

/* Number of FIR filter taps are: 25 */

const uint8 CYCODE Filter_ChannelAFirCoefficients[Filter_FIR_A_SIZE] = 
{
 0xA6u, 0x21u, 0x00u, 0x00u, /* Tap(0), 0.00102686882019043 */

 0x04u, 0x2Eu, 0x00u, 0x00u, /* Tap(1), 0.0014042854309082 */

 0xF4u, 0x45u, 0x00u, 0x00u, /* Tap(2), 0.00213479995727539 */

 0x24u, 0x68u, 0x00u, 0x00u, /* Tap(3), 0.00317811965942383 */

 0x8Fu, 0x92u, 0x00u, 0x00u, /* Tap(4), 0.00447261333465576 */

 0x9Au, 0xC2u, 0x00u, 0x00u, /* Tap(5), 0.00593876838684082 */

 0x47u, 0xF5u, 0x00u, 0x00u, /* Tap(6), 0.00748527050018311 */

 0x5Fu, 0x27u, 0x01u, 0x00u, /* Tap(7), 0.00901401042938232 */

 0xAFu, 0x55u, 0x01u, 0x00u, /* Tap(8), 0.0104273557662964 */

 0x3Cu, 0x7Du, 0x01u, 0x00u, /* Tap(9), 0.011634349822998 */

 0x7Au, 0x9Bu, 0x01u, 0x00u, /* Tap(10), 0.0125572681427002 */

 0x72u, 0xAEu, 0x01u, 0x00u, /* Tap(11), 0.0131361484527588 */

 0xE8u, 0xB4u, 0x01u, 0x00u, /* Tap(12), 0.0133333206176758 */

 0x72u, 0xAEu, 0x01u, 0x00u, /* Tap(13), 0.0131361484527588 */

 0x7Au, 0x9Bu, 0x01u, 0x00u, /* Tap(14), 0.0125572681427002 */

 0x3Cu, 0x7Du, 0x01u, 0x00u, /* Tap(15), 0.011634349822998 */

 0xAFu, 0x55u, 0x01u, 0x00u, /* Tap(16), 0.0104273557662964 */

 0x5Fu, 0x27u, 0x01u, 0x00u, /* Tap(17), 0.00901401042938232 */

 0x47u, 0xF5u, 0x00u, 0x00u, /* Tap(18), 0.00748527050018311 */

 0x9Au, 0xC2u, 0x00u, 0x00u, /* Tap(19), 0.00593876838684082 */

 0x8Fu, 0x92u, 0x00u, 0x00u, /* Tap(20), 0.00447261333465576 */

 0x24u, 0x68u, 0x00u, 0x00u, /* Tap(21), 0.00317811965942383 */

 0xF4u, 0x45u, 0x00u, 0x00u, /* Tap(22), 0.00213479995727539 */

 0x04u, 0x2Eu, 0x00u, 0x00u, /* Tap(23), 0.0014042854309082 */

 0xA6u, 0x21u, 0x00u, 0x00u, /* Tap(24), 0.00102686882019043 */
};


/*******************************************************************************
* ChannelB filter coefficients.
* Filter Type is FIR
*******************************************************************************/

/* Renamed array for backward compatibility.
*  Should not be used in new designs.
*/
#define ChannelBFirCoefficients Filter_ChannelBFirCoefficients

/* Number of FIR filter taps are: 25 */

const uint8 CYCODE Filter_ChannelBFirCoefficients[Filter_FIR_B_SIZE] = 
{
 0xA6u, 0x21u, 0x00u, 0x00u, /* Tap(0), 0.00102686882019043 */

 0x04u, 0x2Eu, 0x00u, 0x00u, /* Tap(1), 0.0014042854309082 */

 0xF4u, 0x45u, 0x00u, 0x00u, /* Tap(2), 0.00213479995727539 */

 0x24u, 0x68u, 0x00u, 0x00u, /* Tap(3), 0.00317811965942383 */

 0x8Fu, 0x92u, 0x00u, 0x00u, /* Tap(4), 0.00447261333465576 */

 0x9Au, 0xC2u, 0x00u, 0x00u, /* Tap(5), 0.00593876838684082 */

 0x47u, 0xF5u, 0x00u, 0x00u, /* Tap(6), 0.00748527050018311 */

 0x5Fu, 0x27u, 0x01u, 0x00u, /* Tap(7), 0.00901401042938232 */

 0xAFu, 0x55u, 0x01u, 0x00u, /* Tap(8), 0.0104273557662964 */

 0x3Cu, 0x7Du, 0x01u, 0x00u, /* Tap(9), 0.011634349822998 */

 0x7Au, 0x9Bu, 0x01u, 0x00u, /* Tap(10), 0.0125572681427002 */

 0x72u, 0xAEu, 0x01u, 0x00u, /* Tap(11), 0.0131361484527588 */

 0xE8u, 0xB4u, 0x01u, 0x00u, /* Tap(12), 0.0133333206176758 */

 0x72u, 0xAEu, 0x01u, 0x00u, /* Tap(13), 0.0131361484527588 */

 0x7Au, 0x9Bu, 0x01u, 0x00u, /* Tap(14), 0.0125572681427002 */

 0x3Cu, 0x7Du, 0x01u, 0x00u, /* Tap(15), 0.011634349822998 */

 0xAFu, 0x55u, 0x01u, 0x00u, /* Tap(16), 0.0104273557662964 */

 0x5Fu, 0x27u, 0x01u, 0x00u, /* Tap(17), 0.00901401042938232 */

 0x47u, 0xF5u, 0x00u, 0x00u, /* Tap(18), 0.00748527050018311 */

 0x9Au, 0xC2u, 0x00u, 0x00u, /* Tap(19), 0.00593876838684082 */

 0x8Fu, 0x92u, 0x00u, 0x00u, /* Tap(20), 0.00447261333465576 */

 0x24u, 0x68u, 0x00u, 0x00u, /* Tap(21), 0.00317811965942383 */

 0xF4u, 0x45u, 0x00u, 0x00u, /* Tap(22), 0.00213479995727539 */

 0x04u, 0x2Eu, 0x00u, 0x00u, /* Tap(23), 0.0014042854309082 */

 0xA6u, 0x21u, 0x00u, 0x00u, /* Tap(24), 0.00102686882019043 */
};

