#include <stdio.h>
#include "bitmap.h"
#include <string.h>
#include "verigizleme.h"
using namespace verigizleme;

int main() {
	try {
		bitmap b = "A.bmp";
		/*verigizle(b.g�vde.bit24, b.bilgiBa�l���.boyut, "Merh. Lena Daha Kolay. Deneyin");
		b.kaydet("B.bmp");*/
		bitmap c = "B.bmp";
		//printf(veri��z(c.g�vde.bit24, c.bilgiBa�l���.boyut));
		printf("%lf %lf %d",get2Dpsnr(b.g�vde.bit24, c.g�vde.bit24, b.bilgiBa�l���.geni�lik, b.bilgiBa�l���.y�kseklik), get2DMse(b.g�vde.bit24, c.g�vde.bit24, b.bilgiBa�l���.geni�lik, b.bilgiBa�l���.y�kseklik), kapasite(b.g�vde.bit24,b.bilgiBa�l���.boyut));
	}
	catch (const bitmap::istisna& istisnakodu) {
		fprintf(stderr, "isnisna kodu: %d", istisnakodu);
	}
	return 0;
}