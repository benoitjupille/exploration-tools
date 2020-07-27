// Ringtone when phone is ringing
const uint16_t ringTone[] PROGMEM = {
  220,50, 440,50,
  220,50, 440,50,
  220,50, 440,50,
  220,50, 440,50,
  220,50, 440,50,
  220,50, 440,50,
  220,50, 440,50,
  220,50, 440,50,
  220,50, 440,50,
  220,50, 440,50,
  0, 600,
  TONES_END
};

// A word that can be pronounced by a character
const uint16_t word1[] PROGMEM = {
  440,100, 450,50, 0,20, 460,50,
  440,50, 340,50,
  0,20, 460,100,
  0, 200,
  TONES_END
};
const uint16_t word2[] PROGMEM = {
  430,100, 460,50, 440,50,
  0,50, 340,50,
  0, 100,
  TONES_END
};

const uint16_t word3[] PROGMEM = {
  440,50, 400,50, 0,50,
  TONES_END
};

const uint16_t word4[] PROGMEM = {
  500,50, 440,50, 0,50,
  TONES_END
};

const uint16_t word5[] PROGMEM = {
  490,50, 0,20,
  TONES_END
};

const uint16_t word6[] PROGMEM = {
  480,50,
  TONES_END
};

const uint16_t word7[] PROGMEM = {
  680,50,
  TONES_END
};

const uint16_t words[7] = {
    word1,
    word2,
    word3,
    word4,
    word5,
    word6,
    word7
};