 /* * Menu yang sangat sederhana pada tampilan OLED (dengan 8 baris teks). * Menampilkan item menu dari menu array. Maks. jumlah barang 7. * * Sketsa ini menggunakan library "U8g2", "Bounce2" dan menggunakan 3 tombol (atas/bawah/pilih). * */

#include <U8g2lib.h>

#include <Bounce2.h>

byte button_pins[] = {9, 5, 6}; // pin tombol, 4,5 = atas/bawah, 6 = pilih

#define NUMBUTTONS sizeof(button_pins)

Bounce * buttons = new Bounce[NUMBUTTONS];

U8X8_SSD1306_128X64_NONAME_HW_I2C display(U8X8_PIN_NONE);

#define MENU_SIZE 6

char *menu[MENU_SIZE] = { "MERAH", "PUTIH", "BIRU", "HIJAU", "KUNING", "MATI" };

int cursor=0;

void setup() {

  Serial.begin(9600);

  pinMode(2, OUTPUT);

  pinMode(3, OUTPUT);

  pinMode(4, OUTPUT);

  pinMode(7, OUTPUT);

  // Buat input & aktifkan resistor pull-up pada pin saklar

  for (int i=0; i<NUMBUTTONS; i++) {

    buttons[i].attach( button_pins[i], INPUT_PULLUP); // atur instance bouncing untuk tombol saat ini

    buttons[i].interval(25); // interval dengan ms (mili second)

  }

  

  display.begin();

  display.setPowerSave(0);

  display.setFont(u8x8_font_pxplusibmcgathin_f);

  showMenu();

}

void loop() {

  // proses tekan tombol:

  for (int i = 0; i<NUMBUTTONS; i++) {

    buttons[i].update(); // Perbarui instance Bounce

    if ( buttons[i].fell() ) { // Jika jatuh

      if (i==2) { // pilih

         display.clearLine(7);

         display.setCursor(0,7);

         display.print(">>");

         display.print(menu[cursor]);

         executeChoice(cursor);

      }

      else {

        // erase previous cursor:

        display.setCursor(0,cursor);

        display.print(' ');

        if (i==0) { // atas

          cursor++;

          if (cursor>(MENU_SIZE-1)) cursor=0;

        }

        else { // bawah

          cursor--;

          if (cursor<0) cursor=(MENU_SIZE-1);

        }

        // tampilkan kursor pada baris baru:

        display.setCursor(0,cursor);

        display.print('>');

      }

    } // akhir jika tombol jatuh ...

  } // akhiri untuk-loop pemeriksaan tombol

}

/** * Hapus tampilan dan tampilkan menu. */

void showMenu() {

  cursor=0;

  display.clearDisplay();

  // show menu items:

  for (int i = 0; i<MENU_SIZE; i++) {

    display.drawString(2,i,menu[i]);

  }

  display.setCursor(0,0);

  display.print('>');

}

/** * Jalankan tugas yang cocok dengan item menu yang dipilih. */

void executeChoice(int choice) {

  switch(choice) {

      case 0 :

                digitalWrite(2, HIGH);

                Serial.print("Kamu Memilih Menu "); Serial.print(choice); Serial.print(" - "); Serial.println(menu[choice]);

                break;

      case 1 :

                digitalWrite(3, HIGH);

                Serial.print("Kamu Memilih Menu "); Serial.print(choice); Serial.print(" - "); Serial.println(menu[choice]);

                break;

      case 2 :

                digitalWrite(4, HIGH);

                Serial.print("Kamu Memilih Menu"); Serial.print(choice); Serial.print(" - "); Serial.println(menu[choice]);

                break;

      case 3 :

                digitalWrite(7, HIGH);

                Serial.print("Kamu Memilih Menu "); Serial.print(choice); Serial.print(" - "); Serial.println(menu[choice]);

                break;

      case 4 :

                Serial.print("Kamu Memilih Menu "); Serial.print(choice); Serial.print(" - "); Serial.println(menu[choice]);

                break;

      case 5 :

                digitalWrite(2, LOW);

                digitalWrite(3, LOW);

                digitalWrite(4, LOW);

                digitalWrite(7, LOW);

                Serial.print("Matikan  Semua");

      default :

                Serial.print("Kamu Memilih Menu"); Serial.print(choice); Serial.print(" - "); Serial.println(menu[choice]);

                break;

  }

  

}
