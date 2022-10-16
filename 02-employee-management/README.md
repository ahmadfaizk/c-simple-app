Buatlah program menggunakan array of struct untuk menghitung gaji bulanan pegawai, dengan ketentuan program sebagai berikut:<br>
Struct berisi data sebagai berikut: Nomor induk pegawai, nama pegawai, alamat, nomor HP, kategori.
Buatlah 4 menu sebagai berikut:
1.	Entry Pegawai<br>
Menu ini akan meminta data pegawai seperti Nomor Induk Pegawai (NIP), nama pegawai, alamat, no_hp, Kategori. Pastikan NIP tidak boleh ada yang sama. 
2.	Entry Jam Kerja Harian<br>
Input yang diminta adalah NIP. Jika NIP ketemu maka masukkan jam kerja harian, jika tidak maka tampilkan pesan kesalahan.<br>
Bila jumlah jam kerja > 8 jam, maka kelebihannya dihitung lembur yang besarnya 20.000/jam.<br>
Total jam lembur bulanan dapat diasumsikan selama 20 hari kerja.<br>
Contoh:<br>
Jam kerja harian = 10 jam, maka:<br>
a.	Jam lembur harian = 10 – 8 = 2 jam<br>
b.	Jam lembur bulanan = 2 x 20 = 40 jam
3.	Print Slip Gaji<br>
Input yang diminta adalah NIP. Jika NIP ketemu maka print slip gaji, jika tidak maka tampilkan pesan kesalahan.<br>
Komponen gaji terdiri atas gaji pokok dan upah lembur.<br>
    - Gaji pokok<br>
    Staff D1 	= Rp. 2.500.000<br>
    Staff D2	= Rp. 2.000.000<br>
    Staff D3	= Rp. 1.500.000<br>
    - Lembur 	= Rp. 20.000/jam
4.	Exit Program<br>
Keluar dari program.
