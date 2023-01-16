#include <stdio.h>
#include "bitmap.h"


bitmap::bitmap(const char* dosyaadý) :gövde({ NULL }), palet(NULL)
{
	auto dosya = fopen(dosyaadý, "rb");
	if (dosya == NULL)
		throw dosyaAçýlamadý;
	fread(&dosyaBaþlýðý, sizeof(dosyaBaþlýðý), 1, dosya);
	if (dosyaBaþlýðý.Tür != dosyaBaþlýðý.bitiþlemresmi)
	{
		fclose(dosya);
		throw dosyaBitÝþlemResmiDeðil;
	}
	fread(&bilgiBaþlýðý, sizeof(bilgiBaþlýðý), 1, dosya);
	auto paletboyutu = (dosyaBaþlýðý.bitDenkleþtirmesi - sizeof(bilgiBaþlýðý) - sizeof(dosyaBaþlýðý));
	palet = (bit32pixel*)new unsigned char[paletboyutu];
	fread(palet, 1, paletboyutu, dosya);
	gövde = { new unsigned char[bilgiBaþlýðý.boyut] };
	if (!gövde.hamveri)
	{
		fclose(dosya);
		throw bellekAçýlamadý;
	}
	fread(gövde.hamveri, 1, bilgiBaþlýðý.boyut, dosya);
	if (gövde.hamveri == NULL)
	{
		fclose(dosya);
		throw bitmapGövdesiOkunamadý;
	}

	fclose(dosya);
}
bitmap::~bitmap() {
	if (gövde.hamveri) delete[]gövde.hamveri;
	if (palet) delete[](unsigned char*)palet;
}
void bitmap::kaydet(const char* dosyaadý) {
	auto dosya = fopen(dosyaadý, "wb");
	if (dosya == NULL)
		throw dosyaAçýlamadý;
	fwrite(&dosyaBaþlýðý, sizeof(dosyaBaþlýðý), 1, dosya);
	fwrite(&bilgiBaþlýðý, sizeof(bilgiBaþlýðý), 1, dosya);
	fwrite(palet, 1, dosyaBaþlýðý.bitDenkleþtirmesi - sizeof(bilgiBaþlýðý) - sizeof(dosyaBaþlýðý), dosya);
	if (!gövde.hamveri)
	{
		fclose(dosya);
		throw bitmapGövdesiOkunamadý;
	}
	fwrite(gövde.hamveri, 1, bilgiBaþlýðý.boyut, dosya);
	fclose(dosya);
}

unsigned char bitmap::bit8pixel::opaklýk = 0;
unsigned char bitmap::bit16pixel::opaklýk = 0;
unsigned char bitmap::bit24pixel::opaklýk = 0;
bool bitmap::bit8pixel::LSB::opaklýk = 0;
bool bitmap::bit16pixel::LSB::opaklýk = 0;
bool bitmap::bit24pixel::LSB::opaklýk = 0;