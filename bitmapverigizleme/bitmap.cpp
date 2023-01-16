#include <stdio.h>
#include "bitmap.h"


bitmap::bitmap(const char* dosyaad�) :g�vde({ NULL }), palet(NULL)
{
	auto dosya = fopen(dosyaad�, "rb");
	if (dosya == NULL)
		throw dosyaA��lamad�;
	fread(&dosyaBa�l���, sizeof(dosyaBa�l���), 1, dosya);
	if (dosyaBa�l���.T�r != dosyaBa�l���.biti�lemresmi)
	{
		fclose(dosya);
		throw dosyaBit��lemResmiDe�il;
	}
	fread(&bilgiBa�l���, sizeof(bilgiBa�l���), 1, dosya);
	auto paletboyutu = (dosyaBa�l���.bitDenkle�tirmesi - sizeof(bilgiBa�l���) - sizeof(dosyaBa�l���));
	palet = (bit32pixel*)new unsigned char[paletboyutu];
	fread(palet, 1, paletboyutu, dosya);
	g�vde = { new unsigned char[bilgiBa�l���.boyut] };
	if (!g�vde.hamveri)
	{
		fclose(dosya);
		throw bellekA��lamad�;
	}
	fread(g�vde.hamveri, 1, bilgiBa�l���.boyut, dosya);
	if (g�vde.hamveri == NULL)
	{
		fclose(dosya);
		throw bitmapG�vdesiOkunamad�;
	}

	fclose(dosya);
}
bitmap::~bitmap() {
	if (g�vde.hamveri) delete[]g�vde.hamveri;
	if (palet) delete[](unsigned char*)palet;
}
void bitmap::kaydet(const char* dosyaad�) {
	auto dosya = fopen(dosyaad�, "wb");
	if (dosya == NULL)
		throw dosyaA��lamad�;
	fwrite(&dosyaBa�l���, sizeof(dosyaBa�l���), 1, dosya);
	fwrite(&bilgiBa�l���, sizeof(bilgiBa�l���), 1, dosya);
	fwrite(palet, 1, dosyaBa�l���.bitDenkle�tirmesi - sizeof(bilgiBa�l���) - sizeof(dosyaBa�l���), dosya);
	if (!g�vde.hamveri)
	{
		fclose(dosya);
		throw bitmapG�vdesiOkunamad�;
	}
	fwrite(g�vde.hamveri, 1, bilgiBa�l���.boyut, dosya);
	fclose(dosya);
}

unsigned char bitmap::bit8pixel::opakl�k = 0;
unsigned char bitmap::bit16pixel::opakl�k = 0;
unsigned char bitmap::bit24pixel::opakl�k = 0;
bool bitmap::bit8pixel::LSB::opakl�k = 0;
bool bitmap::bit16pixel::LSB::opakl�k = 0;
bool bitmap::bit24pixel::LSB::opakl�k = 0;