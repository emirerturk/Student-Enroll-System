#include <stdio.h>
#include <stdlib.h>
FILE *veri,*indeks,*gecici,*gecici2;
struct Ogrenci
{
    int ogrNo;
    int *ogrNoAdres;
    int dersKodu;
    int puan;
};
struct indeks
{
    int orgNo;
    int *ogrNoAdres;

};
void indeksDosyasiniSil()
{
    int sonuc = remove("indeks.txt");

    if(sonuc == 0)
    {
        fprintf(stdout, "Dosya silindi.\n");
    }
    else
    {
        fprintf(stderr, "Dosya silinemedi.\n");
        return -1;
    }
}
void indeksDosyasiniGoster()
{
    int a,b;

    indeks = fopen("indeks.txt", "r");
    if(indeks==NULL)
    {
        printf("Dosya gosterilemedi \n");
    }
    else
    {


        while((!feof(indeks)))
        {

            fscanf(indeks,"%d %d\n",&a,&b);
            printf("%d %d\n",a,b);
        }

        fclose(indeks);
    }
}
void indeksDosyasiOlustur()
{
    int sayac=0;
    struct Ogrenci ogr;
    veri=fopen("veri.bin","rb");
    {
        if(veri!=NULL)
        {
            fread(&ogr,sizeof(struct Ogrenci),1,veri);
            while((!feof(veri)))
            {
                sayac++;
                fread(&ogr,sizeof(struct Ogrenci),1,veri);
            }
        }

        fclose(veri);
    }
    int *dizi1,*dizi2;
    dizi1 = (int*) malloc(sayac * sizeof(int));

    dizi2 = (int*) malloc(sayac * sizeof(int));


    int i=0;

    indeks=fopen("indeks.txt","a+");
    printf("Indeks dosyasi olusturuldu .\n");
    fclose(indeks);
    indeks=fopen("indeks.txt","w");
    veri=fopen("veri.bin","rb");
    fread(&ogr,sizeof(struct Ogrenci),1,veri);
    while((!feof(veri)))
    {
        dizi1[i]=ogr.ogrNo;
        dizi2[i]=ogr.ogrNoAdres;
        fread(&ogr,sizeof(struct Ogrenci),1,veri);
        i++;
    }
    int tut,m;
    for(m=0; m<i; m++)
    {
        for (int k=0; k<i; k++)
        {
            if (dizi1[k]>dizi1[k+1])
            {
                tut=dizi1[k];
                dizi1[k]=dizi1[k+1];
                dizi1[k+1]=tut;
                tut=dizi2[k];
                dizi2[k]=dizi2[k+1];
                dizi2[k+1]=tut;

            }
        }
    }

    for (int k=0; k<i; k++)
    {
        fprintf(indeks,"%d %d\n",dizi1[k],dizi2[k]);

    }
    fclose(veri);
    fclose(indeks);
}
void kayitEkle()
{
    struct Ogrenci *ogr=(struct Ogrenci*)malloc(sizeof(struct Ogrenci));
    struct indeks *ind=(struct indeks*)malloc(sizeof(struct indeks));

    veri=fopen("veri.bin","a+b");
    indeks=fopen("indeks.txt","a+");

    if(veri!=NULL)
    {
        printf("Ogrenci no giriniz:");
        scanf("%d",&ogr->ogrNo);
        ogr->ogrNoAdres=&ogr->ogrNo;
        printf("Ders kodu giriniz:");
        scanf("%d",&ogr->dersKodu);
        printf("Puan giriniz :");
        scanf("%d",&ogr->puan);
        ind->ogrNoAdres=&ogr->ogrNo;
        ind->orgNo=ogr->ogrNo;
        fprintf(indeks,"%d %d\n",ind->orgNo,ind->ogrNoAdres);
        fwrite(ogr,sizeof(struct Ogrenci),1,veri);

    }

    fclose(veri);
    fclose(indeks);


}
void veriDosyasiniGoster()
{
    struct Ogrenci ogr;

    veri=fopen("veri.bin","rb");

    if(veri!=NULL)
    {

        printf("%s\t%s\t%s","Ogrenci No","Ders Kodu","Puan");
        printf("\n\n");
        fread(&ogr,sizeof(struct Ogrenci),1,veri);
        while((!feof(veri)))
        {


            printf("%d\t%d\t%d\n",ogr.ogrNo,ogr.dersKodu,ogr.puan);
            fread(&ogr,sizeof(struct Ogrenci),1,veri);

        }


        fclose(veri);


    }
}
void kayitBul()
{
    int sayac=0;
    struct Ogrenci ogr;
    veri=fopen("veri.bin","rb");
    {
        if(veri!=NULL)
        {
            fread(&ogr,sizeof(struct Ogrenci),1,veri);
            while((!feof(veri)))
            {
                sayac++;
                fread(&ogr,sizeof(struct Ogrenci),1,veri);
            }
        }

        fclose(veri);
    }
    int *dizi1,*dizi2;
    dizi1 = (int*) malloc(sayac * sizeof(int));

    dizi2 = (int*) malloc(sayac * sizeof(int));


    int i=0;
    int a1,a2;


    indeks=fopen("indeks.txt","r");

    while((!feof(indeks)))
    {
        fscanf(indeks,"%d %d",&a1,&a2);
        dizi1[i]=a1;
        dizi2[i]=a2;

        i++;
    }
    int gir,a,b,adres;
    int eb=sayac;
    int ek=0;

    int bak;
    printf("Aranicak ogrenci no giriniz:");
    scanf("%d",&gir);

    indeks = fopen("indeks.txt", "r");
    if(indeks==NULL)
    {
        printf("Dosya gosterilemedi \n");
    }
    else
    {

        while((!feof(indeks)))
        {
            fscanf(indeks,"%d %d",&a,&b);
            if(gir==a)
            {

                adres=b;
                break;
            }


        }



        while(eb-ek>1)
        {
            bak=(eb+ek)/2;
            if(dizi1[bak]==gir && adres==dizi2[bak])
            {



                break;
            }
            else if(dizi1[bak]<gir)
            {
                ek=bak;
            }
            else
            {
                eb=bak;
            }

        }

        fclose(indeks);
    }





    veri=fopen("veri.bin","rb");

    if(veri!=NULL)
    {


        fread(&ogr,sizeof(struct Ogrenci),1,veri);
        while((!feof(veri)))
        {
            if(gir==ogr.ogrNo && adres==ogr.ogrNoAdres )
            {
                printf("%d\t%d\t%d\n",ogr.ogrNo,ogr.dersKodu,ogr.puan);
                break;
            }
          else  if(gir==ogr.ogrNo && adres!=ogr.ogrNoAdres )
            {
                printf("%d\t%d\t%d\n",ogr.ogrNo,ogr.dersKodu,ogr.puan);
            }



            fread(&ogr,sizeof(struct Ogrenci),1,veri);

        }


        fclose(veri);


    }
}
void kayitSil()
{
    int gir,a,b,adres;
    printf("Hangi nolu ogrenci silinsin :");
    scanf("%d",&gir);

    indeks = fopen("indeks.txt", "r");
    if(indeks==NULL)
    {
        printf("Dosya gosterilemedi \n");
    }
    else
    {


        while((!feof(indeks)))
        {
            fscanf(indeks,"%d %d",&a,&b);
            if(gir==a)
            {
                gir=a;
                adres=b;
                break;
            }


        }

        fclose(indeks);
    }


    struct Ogrenci ogr;

    veri=fopen("veri.bin","rb");
    gecici=fopen("gecici.txt","w");
    if(veri!=NULL)
    {


        fread(&ogr,sizeof(struct Ogrenci),1,veri);
        while((!feof(veri)))
        {
            if(gir!=ogr.ogrNo)
            {
                fprintf(gecici,"%d %d %d \n",ogr.ogrNo,ogr.dersKodu,ogr.puan);
            }

            fread(&ogr,sizeof(struct Ogrenci),1,veri);





        }
    }
    fclose(veri);
    fclose(gecici);
    veri=fopen("veri.bin","wb");
    gecici=fopen("gecici.txt","r");
    struct indeks *ind=(struct indeks*)malloc(sizeof(struct indeks));
    struct Ogrenci *gec=(struct Ogrenci*)malloc(sizeof(struct Ogrenci));
    int j,k,l;


    if(veri!=NULL)
    {



        fscanf(gecici,"%d %d %d",&j,&k,&l);
        while((!feof(gecici)))
        {
            gec->ogrNo=j;
            gec->dersKodu=k;
            gec->puan=l;

            fwrite(gec,sizeof(struct Ogrenci),1,veri);
            fscanf(gecici,"%d %d %d",&j,&k,&l);







        }
        fclose(gecici);
        fclose(veri);

    }
    indeks = fopen("indeks.txt", "r");
    gecici2=fopen("gecici2.txt","w");
    if(indeks==NULL)
    {
        printf("Dosya gosterilemedi \n");
    }
    else
    {


        while((!feof(indeks)))
        {
            fscanf(indeks,"%d %d",&a,&b);
            if(gir!=a)

            {
                fprintf(gecici2,"%d %d \n",a,b);

            }


        }

        fclose(indeks);
        fclose(gecici2);
    }


    int sayac=0;

    veri=fopen("veri.bin","rb");
    {
        if(veri!=NULL)
        {
            fread(&ogr,sizeof(struct Ogrenci),1,veri);
            while((!feof(veri)))
            {
                sayac++;
                fread(&ogr,sizeof(struct Ogrenci),1,veri);
            }
        }

        fclose(veri);
    }
    int *dizi1,*dizi2;
    dizi1 = (int*) malloc(sayac * sizeof(int));

    dizi2 = (int*) malloc(sayac * sizeof(int));


    int i=0;



    indeks=fopen("indeks.txt","w");
    gecici2=fopen("gecici2.txt","r");
    int x1,x2;
    fscanf(gecici2,"%d %d",&x1,&x2);
    while((!feof(gecici2)))
    {
        dizi1[i]=x1;
        dizi2[i]=x2;
        fscanf(gecici2,"%d %d",&x1,&x2);
        i++;
    }
    int tut,m;
    for(m=0; m<i; m++)
    {
        for (int k=0; k<i; k++)
        {
            if (dizi1[k]>dizi1[k+1])
            {
                tut=dizi1[k];
                dizi1[k]=dizi1[k+1];
                dizi1[k+1]=tut;
                tut=dizi2[k];
                dizi2[k]=dizi2[k+1];
                dizi2[k+1]=tut;

            }
        }
    }

    for (int k=0; k<i; k++)
    {
        fprintf(indeks,"%d %d\n",dizi1[k],dizi2[k]);

    }
    fclose(gecici2);
    fclose(indeks);
    printf("Kayit silindi.\n");
}
void kayitGuncelle()
{
    int gir,a,b,adres;
    printf("Hangi nolu ogrenci kaydi guncellensin :");
    scanf("%d",&gir);

    indeks = fopen("indeks.txt", "r");
    if(indeks==NULL)
    {
        printf("Dosya gosterilemedi \n");
    }
    else
    {


        while((!feof(indeks)))
        {
            fscanf(indeks,"%d %d",&a,&b);
            if(gir==a)
            {
                gir=a;
                adres=b;
                break;
            }


        }

        fclose(indeks);
    }


    struct Ogrenci ogr;
    int yeninot;

    veri=fopen("veri.bin","rb");
    gecici=fopen("gecici.txt","w");
    if(veri!=NULL)
    {


        fread(&ogr,sizeof(struct Ogrenci),1,veri);
        while((!feof(veri)))
        {
            if(gir==ogr.ogrNo)
            {
                printf("Yeni not giriniz :");
                scanf("%d",&yeninot);
                ogr.puan=yeninot;
                fprintf(gecici,"%d %d %d \n",ogr.ogrNo,ogr.dersKodu,ogr.puan);
            }
            fprintf(gecici,"%d %d %d \n",ogr.ogrNo,ogr.dersKodu,ogr.puan);
            fread(&ogr,sizeof(struct Ogrenci),1,veri);





        }
    }
    fclose(veri);
    fclose(gecici);
    veri=fopen("veri.bin","wb");
    gecici=fopen("gecici.txt","r");
    struct indeks *ind=(struct indeks*)malloc(sizeof(struct indeks));
    struct Ogrenci *gec=(struct Ogrenci*)malloc(sizeof(struct Ogrenci));
    int j,k,l;


    if(veri!=NULL)
    {



        fscanf(gecici,"%d %d %d",&j,&k,&l);
        while((!feof(gecici)))
        {
            gec->ogrNo=j;
            gec->dersKodu=k;
            gec->puan=l;

            fwrite(gec,sizeof(struct Ogrenci),1,veri);
            fscanf(gecici,"%d %d %d",&j,&k,&l);

        }
        fclose(gecici);
        fclose(veri);

    }
    indeks = fopen("indeks.txt", "r");
    gecici2=fopen("gecici2.txt","w");
    if(indeks==NULL)
    {
        printf("Dosya gosterilemedi \n");
    }
    else
    {


        while((!feof(indeks)))
        {
            fscanf(indeks,"%d %d",&a,&b);
            if(gir!=a)

            {
                fprintf(gecici2,"%d %d \n",a,b);

            }


        }

        fclose(indeks);
        fclose(gecici2);
    }
    printf("Kayit guncellendi.\n");
}
int main()
{
    int islem1;

    while(1)
    {

        printf("\n\n");
        printf("****************************************************\n");
        printf("Islem no giriniz\n");
        printf("Cikmak icin 0:\n");
        printf("Veri Dosyasindaki Kayitlari Gostermek Icin 1:\n");
        printf("Kayit Eklemek Icin 2:\n");
        printf("Kayit Guncellemek Icin 3:\n");
        printf("Kayit Silmek Icin 4:\n");
        printf("Kayit Bulmak Icin 5:\n");
        printf("Indeks Dosyasindaki Kayitlari Gostermek Icin 6:\n");
        printf("Indeks Dosyasi Olusturmak icin 7:\n");
        printf("Indeks Dosyasini Silmek Icin 8:\n");
        printf("****************************************************\n");
        printf("Secim :");


        scanf("%d",&islem1);
        switch(islem1)
        {
        case 0:
        {
            exit(0);
            break;
        }
        case 1:
        {
            veriDosyasiniGoster();
            break;
        }
        case 2:
        {
            kayitEkle();
            break;
        }
        case 3:
        {

            kayitGuncelle();

            break;
        }
        case 4:
        {
            kayitSil();

            break;
        }
        case 5:
        {
            kayitBul();
            break;
        }
        case 6:
        {
            indeksDosyasiniGoster();
            break;
        }
        case 7:
        {
            indeksDosyasiOlustur();
            break;
        }
        case 8:
        {

            indeksDosyasiniSil();

            break;
        }

        default:
            printf("Yanlis deger girdiniz . Islemlere donuluyor\n");


        }
    }
    return 0;
}
