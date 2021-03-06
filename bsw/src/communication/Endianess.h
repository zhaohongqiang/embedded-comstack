/**
 * @file      Endianess.h
 * @author    dtuchscherer <daniel.tuchscherer@hs-heilbronn.de>
 * @brief     Endianess interface for byte-swapping
 * @details   This header interface allows byte-swapping between little-
 * 			  and big-endian machines.
 * @version   1.0
 * @copyright Copyright (c) 2015, dtuchscherer.
 *            All rights reserved.
 *
 *            Redistributions and use in source and binary forms, with
 *            or without modifications, are permitted provided that the
 *            following conditions are met: Redistributions of source code must
 *            retain the above copyright notice, this list of conditions and the
 *            following disclaimer.
 *
 *            Redistributions in binary form must reproduce the above copyright
 *            notice, this list of conditions and the following disclaimer in
 *            the documentation and/or other materials provided with the
 *            distribution.
 *
 *            Neither the name of the Heilbronn University nor the name of its
 *            contributors may be used to endorse or promote products derived
 *            from this software without specific prior written permission.
 *
 *            THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS “AS IS”
 *            AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 *            TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 *            PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE REGENTS
 *            OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *            SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *            LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *            USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *            AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *            LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *            ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *            POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ENDIANESS_H_
# define ENDIANESS_H_

/*******************************************************************************
 * MODULES USED
 *******************************************************************************/
# ifdef __unix__
#  include <endian.h>
# elif defined (_WIN32)
#  define BYTE_ORDER (LITTLE_ENDIAN)
# else
#  error "Please #define BYTE_ORDER of your system architecture."
# endif

/*******************************************************************************
 * DEFINITIONS AND MACROS
 *******************************************************************************/

/*******************************************************************************
 * TYPEDEFS, ENUMERATIONS, CLASSES
 *******************************************************************************/

/*******************************************************************************
 * EXPORTED VARIABLES
 *******************************************************************************/

/*******************************************************************************
 * EXPORTED FUNCTIONS
 *******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
template< typename T, size_t Sz >
T swap_bytes(const T& val) noexcept;

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief template specialization to swap an unsigned byte.
 * @return this will only return the byte again.
 */
template< >
inline uint8 swap_bytes< uint8, 1 >(const uint8& val) noexcept
{
    return val;
}

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief template specialization to swap an unsgined word.
 * @return an unsigned word with swapped bytes.
 */
template< >
inline uint16 swap_bytes< uint16, 2 >(const uint16& val) noexcept
{
    uint16 temp = 0U;
    temp  = ((val >> 8U) & 0x00FFU);
    temp |= ((val << 8U) & 0xFFFFU);
    return temp;
}

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief template specialization to swap an unsgined word.
 * @return a signed word with swapped bytes.
 */
template< >
inline sint16 swap_bytes< sint16, 2 >(const sint16& val) noexcept
{
    sint16 temp = 0;
    temp  = ((val >> 8) & 0x00FF);
    temp |= ((val << 8) & 0xFFFF);
    return temp;
}

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Template specialization for swapping 4 bytes of an unsgined double word.
 * @param[in] val the value to byte-swap
 * @return a byte-swapped unsigned double word
 */
template< >
inline uint32 swap_bytes< uint32, 4 >(const uint32& val) noexcept
{
    uint32 temp = 0UL;
    temp  = ((val >> 24U) & 0x000000FFUL); // byte 3 to 0
    temp |= ((val << 24U) & 0xFF000000UL); // byte 0 to 3
    temp |= ((val >> 8U)  & 0x0000FF00UL); // byte 2 to 1
    temp |= ((val << 8U)  & 0x00FF0000UL); // byte 1 to 2
    return temp;
}

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Template specialization for swapping 4 bytes of a double word.
 * @param[in] val the value to byte-swap
 * @return a byte-swapped unsigned double word
 */
template< >
inline sint32 swap_bytes< sint32, 4 >(const sint32& val) noexcept
{
    sint32 temp = 0L;
    temp  = ((val >> 24) & 0x000000FFL); // byte 3 to 0
    temp |= ((val << 24) & 0xFF000000L); // byte 0 to 3
    temp |= ((val >> 8)  & 0x0000FF00L); // byte 2 to 1
    temp |= ((val << 8)  & 0x00FF0000L); // byte 1 to 2
    return temp;
}

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Template specialization for swapping 8 bytes of unsigned quad word.
 * @param[in] val to swap the bytes
 * @return the swapped value
 */
template< >
inline uint64 swap_bytes< uint64, 8 >(const uint64& val) noexcept
{
    uint64 temp = 0ULL;
    temp  = ((val >> 56U) & 0x00000000000000FFULL); // byte 7 to 0
    temp |= ((val << 56U) & 0xFF00000000000000ULL); // byte 0 to 7
    temp |= ((val >> 40U) & 0x000000000000FF00ULL); // byte 6 to 1
    temp |= ((val << 40U) & 0x00FF000000000000ULL); // byte 1 to 6
    temp |= ((val >> 24U) & 0x0000000000FF0000ULL); // byte 5 to 2
    temp |= ((val << 24U) & 0x0000FF0000000000ULL); // byte 2 to 5
    temp |= ((val >> 8U)  & 0x00000000FF000000ULL); // byte 4 to 3
    temp |= ((val << 8U)  & 0x000000FF00000000ULL); // byte 3 to 4
    return temp;
}

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Template specialization for swapping 8 bytes of a signed quad word.
 * @param[in] val to swap the bytes
 * @return the swapped value
 */
template< >
inline sint64 swap_bytes< sint64, 8 >(const sint64& val) noexcept
{
    sint64 temp = 0LL;
    temp  = ((val >> 56U) & 0x00000000000000FFULL); // byte 7 to 0
    temp |= ((val << 56U) & 0xFF00000000000000ULL); // byte 0 to 7
    temp |= ((val >> 40U) & 0x000000000000FF00ULL); // byte 6 to 1
    temp |= ((val << 40U) & 0x00FF000000000000ULL); // byte 1 to 6
    temp |= ((val >> 24U) & 0x0000000000FF0000ULL); // byte 5 to 2
    temp |= ((val << 24U) & 0x0000FF0000000000ULL); // byte 2 to 5
    temp |= ((val >> 8U)  & 0x00000000FF000000ULL); // byte 4 to 3
    temp |= ((val << 8U)  & 0x000000FF00000000ULL); // byte 3 to 4
    return temp;
}

////////////////////////////////////////////////////////////////////////////////
template< >
inline float32 swap_bytes< float32, 4 >(const float32& fval) noexcept
{
    float32 float_swapped = 0.0F;
    float32 temp = fval;
    uint8* float_to_convert = reinterpret_cast< uint8* >(&temp);
    uint8* to_convert = reinterpret_cast< uint8* >(&float_swapped);
    to_convert[0] = float_to_convert[3];
    to_convert[1] = float_to_convert[2];
    to_convert[2] = float_to_convert[1];
    to_convert[3] = float_to_convert[0];
    return float_swapped;
}

////////////////////////////////////////////////////////////////////////////////
template< >
inline float64 swap_bytes< float64, 8 >(const float64& fval) noexcept
{
    float64 float_swapped = 0.0F;
    float64 temp = fval;
    uint8* float_to_convert = reinterpret_cast< uint8* >(&temp);
    uint8* to_convert = reinterpret_cast< uint8* >(&float_swapped);
    to_convert[0] = float_to_convert[7];
    to_convert[1] = float_to_convert[6];
    to_convert[2] = float_to_convert[5];
    to_convert[3] = float_to_convert[4];
    to_convert[4] = float_to_convert[3];
    to_convert[5] = float_to_convert[2];
    to_convert[6] = float_to_convert[1];
    to_convert[7] = float_to_convert[0];
    return float_swapped;
}

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Convert a value of type T from host-byte-order into network-byte-order
 * which is big endian. A byte swap is only necessary if the host is little
 * endian.
 * @tparam T is the type of the value to convert.
 * @param[in] value to convert.
 * @return the network-byte-order value.
 */
template< typename T >
inline T to_network(const T& value) noexcept
{
    T convert = value;

#if ( BYTE_ORDER == LITTLE_ENDIAN )
    convert = swap_bytes< T, sizeof(T) >(value);
#endif

    return convert;
}

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Convert a value of type T from network-byte-order to host-byte-order.
 * A byte swap is only necessary if the host is little endian.
 * @tparam T is the type of the value to convert.
 * @param[in] value to convert
 * @return the host-byte-order value.
 */
template< typename T >
inline T from_network(const T& value) noexcept
{
    T convert = value;

#if ( BYTE_ORDER == LITTLE_ENDIAN )
    convert = swap_bytes< T, sizeof(T) >(value);
#endif

    return convert;
}

#endif /* ENDIANESS_H_ */
