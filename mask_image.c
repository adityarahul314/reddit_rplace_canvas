#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <zlib.h>

unsigned char crc32_checksum[8];
unsigned char raw_image_data[12002000];
unsigned char comp_image_data[12002000];
int uncomp_data_size = 0;
int comp_data_size;
int user_hash_count = 0;

int asciitohex(char char_input){
  int int_out;
  switch (char_input) {
    case '0' : int_out = 0; break;
    case '1' : int_out = 1; break;
    case '2' : int_out = 2; break;
    case '3' : int_out = 3; break;
    case '4' : int_out = 4; break;
    case '5' : int_out = 5; break;
    case '6' : int_out = 6; break;
    case '7' : int_out = 7; break;
    case '8' : int_out = 8; break;
    case '9' : int_out = 9; break;
    case 'A' : int_out = 10; break;
    case 'B' : int_out = 11; break;
    case 'C' : int_out = 12; break;
    case 'D' : int_out = 13; break;
    case 'E' : int_out = 14; break;
    case 'F' : int_out = 15; break;
  }
  return int_out;
}

void get_raw_data_v2(){
  FILE *in_file;
  in_file = fopen("2022-compact.csv","rb");

  char charbuff[256];
  int file_seek = 0;
  char comma = ',';
  unsigned char pixel_color[3];

  //custom pallete initialisation
  unsigned char color_0[3] = {0xFF, 0xFF, 0xFF};
  unsigned char color_1[3] = {0xFF, 0xF8, 0xB8};
  unsigned char color_2[3] = {0xFF, 0xD6, 0x35};
  unsigned char color_3[3] = {0xFF, 0xB4, 0x70};
  unsigned char color_4[3] = {0xFF, 0xA8, 0x00};
  unsigned char color_5[3] = {0xFF, 0x99, 0xAA};
  unsigned char color_6[3] = {0xFF, 0x45, 0x00};
  unsigned char color_7[3] = {0xFF, 0x38, 0x81};
  unsigned char color_8[3] = {0xE4, 0xAB, 0xFF};
  unsigned char color_9[3] = {0xDE, 0x10, 0x7F};
  unsigned char color_10[3] = {0xD4, 0xD7, 0xD9};
  unsigned char color_11[3] = {0xBE, 0x00, 0x39};
  unsigned char color_12[3] = {0xB4, 0x4A, 0xC0};
  unsigned char color_13[3] = {0x9C, 0x69, 0x26};
  unsigned char color_14[3] = {0x94, 0xB3, 0xFF};
  unsigned char color_15[3] = {0x89, 0x8D, 0x90};
  unsigned char color_16[3] = {0x81, 0x1E, 0x9F};
  unsigned char color_17[3] = {0x7E, 0xED, 0x56};
  unsigned char color_18[3] = {0x6D, 0x48, 0x2F};
  unsigned char color_19[3] = {0x6D, 0x00, 0x1A};
  unsigned char color_20[3] = {0x6A, 0x5C, 0xFF};
  unsigned char color_21[3] = {0x51, 0xE9, 0xF4};
  unsigned char color_22[3] = {0x51, 0x52, 0x52};
  unsigned char color_23[3] = {0x49, 0x3A, 0xC1};
  unsigned char color_24[3] = {0x36, 0x90, 0xEA};
  unsigned char color_25[3] = {0x24, 0x50, 0xA4};
  unsigned char color_26[3] = {0x00, 0xCC, 0xC0};
  unsigned char color_27[3] = {0x00, 0xCC, 0x78};
  unsigned char color_28[3] = {0x00, 0xA3, 0x68};
  unsigned char color_29[3] = {0x00, 0x9E, 0xAA};
  unsigned char color_30[3] = {0x00, 0x75, 0x6F};
  unsigned char color_31[3] = {0x00, 0x00, 0x00};

  //unsigned char raw_image_data[4000000];
  int fill_index = 0;
  while(fill_index < 12002000){
    raw_image_data[fill_index] = 0;
    fill_index++;
  }

  int raw_image_data_index = 0;
  unsigned int raw_image_data_x, raw_image_data_y,raw_image_data_xy;

  while(file_seek < 154681277){
    uncomp_data_size++;
    if(fgets(charbuff,256,in_file) == NULL){
      break;
    }
    if((charbuff[0] == 31 && charbuff[1] == 36 && charbuff[2] == 34 && charbuff[3] == 38)){
      continue;
    }

    int commaquote[6];
    int commaquote_index = 0;
    int commaquote_sweep_index = 0;

    while(commaquote_sweep_index <256){
      if(charbuff[commaquote_sweep_index] == comma){
        commaquote[commaquote_index] = commaquote_sweep_index;
        commaquote_index++;
      }
      commaquote_sweep_index++;
    }

    int xy_size = 3;
    int xy_size_limit = 3 - (commaquote[4] - commaquote[3] - 1);
    int xy_ogtrack = commaquote[4]-1;
    unsigned char raw_image_data_xychar[5] = "00000";
    raw_image_data_xychar[4] = '\0';
    while(xy_size > xy_size_limit){
      raw_image_data_xychar[xy_size] = charbuff[xy_ogtrack];
      xy_size--;
      xy_ogtrack--;
    }
    raw_image_data_x = atoi(raw_image_data_xychar);

    xy_size = 3;
    xy_size_limit = 3 - (commaquote[3] - commaquote[2] - 1);
    xy_ogtrack = commaquote[3] - 1;
    int xychar_reset = 0;
    while(xychar_reset < 4){
      raw_image_data_xychar[xychar_reset] = 48;
      xychar_reset++;
    }
    raw_image_data_xychar[4] = '\0';
    while(xy_size > xy_size_limit){
      raw_image_data_xychar[xy_size] = charbuff[xy_ogtrack];
      xy_size--;
      xy_ogtrack--;
    }
    raw_image_data_y = atoi(raw_image_data_xychar);
    raw_image_data_xy = (6001*raw_image_data_x)+(3*raw_image_data_y)+1;

    //color pallete import
    //reset read buffer "00000"
    xychar_reset = 0;
    while(xychar_reset < 4){
      raw_image_data_xychar[xychar_reset] = '0';
      xychar_reset++;
    }

    //extract palette index
    int palette_index = 0;
    //commaquote[2]-commaquote[1]-1;
    raw_image_data_xychar[3] = charbuff[commaquote[2]-1];
    //printf("%i\n", commaquote[2]-commaquote[1]);
    if(commaquote[2]-commaquote[1] == 3){
      raw_image_data_xychar[2] = charbuff[commaquote[2]-2];
    }
    palette_index = atoi(raw_image_data_xychar);

    //user id extraction
    /*
    if(commaquote[1]-commaquote[0] > user_hash_lenght){
      user_hash_lenght = commaquote[1]-commaquote[0];
    }
    printf("user_hash_lenght %i\n", user_hash_lenght);
    */
    unsigned char user_hash[9] = "000000000";
    int user_hash_sweep = commaquote[1];
    int user_hash_index = 8;
    while(user_hash_sweep > commaquote[0]){
      user_hash[user_hash_index] = charbuff[user_hash_sweep];
      user_hash_sweep--;
      user_hash_index--;
    }
    int user_hash_int = atoi(user_hash);
    if(user_hash_int == 27996){
      user_hash_count++;
      printf("user_hash_count %i %i %i\n", raw_image_data_x, raw_image_data_y, user_hash_count);
    }
    if(raw_image_data_y == 673 && raw_image_data_x == 452 && palette_index == 5){
      printf("xxxxxxxxxxxxxx user_hash_count %i \n", user_hash_int);
    }
    //printf("user_hash_int %i %i\n", user_hash_int, user_hash_count);


    //printf("palette %i,%i,%i\n", palette_index,raw_image_data_y,raw_image_data_x);
    switch (palette_index) {
      //printf("%s\n", "switch case");
      case 0:
        pixel_color[0] = 0xff;
        pixel_color[1] = 0xff;
        pixel_color[2] = 0xff;
        break;
      case 1:
        pixel_color[0] = 0xff;
        pixel_color[1] = 0xf8;
        pixel_color[2] = 0xb8;
        break;
      case 2:
        pixel_color[0] = 0xff;
        pixel_color[1] = 0xd6;
        pixel_color[2] = 0x35;
        break;
      case 3:
        pixel_color[0] = 0xff;
        pixel_color[1] = 0xb4;
        pixel_color[2] = 0x70;
        break;
      case 4:
        pixel_color[0] = 0xff;
        pixel_color[1] = 0xa8;
        pixel_color[2] = 0x00;
        break;
      case 5:
        pixel_color[0] = 0xff;
        pixel_color[1] = 0x99;
        pixel_color[2] = 0xaa;
        break;
      case 6:
        pixel_color[0] = 0xff;
        pixel_color[1] = 0x45;
        pixel_color[2] = 0x00;
        break;
      case 7:
        pixel_color[0] = 0xff;
        pixel_color[1] = 0x38;
        pixel_color[2] = 0x81;
        break;
      case 8:
        pixel_color[0] = 0xe4;
        pixel_color[1] = 0xab;
        pixel_color[2] = 0xff;
        break;
      case 9:
        pixel_color[0] = 0xde;
        pixel_color[1] = 0x10;
        pixel_color[2] = 0x7f;
        break;
      case 10:
        pixel_color[0] = 0xd4;
        pixel_color[1] = 0xd7;
        pixel_color[2] = 0xd9;
        break;
      case 11:
        pixel_color[0] = 0xbe;
        pixel_color[1] = 0x00;
        pixel_color[2] = 0x39;
        break;
      case 12:
        pixel_color[0] = 0xb4;
        pixel_color[1] = 0x4a;
        pixel_color[2] = 0xc0;
        break;
      case 13:
        pixel_color[0] = 0x9c;
        pixel_color[1] = 0x69;
        pixel_color[2] = 0x26;
        break;
      case 14:
        pixel_color[0] = 0x94;
        pixel_color[1] = 0xb3;
        pixel_color[2] = 0xff;
        break;
      case 15:
        pixel_color[0] = 0x89;
        pixel_color[1] = 0x8d;
        pixel_color[2] = 0x90;
        break;
      case 16:
        pixel_color[0] = 0x81;
        pixel_color[1] = 0x1e;
        pixel_color[2] = 0x9f;
        break;
      case 17:
        pixel_color[0] = 0x7e;
        pixel_color[1] = 0xed;
        pixel_color[2] = 0x56;
        break;
      case 18:
        pixel_color[0] = 0x6d;
        pixel_color[1] = 0x48;
        pixel_color[2] = 0x2f;
        break;
      case 19:
        pixel_color[0] = 0x6d;
        pixel_color[1] = 0x00;
        pixel_color[2] = 0x1a;
        break;
      case 20:
        pixel_color[0] = 0x6a;
        pixel_color[1] = 0x5c;
        pixel_color[2] = 0xff;
        break;
      case 21:
        pixel_color[0] = 0x51;
        pixel_color[1] = 0xe9;
        pixel_color[2] = 0xf4;
        break;
      case 22:
        pixel_color[0] = 0x51;
        pixel_color[1] = 0x52;
        pixel_color[2] = 0x52;
        break;
      case 23:
        pixel_color[0] = 0x49;
        pixel_color[1] = 0x3a;
        pixel_color[2] = 0xc1;
        break;
      case 24:
        pixel_color[0] = 0x36;
        pixel_color[1] = 0x90;
        pixel_color[2] = 0xea;
        break;
      case 25:
        pixel_color[0] = 0x24;
        pixel_color[1] = 0x50;
        pixel_color[2] = 0xa4;
        break;
      case 26:
        pixel_color[0] = 0x00;
        pixel_color[1] = 0xcc;
        pixel_color[2] = 0xc0;
        break;
      case 27:
        pixel_color[0] = 0x00;
        pixel_color[1] = 0xcc;
        pixel_color[2] = 0x78;
        break;
      case 28:
        pixel_color[0] = 0x00;
        pixel_color[1] = 0xa3;
        pixel_color[2] = 0x68;
        break;
      case 29:
        pixel_color[0] = 0x00;
        pixel_color[1] = 0x9e;
        pixel_color[2] = 0xaa;
        break;
      case 30:
        pixel_color[0] = 0x00;
        pixel_color[1] = 0x75;
        pixel_color[2] = 0x6f;
        break;
      case 31:
        pixel_color[0] = 0x00;
        pixel_color[1] = 0x00;
        pixel_color[2] = 0x00;
        break;
    }

    raw_image_data[raw_image_data_xy] = pixel_color[0];
    //printf("%x\n", pixel_color[0]);
    raw_image_data[raw_image_data_xy+1] = pixel_color[1];
    //printf("%x\n", pixel_color[1]);
    raw_image_data[raw_image_data_xy+2] = pixel_color[2];
    //printf("%x\n", pixel_color[2]);

    //printf("%x %x %x\n", pixel_color[0], pixel_color[1], pixel_color[2]);

    file_seek++;
    //printf("file_seek %i\n", file_seek);
    //printf("%i %i %i %i %i %i\n\n", commaquote[0], commaquote[1], commaquote[2], commaquote[3], commaquote[4], commaquote[5]);
  }
}

void get_raw_data(){
  FILE *in_file;
  in_file = fopen("comb_header.txt","rb");

  char charbuff[256];
  int file_seek = 0;
  char comma = ',';
  char quote = '\"';
  unsigned char pixel_color[3];

  //unsigned char raw_image_data[4000000];
  int fill_index = 0;
  while(fill_index < 12002000){
    raw_image_data[fill_index] = 0;
    fill_index++;
  }

  int raw_image_data_index = 0;
  unsigned int raw_image_data_x, raw_image_data_y,raw_image_data_xy;

  while(file_seek < 154681277 ){
    uncomp_data_size++;
    if(fgets(charbuff,256,in_file) == NULL){
      break;
    }
    if(!(charbuff[0] == 50 && charbuff[1] == 48 && charbuff[2] == 50 && charbuff[3] == 50)){
      continue;
    }

    int commaquote[6];
    int commaquote_index = 0;
    int commaquote_sweep_index = 0;

    while(commaquote_sweep_index <256){
      if(charbuff[commaquote_sweep_index] == comma){
        commaquote[commaquote_index] = commaquote_sweep_index;
        commaquote_index++;
      }
      if(charbuff[commaquote_sweep_index] == quote){
        commaquote[commaquote_index] = commaquote_sweep_index;
        commaquote_index++;
      }
      commaquote_sweep_index++;
    }

    int xy_size = 3;
    int xy_size_limit = 3 - (commaquote[4] - commaquote[3] - 1);
    int xy_ogtrack = commaquote[4]-1;
    unsigned char raw_image_data_xychar[5] = "00000";
    raw_image_data_xychar[4] = '\0';
    while(xy_size > xy_size_limit){
      raw_image_data_xychar[xy_size] = charbuff[xy_ogtrack];
      xy_size--;
      xy_ogtrack--;
    }
    raw_image_data_x = atoi(raw_image_data_xychar);

    xy_size = 3;
    xy_size_limit = 3 - (commaquote[5] - commaquote[4] - 1);
    xy_ogtrack = commaquote[5] - 1;
    int xychar_reset = 0;
    while(xychar_reset < 4){
      raw_image_data_xychar[xychar_reset] = 48;
      xychar_reset++;
    }
    raw_image_data_xychar[4] = '\0';
    while(xy_size > xy_size_limit){
      raw_image_data_xychar[xy_size] = charbuff[xy_ogtrack];
      xy_size--;
      xy_ogtrack--;
    }
    raw_image_data_y = atoi(raw_image_data_xychar);
    raw_image_data_xy = (6001*raw_image_data_y)+(3*raw_image_data_x)+1;

    pixel_color[0] = asciitohex(charbuff[commaquote[1]+2])*16 + asciitohex(charbuff[commaquote[1]+3]);
    pixel_color[1] = asciitohex(charbuff[commaquote[1]+4])*16 + asciitohex(charbuff[commaquote[1]+5]);
    pixel_color[2] = asciitohex(charbuff[commaquote[1]+6])*16 + asciitohex(charbuff[commaquote[1]+7]);

    //printf("x %i", raw_image_data_x);
    //printf(", y %i", raw_image_data_y);
    //printf(" %x %x %x\n", pixel_color[0], pixel_color[1], pixel_color[2]);

    raw_image_data[raw_image_data_xy] = pixel_color[0];
    //printf("%x\n", pixel_color[0]);
    raw_image_data[raw_image_data_xy+1] = pixel_color[1];
    //printf("%x\n", pixel_color[1]);
    raw_image_data[raw_image_data_xy+2] = pixel_color[2];
    //printf("%x\n", pixel_color[2]);
    file_seek++;
  }
  printf("b %i\n", raw_image_data[1128360]);
}

void compress_data(){
  FILE *size_est_file_ptr;
  size_est_file_ptr = fopen("size_est.bin","w+b");

  z_stream strm;
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;

  deflateInit(&strm, -1);
  strm.next_in = raw_image_data;
  strm.next_out = comp_image_data;
  strm.avail_in = 12002000;
  strm.avail_out = 12002000;
  printf("strm.avail_out pre deflate %i\n", strm.avail_out);
  deflate(&strm, Z_FINISH);
  printf("strm.avail_out post deflate %i\n", strm.avail_out);
  deflateEnd(&strm);
  comp_data_size = 12002000-strm.avail_out+32;
  //fwrite(comp_image_data,1,4000000-strm.avail_out+32  ,size_est_file_ptr);
  fwrite(raw_image_data,1,128 ,size_est_file_ptr);
}

void compute_crc32_hexsum(int crc32_base10){
  unsigned int crc32_input = crc32_base10;
  int crc32_quotient = 0;
  int crc32_remainder = 0;
  int crc32_index = 0;

  unsigned char crc32_expanded[16];
  while(crc32_index<8){
    crc32_quotient = crc32_input/16;
    crc32_remainder = crc32_input - (crc32_quotient*16);
    crc32_input = crc32_quotient;
    crc32_expanded[7-crc32_index] = crc32_remainder;
    crc32_index++;
  }
  crc32_index = 0;
  while (crc32_index<4) {
    crc32_checksum[crc32_index] = crc32_expanded[2*crc32_index]*16 + crc32_expanded[2*crc32_index+1];
    crc32_index = crc32_index+1;
  }
}

void write_idat_chunk(FILE *png_file){
  // idat_length initialisation and calculating from compressed data size comp_data_size
  unsigned char idat_size[4] = {0x00, 0x00, 0x00, 0x00};
  unsigned int idat_size_int = comp_data_size+4;
  idat_size[3] = idat_size_int % 256;
  idat_size_int = idat_size_int / 256;
  idat_size[2] = idat_size_int % 256;
  idat_size_int = idat_size_int / 256;
  idat_size[1] = idat_size_int % 256;
  idat_size_int = idat_size_int / 256;
  idat_size[0] = idat_size_int % 256;
  unsigned int idat_adler32_sum = 0;
  //idat_adler32_sum = adler32(idat_adler32_sum,raw_image_data,uncomp_data_size);

  // idat_signature = IDAT in hex
  unsigned char idat_signature[4] = {0x49, 0x44, 0x41, 0x54};

  int idat_crc32 = 0;
  idat_crc32 = crc32(idat_crc32, idat_signature, 4);
  idat_crc32 = crc32(idat_crc32, comp_image_data,comp_data_size);
  //compute_crc32_hexsum(idat_crc32);

  fwrite(idat_size, sizeof(idat_size),1,png_file);
  fwrite(idat_signature, sizeof(idat_signature),1,png_file);
  fwrite(comp_image_data, comp_data_size,1,png_file);
  compute_crc32_hexsum(idat_adler32_sum);
  fwrite(crc32_checksum,sizeof(crc32_checksum)/2,1,png_file);
  compute_crc32_hexsum(idat_crc32);
  fwrite(crc32_checksum,sizeof(crc32_checksum)/2,1,png_file);
}

void write_png_signature(FILE *png_file){
  unsigned char png_signature[8] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A };
  fwrite(png_signature,sizeof(png_signature),1,png_file);
}

void write_ihdr_chunk(FILE *png_file){
  // ihdr_lenght = number of bytes ihdr_signature+ihdr_data
  unsigned char ihdr_length[4] = {0x00, 0x00, 0x00, 0x0D};

  // ihdr_signature = IHDR in hex
  unsigned char ihdr_signature[4] = {0x49, 0x48, 0x44, 0x52};

  // ihdr_data = width, height, bit depth, color type, comp method, filter method, interlaced
  unsigned char ihdr_data[13] = {0x00, 0x00, 0x07, 0xd0, 0x00, 0x00, 0x07, 0xd0, 0x08, 0x02, 0x00, 0x00, 0x00};

  // computing crc32 checksum of ihdr_signature+ihdr_data
  unsigned int ihdr_crc32_compute = 0;
  ihdr_crc32_compute = crc32(ihdr_crc32_compute,ihdr_signature,4);
  ihdr_crc32_compute = crc32(ihdr_crc32_compute,ihdr_data,13);
  compute_crc32_hexsum(ihdr_crc32_compute);

  fwrite(ihdr_length,sizeof(ihdr_length),1,png_file);
  fwrite(ihdr_signature,sizeof(ihdr_signature),1,png_file);
  fwrite(ihdr_data,sizeof(ihdr_data),1,png_file);
  fwrite(crc32_checksum,sizeof(crc32_checksum)/2,1,png_file);
}

void write_iend_chunk(FILE *png_file){
  unsigned char iend_chunk[12] = {0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82};
  fwrite(iend_chunk,sizeof(iend_chunk),1,png_file);
}

int main(){
  FILE *png_file;
  png_file = fopen("proc_img.png","w+b");
  write_png_signature(png_file);
  write_ihdr_chunk(png_file);
  //fclose(png_file);
  //get_raw_data_v2();
  //fclose(png_file);
  //return 0;

  get_raw_data_v2();
  compress_data();
  printf("%i\n", comp_data_size);
  write_idat_chunk(png_file);
  write_iend_chunk(png_file);
  fclose(png_file);
  return 0;
}
