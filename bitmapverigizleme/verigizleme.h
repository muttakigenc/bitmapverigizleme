#pragma once
#include "bitvekt�r.h"
#include <cmath>

namespace verigizleme {

	template<typename t>
	void verigizle(t* g�vde, size_t g�vdeuzunluk, const bitVekt�r& mesaj) {
		size_t pixelmiktar� = g�vdeuzunluk / sizeof(*g�vde);
		auto j = 0;
		for (size_t i = 0; i < pixelmiktar� - 1 && j < mesaj.uzunluk; i++) {
			auto& pixel = g�vde[i], & kom�upixel = g�vde[i + 1];
			auto fark = pixel.k�rm�z� - kom�upixel.k�rm�z�;
			if (abs(fark) > 3) {
				pixel.LSB.k�rm�z� = mesaj[j];
				kom�upixel.k�rm�z� = pixel.k�rm�z� - fark;
				j++; i++;
			}
			else if (abs(fark = pixel.ye�il - kom�upixel.ye�il) > 3) {
				pixel.LSB.ye�il = mesaj[j];
				kom�upixel.ye�il = pixel.ye�il - fark;
				j++; i++;
			}
			else	if (abs(fark = pixel.mavi - kom�upixel.mavi) > 3) {
				pixel.LSB.mavi = mesaj[j];
				kom�upixel.mavi = pixel.mavi - fark;
				j++; i++;
			}
			else if (abs(fark = pixel.opakl�k - kom�upixel.opakl�k) > 3) {
				pixel.LSB.opakl�k = mesaj[j];
				kom�upixel.opakl�k = pixel.opakl�k - fark;
				j++; i++;
			}
		}
	}

	template<typename t>
	void verigizle(t* g�vde, size_t g�vdeuzunluk, const char* buffer) { verigizle(g�vde, g�vdeuzunluk, { buffer,strlen(buffer) + 1 }); };

	template<typename t>
	bitVekt�r veri��z(t* g�vde, size_t g�vdeuzunluk, char sonland�r�c� = 0x00) {
		bitVekt�r yeni;
		size_t pixelmiktar� = g�vdeuzunluk / sizeof(*g�vde);
		for (size_t i = 0; i < pixelmiktar� - 1 && (yeni.uzunluk == 0 || (yeni.uzunluk % 8 > 0 || yeni(yeni.uzunluk / 8) != sonland�r�c�)); i++) {
			auto& pixel = g�vde[i], & kom�upixel = g�vde[i + 1];
			if (abs(pixel.k�rm�z� - kom�upixel.k�rm�z�) > 3) {
				yeni += pixel.LSB.k�rm�z�;
				i++;
			}
			else if (abs(pixel.ye�il - kom�upixel.ye�il) > 3) {
				yeni += pixel.LSB.ye�il;
				i++;
			}
			else if (abs(pixel.mavi - kom�upixel.mavi) > 3) {
				yeni += pixel.LSB.mavi;
				i++;
			}
			else if (abs(pixel.opakl�k - kom�upixel.opakl�k) > 3) {
				yeni += pixel.LSB.opakl�k;
				i++;
			}
		}
		return yeni;
	}

	template<typename t>
	double get2DMse(t* g�vde1, t* g�vde2, size_t geni�lik, size_t y�kseklik) {
		size_t rtoplam = 0, gtoplam = 0, btoplam = 0, atoplam = 0;
		auto uzunluk = geni�lik * y�kseklik;
		for (size_t i = 0; i < uzunluk; i++) {
			rtoplam += pow(g�vde1[i].k�rm�z� - g�vde2[i].k�rm�z�, 2);
			gtoplam += pow(g�vde1[i].ye�il - g�vde2[i].ye�il, 2);
			btoplam += pow(g�vde1[i].mavi - g�vde2[i].mavi, 2);
			atoplam += pow(g�vde1[i].opakl�k - g�vde2[i].opakl�k, 2);
		}
		double payda = uzunluk;
		auto rmse = double(rtoplam) / payda, gmse = double(gtoplam) / payda, bmse = double(btoplam) / payda, amse = double(atoplam) / payda;
		return (rmse + gmse + bmse + amse) / (3 + (atoplam > 0));
	}

	template<typename t>
	auto get2Dpsnr(t* g�vde1, t* g�vde2, size_t geni�lik, size_t y�kseklik) {
		return 10 * log10(pow(255.0, 2.0) / get2DMse(g�vde1, g�vde2, geni�lik, y�kseklik));
	}

	template<typename t>
	auto kapasite(t* g�vde, size_t g�vdeuzunluk) {
		size_t pixelmiktar� = g�vdeuzunluk / sizeof(*g�vde);
		auto j = 0;
		for (size_t i = 0; i < pixelmiktar� - 1; i++) {
			auto& pixel = g�vde[i], & kom�upixel = g�vde[i + 1];
			auto fark = pixel.k�rm�z� - kom�upixel.k�rm�z�;
			if (abs(fark) > 3) {
				j++; i++;
			}
			else if (abs(fark = pixel.ye�il - kom�upixel.ye�il) > 3) {
				j++; i++;
			}
			else	if (abs(fark = pixel.mavi - kom�upixel.mavi) > 3) {
				j++; i++;
			}
			else if (abs(fark = pixel.opakl�k - kom�upixel.opakl�k) > 3) {
				j++; i++;
			}
		}
		return j;
	}
}