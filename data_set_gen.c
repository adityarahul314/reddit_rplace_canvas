#include <stdio.h>
#include <zlib.h>

int main(){
  FILE *scrap;
  scrap = fopen("xx_header.txt","w+b");
  unsigned char buffer[] = "2022,user_id,#FF0000,\"103,1512\"\n";
  unsigned char buffer_1[] = "2022-04-04 21:13:48.993 UTC,0cSPtex/zsj8oFNjQM0V+sKmD+DB/aK3pJb4gRbRodHVPPT6wiF+d5/ayYxBQdbYDVUb5YazL8oyEgj11Ev4Ng==,#FFFFFF,\"";
  unsigned char buffer_2[] = ",";
  unsigned char buffer_3[] = "\"\n";

  int count = 0;
  char count_char[1] = "0";
  while(count < 2000){
    //ount_char[0] = count;
    fwrite(buffer_1,sizeof(buffer_1),1,scrap);
    fprintf(scrap, "%i", count);
    fwrite(buffer_2,sizeof(buffer_2),1,scrap);
    fprintf(scrap, "%i", count);
    fwrite(buffer_3,sizeof(buffer_3),1,scrap);
    count++;
  }
  fclose(scrap);
  return 0;
}
