#include <iostream>
#include <fstream>

using namespace std;

class hesap
{
public:
    string hsismi;
    int hesapno;
    float bakiye;
    int hesapturu;
    hesap();
    void parayatir(int hesapno,float para);
    void paracek(int hesapno,float para);
    void bilgigoruntule(int hesapno);
    void hesapekle();
};

hesap bir;

int main(int argc, char **argv)
{
    float para;
    int secim;
    
    bir.hesapekle();
    
    while(true){
        cout << "Banka islemlerine hosgeldiniz!\n\n";
        cout << "Lutfen islem yapmak istediginiz secenegi belirleyiniz:\n\n";
        cout << "Para yatirma -> 1\n";
        cout << "Para cekme -> 2\n";
        cout << "Bakiye goruntuleme -> 3\n";
        cout << "Cikis -> 4\n";
        
        cout << "Seciminiz: ";
        cin >> secim;
        
        switch(secim){
            case 1:
            cout << endl << "Yatiralacak miktari giriniz: ";
            cin >> para;
            cout << endl << "Hesap noyu giriniz: ";
            cin >> bir.hesapno;
            bir.parayatir(bir.hesapno,para);
            break;
            case 2:
            cout << endl << "Cekilecek miktari giriniz: ";
            cin >> para;
            cout << endl << "Hesap noyu giriniz: ";
            cin >> bir.hesapno;
            bir.paracek(bir.hesapno,para);
            break;
            case 3:
            cout << endl << "Goruntulemek istediginiz hesap noyu giriniz: ";
            cin >> bir.hesapno;
            bir.bilgigoruntule(bir.hesapno);
            break;
            case 4:
            exit(0);
            break;
            default:
            cout << "Yanlis secim" << endl;
            break;
        }
    }
}

hesap::hesap(){
    bir.bakiye=0.0;
}

void hesap::parayatir(int hesapno, float para){
    ifstream oku;
    ofstream yaz;
    
    oku.open("banka.txt",ios::in);
    yaz.open("bankaguncel.txt",ios::out);
    
    if(!oku.is_open() || !yaz.is_open()){
        cout << "Dosya acilamiyor." << endl;
    }
    
    while(!oku.eof()){
        oku >> bir.hesapno >> bir.hsismi >> bir.bakiye >> bir.hesapturu;
        
        if(hesapno==bir.hesapno){
            bir.bakiye=bir.bakiye+para;
            yaz << bir.hesapno << " " << bir.hsismi << " " << bir.bakiye << " " << bir.hesapturu << endl;
        }
        else{
            cout << "Hesap numarasi maalesef eslesmedi." << endl;
            yaz << bir.hesapno << " " << bir.hsismi << " " << bir.bakiye << " " << bir.hesapturu << endl;
        }
    }
    oku.close();
    yaz.close();
    
    remove("banka.txt");
    rename("bankaguncel.txt","banka.txt");
}

void hesap::paracek(int hesapno,float para){
    ifstream oku;
    ofstream yaz;
    
    oku.open("banka.txt",ios::in);
    yaz.open("bankaguncel.txt",ios::out);
    
    if(!oku.is_open() || !yaz.is_open()){
        cout << "Dosya acilamiyor." << endl;
    }
    
    while(!oku.eof()){
        oku >> bir.hesapno >> bir.hsismi >> bir.bakiye >> bir.hesapturu;
        
        if(hesapno==bir.hesapno && bir.bakiye-para<0){
            cout << endl << "Yetersiz bakiye." << endl;
            yaz.close();
            break;
        }
        else if(hesapno==bir.hesapno && bir.bakiye-para>=0){
            bir.bakiye=bir.bakiye-para;
            yaz << bir.hesapno << " " << bir.hsismi << " " << bir.bakiye << " " <<bir.hesapturu << endl;
        }
        else if(hesapno!=bir.hesapno){
            cout << "Hesap numarasi maalesef eslesmedi." << endl;
            yaz << bir.hesapno << " " << bir.hsismi << " " << bir.bakiye << " " <<bir.hesapturu << endl;
        }
    }
    oku.close();
    yaz.close();
    
    remove("banka.txt");
    rename("bankaguncel.txt","banka.txt");
}

void hesap::bilgigoruntule(int hesapno){
    ifstream oku;
    
    oku.open("banka.txt",ios::in);
    
    if(!oku.is_open()){
        cout << "Dosya acilamiyor." << endl;
    }
    
    while(!oku.eof()){
        oku >> bir.hesapno >> bir.hsismi >> bir.bakiye >> bir.hesapturu;
        
        if(hesapno==bir.hesapno){
            cout << bir.hesapno << " " << bir.hsismi << " " << bir.bakiye << " " << bir.hesapturu << endl;
            break;
        }
        else
            cout << "Hesap numarasi maalesef eslesmedi." << endl;
    }
    oku.close();
}

void hesap::hesapekle(){
    ofstream yaz;
    char k;
    
    yaz.open("banka.txt",ios::app);
    
    if(!yaz.is_open()){
        cout << "Dosya acilamiyor." << endl;
    }
    
    while(true){
        s1:
        cout << "Hesap eklemek icin e'ye cikmak icin c'ye basiniz: ";
        cin >> k;
        
        if(k=='c')
            break;
            
        else if(k=='e'){
            cout << endl << "Eklenecek hesap no: ";
            cin >> bir.hesapno;
            cout << endl << "Eklenecek hesabin ismi: ";
            cin >> bir.hsismi;
            cout << endl << "Eklenecek hesap bakiyesi: ";
            cin >> bir.bakiye;
            cout << endl << "Eklenecek hesap turu (0-vadesiz, 1-vadeli): ";
            cin >> bir.hesapturu;
            yaz << endl << bir.hesapno << " " << bir.hsismi << " " << bir.bakiye << " " << bir.hesapturu;
        }
        else{
            cout << endl << "Yanlis karaktere bastiniz." << endl;
            goto s1;
        }
    }
    yaz.close();
}