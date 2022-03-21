struct msg
{
    long msgtyp;
    int ilosc_misiow;
    int ilosc_robotnic;
    int ilosc_wojownikow;
    int ilosc_krolowych;
    int ilosc_miodku;
};

struct order
{
    int typ;
    int typ_pszczoly;
    int ilosc;
};

struct msgbuf
{
    long mtype;
    struct order zamowienie;
};

struct msgpid
{
    long mtype;
    int processPID;
};