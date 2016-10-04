#define _BALANCE      0
#define _BLOOD        1    // see _TRANSFUSION
#define _BREAST       2
#define _BUPA         3
#define _CAR 	       4    // vela casu (cca 2 dni)
#define _CMC          5    // vela casu (cca 4 dni)
#define _CRX          6    // oFDT and sFDT potrebuju vela casu
#define _DIAGNOSIS    7
#define _ECOLI        8
#define _FAULTS       9
#define _FOREST      10
#define _GERMAN      11
#define _GERMAN24    12
#define _GLASS       13    // 4-5 dni
#define _HABERMAN    14
#define _HEART       15       // oFDT and sFDT potrebuju vela casu  (2-3 tyzden)
#define _ILPD        16
#define _IMAGE       17
#define _IRIS        18

#define _PAGEBLOCKS  19
#define _NURSERY     20
#define _PARKINSONS  21
#define _PIMA        22
#define _SEEDS       23
#define _SONAR       24
#define _TAE         25    // CART nie
#define _THYROID     26
#define _TIC 	      27
#define _VENICLE     28       // oFDT and sFDT potrebuju vela casu
#define _VERTEBRAL2  29
#define _VERTEBRAL3  30
#define _VOWEL 	   31    // vela casu (cca 7 dni)

#define _WDBC        32
#define _WINE        33
#define _WINERED     34
#define _WINEWHITE   35      // red schitala den
#define _WPBC        36
#define _YEAST       37    // 100 za den

#define _LETTER      39

#define _PENDIGITS   43

  #define _IONOSPHERE 60
  #define _KRKOPT     61 // po 1 experimentu      zavisaet na CART-8
  #define _MAGIC      62

// ------------------------------------------
   #define _BANK       55       // oFDT and sFDT potrebuju vela casu
// ------------------------------------------
  #define _ConfJSI     70        // bad
  #define _MINIBOONE   71
  #define _PLRX        72
  #define _SENSOR2     73
  #define _SENSOR4     74
  #define _SENSOR24    75
  #define _SKIN        76       // oFDT and sFDT potrebuju vela casu (No 2 -> 4 dni)
// ------------------------------------------
#define _ABALONE     90      // 1 experiment only
#define _MONKS1      91      // 1 experiment only
#define _MONKS2      92
#define _MONKS3      93
#define _SHUTTLE     94       // 1 experiment only

#define _GOLF       1098       // used for teacher only
#define _SAT_UA     1099       // unknown class attribute
#define _SEMESTR    1097
#define _TEST       1096
#define _POLAND     1100
#define _IOSIF      1101
#define _IOSIF_LENA 1102
#define _LENKA      1103
#define _OSTRAVA1   1104
#define _OSTRAVA10  1110
#define _OSTRAVA2BEZ 1122

#define _SF1        1105
#define _SF_NATVIG  1106
#define _SF_XING    1107
#define _SF_KAPUR   1108

#define _LENKA_DECERNO 1109
#define _PODOFILINI  1111
// -------------------------------------------------------------
#define PATHinCrisp    "c:\\cpp\\DataSets\\db_all\\"
#define PATHoutCrisp   "c:\\cpp\\DataSets\\"
typedef struct  { float* A; } instance;

class DataSets
{ public:
    unsigned long   TotalSets;
    unsigned int    NumberOfAttributes;
	 unsigned int    NumberOfInputAttributes;
    unsigned int    NumberOfOutputAttributes;
    unsigned int    NumberOfOutputIntervals;
    unsigned int*   nonNumericAttributes;
    instance*       R;
    char            nameDB[50];
  public:
    DataSets                    (unsigned int numDB);
    ~DataSets();
    int    ReadDataSets         (unsigned int numDB);
    int    WriteCrispFile       (void);


    int    ReadCrispFileBalance    (FILE* fp);
	 int	  ReadCrispFileBlood	     (FILE* fp);
    int	  ReadCrispFileBreast     (FILE* fp);
    int    ReadCrispFileBupa       (FILE* fp);
	 int	  ReadCrispFileCar		  (FILE* fp);
    int    ReadCrispFileCmc        (FILE* fp);
    int    ReadCrispFileCrx        (FILE* fp);
  	 int	  ReadCrispFileDiagnosis  (FILE* fp);
    int    ReadCrispFileEcoli      (FILE* fp);
	 int	  ReadCrispFileForestfires(FILE* fp);
    int    ReadCrispFileGerman     (FILE* fp);
    int    ReadCrispFileGerman24   (FILE* fp);
    int    ReadCrispFileGlass      (FILE* fp);
    int    ReadCrispFileGolf       (FILE* fp);
    int    ReadCrispFileHaberman   (FILE* fp);
	 int	  ReadCrispFileILPD       (FILE* fp);
    int    ReadCrispFileImage      (FILE* fp);
    int    ReadCrispFileIonosphere (FILE* fp);
    int	  ReadCrispFileIosif         (FILE* fp);
    int	  ReadCrispFileIosifLena     (FILE* fp);
    int	  ReadCrispFileLenka         (FILE* fp);
    int	  ReadCrispFileLenkaDecerno  (FILE* fp);
    int	  ReadCrispFilePodofilini (FILE* fp);

    int	  ReadCrispFileSF1           (FILE* fp);
    int	  ReadCrispFileSFNatvig      (FILE* fp);
    int	  ReadCrispFileSFXing        (FILE* fp);
    int	  ReadCrispFileSFKapur       (FILE* fp);

    int    ReadCrispFileIris       (FILE* fp);
    int    ReadCrispFileLetter     (FILE* fp);
    int    ReadCrispFileOstrava1   (FILE* fp);
    int    ReadCrispFileOstrava10  (FILE* fp);
    int    ReadCrispFileOstrava2bez(FILE* fp);

	 int	  ReadCrispFileParkinsons (FILE* fp);
    int    ReadCrispFilePendigits  (FILE* fp);
    int    ReadCrispFilePima       (FILE* fp);
    int    ReadCrispFilePlrx       (FILE* fp);
    int	  ReadCrispFilePoland        (FILE* fp);
    int    ReadCrispFileSeeds      (FILE* fp);
    int    ReadCrispFileSensor2    (FILE* fp);
    int    ReadCrispFileSensor4    (FILE* fp);
    int    ReadCrispFileSensor24   (FILE* fp);
	 int	  ReadCrispFileSonar	     (FILE* fp);
    int    ReadCrispFileTae        (FILE* fp);
    int    ReadCrispFileThyroid    (FILE* fp);
	 int	  ReadCrispFileTic	     (FILE* fp);
	 int	  ReadCrispFileVertebral  (FILE* fp);
	 int    ReadCrispFileVowel	     (FILE* fp);
    int    ReadCrispFileWDBC       (FILE* fp);
    int    ReadCrispFileWPBC       (FILE* fp);
    int    ReadCrispFileWine       (FILE* fp);
    int	  ReadCrispFileWineQuality(FILE* fp);
    int    ReadCrispFileYeast      (FILE* fp);


    int    ReadCrispFileAbalone    (FILE* fp);
  	 int	  ReadCrispFileBank        (FILE* fp);
	 int	  ReadCrispFileSkin        (FILE* fp);
 	 int    ReadCrispFileConfLongDemo(FILE* fp);
 	 int    ReadCrispFileFaults      (FILE* fp);
 	 int    ReadCrispFileMiniBooNE   (FILE* fp);
 	 int	  ReadCrispFileSatUA       (FILE* fp);
    int	  ReadCrispFileSemestralka (FILE* fp);         //
    int	  ReadCrispFileTest        (FILE* fp);         //

    int	  ReadCrispFileHeart       (FILE* fp);
    int    ReadCrispFileKrkopt      (FILE* fp);
    int	  ReadCrispFileMagic       (FILE* fp);
    int	  ReadCrispFileMonks       (FILE* fp);
    int	  ReadCrispFileNursery     (FILE* fp);
    int    ReadCrispFilePageblocks  (FILE* fp);
    int	  ReadCrispFileShuttle     (FILE* fp);
    int	  ReadCrispFileVenicle     (FILE* fp);

    char*         ReturnNameDB   (void){return(nameDB);}
    unsigned long ReturnTotalSets(void){return(TotalSets);}
    unsigned int  ReturnNoA      (void){return(NumberOfAttributes);}
    float         InitialError   (unsigned int numDB);
};
//  ---------------------------------------------------------------------------
DataSets::DataSets(unsigned int numDB)
{ unsigned int     NoA, NoIA, NoOA, NoOI;
  unsigned long    TS;
  switch(numDB)
  { case _BALANCE:   strcpy(nameDB, "balance1");
                     TS =    625;   NoIA =  4;  NoOA = 1; NoOI =  3; break;
    case _BANK:      strcpy(nameDB, "bank");
                     TS =  45211;   NoIA = 16;  NoOA = 1; NoOI =  2; break;
    case _BLOOD:     strcpy(nameDB, "blood");
                     TS =    748;   NoIA =  4;  NoOA = 1; NoOI =  2; break;
    case _BREAST:    strcpy(nameDB, "breast");
                     TS =    106;   NoIA =  9;  NoOA = 1; NoOI =  6; break;
    case _BUPA:      strcpy(nameDB, "bupa");
                     TS =    345;   NoIA =  6;  NoOA = 1; NoOI =  2; break;
    case _CAR:       strcpy(nameDB, "car");
                     TS =   1728;   NoIA =  6;  NoOA = 1; NoOI =  4; break;
    case _CMC:       strcpy(nameDB, "cmc");
                     TS =   1473;   NoIA =  9;  NoOA = 1; NoOI =  3; break;
    case _CRX:       strcpy(nameDB, "crx");
                     TS =    653;   NoIA = 15;  NoOA = 1; NoOI =  2; break;// TS=690 ???
    case _DIAGNOSIS: strcpy(nameDB, "diagnosis");                          // NoOA=2
                     TS =    120;   NoIA =  6;  NoOA = 1; NoOI =  2; break;
    case _ECOLI:     strcpy(nameDB, "ecoli");
                     TS =    336;   NoIA =  7;  NoOA = 1; NoOI =  8; break;
    case _FOREST:    strcpy(nameDB, "forestfires");
                     TS =    517;   NoIA = 12;  NoOA = 1; NoOI =  3; break;// NoOI=4 ???
    case _GERMAN:    strcpy(nameDB, "german");
                   TS = 1000 ; NoIA = 20 ; NoOA = 1 ; NoOI = 2 ; break ;
    case _GERMAN24:  strcpy(nameDB, "german24");
                   TS = 1000 ; NoIA = 24 ; NoOA = 1 ; NoOI = 2 ; break ;
    case _GLASS:     strcpy(nameDB, "glass");
                     TS =    214;   NoIA =  9;  NoOA = 1; NoOI =  7; break;
    case _HABERMAN:  strcpy(nameDB, "haberman");
                     TS =    306;   NoIA =  3;  NoOA = 1; NoOI =  2; break;
    case _HEART:     strcpy(nameDB, "heart");
                     TS =    270;   NoIA = 13;  NoOA = 1; NoOI =  2; break;
    case _ILPD:      strcpy(nameDB, "ilpd");                               // TS-4 (miss record No 209, etc)
                     TS =    579;   NoIA = 10;  NoOA = 1; NoOI =  2; break;
    case _IMAGE:     strcpy(nameDB, "image1");                             // input attribut A[2] is 9 ???
                     TS =   2100;   NoIA = 18;  NoOA = 1; NoOI =  7; break;
    case _IONOSPHERE:strcpy(nameDB, "ionosphere");                         // input attribut A[1] is empty ???
                     TS =    351;   NoIA = 33;  NoOA = 1; NoOI =  2; break;
    case _IRIS:      strcpy(nameDB, "iris");
                     TS =    150;   NoIA =  4;  NoOA = 1; NoOI =  3; break;
    case _KRKOPT:    strcpy(nameDB, "krkopt");
                     TS =  28056;   NoIA =  6;  NoOA = 1; NoOI = 18; break;
    case _LETTER:    strcpy(nameDB, "letter");
                     TS =  20000;   NoIA = 16;  NoOA = 1; NoOI = 26; break;
    case _MAGIC:     strcpy(nameDB, "magic04");
                     TS =  19020;   NoIA = 10;  NoOA = 1; NoOI =  2; break;
    case _NURSERY:   strcpy(nameDB, "nursery");
                     TS =  12960;   NoIA =  8;  NoOA = 1; NoOI =  5; break;
    case _PAGEBLOCKS:strcpy(nameDB, "pageblocks");
                     TS =   5473;   NoIA = 10;  NoOA = 1; NoOI =  5; break;
    case _PARKINSONS:strcpy(nameDB, "parkinsons");
                     TS =    195;   NoIA = 22;  NoOA = 1; NoOI =  2; break;
    case _PENDIGITS: strcpy(nameDB, "pendigits");
                     TS =  10992;   NoIA = 16;  NoOA = 1; NoOI = 10; break;
    case _PIMA:      strcpy(nameDB, "pima");
                     TS =    768;   NoIA =  8;  NoOA = 1; NoOI =  2; break;
    case _PLRX:      strcpy(nameDB, "plrx");
                     TS =    182;   NoIA = 12;  NoOA = 1; NoOI =  2; break;
    case _SEEDS:     strcpy(nameDB, "seeds");
                     TS =    210;   NoIA =  7;  NoOA = 1; NoOI =  3; break;
    case _SENSOR2:   strcpy(nameDB, "sensor2");
                     TS =   5456;   NoIA =  2;  NoOA = 1; NoOI =  4; break;
    case _SENSOR4:   strcpy(nameDB, "sensor4");
                     TS =   5456;   NoIA =  4;  NoOA = 1; NoOI =  4; break;
    case _SENSOR24:  strcpy(nameDB, "sensor24");
                     TS =   5456;   NoIA = 24;  NoOA = 1; NoOI =  4; break;
    case _SKIN:      strcpy(nameDB, "skin");
                     TS = 245057;   NoIA =  3;  NoOA = 1; NoOI =  2; break;
    case _SONAR:     strcpy(nameDB, "sonar");
                     TS =    208;   NoIA = 60;  NoOA = 1; NoOI =  2; break;
    case _TAE:       strcpy(nameDB, "tae");
                     TS =    151;   NoIA =  5;  NoOA = 1; NoOI =  3; break;
    case _THYROID:   strcpy(nameDB, "new-thyroid");
                     TS =    215;   NoIA =  5;  NoOA = 1; NoOI =  3; break;
    case _TIC:       strcpy(nameDB, "tic");
                     TS =    958;   NoIA =  9;  NoOA =1 ; NoOI =  2; break;
    case _VENICLE:   strcpy(nameDB, "venicle");
                     TS =    846;   NoIA = 18;  NoOA = 1; NoOI =  4; break;
    case _VERTEBRAL2:strcpy(nameDB, "vertebral2");
                     TS =    310;   NoIA =  6;  NoOA = 1; NoOI =  2; break;
    case _VERTEBRAL3:strcpy(nameDB, "vertebral3");
                     TS =    310;   NoIA =  6;  NoOA = 1; NoOI =  3; break;
    case _VOWEL:     strcpy(nameDB, "vowel");
                     TS =    990;   NoIA = 10;  NoOA = 1; NoOI = 11; break;
    case _WDBC:      strcpy(nameDB, "wdbc");
                     TS =    569;   NoIA = 30;  NoOA = 1; NoOI =  2; break;
    case _WINE:      strcpy(nameDB, "wine");
                     TS =    178;   NoIA = 13;  NoOA = 1; NoOI =  3; break;
    case _WINERED:   strcpy(nameDB, "winequalityred");
                     TS =   1599;   NoIA = 11;  NoOA = 1; NoOI =  6; break;
    case _WINEWHITE: strcpy(nameDB, "winequalitywhite");
                     TS =    4898;  NoIA = 11;  NoOA = 1; NoOI =  7; break;
    case _WPBC:      strcpy(nameDB, "wpbc1");
                     TS =    194;   NoIA = 33;  NoOA = 1; NoOI =  2; break;     // TS=198, NoIA=32
    case _YEAST:     strcpy(nameDB, "yeast");
                     TS =   1484;   NoIA =  8;  NoOA = 1; NoOI = 10; break;
// ----------------------
    case _ABALONE:   strcpy(nameDB, "abalone");
                   TS   =4177;  NoIA = 8;  NoOA = 1; NoOI = 28; break;
    case _ConfJSI:   strcpy(nameDB, "confLongDemo");
                   TS   = 164860;  NoIA = 7;  NoOA = 1; NoOI = 11; break;
    case _FAULTS:    strcpy(nameDB, "faults");
                   TS   =   1941;  NoIA = 27;  NoOA = 1; NoOI = 7; break;
    case _GOLF:      strcpy(nameDB, "golf");
                   TS =   14 ; NoIA = 4 ; NoOA = 1 ; NoOI = 2 ; break ;
    case _MINIBOONE:    strcpy(nameDB, "miniboone");
                   TS   =   130065;NoIA = 50;  NoOA = 1; NoOI = 2; break;
    case _MONKS1:     strcpy(nameDB, "monks1");
                   TS   =    556;  NoIA = 6;  NoOA = 1; NoOI = 2; break;
    case _MONKS2:     strcpy(nameDB, "monks2");
                   TS   =    601;  NoIA = 6;  NoOA = 1; NoOI = 2; break;
    case _MONKS3:     strcpy(nameDB, "monks3");
                   TS   =    554;  NoIA = 6;  NoOA = 1; NoOI = 2; break;
    case _SHUTTLE:   strcpy(nameDB, "shuttle12");
                   TS   =   58000;  NoIA = 9;  NoOA = 1; NoOI = 7; break;
    case _SAT_UA:    strcpy(nameDB, "sat-UA");
                   TS   =   323980;NoIA = 3;  NoOA = 1; NoOI = 10; break;  // NoOI=9 + SAMPLE
    case _SEMESTR:   strcpy(nameDB, "semestralka");
                   TS   =     17;  NoIA = 4;  NoOA = 1; NoOI = 3; break;
    case _TEST:      strcpy(nameDB, "test");
                   TS   =     10;  NoIA = 3;  NoOA = 1; NoOI = 3; break;
    case _POLAND:    strcpy(nameDB, "poland");
                   TS   =   1710;  NoIA =13;  NoOA = 1; NoOI = 20; break;
    case _IOSIF:     strcpy(nameDB, "iosif");
                   TS   =    313;  NoIA =21;  NoOA = 1; NoOI =  5; break;
    case _IOSIF_LENA:     strcpy(nameDB, "iosif-lena");
                   TS   =    12;  NoIA =4;  NoOA = 1; NoOI =  3; break;
    case _LENKA:          strcpy(nameDB, "_lenka");
                   TS   =    16;  NoIA =3;  NoOA = 1; NoOI =  4; break;

    case _LENKA_DECERNO:  strcpy(nameDB, "lenkadecerno");
                   TS   =    36;  NoIA =4;  NoOA = 1; NoOI =  4; break;
    case _PODOFILINI:  strcpy(nameDB, "podofilini");
                   TS   =    16;  NoIA =3;  NoOA = 1; NoOI =  3; break;
    case _OSTRAVA1:       strcpy(nameDB, "ostrava1");
                   TS   =  1116;  NoIA =11;  NoOA = 1; NoOI =  7; break;
    case _OSTRAVA10:      strcpy(nameDB, "ostrava1");
                   TS   =  1116;  NoIA =10;  NoOA = 1; NoOI =  7; break;
    case _OSTRAVA2BEZ:       strcpy(nameDB, "ostrava2bez");
                   TS   =  538;  NoIA =11;  NoOA = 1; NoOI =  7; break;



    case _SF1:            strcpy(nameDB, "sf1");
                   TS   =131072;  NoIA =17;  NoOA = 1; NoOI =  2; break;
    case _SF_NATVIG:      strcpy(nameDB, "Natvig");
                   TS   =   243;  NoIA = 5;  NoOA = 1; NoOI =  3; break;
    case _SF_XING:        strcpy(nameDB, "Xing");
                   TS   =   512;  NoIA = 5;  NoOA = 1; NoOI =  4; break;
    case _SF_KAPUR:       strcpy(nameDB, "Kapur");
                   TS   =   108;  NoIA = 4;  NoOA = 1; NoOI =  5; break;


     default: { printf("Uncorrect DataBase's numbers in main()\n"); getchar();}
  }
  NoA = NoIA + NoOA;
  R = (instance*) new instance [TS];
      if(!R) MyError("Bad allocation R in DataSets()");
  for(unsigned long k=0; k<TS; k++)
  {  R[k].A  = (float*) new float [NoA];
     if(!R[k].A) MyError("Bad allocation R[k].A in DataSets()");
  }
  nonNumericAttributes = newUnInt(NoA, 0,"nonNumericAttributes in DataSets()");
  nonNumericAttributes[NoIA] = NoOI;
  TotalSets                = TS;
  NumberOfAttributes       = NoA;
  NumberOfInputAttributes  = NoIA;
  NumberOfOutputAttributes = NoOA;
  NumberOfOutputIntervals  = NoOI;
} // ------------------        ~DataSets()   -------------------------------
DataSets:: ~DataSets()
{  for(unsigned long k=0; k<TotalSets; k++)
       delete[] R[k].A  ;
   delete[] R;
   delete[] nonNumericAttributes;
} // ------------------        ReadDataSets   -------------------------------
int DataSets::ReadDataSets(unsigned int numDB)
{ char FileNameDB[99];
  FILE *fp;
  strcpy(FileNameDB,PATHinCrisp); strcat(FileNameDB,nameDB); strcat(FileNameDB,".data");

  fp=fopen(FileNameDB, "r");
  if (fp == NULL) MyError("Error reading file from DataSets::ReadDataSets\n");
  switch(numDB)
  { case _ABALONE     : ReadCrispFileAbalone     (fp);  break;
    case _BALANCE     : ReadCrispFileBalance     (fp);  break;
    case _BLOOD		 : ReadCrispFileBlood       (fp);  break;
    case _BREAST      : ReadCrispFileBreast      (fp);  break;
    case _BUPA        : ReadCrispFileBupa        (fp);  break;
    case _CAR	       : ReadCrispFileCar		    (fp);  break;
    case _CMC         : ReadCrispFileCmc         (fp);  break;
    case _CRX         : ReadCrispFileCrx         (fp);  break;
    case _DIAGNOSIS   : ReadCrispFileDiagnosis   (fp);  break;
    case _ECOLI       : ReadCrispFileEcoli       (fp);  break;
    case _FOREST      : ReadCrispFileForestfires (fp);  break;
    case _GERMAN      : ReadCrispFileGerman      (fp);  break;
    case _GERMAN24    : ReadCrispFileGerman24    (fp);  break;
    case _GLASS       : ReadCrispFileGlass       (fp);  break;
//  bad    case _GOLF : ReadCrispFileGolf     (fp);  break;
    case _HABERMAN    : ReadCrispFileHaberman    (fp);  break;
    case _ILPD        : ReadCrispFileILPD        (fp);  break;
    case _IMAGE       : ReadCrispFileImage       (fp);  break;
    case _IONOSPHERE  : ReadCrispFileIonosphere  (fp);  break;
    case _IRIS        : ReadCrispFileIris        (fp);  break;
    case _LETTER      : ReadCrispFileLetter      (fp);  break;
    case _NURSERY     : ReadCrispFileNursery     (fp);  break;
    case _PAGEBLOCKS  : ReadCrispFilePageblocks  (fp);  break;
    case _PARKINSONS  : ReadCrispFileParkinsons  (fp);  break;
    case _PENDIGITS   : ReadCrispFilePendigits   (fp);  break;
    case _PIMA        : ReadCrispFilePima        (fp);  break;
    case _PLRX        : ReadCrispFilePlrx        (fp);  break;
    case _SEEDS       : ReadCrispFileSeeds       (fp);  break;
    case _SENSOR2     : ReadCrispFileSensor2     (fp);  break;
    case _SENSOR4     : ReadCrispFileSensor4     (fp);  break;
    case _SENSOR24    : ReadCrispFileSensor24    (fp);  break;
    case _TAE         : ReadCrispFileTae         (fp);  break;
    case _THYROID     : ReadCrispFileThyroid     (fp);  break;
    case _TIC		    : ReadCrispFileTic		    (fp);  break;
    case	_VENICLE     : ReadCrispFileVenicle     (fp);  break;
    case	_VERTEBRAL2  :
    case	_VERTEBRAL3  :ReadCrispFileVertebral    (fp);  break;
  	 case _VOWEL		 : ReadCrispFileVowel	    (fp);  break;
    case _WDBC        : ReadCrispFileWDBC        (fp);  break;
    case _WINE        : ReadCrispFileWine        (fp);  break;
    case	_WINERED     :
    case	_WINEWHITE   : ReadCrispFileWineQuality (fp);  break;
    case _WPBC        : ReadCrispFileWPBC        (fp);  break;
    case _YEAST       : ReadCrispFileYeast       (fp);  break;

    case _BANK        : ReadCrispFileBank        (fp); break;
 	 case _ConfJSI     : ReadCrispFileConfLongDemo(fp); break;
 	 case _FAULTS      : ReadCrispFileFaults      (fp); break;
//    case _MINIBOONE : ReadCrispFileMiniBooNE   (fp); break;

    case _SKIN        : ReadCrispFileSkin        (fp); break;
	 case _SONAR		 : ReadCrispFileSonar	    (fp); break;

    case _HEART		 : ReadCrispFileHeart	    (fp); break;
    case _KRKOPT		 : ReadCrispFileKrkopt	    (fp); break;
    case _MAGIC		 : ReadCrispFileMagic	    (fp); break;
    case _MONKS1		 :
    case _MONKS2		 :
    case _MONKS3		 : ReadCrispFileMonks	    (fp); break;
    case	_SHUTTLE     : ReadCrispFileShuttle     (fp); break;

    case _SAT_UA      : ReadCrispFileSatUA       (fp); break;
    case _SEMESTR     : ReadCrispFileSemestralka (fp); break;
    case _TEST        : ReadCrispFileTest        (fp); break;
    case _POLAND      : ReadCrispFilePoland      (fp); break;
    case _IOSIF       : ReadCrispFileIosif       (fp); break;
    case _IOSIF_LENA  : ReadCrispFileIosifLena   (fp); break;
    case _OSTRAVA1    : ReadCrispFileOstrava1    (fp); break;
    case _OSTRAVA10   : ReadCrispFileOstrava10   (fp); break;
    case _OSTRAVA2BEZ : ReadCrispFileOstrava2bez   (fp); break;

    case _LENKA       : ReadCrispFileLenka       (fp); break;
   case _LENKA_DECERNO: ReadCrispFileLenkaDecerno(fp); break;
    case _PODOFILINI  : ReadCrispFilePodofilini  (fp); break;
    case _SF1         : ReadCrispFileSF1         (fp); break;
    case _SF_NATVIG   : ReadCrispFileSFNatvig    (fp); break;
    case _SF_XING     : ReadCrispFileSFXing      (fp); break;
    case _SF_KAPUR    : ReadCrispFileSFKapur     (fp); break;
  };
  fclose(fp);
  return 1;
}  // --------------------------   WriteCrispFile    --------------------------
int DataSets::WriteCrispFile(void)
{ char FileName[99];
  FILE *fp;
  strcpy(FileName,PATHoutCrisp); strcat(FileName,nameDB); strcat(FileName,".crisp");
  fp = fopen(FileName, "w");
  if (fp == NULL) {printf("Error FileName in WriteCrispFile()"); getchar(); return 0;};

  for (unsigned int i=0; i<NumberOfAttributes; i++)
      fprintf(fp, "%d ", nonNumericAttributes[i]);
  fprintf(fp, "\n");

  for(unsigned long k=0; k<TotalSets; k++)
  { fprintf(fp, "(k=%ld)  ", k);
    for (unsigned int i=0; i<NumberOfAttributes; i++)
            fprintf(fp, "%f ", R[k].A[i]);
    fprintf(fp, "\n");
  }
  fprintf(fp, "End of Crisp File");
  fclose(fp);
  return 1;
}
// --------------------------   ReadCrispFile  - SF-1  --------------------------
int DataSets::ReadCrispFileSF1(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
  {  fscanf(fp,"%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
       &R[k].A[ 0], &R[k].A[ 1], &R[k].A[ 2], &R[k].A[ 3], &R[k].A[ 4],
       &R[k].A[ 5], &R[k].A[ 6], &R[k].A[ 7], &R[k].A[ 8], &R[k].A[ 9],
       &R[k].A[10], &R[k].A[11], &R[k].A[12], &R[k].A[13], &R[k].A[14],
       &R[k].A[15], &R[k].A[16], &R[k].A[17]);
  }
  nonNumericAttributes[0]= 2;   nonNumericAttributes[10]= 2;
  nonNumericAttributes[1]= 2;   nonNumericAttributes[11]= 2;
  nonNumericAttributes[2]= 2;   nonNumericAttributes[12]= 2;
  nonNumericAttributes[3]= 2;   nonNumericAttributes[13]= 2;
  nonNumericAttributes[4]= 2;   nonNumericAttributes[14]= 2;
  nonNumericAttributes[5]= 2;   nonNumericAttributes[15]= 2;
  nonNumericAttributes[6]= 2;   nonNumericAttributes[16]= 2;
  nonNumericAttributes[7]= 2;   nonNumericAttributes[17]= 2;
  nonNumericAttributes[8]= 2;
  nonNumericAttributes[9]= 2;
  return 1;
}
// -------------------------------------------------
int DataSets::ReadCrispFilePodofilini(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
  {  fscanf(fp,"%f, %f, %f, %f",  &R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3]);
  }
  nonNumericAttributes[0]= 2;
  nonNumericAttributes[1]= 2;
  nonNumericAttributes[2]= 4;
  return 1;
}
// --------------------------   ReadCrispFile  - SF_Natvig  ------------------------
int DataSets::ReadCrispFileSFNatvig(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
  {  fscanf(fp,"%f %f %f %f %f %f",
       &R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3], &R[k].A[4], &R[k].A[5]);
       for (unsigned int i=0; i<6; i++)
       { if (R[k].A[i] ==  2.0) R[k].A[i] = 1.0;
         if (R[k].A[i] ==  4.0) R[k].A[i] = 2.0;
       }
  }
  nonNumericAttributes[0]= 3;
  nonNumericAttributes[1]= 3;
  nonNumericAttributes[2]= 3;
  nonNumericAttributes[3]= 3;
  nonNumericAttributes[4]= 3;
  nonNumericAttributes[5]= 3;
  return 1;
}
// --------------------------   ReadCrispFile  - SF_Xing  ------------------------
int DataSets::ReadCrispFileSFXing(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
    fscanf(fp,"%f %f %f %f %f %f",
       &R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3], &R[k].A[4], &R[k].A[5]);

  nonNumericAttributes[0]= 4;
  nonNumericAttributes[1]= 4;
  nonNumericAttributes[2]= 4;
  nonNumericAttributes[3]= 4;
  nonNumericAttributes[4]= 2;
  nonNumericAttributes[5]= 4;
  return 1;
}
// --------------------------   ReadCrispFile  - SF_Kapur  ------------------------
int DataSets::ReadCrispFileSFKapur(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
    fscanf(fp,"%f %f %f %f %f",&R[k].A[0],&R[k].A[1],&R[k].A[2],&R[k].A[3],&R[k].A[4]);

  nonNumericAttributes[0]= 2;
  nonNumericAttributes[1]= 2;
  nonNumericAttributes[2]= 3;
  nonNumericAttributes[3]= 3;
  nonNumericAttributes[4]= 5;
  return 1;
}
// --------------------------   ReadCrispFile  - Ostrava1  --------------------------
int DataSets::ReadCrispFileOstrava1(FILE* fp)
{ float no;
  for (unsigned long k=0; k<TotalSets; k++)
  {  fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", &no,
       &R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3], &R[k].A[4],
       &R[k].A[5], &R[k].A[6], &R[k].A[7], &R[k].A[8], &R[k].A[9], &R[k].A[10], &R[k].A[11]);
  }
  nonNumericAttributes[0]= 2; // 0 - "s"   and 1 - "a"
  nonNumericAttributes[1]= 2; // 0 - "ne"  and 1 - "ano"  (Alergie)
  nonNumericAttributes[2]= 3; // 0, 1, 2 - "X"  (OA-ASTMA)
  nonNumericAttributes[3]= 3; //     ...        (OA-RYMA)
  nonNumericAttributes[4]= 3; //     ...        (OA-EKZEM)
  nonNumericAttributes[5]= 3; //     ...        (OA-OSTATNI)
  nonNumericAttributes[6]= 3; //     ...        (RA-ASTMA)
  nonNumericAttributes[7]= 3; //     ...        (RA-RYMA)
  nonNumericAttributes[8]= 3; //     ...        (RA-EKZEM)
  nonNumericAttributes[9]= 3; //     ...        (RA-OSTATNI)
  return 1;
}
int DataSets::ReadCrispFileOstrava10(FILE* fp)
{ float no;
  for (unsigned long k=0; k<TotalSets; k++)
  {  fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", &no,
       &R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3], &R[k].A[4],
       &R[k].A[5], &R[k].A[6], &R[k].A[7], &R[k].A[8], &R[k].A[9], &no, &R[k].A[10]);
  }
  nonNumericAttributes[0]= 2; // 0 - "s"   and 1 - "a"
  nonNumericAttributes[1]= 2; // 0 - "ne"  and 1 - "ano"  (Alergie)
  nonNumericAttributes[2]= 3; // 0, 1, 2 - "X"  (OA-ASTMA)
  nonNumericAttributes[3]= 3; //     ...        (OA-RYMA)
  nonNumericAttributes[4]= 3; //     ...        (OA-EKZEM)
  nonNumericAttributes[5]= 3; //     ...        (OA-OSTATNI)
  nonNumericAttributes[6]= 3; //     ...        (RA-ASTMA)
  nonNumericAttributes[7]= 3; //     ...        (RA-RYMA)
  nonNumericAttributes[8]= 3; //     ...        (RA-EKZEM)
  nonNumericAttributes[9]= 3; //     ...        (RA-OSTATNI)
  return 1;
}

int DataSets::ReadCrispFileOstrava2bez(FILE* fp)
{ float no;
  for (unsigned long k=0; k<TotalSets; k++)
  {  fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", &no,
       &R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3], &R[k].A[4],
       &R[k].A[5], &R[k].A[6], &R[k].A[7], &R[k].A[8], &R[k].A[9], &R[k].A[10], &R[k].A[11]);
  }
  nonNumericAttributes[0]= 2; // 0 - "s"   and 1 - "a"
  nonNumericAttributes[1]= 2; // 0 - "ne"  and 1 - "ano"  (Alergie)
  nonNumericAttributes[2]= 2; // 0, 1, 2 - "X"  (OA-ASTMA)
  nonNumericAttributes[3]= 2; //     ...        (OA-RYMA)
  nonNumericAttributes[4]= 2; //     ...        (OA-EKZEM)
  nonNumericAttributes[5]= 2; //     ...        (OA-OSTATNI)
  nonNumericAttributes[6]= 2; //     ...        (RA-ASTMA)
  nonNumericAttributes[7]= 2; //     ...        (RA-RYMA)
  nonNumericAttributes[8]= 2; //     ...        (RA-EKZEM)
  nonNumericAttributes[9]= 2; //     ...        (RA-OSTATNI)
  return 1;
}
// --------------------------   ReadCrispFile  - Nursery  --------------------------
int DataSets::ReadCrispFileNursery(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f", &R[k].A[0], &R[k].A[1], &R[k].A[2],
       &R[k].A[3], &R[k].A[4], &R[k].A[5], &R[k].A[6], &R[k].A[7], &R[k].A[8]);
    R[k].A[3]--;
  }
  nonNumericAttributes[0]= 3; // parents  - usual, pretentious, great_pret
  nonNumericAttributes[1]= 5; // has_nurs - proper,less_proper,improper,critical,very_crit
  nonNumericAttributes[2]= 4; // form     - complete, completed, incomplete, foster
  nonNumericAttributes[3]= 4; // children - 1, 2, 3, more
  nonNumericAttributes[4]= 3; // housing  - convenient, less_conv, critical
  nonNumericAttributes[5]= 2; // finance  - convenient, inconv
  nonNumericAttributes[6]= 3; // social   - non-prob, slightly_prob, problematic
  nonNumericAttributes[7]= 3; // health   - recommended, priority, not_recom
  return 1;
}
// --------------------------   ReadCrispFile  - POLAND   -----------------------
int DataSets::ReadCrispFilePoland(FILE* fp)
{ char Opis[20];
  for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %s",
       &R[k].A[ 0], &R[k].A[ 1], &R[k].A[ 2], &R[k].A[ 3], &R[k].A[ 4],
       &R[k].A[ 5], &R[k].A[ 6], &R[k].A[ 7], &R[k].A[ 8], &R[k].A[ 9],
       &R[k].A[10], &R[k].A[11], &R[k].A[12], Opis);

    if (!strcmp(Opis,"NORM-W")   ) R[k].A[NumberOfInputAttributes] = 0.0;
    if (!strcmp(Opis,"NEUR-W")   ) R[k].A[NumberOfInputAttributes] = 1.0;
    if (!strcmp(Opis,"PSYCH-W")  ) R[k].A[NumberOfInputAttributes] = 2.0;
    if (!strcmp(Opis,"ORG-W")    ) R[k].A[NumberOfInputAttributes] = 3.0;
    if (!strcmp(Opis,"SCHIZ-W")  ) R[k].A[NumberOfInputAttributes] = 4.0;
    if (!strcmp(Opis,"DEL.S-W")  ) R[k].A[NumberOfInputAttributes] = 5.0;
    if (!strcmp(Opis,"RE.PSY-W") ) R[k].A[NumberOfInputAttributes] = 6.0;
    if (!strcmp(Opis,"PARAN-W")  ) R[k].A[NumberOfInputAttributes] = 7.0;
    if (!strcmp(Opis,"MAN.ST-W") ) R[k].A[NumberOfInputAttributes] = 8.0;
    if (!strcmp(Opis,"CRIM-W")   ) R[k].A[NumberOfInputAttributes] = 9.0;
    if (!strcmp(Opis,"ALCOH-W")  ) R[k].A[NumberOfInputAttributes] =10.0;
    if (!strcmp(Opis,"DRUG-W")   ) R[k].A[NumberOfInputAttributes] =11.0;
    if (!strcmp(Opis,"SIMU-W")   ) R[k].A[NumberOfInputAttributes] =12.0;
    if (!strcmp(Opis,"DISSIMU-W")) R[k].A[NumberOfInputAttributes] =13.0;
    if (!strcmp(Opis,"DEV1-W")   ) R[k].A[NumberOfInputAttributes] =14.0;
    if (!strcmp(Opis,"DEV2-W")   ) R[k].A[NumberOfInputAttributes] =15.0;
    if (!strcmp(Opis,"DEV3-W")   ) R[k].A[NumberOfInputAttributes] =16.0;
    if (!strcmp(Opis,"DEV4-W")   ) R[k].A[NumberOfInputAttributes] =17.0;
    if (!strcmp(Opis,"DEV5-W")   ) R[k].A[NumberOfInputAttributes] =18.0;
    if (!strcmp(Opis,"DEV6-W")   ) R[k].A[NumberOfInputAttributes] =19.0;
//  printf("%s R[%d].A[%f]=%f\n", Opis,k,NumberOfInputAttributes,R[k].A[NumberOfInputAttributes]);
  }
  return 1;
}// --------------------------   ReadCrispFile  - Iosif  --------------------------
int DataSets::ReadCrispFileIosif(FILE* fp)
{ int Number;
  for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
       &Number, &R[k].A[ 0], &R[k].A[ 1], &R[k].A[ 2], &R[k].A[ 3], &R[k].A[ 4],
                &R[k].A[ 5], &R[k].A[ 6], &R[k].A[ 7], &R[k].A[ 8], &R[k].A[ 9],
                &R[k].A[10], &R[k].A[11], &R[k].A[12], &R[k].A[13], &R[k].A[14],
                &R[k].A[15], &R[k].A[16], &R[k].A[17], &R[k].A[18], &R[k].A[19],
                &R[k].A[20], &R[k].A[21]);
    R[k].A[ 0]--; R[k].A[ 1]--; R[k].A[ 2]--; R[k].A[ 3]--; R[k].A[ 4]--;
    R[k].A[ 5]--; R[k].A[ 6]--; R[k].A[ 7]--; R[k].A[ 8]--; R[k].A[ 9]--;
    R[k].A[10]--; R[k].A[11]--; R[k].A[12]--; R[k].A[13]--; R[k].A[14]--;
    R[k].A[15]--; R[k].A[16]--; R[k].A[17]--; R[k].A[18]--; R[k].A[19]--; R[k].A[20]--; R[k].A[21]--;
  }
  nonNumericAttributes[ 0]= 2; // sex
  nonNumericAttributes[ 1]= 8; //
  nonNumericAttributes[ 2]= 8; //
  nonNumericAttributes[ 3]= 3; //
  nonNumericAttributes[ 4]= 5; //
  nonNumericAttributes[ 5]= 5; //
  nonNumericAttributes[ 6]= 3; //
  nonNumericAttributes[ 7]= 3; //
  nonNumericAttributes[ 8]= 5; //
  nonNumericAttributes[ 9]= 5; //
  nonNumericAttributes[10]= 5; //
  nonNumericAttributes[11]= 4; //
  nonNumericAttributes[12]= 4; //
  nonNumericAttributes[13]= 4; //
  nonNumericAttributes[14]= 4; //
  nonNumericAttributes[15]= 3; //
  nonNumericAttributes[16]= 4; //
  nonNumericAttributes[17]= 2; //
  nonNumericAttributes[18]= 5; //
  nonNumericAttributes[19]= 5; //
  nonNumericAttributes[20]= 5; //
  nonNumericAttributes[21]= 5; //
  return 1;
}
// --------------------------   ReadCrispFile  - Lenka  --------------------------
int DataSets::ReadCrispFileLenka(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
    fscanf(fp,"%f, %f, %f, %f", &R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3]);
  return 1;
}// --------------------------   ReadCrispFile  - Lenka-Decerno  --------------------------
int DataSets::ReadCrispFileLenkaDecerno(FILE* fp)
{ float no;
  for (unsigned long k=0; k<TotalSets; k++)
    fscanf(fp,"%f,%f,%f,%f, %f, %f", &R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3], &R[k].A[4], &no);
  nonNumericAttributes[0]= 2; // device
  nonNumericAttributes[1]= 2; // anastez
  nonNumericAttributes[2]= 3; // surgent
  nonNumericAttributes[3]= 3; // nurse
  return 1;
}
// --------------------------   ReadCrispFile  - Iosif-Lena  --------------------------
int DataSets::ReadCrispFileIosifLena(FILE* fp)
{ int Number;
  for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%f,%f,%f,%f,%f", &R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3], &R[k].A[4]);
  }
  nonNumericAttributes[ 0]= 2; // sex
  nonNumericAttributes[ 1]= 6; //
  nonNumericAttributes[ 2]= 6; //
  nonNumericAttributes[ 3]= 3; //
  return 1;
}
// --------------------------   ReadCrispFile  - LETTER   -----------------------
int DataSets::ReadCrispFileLetter(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", &R[k].A[16],
       &R[k].A[ 0], &R[k].A[ 1], &R[k].A[ 2], &R[k].A[ 3], &R[k].A[ 4],
       &R[k].A[ 5], &R[k].A[ 6], &R[k].A[ 7], &R[k].A[ 8], &R[k].A[ 9],
       &R[k].A[10], &R[k].A[11], &R[k].A[12], &R[k].A[13], &R[k].A[14],
       &R[k].A[15]);
  }
  return 1;
}
// --------------------------   ReadCrispFile  - Pageblocks  -----------------------
int DataSets::ReadCrispFilePageblocks(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
       &R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3], &R[k].A[4],
       &R[k].A[5], &R[k].A[6], &R[k].A[7], &R[k].A[8], &R[k].A[9], &R[k].A[10]);
    R[k].A[10]--;
  }
  return 1;
}
// --------------------------   ReadCrispFile  - PENDIGITS     -----------------------
int DataSets::ReadCrispFilePendigits(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
       &R[k].A[ 0], &R[k].A[ 1], &R[k].A[ 2], &R[k].A[ 3], &R[k].A[ 4],
       &R[k].A[ 5], &R[k].A[ 6], &R[k].A[ 7], &R[k].A[ 8], &R[k].A[ 9],
       &R[k].A[10], &R[k].A[11], &R[k].A[12], &R[k].A[13], &R[k].A[14], &R[k].A[15],&R[k].A[16]);
  }
  return 1;
}
// --------------------------   ReadCrispFile  - PLRX  -----------------------
int DataSets::ReadCrispFilePlrx(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%e %e %e %e %e %e %e %e %e %e %e %e %e", &R[k].A[0],
       &R[k].A[1], &R[k].A[2], &R[k].A[3], &R[k].A[4],  &R[k].A[5],
       &R[k].A[6], &R[k].A[7], &R[k].A[8], &R[k].A[9], &R[k].A[10], &R[k].A[11], &R[k].A[12]);
    R[k].A[12]--;
  }
  return 1;
}
// --------------------------   ReadCrispFile  - Seeds   -----------------------
int DataSets::ReadCrispFileSeeds(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f",   &R[k].A[0], &R[k].A[1], &R[k].A[2],
       &R[k].A[3], &R[k].A[4], &R[k].A[5], &R[k].A[6], &R[k].A[7]);
    R[k].A[7]--;
  }
  return 1;
}
// --------------------------   ReadCrispFile  - SENSOR-2   -----------------------
int DataSets::ReadCrispFileSensor2(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
   fscanf(fp,"%f,%f,%f", &R[k].A[0], &R[k].A[1], &R[k].A[2]);
  return 1;
}
int DataSets::ReadCrispFileSensor4(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
   fscanf(fp,"%f,%f,%f,%f,%f", &R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3], &R[k].A[4]);
  return 1;
}
int DataSets::ReadCrispFileSensor24(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
   fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
       &R[k].A[ 0], &R[k].A[ 1], &R[k].A[ 2], &R[k].A[ 3], &R[k].A[ 4],
       &R[k].A[ 5], &R[k].A[ 6], &R[k].A[ 7], &R[k].A[ 8], &R[k].A[ 9],
       &R[k].A[10], &R[k].A[11], &R[k].A[12], &R[k].A[13], &R[k].A[14],
       &R[k].A[15], &R[k].A[16], &R[k].A[17], &R[k].A[18], &R[k].A[19],
       &R[k].A[20], &R[k].A[21], &R[k].A[22], &R[k].A[23], &R[k].A[24]);
  return 1;
}
// --------------------------   ReadCrispFile  - THYROID    -----------------------
int DataSets::ReadCrispFileThyroid(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%f,%f,%f,%f,%f,%f", &R[k].A[5], &R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3], &R[k].A[4]);
    R[k].A[5]--;
  }
  return 1;
}
// --------------------------   ReadCrispFile  - VERTEBRAL  -----------------------
int DataSets::ReadCrispFileVertebral(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
   fscanf(fp,"%f,%f,%f,%f,%f,%f,%f",
       &R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3], &R[k].A[4], &R[k].A[5], &R[k].A[6]);
  return 1;
}
// --------------------------   ReadCrispFile  - MONKS  --------------------------
int DataSets::ReadCrispFileMonks(FILE* fp)
{ char opis[15];
  for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%s",
      &R[k].A[6], &R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3], &R[k].A[4], &R[k].A[5], opis);
    R[k].A[0]--;    R[k].A[1]--;    R[k].A[2]--;    R[k].A[3]--;    R[k].A[4]--;    R[k].A[5]--;
  }
  nonNumericAttributes[0]= 3;
  nonNumericAttributes[1]= 3;
  nonNumericAttributes[2]= 2;
  nonNumericAttributes[3]= 3;
  nonNumericAttributes[4]= 4;
  nonNumericAttributes[5]= 2;
  return 1;
}
// --------------------------   ReadCrispFile  - SUTTLE  --------------------------
int DataSets::ReadCrispFileShuttle(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
  {  fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
      &R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3], &R[k].A[4],
      &R[k].A[5], &R[k].A[6], &R[k].A[7], &R[k].A[8], &R[k].A[9]);
     R[k].A[9]--;
  }
  return 1;
}

// --------------------------   ReadCrispFile  - BANK  --------------------------
int DataSets::ReadCrispFileBank(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
       &R[k].A[ 0], &R[k].A[ 1], &R[k].A[ 2], &R[k].A[ 3], &R[k].A[ 4],
       &R[k].A[ 5], &R[k].A[ 6], &R[k].A[ 7], &R[k].A[ 8], &R[k].A[ 9],
       &R[k].A[10], &R[k].A[11], &R[k].A[12], &R[k].A[13], &R[k].A[14], &R[k].A[15], &R[k].A[16]);
    if (R[k].A[13] == -1) R[k].A[13]=0;
  }

  nonNumericAttributes[ 1]=12;  // A[2] - type of job
  nonNumericAttributes[ 2]= 3;  // A[3] - marital status  ("married","divorced","single")
  nonNumericAttributes[ 3]= 4;  // A[4] - education       ("unknown","secondary","primary","tertiary")
  nonNumericAttributes[ 4]= 2;  // A[5] - has credit in default (Y/N)?
  nonNumericAttributes[ 6]= 2;  // A[7] - has housing loan (Y/N)?
  nonNumericAttributes[ 7]= 2;  // A[8] - has housing  loan (Y/N)?
  nonNumericAttributes[ 8]= 3;  // A[9] - contact communication type ("unknown","telephone","cellular")
  nonNumericAttributes[10]=12;  // A[11] - month of year (0...11)
  nonNumericAttributes[15]= 4;  // A[16] - outcome of the previous campaign ("unknown","other","failure","success")
  return 1;
}
 // --------------------------   ReadCrispFile - Abalone    --------------------------
int DataSets::ReadCrispFileAbalone(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f", &R[k].A[0],  &R[k].A[1], &R[k].A[2],
          &R[k].A[3], &R[k].A[4], &R[k].A[5], &R[k].A[6],  &R[k].A[7], &R[k].A[8]);
    R[k].A[8]--;
  }
  nonNumericAttributes[0] = 3;   // A[2] - Sex:   M- 0, F- 1, I (infant) - 2
  return 1;
}   // -------------------------    ReadCrispFile  - German ---------------------------
int DataSets::ReadCrispFileGerman24(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
          &R[k].A[ 0], &R[k].A[ 1], &R[k].A[ 2], &R[k].A[ 3], &R[k].A[ 4],
          &R[k].A[ 5], &R[k].A[ 6], &R[k].A[ 7], &R[k].A[ 8], &R[k].A[ 9],
          &R[k].A[10], &R[k].A[11], &R[k].A[12], &R[k].A[13], &R[k].A[14],
          &R[k].A[15], &R[k].A[16], &R[k].A[17], &R[k].A[18], &R[k].A[19],
          &R[k].A[20], &R[k].A[21], &R[k].A[22], &R[k].A[23], &R[k].A[24]);
    R[k].A[24]--;
  }
  return 1;
} // -------------------------    ReadCrispFile  - German ---------------------------
int DataSets::ReadCrispFileGerman(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
          &R[k].A[ 0], &R[k].A[ 1], &R[k].A[ 2], &R[k].A[ 3], &R[k].A[ 4],
          &R[k].A[ 5], &R[k].A[ 6], &R[k].A[ 7], &R[k].A[ 8], &R[k].A[ 9],
          &R[k].A[10], &R[k].A[11], &R[k].A[12], &R[k].A[13], &R[k].A[14],
          &R[k].A[15], &R[k].A[16], &R[k].A[17], &R[k].A[18], &R[k].A[19], &R[k].A[20]);
    R[k].A[20]--;
  }
  nonNumericAttributes[ 0]= 4; // Status of existing checking account (A11,A12,A13,A14)
  nonNumericAttributes[ 2]= 5; // Credit history (A30,A31,A32,A33,A34)
  nonNumericAttributes[ 3]=10; // Purpose    (A40,A41,A42,A43,A44,A45,A46,A48,A49,A410) A47=Non
  nonNumericAttributes[ 5]= 5; // Savings account/bonds    (A61,A62,A63,A64,A65)
  nonNumericAttributes[ 6]= 5; // Present employment since (A71,A72,A73,A74,A75)
  nonNumericAttributes[ 8]= 4; // Personal status and sex  (A91,A92,A93,A94)   A95=Non
  nonNumericAttributes[ 9]= 3; // Other debtors / guarantors (A101,A102,A103)
  nonNumericAttributes[11]= 4; // Property  (A121,A122, A123, A124)
  nonNumericAttributes[13]= 3; // Other installment plans    (A141,A142,A143)
  nonNumericAttributes[14]= 3; // Housing (A151,A152,A153)
  nonNumericAttributes[16]= 4; // Job     (A171,A172,A173,A174)
  nonNumericAttributes[18]= 2; // Telephone    (A191,A192)
  nonNumericAttributes[19]= 2; // foreign worker  (A201,A202)
  return 1;
} // -------------------------    ReadCrispFile  - GOLF ---------------------------
int DataSets::ReadCrispFileGolf(FILE* fp)
{
//    atribut 0 (Outlook)  0 = sunny,  1 = overcast,  2 = rain
//            1 (Temperature)  numericky
//            2 (Humidity)  numericky
//            3 (Windy)  0 = false     1 = true
//   class atribut 0 = Play (positive) / Don't Play (negative))    1 = Play

  for (unsigned long k=0; k<TotalSets; k++)
    fscanf(fp,"%f,%f,%f,%f,%f",&R[k].A[0],&R[k].A[1],&R[k].A[2],&R[k].A[3],&R[k].A[4]);
  nonNumericAttributes[0]=3;
  nonNumericAttributes[3]=2;
  return 1;
}
  // -------------------------    ReadCrispFile  - ConfLongDemo_JSI ---------------------------
int DataSets::ReadCrispFileConfLongDemo(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
 { fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f", &R[k].A[0], &R[k].A[1],
                &R[k].A[2], &R[k].A[3], &R[k].A[4], &R[k].A[5], &R[k].A[6], &R[k].A[7]);
 }
  nonNumericAttributes[0]=25;
  nonNumericAttributes[1]=4;
  return 1;
}// -------------------------    ReadCrispFile  - Faults   ---------------------------
int DataSets::ReadCrispFileFaults(FILE* fp)
{ unsigned int a[7];

 for (unsigned long k=0; k<TotalSets; k++)
 { fscanf(fp,"%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %d %d %d %d %d %d %d",
       &R[k].A[ 0],&R[k].A[ 1],&R[k].A[ 2],&R[k].A[ 3],&R[k].A[ 4],
       &R[k].A[ 5],&R[k].A[ 6],&R[k].A[ 7],&R[k].A[ 8],&R[k].A[ 9],
       &R[k].A[10],&R[k].A[11],&R[k].A[12],&R[k].A[13],&R[k].A[14],
       &R[k].A[15],&R[k].A[16],&R[k].A[17],&R[k].A[18],&R[k].A[19],
       &R[k].A[20],&R[k].A[21],&R[k].A[22],&R[k].A[23],&R[k].A[24],
       &R[k].A[25],&R[k].A[26],&a[0], &a[1], &a[2], &a[3], &a[4], &a[5], &a[6]);

   for (unsigned int jb=0; jb<NumberOfOutputIntervals; jb++)
      if (a[jb] == 1) R[k].A[27] = jb;
 }
 return 1;
} // -------------------------    ReadCrispFile  - MiniBooNE   ---------------------------
int DataSets::ReadCrispFileMiniBooNE(FILE* fp)
{ unsigned long num0, num1;
  fscanf(fp,"%f,%f", num0, num1);

  for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f",
       &R[k].A[ 0],&R[k].A[ 1],&R[k].A[ 2],&R[k].A[ 3],&R[k].A[ 4],
       &R[k].A[ 5],&R[k].A[ 6],&R[k].A[ 7],&R[k].A[ 8],&R[k].A[ 9],
       &R[k].A[10],&R[k].A[11],&R[k].A[12],&R[k].A[13],&R[k].A[14],
       &R[k].A[15],&R[k].A[16],&R[k].A[17],&R[k].A[18],&R[k].A[19],
       &R[k].A[20],&R[k].A[21],&R[k].A[22],&R[k].A[23],&R[k].A[24],
       &R[k].A[25],&R[k].A[26],&R[k].A[27],&R[k].A[28],&R[k].A[29],
       &R[k].A[30],&R[k].A[31],&R[k].A[32],&R[k].A[33],&R[k].A[34],
       &R[k].A[35],&R[k].A[36],&R[k].A[37],&R[k].A[38],&R[k].A[39],
       &R[k].A[40],&R[k].A[41],&R[k].A[42],&R[k].A[43],&R[k].A[44],
       &R[k].A[45],&R[k].A[46],&R[k].A[47],&R[k].A[48],&R[k].A[49]);

    if (k < num0) R[k].A[50] = 0.0;
    else          R[k].A[50] = 1.0;
 }
 return 1;
} // -------------------------    ReadCrispFile  - Sat-UA   ---------------------------
int DataSets::ReadCrispFileSatUA(FILE* fp)
{ char Opis[20];
  for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%f %f %f %s", &R[k].A[0], &R[k].A[1], &R[k].A[2], Opis);
    if (!strcmp(Opis,"ARABLE"  )) R[k].A[NumberOfInputAttributes]=0.0;
    if (!strcmp(Opis,"BARREN"  )) R[k].A[NumberOfInputAttributes]=1.0;
    if (!strcmp(Opis,"CONCRETE")) R[k].A[NumberOfInputAttributes]=2.0;
    if (!strcmp(Opis,"CROP"    )) R[k].A[NumberOfInputAttributes]=3.0;
    if (!strcmp(Opis,"GRASS"   )) R[k].A[NumberOfInputAttributes]=4.0;
    if (!strcmp(Opis,"LAWN"    )) R[k].A[NumberOfInputAttributes]=5.0;
    if (!strcmp(Opis,"SAND"    )) R[k].A[NumberOfInputAttributes]=6.0;
    if (!strcmp(Opis,"SHALLOW" )) R[k].A[NumberOfInputAttributes]=7.0;
    if (!strcmp(Opis,"WATER"   )) R[k].A[NumberOfInputAttributes]=8.0;
    if (!strcmp(Opis,"SAMPLE"  )) R[k].A[NumberOfInputAttributes]=9.0;
  }
  return 1;
}  // -------------------------    Initial Error   ---------------------------
float DataSets::InitialError(unsigned int numDB)
{ unsigned long* classNoOI, maxClass;
  unsigned int jb;

  classNoOI = newUnLong(NumberOfOutputIntervals, 0l, " classNoOI from InitialErrorDS");
  for (unsigned long k=0; k<TotalSets; k++)
  { jb = R[k].A[NumberOfInputAttributes];
    classNoOI[jb]++;
  }
  maxClass = classNoOI[0];
  for (jb=0; jb<NumberOfOutputIntervals; jb++)
  { printf("classNoOI[jb=%d]=%d\n", jb, classNoOI[jb]) ;
    if( classNoOI[jb] > maxClass)  maxClass = classNoOI[jb];
  }
  return(1-(float)maxClass*1.0f/TotalSets);
}









//------------------------------------------------------------------------------
// USED DATABASE
//------------------------------------------------------------------------------

// --------------------------   ReadCrispFile - Balance 1000  ------------------
int DataSets::ReadCrispFileBalance(FILE* fp)
{ char Opis[3];
  int a0, a1, a2, a3;
  for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%s %d %d %d %d", Opis, &a0, &a1, &a2, &a3);
    if (!strcmp(Opis, "L"))  R[k].A[NumberOfInputAttributes]=0.0;
    if (!strcmp(Opis, "B"))  R[k].A[NumberOfInputAttributes]=1.0;
    if (!strcmp(Opis, "R"))  R[k].A[NumberOfInputAttributes]=2.0;
    R[k].A[0]=a0-1;   R[k].A[1]=a1-1;   R[k].A[2]=a2-1;    R[k].A[3]=a3-1;
  }
  return 1;
} // -------------------------  ReadCrispFile  - Blood  1000   -----------------
int	DataSets::ReadCrispFileBlood(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
    fscanf(fp,"%f,%f,%f,%f,%f",&R[k].A[0],&R[k].A[1],&R[k].A[2],&R[k].A[3],&R[k].A[4]);
  return 1;
} // -------------------------  ReadCrispFile  - BREAST 1000 -------------------
int DataSets::ReadCrispFileBreast(FILE* fp)
{ float hlm;
  for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", &hlm, &R[k].A[9],
                 &R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3], &R[k].A[4],
                 &R[k].A[5], &R[k].A[6], &R[k].A[7], &R[k].A[8]);
  }
  return 1;
} // -------------------------  ReadCrispFile - BUPA 1000  ---------------------
int DataSets::ReadCrispFileBupa(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%f,%f,%f,%f,%f,%f,%f",
      &R[k].A[0],&R[k].A[1],&R[k].A[2],&R[k].A[3],&R[k].A[4],&R[k].A[5],&R[k].A[6]);
    --R[k].A[6];
  }
  return 1;
} // -------------------------  ReadCrispFile - CAR 1000 -----------------------
int	DataSets::ReadCrispFileCar(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
    fscanf(fp,"%f,%f,%f,%f,%f,%f,%f",
      &R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3], &R[k].A[4],&R[k].A[5],&R[k].A[6]);
  nonNumericAttributes[0]=4;  //  buying  [0]:  vhigh = 0, high = 1, med = 2, low = 3.
  nonNumericAttributes[1]=4;  //  maint   [1]:  vhigh = 0, high = 1, med = 2, low = 3.
  nonNumericAttributes[2]=4;  //  doors   [2]:  2 -> 0, 3 -> 1, 4 -> 2, 5 and more -> 3.
  nonNumericAttributes[3]=3;  //  persons [3]:	2 -> 0, 4 -> 1, more -> 2.
  nonNumericAttributes[4]=3;  //  lug_boot[4]:	small = 0, medium = 1, bigh = 2.
  nonNumericAttributes[5]=3;  //  safety	[5]:  low   = 0, medium = 1, high = 2.
                              //  class      :  unacc = 0, acc = 2, good = 3, vgood = 1.
  return 1;
} // --------------------------   ReadCrispFile - CMC 1000 ---------------------
int DataSets::ReadCrispFileCmc(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",&R[k].A[0],&R[k].A[1],&R[k].A[2],
        &R[k].A[3], &R[k].A[4],  &R[k].A[5],  &R[k].A[6],&R[k].A[7],&R[k].A[8],&R[k].A[9]);
      --R[k].A[1]; --R[k].A[2]; --R[k].A[6]; --R[k].A[7];--R[k].A[9];
  }
  nonNumericAttributes[1]=4;
  nonNumericAttributes[2]=4;
  nonNumericAttributes[4]=2;
  nonNumericAttributes[5]=2;
  nonNumericAttributes[6]=4;
  nonNumericAttributes[7]=4;
  nonNumericAttributes[8]=2;
  return 1;
} // -------------------------    ReadCrispFile  - CRX -------------------------
int DataSets::ReadCrispFileCrx(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
    fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
     &R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3], &R[k].A[4],&R[k].A[5],
     &R[k].A[6], &R[k].A[7], &R[k].A[8], &R[k].A[9], &R[k].A[10],
     &R[k].A[11],&R[k].A[12],&R[k].A[13],&R[k].A[14],&R[k].A[15]);
  nonNumericAttributes[0]= 2; // A1:  b = 0, a = 1.
  nonNumericAttributes[3]= 3; // A4:  u = 0, y = 1, l = 2, t= 3.
  nonNumericAttributes[4]= 3; // A5:  g = 0, p = 1 , gg = 2.
  nonNumericAttributes[5]=14; // A6:  c=0,d=1,cc=2,i=3,j=4,k=5,m=6,r=7,q=8,w=9,x=10,e=11,aa=12,ff=13
  nonNumericAttributes[6]= 9; // A7:  v = 0, h = 1, bb=2, j=3, n=4, z=5, dd=6, ff=7, o=8.
  nonNumericAttributes[8]= 2; // A9:  t = 0, f = 1.
  nonNumericAttributes[9]= 2; // A10: t = 0, f = 1.
  nonNumericAttributes[11]=2; // A12: t = 0, f = 1.
  nonNumericAttributes[12]=3; // A13: g = 0, p = 1, s = 2.
                              // A16: + = 0, - = 1 (class attribute)
  return 1;
} // -------------------------  ReadCrispFile - DIAGNOSIS ----------------------
int DataSets::ReadCrispFileDiagnosis(FILE* fp)
{ float hlm;
  for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f",
    &R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3], &R[k].A[4], &R[k].A[5], &hlm, &R[k].A[6]);
  }
  nonNumericAttributes[1]=2;
  nonNumericAttributes[2]=2;
  nonNumericAttributes[3]=2;
  nonNumericAttributes[4]=2;
  nonNumericAttributes[5]=2;
  return 1;
}  // --------------------------   ReadCrispFile - ECOLI    --------------------
int DataSets::ReadCrispFileEcoli(FILE* fp)
{ char Opis[5], hlam[20];
  for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%s %f %f %f %f %f %f %f %s", hlam,  &R[k].A[0], &R[k].A[1],
               &R[k].A[2], &R[k].A[3], &R[k].A[4], &R[k].A[5], &R[k].A[6], Opis);
    if (!strcmp(Opis, "cp"))  R[k].A[NumberOfInputAttributes]=0.0;
    if (!strcmp(Opis, "im"))  R[k].A[NumberOfInputAttributes]=1.0;
    if (!strcmp(Opis, "pp"))  R[k].A[NumberOfInputAttributes]=2.0;
    if (!strcmp(Opis, "imU")) R[k].A[NumberOfInputAttributes]=3.0;
    if (!strcmp(Opis, "om"))  R[k].A[NumberOfInputAttributes]=4.0;
    if (!strcmp(Opis, "omL")) R[k].A[NumberOfInputAttributes]=5.0;
    if (!strcmp(Opis, "imL")) R[k].A[NumberOfInputAttributes]=6.0;
    if (!strcmp(Opis, "imS")) R[k].A[NumberOfInputAttributes]=7.0;
    if (R[k].A[2] == 0.48) R[k].A[2]=0.0;
    if (R[k].A[3] == 0.50) R[k].A[3]=0.0;                                       
  }
  nonNumericAttributes[2]=2;
  nonNumericAttributes[3]=2;
  return 1;
} // --------------------------   ReadCrispFile  - FOREST -1000 ----------------
int DataSets::ReadCrispFileForestfires(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
    &R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3], &R[k].A[4],
    &R[k].A[5], &R[k].A[6], &R[k].A[7], &R[k].A[8], &R[k].A[9], &R[k].A[10], &R[k].A[11], &R[k].A[12]);

    if ((0   < R[k].A[12]) && (R[k].A[12]<=10  ))     R[k].A[NumberOfInputAttributes]=1.0;
    if ((10  < R[k].A[12]) /*&& (R[k].A[12]<=100 )*/) R[k].A[NumberOfInputAttributes]=2.0;
 //   if ((100 < R[k].A[12]) && (R[k].A[12]<=1000)) R[k].A[NumberOfInputAttributes]=3.0;
  }                         //   Normalization to Log10()
  nonNumericAttributes[2]=12;   //  A[3] - month(0...11)
  nonNumericAttributes[3]= 7;   //  A[4] - day  (0... 6)
  return 1;
} // --------------------------   ReadCrispFile - GLASS    ---------------------
int DataSets::ReadCrispFileGlass(FILE* fp)
{ int num;
  for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",&num,&R[k].A[0],&R[k].A[1],&R[k].A[2],
          &R[k].A[3],&R[k].A[4],&R[k].A[5],&R[k].A[6],&R[k].A[7],&R[k].A[8],&R[k].A[9]);
    --R[k].A[9];             //   Normalization from 0 till NumberOfOutputIntervals-1
  }
  return 1;
} // --------------------------   ReadCrispFile - Haberman    ------------------
int DataSets::ReadCrispFileHaberman(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%f,%f,%f,%f", &R[k].A[0], &R[k].A[1], &R[k].A[2],  &R[k].A[3]);
    --R[k].A[3];            //   Normalization from 0 till NumberOfOutputIntervals-1
  }
  return 1;
}  // --------------------------   ReadCrispFile  - HEART  --------------------------
int DataSets::ReadCrispFileHeart(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
       &R[k].A[ 0], &R[k].A[ 1], &R[k].A[ 2], &R[k].A[ 3], &R[k].A[ 4],
       &R[k].A[ 5], &R[k].A[ 6], &R[k].A[ 7], &R[k].A[ 8], &R[k].A[ 9],
       &R[k].A[10], &R[k].A[11], &R[k].A[12], &R[k].A[13]);
    R[k].A[ 2]--;    R[k].A[10]--;    R[k].A[13]--;
    if (R[k].A[12] == 3) R[k].A[12]=0.0;
    if (R[k].A[12] == 6) R[k].A[12]=1.0;
    if (R[k].A[12] == 7) R[k].A[12]=2.0;
  }
  nonNumericAttributes[ 1]= 2; // A[2] - sex
  nonNumericAttributes[ 2]= 4; // A[3] - chest pain type (1-4)
  nonNumericAttributes[ 5]= 2; // A[6] - fasting blood sugar > 120 mg/dl
  nonNumericAttributes[ 6]= 3; // A[7] - hresting electrocardiographic results (0,1,2)
  nonNumericAttributes[ 8]= 2; // A[9] - exercise induced angina
  nonNumericAttributes[10]= 3; // A[11] - the slope of the peak exercise ST segment
  nonNumericAttributes[11]= 4; // A[12] - number of major vessels (0-3) colored by flourosopy
  nonNumericAttributes[12]= 3; // A[13] - thal: 0->3 (normal); 1->6 (fixed defect); 2->7 (reversable defect)
  return 1;
}  // --------------------------   ReadCrispFile  - ILPD  --------------------------
int DataSets::ReadCrispFileILPD(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
    &R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3], &R[k].A[4],
    &R[k].A[5], &R[k].A[6], &R[k].A[7], &R[k].A[8], &R[k].A[9], &R[k].A[10]);
    --R[k].A[10];            //   Normalization from 0 till NumberOfOutputIntervals-1
  }
  nonNumericAttributes[1]=2;    //  A[2]=0/1  (Female / Male)
  return 1;
} // --------------------------   ReadCrispFile - Image    --------------------------
int DataSets::ReadCrispFileImage(FILE* fp)
{ char Opis[20];
  float hlam_nine;
  for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%s %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", Opis,
       &R[k].A[0], &R[k].A[1], &hlam_nine, &R[k].A[2], &R[k].A[3], &R[k].A[4], &R[k].A[5],
       &R[k].A[6], &R[k].A[7], &R[k].A[8], &R[k].A[9], &R[k].A[10],&R[k].A[11],&R[k].A[12],
       &R[k].A[13],&R[k].A[14],&R[k].A[15],&R[k].A[16],&R[k].A[17]);
    if (!strcmp(Opis, "BRICKFACE")) R[k].A[NumberOfInputAttributes]=0.0;
    if (!strcmp(Opis, "SKY"))       R[k].A[NumberOfInputAttributes]=1.0;
    if (!strcmp(Opis, "FOLIAGE"))   R[k].A[NumberOfInputAttributes]=2.0;
    if (!strcmp(Opis, "CEMENT"))    R[k].A[NumberOfInputAttributes]=3.0;
    if (!strcmp(Opis, "WINDOW"))    R[k].A[NumberOfInputAttributes]=4.0;
    if (!strcmp(Opis, "PATH"))      R[k].A[NumberOfInputAttributes]=5.0;
    if (!strcmp(Opis, "GRASS"))     R[k].A[NumberOfInputAttributes]=6.0;
  }
  return 1;
}
// --------------------------   ReadCrispFile - Ionosphere    --------------------------
int DataSets::ReadCrispFileIonosphere(FILE* fp)
{ char Opis[3];    float tmp;
  for (unsigned long k=0; k<351; k++)
  { fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%1s",
     &R[k].A[0], &tmp,       &R[k].A[1], &R[k].A[2], &R[k].A[3], &R[k].A[4],&R[k].A[5],
     &R[k].A[6], &R[k].A[7], &R[k].A[8], &R[k].A[9],
     &R[k].A[10],&R[k].A[11],&R[k].A[12],&R[k].A[13],&R[k].A[14],&R[k].A[15],
     &R[k].A[16],&R[k].A[17],&R[k].A[18],&R[k].A[19],
     &R[k].A[20],&R[k].A[21],&R[k].A[22],&R[k].A[23],&R[k].A[24],&R[k].A[25],
     &R[k].A[26],&R[k].A[27],&R[k].A[28],&R[k].A[29],
     &R[k].A[30],&R[k].A[31],&R[k].A[32],      Opis);

    if (!strcmp(Opis, "b"))  R[k].A[NumberOfInputAttributes]=0.0;
    if (!strcmp(Opis, "g"))  R[k].A[NumberOfInputAttributes]=1.0;
//    if (tmp != 0) printf ("non zero\n");
//    else          printf (".");
  }
  nonNumericAttributes[0]= 2;
  return 1;
}


// --------------------------   ReadCrispFile  - IRIS  -----------------------
int DataSets::ReadCrispFileIris(FILE* fp)
{ char Opis[20];
  for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%f,%f,%f,%f,%s", &R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3], Opis);
    if (!strcmp(Opis,"Iris-setosa")    ) R[k].A[NumberOfInputAttributes]=0.0;
    if (!strcmp(Opis,"Iris-versicolor")) R[k].A[NumberOfInputAttributes]=1.0;
    if (!strcmp(Opis,"Iris-virginica") ) R[k].A[NumberOfInputAttributes]=2.0;
  }
  return 1;
} // --------------------------   ReadCrispFile  - KRKOPT  ---------------------
int DataSets::ReadCrispFileKrkopt(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%f,%f,%f,%f,%f,%f,%f",
      &R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3], &R[k].A[4], &R[k].A[5], &R[k].A[6]);
    R[k].A[1]--;
    R[k].A[3]--;
    R[k].A[5]--;
  }
  nonNumericAttributes[0]= 4;  // A[1] - White King file (column) (a,b,c,d)
  nonNumericAttributes[1]= 4;  // A[2] - White King rank (row)    (1,2,3,4)
  nonNumericAttributes[2]= 8;  // A[3] - White Rook file (A,B,C,D,E,F,G,H)
  nonNumericAttributes[3]= 8;  // A[4] - White Rook rank (1,2,3,4,5,6,7,8)
  nonNumericAttributes[4]= 8;  // A[5] - Black King file (A,B,C,D,E,F,G,H)
  nonNumericAttributes[5]= 8;  // A[6] - Black King rank (1,2,3,4,5,6,7,8)
  return 1;
} // --------------------------   ReadCrispFile  - MAGIC  --------------------------
int DataSets::ReadCrispFileMagic(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
      &R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3], &R[k].A[4],
      &R[k].A[5], &R[k].A[6], &R[k].A[7], &R[k].A[8], &R[k].A[9], &R[k].A[10]);
  }
  return 1;
} // -------------------------    ReadCrispFile - PARKINSONS -------------------
int	DataSets::ReadCrispFileParkinsons	(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
    fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
		&R[k].A[ 0],&R[k].A[ 1],&R[k].A[ 2], &R[k].A[ 3],&R[k].A[ 4],&R[k].A[ 5],&R[k].A[ 6],
		&R[k].A[ 7],&R[k].A[ 8],&R[k].A[ 9], &R[k].A[10],&R[k].A[11],&R[k].A[12],&R[k].A[13],
		&R[k].A[14],&R[k].A[15],&R[k].A[16], &R[k].A[17],&R[k].A[18],&R[k].A[19],&R[k].A[20],
		&R[k].A[21],&R[k].A[22],&R[k].A[23]);
  return 1;
} // --------------------------   ReadCrispFile - Pima    --------------------------
int DataSets::ReadCrispFilePima(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
    fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f",   &R[k].A[0], &R[k].A[1], &R[k].A[2],
        &R[k].A[3],  &R[k].A[4],  &R[k].A[5], &R[k].A[6], &R[k].A[7], &R[k].A[8]);
  return 1;
} // --------------------------   ReadCrispFile  - SKIN  --------------------------
int DataSets::ReadCrispFileSkin(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"   %f,%f,%f,%f", &R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3]);
    --R[k].A[3];             //   Normalization from 0 till NumberOfOutputIntervals-1
  }
  return 1;
} // -------------------------    ReadCrispFile  - SONAR -----------------------
int	DataSets::ReadCrispFileSonar(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
    fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
		&R[k].A[ 0], &R[k].A[ 1], &R[k].A[ 2], &R[k].A[ 3], &R[k].A[ 4],&R[k].A[ 5],&R[k].A[ 6],
		&R[k].A[ 7], &R[k].A[ 8], &R[k].A[ 9], &R[k].A[10], &R[k].A[11],&R[k].A[12],&R[k].A[13],
		&R[k].A[14], &R[k].A[15], &R[k].A[16], &R[k].A[17], &R[k].A[18],&R[k].A[19],&R[k].A[20],
		&R[k].A[21], &R[k].A[22], &R[k].A[23], &R[k].A[24], &R[k].A[25],&R[k].A[26],&R[k].A[27],
		&R[k].A[28], &R[k].A[29], &R[k].A[30], &R[k].A[31], &R[k].A[32],&R[k].A[33],&R[k].A[34],
		&R[k].A[35], &R[k].A[36], &R[k].A[37], &R[k].A[38], &R[k].A[39],&R[k].A[40],&R[k].A[41],
		&R[k].A[42], &R[k].A[43], &R[k].A[44], &R[k].A[45], &R[k].A[46],&R[k].A[47],&R[k].A[48],
		&R[k].A[49], &R[k].A[50], &R[k].A[51], &R[k].A[52], &R[k].A[53],&R[k].A[54],&R[k].A[55],
		&R[k].A[56], &R[k].A[57], &R[k].A[58], &R[k].A[59], &R[k].A[60]); //   class - M=0, R=1
  return 1;
} // --------------------------   ReadCrispFile - Tae --------------------------
int DataSets::ReadCrispFileTae(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
  {  fscanf(fp,"%f,%f,%f,%f,%f,%f",
      &R[k].A[0],  &R[k].A[1],  &R[k].A[2],  &R[k].A[3],  &R[k].A[4],  &R[k].A[5]);
     --R[k].A[0]; --R[k].A[1]; --R[k].A[2]; --R[k].A[3]; --R[k].A[5];
  }
  nonNumericAttributes[0]= 2;
  nonNumericAttributes[1]=25;
  nonNumericAttributes[2]=26;
  nonNumericAttributes[3]= 2;
  return 1;
}

// -------------------------    ReadCrispFile  - TIC ---------------------------
int	DataSets::ReadCrispFileTic(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
    fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",&R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3],
                          &R[k].A[4], &R[k].A[5],&R[k].A[6],&R[k].A[7],&R[k].A[8],&R[k].A[9]);
  nonNumericAttributes[0]=3;     // top-left-square:      x,o,b.
  nonNumericAttributes[1]=3;     // top-middle-square:    x,o,b.
  nonNumericAttributes[2]=3;     // top-right-square:     x,o,b.
  nonNumericAttributes[3]=3;     // middle-left-square:   x,o,b.
  nonNumericAttributes[4]=3;     // middle-middle-square: x,o,b.
  nonNumericAttributes[5]=3;     // middle-right-square:  x,o,b.
  nonNumericAttributes[6]=3;     // bottom-left-square:   x,o,b.
  nonNumericAttributes[7]=3;     // bottom-middle-square: x,o,b.
  nonNumericAttributes[8]=3;     // bottom-right-square:  x,o,b.
  return 1;
} // --------------------------   ReadCrispFile  - VENICLE -1000 ---------------
int DataSets::ReadCrispFileVenicle(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
   fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
       &R[k].A[ 0], &R[k].A[ 1], &R[k].A[ 2], &R[k].A[ 3], &R[k].A[ 4],
       &R[k].A[ 5], &R[k].A[ 6], &R[k].A[ 7], &R[k].A[ 8], &R[k].A[ 9],
       &R[k].A[10], &R[k].A[11], &R[k].A[12], &R[k].A[13], &R[k].A[14],
       &R[k].A[15], &R[k].A[16], &R[k].A[17], &R[k].A[18]);
  return 1;
} // -------------------------    ReadCrispFile  - Vowel ---------------------------
int	DataSets::ReadCrispFileVowel(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
    fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
		&R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3], &R[k].A[4],&R[k].A[5],&R[k].A[6],
		&R[k].A[7], &R[k].A[8], &R[k].A[9], &R[k].A[10]);
  return 1;
} // -------------------------    ReadCrispFile - WDBC -------------------------
int DataSets::ReadCrispFileWDBC(FILE* fp)
{ unsigned long k, ID;
  for (k=0; k<TotalSets; k++)
    fscanf(fp,"%ld,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
    &ID,&R[k].A[30],&R[k].A[ 0], &R[k].A[ 1], &R[k].A[ 2], &R[k].A[ 3],&R[k].A[ 4],
                    &R[k].A[ 5], &R[k].A[ 6], &R[k].A[ 7], &R[k].A[ 8],&R[k].A[ 9],
                    &R[k].A[10], &R[k].A[11], &R[k].A[12], &R[k].A[13],&R[k].A[14],
                    &R[k].A[15], &R[k].A[16], &R[k].A[17], &R[k].A[18],&R[k].A[19],
                    &R[k].A[20], &R[k].A[21], &R[k].A[22], &R[k].A[23],&R[k].A[24],
                    &R[k].A[25], &R[k].A[26], &R[k].A[27], &R[k].A[28],&R[k].A[29]);// class "M"->0  "B"->1
  return 1;
} // --------------------------   ReadCrispFile - WINE    ----------------------
int DataSets::ReadCrispFileWine(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", &R[k].A[13],
     &R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3],  &R[k].A[4], &R[k].A[5],&R[k].A[6],
     &R[k].A[7], &R[k].A[8], &R[k].A[9], &R[k].A[10], &R[k].A[11],&R[k].A[12]);
    --R[k].A[NumberOfInputAttributes];    //  NumberOfInputAttributes == 13
  }
  return 1;
} // --------------------------   ReadCrispFile  - WINERED & WINEWHITE --------------------------
int DataSets::ReadCrispFileWineQuality(FILE* fp)
{ for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
       &R[k].A[ 0], &R[k].A[ 1], &R[k].A[ 2], &R[k].A[ 3], &R[k].A[ 4],
       &R[k].A[ 5], &R[k].A[ 6], &R[k].A[ 7], &R[k].A[ 8], &R[k].A[ 9], &R[k].A[10], &R[k].A[11]);
    R[k].A[11] -= 3;
  }
  return 1;
} // -------------------------    ReadCrispFile - WPBC ---------------------------
int DataSets::ReadCrispFileWPBC(FILE* fp)
{ unsigned long k, ID;
  for (k=0; k<TotalSets; k++)
    fscanf(fp,"%ld,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
    &ID,&R[k].A[33],&R[k].A[ 0], &R[k].A[ 1], &R[k].A[ 2], &R[k].A[ 3],&R[k].A[ 4],
                    &R[k].A[ 5], &R[k].A[ 6], &R[k].A[ 7], &R[k].A[ 8],&R[k].A[ 9],
                    &R[k].A[10], &R[k].A[11], &R[k].A[12], &R[k].A[13],&R[k].A[14],
                    &R[k].A[15], &R[k].A[16], &R[k].A[17], &R[k].A[18],&R[k].A[19],
                    &R[k].A[20], &R[k].A[21], &R[k].A[22], &R[k].A[23],&R[k].A[24],
                    &R[k].A[25], &R[k].A[26], &R[k].A[27], &R[k].A[28],&R[k].A[29],
                    &R[k].A[30], &R[k].A[31], &R[k].A[32]);      // class "R"->0  "N"->1
  return 1;
} // --------------------------   ReadCrispFile - Yeast    --------------------------
int DataSets::ReadCrispFileYeast(FILE* fp)
{ char Opis[15], OpisHlam[15];
  for (unsigned long k=0; k<TotalSets; k++)
  { fscanf(fp,"%s  %f  %f  %f  %f  %f  %f  %f  %f  %s",  OpisHlam,
               &R[k].A[0], &R[k].A[1], &R[k].A[2], &R[k].A[3], &R[k].A[4],
               &R[k].A[5], &R[k].A[6], &R[k].A[7], Opis);

    if (R[k].A[4] == 0.50) R[k].A[4]=0.0;
    if (R[k].A[5] == 0.50) R[k].A[5]=1.0;
    if (R[k].A[5] == 0.83) R[k].A[5]=2.0;
    if (!strcmp(Opis, "CYT"))  R[k].A[NumberOfInputAttributes]=0.0;
    if (!strcmp(Opis, "NUC"))  R[k].A[NumberOfInputAttributes]=1.0;
    if (!strcmp(Opis, "MIT"))  R[k].A[NumberOfInputAttributes]=2.0;
    if (!strcmp(Opis, "ME3"))  R[k].A[NumberOfInputAttributes]=3.0;
    if (!strcmp(Opis, "ME2"))  R[k].A[NumberOfInputAttributes]=4.0;
    if (!strcmp(Opis, "ME1"))  R[k].A[NumberOfInputAttributes]=5.0;
    if (!strcmp(Opis, "EXC"))  R[k].A[NumberOfInputAttributes]=6.0;
    if (!strcmp(Opis, "VAC"))  R[k].A[NumberOfInputAttributes]=7.0;
    if (!strcmp(Opis, "POX"))  R[k].A[NumberOfInputAttributes]=8.0;
    if (!strcmp(Opis, "ERL"))  R[k].A[NumberOfInputAttributes]=9.0;
 }
 nonNumericAttributes[4] = 2;           //  0.5   1.0
 nonNumericAttributes[5] = 3;           //  0.0   0.5  0.83
 return 1;
}
// --------------------------   ReadCrispFile  - Semstralka  --------------------------
int DataSets::ReadCrispFileSemestralka(FILE* fp){  return 1; }
int DataSets::ReadCrispFileTest       (FILE* fp){  return 1; }

