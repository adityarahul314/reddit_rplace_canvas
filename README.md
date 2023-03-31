# Reddit r/place canvas rendering using C

Quick and Effiecient generation of frames for timelapse of reddit rplace canvas. Includes custom IHDR, IDAT and IEND chunks to optimise image processing. uses inplace memory with peak mem usage less than 15MB.

Requirements:
  - "zlib.h" zlib compression library to compress image to reasonable size.

Usage:

```
  gcc draw_image.c -lz -o draw_image.o
  ./draw_image.o {number of entries to process from data set, max 154681277}
  ./draw_image.o 1000 //renders image using first 1000 entries
```
Data Set:
  - included data set contains only first 10 entries. complete data set is listed at the end.
  - data format is "timestamp,user_hash,color,x_coordinate,y_coordinate,x2_coordinate,y2_coordinate"
  - color palette is
  ```
      0: #FFFFFF   8: #E4ABFF 16: #811E9F 24: #3690EA
      1: #FFF8B8   9: #DE107F 17: #7EED56 25: #2450A4
      2: #FFD635  10: #D4D7D9 18: #6D482F 26: #00CCC0
      3: #FFB470  11: #BE0039 19: #6D001A 27: #00CC78
      4: #FFA800  12: #B44AC0 20: #6A5CFF 28: #00A368
      5: #FF99AA  13: #9C6926 21: #51E9F4 29: #009EAA
      6: #FF4500  14: #94B3FF 22: #515252 30: #00756F
      7: #FF3881  15: #898D90 23: #493AC1 31: #000000
  ```
  - complete data set "2022-compact.csv" is obtained from https://drive.google.com/file/d/1NuKb6oaRqnILN0MKYKqMXwHDDbnQMAV_/view
  - data set can be extracted using !(zstandard)[https://github.com/facebook/zstd/]
  ```
  zstd -d 2022-compact.csv.zst
  ```
  - credit for data set: https://www.reddit.com/r/place/comments/txvk2d/comment/i3utewb/?utm_source=share&utm_medium=web2x&context=3
