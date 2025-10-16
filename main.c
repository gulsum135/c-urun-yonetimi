
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Dugum{
  int birim_fiyat,adet,satis_fiyat,sayac; 
	float kar;
	char Ad[20],kategori[20];
	struct Dugum* sonraki;
}Dugum;
Dugum* Dosyayi_Oku(){

FILE *file;
file= fopen("urun.txt","r");
char Ad[20];
int birim_fiyat,adet,satis_fiyat;
char kategori[20];
Dugum* bas=NULL;            
Dugum* son=NULL;

if(file==NULL){
	printf("Dosya okunamadi");
	return NULL;
}

while(fscanf(file, " %99[^,], %d, %d, %d, %49[^\n]", Ad, &birim_fiyat, &adet, &satis_fiyat, kategori) == 5){
      Dugum* yeni_dugum=(Dugum*)malloc(sizeof(Dugum));
       if (yeni_dugum == NULL) {
            printf("Bellek ayrilamadi!\n");
            fclose(file);
            return bas;
            
        }

strcpy(yeni_dugum->Ad, Ad);
yeni_dugum-> birim_fiyat=birim_fiyat;
yeni_dugum-> satis_fiyat=satis_fiyat;
yeni_dugum-> adet=adet;
strcpy(yeni_dugum->kategori, kategori);  
yeni_dugum->sonraki = NULL;
	  
	if(bas==NULL){ 
        bas= yeni_dugum;
        son= yeni_dugum;}
	else{
    son->sonraki= yeni_dugum; 
    son= yeni_dugum;
	}
}   fclose(file);
	return bas;  
}

void ListeyiYazdir(Dugum* bas){
	int toplam_kar=0;
    while (bas != NULL) {
        float kar = (float)100*(bas->satis_fiyat - bas->birim_fiyat) / bas->birim_fiyat;
        printf("%s  %d  %d  %d  %s   %.2f",bas->Ad, bas->birim_fiyat, bas->adet, bas->satis_fiyat, bas->kategori, kar);
        printf("\n");
        
        toplam_kar+=(bas->satis_fiyat - bas->birim_fiyat)*bas->adet;
        bas = bas->sonraki;
    }
    printf("\nToplam kar: %d\n",toplam_kar);
}

void Kategoriye_Gore_Sil(Dugum** bas,char* silinecek_kategori){
    Dugum* gecici = *bas;
    Dugum* onceki = NULL; 

    while(gecici !=NULL){
        if(strcmp(gecici->kategori, silinecek_kategori) == 0){
            Dugum* silinecek= gecici;

        if(onceki== NULL){
            *bas= gecici->sonraki; 
            gecici = *bas;
        }else{
        onceki->sonraki= gecici->sonraki;
        gecici= gecici->sonraki;
        }

        free(silinecek);
        } else{ 
            onceki= gecici;
            gecici= gecici->sonraki;
        }
    }
}
void EnYuksekKarliUrunuSil(Dugum** bas) {
    Dugum* gecici = *bas;
    Dugum* onceki = NULL;
    
    Dugum* enYuksekDugum = NULL;
    Dugum* enYuksekOnceki = NULL;
    float EnBuyukKarOrani = -1;

    while(gecici != NULL){
        float karOrani =(float)(gecici->satis_fiyat- gecici->birim_fiyat)/ gecici->birim_fiyat;

        if(karOrani>EnBuyukKarOrani){
        EnBuyukKarOrani= karOrani;
        enYuksekDugum = gecici;
        enYuksekOnceki = onceki;}
       
	    onceki = gecici; 
        gecici = gecici->sonraki;
    }

    if(enYuksekDugum !=NULL){
        printf("En yuksek kar oranli urun siliniyor: %s Kar Orani: %.2f\n", enYuksekDugum->Ad, EnBuyukKarOrani);

        if(enYuksekOnceki==NULL){// Başta ise
            *bas=enYuksekDugum->sonraki;} 
		else{
            enYuksekOnceki->sonraki=enYuksekDugum->sonraki;
        }

        free(enYuksekDugum);
    } else {
        printf("Silinecek urun bulunamadi\n");
    }
}
void SirayaUrunEkle(Dugum** bas, int sira){ 
    Dugum* yeni = (Dugum*)malloc(sizeof(Dugum));
    if (yeni == NULL) {
        printf("Bellek ayrilamadi!\n");
        return;
    }
    printf("Yeni urun adini girin: ");
    fgets(yeni->Ad, sizeof(yeni->Ad), stdin);
    yeni->Ad[strcspn(yeni->Ad,"\n")] = '\0'; 

    printf("Birim fiyati: ");
    scanf("%d",&yeni->birim_fiyat);

    printf("Adet: ");
    scanf("%d",&yeni->adet);

    printf("Satis fiyati: ");
    scanf("%d",&yeni->satis_fiyat);
    getchar(); 

    printf("Kategori: ");
    fgets(yeni->kategori, sizeof(yeni->kategori), stdin);
    yeni->kategori[strcspn(yeni->kategori, "\n")] = '\0';

    yeni->sonraki = NULL;
    
	if(sira<=1 || *bas==NULL){
        yeni->sonraki= *bas;
        *bas=yeni;
        return;
    }
    Dugum* onceki= *bas;
    int i=1;
    while(onceki->sonraki != NULL && i<sira-1){
        onceki = onceki->sonraki;
        i++;
    }

    yeni->sonraki=onceki->sonraki;
    onceki->sonraki=yeni;
}
void SatisFiyatiGuncelle(Dugum* bas, int sira){
    int i=1;
    while(bas != NULL && i < sira){
        bas=bas->sonraki;
        i++;
    }

    if(bas==NULL){
        printf("Belirtilen sira numarasi hatali!\n");
        return;
    }
    printf("Mevcut satis fiyati: %d\n",bas->satis_fiyat);

    int yeniFiyat;
    printf("Yeni satis fiyati girin: ");
    scanf("%d",&yeniFiyat);

    bas->satis_fiyat = yeniFiyat;
    printf("Satis fiyati guncellendi.\n");
}
int main(){
char Ad[20];
int birim_fiyat,adet,satis_fiyat;
char kategori[20],silinecek_kategori[50];
 int secim;
    Dugum* urunListesi= Dosyayi_Oku();

    if(urunListesi==NULL){
        printf("Urun listesi yüklenemedi!\n");
        return 1;
    }

    do{
        printf("\nMenu:\n");
        printf("1. Listeyi Goster\n");
        printf("2. Kategoriye Gore Sil\n");
        printf("3. En Yuksek Kar Oranli urunu Sil\n");
        printf("4. istenilen siraya yeni urun ekle\n");
        printf("5. Satis Fiyati Guncelle\n");
        printf("6. Cikis\n");
        printf("Seciminizi girin: ");
        scanf("%d",&secim);
        getchar(); 

        switch(secim){
            case 1:
                ListeyiYazdir(urunListesi);
                break;
            case 2:{
                char kategori[50];
                printf("Silinecek kategori: ");
                fgets(kategori, sizeof(kategori), stdin);
                kategori[strcspn(kategori, "\n")] = 0;
                Kategoriye_Gore_Sil(&urunListesi, kategori);
                break;
            }
            case 3:
                EnYuksekKarliUrunuSil(&urunListesi);
                break;
            case 4: {
                int sira;
                printf("Eklemek istedigin sira numarasini gir: ");
                scanf("%d",&sira);
                getchar(); // \n temizle
                SirayaUrunEkle(&urunListesi, sira);
                break;
            }
            case 5:{
                int sira;
                printf("Guncellemek istedigin urunun sirasi: ");
                scanf("%d",&sira);
                SatisFiyatiGuncelle(urunListesi,sira);
                break;
            }
            case 6:
                printf("Cikis yapiliyor...\n");
                break;
            default:
                printf("Gecersiz secim. Tekrar deneyin.\n");
        }
		} while (secim != 6);

   Dugum* tmp;
    while (urunListesi != NULL) {
    tmp = urunListesi;      
    urunListesi = urunListesi->sonraki; 
    free(tmp); 
}

	return 0;
}



