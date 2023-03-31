#include <stdio.h>
#include <zlib.h>

int main(){
  FILE *scrap;
  scrap = fopen("scrap.bin","w+b");
  unsigned char pixel_color[3];
  pixel_color[0] = 0xff;
  pixel_color[1] = 0x12;
  pixel_color[2] = 0xdd;

  int uncomp_data_size = 160353106;
  //154681277
  //unsigned char raw_image_data[8381253];
  unsigned char raw_image_data[8381253];
  unsigned int idat_adler32_sum = 0;
  //idat_adler32_sum = adler32(idat_adler32_sum,raw_image_data,uncomp_data_size);

  int window_size = 65536;
  int window_seek = 0;
  uncomp_data_size = uncomp_data_size + 65536;
  while(window_seek < uncomp_data_size){
    idat_adler32_sum = adler32(idat_adler32_sum,raw_image_data,window_size);
  }


  fwrite(pixel_color,3,1,scrap);
  fclose(scrap);
  return 0;
}
