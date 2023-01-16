#pragma once

class bitmap {
	public:
#pragma pack(push, 1)
	enum istisna :unsigned char {
		dosyaA��lamad�,
		dosyaBit��lemResmiDe�il,
		bellekA��lamad�,
		bitmapG�vdesiOkunamad�
	};
	struct {
		enum : unsigned short {
			biti�lemresmi = 0x4D42
		} T�r;
		unsigned long boyut, :32, bitDenkle�tirmesi;
	} dosyaBa�l���;
	struct {
		unsigned long Yap�boyutu;
		long geni�lik;
		long y�kseklik;
		unsigned short u�aklar;
		unsigned short renkDerinli�i;
		enum :unsigned long { RGB, bitAlanlar� } s�k��t�rma;
		unsigned long boyut;
		long x��z�n�rl�k;
		long y��z�n�rl�k;
		unsigned long paletMiktar�;
		unsigned long gerekliPaletMiktar�;
	} bilgiBa�l���;
	union bit8pixel {
		struct { unsigned char mavi : 2, ye�il : 3, k�rm�z� : 3; };
		struct LSB { unsigned char  mavi : 1, : 1, ye�il : 1, : 2, k�rm�z� : 1, : 2;	static bool opakl�k; } LSB;
		static unsigned char opakl�k;
	};
	union bit16pixel {
		struct { unsigned short mavi : 5, ye�il : 6, k�rm�z� : 5; };
		struct LSB { unsigned char  mavi : 1, : 4, ye�il : 1, : 5, k�rm�z� : 1, : 4; static bool opakl�k; } LSB;
		static unsigned char opakl�k;
	};
	union bit24pixel {
		struct { unsigned char  mavi : 8, ye�il : 8, k�rm�z� : 8; };
		struct LSB { unsigned char  mavi : 1, : 7, ye�il : 1, : 7, k�rm�z� : 1, : 7; static bool opakl�k; } LSB;
		static unsigned char opakl�k;
	};
	union bit32pixel {
		struct { unsigned char  mavi : 8, ye�il : 8, k�rm�z� : 8, opakl�k : 8; };
		struct { unsigned char  mavi : 1, : 7, ye�il : 1, : 7, k�rm�z� : 1, : 7, opakl�k : 1, : 7; } LSB;
	};
	bit32pixel* palet;
	union bitmapgovde {
		unsigned char* hamveri;
		bit8pixel* bit8;
		bit16pixel* bit16;
		bit24pixel* bit24;
		bit32pixel* bit32;
	} g�vde;
#pragma pack(pop)
	bitmap(const char* dosyaad�);
	~bitmap();
	void kaydet(const char* dosyaad�);
};