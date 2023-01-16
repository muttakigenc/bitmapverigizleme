#pragma once

class bitVektör {
	char* veri;
	public:
	bitVektör();
	bitVektör(const bitVektör& c);
	bitVektör(bitVektör&& m);
	bitVektör(const void* buffer, size_t uzunluk, size_t boyut = sizeof(char));
	const char operator()(const size_t index) const;
	const bool operator[](const size_t index) const;
	bool operator+=(bool eklenen);
	operator const char* ();
	size_t uzunluk;
};