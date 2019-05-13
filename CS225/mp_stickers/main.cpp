#include "Image.h"
#include "StickerSheet.h"

int main() {

  Image picture;
  Image sticker1;
  Image sticker2;
  Image sticker3;

  picture.readFromFile("alma.png");
  sticker1.readFromFile("st1.png");
  sticker2.readFromFile("st2.png");
  sticker3.readFromFile("st3.png");

  cs225::StickerSheet st(picture, 4);


  st.addSticker(sticker1, 100, 100);
  st.addSticker(sticker2, 500, 100);
  st.addSticker(sticker3, 300, 400);
  Image output = st.render();

  output.writeToFile("myImage.png");



  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  return 0;
}
