#include <stdio.h>
#include "bitmap.h"
#include <string.h>
#include "verigizleme.h"
using namespace verigizleme;

int main() {
	try {
		bitmap b = "A.bmp";
		/*verigizle(b.gövde.bit24, b.bilgiBaþlýðý.boyut, "Merh. Lena Daha Kolay. Deneyin");
		b.kaydet("B.bmp");*/
		bitmap c = "B.bmp";
		//printf(veriçöz(c.gövde.bit24, c.bilgiBaþlýðý.boyut));
		printf("%lf %lf %d",get2Dpsnr(b.gövde.bit24, c.gövde.bit24, b.bilgiBaþlýðý.geniþlik, b.bilgiBaþlýðý.yükseklik), get2DMse(b.gövde.bit24, c.gövde.bit24, b.bilgiBaþlýðý.geniþlik, b.bilgiBaþlýðý.yükseklik), kapasite(b.gövde.bit24,b.bilgiBaþlýðý.boyut));
	}
	catch (const bitmap::istisna& istisnakodu) {
		fprintf(stderr, "isnisna kodu: %d", istisnakodu);
	}
	return 0;
}