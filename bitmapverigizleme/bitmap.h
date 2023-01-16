#pragma once

class bitmap {
	public:
#pragma pack(push, 1)
	enum istisna :unsigned char {
		dosyaAçýlamadý,
		dosyaBitÝþlemResmiDeðil,
		bellekAçýlamadý,
		bitmapGövdesiOkunamadý
	};
	struct {
		enum : unsigned short {
			bitiþlemresmi = 0x4D42
		} Tür;
		unsigned long boyut, :32, bitDenkleþtirmesi;
	} dosyaBaþlýðý;
	struct {
		unsigned long Yapýboyutu;
		long geniþlik;
		long yükseklik;
		unsigned short uçaklar;
		unsigned short renkDerinliði;
		enum :unsigned long { RGB, bitAlanlarý } sýkýþtýrma;
		unsigned long boyut;
		long xçözünürlük;
		long yçözünürlük;
		unsigned long paletMiktarý;
		unsigned long gerekliPaletMiktarý;
	} bilgiBaþlýðý;
	union bit8pixel {
		struct { unsigned char mavi : 2, yeþil : 3, kýrmýzý : 3; };
		struct LSB { unsigned char  mavi : 1, : 1, yeþil : 1, : 2, kýrmýzý : 1, : 2;	static bool opaklýk; } LSB;
		static unsigned char opaklýk;
	};
	union bit16pixel {
		struct { unsigned short mavi : 5, yeþil : 6, kýrmýzý : 5; };
		struct LSB { unsigned char  mavi : 1, : 4, yeþil : 1, : 5, kýrmýzý : 1, : 4; static bool opaklýk; } LSB;
		static unsigned char opaklýk;
	};
	union bit24pixel {
		struct { unsigned char  mavi : 8, yeþil : 8, kýrmýzý : 8; };
		struct LSB { unsigned char  mavi : 1, : 7, yeþil : 1, : 7, kýrmýzý : 1, : 7; static bool opaklýk; } LSB;
		static unsigned char opaklýk;
	};
	union bit32pixel {
		struct { unsigned char  mavi : 8, yeþil : 8, kýrmýzý : 8, opaklýk : 8; };
		struct { unsigned char  mavi : 1, : 7, yeþil : 1, : 7, kýrmýzý : 1, : 7, opaklýk : 1, : 7; } LSB;
	};
	bit32pixel* palet;
	union bitmapgovde {
		unsigned char* hamveri;
		bit8pixel* bit8;
		bit16pixel* bit16;
		bit24pixel* bit24;
		bit32pixel* bit32;
	} gövde;
#pragma pack(pop)
	bitmap(const char* dosyaadý);
	~bitmap();
	void kaydet(const char* dosyaadý);
};