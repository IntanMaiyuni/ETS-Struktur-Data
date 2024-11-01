#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MAHASISWA 20 // Batas maksimum jumlah mahasiswa

// Struktur data untuk mahasiswa
struct Mahasiswa {
    char nama[50];
    char jenisKelamin;
    struct Mahasiswa *next;
};

// Counter untuk jumlah mahasiswa
int jumlahMahasiswa = 0;

// Fungsi untuk menambahkan mahasiswa ke lingkaran
void tambahKeLingkaran(struct Mahasiswa **head, char nama[], char jenisKelamin) {
    if (jumlahMahasiswa >= MAX_MAHASISWA) {
        printf("Tidak dapat menambahkan %s. Batas maksimum mahasiswa tercapai.\n", nama);
        return;
    }

    struct Mahasiswa *baru = (struct Mahasiswa *)malloc(sizeof(struct Mahasiswa));
    strcpy(baru->nama, nama);
    baru->jenisKelamin = jenisKelamin;

    if (*head == NULL) {
        *head = baru;
        baru->next = *head; // Circular link
    } else {
        struct Mahasiswa *temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = baru;
        baru->next = *head; // Circular link
    }
    jumlahMahasiswa++;
    printf("%s ditambahkan ke lingkaran.\n", nama);
}

// Fungsi untuk mengeluarkan mahasiswa dari lingkaran
void keluarDariLingkaran(struct Mahasiswa **head, char nama[]) {
    if (*head == NULL) {
        printf("Lingkaran kosong.\n");
        return;
    }

    struct Mahasiswa *temp = *head;
    struct Mahasiswa *prev = NULL;

    // Jika yang dihapus adalah head
    if (strcmp(temp->nama, nama) == 0) {
        if (temp->next == *head) {
            *head = NULL; // Hanya ada satu elemen
        } else {
            // Cari elemen terakhir dan update head
            while (temp->next != *head) {
                temp = temp->next;
            }
            temp->next = (*head)->next;
            *head = (*head)->next;
        }
        free(temp);
        jumlahMahasiswa--;
        printf("%s keluar dari lingkaran.\n", nama);
        return;
    }

    // Jika yang dihapus adalah elemen lainnya
    temp = *head;
    do {
        prev = temp;
        temp = temp->next;
        if (strcmp(temp->nama, nama) == 0) {
            prev->next = temp->next;
            free(temp);
            jumlahMahasiswa--;
            printf("%s keluar dari lingkaran.\n", nama);
            return;
        }
    } while (temp != *head);

    printf("Mahasiswa tidak ditemukan dalam lingkaran.\n");
}

// Fungsi untuk mencetak lingkaran besar (semua mahasiswa)
void cetakLingkaran(struct Mahasiswa *head) {
    if (head == NULL) {
        printf("Lingkaran kosong.\n");
        return;
    }

    struct Mahasiswa *temp = head;
    printf("Lingkaran besar (semua mahasiswa):\n");
    do {
        printf("- %s (Jenis Kelamin: %c)\n", temp->nama, temp->jenisKelamin);
        temp = temp->next;
    } while (temp != head);
}

// Fungsi untuk memisahkan lingkaran mahasiswa dan mahasiswi
void pisahLingkaran(struct Mahasiswa *head) {
    if (head == NULL) {
        printf("Lingkaran kosong.\n");
        return;
    }

    struct Mahasiswa *temp = head;

    // Lingkaran Mahasiswa Laki-laki
    printf("\nLingkaran Mahasiswa Laki-laki:\n");
    do {
        if (temp->jenisKelamin == 'L') {
            printf("- %s\n", temp->nama);
        }
        temp = temp->next;
    } while (temp != head);

    // Lingkaran Mahasiswi Perempuan
    printf("\nLingkaran Mahasiswi Perempuan:\n");
    temp = head;
    do {
        if (temp->jenisKelamin == 'P') {
            printf("- %s\n", temp->nama);
        }
        temp = temp->next;
    } while (temp != head);
}

// Fungsi utama
int main() {
    struct Mahasiswa *head = NULL;
    int pilihan;

    // Menambahkan beberapa mahasiswa awal
    tambahKeLingkaran(&head, "Irsyad", 'L');
    tambahKeLingkaran(&head, "Arsyad", 'L');
    tambahKeLingkaran(&head, "Cindy", 'P');
    tambahKeLingkaran(&head, "Dina", 'P');
    tambahKeLingkaran(&head, "Budi", 'L');

    do {
        printf("\nPilihan:\n");
        printf("1. Tambah Mahasiswa ke Lingkaran\n");
        printf("2. Keluarkan Mahasiswa dari Lingkaran\n");
        printf("3. Lihat Status Lingkaran (Besar)\n");
        printf("4. Pisahkan Lingkaran Mahasiswa dan Mahasiswi\n");
        printf("5. Keluar\n");
        printf("Pilih opsi (1-5): ");
        scanf("%d", &pilihan);

        if (pilihan == 1) {
            char nama[50];
            char jenisKelamin;
            printf("Masukkan nama mahasiswa: ");
            scanf("%s", nama);
            printf("Masukkan jenis kelamin (L/P): ");
            scanf(" %c", &jenisKelamin);

            tambahKeLingkaran(&head, nama, jenisKelamin);

        } else if (pilihan == 2) {
            char nama[50];
            printf("Masukkan nama mahasiswa yang ingin keluar: ");
            scanf("%s", nama);
            keluarDariLingkaran(&head, nama);

        } else if (pilihan == 3) {
            cetakLingkaran(head);

        } else if (pilihan == 4) {
            cetakLingkaran(head); // Tampilkan lingkaran besar dulu
            pisahLingkaran(head); // Lalu pisahkan menjadi lingkaran laki-laki dan perempuan

        } else if (pilihan == 5) {
            printf("Keluar dari program.\n");
        } else {
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (pilihan != 5);

    return 0;
}
