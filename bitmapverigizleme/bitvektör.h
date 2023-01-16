#pragma once

class bitVekt�r {
	char* veri;
	public:
	bitVekt�r();
	bitVekt�r(const bitVekt�r& c);
	bitVekt�r(bitVekt�r&& m);
	bitVekt�r(const void* buffer, size_t uzunluk, size_t boyut = sizeof(char));
	const char operator()(const size_t index) const;
	const bool operator[](const size_t index) const;
	bool operator+=(bool eklenen);
	operator const char* ();
	size_t uzunluk;
};