#include "bitvektör.h"
#include <utility>
template <typename T>
T* hafizaal(T* alan, unsigned long uzunluk, unsigned long eskiuzunluk) {
	T* eski = alan;
	T* yeni = new T[uzunluk];
	if (yeni != 0) {
		for (unsigned long i = 0; i < eskiuzunluk && i < uzunluk; i++) yeni[i] = std::move(eski[i]);
		if (eski != 0) delete[] eski;
	}
	return yeni;
}

bitVektör::bitVektör() :uzunluk(0), veri(NULL) {};
bitVektör::bitVektör(const bitVektör& c) :uzunluk(c.uzunluk), veri(c.veri) {
};
bitVektör::bitVektör(bitVektör&& m) :uzunluk(m.uzunluk), veri(m.veri) {

};
bitVektör::bitVektör(const void* buffer, size_t uzunluk, size_t boyut) :veri((char*)buffer), uzunluk(uzunluk* boyut * 8) {}
const char bitVektör::operator()(const size_t index) const { return veri[index]; };
const bool bitVektör::operator[](const size_t index) const {
	union {
		char hamveri;
		struct {
			bool b7 : 1;
			bool b6 : 1;
			bool b5 : 1;
			bool b4 : 1;
			bool b3 : 1;
			bool b2 : 1;
			bool b1 : 1;
			bool b0 : 1;
		};
	} a = { veri[index / 8] };
	switch (index % 8) {
		case 0:return a.b0;
		case 1:return a.b1;
		case 2:return a.b2;
		case 3:return a.b3;
		case 4:return a.b4;
		case 5:return a.b5;
		case 6:return a.b6;
		case 7:return a.b7;
	}
}
bool bitVektör::operator+=(bool eklenen) {
	if (uzunluk % 8 == 0) veri = hafizaal(veri, (uzunluk / 8) + 1, uzunluk / 8);
	union {
		char* hamveri;
		struct {
			bool b7 : 1;
			bool b6 : 1;
			bool b5 : 1;
			bool b4 : 1;
			bool b3 : 1;
			bool b2 : 1;
			bool b1 : 1;
			bool b0 : 1;
		} *bytes;
	} _veri = { veri };
	auto& a = _veri.bytes[uzunluk / 8];
	switch (uzunluk % 8) {
		case 0:a.b0 = eklenen;
		case 1:a.b1 = eklenen;
		case 2:a.b2 = eklenen;
		case 3:a.b3 = eklenen;
		case 4:a.b4 = eklenen;
		case 5:a.b5 = eklenen;
		case 6:a.b6 = eklenen;
		case 7:a.b7 = eklenen;
	}
	uzunluk++;
	return eklenen;
}
bitVektör::operator const char* () { return veri; };