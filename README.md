# PREDIKSI KASUS COVID-19 DENGAN BACKPROPAGATION MENGGUNAKAN BORLAND CPP

Berikut adalah Implementasi algoritma Backpropagation untuk memprediksi penambahan kasus harian COVID-19 di Indonesia dari tanggal 09 Maret 2020 sampai 5 Desember 2020 dengan menggunakan Borland C++.

## Metode
1. Inisialisasi semua bobot dan bias dengan bilangan real secara acak (0,1)
2. Jika kondisi penghentian belum terpenuhi (iter>max iter), lakukan 3 sampai 8. Jika kondisi pemberhentian terpenuhi (iter< max iter) langsung menuju langkah 9
3. Untuk setiap pasang data pelatihan, lakukan 4 sampai 8

Fase II  : Perubahan bobot

4. Setiap unit input (xi, dengan i=1,2,…,n ) menerima sinyal input xi dan meneruskan sinyal ke unit tersembunyi di atasnya
5. Setiap hidden unit (zj, dengan j=1,2,…,p ) akan menjumlahkan sinyal input yang sudah berbobot dan biasnya:
   
       zinj = v0j + ∑(xi • vij)

    Dan menggunakan fungsi aktivasi yang telah ditentukan untuk menghitung sinyal output dan hidden unit yang bersangkutan :

        zj = f(zinj)

    Lalu mengirim sinyal output tersebut ke seluruh unit output.
6. Hitung semua keluaran jaringan di unit (yk, dengan k=1,2,…,m) yang menjumlahkan sinyal input yang sudah berbobot dan biasnya :

        yink= w0k + ∑(zj • wjk )

    Dan menggunakan fungsi aktivasi yang telah ditentukan untuk menghitung sinyal output dan unit output yang bersangkutan :

        zj = f(zinj)

    Lalu mengirim sinyal output tersebut ke seluruh unit pada unit output.

Fase II  : Perubahan bobot

7. Hitung semua perubahan bobot Perubahan bobot garis yang menuju ke unit keluaran :
  
        𝑤𝑘𝑗(𝑏𝑎𝑟𝑢) =  𝑤𝑘𝑗(𝑙𝑎𝑚𝑎) + ∆w𝑘𝑗

Perubahan bobot garis yang menuju ke unit keluaran :

        𝑣𝑗𝑖(𝑏𝑎𝑟𝑢) =  v𝑗𝑖(𝑙𝑎𝑚𝑎) + ∆𝑣𝑗𝑖

8. Memeriksa stop condition. Jika stop condition telah terpenuhi, pelatihan jaringan dapat dihentikan. 
9. Setelah pelatihan selesai dilakukan, bobot dan bias terbaik dapat dipakai untuk uji validasi. 

## Dataset
Data yang akan digunakan adalah data sekunder dari Gugus Tugas Percepatan Penanganan COVID-19 Republik Indonesia. Data yang digunakan adalah data penambahan kasus harian COVID-19 di Indonesia dari tanggal 09 Maret 2020 sampai 5 Desember 2020, dengan jumlah keseluruhan ada 272 data. Data keseluruhan tersebut dibagi menjadi dua yaitu data training sebesar 70% dan data validasi 30%.

## Arsitektur Jaringan 
```
Input layer sebanyak 3 unit.
Hidden layer sebanyak 3 unit.
Output layer sebanyak 1 unit.
```

## Deployment
File berikut harus berada pada satu folder :
```
PROGRAMFIXXXXBANGET.CPP
DataUji.txt
Datalatih.txt
targetlatih.txt
targetuji.txt
```
## Authors
* **Mega Musfivawati** - *Initial work* - [megamusfiva](https://github.com/megamusfiva/)
