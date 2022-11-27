/* Copyright (C) 2022 Aleksandar Tomić - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the GNU AGPL v3.0 license.
 *
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: Kanduti, or visit : https://github.com/Kanduti/Album-playlister/blob/main/LICENSE
*/
#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>

using namespace std;

string zanr, album, extention;
ifstream Unet();
string line[70];

void singular_timestamp(string line[70], string& odKad, string& doKad, int pos, int i, int w, int wbuff, int pbuff)
{
   // avoiding outOfRange
    if (pbuff > 1){
            if(isdigit(line[i-1][pbuff-2])){ //some nigger put time stamps in parentasis
        odKad = line[i - 1].substr(pbuff - 2, wbuff + 2);
            }
            else {
                odKad = line[i - 1].substr(pbuff - 1, wbuff + 1);
            }
    }
    else
        odKad = line[i - 1].substr(pbuff - 1, wbuff + 1);
    if (pos > 1){ // same as above
            if(isdigit(line[i][pos-2]))
            {
        doKad = line[i].substr(pos - 2, w + 2);
            }else {
            doKad = line[i].substr(pos - 1, w + 1);
            }
    }
    else
        doKad = line[i].substr(pos - 1, w + 1);

}




void dupli_timestamp(string line[70], string& odKad, string& doKad, int pos, int i, int w) // doKad nema zavrsetak dakle ne radi kada je br prvi
{

    int crta, razmak, drugi, crta_linija, dvostruki, trostruki;


    crta = line[i].find("-", pos);
    if (crta != -1) {
        crta_linija = line[i].find("- ", pos);
        if (crta_linija != -1)
        {
            odKad = line[i].substr(pos - 2, crta - pos + 1);
            doKad = line[i].substr(crta + 2);
        }
        else
        {
            odKad = line[i].substr(pos - 2, crta - pos + 2);
            doKad = line[i].substr(crta + 1);
        }

    }
    else
    {
        razmak = line[i].find(" ", pos);
        if (razmak != -1)
        {  //cout<<" jednostruki razmak ";
            dvostruki = line[i].find("  ", pos);
            if (dvostruki != -1)
            {  // cout<<" dvostruki razmak ";
                odKad = line[i].substr(pos - 2, razmak - pos + 2);
                doKad = line[i].substr(dvostruki + 1, pos + w - razmak);
                trostruki = line[i].find("   ", pos);
                if (trostruki != -1)
                {   //cout<<" cak trostruki razmak ";
                    odKad = line[i].substr(pos - 2, razmak - pos + 2);
                    doKad = line[i].substr(trostruki + 1, pos + w - razmak);

                }
            }
            else {
                odKad = line[i].substr(pos - 2, razmak - pos + 2);
                doKad = line[i].substr(razmak + 1, pos + w - razmak);

            }
        }
        else cout << "nema razmaka";

    }
}



int main() {

    remove("iseckaj.bat");

    // Create and open a text file

    ofstream MyFile("iseckaj.bat");



    // biranje albuma
    string tStampPath, albumFPath, albumName, albumRelPath;
    cout << "enter full path of timestamp file: " << endl;
    getline(cin, tStampPath);
    tStampPath.erase(0, 1);
    tStampPath.pop_back();
    cout << tStampPath << endl;
    cout << "enter full path of music file: " << endl;
    getline(cin, albumFPath);
    albumFPath.erase(0, 1);
    albumFPath.pop_back();
    int s = albumFPath.rfind("\\");
        albumName = albumFPath.substr(s);
    albumRelPath = albumFPath.substr(0, s);
    cout<<"album rel path: "<<albumRelPath<<endl;
    int priv = albumName.find(".");
    extention = albumName.substr(priv);
    cout<<"extention: "<<extention<<endl;
    ifstream Unet(tStampPath);
    // fajl specifikacije
    string line[70];
    string imePesme[150];
    string odKadDoKad[70];

    string imebuff;
    //string odKadbuff;
    // this works

   // string imebuff;
    int wbuff;
    int pbuff;
    int postmortem;


    if (Unet.is_open())
    {

        string odKad;
        string doKad;
        for (int i = 0; getline(Unet, line[i]); i++) {

            size_t pos = line[i].find(":");
            int w = 0;

            //pos + w nam daje poziciju poslednjeg broja
            while (isdigit(line[i][pos + w]) || isdigit(line[i][pos + w + 1]) || isdigit(line[i][pos + w + 4]) || isdigit(line[i][pos + w + 3]))
            {
                w++;
            }



            if (isalpha(line[i][4]) || isalpha(line[i][3]) || isalpha(line[i][2] || (isalpha(line[i][5]) && pos > 5)) || (isalpha(line[i][6] && pos > 6)))
            {

                //AKO JE IME PRVO
                int kraj;  //pozicija kranjeg slova imena
                int pocetak = 0; // pozicija pocetnog slova

                    //pos je pozicija prve dvotacke
                    // deluje dobro (trazi zadnje slovo)
                bool isAlpha = isalpha(line[i][pos - 3]);
                bool isAlpha1 = isalpha(line[i][pos - 4]);
                if (isAlpha)
                {
                    kraj = pos - 3;
                }
                else if (isAlpha1) {
                    kraj = pos - 4;
                    //  bool isAlpha2 = isalpha(line[i][pos-5], loc);}
                }
                else if (isalpha(line[i][pos - 5])) {
                    kraj = pos - 5;
                    // bool isAlpha3 = isalpha(line[i][pos-6], loc);
                }
                else if (isalpha(line[i][pos - 6])) {
                    kraj = pos - 6;
                }
                else if (isalpha(line[i][pos - 7])) {
                    kraj = pos - 7;
                }
                else if (isalpha(line[i][pos - 8]))
                {
                    kraj = pos - 8;
                }



                for (int p = 0; p < line[i].size(); p++) {
                    if (isalpha(line[i][p]))
                    {
                        pocetak = p;
                        break;
                    }

                }
                //  cout<<"  pocetak: "<<pocetak<<endl;

                imePesme[i] = line[i].substr(pocetak, kraj - pocetak + 1);

                odKadDoKad[i] = line[i].substr(pos - 2, w + 2);

                if (odKadDoKad[i].size() > 8)
                {
                    dupli_timestamp(line, odKad, doKad, pos, i, w);
                     MyFile << "@ECHO OFF \n"
                        "ffmpeg -i \"" << albumFPath << "\" -ss " << odKad << " -to " << doKad << " -c:v copy -c:a copy \"" << albumRelPath << "\\" << imePesme[i] << extention << "\"\n";
                    cout << "ime pesme je: " << imePesme[i] << "  period pesme je: " << odKad << " " << doKad << endl;
                }
                else if (i != 0) {
                    // on mi mozda printuje 0 ime ali zato imaj indikator
                    // PREDHODNI POS I W

                    singular_timestamp(line, odKad, doKad, pos, i, w, wbuff, pbuff);
                     MyFile << "@ECHO OFF \n"
                        "ffmpeg -i \"" << albumFPath << "\" -ss " << odKad << " -to " << doKad << " -c:v copy -c:a copy \"" << albumRelPath << "\\" << imePesme[i - 1] << extention << "\"\n";
                    cout << "ime pesme je: " << imePesme[i - 1] << "  period pesme je: " << odKad << " " << doKad << endl;

                }

            }
            else {


                // AKO JE BROJ PRVI (status: works)

                if (pos > 1)
                {
                    odKadDoKad[i] = line[i].substr(pos - 2, w + 2);
                }
                else
                {
                    odKadDoKad[i] = line[i].substr(pos - 1, w + 2);
                }

                imePesme[i] = line[i].substr(pos + w + 1);
                //   imePesme[i]=line[i].substr(pos+w+1);

        //dupli time stamp
                if (odKadDoKad[i].size() > 8)
                {
                    dupli_timestamp(line, odKad, doKad, pos, i, w);
                    MyFile << "@ECHO OFF \n"
                        "ffmpeg -i \"" << albumFPath << "\" -ss " << odKad << " -to " << doKad << " -c:v copy -c:a copy \"" << albumRelPath << "\\" << imePesme[i] << extention << "\"\n";
                    cout << "ime pesme je: " << imePesme[i] << "  period pesme je: " << odKad << " " << doKad << endl;
                }
                else if (i != 0) {

                    singular_timestamp(line, odKad, doKad, pos, i, w, wbuff, pbuff);
                    MyFile << "@ECHO OFF \n"
                        "ffmpeg -i \"" << albumFPath << "\" -ss " << odKad << " -to " << doKad << " -c:v copy -c:a copy \"" << albumRelPath << "\\" << imePesme[i - 1] << extention << "\"\n";
                    cout << "ime pesme je: " << imePesme[i - 1] << "  period pesme je: " << odKad << " " << doKad << endl; // nije dobro jer ti se nece poslednji odstampati
                }


            }

            wbuff = w;
            pbuff = pos;
            //cout<<"ime pesme je: "<<imePesme[i]<<"  period pesme je: "<<odKad<<" "<<doKad<<endl;
            postmortem = i;

        } // izlazak iz fora

        if (odKadDoKad[postmortem].size() < 9)
        {
            cout << "ime pesme je: " << imePesme[postmortem] << "  period pesme je: " << doKad << endl;
            MyFile << "@ECHO OFF \n"
                "ffmpeg -i \""<< albumFPath << "\" -ss " << odKad << " -to " << doKad << " -c:v copy -c:a copy \"" << albumRelPath << "\\" << imePesme[postmortem] << extention << "\"\n";

        }

        //  MyFile <<"@ECHO OFF \n ffmpeg -i \"C:\\Users\\milan\\Music\\zanr\\album\" -ss "<<odKad<<" -to "<<doKad<<" -c:v copy -c:a copy \"C:\\Users\\milan\\Music\\"<<imePesme[i]<<"\"\n";

    }
    else cout << "nece da otvori fajl";
    Unet.close();



    //   if()
      // / Write to the file


         // Close the file
    MyFile.close();

    system("iseckaj.bat");






    return 0;
}
