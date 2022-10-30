#include <stddef.h>
#include <iostream>
#include <string.h>
#include <assert.h>
#include <utility>
#include "variadichelper.h"

template <typename... Args>
class GenericContainer
{
public:
	//harden the class from any misuse.
	GenericContainer(void) = delete;
	GenericContainer(const GenericContainer &) = delete;
	GenericContainer &operator=(const GenericContainer &) = delete;
	GenericContainer(GenericContainer &&) = delete;
	GenericContainer &operator=(GenericContainer &&) = delete;

	//The usable Construtor.
	GenericContainer(Args... args) : data{nullptr}
	{

		if (nullptr != data)
			delete[] data;

		data = new uint8_t[len];
		uint8_t *tmp_ptr = data;
		StoreVariadicParameters::store(tmp_ptr, args...);
	}
	~GenericContainer()
	{
		delete[] data;
	}

	template <typename... NewArgs>
	void get_data(NewArgs &...out_args)
	{
		assert(data!= nullptr);
		constexpr size_t newLen = VariadicSizeOf<NewArgs...>::Size;
		static_assert(newLen == len, "Size of the getdata arguments must be equal to the data stored");
		uint8_t *tmp_ptr = data;
		RetreiveVariadicParameters::retrieveData(tmp_ptr, out_args...);
	}

private:
	uint8_t *data = nullptr;
	static const size_t len = VariadicSizeOf<Args...>::Size;
};

int main()
{
	GenericContainer c1{1684234849, 'n', 87.8, 0.1F, 8}; // Initializes a GenericContainer<int, char> object
	char a1 = '1', a2, a3, a4, a5;
	int b;
	double c;
	float f;
	int z, u;
	// Test with the same size of data but with different number of parameters.
	c1.get_data(a1, a2, a3, a4, a5, c, f, z);

	assert(c == 87.8);
	assert(f == 0.1F);
	assert(z == 8);

	c1.get_data(z, a2, c, f, u);

	assert(z == 1684234849);
	assert(a2 == 'n');
	assert(c == 87.8);
	assert(f == 0.1F);
	assert(u == 8);

	std::cout << "OK" << std::endl;
	
}