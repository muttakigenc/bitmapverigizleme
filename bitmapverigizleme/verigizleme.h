#pragma once
#include "bitvektör.h"
#include <cmath>

namespace verigizleme {

	template<typename t>
	void verigizle(t* gövde, size_t gövdeuzunluk, const bitVektör& mesaj) {
		size_t pixelmiktarý = gövdeuzunluk / sizeof(*gövde);
		auto j = 0;
		for (size_t i = 0; i < pixelmiktarý - 1 && j < mesaj.uzunluk; i++) {
			auto& pixel = gövde[i], & komþupixel = gövde[i + 1];
			auto fark = pixel.kýrmýzý - komþupixel.kýrmýzý;
			if (abs(fark) > 3) {
				pixel.LSB.kýrmýzý = mesaj[j];
				komþupixel.kýrmýzý = pixel.kýrmýzý - fark;
				j++; i++;
			}
			else if (abs(fark = pixel.yeþil - komþupixel.yeþil) > 3) {
				pixel.LSB.yeþil = mesaj[j];
				komþupixel.yeþil = pixel.yeþil - fark;
				j++; i++;
			}
			else	if (abs(fark = pixel.mavi - komþupixel.mavi) > 3) {
				pixel.LSB.mavi = mesaj[j];
				komþupixel.mavi = pixel.mavi - fark;
				j++; i++;
			}
			else if (abs(fark = pixel.opaklýk - komþupixel.opaklýk) > 3) {
				pixel.LSB.opaklýk = mesaj[j];
				komþupixel.opaklýk = pixel.opaklýk - fark;
				j++; i++;
			}
		}
	}

	template<typename t>
	void verigizle(t* gövde, size_t gövdeuzunluk, const char* buffer) { verigizle(gövde, gövdeuzunluk, { buffer,strlen(buffer) + 1 }); };

	template<typename t>
	bitVektör veriçöz(t* gövde, size_t gövdeuzunluk, char sonlandýrýcý = 0x00) {
		bitVektör yeni;
		size_t pixelmiktarý = gövdeuzunluk / sizeof(*gövde);
		for (size_t i = 0; i < pixelmiktarý - 1 && (yeni.uzunluk == 0 || (yeni.uzunluk % 8 > 0 || yeni(yeni.uzunluk / 8) != sonlandýrýcý)); i++) {
			auto& pixel = gövde[i], & komþupixel = gövde[i + 1];
			if (abs(pixel.kýrmýzý - komþupixel.kýrmýzý) > 3) {
				yeni += pixel.LSB.kýrmýzý;
				i++;
			}
			else if (abs(pixel.yeþil - komþupixel.yeþil) > 3) {
				yeni += pixel.LSB.yeþil;
				i++;
			}
			else if (abs(pixel.mavi - komþupixel.mavi) > 3) {
				yeni += pixel.LSB.mavi;
				i++;
			}
			else if (abs(pixel.opaklýk - komþupixel.opaklýk) > 3) {
				yeni += pixel.LSB.opaklýk;
				i++;
			}
		}
		return yeni;
	}

	template<typename t>
	double get2DMse(t* gövde1, t* gövde2, size_t geniþlik, size_t yükseklik) {
		size_t rtoplam = 0, gtoplam = 0, btoplam = 0, atoplam = 0;
		auto uzunluk = geniþlik * yükseklik;
		for (size_t i = 0; i < uzunluk; i++) {
			rtoplam += pow(gövde1[i].kýrmýzý - gövde2[i].kýrmýzý, 2);
			gtoplam += pow(gövde1[i].yeþil - gövde2[i].yeþil, 2);
			btoplam += pow(gövde1[i].mavi - gövde2[i].mavi, 2);
			atoplam += pow(gövde1[i].opaklýk - gövde2[i].opaklýk, 2);
		}
		double payda = uzunluk;
		auto rmse = double(rtoplam) / payda, gmse = double(gtoplam) / payda, bmse = double(btoplam) / payda, amse = double(atoplam) / payda;
		return (rmse + gmse + bmse + amse) / (3 + (atoplam > 0));
	}

	template<typename t>
	auto get2Dpsnr(t* gövde1, t* gövde2, size_t geniþlik, size_t yükseklik) {
		return 10 * log10(pow(255.0, 2.0) / get2DMse(gövde1, gövde2, geniþlik, yükseklik));
	}

	template<typename t>
	auto kapasite(t* gövde, size_t gövdeuzunluk) {
		size_t pixelmiktarý = gövdeuzunluk / sizeof(*gövde);
		auto j = 0;
		for (size_t i = 0; i < pixelmiktarý - 1; i++) {
			auto& pixel = gövde[i], & komþupixel = gövde[i + 1];
			auto fark = pixel.kýrmýzý - komþupixel.kýrmýzý;
			if (abs(fark) > 3) {
				j++; i++;
			}
			else if (abs(fark = pixel.yeþil - komþupixel.yeþil) > 3) {
				j++; i++;
			}
			else	if (abs(fark = pixel.mavi - komþupixel.mavi) > 3) {
				j++; i++;
			}
			else if (abs(fark = pixel.opaklýk - komþupixel.opaklýk) > 3) {
				j++; i++;
			}
		}
		return j;
	}
}