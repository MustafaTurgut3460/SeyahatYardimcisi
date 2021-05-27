#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include "Tesisler.h"

//FONKSIYON PROTOTIPLERI
void anaMenuYazdir();
void istanbulYazdir();
void ankaraYazdir();
void izmirYazdir();
void vanYazdir();
void antalyaYazdir();
//void iaTesisYazdir();

//yorum ekleme
void YorumEkle();
void YorumListele();
void YorumOku();

//Seyahat bilgileri
void SeyahatBilgisiYazdir();
void SeyahatTarihSor();

//kullanici ekleme
void KullaniciOku();
void KullaniciEkle();
void KullaniciListele();

//hata yakalama
void hataYakala(int *x, int max, int min);

typedef struct
{ //her bir struct ayri sehirlerin bilgilerini tutar
	char riskGrup[15] = "Yuksek Riskli", virusSayi[10] = "Artista", sehirDurum[350] = "Restorantlar, esnaflar vs. kapalidir. Haftasonu yasagi devam ediyor. Haftaici 21.00  dan sonra sokaga cikma yasagi vardir.";
	int asiOran = 18, tehlikeOran = 78;
} Istanbul;

typedef struct
{
	char riskGrup[15] = "Riskli", virusSayi[10] = "Artista", sehirDurum[350] = "Restorantlar, esnaflar vs. haftaici saat 20.00 a kadar aciktir. Pazar gunu sokaga cikma yasagi vardir.";
	int asiOran = 26, tehlikeOran = 61;
} Ankara;

typedef struct
{
	char riskGrup[15] = "Yuksek Riskli", virusSayi[10] = "Artista", sehirDurum[350] = "Restorantlar, esnaflar vs. kapalidir. Haftasonu yasagi devam ediyor. Haftaici 21.00  dan sonra sokaga cikma yasagi vardir.";
	int asiOran = 23, tehlikeOran = 73;
} Izmir;

typedef struct
{
	char riskGrup[15] = "Dusuk Riskli", virusSayi[10] = "Dususte", sehirDurum[350] = "Restorantlar, esnaflar vs. pazar g�n� haric aciktir. Haftasonu yasagi yoktur. Her gun 21.00  dan sonra yasak vardir.";
	int asiOran = 21, tehlikeOran = 29;
} Van;

typedef struct
{
	char riskGrup[15] = "Orta Riskli", virusSayi[10] = "Artista", sehirDurum[350] = "Restorantlar, esnaflar vs. haftaici aciktir. Pazar gunu sokaga cikma yasagi vardir. ";
	int asiOran = 27, tehlikeOran = 46;
} Antalya;

typedef struct
{
	char isim[20];
	char yorum[200];
	float puan;

} Kullanici; //Kullanici yorumu icin herbir kullanicinin ozellikleri struct ile tuttuk

typedef struct
{
	char SeyahatTipi[50];
	int SeyahatTehlikesi;
	int SeyahatUcreti;
	char SeyahatSuresi[20];
	char SeyahatSaati[10];
	char ad[30];
} SeyahatBilgi; //Her kullanicinin seyahat bilgileri icin struct olusturduk

//GLOBAL DEGISKENLER
Istanbul istanbul;
Ankara ankara;
Izmir izmir;
Van van;
Antalya antalya;
SeyahatBilgi seyahatbilgi[100], *sp = seyahatbilgi;

char yuzde = '%', sehirler[5][10] = {"Istanbul", "Ankara", "Izmir", "Van", "Antalya"};
char *gidileceksehir, otobusFirmalari[10][20] = {"Efe Tur", "Cizre Ruh", "Anka", "Metro Turizm", "Kamil Koc",
																 "Ulusoy Turizm", "Has Turizm", "Pamukkale Turizm", "Nilufer Turizm", "Esadas Turizm"};
char ucakFirmalari[10][20] = {"Pegasus", "Anadolu Jet", "Turk Hava Yollari", "Onur Air", "Atlas Global", "Sunexpress", "Corendon Airlines", "Lufthansa",
										"AtlasGlobal", "BoraJet"};

FILE *fpYorum, *fpKullanici;
Kullanici kullanici[100], *kp = kullanici;
int kullanicisayisi = 0, i, yorumsor, kontrol = 0, seyahatiptal, sehirsecim, seyahattercihi, yorumsayisi = 0;
int gun, ay, otobusbileti, d1, d2, d3;
char seyahatSaat[10][8] = {"12.45", "21.30", "21.00", "20.00", "19.00", "19.30", "09.45", "10.00", "11.30", "18.30"};
int* p;

int main()
{

	int menusecim, gidilecekyer, i, a = 1, menudon = 1, kiralikarac, ucakbileti;
	int aracfiyat[4] = {175, 230, 275, 390}, dolulukOran[10] = {13, 25, 34, 12, 65, 47, 86, 54, 61, 79}, otobusFiyat[10] = {73, 77, 81, 95, 84, 91, 75, 79, 89, 94};
	int rastDeger[3], ucakFiyat[10] = {140, 127, 159, 132, 145, 179, 190, 170, 200, 165};
	srand(time(NULL));

	do
	{
		system("cls");
		if (kontrol == 0)
		{
			KullaniciOku();
			YorumOku();
		}

		anaMenuYazdir(); //fonksiyon ile ana menuyu yazdirdik
		scanf("%d", &menusecim);

		//yanlis veri kontrolu
		p = &menusecim;
		hataYakala(p, 4, 1);

		switch (menusecim)
		{ //menu islemleri icin switch case

		case 1:
			kontrol++;
			system("cls"); //ekrani temizledik
			printf("Seyahatimiz Dahilinde Olan Sehirler:\n");
			printf("-------------------------------------\n");
			printf("1-Istanbul\n2-Ankara\n3-Izmir\n4-Van\n5-Antalya\n");
			printf("\nHangi sehirdesiniz: ");
			scanf("%d", &sehirsecim); //hangi sehirde oldugunu aldik

			//yanlis veri kontrolu
			p = &sehirsecim;
			hataYakala(p, 5, 1);

			for (i = 0; i < 5; i++)
			{ //Ilk secilen sehir disindaki sehirleri bu sekilde yazdirdik
				if (i == sehirsecim - 1)
					continue;
				printf("\n%d-%s", a, sehirler[i]);
				a++;
			}

			printf("\nHangi sehire gideceksiniz: ");
			scanf("%d", &gidilecekyer); //gidilecek yeri aldik

			//yanlis veri kontrolu
			p = &gidilecekyer;
			hataYakala(p, 4, 1);

			if (gidilecekyer >= sehirsecim) //2. olarak hangi sehiri secti onu bulduk(2. secimde sehirler 1 eksildigi icin numaralari degisiyor o yuzden)
				gidileceksehir = sehirler[gidilecekyer];
			else
				gidileceksehir = sehirler[gidilecekyer - 1];

			if (gidilecekyer > 0 && gidilecekyer < 5)
			{
				system("cls");
				printf("Seyahatinizi Nasil Yapmak Istersiniz ?\n");
				printf("-------------------------------------\n");
				printf("1-Kiralik Araba\n2-Sehirler Arasi Otobus\n3-Ucak\n");
				printf("Seciminiz: ");
				scanf("%d", &seyahattercihi);

				p = &seyahattercihi;
				hataYakala(p, 3, 1);

				switch (seyahattercihi)
				{

				case 1:
					system("cls");
					printf("Su anda Kiralik Olan Arabalar\n\n");
					printf("------------------------------------------------------------------------------------\n");
					printf("1-Fiat Egea             | Benzinli, Manuel, Ekonomik         |  FIYAT: 175 TL/gun  |\n");
					printf("------------------------------------------------------------------------------------\n");
					printf("2-Opel Astra AT         | Benzinli, Otomatik, Orta Segment   |  FIYAT: 230 TL/gun  |\n");
					printf("------------------------------------------------------------------------------------\n");
					printf("3-Seat Arona            | Dizel, Otomatik, Orta Segment      |  FIYAT: 275 TL/gun  |\n");
					printf("------------------------------------------------------------------------------------\n");
					printf("4-Kia Sportage Elegance | Dizel, Otomatik, Ust Segment       |  FIYAT: 390 TL/gun  |\n");
					printf("------------------------------------------------------------------------------------\n");
					printf("\nArac Seciminiz: ");
					scanf("%d", &kiralikarac);
					p = &kiralikarac;
					hataYakala(p, 4, 1);

					printf("\nKac Gunluk Kiralayacaksiniz: ");
					scanf("%d", &gun);
					(sp + kullanicisayisi)->SeyahatUcreti = aracfiyat[kiralikarac - 1] * gun; //Ucreti structa attik
					break;

				case 2:
					SeyahatTarihSor(); //2 kere kullanildigi icin fonksiyona cevirdim ve oyle yazdirdik

					rastDeger[0] = rand() % 10; //random otobus firmasi sectik
					if (rastDeger[0] > 5)
					{
						rastDeger[1] = rastDeger[0] - 2; //digerlerini de ilk secilene gore sectik
						rastDeger[2] = rastDeger[0] - 4;
					}
					else
					{
						rastDeger[1] = rastDeger[0] + 2;
						rastDeger[2] = rastDeger[0] + 4;
					}
					d1 = rastDeger[0], d2 = rastDeger[1], d3 = rastDeger[2];
					system("cls");
					printf("%d/%d/2021 Tarihindeki Otobus Biletleri Asagida Listelenmistir Birini Seciniz:\n\n", gun, ay);
					printf("1-%s\n----------------------------\nSaat: %s \nKoltuk Duzeni: 2+2\nOtobus Doluluk Orani: %c%d\nFiyat: %dTL\n\n", otobusFirmalari[d1], seyahatSaat[d1], yuzde, dolulukOran[d1], otobusFiyat[d1]);
					printf("2-%s\n----------------------------\nSaat: %s \nKoltuk Duzeni: 2+1\nOtobus Doluluk Orani: %c%d\nFiyat: %dTL\n\n", otobusFirmalari[d2], seyahatSaat[d2], yuzde, dolulukOran[d2], otobusFiyat[d2]);
					printf("3-%s\n----------------------------\nSaat: %s\nKoltuk Duzeni: 2+1\nOtobus Doluluk Orani: %c%d \nFiyat: %dTL\n\n", otobusFirmalari[d3], seyahatSaat[d3], yuzde, dolulukOran[d3], otobusFiyat[d3]);
					printf("\nSeciminiz: ");
					scanf("%d", &otobusbileti);
					
					p = &otobusbileti;
					hataYakala(p, 3, 1);

					switch (otobusbileti)
					{
					case 1:
						(sp + kullanicisayisi)->SeyahatUcreti = otobusFiyat[d1];
						strcpy((sp + kullanicisayisi)->SeyahatSaati, seyahatSaat[d1]);
						break;
					case 2:
						(sp + kullanicisayisi)->SeyahatUcreti = otobusFiyat[d2];
						strcpy((sp + kullanicisayisi)->SeyahatSaati, seyahatSaat[d2]);
						break;
					case 3:
						(sp + kullanicisayisi)->SeyahatUcreti = otobusFiyat[d3];
						strcpy((sp + kullanicisayisi)->SeyahatSaati, seyahatSaat[d1]);
						break;
					}
					break;

				case 3:
					SeyahatTarihSor(); //2 kere kullanildigi icin fonksiyona cevirdim ve oyle yazdirdik

					rastDeger[0] = rand() % 10; //random otobus firmasi sectik
					if (rastDeger[0] > 5)
					{
						rastDeger[1] = rastDeger[0] - 2; //digerlerini de ilk secilene gore sectik
						rastDeger[2] = rastDeger[0] - 4;
					}
					else
					{
						rastDeger[1] = rastDeger[0] + 2;
						rastDeger[2] = rastDeger[0] + 4;
					}
					d1 = rastDeger[0], d2 = rastDeger[1], d3 = rastDeger[2];

					system("cls");
					printf("%d/%d/2021 Tarihindeki Ucak Biletleri Asagida Listelenmistir Birini Seciniz:\n\n", gun, ay);
					printf("1-%s \n------------------------------\nSaat: %s  \nYer: Sabiha Gokcen Havalimani\nUcak Doluluk Orani: %c%d\nFiyat: %dTL\n\n", ucakFirmalari[d1], seyahatSaat[d1], yuzde, dolulukOran[d1], ucakFiyat[d1]);
					printf("2-%s\n------------------------------\nSaat: %s \nYer: Istanbul Havalimani\nUcak Doluluk Orani: %c%d  \nFiyat: %dTL\n\n", ucakFirmalari[d2], seyahatSaat[d2], yuzde, dolulukOran[d2], ucakFiyat[d2]);
					printf("3-%s\n------------------------------\nSaat: %s\nYer: Istanbul Havalimani\nUcak Doluluk Orani: %c%d\nFiyat: %dTL\n\n", ucakFirmalari[d3], seyahatSaat[d3], yuzde, dolulukOran[d3], ucakFiyat[d3]);
					printf("\nSeciminiz: ");
					scanf("%d", &ucakbileti);

					p = &ucakbileti;
					hataYakala(p, 3, 1);

					switch (ucakbileti)
					{
					case 1:
						(sp + kullanicisayisi)->SeyahatUcreti = ucakFiyat[d1];
						strcpy((sp + kullanicisayisi)->SeyahatSaati, seyahatSaat[d1]);
						break;
					case 2:
						(sp + kullanicisayisi)->SeyahatUcreti = ucakFiyat[d2];
						strcpy((sp + kullanicisayisi)->SeyahatSaati, seyahatSaat[d2]);
						break;
					case 3:
						(sp + kullanicisayisi)->SeyahatUcreti = ucakFiyat[d3];
						strcpy((sp + kullanicisayisi)->SeyahatSaati, seyahatSaat[d3]);
						break;
					}
					break;
				}
				if (seyahattercihi == 1) //Seyahat tipini strcuta attik
					strcpy((sp + kullanicisayisi)->SeyahatTipi, "Kiralik Araba");
				else if (seyahattercihi == 2)
					strcpy((sp + kullanicisayisi)->SeyahatTipi, "Otobus");
				else
					strcpy((sp + kullanicisayisi)->SeyahatTipi, "Ucak");
			}

			int altmenudon;

			do
			{

				system("cls");
				printf("------Alt Menu------\n\n");
				a = 1;
				int altmenu;

				if (seyahattercihi == 1)
				{ //kiralik araba menusune girmezse buna gerek kalmayacagi icin sadece o kisimda yazidirilacak.
					printf("%d-Guzergah uzerindeki dinlenme tesislerini goster\n", a);
					a++;
				}
				printf("%d-%s ve %s sehirlerinin virus durumunu goster\n", a, sehirler[sehirsecim - 1], gidileceksehir);
				a++;
				printf("%d-Devam et(seyahat bilgilerini goster)\n", a);
				printf("\nSeciminiz: ");
				scanf("%d", &altmenu);

				p = &altmenu;
				hataYakala(p, 3, 1);

				if (a == 2)
				{ //buradaki algoritma da 1-tesisler 2-virus durum 3-devam etme menusunu istedigimiz gibi duzenleme icin yapildi.
					altmenu += 1;
				}

				if (!strcmp(gidileceksehir, "Istanbul") || sehirsecim == 1)
				{ //birinci karsilastirma strcmp olmadan olmuyor, basina da unlem koymak gerek cunku 0 donderiyor.

					if (!strcmp(gidileceksehir, "Ankara") || sehirsecim == 2)
					{ //sehirsecim de ilk menude secilen odlugundan boyle kontrol edilebiliyor

						if (seyahattercihi == 2)
							strcpy((sp + kullanicisayisi)->SeyahatSuresi, "4 saat 15 dakika"); //Sureyi strcuta attik(Otobus)
						else if (seyahattercihi == 3)
							strcpy((sp + kullanicisayisi)->SeyahatSuresi, "1 saat 5 dakika"); //Ayni sekilde(Ucak)

						(sp + kullanicisayisi)->SeyahatTehlikesi = (istanbul.tehlikeOran + ankara.tehlikeOran) / 2; //Seyahatin tehlike oranini hesapladik ve strcuta attik

						if (altmenu == 1)
						{
							system("cls");
							iaTesisYazdir(); //Tesis yazdirdik
							printf("\n\nAlt menuye donmek icin 1 e basiniz: ");
							scanf("%d", &altmenudon);

							p = &altmenudon;
							hataYakala(p, 1, 1);
						}
						else if (altmenu == 2)
						{
							system("cls");
							istanbulYazdir(); //Virus durumunu yazdirdik
							ankaraYazdir();

							printf("\nAlt menuye donmek icin 1 e basiniz: ");
							scanf("%d", &altmenudon); //Seyahat bilgilerini yazdirma ve virus ekranini temizlemek icin sordum

							p = &altmenudon;
							hataYakala(p, 1, 1);
						}
						else if (altmenu == 3)
							break; //Seyahat bilgilerini yazdirmak icin devam etmek gerek bunun icin de donguden ciktik
					}
					else if (!strcmp(gidileceksehir, "Izmir") || sehirsecim == 3)
					{

						if (seyahattercihi == 2)
							strcpy((sp + kullanicisayisi)->SeyahatSuresi, "7 saat 35 dakika");
						else if (seyahattercihi == 3)
							strcpy((sp + kullanicisayisi)->SeyahatSuresi, "1 saat");

						(sp + kullanicisayisi)->SeyahatTehlikesi = (istanbul.tehlikeOran + izmir.tehlikeOran) / 2;

						if (altmenu == 1)
						{
							//Dinlenme tesisleri yazilacak
							system("cls");
							iiTesisYazdir();
							printf("\n\nAlt menuye donmek icin 1 e basiniz: ");
							scanf("%d", &altmenudon);

							p = &altmenudon;
							hataYakala(p, 1, 1);
						}
						else if (altmenu == 2)
						{
							system("cls");
							istanbulYazdir();
							izmirYazdir();

							printf("\nAlt menuye donmek icin 1 e basiniz: ");
							scanf("%d", &altmenudon); //Seyahat bilgilerini yazdirma ve virus ekranini temizlemek icin sordum

							p = &altmenudon;
							hataYakala(p, 1, 1);
						}
						else if (altmenu == 3)
							break;
					}
					else if (!strcmp(gidileceksehir, "Van") || sehirsecim == 4)
					{

						if (seyahattercihi == 2)
							strcpy((sp + kullanicisayisi)->SeyahatSuresi, "21 saat 40 dakika");
						else if (seyahattercihi == 3)
							strcpy((sp + kullanicisayisi)->SeyahatSuresi, "1 saat 55 dakika");

						(sp + kullanicisayisi)->SeyahatTehlikesi = (istanbul.tehlikeOran + van.tehlikeOran) / 2;

						if (altmenu == 1)
						{
							//Dinlenme tesisleri yazilacak
							system("cls");
							ivTesisYazdir();
							printf("\n\nAlt menuye donmek icin 1 e basiniz: ");
							scanf("%d", &altmenudon);

							p = &altmenudon;
							hataYakala(p, 1, 1);
						}
						else if (altmenu == 2)
						{
							system("cls");
							istanbulYazdir();
							vanYazdir();

							printf("\nAlt menuye donmek icin 1 e basiniz: ");
							scanf("%d", &altmenudon); //Seyahat bilgilerini yazdirma ve virus ekranini temizlemek icin sordum

							p = &altmenudon;
							hataYakala(p, 1, 1);
						}
						else if (altmenu == 3)
							break;
					}
					else if (!strcmp(gidileceksehir, "Antalya") || sehirsecim == 5)
					{

						if (seyahattercihi == 2)
							strcpy((sp + kullanicisayisi)->SeyahatSuresi, "10 saat 45 dakika");
						else if (seyahattercihi == 3)
							strcpy((sp + kullanicisayisi)->SeyahatSuresi, "1 saat 5 dakika");

						(sp + kullanicisayisi)->SeyahatTehlikesi = (istanbul.tehlikeOran + antalya.tehlikeOran) / 2;

						if (altmenu == 1)
						{
							//Dinlenme tesisleri yazilacak
							system("cls");
							ianTesisYazdir();
							printf("\n\nAlt menuye donmek icin 1 e basiniz: ");
							scanf("%d", &altmenudon);

							p = &altmenudon;
							hataYakala(p, 1, 1);
						}
						else if (altmenu == 2)
						{
							system("cls");
							istanbulYazdir();
							antalyaYazdir();

							printf("\nAlt menuye donmek icin 1 e basiniz: ");
							scanf("%d", &altmenudon); //Seyahat bilgilerini yazdirma ve virus ekranini temizlemek icin sordum

							p = &altmenudon;
							hataYakala(p, 1, 1);
						}
						else if (altmenu == 3)
							break;
					}
				}
				else if (!strcmp(gidileceksehir, "Ankara") || sehirsecim == 2)
				{

					if (!strcmp(gidileceksehir, "Izmir") || sehirsecim == 3)
					{

						if (seyahattercihi == 2)
							strcpy((sp + kullanicisayisi)->SeyahatSuresi, "7 saat 5 dakika");
						else if (seyahattercihi == 3)
							strcpy((sp + kullanicisayisi)->SeyahatSuresi, "1 saat 10 dakika");

						(sp + kullanicisayisi)->SeyahatTehlikesi = (ankara.tehlikeOran + izmir.tehlikeOran) / 2;

						if (altmenu == 1)
						{
							//Dinlenme tesisleri yazilacak
							system("cls");
							aiTesisYazdir();
							printf("\n\nAlt menuye donmek icin 1 e basiniz: ");
							scanf("%d", &altmenudon);

							p = &altmenudon;
							hataYakala(p, 1, 1);
						}
						else if (altmenu == 2)
						{
							system("cls");
							ankaraYazdir();
							izmirYazdir();

							printf("\nAlt menuye donmek icin 1 e basiniz: ");
							scanf("%d", &altmenudon); //Seyahat bilgilerini yazdirma ve virus ekranini temizlemek icin sordum

							p = &altmenudon;
							hataYakala(p, 1, 1);
						}
						else if (altmenu == 3)
							break;
					}
					else if (!strcmp(gidileceksehir, "Van") || sehirsecim == 4)
					{

						if (seyahattercihi == 2)
							strcpy((sp + kullanicisayisi)->SeyahatSuresi, "17 saat 45 dakika");
						else if (seyahattercihi == 3)
							strcpy((sp + kullanicisayisi)->SeyahatSuresi, "1 saat 30 dakika");

						(sp + kullanicisayisi)->SeyahatTehlikesi = (ankara.tehlikeOran + van.tehlikeOran) / 2;

						if (altmenu == 1)
						{
							//Dinlenme tesisleri yazilacak
							system("cls");
							avTesisYazdir();
							printf("\n\nAlt menuye donmek icin 1 e basiniz: ");
							scanf("%d", &altmenudon);

							p = &altmenudon;
							hataYakala(p, 1, 1);
						}
						else if (altmenu == 2)
						{
							system("cls");
							ankaraYazdir();
							vanYazdir();

							printf("\nAlt menuye donmek icin 1 e basiniz: ");
							scanf("%d", &altmenudon); //Seyahat bilgilerini yazdirma ve virus ekranini temizlemek icin sordum

							p = &altmenudon;
							hataYakala(p, 1, 1);
						}
						else if (altmenu == 3)
							break;
					}
					else if (!strcmp(gidileceksehir, "Antalya") || sehirsecim == 5)
					{

						if (seyahattercihi == 2)
							strcpy((sp + kullanicisayisi)->SeyahatSuresi, "4 saat 15 dakika");
						else if (seyahattercihi == 3)
							strcpy((sp + kullanicisayisi)->SeyahatSuresi, "1 saat");

						(sp + kullanicisayisi)->SeyahatTehlikesi = (ankara.tehlikeOran + antalya.tehlikeOran) / 2;

						if (altmenu == 1)
						{
							//Dinlenme tesisleri yazilacak
							system("cls");
							aaTesisYazdir();
							printf("\n\nAlt menuye donmek icin 1 e basiniz: ");
							scanf("%d", &altmenudon);

							p = &altmenudon;
							hataYakala(p, 1, 1);
						}
						else if (altmenu == 2)
						{
							system("cls");
							ankaraYazdir();
							antalyaYazdir();

							printf("\nAlt menuye donmek icin 1 e basiniz: ");
							scanf("%d", &altmenudon); //Seyahat bilgilerini yazdirma ve virus ekranini temizlemek icin sordum

							p = &altmenudon;
							hataYakala(p, 1, 1);
						}
						else if (altmenu == 3)
							break;
					}
				}
				else if (!strcmp(gidileceksehir, "İzmir") || sehirsecim == 3)
				{

					if (!strcmp(gidileceksehir, "Van") || sehirsecim == 4)
					{

						if (seyahattercihi == 2)
							strcpy((sp + kullanicisayisi)->SeyahatSuresi, "22 saat 15 dakika");
						else if (seyahattercihi == 3)
							strcpy((sp + kullanicisayisi)->SeyahatSuresi, "4 saat 5 dakika");

						(sp + kullanicisayisi)->SeyahatTehlikesi = (van.tehlikeOran + izmir.tehlikeOran) / 2;

						if (altmenu == 1)
						{
							//Dinlenme tesisleri yazilacak
							system("cls");
							izvTesisYazdir();
							printf("\n\nAlt menuye donmek icin 1 e basiniz: ");
							scanf("%d", &altmenudon);

							p = &altmenudon;
							hataYakala(p, 1, 1);
						}
						else if (altmenu == 2)
						{
							system("cls");
							izmirYazdir();
							vanYazdir();

							printf("\nAlt menuye donmek icin 1 e basiniz: ");
							scanf("%d", &altmenudon); //Seyahat bilgilerini yazdirma ve virus ekranini temizlemek icin sordum

							p = &altmenudon;
							hataYakala(p, 1, 1);
						}
						else if (altmenu == 3)
							break;
					}
					else if (!strcmp(gidileceksehir, "Antalya") || sehirsecim == 5)
					{

						if (seyahattercihi == 2)
							strcpy((sp + kullanicisayisi)->SeyahatSuresi, "4 saat 15 dakika");
						else if (seyahattercihi == 3)
							strcpy((sp + kullanicisayisi)->SeyahatSuresi, "55 dakika");

						(sp + kullanicisayisi)->SeyahatTehlikesi = (antalya.tehlikeOran + izmir.tehlikeOran) / 2;

						if (altmenu == 1)
						{
							//Dinlenme tesisleri yazilacak
							system("cls");
							izaTesisYazdir();
							printf("\n\nAlt menuye donmek icin 1 e basiniz: ");
							scanf("%d", &altmenudon);

							p = &altmenudon;
							hataYakala(p, 1, 1);
						}
						else if (altmenu == 2)
						{
							system("cls");
							izmirYazdir();
							antalyaYazdir();

							printf("\nAlt menuye donmek icin 1 e basiniz: ");
							scanf("%d", &altmenudon); //Seyahat bilgilerini yazdirma ve virus ekranini temizlemek icin sordum

							p = &altmenudon;
							hataYakala(p, 1, 1);
						}
						else if (altmenu == 3)
							break;
					}
				}
				else if (!strcmp(gidileceksehir, "Van") || sehirsecim == 4)
				{
					if (!strcmp(gidileceksehir, "Antalya") || sehirsecim == 5)
					{

						if (seyahattercihi == 2)
							strcpy((sp + kullanicisayisi)->SeyahatSuresi, "18 saat 45 dakika");
						else if (seyahattercihi == 3)
							strcpy((sp + kullanicisayisi)->SeyahatSuresi, "2 saat 35 dakika");

						(sp + kullanicisayisi)->SeyahatTehlikesi = (van.tehlikeOran + antalya.tehlikeOran) / 2;

						if (altmenu == 1)
						{
							//Dinlenme tesisleri yazilacak
							system("cls");
							anvTesisYazdir();
							printf("\n\nAlt menuye donmek icin 1 e basiniz: ");
							scanf("%d", &altmenudon);

							p = &altmenudon;
							hataYakala(p, 1, 1);
						}
						else if (altmenu == 2)
						{
							system("cls");
							vanYazdir();
							antalyaYazdir();

							printf("\nAlt menuye donmek icin 1 e basiniz: ");
							scanf("%d", &altmenudon); //Seyahat bilgilerini yazdirma ve virus ekranini temizlemek icin sordum

							p = &altmenudon;
							hataYakala(p, 1, 1);
						}
						else if (altmenu == 3)
							break;
					}
				}

			} while (altmenudon != 0);

			SeyahatBilgisiYazdir(); //Donguden cikip bilgiyi yazdirdik

			printf("\n\nSistemimiz hakkinda yorum yapmak icin 1, programdan cikmak icin 0 tuslayiniz: ");
			scanf("%d", &yorumsor);

			p = &yorumsor;
			hataYakala(p, 1, 0);

			menudon = 0; //donguden ciktik

			break;

		case 2:
			kontrol++;
			system("cls");		//ekrani temizledik
			istanbulYazdir(); //tum sehirlerin virus durumu yazildi

			ankaraYazdir();

			izmirYazdir();

			vanYazdir();

			antalyaYazdir();

			printf("Ana menuye gitmek icin 1 i, programi kapatmak icin 0 i tuslayiniz: ");
			scanf("%d", &menudon); //menuye geri donme while ile yapildi

			p = &menudon;
			hataYakala(p, 1, 0);

			break;

		case 3:
			kontrol++;
			YorumListele(); //yorumlari gosterdik
			printf("Ana menuye gitmek icin 1 i, programi kapatmak icin 0 i tuslayiniz: ");
			scanf("%d", &menudon); //menuye geri donmek icin yazildi

			p = &menudon;
			hataYakala(p, 1, 0);

			break;

		case 4:
			KullaniciListele(); //kullanicilar listelendi
			printf("Ana menuye gitmek icin 1 i, programi kapatmak icin 0 i tuslayiniz: ");
			scanf("%d", &menudon); //menuye geri donmek icin yazildi

			p = &menudon;
			hataYakala(p, 1, 0);

			break;
		}

	} while (menudon != 0);

	if (yorumsor == 1)
	{

		YorumEkle(); //fonksiyon ile sisteme yorum ekledik
		printf("\nYorum icin tesekkur eder, iyi gunler dileriz...");
	}

	int kayitsor;
	printf("\n\nSeyahat bilgileriniz sisteme kaydedilsin mi?(Evet:1/Hayir:0) ");
	scanf("%d", &kayitsor);

	p = &kayitsor;
	hataYakala(p, 1, 0);

	if (kayitsor == 1)
	{
		//Kullanicin seyahat bilgilerini kaydet
		KullaniciEkle();
		printf("\nSeyahat bilgileriniz basari ile kaydedilmistir, iyi gunler dileriz...");
	}
	else
	{
		printf("\nIyi gunler dileriz...");
	}

	getch();
	return 0;
}

void anaMenuYazdir()
{
	printf("\n-----Ana Menu-----\n\n");
	printf("1-Seyahat Sec\n");
	printf("2-Sehirlerdeki Virus Durumunu Goster\n");
	printf("3-Kullanici Yorumlarini Goster\n");
	printf("4-Kayitli Kullanicilarin Seyahat Bilgilerini Goster\n\n");
	printf("Seciminiz: ");
}

void istanbulYazdir()
{
	printf("ISTANBUL\n-----------\n"); //buras� ve a�a��s� �ehirlerin durumlar�n� yazd�rma
	printf("Risk Grubu: %s\n", istanbul.riskGrup);
	printf("Asilanan Orani: %c%d\n", yuzde, istanbul.asiOran);
	printf("Virus Sayisi: %s\n", istanbul.virusSayi);
	printf("Tehlike Orani: %c%d\n", yuzde, istanbul.tehlikeOran);
	printf("Sehir Durumu: %s\n\n", istanbul.sehirDurum);
}

void ankaraYazdir()
{
	printf("ANKARA\n------------\n");
	printf("Risk Grubu: %s\n", ankara.riskGrup);
	printf("Asilanan Orani: %c%d\n", yuzde, ankara.asiOran);
	printf("Virus Sayisi: %s\n", ankara.virusSayi);
	printf("Tehlike Orani: %c%d\n", yuzde, ankara.tehlikeOran);
	printf("Sehir Durumu: %s\n\n", ankara.sehirDurum);
}

void izmirYazdir()
{
	printf("IZMIR\n------------\n");
	printf("Risk Grubu: %s\n", izmir.riskGrup);
	printf("Asilanan Orani: %c%d\n", yuzde, izmir.asiOran);
	printf("Virus Sayisi: %s\n", izmir.virusSayi);
	printf("Tehlike Orani: %c%d\n", yuzde, izmir.tehlikeOran);
	printf("Sehir Durumu: %s\n\n", izmir.sehirDurum);
}

void vanYazdir()
{
	printf("VAN\n------------\n");
	printf("Risk Grubu: %s\n", van.riskGrup);
	printf("Asilanan Orani: %c%d\n", yuzde, van.asiOran);
	printf("Virus Sayisi: %s\n", van.virusSayi);
	printf("Tehlike Orani: %c%d\n", yuzde, van.tehlikeOran);
	printf("Sehir Durumu: %s\n\n", van.sehirDurum);
}

void antalyaYazdir()
{
	printf("ANTALYA\n--------------\n");
	printf("Risk Grubu: %s\n", antalya.riskGrup);
	printf("Asilanan Orani: %c%d\n", yuzde, antalya.asiOran);
	printf("Virus Sayisi: %s\n", antalya.virusSayi);
	printf("Tehlike Orani: %c%d\n", yuzde, antalya.tehlikeOran);
	printf("Sehir Durumu: %s\n\n", antalya.sehirDurum);
}

void YorumEkle()
{
	system("cls");
	printf("-------YORUM YAP-------\n\n");
	gets((kp + yorumsayisi)->isim); //pointer ile structa degerleri atadik
	printf("Adinizi giriniz: ");
	gets((kp + yorumsayisi)->isim);
	printf("\nYorum bolumu bos birakilirsa yorumlar kisminda gozukmeyecektir!!!(En az 3 harf)\nYorumunuzu giriniz: ");
	gets((kp + yorumsayisi)->yorum);
	printf("\nPuaninizi giriniz(10 uzerinden,eger string girilirse puan alinmayacaktir): ");
	scanf("%f", &(kp + yorumsayisi)->puan);

	if ((kp + yorumsayisi)->puan > 10 || (kp + yorumsayisi)->puan < 0)
	{ //puan kontrol
		printf("\nYanlis puan girildi tekrar giriniz(bir kez daha yanlis girilirse program kapanacaktir): ");
		scanf("%f", &(kp + yorumsayisi)->puan);

		if ((kp + yorumsayisi)->puan > 10 || (kp + yorumsayisi)->puan < 0)
		{
			printf("\n\nProgram Kapatiliyor...");
			exit(EXIT_SUCCESS);
		}
	}

	fpYorum = fopen("yorumlar.txt", "a");							  //dosyayi actik
	fwrite((kp + yorumsayisi), sizeof(Kullanici), 1, fpYorum); //dosyaya yazdik yani kayit yaptik
	fclose(fpYorum);														  //dosyayi kapattik
	yorumsayisi++;															  //kullanici sayisi artti
}

void KullaniciEkle()
{
	gets((sp + kullanicisayisi)->ad);
	printf("Sistemde kayitli olacak adinizi giriniz: ");
	gets((sp + kullanicisayisi)->ad);

	fpKullanici = fopen("kullanicilar.txt", "a");
	fwrite((sp + kullanicisayisi), sizeof(SeyahatBilgi), 1, fpKullanici);
	fclose(fpKullanici);
	kullanicisayisi++;
}

void YorumListele()
{
	system("cls");
	if (yorumsayisi == 0)
	{
		printf("Suanda kullanici bulunmamaktadir...\n\n");
	}
	else
	{
		printf("------YORUMLAR------\n\n\n");

		int yorumboyut, eksikKullanici = 0;
		float puanort, toplam = 0;

		for (i = 0; i < yorumsayisi; i++)
		{
			if ((kp + i)->puan == 0) //puan string girildiyse eksik kullanici olarak alindi(string girince puan 0 oluyor o yuzden boyle kontrol ettim)
				eksikKullanici++;

			toplam += ((kp + i)->puan); //puan toplami

			yorumboyut = strlen((kp + i)->yorum); //yorum boyutunu aldik cunku en az 3 karakter olmali yorumda sistemde gozukmesi icin

			if (yorumboyut > 3)
			{
				if (strlen((kp + i)->isim) < 3)
					strcpy((kp + i)->isim, "Ismi bilinmeyen kullanici"); //isim 3 harften daha az ise bilinmeyen kullanici olarak ayarlandi

				printf("AD: %s\n", (kp + i)->isim);
				if ((kp + i)->puan == 0) //puan string ise soru isareti yazidirildi
					printf("PUAN: ????\n\n");
				else
					printf("PUAN: %.1f\n\n", (kp + i)->puan);
				printf("YORUM: %s\n\n", (kp + i)->yorum);
				printf("-----------------------\n\n");
			}
		}
		puanort = (float)toplam / (yorumsayisi - eksikKullanici);
		printf("\nGenel Kullanici Puan Ortalamasi: %.1f\n\n", puanort); //genel puan ortalamasi yazdirildi
	}
}

void KullaniciListele()
{
	system("cls");
	if (kullanicisayisi == 0)
	{
		printf("Sistemde kayitli kullanici bulunmamaktadir...");
	}
	else
	{
		printf("---KULLANICILAR---\n\n");

		for (i = 0; i < kullanicisayisi; i++)
		{
			printf("AD: %s\n", (sp + i)->ad);
			printf("Seyahat Saati: %s\n", (sp + i)->SeyahatSaati);
			printf("Seyahat Suresi: %s\n", (sp + i)->SeyahatSuresi);
			printf("Seyahat Tipi: %s\n", (sp + i)->SeyahatTipi);
			printf("Seyahat Ucreti: %dTL\n", (sp + i)->SeyahatUcreti);
			printf("Seyahat Tehlikesi: %c%d\n", yuzde, (sp + i)->SeyahatTehlikesi);
			printf("-----------------------------------------\n\n");
		}
	}
}

void YorumOku()
{
	fpYorum = fopen("yorumlar.txt", "r"); //dosyayi actik
	if (fpYorum != NULL)
	{ //dosya var mi yok mu kontrol ettik

		while (fread((kp + yorumsayisi), sizeof(Kullanici), 1, fpYorum))
		{ //kullanici sayisini bulmak icin dosyanin sonuna kadar gittik okuyarak(okuyacak birse kalmayana kadar)
			yorumsayisi++;
		}
		printf("Sistemde Yorumu Bulunan Kullanici Sayisi: %d\n", yorumsayisi);
	}
	fclose(fpYorum); //dosya kapandi

	if (yorumsayisi == 0)
		printf("Sistemde Kaydi Bulunan Yorum Sayisi: 0\n");
}

void KullaniciOku()
{
	fpKullanici = fopen("kullanicilar.txt", "r"); //Dosya acildi
	if (fpKullanici != NULL)
	{

		while (fread((sp + kullanicisayisi), sizeof(SeyahatBilgi), 1, fpKullanici))
		{
			kullanicisayisi++;
		}
		printf("Sistemde Kaydi Bulunan Kullanici Sayisi: %d\n", kullanicisayisi);
	}
	fclose(fpKullanici);

	if (kullanicisayisi == 0)
		printf("Sistemde Kaydi Bulunan Kullanici Sayisi: 0\n");
}

void SeyahatBilgisiYazdir()
{
	system("cls");
	printf("-----Seyahat Bilgileri-----\n\n");
	printf("Seyahat Rotasi: %s ---> %s \n", sehirler[sehirsecim - 1], gidileceksehir);
	if (otobusbileti == 1)
		printf("Seyahat Saati: %s\n", seyahatSaat[d1]);
	else if (otobusbileti == 2)
		printf("Seyahat Saati: %s\n", seyahatSaat[d2]);
	else if (otobusbileti == 3)
		printf("Seyahat Saati: %s\n", seyahatSaat[d3]);
	else
		printf("Seyahat Saati: Kullaniciya baglidir\n");
	printf("Seyahat Tipi: %s\n", (sp + kullanicisayisi)->SeyahatTipi);
	if (seyahattercihi == 1)
		printf("Seyahat Suresi: Kullaniciya baglidir\n");
	else
		printf("Seyahat Suresi: Tahmini %s\n", (sp + kullanicisayisi)->SeyahatSuresi);
	printf("Seyahat Ucreti: %dTL\n", (sp + kullanicisayisi)->SeyahatUcreti);
	printf("Seyahat Tehlikesi: %c%d\n", yuzde, (sp + kullanicisayisi)->SeyahatTehlikesi);

	if ((sp + kullanicisayisi)->SeyahatTehlikesi > 60)
	{
		printf("\nUYARI: Seyahatiniz riskli gozukuyor, zorunlu degilse lutfen iptal ediniz...(iptal etmek icin 0, devam etmek icin 1 tuslayiniz): ");
		scanf("%d", &seyahatiptal);

		//Yanlis veri kontrolu
		p = &seyahatiptal;
		hataYakala(p, 1, 0);

		if (seyahatiptal == 0)
		{
			printf("Iyı gunler dileriz...");
			getch();
			exit(EXIT_SUCCESS);
		}
	}
}

void SeyahatTarihSor()
{
	system("cls");
	printf("Seyahat Edeceginiz Tarihi  Giriniz:\n\n");
	printf("Gun : ");
	scanf("%d", &gun);

	p = &gun;
	hataYakala(p, 30, 0);

	printf("\nAy : ");
	scanf("%d", &ay);

	p = &ay;
	hataYakala(p, 12, 0);
}

void hataYakala(int* x, int max, int min){
	if(*x < min || *x > max){
		printf("Hatali Giris Yaptiniz,tekrar giriniz(bir daha yanlis girilirse program kapanacaktir):\n");
		scanf("%d", x);

		if (*x < min || *x > max){
			printf("\nProgram kapatiliyor...");
			getch();
			exit(EXIT_SUCCESS);
		}
	}
}
