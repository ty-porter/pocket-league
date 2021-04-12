#define BGM_LENGTH 128

//Define note names
typedef enum {
  C3, Cd3, D3, Dd3, E3, F3, Fd3, G3, Gd3, A3, Ad3, B3,
  C4, Cd4, D4, Dd4, E4, F4, Fd4, G4, Gd4, A4, Ad4, B4,
  C5, Cd5, D5, Dd5, E5, F5, Fd5, G5, Gd5, A5, Ad5, B5,
  C6, Cd6, D6, Dd6, E6, F6, Fd6, G6, Gd6, A6, Ad6, B6,
  C7, Cd7, D7, Dd7, E7, F7, Fd7, G7, Gd7, A7, Ad7, B7,
  C8, Cd8, D8, Dd8, E8, F8, Fd8, G8, Gd8, A8, Ad8, B8,
  SILENCE
} pitch;

const UWORD frequencies[] = { //values based on a formula used by the GB processor
    44,  156,  262,  363,  457,  547,  631,  710,  786,  854,  923,  986,
  1046, 1102, 1155, 1205, 1253, 1297, 1339, 1379, 1417, 1452, 1486, 1517,
  1546, 1575, 1602, 1627, 1650, 1673, 1694, 1714, 1732, 1750, 1767, 1783,
  1798, 1812, 1825, 1837, 1849, 1860, 1871, 1881, 1890, 1899, 1907, 1915,
  1923, 1930, 1936, 1943, 1949, 1954, 1959, 1964, 1969, 1974, 1978, 1982,
  1985, 1988, 1992, 1995, 1998, 2001, 2004, 2006, 2009, 2011, 2013, 2015
};

//Define Instrument names
//Instruments should be confined to one channel
//due to different registers used between ch1, 2, 3, 4
typedef enum {
  QUIET,
  RHYTHM,  //channel 1
  MELODY,  //channel 2
  HARMONY, //channel 3
  SNARE,   //channel 4
  CYMBAL,  //channel 4
  BASS     //channel 4
} instrument;

// Define a note as having a pitch and instrument
typedef struct {
  instrument i;
  pitch p;
} note;

// Notes to be played on channel 2
const note song_ch1[BGM_LENGTH] = {
  {RHYTHM, G5},
  {QUIET, SILENCE},
  {RHYTHM, A5},
  {QUIET, SILENCE},
  {RHYTHM, Ad5},
  {QUIET, SILENCE},
  {RHYTHM, C6},
  {QUIET, SILENCE},
  
  {RHYTHM, D6},
  {QUIET, SILENCE},
  {RHYTHM, F6},
  {QUIET, SILENCE},
  {RHYTHM, E6},
  {RHYTHM, E6},
  {QUIET, SILENCE},
  {QUIET, SILENCE},

  {RHYTHM, C6},
  {RHYTHM, C6},
  {RHYTHM, C6},
  {RHYTHM, C6},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},

  {RHYTHM, G5},
  {QUIET, SILENCE},
  {RHYTHM, A5},
  {QUIET, SILENCE},
  {RHYTHM, Ad5},
  {QUIET, SILENCE},
  {RHYTHM, C6},
  {QUIET, SILENCE},
  
  {RHYTHM, D6},
  {QUIET, SILENCE},
  {RHYTHM, F6},
  {QUIET, SILENCE},
  {RHYTHM, E6},
  {RHYTHM, E6},
  {QUIET, SILENCE},
  {QUIET, SILENCE},

  {RHYTHM, G6},
  {RHYTHM, G6},
  {RHYTHM, G6},
  {RHYTHM, G6},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  
  {RHYTHM, G6},
  {RHYTHM, G6},
  {RHYTHM, G6},
  {RHYTHM, G6},
  {RHYTHM, G6},
  {RHYTHM, G6},
  {QUIET, SILENCE},
  {RHYTHM, G6},

  {RHYTHM, A6},
  {RHYTHM, A6},
  {QUIET, SILENCE},
  {RHYTHM, G6},
  {RHYTHM, G6},
  {QUIET, SILENCE},
  {RHYTHM, F6},
  {RHYTHM, F6},

  {RHYTHM, Ad6},
  {RHYTHM, A6},
  {RHYTHM, G6},
  {QUIET, SILENCE},
  {RHYTHM, G6},
  {RHYTHM, G6},
  {RHYTHM, G6},
  {RHYTHM, G6},
  
  {RHYTHM, G6},
  {RHYTHM, G6},
  {RHYTHM, G6},
  {RHYTHM, G6},
  {RHYTHM, G6},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {RHYTHM, G6},

  {RHYTHM, D7},
  {RHYTHM, D7},
  {QUIET, SILENCE},
  {RHYTHM, C7},
  {RHYTHM, C7},
  {QUIET, SILENCE},
  {RHYTHM, Ad6},
  {RHYTHM, Ad6},

  {RHYTHM, C7},
  {RHYTHM, C7},
  {RHYTHM, C7},
  {RHYTHM, C7},
  {RHYTHM, C7},
  {RHYTHM, C7},
  {RHYTHM, C7},
  {RHYTHM, C7},
  
  {RHYTHM, C7},
  {RHYTHM, C7},
  {RHYTHM, C7},
  {RHYTHM, C7},
  {RHYTHM, D7},
  {RHYTHM, C7},
  {RHYTHM, C7},
  {RHYTHM, C7},

  {RHYTHM, B6},
  {RHYTHM, B6},
  {RHYTHM, B6},
  {RHYTHM, B6},
  {RHYTHM, B6},
  {RHYTHM, B6},
  {RHYTHM, B6},
  {RHYTHM, B6},
  
  {RHYTHM, B6},
  {RHYTHM, B6},
  {RHYTHM, B6},
  {RHYTHM, B6},
  {RHYTHM, B6},
  {RHYTHM, B6},
  {RHYTHM, B6},
  {RHYTHM, B6},

  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE}
};

// Notes to be played on channel 3
const note song_ch3[BGM_LENGTH] = { 
  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},

  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},

  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},

  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},

  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},

  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},

  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},

  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},

    {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},

  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},

  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},

  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},

  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},

  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},

  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {HARMONY, G3},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},

  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE}
};

// Notes to be played on channel 4
// SILENCE, since it doesn't matter what pitch
const note song_ch4[BGM_LENGTH] = { 
  {BASS, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {SNARE, SILENCE},
  {BASS, SILENCE},
  {QUIET, SILENCE},
  {BASS, SILENCE},
  {CYMBAL, SILENCE},
  
  {SNARE, SILENCE},
  {BASS, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {BASS, SILENCE},
  {CYMBAL, SILENCE},
  {SNARE, SILENCE},
  {BASS, SILENCE},

  {BASS, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {SNARE, SILENCE},
  {BASS, SILENCE},
  {QUIET, SILENCE},
  {BASS, SILENCE},
  {CYMBAL, SILENCE},
  
  {SNARE, SILENCE},
  {BASS, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {BASS, SILENCE},
  {CYMBAL, SILENCE},
  {SNARE, SILENCE},
  {BASS, SILENCE},
  
  {BASS, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {SNARE, SILENCE},
  {BASS, SILENCE},
  {QUIET, SILENCE},
  {BASS, SILENCE},
  {CYMBAL, SILENCE},
  
  {SNARE, SILENCE},
  {BASS, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {BASS, SILENCE},
  {CYMBAL, SILENCE},
  {SNARE, SILENCE},
  {BASS, SILENCE},
  
  {BASS, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {SNARE, SILENCE},
  {BASS, SILENCE},
  {QUIET, SILENCE},
  {BASS, SILENCE},
  {CYMBAL, SILENCE},
  
  {SNARE, SILENCE},
  {BASS, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {BASS, SILENCE},
  {CYMBAL, SILENCE},
  {SNARE, SILENCE},
  {BASS, SILENCE},

  {BASS, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {SNARE, SILENCE},
  {BASS, SILENCE},
  {QUIET, SILENCE},
  {BASS, SILENCE},
  {CYMBAL, SILENCE},
  
  {SNARE, SILENCE},
  {BASS, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {BASS, SILENCE},
  {CYMBAL, SILENCE},
  {SNARE, SILENCE},
  {BASS, SILENCE},

  {BASS, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {SNARE, SILENCE},
  {BASS, SILENCE},
  {QUIET, SILENCE},
  {BASS, SILENCE},
  {CYMBAL, SILENCE},
  
  {SNARE, SILENCE},
  {BASS, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {BASS, SILENCE},
  {CYMBAL, SILENCE},
  {SNARE, SILENCE},
  {BASS, SILENCE},
  
  {BASS, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {SNARE, SILENCE},
  {BASS, SILENCE},
  {QUIET, SILENCE},
  {BASS, SILENCE},
  {CYMBAL, SILENCE},
  
  {SNARE, SILENCE},
  {BASS, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {BASS, SILENCE},
  {CYMBAL, SILENCE},
  {SNARE, SILENCE},
  {BASS, SILENCE},
  
  {BASS, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {SNARE, SILENCE},
  {BASS, SILENCE},
  {QUIET, SILENCE},
  {BASS, SILENCE},
  {CYMBAL, SILENCE},

  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE},
  {QUIET, SILENCE}
};

//function to set sound registers based on notes chosen
void set_note(note *n) {
  switch((*n).i) {
    case RHYTHM:
      NR10_REG = 0x00;
      NR11_REG = 0x00;
      NR14_REG = 0xF3;
      NR13_REG = (UBYTE)frequencies[(*n).p]; //low bits of frequency
      NR14_REG = 0x80 | ((UWORD)frequencies[(*n).p]>>8); //high bits of frequency (and sound reset)
    case MELODY:
      NR21_REG = 0xC0;
      NR22_REG = 0x63;
      NR23_REG = (UBYTE)frequencies[(*n).p]; //low bits of frequency
      NR24_REG = 0x80 | ((UWORD)frequencies[(*n).p]>>8); //high bits of frequency (and sound reset)
    break;
    case HARMONY:
      NR30_REG = 0x80;
      NR31_REG = 0x85;
      NR32_REG = 0x60;
      NR33_REG = (UBYTE)frequencies[(*n).p]; //low bits of frequency
      NR34_REG = 0xC0 | ((UWORD)frequencies[(*n).p]>>8);
    break;
    case SNARE:
      NR41_REG = 0x01;
      NR42_REG = 0x37;
      NR43_REG = 0x33;
      NR44_REG = 0x80;
    break;
    case CYMBAL:
      NR41_REG = 0x01;
      NR42_REG = 0x37;
      NR43_REG = 0x13;
      NR44_REG = 0x80;
    break;
    case BASS:
      NR41_REG = 0x01;
      NR42_REG = 0x37;
      NR43_REG = 0x63;
      NR44_REG = 0x80;
    case QUIET:
    break;
	}
}

void play_song(INT8 current_beat) {
  set_note(&song_ch1[current_beat]);
  set_note(&song_ch3[current_beat]);
  set_note(&song_ch4[current_beat]);
}

