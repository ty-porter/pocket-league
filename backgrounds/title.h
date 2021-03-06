// ///////////////////////
// //                   //
// //  File Attributes  //
// //                   //
// ///////////////////////

// Filename: title.png
// Pixel Width: 168px
// Pixel Height: 144px

// WARNING:  Width of input image padded 6px to 168px

// /////////////////
// //             //
// //  Constants  //
// //             //
// /////////////////

const int title_tile_map_size = 0x017A;
const int title_tile_map_width = 0x15;
const int title_tile_map_height = 0x12;

const int title_tile_data_size = 0x0700;
const int title_tile_count = 0x70;

// ////////////////
// //            //
// //  Map Data  //
// //            //
// ////////////////

const const unsigned char title_map_data[] ={
  0x00,0x00,0x00,0x01,0x02,0x03,0x01,0x04,0x00,0x05,0x06,0x07,0x08,0x02,0x09,0x02,
  0x0A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0B,0x0C,0x0D,0x0E,0x0F,0x10,0x11,0x12,
  0x13,0x14,0x15,0x16,0x17,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0B,0x19,0x1A,
  0x1B,0x1C,0x1D,0x1E,0x1F,0x20,0x21,0x15,0x22,0x23,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,0x30,0x0A,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0B,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,
  0x39,0x3A,0x3B,0x33,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0B,0x3D,0x3E,0x33,
  0x3F,0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x33,0x47,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x48,0x49,0x4A,0x49,0x4B,0x4C,0x4D,0x4E,0x4F,0x50,0x51,0x52,0x49,0x53,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x54,0x55,0x56,0x57,0x58,0x59,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x5A,
  0x5B,0x5C,0x5D,0x5E,0x5F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

// /////////////////
// //             //
// //  Tile Data  //
// //             //
// /////////////////

const const unsigned char title_tile_data[] ={
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0xF0,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x1F,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xDF,0xDF,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC3,0xC3,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFB,0xFB,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE7,0xE7,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xC0,
  0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF1,0xF1,0xF0,0xF0,0xF0,0xF0,
  0xE0,0xE0,0xF8,0xF8,0xF8,0xF8,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFD,0xFD,
  0x0F,0x0F,0x1F,0x1F,0x3F,0x3F,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xFC,
  0xFC,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x3F,0x0F,0x0F,
  0x00,0x00,0x00,0x00,0x81,0x81,0x83,0x83,0xC7,0xC7,0xC7,0xC7,0xE7,0xE7,0xEF,0xEF,
  0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0xF8,0xE0,0xE0,
  0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0x1F,0x1F,
  0xC7,0xC7,0xC7,0xC7,0xCF,0xCF,0xCF,0xCF,0xDF,0xDF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xF3,0xF3,0xF3,0xF3,0xE3,0xE3,0xC3,0xC3,0xC3,0xC3,0x83,0x83,0x83,0x83,0x03,0x03,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0xF0,0xF0,0xF0,0xFF,0xFF,
  0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0x00,0x00,0x00,0x00,0xC0,0xC0,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,
  0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,
  0xF1,0xF1,0xF1,0xF1,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0xF0,0xF0,0xF0,
  0xFD,0xFD,0xFD,0xFD,0xF9,0xF9,0xF1,0xF1,0xC1,0xC1,0x80,0x80,0x00,0x00,0x00,0x00,
  0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFE,0xFE,0xFF,0xFF,0xFF,0xFF,
  0x0F,0x0F,0x07,0x07,0x07,0x07,0x07,0x07,0x0F,0x0F,0x1F,0x1F,0xFF,0xFF,0xFF,0xFF,
  0xEF,0xEF,0xEF,0xEF,0xEF,0xEF,0xEF,0xEF,0xEF,0xEF,0xEF,0xEF,0xC7,0xC7,0xC7,0xC7,
  0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xF0,0xF0,0xFF,0xFF,0xFF,0xFF,
  0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F,0x5F,0x5F,0xDF,0xDF,0xDF,0xDF,
  0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xDF,0xDF,
  0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x83,0x83,0xC3,0xC3,
  0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0x00,0x00,0x00,0x00,0xE0,0xE0,
  0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,
  0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x00,0x00,0x00,0x00,0x03,0x03,
  0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0x00,0x00,0x00,0x00,0xF0,0xF0,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x07,
  0x7F,0x7F,0x7F,0x7F,0x3F,0x3F,0x0F,0x0F,0x07,0x07,0x00,0x00,0x00,0x00,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0xF8,0xF8,0x00,0x00,0x00,0x00,0xC0,0xC0,
  0xC3,0xC3,0x81,0x81,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x3F,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x3F,0x3F,0x00,0x00,0x00,0x00,0x80,0x80,
  0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0xDF,0x00,0x00,0x07,0x07,0x1F,0x1F,
  0xDF,0xDF,0xCF,0xCF,0xCF,0xCF,0xC7,0xC7,0xC7,0xC7,0x00,0x00,0xC0,0xC0,0xF8,0xF8,
  0xC3,0xC3,0xE3,0xE3,0xE3,0xE3,0xF3,0xF3,0xFB,0xFB,0x00,0x00,0x00,0x00,0x3F,0x3F,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x87,0x87,
  0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0x00,0x00,0x00,0x00,0xE7,0xE7,
  0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0x00,0x00,0x00,0x00,0xFF,0xFF,
  0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,
  0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0xE0,0xE0,0xE0,0xE0,0xE0,0xFF,0xFF,
  0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0x00,0x00,0x00,0x00,0x01,0x01,0x81,0x81,
  0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF3,0xF3,
  0x80,0x80,0x80,0x80,0x81,0x81,0xC1,0xC1,0xC3,0xC3,0xC3,0xC3,0xE3,0xE3,0xE7,0xE7,
  0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xFC,0xF0,0xF0,0xF1,0xF1,
  0xFC,0xFC,0xFE,0xFE,0xFE,0xFE,0xFC,0xFC,0xF8,0xF8,0x30,0x30,0x00,0x00,0xFF,0xFF,
  0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0xBF,0xBF,
  0x87,0x87,0x87,0x87,0x87,0x87,0x87,0x87,0x87,0x87,0x87,0x87,0x87,0x87,0x87,0x87,
  0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,
  0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x80,
  0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xFF,0xFF,
  0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0x07,0xE7,0xE7,
  0x81,0x81,0x83,0x83,0x83,0x83,0x83,0x83,0x03,0x03,0x07,0x07,0x07,0x07,0xC7,0xC7,
  0xF3,0xF3,0xF3,0xF3,0xF3,0xF3,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xE7,0xE7,0xE7,0xE7,0xF7,0xF7,0xF7,0xF7,0xF3,0xF3,0xFB,0xFB,0xFB,0xFB,0xF9,0xF9,
  0xF1,0xF1,0xE1,0xE1,0xF1,0xF1,0xF1,0xF1,0xF1,0xF1,0xF8,0xF8,0xFC,0xFC,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x3F,0x7F,0x7F,0xFF,0xFF,
  0xBF,0xBF,0xBF,0xBF,0xBF,0xBF,0xBF,0xBF,0xBF,0xBF,0x3F,0x3F,0x1F,0x1F,0x1F,0x1F,
  0x87,0x87,0x87,0x87,0x87,0x87,0x87,0x87,0x87,0x87,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xC7,0xC7,
  0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0xC0,
  0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0xCF,0xCF,0xCF,0xCF,0xCF,0xCF,0xDF,0xDF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0xFF,0xFF,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0xFF,0xFF,0xFF,0xFF,0x3F,0x3F,0x1F,0x1F,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,
  0xFE,0xFE,0xFC,0xFC,0xF8,0xF8,0xF0,0xF0,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
  0x0F,0x0F,0x0F,0x0F,0x07,0x07,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0x70,0x70,0x00,0x00,0x00,0x00,0x00,0x00,
  0xC7,0xC7,0x87,0x87,0x07,0x07,0x07,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x06,0x06,0x06,0x06,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC7,0xC7,0x61,0x61,0x01,0x01,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE1,0xE1,0x83,0x83,0x86,0x86,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x87,0x87,0xC6,0xC6,0x66,0x66,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC7,0xC7,0x61,0x61,0x61,0x61,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE0,0xE0,0x80,0x80,0x80,0x80,
  0x03,0x03,0x01,0x01,0x00,0x00,0x00,0x00,0x06,0x06,0x03,0x03,0x00,0x00,0x00,0x00,
  0x01,0x01,0x81,0x81,0xC1,0xC1,0x61,0x61,0x61,0x61,0xC1,0xC1,0x00,0x00,0x00,0x00,
  0x86,0x86,0x86,0x86,0x87,0x87,0x86,0x86,0x86,0x86,0x86,0x86,0x00,0x00,0x00,0x00,
  0x66,0x66,0x67,0x67,0xE6,0xE6,0x66,0x66,0x66,0x66,0x66,0x66,0x00,0x00,0x00,0x00,
  0x61,0x61,0xC1,0xC1,0xC1,0xC1,0x61,0x61,0x61,0x61,0x61,0x61,0x00,0x00,0x00,0x00,
  0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00,0x00,0x00,0x00,
  0x00,0x00,0x03,0x03,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,0x06,
  0x00,0x00,0xC7,0xC7,0x66,0x66,0x66,0x66,0x06,0x06,0x07,0x07,0x06,0x06,0x66,0x66,
  0x00,0x00,0xC7,0xC7,0x66,0x66,0x66,0x66,0x66,0x66,0xC7,0xC7,0xC6,0xC6,0x66,0x66,
  0x00,0x00,0xE7,0xE7,0x06,0x06,0x06,0x06,0x06,0x06,0xC6,0xC6,0x06,0x06,0x06,0x06,
  0x00,0x00,0x83,0x83,0xC1,0xC1,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,0x61,
  0x00,0x00,0xC7,0xC7,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,
  0x00,0x00,0xE3,0xE3,0x86,0x86,0x86,0x86,0x83,0x83,0x81,0x81,0x80,0x80,0x80,0x80,
  0x00,0x00,0xC0,0xC0,0x60,0x60,0x00,0x00,0x00,0x00,0x80,0x80,0xC0,0xC0,0x60,0x60,
  0x06,0x06,0x03,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x66,0x66,0xC6,0xC6,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x66,0x66,0x67,0x67,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x06,0x06,0xE7,0xE7,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0xC1,0xC1,0x83,0x83,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x81,0x81,0xC1,0xC1,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x86,0x86,0x83,0x83,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x60,0x60,0xC0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
