/**
	variadichelper.h
	Purpose: To ease variadic arguments/types operations
	@author Moataz Metwally
	@version 1.0 27/10/2022
*/

#ifndef VARIADICHELPER_H
#define VARIADICHELPER_H

#include <iostream>

// Get Sizeof the sum of all Variadic arguments types
template <typename... Types>
struct VariadicSizeOf;

template <typename T>
struct VariadicSizeOf<T>
{
    static constexpr auto Size = (sizeof(T));
};

template <typename T, typename... Ts>
struct VariadicSizeOf<T, Ts...>
{
    static constexpr auto Size = (sizeof(T) + VariadicSizeOf<Ts...>::Size);
};

// Store All variadic parameters to a given memory address

struct StoreVariadicParameters
{

    template <typename T1, typename... Ts>
    static void store(uint8_t *tmp_ptr, T1 &t1, Ts &...ts)
    {
        assert(tmp_ptr!= nullptr);
        memcpy(tmp_ptr, &t1, sizeof(t1));
        tmp_ptr += sizeof(t1);
        return store(tmp_ptr, ts...);
    }

    template <typename... Ts>
    static void store(uint8_t *tmp_ptr)
    {
        assert(tmp_ptr!= nullptr);
        return;
    }
};

// Retreive All variadic parameters from a given memory address

struct RetreiveVariadicParameters
{

  	template <typename... Ts>
	static void retrieveData(uint8_t *tmp_ptr)
	{
        assert(tmp_ptr!= nullptr);
		return;
	}

	template <typename T1, typename... Ts>
	static void retrieveData(uint8_t *tmp_ptr, T1 &t1, Ts &...ts)
	{
        assert(tmp_ptr!= nullptr);
		memcpy(&t1, tmp_ptr, sizeof(t1));
		tmp_ptr += sizeof(T1);
		return retrieveData(tmp_ptr, ts...);
	}
};

#endif // VARIADICHELPER_H